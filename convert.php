<?php
		ini_set('display_errors', '1');

function GenerateRandomString ($length){
	$ALPHANUMERIC_CHARS = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
	$random_string = "";
	for($i=0; $i<$length; $i++)
		$random_string .= $ALPHANUMERIC_CHARS[mt_rand(0,61)];
	return $random_string;
}


$wp = new PDO("mysql:host=localhost;dbname=dd_wp", "root", "");
$wp->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$wp->setAttribute(PDO::ATTR_EMULATE_PREPARES, false);

$dd = new PDO("mysql:host=localhost;dbname=dd_anders", "root", "");
$dd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$dd->setAttribute(PDO::ATTR_EMULATE_PREPARES, false);



$stmt = $wp->prepare("SELECT id, user_login, user_pass, user_email, UNIX_TIMESTAMP(user_registered) AS registration_time, display_name, (SELECT meta_value FROM wp_usermeta um WHERE um.user_id=u.id AND um.meta_key='first_name') AS first_name, (SELECT meta_value FROM wp_usermeta um WHERE um.user_id=u.id AND um.meta_key='last_name') AS last_name, (SELECT meta_value FROM wp_usermeta um WHERE um.user_id=u.id AND um.meta_key='description') AS description, (SELECT meta_value FROM wp_usermeta um WHERE um.user_id=u.id AND um.meta_key='nickname') AS nickname FROM wp_users u");
$stmt->execute();
$wp_users = $stmt->fetchAll();


