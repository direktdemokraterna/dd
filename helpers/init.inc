<?php 
session_start();

date_default_timezone_set('Europe/Stockholm');

// Declares unset variables
if(empty($_GET['action'])) $_GET['action']=null; 
if(empty($_GET['type'])) $_GET['type']=null; 
if(empty($_GET['sort'])) $_GET['sort']=null; 
if(empty($_GET['filter'])) $_GET['filter']=null; 

// Includes files
include(dirname(__FILE__)."/config.inc");
include(dirname(__FILE__)."/general_helpers.inc");
include(dirname(__FILE__)."/navigation_helpers.inc");
include(dirname(__FILE__)."/forum_helpers.inc");
include(dirname(__FILE__)."/vote_helpers.inc");
include(dirname(__FILE__)."/crypt_helpers.inc");

include(dirname(__FILE__)."/view/general_helper.inc");
include(dirname(__FILE__)."/view/vote_helper.inc");
include(dirname(__FILE__)."/view/forum_post_helper.inc");

include(dirname(__FILE__)."/db/db.inc");
include(dirname(__FILE__)."/db/db_general.inc");
include(dirname(__FILE__)."/db/db_user.inc");
include(dirname(__FILE__)."/db/db_admin.inc");
include(dirname(__FILE__)."/db/db_forum_admin.inc");
include(dirname(__FILE__)."/db/db_vote_admin.inc");
include(dirname(__FILE__)."/db/db_member_admin.inc");
include(dirname(__FILE__)."/db/db_forum.inc");
include(dirname(__FILE__)."/db/db_message.inc");
include(dirname(__FILE__)."/db/db_workgroup.inc");
include(dirname(__FILE__)."/db/db_helpers.inc");
include(dirname(__FILE__)."/db/db_calendar.inc");
include(dirname(__FILE__)."/db/db_vote.inc");
include(dirname(__FILE__)."/db/db_prop.inc");
include(dirname(__FILE__)."/db/db_delegate.inc");
include(dirname(__FILE__)."/db/db_constituency.inc");

// Defines constants
define("USERIMG_PATH", "images/userimg/");
define("WORKGROUP_PUBLIC_FORUMS_CATEGORY", 9);
define("WORKGROUP_PRIVATE_FORUMS_CATEGORY", 8);
define("POSTS_PER_PAGE", 10);
define("LIST_ITEMS_PER_PAGE", 50);
define("LIST_ITEMS_PER_PAGE_SHORT", 20);
define("DEFAULT_CONSTITUENCY_ID", 313);

define("PROP_TO_VOTE_SUPPORT", 0.05);
define("PROP_REMOVAL_TIME", 14*24*60*60);
define("STANDARD_VOTE_LENGTH", 14*24*60*60);
define("BUFFER_TIME_FOR_CONTINUOUS_ELECTIONS", 1*24*60*60);

