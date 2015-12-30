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
include(dirname(__FILE__)."/helpers/db/db_member_admin.inc");
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

DEFINE('BASE_URL', (!empty($_SERVER['HTTPS']) ? 'https' : 'http') . '://' . $_SERVER['HTTP_HOST'] . '/dd/');

define("RSA_PRIVATE_KEY", "-----BEGIN RSA PRIVATE KEY----- MIIEogIBAAKCAQEAsIpWVPRtuUJci9JuZEQYExLoWrWqCO7KImTVRRryZKCQ8ywg i9bfS7inDpOvrmiMORomHjj7SDRySIzB8hpyC+DLVQEKz3vVs5bafzGxQcBdvdI3 bXmCEd3mkmwaWhPcwTbARS71VbOTMezz7EQMjsSO4L6B74vblIJV+t+Q5D4v+FU1 EgVCR22o3niM8MaqGAQTDpwC08cYQ2K4Iog5Wh8Qv53JeJv0h6qQC7iB1Pf5oLrX tXxF/ozzBapFzRPFCj/Yvfx/7NPj1qFD/z4LkJAgWWnrpUEgwj55Lm6YHZPJThul x5IkvUdPjjtaMx4ktVaV1pj1g0ulB59It2E54wIDAQABAoIBAAOlPHNXpfzJdB8t Be6+TmyPNOR+oNeILfz4B3fJJSoGLy536E1XvArhWFqSmr7N70TuMQBQKk9k43Rz d6PLGQGWyQwYNlCitkuvLBOsg1EGXfxhkjE805gQp9/sXItX1dsL7693pBHhE4NY T12L6ch4iMzD3x7Pszj48gaSrEUr3KdiSY3qqx8cRRcQJDfTrRjOnx5JYWMPUAIU P+uoVrZIbKNWPPcdm5ErkcSJWPw48B8s47zrlEglNCdrRYp3n70cx+SuOd2rx2ND NV6EUVXTBz2gu6HOvYFChv4L9XmspCsaDnqNPgxbh0fJkXP3i/DHHJASxwKG1eY+ ybkuEDUCgYEAshohDFDmLe98MvuCCbjpB0A8m6To5mUqXBG0xnLqj+dVmZTiZTbr l/WwCRwEoDTLVOzTTovCtsFKM3Bcmj0mIdsc5bEMiV9w7kb+OTj28gHUVPxiOyqd KhIPJ5P3LKpT4Jk2gNgILuDKIMFq7hYt6ZWWlDwq6NGephtYuCJoRc0CgYEA/cFZ E9AUiR7V0rRnJXQ66POQeIItmhHACjB1NoDv5g2wanF8K+mUdnPWXry4HVUgmp4c N2JW3t/CE7OaZ2q08WEEJuPAgtuxfYbSiTWHigwe2VUNWmGjR78Q8pIYePgnyDft MATy2obRzx3EvjlQRQz5ixLr+zuu/vu7pXQAzm8CgYBX5b1ZrrNrCD5riuTql2+q PHGs/v5SdqspNTPanOxWiP0eBvSUrz4miQKP/FvsFSIkj5zZrvAx8cMFD/cjx/oB y3m/glmFkqzRbAgbhZmaZny8VLLGMInQMYl5JvVd/dHXjsXvYK7pM9eNwudbCWcv WLwv/GHQ9WMu52ApwBFmIQKBgCQ8y0rACV63j5OCfcRkf9EqjzQWawq4hDMwTlzV Nu0kgVACGthuh+wOiMuIqcZOlNRfxenG2l8Dl0SW/nLMU0CxORWQqrpFQ2iIq2I6 ybtWFcW1lq2UievCBlqNsH79+ThnfDDCVCgO3sF0H9eGeccSnkRVFGwRTuFM87Qi B8dzAoGAZgaDoRoVmGwy4xsTOlwISdUfmYvGjLEFujUHTC2ky4x7CjVoAGtSycJx U6wdMOfAZG/NeuRaop3Jz35H7+zFr2195pnKgJirdvAcwPO2hoKv8xF9yGU6Pp1Q 7dBfULUhppU0IT7hX9fONkaKk9TzpU4R/paFDTxPTuiA1v5rLlg= -----END RSA PRIVATE KEY-----");
define("DD_PUBLIC_KEY", "-----BEGIN PUBLIC KEY----- MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAsIpWVPRtuUJci9JuZEQY ExLoWrWqCO7KImTVRRryZKCQ8ywgi9bfS7inDpOvrmiMORomHjj7SDRySIzB8hpy C+DLVQEKz3vVs5bafzGxQcBdvdI3bXmCEd3mkmwaWhPcwTbARS71VbOTMezz7EQM jsSO4L6B74vblIJV+t+Q5D4v+FU1EgVCR22o3niM8MaqGAQTDpwC08cYQ2K4Iog5 Wh8Qv53JeJv0h6qQC7iB1Pf5oLrXtXxF/ozzBapFzRPFCj/Yvfx/7NPj1qFD/z4L kJAgWWnrpUEgwj55Lm6YHZPJThulx5IkvUdPjjtaMx4ktVaV1pj1g0ulB59It2E5 4wIDAQAB -----END PUBLIC KEY-----");
define("DD_ANON_PUBLIC_KEY", "-----BEGIN PUBLIC KEY----- MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAix8NoW5Csdq2DCb8+LxC pqwXIVb123jPuhYvqm7tfFGtwRvxWUa8jWhscAipZQ+zdHXpYgchR3lgp3GGp1f3 DWF/+nr2oEosSmAupeF2WmzbpAlfGSFzCh+lmzlimYKntartYcWg1uuSeKqVj54u 5MHY66iG3LkNT0WQmqXfRMWV+6SSH9PLjWIsaAs/x0VLuHUe/lSxLhxMIPIPqtFc y324GTJWYVYiRK/eDiiBSbKBB11VmgVeIf1x3cDosTeMntXy1PBPzxiBzkMo2COe QJKZQT2912sOeURYTTGTvwxGb/nNDeqLXLI9Wpwm3UZO6/yYK5/z8dgwYgK6cvu1 LSkY7RzggKnGAHAxawjTRjgpWLIcnHYe/mE/BaDVLE/113piXbuUbqC3BBJ5JjzI XVMDQdN08ptZpSAXgXLTY9+L0aGzupb1AHwfr201FdtbBUEtfBl0AdrEu9r+ls5v QqIvkNbu5wwLllY5/5u6D2I2adXauBkqCq/Z2ksyw+LOc4py3G5zxfhcBfMqILl0 Nk5u4wNhTKxjOmdrOEW4oWrqj5NW6G1va/6PCNR2cIL8v0bpr0JABzYzXEzXSJO4 J9QJOxnyVUgaqC6dw3myRKX0MFe1kaHfWN4FPdNGaG52nkXMp5IzRg2NbP5P1GEw 3febVTI/8Gx40Mw04e5wJIkCAwEAAQ== -----END PUBLIC KEY-----");

?>