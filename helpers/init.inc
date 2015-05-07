<?php 
session_start();

// Declares unset variables
if(empty($_GET['action'])) $_GET['action']=null; 
if(empty($_GET['type'])) $_GET['type']=null; 
if(empty($_GET['sort'])) $_GET['sort']=null; 
if(empty($_GET['filter'])) $_GET['filter']=null; 

// Includes files
include(dirname(__FILE__)."/general_helpers.inc");
include(dirname(__FILE__)."/forum_helpers.inc");
include(dirname(__FILE__)."/vote_helpers.inc");
include(dirname(__FILE__)."/crypt_helpers.inc");

include(dirname(__FILE__)."/db/db.inc");
include(dirname(__FILE__)."/db/db_user.inc");
include(dirname(__FILE__)."/db/db_admin.inc");
include(dirname(__FILE__)."/db/db_forum_admin.inc");
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
define("WORKGRUOP_PUBLIC_FORUMS_CATEGORY", 9);
define("WORKGRUOP_PRIVATE_FORUMS_CATEGORY", 8);
define("POSTS_PER_PAGE", 50);
define("LIST_ITEMS_PER_PAGE", 50);
define("LIST_ITEMS_PER_PAGE_SHORT", 20);

define("PROP_TO_VOTE_SUPPORT", 0.05);
define("STANDARD_VOTE_LENGTH", 14*24*60*60);
define("ANON_SERVER_URL", "http://localhost/dd_anon/");
define("RSA_PRIVATE_KEY", file_get_contents(dirname(__FILE__)."/keys/dd_priv_key.txt"));

?>