define("RSA_PRIVATE_KEY", "-----BEGIN RSA PRIVATE KEY----- MIIEogIBAAKCAQEAsIpWVPRtuUJci9JuZEQYExLoWrWqCO7KImTVRRryZKCQ8ywg i9bfS7inDpOvrmiMORomHjj7SDRySIzB8hpyC+DLVQEKz3vVs5bafzGxQcBdvdI3 bXmCEd3mkmwaWhPcwTbARS71VbOTMezz7EQMjsSO4L6B74vblIJV+t+Q5D4v+FU1 EgVCR22o3niM8MaqGAQTDpwC08cYQ2K4Iog5Wh8Qv53JeJv0h6qQC7iB1Pf5oLrX tXxF/ozzBapFzRPFCj/Yvfx/7NPj1qFD/z4LkJAgWWnrpUEgwj55Lm6YHZPJThul x5IkvUdPjjtaMx4ktVaV1pj1g0ulB59It2E54wIDAQABAoIBAAOlPHNXpfzJdB8t Be6+TmyPNOR+oNeILfz4B3fJJSoGLy536E1XvArhWFqSmr7N70TuMQBQKk9k43Rz d6PLGQGWyQwYNlCitkuvLBOsg1EGXfxhkjE805gQp9/sXItX1dsL7693pBHhE4NY T12L6ch4iMzD3x7Pszj48gaSrEUr3KdiSY3qqx8cRRcQJDfTrRjOnx5JYWMPUAIU P+uoVrZIbKNWPPcdm5ErkcSJWPw48B8s47zrlEglNCdrRYp3n70cx+SuOd2rx2ND NV6EUVXTBz2gu6HOvYFChv4L9XmspCsaDnqNPgxbh0fJkXP3i/DHHJASxwKG1eY+ ybkuEDUCgYEAshohDFDmLe98MvuCCbjpB0A8m6To5mUqXBG0xnLqj+dVmZTiZTbr l/WwCRwEoDTLVOzTTovCtsFKM3Bcmj0mIdsc5bEMiV9w7kb+OTj28gHUVPxiOyqd KhIPJ5P3LKpT4Jk2gNgILuDKIMFq7hYt6ZWWlDwq6NGephtYuCJoRc0CgYEA/cFZ E9AUiR7V0rRnJXQ66POQeIItmhHACjB1NoDv5g2wanF8K+mUdnPWXry4HVUgmp4c N2JW3t/CE7OaZ2q08WEEJuPAgtuxfYbSiTWHigwe2VUNWmGjR78Q8pIYePgnyDft MATy2obRzx3EvjlQRQz5ixLr+zuu/vu7pXQAzm8CgYBX5b1ZrrNrCD5riuTql2+q PHGs/v5SdqspNTPanOxWiP0eBvSUrz4miQKP/FvsFSIkj5zZrvAx8cMFD/cjx/oB y3m/glmFkqzRbAgbhZmaZny8VLLGMInQMYl5JvVd/dHXjsXvYK7pM9eNwudbCWcv WLwv/GHQ9WMu52ApwBFmIQKBgCQ8y0rACV63j5OCfcRkf9EqjzQWawq4hDMwTlzV Nu0kgVACGthuh+wOiMuIqcZOlNRfxenG2l8Dl0SW/nLMU0CxORWQqrpFQ2iIq2I6 ybtWFcW1lq2UievCBlqNsH79+ThnfDDCVCgO3sF0H9eGeccSnkRVFGwRTuFM87Qi B8dzAoGAZgaDoRoVmGwy4xsTOlwISdUfmYvGjLEFujUHTC2ky4x7CjVoAGtSycJx U6wdMOfAZG/NeuRaop3Jz35H7+zFr2195pnKgJirdvAcwPO2hoKv8xF9yGU6Pp1Q 7dBfULUhppU0IT7hX9fONkaKk9TzpU4R/paFDTxPTuiA1v5rLlg= -----END RSA PRIVATE KEY-----");
define("DD_PUBLIC_KEY", "-----BEGIN PUBLIC KEY----- MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAsIpWVPRtuUJci9JuZEQY ExLoWrWqCO7KImTVRRryZKCQ8ywgi9bfS7inDpOvrmiMORomHjj7SDRySIzB8hpy C+DLVQEKz3vVs5bafzGxQcBdvdI3bXmCEd3mkmwaWhPcwTbARS71VbOTMezz7EQM jsSO4L6B74vblIJV+t+Q5D4v+FU1EgVCR22o3niM8MaqGAQTDpwC08cYQ2K4Iog5 Wh8Qv53JeJv0h6qQC7iB1Pf5oLrXtXxF/ozzBapFzRPFCj/Yvfx/7NPj1qFD/z4L kJAgWWnrpUEgwj55Lm6YHZPJThulx5IkvUdPjjtaMx4ktVaV1pj1g0ulB59It2E5 4wIDAQAB -----END PUBLIC KEY-----");
define("DD_ANON_PUBLIC_KEY", "-----BEGIN PUBLIC KEY----- MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAix8NoW5Csdq2DCb8+LxC pqwXIVb123jPuhYvqm7tfFGtwRvxWUa8jWhscAipZQ+zdHXpYgchR3lgp3GGp1f3 DWF/+nr2oEosSmAupeF2WmzbpAlfGSFzCh+lmzlimYKntartYcWg1uuSeKqVj54u 5MHY66iG3LkNT0WQmqXfRMWV+6SSH9PLjWIsaAs/x0VLuHUe/lSxLhxMIPIPqtFc y324GTJWYVYiRK/eDiiBSbKBB11VmgVeIf1x3cDosTeMntXy1PBPzxiBzkMo2COe QJKZQT2912sOeURYTTGTvwxGb/nNDeqLXLI9Wpwm3UZO6/yYK5/z8dgwYgK6cvu1 LSkY7RzggKnGAHAxawjTRjgpWLIcnHYe/mE/BaDVLE/113piXbuUbqC3BBJ5JjzI XVMDQdN08ptZpSAXgXLTY9+L0aGzupb1AHwfr201FdtbBUEtfBl0AdrEu9r+ls5v QqIvkNbu5wwLllY5/5u6D2I2adXauBkqCq/Z2ksyw+LOc4py3G5zxfhcBfMqILl0 Nk5u4wNhTKxjOmdrOEW4oWrqj5NW6G1va/6PCNR2cIL8v0bpr0JABzYzXEzXSJO4 J9QJOxnyVUgaqC6dw3myRKX0MFe1kaHfWN4FPdNGaG52nkXMp5IzRg2NbP5P1GEw 3febVTI/8Gx40Mw04e5wJIkCAwEAAQ== -----END PUBLIC KEY-----");

?>