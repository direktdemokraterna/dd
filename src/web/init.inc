<?php 
DEFINE('VERSION', 0.201);

session_start();

date_default_timezone_set('Europe/Stockholm');

// Declares unset variables
if(empty($_GET['action'])) $_GET['action']=null; 
if(empty($_GET['type'])) $_GET['type']=null; 
if(empty($_GET['sort'])) $_GET['sort']=null; 
if(empty($_GET['filter'])) $_GET['filter']=null; 

set_include_path(get_include_path() . PATH_SEPARATOR . 'helpers');

// Includes files
require(dirname(__FILE__)."/helpers/util.inc");

require(dirname(__FILE__)."/../../config.inc");
require(dirname(__FILE__)."/../includes/config_default.inc");

require(dirname(__FILE__)."/helpers/general_helpers.inc");
require(dirname(__FILE__)."/helpers/navigation_helpers.inc");
require(dirname(__FILE__)."/helpers/vote_helpers.inc");
require(dirname(__FILE__)."/helpers/crypt_helpers.inc");
require(dirname(__FILE__)."/helpers/class-phpass.php");
require(dirname(__FILE__)."/helpers/session.inc");

require(dirname(__FILE__)."/helpers/cache/shmop_cache.inc");

require(dirname(__FILE__)."/helpers/db/db.inc");
require(dirname(__FILE__)."/helpers/db/db_general.inc");
require(dirname(__FILE__)."/helpers/db/db_user.inc");
require(dirname(__FILE__)."/helpers/db/db_admin.inc");
require(dirname(__FILE__)."/helpers/db/db_forum_admin.inc");
require(dirname(__FILE__)."/helpers/db/db_vote_admin.inc");
require(dirname(__FILE__)."/helpers/db/db_forum.inc");
require(dirname(__FILE__)."/helpers/db/db_message.inc");
require(dirname(__FILE__)."/helpers/db/db_workgroup.inc");
require(dirname(__FILE__)."/helpers/db/db_error.inc");
require(dirname(__FILE__)."/helpers/db/db_calendar.inc");
require(dirname(__FILE__)."/helpers/db/db_vote.inc");
require(dirname(__FILE__)."/helpers/db/db_prop.inc");
require(dirname(__FILE__)."/helpers/db/db_delegate.inc");
require(dirname(__FILE__)."/helpers/db/db_constituency.inc");
require(dirname(__FILE__)."/helpers/db/db_treasurer.inc");
require(dirname(__FILE__)."/helpers/db/db_user_password_reset_tokenuser.inc");
require(dirname(__FILE__)."/helpers/db/db_notice.inc");

require(dirname(__FILE__)."/helpers/i18n/controller.inc");
require(dirname(__FILE__)."/helpers/i18n/selectors.inc");
require(dirname(__FILE__)."/helpers/i18n/template.inc");
require(dirname(__FILE__)."/helpers/i18n/template_candidate.inc");
require(dirname(__FILE__)."/helpers/i18n/template_match.inc");
require(dirname(__FILE__)."/helpers/i18n/template_engine.inc");
require(dirname(__FILE__)."/helpers/i18n/template_storage.inc");
require(dirname(__FILE__)."/helpers/i18n/templates.inc");
require(dirname(__FILE__)."/helpers/i18n/translator.inc");
require(dirname(__FILE__)."/helpers/i18n/translator_match.inc");
require(dirname(__FILE__)."/helpers/i18n/translation_identifier.inc");
require(dirname(__FILE__)."/helpers/i18n/noun_modifier.inc");
require(dirname(__FILE__)."/helpers/i18n/translation_storage.inc");
require(dirname(__FILE__)."/helpers/i18n/adjectives.inc");
require(dirname(__FILE__)."/helpers/i18n/nouns.inc");
require(dirname(__FILE__)."/helpers/i18n/pronouns.inc");
require(dirname(__FILE__)."/helpers/i18n/verbs.inc");
require(dirname(__FILE__)."/helpers/i18n/util.inc");
require(dirname(__FILE__)."/helpers/i18n/word_form.inc");

require(dirname(__FILE__)."/helpers/i18n/thesaurus/abbreviations.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/adverbs.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/adjectives.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/conjunctions.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/interjections.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/modifiers.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/names.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/nouns.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/phrases.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/prepositions.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/pronouns.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/quantifiers.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/time_and_date.inc");
require(dirname(__FILE__)."/helpers/i18n/thesaurus/verbs.inc");

require(dirname(__FILE__)."/helpers/logic/calendar.inc");
require(dirname(__FILE__)."/helpers/logic/constituency.inc");
require(dirname(__FILE__)."/helpers/logic/delegate.inc");
require(dirname(__FILE__)."/helpers/logic/forum.inc");
require(dirname(__FILE__)."/helpers/logic/global.inc");
require(dirname(__FILE__)."/helpers/logic/resetpassword.inc");
require(dirname(__FILE__)."/helpers/logic/text.inc");
require(dirname(__FILE__)."/helpers/logic/user.inc");
require(dirname(__FILE__)."/helpers/logic/util.inc");
require(dirname(__FILE__)."/helpers/logic/vote.inc");

require(dirname(__FILE__)."/helpers/view/general.inc");
require(dirname(__FILE__)."/helpers/view/generators.inc");
require(dirname(__FILE__)."/helpers/view/controls.inc");
require(dirname(__FILE__)."/helpers/view/calendar.inc");
require(dirname(__FILE__)."/helpers/view/delegate.inc");
require(dirname(__FILE__)."/helpers/view/forum.inc");
require(dirname(__FILE__)."/helpers/view/index.inc");
require(dirname(__FILE__)."/helpers/view/member.inc");
require(dirname(__FILE__)."/helpers/view/message.inc");
require(dirname(__FILE__)."/helpers/view/vote.inc");
require(dirname(__FILE__)."/helpers/view/workgroup.inc");

setlocale(LC_ALL, 'swedish', 'sv_SE', 'sv_SE.UTF-8');

$app_folder_name = str_replace('index.php', '', $_SERVER['PHP_SELF']);
$app_folder_name = str_replace('bli-medlem/', '', $app_folder_name);
$app_folder_name = str_replace('aktivering/', '', $app_folder_name);
$app_folder_name = str_replace('aterstall-losenord/', '', $app_folder_name);
DEFINE('BASE_URL', (!empty($_SERVER['HTTPS']) ? 'https' : 'http') . '://'
	. $_SERVER['HTTP_HOST'] . $app_folder_name);
DEFINE('BASE_FOLDER', $_SERVER['DOCUMENT_ROOT'] . $app_folder_name);

define_if_undefined("USERIMG_PATH", BASE_URL . "images/userimg/");
define_if_undefined("USERIMG_FOLDER", BASE_FOLDER . "images/userimg/");

define_if_undefined("DD_PRIVATE_KEY", file_get_contents(__DIR__ . "/helpers/keys/dd_private_key.txt"));
define_if_undefined("DD_PUBLIC_KEY", file_get_contents(__DIR__ . "/helpers/keys/dd_public_key.txt"));
define_if_undefined("DD_ANON_PUBLIC_KEY", file_get_contents(__DIR__ . "/helpers/keys/dd_anon/dd_anon_public_key.txt"));