foreach ($wp_users as $wp_user) {
	if(isset($wp_user['first_name']) && isset($wp_user['last_name'])){
		$first_name = ucfirst($wp_user['first_name']);
		$last_name = ucfirst($wp_user['last_name']);
	}
	else{
		$first_name = $wp_user['display_name'];
		$last_name = "";
	}

	$activation_code = GenerateRandomString(12);

	$stmt = $dd->prepare("DELETE FROM user WHERE id = ?");
	$stmt->execute(Array($wp_user['id']));

	$stmt = $dd->prepare("INSERT INTO user (id, username, password, registration_time, first_name, last_name, email, description, activation_code, activation_first_name, activation_last_name) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
	$stmt->execute(Array($wp_user['id'], $wp_user['user_login'], $wp_user['user_pass'], $wp_user['registration_time'], "Inte", "aktiverad", $wp_user['user_email'], $wp_user['description'], $activation_code, $wp_user['first_name'], $wp_user['last_name']));
}




$lines = file("data.txt");
$head = str_getcsv(array_shift($lines));

$array = array();
foreach ($lines as $line) {
    $array[] = array_combine($head, str_getcsv($line));
}

foreach ($array as $row) {
	$stmt = $dd->prepare("SELECT id FROM user WHERE email = ? AND county_id = 0");
	$stmt->execute(Array($row['from_email']));
	$result = $stmt->fetchAll(PDO::FETCH_ASSOC);

	if(!empty($result)){
		$anvandar_id = $result[0];

		$stmt = $dd->prepare("SELECT id, parent_id FROM constituency WHERE title = ? OR title = ? AND constituency_level = 3");
		$stmt->execute(Array($row['kommun'], substr($row['kommun'], 0, -1)));
		$result = $stmt->fetchAll(PDO::FETCH_ASSOC);
		$kommuner = $result[0];

		$stmt = $dd->prepare("UPDATE user SET street_address = ?, zip_code = ?, city_address = ?, county_id = ?, region_id = ?, social_security_number = ?, telephone1 = ? WHERE id = ?");
		$stmt->execute(Array($row['adress'], $row['postnummer'], $row['postadress'], $kommuner['id'], $kommuner['parent_id'], $row['personnummer'], $row['telefon'], $anvandar_id['id']));
	}
}




$stmt = $wp->prepare("SELECT id, post_title, post_content FROM wp_2_posts WHERE post_type='forum'");
$stmt->execute();
$wp_forums = $stmt->fetchAll();

$stmt = $dd->prepare("INSERT INTO category (title) VALUES (?)");
$stmt->execute(Array("Forum från Wordpress-forumet"));
$category_id = $dd->lastInsertId();

foreach ($wp_forums as $wp_forum) {
	$stmt = $dd->prepare("DELETE FROM forum WHERE id = ?");
	$stmt->execute(Array($wp_forum['id']));

	$stmt = $dd->prepare("INSERT INTO forum (id, category_id, title, description, access_type) VALUES (?, ?, ?, ?, ?)");
	$stmt->execute(Array($wp_forum['id'], $category_id, $wp_forum['post_title'], $wp_forum['post_content'], "public"));
}



$stmt = $wp->prepare("SELECT id, post_author, post_title, post_content, UNIX_TIMESTAMP(post_date) AS post_date, UNIX_TIMESTAMP(post_modified) AS post_modified, post_parent FROM wp_2_posts WHERE post_type='topic'");
$stmt->execute();
$wp_topics = $stmt->fetchAll();

foreach ($wp_topics as $wp_topic) {
	$stmt = $dd->prepare("DELETE FROM post WHERE id = ?");
	$stmt->execute(Array($wp_topic['id']));

	$stmt = $dd->prepare("INSERT INTO post (id, topic_id, user_id, forum_id, is_topic, posted_time, last_edited_time, title, content) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
	$stmt->execute(Array($wp_topic['id'], $wp_topic['id'], $wp_topic['post_author'], $wp_topic['post_parent'], 1, $wp_topic['post_date'], $wp_topic['post_modified'], $wp_topic['post_title'], $wp_topic['post_content'], ));
}


$stmt = $wp->prepare("SELECT id, post_author, post_title, post_content, UNIX_TIMESTAMP(post_date) AS post_date, UNIX_TIMESTAMP(post_modified) AS post_modified, post_parent, (SELECT meta_value FROM wp_2_postmeta pm WHERE pm.post_id=p.id AND pm.meta_key='_bbp_forum_id') AS forum_id FROM wp_2_posts p WHERE p.post_type='reply'");
$stmt->execute();
$wp_posts = $stmt->fetchAll();

foreach ($wp_posts as $wp_post) {
	$stmt = $dd->prepare("DELETE FROM post WHERE id = ?");
	$stmt->execute(Array($wp_post['id']));

	$stmt = $dd->prepare("INSERT INTO post (id, topic_id, user_id, forum_id, is_topic, posted_time, last_edited_time, title, content) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)");
	$stmt->execute(Array($wp_post['id'], $wp_post['post_parent'], $wp_post['post_author'], $wp_post['forum_id'], 0, $wp_post['post_date'], $wp_post['post_modified'], $wp_post['post_title'], $wp_post['post_content'], ));
}




$stmt = $dd->prepare("SELECT id FROM forum");
$stmt->execute();
$forums = $stmt->fetchAll();

foreach ($forums as $forum) {
	$stmt = $dd->prepare("update forum set last_posted_time = (select posted_time from post where forum_id = ? order by posted_time desc limit 1), last_posted_post = (select id from post where forum_id = ? order by posted_time desc limit 1), number_of_topics = (select count(*) from post where is_topic = 1 and forum_id = ?), number_of_posts = (select count(*) from post where forum_id = ?) where id = ?");
	$stmt->execute(Array($forum['id'], $forum['id'], $forum['id'], $forum['id'], $forum['id']));
}



$stmt = $dd->prepare("SELECT id FROM user");
$stmt->execute();
$users = $stmt->fetchAll();

foreach ($users as $user) {
	$stmt = $dd->prepare("update user set number_of_posts = (select count(*) from post where user_id = ?), number_of_topics = (select count(*) from post where is_topic = 1 and user_id = ?)  where id = ?");
	$stmt->execute(Array($user['id'], $user['id'], $user['id']));

	$stmt = $dd->prepare("DELETE FROM voter WHERE id = ?");
	$stmt->execute(Array($user['id']));

	$stmt = $dd->prepare("INSERT INTO voter (id, voter_type) VALUES (?, ?)");
	$stmt->execute(Array($user['id'], "user"));
}


// FYLLER I TITEL PÅ FORUM-SVAR SOM INTE REDAN HAR DET
$stmt = $dd->prepare("update post p1, post p2 set p1.title=p2.title where p1.topic_id=p2.id and p1.is_topic=0 and p1.title=''");
$stmt->execute();

// SÄTTER REGIONER TILL UTOMLANDS FÖR ANVÄNDARE SOM INTE HAR FÅTT NÅGON REGION
$stmt = $dd->prepare("update user set county_id=314, region_id=315 where county_id=0 and region_id=0");
$stmt->execute();
