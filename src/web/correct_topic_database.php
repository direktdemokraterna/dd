<?php
		ini_set('display_errors', '1');

$dd = new PDO("mysql:host=localhost;dbname=dd", "root", "anders");
$dd->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
$dd->setAttribute(PDO::ATTR_EMULATE_PREPARES, false);



$query = "select p.id as topic_id, 
			(select count(*) from post p2 where p2.topic_id = p.id) as number_of_posts, 
			(select count(distinct user_id) from post p3 where p3.topic_id = p.id) as number_of_participants, 
			(select p4.posted_time from post p4 where p4.topic_id = p.id order by p4.posted_time desc limit 1) as last_posted_time, 
			(select u2.id from post p5, user u2 where p5.user_id = u2.id and p5.topic_id = p.id order by p5.posted_time desc limit 1) as last_user_id
			from post p 
			where p.is_topic = 1";
$stmt = $dd->prepare($query);
$stmt->execute();
$topics = $stmt->fetchAll();

foreach ($topics as $topic) {
	$stmt = $dd->prepare("INSERT INTO topic_meta_info (topic_id, number_of_posts, number_of_participants, last_posted_time, last_user_id) VALUES (?, ?, ?, ?, ?)");
	$stmt->execute(Array($topic['topic_id'], $topic['number_of_posts'], $topic['number_of_participants'], $topic['last_posted_time'], $topic['last_user_id']));
	echo $topic['topic_id'] . "<br>";
}

