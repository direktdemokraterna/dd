<?php 
session_start();

date_default_timezone_set('Europe/Stockholm');

// Declares unset variables
if(empty($_GET['action'])) $_GET['action']=null; 
if(empty($_GET['type'])) $_GET['type']=null; 
if(empty($_GET['sort'])) $_GET['sort']=null; 
if(empty($_GET['filter'])) $_GET['filter']=null; 

set_include_path(get_include_path() . PATH_SEPARATOR . 'helpers');

// Includes files
include(dirname(__FILE__)."/config.inc");

include(dirname(__FILE__)."/helpers/general_helpers.inc");
include(dirname(__FILE__)."/helpers/navigation_helpers.inc");
include(dirname(__FILE__)."/helpers/forum_helpers.inc");
include(dirname(__FILE__)."/helpers/vote_helpers.inc");
include(dirname(__FILE__)."/helpers/crypt_helpers.inc");
include(dirname(__FILE__)."/helpers/class-phpass.php");
include(dirname(__FILE__)."/helpers/session.inc");

include(dirname(__FILE__)."/helpers/db/db.inc");
include(dirname(__FILE__)."/helpers/db/db_general.inc");
include(dirname(__FILE__)."/helpers/db/db_user.inc");
include(dirname(__FILE__)."/helpers/db/db_admin.inc");
include(dirname(__FILE__)."/helpers/db/db_forum_admin.inc");
include(dirname(__FILE__)."/helpers/db/db_vote_admin.inc");
include(dirname(__FILE__)."/helpers/db/db_forum.inc");
include(dirname(__FILE__)."/helpers/db/db_message.inc");
include(dirname(__FILE__)."/helpers/db/db_workgroup.inc");
include(dirname(__FILE__)."/helpers/db/db_error.inc");
include(dirname(__FILE__)."/helpers/db/db_calendar.inc");
include(dirname(__FILE__)."/helpers/db/db_vote.inc");
include(dirname(__FILE__)."/helpers/db/db_prop.inc");
include(dirname(__FILE__)."/helpers/db/db_delegate.inc");
include(dirname(__FILE__)."/helpers/db/db_constituency.inc");

include(dirname(__FILE__)."/helpers/i18n/controller.inc");
include(dirname(__FILE__)."/helpers/i18n/engine.inc");
include(dirname(__FILE__)."/helpers/i18n/selectors.inc");
include(dirname(__FILE__)."/helpers/i18n/translator.inc");
include(dirname(__FILE__)."/helpers/i18n/adjectives.inc");
include(dirname(__FILE__)."/helpers/i18n/nouns.inc");
include(dirname(__FILE__)."/helpers/i18n/pronouns.inc");
include(dirname(__FILE__)."/helpers/i18n/verbs.inc");

include(dirname(__FILE__)."/helpers/i18n/thesaurus/adjectives.inc");
include(dirname(__FILE__)."/helpers/i18n/thesaurus/conjunctions.inc");
include(dirname(__FILE__)."/helpers/i18n/thesaurus/modifiers.inc");
include(dirname(__FILE__)."/helpers/i18n/thesaurus/names.inc");
include(dirname(__FILE__)."/helpers/i18n/thesaurus/nouns.inc");
include(dirname(__FILE__)."/helpers/i18n/thesaurus/phrases.inc");
include(dirname(__FILE__)."/helpers/i18n/thesaurus/prepositions.inc");
include(dirname(__FILE__)."/helpers/i18n/thesaurus/pronouns.inc");
include(dirname(__FILE__)."/helpers/i18n/thesaurus/quantifiers.inc");
include(dirname(__FILE__)."/helpers/i18n/thesaurus/time_and_date.inc");
include(dirname(__FILE__)."/helpers/i18n/thesaurus/verbs.inc");

include(dirname(__FILE__)."/helpers/logic/calendar.inc");
include(dirname(__FILE__)."/helpers/logic/constituency.inc");
include(dirname(__FILE__)."/helpers/logic/delegate.inc");
include(dirname(__FILE__)."/helpers/logic/forum.inc");
include(dirname(__FILE__)."/helpers/logic/global.inc");
include(dirname(__FILE__)."/helpers/logic/user.inc");
include(dirname(__FILE__)."/helpers/logic/util.inc");
include(dirname(__FILE__)."/helpers/logic/vote.inc");

include(dirname(__FILE__)."/helpers/view/calendar.inc");
include(dirname(__FILE__)."/helpers/view/forum.inc");
include(dirname(__FILE__)."/helpers/view/general.inc");
include(dirname(__FILE__)."/helpers/view/generators.inc");
include(dirname(__FILE__)."/helpers/view/index.inc");
include(dirname(__FILE__)."/helpers/view/member.inc");
include(dirname(__FILE__)."/helpers/view/vote.inc");
include(dirname(__FILE__)."/helpers/view/workgroup.inc");

switch (\I18n\controller::get_language()) {
	case 'en': 
		setlocale(LC_ALL, NULL);
		break;
	case 'sv': 
		setlocale(LC_ALL, 'swedish', 'sv_SE', 'sv_SE.ISO8859-1');
		break;
}

$app_folder_name = str_replace('index.php', '', $_SERVER['PHP_SELF']);
DEFINE('BASE_URL', (!empty($_SERVER['HTTPS']) ? 'https' : 'http') . '://' 
	. $_SERVER['HTTP_HOST'] . $app_folder_name);

define("USERIMG_PATH", BASE_URL . "images/userimg/");

define("DD_PRIVATE_KEY", file_get_contents(__DIR__ . "/helpers/keys/dd_private_key.txt"));
define("DD_PUBLIC_KEY", file_get_contents(__DIR__ . "/helpers/keys/dd_public_key.txt"));
define("DD_ANON_PUBLIC_KEY", file_get_contents(__DIR__ . "/helpers/keys/dd_anon/dd_anon_public_key.txt"));

?>