<?

mysql_connect("localhost") or die("could not connect to localhost");
mysql_select_db("dd") or die("Could not select database");

$kommuner = mysql_query("SELECT kommun FROM kommuner ORDER BY kommun ASC");
while($row = mysql_fetch_array($kommuner)){
	echo $row['kommun'];
  mysql_query("INSERT INTO forums VALUES (null, 2, '$row[kommun]', '', null, null, 0, 0, 'local_county')") or die(mysql_error());
  $insert_id = mysql_insert_id();
  mysql_query("INSERT INTO constituencies VALUES (null, '$row[kommun]', '', 0, $insert_id, 'local_county')") or die(mysql_error());
}
$lan = mysql_query("SELECT DISTINCT lan FROM kommuner ORDER BY lan ASC");
while($row = mysql_fetch_array($lan)){
	echo $row['lan'];
  mysql_query("INSERT INTO forums VALUES (null, 2, '$row[lan]', '', null, null, 0, 0, 'local_region')");
  $insert_id = mysql_insert_id();
  mysql_query("INSERT INTO constituencies VALUES (null, '$row[lan]', '', 0, $insert_id, 'local_region')");
}