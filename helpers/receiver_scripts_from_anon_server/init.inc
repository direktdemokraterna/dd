<?php 

// Defines constants
define("DB_HOST", "localhost");
define("DB_NAME", "dd");
define("DB_USERNAME", "");
define("DB_PASSWORD", "");

define("USERIMG_PATH", "images/userimg/");
define("WORKGRUOP_PUBLIC_FORUMS_CATEGORY", 9);
define("WORKGRUOP_PRIVATE_FORUMS_CATEGORY", 8);
//define("POSTS_PER_PAGE", 10);
define("LIST_ITEMS_PER_PAGE", 50);

define("PROP_TO_VOTE_SUPPORT", 0.2);
define("STANDARD_VOTE_LENGTH", 14*24*60*60);
define("ANON_SERVER_URL", "http://localhost/dd_anon/");
define("RSA_PRIVATE_KEY", file_get_contents("../keys/dd_priv_key.txt"));

// Includes files
include("../helpers.inc");
include("../db/db.inc");
include("../db/db_user.inc");
include("../db/db_admin.inc");
include("../db/db_forum_admin.inc");
include("../db/db_forum.inc");
include("../db/db_message.inc");
include("../db/db_workgroup.inc");
include("../db/db_error.inc");
include("../db/db_calendar.inc");
include("../db/db_vote.inc");
include("../db/db_prop.inc");
include("../db/db_delegate.inc");
include("../db/db_constituency.inc");

?>