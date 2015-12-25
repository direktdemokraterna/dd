<?php 
// Defines database constants
define("DB_HOST", "localhost");
define("DB_NAME", "dd");
define("DB_USERNAME", "");
define("DB_PASSWORD", "");

// Defines address for anonymisation server
define("ANON_SERVER_URL", "http://localhost/dd_anon/");
define("ANON_SERVER_BROWSER_URL", "http://localhost/dd_anon/");

// Language
define("BASE_LANG", "en");
define("LANG", "sv");

// Defines constants
define("USERIMG_PATH", "images/userimg/");
define("WORKGROUP_PUBLIC_FORUMS_CATEGORY", 9);
define("WORKGROUP_PRIVATE_FORUMS_CATEGORY", 8);
define("POSTS_PER_PAGE", 10);
define("LIST_ITEMS_PER_PAGE", 50);
define("LIST_ITEMS_PER_PAGE_SHORT", 20);
define("MAX_ACTIVE_PROPOSITION_COUNT", 5);
define("DEFAULT_CONSTITUENCY_ID", 313);

define("PROP_TO_VOTE_SUPPORT", 0.2);
define("PROP_REMOVAL_TIME", 14*24*60*60);
define("STANDARD_VOTE_LENGTH", 14*24*60*60);
define("BUFFER_TIME_FOR_CONTINUOUS_ELECTIONS", 1*24*60*60);

define("BASE_DIR", __DIR__);
?>