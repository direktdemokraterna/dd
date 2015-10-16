-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	4.1.22-community-nt

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

--
-- Create schema dd_anon
--

CREATE DATABASE IF NOT EXISTS dd_anon;
USE dd_anon;

--
-- Definition of table `temp_codes_constituencies`
--

DROP TABLE IF EXISTS `temp_codes_constituencies`;
CREATE TABLE `temp_codes_constituencies` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `temp_code` varchar(45) NOT NULL default '',
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `timestamp_created` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `temp_codes_constituencies`
--

/*!40000 ALTER TABLE `temp_codes_constituencies` DISABLE KEYS */;
/*!40000 ALTER TABLE `temp_codes_constituencies` ENABLE KEYS */;

--
-- Definition of table `user_temp_codes`
--

DROP TABLE IF EXISTS `user_temp_codes`;
CREATE TABLE `user_temp_codes` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `temp_code` varchar(45) NOT NULL default '',
  `user_id` int(10) unsigned default NULL,
  `timestamp_created` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `user_temp_codes`
--

/*!40000 ALTER TABLE `user_temp_codes` DISABLE KEYS */;
INSERT INTO `user_temp_codes` (`id`,`temp_code`,`user_id`,`timestamp_created`) VALUES 
 (1,'j7O5zpQpJ1Dpc28VyYxb',5,1428224049),
 (2,'s6eY7CZM1Ghp8kTkms3',5,1428224399),
 (3,'7oTsdUgON7w9YRG2ljEp',5,1428224421),
 (4,'DLwuMGBGw9GTlIxRksuI',5,1428224573),
 (5,'2plbn3WeF66nm0nxEwH',5,1428224621),
 (6,'WJc0JMmnC8sHEcGmu2oR',5,1428224819),
 (7,'cA90oizGqSAmYvRsKM35',5,1428225044),
 (8,'Fit4ZtzB8Ldro1Jnub',5,1428228361),
 (9,'p3Ly25MPTFe7MiJgXHJ',5,1428228387),
 (10,'O2SnE2xo9CTpbGLNRiv1',5,1428229939),
 (11,'YJDQpf8BSzTtPVbBnG2R',5,1428230032),
 (12,'vsQLeg1EsPWtbShsFgBL',5,1428230131),
 (13,'uCMCLJh3A85f8K0hwvRC',5,1428230311),
 (14,'eHuSaRnV8AvC1iOsjUpk',5,1428231196),
 (15,'DqHpdgKvQ9La6UxqP0oJ',5,1428231331),
 (16,'o8WGpOqAw9l9bZrGQWQ',5,1428231686),
 (17,'QtFauzkoaI2w2MmoPbhI',5,1428231824),
 (18,'RJeZlSfwzm46pUYylak',5,1428232713),
 (19,'XJraWK20nfQhO2XVNWdP',4,1428469709),
 (20,'3PhSBo0LaKp2ZINxo1uu',5,1428695056),
 (21,'CbsoVTMt73DQji09BLl0',6,1429087518),
 (22,'vP0hl3kM3nDD8hqJJq0y',5,1429092557),
 (23,'IShC4Kgif0olNQy5UVLe',1,1429092564),
 (24,'L9U240yGy0tzJuNn28ly',6,1429123006),
 (25,'eaQBqwZ59UOuEBIrewE0',1,1429166182),
 (26,'eu4P0EEr0dJixZmqDQxT',6,1429166227),
 (27,'C2060ASDolZQrqwH5Ei1',6,1429521738),
 (28,'yN7QBxING30BgByj0sFf',6,1429601269),
 (29,'9hUbPxlPzMg6QdRxEJ1H',6,1429604714),
 (30,'vmmU4cjllex5dqqOsY9j',6,1431326289),
 (31,'jI01TPxbXDVfjWtuCGYy',1,1431328858),
 (32,'2g5JLOkTCN34jSVTFUcO',1,1431425285),
 (33,'BowmOCjV12sfdyMCUL4r',6,1432010082),
 (34,'yKJIH8UyHQqXTPjDqr88',1,1432012108),
 (35,'ChYErZkWoLc4RZ0h4DBH',6,1432105445),
 (36,'HAw439LECP1zJYysM0xQ',1,1432108440),
 (37,'VeKxedxNyS1JxQ2c5Pma',6,1432108798),
 (38,'pgI0dc2yqc8JpjLsCt9h',1,1432110519),
 (39,'ogHKs9ddjioTOP9buswy',8,1432275195),
 (40,'HsGHVzfYjsatTTLs9wH1',11,1432277331),
 (41,'Ostp6LsXeuy4ZAjYXhXU',11,1432277702),
 (42,'M6QtXCkGnvEpXxaIHX9c',1,1432277749),
 (43,'v9lFidqj9Cfl8HVgVh2f',4,1432278021),
 (44,'KC4XFi124KNHxGBT3nLE',6,1432278189),
 (45,'EjZBjUobImMZUlfnCFr0',5,1432278207),
 (46,'U5EyS5uCJ2gflf3FiRMZ',4,1432278223),
 (47,'lInIMMoMSoQesaqobdxk',13,1432280541),
 (48,'1jc1QYgKjA5xrFd4vI2w',4,1432280572),
 (49,'5Y9oW7I6e3His02q1GrL',5,1432280590),
 (50,'AztDYFxAP11JJAOz5AiJ',4,1432285333),
 (51,'9IXGx18M6xc0gvv9kQMO',6,1432311727),
 (52,'1gQrG1vahFgpPdHzwXM2',5,1433239547),
 (53,'2U8GMPxNfi36hitomQ7J',6,1433330071),
 (54,'Rk7LisGCRlWlnpq8bWoY',13,1433490316),
 (55,'OM8aRSXEgliEOWsCznaC',5,1433764911),
 (56,'QMbwFglGrlsNvoXmNZAI',13,1433764952),
 (57,'jo3gwhnzYRXycDIJp6Yp',6,1433765673),
 (58,'7RufJUSfpkE1jQ8rF1Hu',5,1433765976),
 (59,'X0TodqxamuSuKRZ9m2EK',6,1433831435),
 (60,'xw6EnH4ynyrqcSfrNNRF',5,1433832939),
 (61,'Ix4CiWGwDngSl0IqvdXr',4,1433832994),
 (62,'2vBLZ4kKf0AWf4PoenC1',5,1433833055),
 (63,'zWbZpxWeBZKojag381EN',6,1433833296),
 (64,'lHIxuHyjCsG6dkQffX2O',6,1433833316),
 (65,'RfDBVGbkyQtulnDoj7eB',6,1433833439),
 (66,'0ftemHL3SfoAoS607TY9',6,1433921138),
 (67,'FPkJzbyVyCRgxOoQ8K7S',6,1434022933),
 (68,'XZ08UK25sxaVCVMw2sMi',6,1434356128),
 (69,'ljqbxLvRrGMmexb6lEtX',6,1434555986),
 (70,'RBXL2ZnG7iXYA4MizTti',5,1434988715),
 (71,'OCEiQ6jjpnEJAIjRePMD',5,1435233880),
 (72,'nmJH8fR3dw6EJ6ROnuke',5,1435236707),
 (73,'jXey8auMiiriWJe5kpat',5,1435306855),
 (74,'BwVNEbo39sQoR3P749dd',5,1436274029),
 (75,'1biXd2W0rE8x0ycHYBEg',5,1439705639),
 (76,'Vzz2xr23Bzk8broaSzU8',14,1440242816),
 (77,'utTXx42XXfY2dTzT1MoY',5,1440243656),
 (78,'wAkXsf2WWOe3Ot3KL4hE',14,1440243808),
 (79,'aL7AOZnZ4gzZhQnMOrAe',5,1440244687),
 (80,'QJgmf8FNufhj09KNstYe',5,1440271739),
 (81,'WQtAWMfuML3odctv03q1',5,1440314817),
 (82,'KNEtaMoQOBSdI2w6NP0U',16,1440401333),
 (83,'TSmxM48i76kYpaTiK4AD',5,1440401359),
 (84,'08sG2cjfaO0TOy5aMdRG',6,1440831621),
 (85,'vjkLzEXsGtcnWOrptzjF',4,1440834631),
 (86,'STHCEpCP1SnVmAtO3kFc',4,1440834660),
 (87,'5EdJwG2teV3VU9fqt13V',5,1441045436),
 (88,'DNFH2PmH5V1Mjr77GJUs',4,1441045449),
 (89,'azof6c4JsvjiKgpmHMVo',5,1441193417),
 (90,'C48KLllW06yJTng5YREj',4,1441270293),
 (91,'JTi51VF5E75YQxVPgRXn',5,1441305620),
 (92,'5EXrG8eqthTXK50UNBip',4,1441401216),
 (93,'6EXRgA6TqKqjXLNr5AuT',5,1442754858),
 (94,'cgooYscZuQNfSIo9YaUK',5,1444411776),
 (95,'AJa5JY5NSrBMWkA1vQ5V',5,1444481227),
 (96,'nntNF69OeYdgkbG62tw0',6,1444481394),
 (97,'ab56LBCjpsytcMyn6hwz',6,1444547284),
 (98,'O1JOBVwLYYIcxae5tHsd',6,1444585621);
/*!40000 ALTER TABLE `user_temp_codes` ENABLE KEYS */;

--
-- Definition of table `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `user_id` int(10) unsigned NOT NULL default '0',
  `active_user_code` varchar(20) NOT NULL default '',
  `passive_user_code1` varchar(20) NOT NULL default '',
  `passive_user_code2` varchar(20) NOT NULL default '',
  `passive_user_code3` varchar(20) NOT NULL default '',
  `timestamp_last_login` int(10) unsigned default NULL,
  `timestamp_last_activity` int(10) unsigned default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `users`
--

/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` (`id`,`user_id`,`active_user_code`,`passive_user_code1`,`passive_user_code2`,`passive_user_code3`,`timestamp_last_login`,`timestamp_last_activity`) VALUES 
 (1,5,'osb8A8xrrQrGQfologrm','Csc0Wdfy6CHQB9eEx2UW','nTY2K5KFS3qsVuewTQNj','evYYqLsXAtpiEyQAu9vU',NULL,NULL),
 (2,6,'9ZvUSJF2Y9binMKfwOr7','QzcZsdP5ilu1roSlrhSW','qW4dkmHmZGXd2qpTAAeC','4uNKQd3WK8RzdQAqtFRp',NULL,NULL),
 (3,4,'OBc7rZoonK45KsRWs4gq','S28ZUXNjGMofzPxd16iJ','Dys7rHw0qdeH3vOrmDk0','afflJNzLhhT5QyX1cDuF',NULL,NULL),
 (4,13,'nNSpJccU3OdwJxq3SMBw','sKbDUhNO4GHSweyENtF4','nrjiKEbZCJm7XrUhg8Yg','ko7qVZd1ePk3vF5JU8o5',NULL,NULL);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;

--
-- Create schema dd
--

CREATE DATABASE IF NOT EXISTS dd;
USE dd;

--
-- Definition of table `admin_role`
--

DROP TABLE IF EXISTS `admin_role`;
CREATE TABLE `admin_role` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `title` varchar(90) NOT NULL default '',
  `description` text,
  `type` varchar(45) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `admin_role`
--

/*!40000 ALTER TABLE `admin_role` DISABLE KEYS */;
INSERT INTO `admin_role` (`id`,`title`,`description`,`type`) VALUES 
 (1,'Superadmin','','superadmin'),
 (2,'Medlemsadministratör','','member_admin'),
 (3,'Forumadministratör','','forum_admin'),
 (4,'Valadministratör','','vote_admin'),
 (5,'Kassör','','treasurer');
/*!40000 ALTER TABLE `admin_role` ENABLE KEYS */;

--
-- Definition of table `admin_role_user`
--

DROP TABLE IF EXISTS `admin_role_user`;
CREATE TABLE `admin_role_user` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `admin_role_id` int(10) unsigned NOT NULL default '0',
  `user_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=96 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `admin_role_user`
--

/*!40000 ALTER TABLE `admin_role_user` DISABLE KEYS */;
INSERT INTO `admin_role_user` (`id`,`admin_role_id`,`user_id`) VALUES 
 (89,1,5),
 (88,5,13),
 (87,4,6),
 (80,2,4),
 (86,3,6),
 (85,2,6),
 (84,1,4),
 (90,5,5),
 (91,2,5),
 (92,3,13),
 (93,3,4),
 (94,4,4);
/*!40000 ALTER TABLE `admin_role_user` ENABLE KEYS */;

--
-- Definition of table `ballot`
--

DROP TABLE IF EXISTS `ballot`;
CREATE TABLE `ballot` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `vote_id` int(10) unsigned NOT NULL default '0',
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `ballot` text,
  `user_code` varchar(20) default NULL,
  `voter_is_delegate_id` int(10) unsigned default NULL,
  `delegate_id` int(10) unsigned default NULL,
  `delegation_level` int(10) unsigned default NULL,
  `delegate_priority` int(10) unsigned default NULL,
  `time_ballot_placed` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=221 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ballot`
--

/*!40000 ALTER TABLE `ballot` DISABLE KEYS */;
INSERT INTO `ballot` (`id`,`vote_id`,`constituency_id`,`ballot`,`user_code`,`voter_is_delegate_id`,`delegate_id`,`delegation_level`,`delegate_priority`,`time_ballot_placed`) VALUES 
 (185,13,313,'no',NULL,7,NULL,NULL,NULL,1443531961),
 (100,8,313,'[]','OBc7rZoonK45KsRWs4gq',NULL,NULL,NULL,NULL,1441401249),
 (18,1,165,'no','nNSpJccU3OdwJxq3SMBw',NULL,NULL,NULL,NULL,1430117214),
 (15,2,165,'22','nNSpJccU3OdwJxq3SMBw',NULL,NULL,NULL,NULL,1429606227),
 (32,3,165,'{\"2\":-1}','nNSpJccU3OdwJxq3SMBw',NULL,NULL,NULL,NULL,1430802217),
 (38,4,165,'{\"6\":1}','nNSpJccU3OdwJxq3SMBw',NULL,NULL,NULL,NULL,1431326408),
 (76,1,165,'yes','9ZvUSJF2Y9binMKfwOr7',NULL,NULL,NULL,NULL,1434556181),
 (65,5,291,'no',NULL,6,NULL,NULL,NULL,1433832853),
 (186,13,313,'no','nNSpJccU3OdwJxq3SMBw',NULL,7,0,1,1443531961),
 (71,5,0,'no','9ZvUSJF2Y9binMKfwOr7',NULL,6,1,1,1433854681),
 (77,1,165,'yes',NULL,6,NULL,NULL,NULL,1434557442),
 (209,9,313,'{\"12\":2}',NULL,7,NULL,NULL,NULL,1443792695),
 (210,9,313,'{\"12\":2}','nNSpJccU3OdwJxq3SMBw',NULL,7,0,1,1443792696);
/*!40000 ALTER TABLE `ballot` ENABLE KEYS */;

--
-- Definition of table `calendar`
--

DROP TABLE IF EXISTS `calendar`;
CREATE TABLE `calendar` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `timestamp` int(10) unsigned NOT NULL default '0',
  `year` int(4) unsigned NOT NULL default '0',
  `month` int(2) unsigned NOT NULL default '0',
  `day` int(2) unsigned NOT NULL default '0',
  `time` varchar(20) NOT NULL default '',
  `timestamp_added` int(10) unsigned NOT NULL default '0',
  `added_by_user` int(10) unsigned NOT NULL default '0',
  `location` varchar(45) NOT NULL default '',
  `title` varchar(90) NOT NULL default '',
  `content` text NOT NULL,
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `search` (`title`,`content`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `calendar`
--

/*!40000 ALTER TABLE `calendar` DISABLE KEYS */;
INSERT INTO `calendar` (`id`,`timestamp`,`year`,`month`,`day`,`time`,`timestamp_added`,`added_by_user`,`location`,`title`,`content`) VALUES 
 (1,1425513599,2015,3,5,'Hela dagen',1425586448,4,'Internet','Programmering','Bara programmering, inget skoj.'),
 (2,1425599999,2015,3,6,'Hela dagen',1425586448,4,'Internet','Programmering','Bara programmering, inget skoj.'),
 (3,1425686399,2015,3,7,'Hela dagen',1425586448,4,'Internet','Programmering','Bara programmering, inget skoj.'),
 (4,1439855999,2015,8,18,'18.00',1439889397,5,'Internet','Test','test'),
 (5,1440115199,2015,8,21,'15',1439964396,5,'Internet','Ändrings-test','Bara test3');
/*!40000 ALTER TABLE `calendar` ENABLE KEYS */;

--
-- Definition of table `calendar_participant`
--

DROP TABLE IF EXISTS `calendar_participant`;
CREATE TABLE `calendar_participant` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `calendar_id` int(10) unsigned NOT NULL default '0',
  `user_id` int(10) unsigned NOT NULL default '0',
  `timestamp_registration` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Definition of table `category`
--

DROP TABLE IF EXISTS `category`;
CREATE TABLE `category` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `title` varchar(45) NOT NULL default '',
  `description` text NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=10 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `category`
--

/*!40000 ALTER TABLE `category` DISABLE KEYS */;
INSERT INTO `category` (`id`,`title`,`description`) VALUES 
 (4,'Testkategorin','Bara ett test. '),
 (5,'Andra testkategorin','Ännu ett test. '),
 (8,'Interna arbetsgruppsforum','Dessa forum har bara medlemmarna i den respektive arbetsgrupperna tillg†ng till.'),
 (9,'Arbetsgrupper','Publika forum f”r de olika arbetsgrupperna.'),
 (2,'Lokala forum','');
/*!40000 ALTER TABLE `category` ENABLE KEYS */;

--
-- Definition of table `constituency`
--

DROP TABLE IF EXISTS `constituency`;
CREATE TABLE `constituency` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `title` varchar(90) NOT NULL default '',
  `description` text NOT NULL,
  `number_of_voters` int(10) unsigned default NULL,
  `forum_id` int(10) unsigned NOT NULL default '0',
  `constituency_level` int(10) unsigned NOT NULL default '1',
  `parent_id` int(10) unsigned NULL,
  PRIMARY KEY  (`id`),
  KEY `constituency_level` (`constituency_level`)
) ENGINE=MyISAM AUTO_INCREMENT=314 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `constituency`
--

/*!40000 ALTER TABLE `constituency` DISABLE KEYS */;
INSERT INTO `constituency` (`id`,`title`,`description`,`number_of_voters`,`forum_id`,`constituency_level`,`parent_id`) 
VALUES 
(1,'Ale','',0,11,3,310),
(2,'Alingsås','',0,12,3,310),
(3,'Alvesta','',0,13,3,299),
(4,'Aneby','',0,14,3,297),
(5,'Arboga','',0,15,3,309),
(6,'Arjeplog','',0,16,3,300),
(7,'Arvidsjaur','',0,17,3,300),
(8,'Arvika','',0,18,3,306),
(9,'Askersund','',0,19,3,311),
(10,'Avesta','',0,20,3,292),
(11,'Bengtsfors','',0,21,3,310),
(12,'Berg','',0,22,3,296),
(13,'Bjurholm','',0,23,3,307),
(14,'Bjuv','',0,24,3,302),
(15,'Boden','',0,25,3,300),
(16,'Bollebygd','',0,26,3,310),
(17,'Bollnäs','',0,27,3,294),
(18,'Borgholm','',0,28,3,298),
(19,'Borlänge','',0,29,3,292),
(20,'Borås','',0,30,3,310),
(21,'Botkyrka','',0,31,3,303),
(22,'Boxholm','',0,32,3,312),
(23,'Bromölla','',0,33,3,302),
(24,'Bräcke','',0,34,3,296),
(25,'Burlöv','',0,35,3,302),
(26,'Båstad','',0,36,3,302),
(27,'Dals-Ed','',0,37,3,310),
(28,'Danderyd','',0,38,3,303),
(29,'Degerfors','',0,39,3,311),
(30,'Dorotea','',0,40,3,307),
(31,'Eda','',0,41,3,306),
(32,'Ekerö','',0,42,3,303),
(33,'Eksjö','',0,43,3,297),
(34,'Emmaboda','',0,44,3,298),
(35,'Enköping','',0,45,3,305),
(36,'Eskilstuna','',0,46,3,304),
(37,'Eslöv','',0,47,3,302),
(38,'Essunga','',0,48,3,310),
(39,'Fagersta','',0,49,3,309),
(40,'Falkenberg','',0,50,3,295),
(41,'Falköping','',0,51,3,310),
(42,'Falu','',0,52,3,292),
(43,'Filipstad','',0,53,3,306),
(44,'Finspång','',0,54,3,312),
(45,'Flen','',0,55,3,304),
(46,'Forshaga','',0,56,3,306),
(47,'Färgelanda','',0,57,3,310),
(48,'Gagnef','',0,58,3,292),
(49,'Gislaved','',0,59,3,297),
(50,'Gnesta','',0,60,3,304),
(51,'Gnosjö','',0,61,3,297),
(52,'Gotland','',0,62,3,293),
(53,'Grums','',0,63,3,306),
(54,'Grästorp','',0,64,3,310),
(55,'Gullspång','',0,65,3,310),
(56,'Gällivare','',0,66,3,300),
(57,'Gävle','',0,67,3,294),
(58,'Göteborg','',0,68,3,310),
(59,'Götene','',0,69,3,310),
(60,'Habo','',0,70,3,297),
(61,'Hagfors','',0,71,3,306),
(62,'Hallsberg','',0,72,3,311),
(63,'Hallstahammar','',0,73,3,309),
(64,'Halmstad','',0,74,3,295),
(65,'Hammarö','',0,75,3,306),
(66,'Haninge','',0,76,3,303),
(67,'Haparanda','',0,77,3,300),
(68,'Heby','',0,78,3,305),
(69,'Hedemora','',0,79,3,292),
(70,'Helsingborg','',0,80,3,302),
(71,'Herrljunga','',0,81,3,310),
(72,'Hjo','',0,82,3,310),
(73,'Hofors','',0,83,3,294),
(74,'Huddinge','',0,84,3,303),
(75,'Hudiksvall','',0,85,3,294),
(76,'Hultsfred','',0,86,3,298),
(77,'Hylte','',0,87,3,295),
(78,'Håbo','',0,88,3,305),
(79,'Hällefors','',0,89,3,311),
(80,'Härjedalen','',0,90,3,296),
(81,'Härnösand','',0,91,3,308),
(82,'Härryda','',0,92,3,310),
(83,'Hässleholm','',0,93,3,302),
(84,'Höganäs','',0,94,3,302),
(85,'Högsby','',0,95,3,298),
(86,'Hörby','',0,96,3,302),
(87,'Höör','',0,97,3,302),
(88,'Jokkmokk','',0,98,3,300),
(89,'Järfälla','',0,99,3,303),
(90,'Jönköping','',0,100,3,297),
(91,'Kalix','',0,101,3,300),
(92,'Kalmar','',0,102,3,298),
(93,'Karlsborg','',0,103,3,310),
(94,'Karlshamn','',0,104,3,291),
(95,'Karlskoga','',0,105,3,311),
(96,'Karlskrona','',0,106,3,291),
(97,'Karlstad','',0,107,3,306),
(98,'Katrineholm','',0,108,3,304),
(99,'Kil','',0,109,3,306),
(100,'Kinda','',0,110,3,312),
(101,'Kiruna','',0,111,3,300),
(102,'Klippan','',0,112,3,302),
(103,'Knivsta','',0,113,3,305),
(104,'Kramfors','',0,114,3,308),
(105,'Kristianstad','',0,115,3,302),
(106,'Kristinehamn','',0,116,3,306),
(107,'Krokom','',0,117,3,296),
(108,'Kumla','',0,118,3,311),
(109,'Kungsbacka','',0,119,3,295),
(110,'Kungsör','',0,120,3,309),
(111,'Kungälv','',0,121,3,310),
(112,'Kävlinge','',0,122,3,302),
(113,'Köping','',0,123,3,309),
(114,'Laholm','',0,124,3,295),
(115,'Landskrona','',0,125,3,302),
(116,'Laxå','',0,126,3,311),
(117,'Lekeberg','',0,127,3,311),
(118,'Leksand','',0,128,3,292),
(119,'Lerum','',0,129,3,310),
(120,'Lessebo','',0,130,3,299),
(121,'Lidingö','',0,131,3,303),
(122,'Lidköping','',0,132,3,310),
(123,'Lilla Edet','',0,133,3,310),
(124,'Lindesberg','',0,134,3,311),
(125,'Linköping','',0,135,3,312),
(126,'Ljungby','',0,136,3,299),
(127,'Ljusdal','',0,137,3,294),
(128,'Ljusnarsberg','',0,138,3,311),
(129,'Lomma','',0,139,3,302),
(130,'Ludvika','',0,140,3,292),
(131,'Luleå','',0,141,3,300),
(132,'Lund','',0,142,3,302),
(133,'Lycksele','',0,143,3,307),
(134,'Lysekil','',0,144,3,310),
(135,'Malmö','',0,145,3,302),
(136,'Malung-Sälen','',0,146,3,292),
(137,'Malå','',0,147,3,307),
(138,'Mariestad','',0,148,3,310),
(139,'Mark','',0,149,3,310),
(140,'Markaryd','',0,150,3,299),
(141,'Mellerud','',0,151,3,310),
(142,'Mjölby','',0,152,3,312),
(143,'Mora','',0,153,3,292),
(144,'Motala','',0,154,3,312),
(145,'Mullsjö','',0,155,3,297),
(146,'Munkedal','',0,156,3,310),
(147,'Munkfors','',0,157,3,306),
(148,'Mölndal','',0,158,3,310),
(149,'Mönsterås','',0,159,3,298),
(150,'Mörbylånga','',0,160,3,298),
(151,'Nacka','',0,161,3,303),
(152,'Nora','',0,162,3,311),
(153,'Norberg','',0,163,3,309),
(154,'Nordanstig','',0,164,3,294),
(155,'Nordmaling','',0,165,3,307),
(156,'Norrköping','',0,166,3,312),
(157,'Norrtälje','',0,167,3,303),
(158,'Norsjö','',0,168,3,307),
(159,'Nybro','',0,169,3,298),
(160,'Nykvarn','',0,170,3,303),
(161,'Nyköping','',0,171,3,304),
(162,'Nynäshamn','',0,172,3,303),
(163,'Nässjö','',0,173,3,297),
(164,'Ockelbo','',0,174,3,294),
(165,'Olofström','',9,175,3,291),
(166,'Orsa','',0,176,3,292),
(167,'Orust','',0,177,3,310),
(168,'Osby','',0,178,3,302),
(169,'Oskarshamn','',0,179,3,298),
(170,'Ovanåker','',0,180,3,294),
(171,'Oxelösund','',0,181,3,304),
(172,'Pajala','',0,182,3,300),
(173,'Partille','',0,183,3,310),
(174,'Perstorp','',0,184,3,302),
(175,'Piteå','',0,185,3,300),
(176,'Ragunda','',0,186,3,296),
(177,'Robertsfors','',0,187,3,307),
(178,'Ronneby','',0,188,3,291),
(179,'Rättvik','',0,189,3,292),
(180,'Sala','',0,190,3,309),
(181,'Salem','',0,191,3,303),
(182,'Sandviken','',0,192,3,294),
(183,'Sigtuna','',0,193,3,303),
(184,'Simrishamn','',0,194,3,302),
(185,'Sjöbo','',0,195,3,302),
(186,'Skara','',0,196,3,310),
(187,'Skellefteå','',0,197,3,307),
(188,'Skinnskatteberg','',0,198,3,309),
(189,'Skurup','',0,199,3,302),
(190,'Skövde','',0,200,3,310),
(191,'Smedjebacken','',0,201,3,292),
(192,'Sollefteå','',0,202,3,308),
(193,'Sollentuna','',0,203,3,303),
(194,'Solna','',0,204,3,303),
(195,'Sorsele','',0,205,3,307),
(196,'Sotenäs','',0,206,3,310),
(197,'Staffanstorp','',0,207,3,302),
(198,'Stenungsund','',0,208,3,310),
(199,'Stockholm','',0,209,3,303),
(200,'Storfors','',0,210,3,306),
(201,'Storuman','',0,211,3,307),
(202,'Strängnäs','',0,212,3,304),
(203,'Strömstad','',0,213,3,310),
(204,'Strömsund','',0,214,3,296),
(205,'Sundbyberg','',0,215,3,303),
(206,'Sundsvall','',0,216,3,308),
(207,'Sunne','',0,217,3,306),
(208,'Surahammar','',0,218,3,309),
(209,'Svalöv','',0,219,3,302),
(210,'Svedala','',0,220,3,302),
(211,'Svenljunga','',0,221,3,310),
(212,'Säffle','',0,222,3,306),
(213,'Säter','',0,223,3,292),
(214,'Sävsjö','',0,224,3,297),
(215,'Söderhamn','',0,225,3,294),
(216,'Söderköping','',0,226,3,312),
(217,'Södertälje','',0,227,3,303),
(218,'Sölvesborg','',0,228,3,291),
(219,'Tanum','',0,229,3,310),
(220,'Tibro','',0,230,3,310),
(221,'Tidaholm','',0,231,3,310),
(222,'Tierp','',0,232,3,305),
(223,'Timrå','',0,233,3,308),
(224,'Tingsryd','',0,234,3,299),
(225,'Tjörn','',0,235,3,310),
(226,'Tomelilla','',0,236,3,302),
(227,'Torsby','',0,237,3,306),
(228,'Torsås','',0,238,3,298),
(229,'Tranemo','',0,239,3,310),
(230,'Tranås','',0,240,3,297),
(231,'Trelleborg','',0,241,3,302),
(232,'Trollhättan','',0,242,3,310),
(233,'Trosa','',0,243,3,304),
(234,'Tyresö','',0,244,3,303),
(235,'Täby','',0,245,3,303),
(236,'Töreboda','',0,246,3,310),
(237,'Uddevalla','',0,247,3,310),
(238,'Ulricehamn','',0,248,3,310),
(239,'Umeå','',0,249,3,307),
(240,'Upplands Väsby','',0,250,3,303),
(241,'Upplands-Bro','',0,251,3,303),
(242,'Uppsala','',0,252,3,305),
(243,'Uppvidinge','',0,253,3,299),
(244,'Vadstena','',0,254,3,312),
(245,'Vaggeryd','',0,255,3,297),
(246,'Valdemarsvik','',0,256,3,312),
(247,'Vallentuna','',0,257,3,303),
(248,'Vansbro','',0,258,3,292),
(249,'Vara','',0,259,3,310),
(250,'Varberg','',0,260,3,295),
(251,'Vaxholm','',0,261,3,303),
(252,'Vellinge','',0,262,3,302),
(253,'Vetlanda','',0,263,3,297),
(254,'Vilhelmina','',0,264,3,307),
(255,'Vimmerby','',0,265,3,298),
(256,'Vindeln','',0,266,3,307),
(257,'Vingåker','',0,267,3,304),
(258,'Vårgårda','',0,268,3,310),
(259,'Vänersborg','',0,269,3,310),
(260,'Vännäs','',0,270,3,307),
(261,'Värmdö','',0,271,3,303),
(262,'Värnamo','',0,272,3,297),
(263,'Västervik','',0,273,3,298),
(264,'Västerå','',0,274,3,309),
(265,'Växjö','',0,275,3,299),
(266,'Ydre','',0,276,3,312),
(267,'Ystad','',0,277,3,302),
(268,'Åmål','',0,278,3,310),
(269,'Ånge','',0,279,3,308),
(270,'Åre','',0,280,3,296),
(271,'Årjäng','',0,281,3,306),
(272,'Åsele','',0,282,3,307),
(273,'Åstorp','',0,283,3,302),
(274,'Åtvidaberg','',0,284,3,312),
(275,'Älmhult','',0,285,3,299),
(276,'Älvdalen','',0,286,3,292),
(277,'Älvkarleby','',0,287,3,305),
(278,'Älvsbyn','',0,288,3,300),
(279,'Ängelholm','',0,289,3,302),
(280,'Öckerö','',0,290,3,310),
(281,'Ödeshög','',0,291,3,312),
(282,'Örebro','',0,292,3,311),
(283,'Örkelljunga','',0,293,3,302),
(284,'Örnsköldsvik','',0,294,3,308),
(285,'Östersund','',0,295,3,296),
(286,'Österåker','',0,296,3,303),
(287,'Östhammar','',0,297,3,305),
(288,'Östra Göinge','',0,298,3,302),
(289,'Överkalix','',0,299,3,300),
(290,'Övertorneå','',0,300,3,301),
(291,'Blekinge','',9,301,2,313),
(292,'Dalarna','',0,302,2,313),
(293,'Gotland','',0,303,2,313),
(294,'Gävleborg','',0,304,2,313),
(295,'Halland','',0,305,2,313),
(296,'Jämtland','',0,306,2,313),
(297,'Jönköping','',0,307,2,313),
(298,'Kalmar','',0,308,2,313),
(299,'Kronoberg','',0,309,2,313),
(300,'Norrbotten','',0,310,2,313),
(301,'Norrbotten','',0,311,2,313),
(302,'Skåne','',0,312,2,313),
(303,'Stockholm','',0,313,2,313),
(304,'Södermanland','',0,314,2,313),
(305,'Uppsala','',0,315,2,313),
(306,'Värmland','',0,316,2,313),
(307,'Västerbotten','',0,317,2,313),
(308,'Västernorrland','',0,318,2,313),
(309,'Västmanland','',0,319,2,313),
(310,'Västra Götaland','',0,320,2,313),
(311,'Örebro','',0,321,2,313),
(312,'Östergötland','',0,322,2,313),
(313,'Allmant','',4,1,1,NULL);
/*!40000 ALTER TABLE `constituency` ENABLE KEYS */;

--
-- Definition of table `constituency_delegate`
--

DROP TABLE IF EXISTS `constituency_delegate`;
CREATE TABLE `constituency_delegate` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `delegate_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=13 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `constituency_delegate`
--

/*!40000 ALTER TABLE `constituency_delegate` DISABLE KEYS */;
INSERT INTO `constituency_delegate` (`id`,`constituency_id`,`delegate_id`) VALUES 
 (7,291,6),
 (6,165,6),
 (10,165,7),
 (11,291,7),
 (12,313,7);
/*!40000 ALTER TABLE `constituency_delegate` ENABLE KEYS */;

--
-- Definition of table `constituency_level`
--

DROP TABLE IF EXISTS `constituency_level`;
CREATE TABLE `constituency_level` (
  `level` int(10) unsigned NOT NULL auto_increment,
  `name` varchar(20) NOT NULL default '',
  PRIMARY KEY  (`level`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `constituency_level`
--

/*!40000 ALTER TABLE `constituency_level` DISABLE KEYS */;
INSERT INTO `constituency_level` (`level`,`name`) VALUES 
 (1,'general'),
 (2,'region'),
 (3,'county'),
 (4,'workgroup');
/*!40000 ALTER TABLE `constituency_level` ENABLE KEYS */;

--
-- Definition of table `constituency_user`
--

DROP TABLE IF EXISTS `constituency_user`;
CREATE TABLE `constituency_user` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `user_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=42 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `constituency_user`
--

/*!40000 ALTER TABLE `constituency_user` DISABLE KEYS */;
INSERT INTO `constituency_user` (`id`,`constituency_id`,`user_id`) VALUES 
 (12,291,13),
 (34,165,4),
 (40,165,5),
 (4,165,6),
 (5,291,6),
 (41,291,5),
 (37,313,5),
 (11,165,13),
 (13,165,14),
 (14,291,14),
 (15,165,15),
 (16,291,15),
 (17,165,16),
 (18,291,16),
 (19,165,17),
 (20,291,17),
 (21,165,18),
 (22,291,18),
 (35,291,4),
 (36,313,4);
/*!40000 ALTER TABLE `constituency_user` ENABLE KEYS */;

--
-- Definition of table `delegate`
--

DROP TABLE IF EXISTS `delegate`;
CREATE TABLE `delegate` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `title` varchar(90) NOT NULL default '',
  `description` text NOT NULL,
  `timestamp_created` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=8 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `delegate`
--

/*!40000 ALTER TABLE `delegate` DISABLE KEYS */;
INSERT INTO `delegate` (`id`,`title`,`description`,`timestamp_created`) VALUES 
 (6,'Suddis Katt','',0),
 (7,'Missan Katt','',0);
/*!40000 ALTER TABLE `delegate` ENABLE KEYS */;

--
-- Definition of table `delegate_ballot`
--

DROP TABLE IF EXISTS `delegate_ballot`;
CREATE TABLE `delegate_ballot` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `vote_id` int(10) unsigned NOT NULL default '0',
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `ballot_alternative` varchar(9) default NULL,
  `vote_alternative_id` int(10) unsigned default NULL,
  `priority` int(10) unsigned default NULL,
  `median_vote_value` float default NULL,
  `ballot_owner_id` int(10) unsigned NOT NULL default '0',
  `delegate_id` int(10) unsigned default NULL,
  `delegation_level` int(10) unsigned default NULL,
  `delegate_priority` int(10) unsigned default NULL,
  `time_ballot_placed` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `delegate_ballot`
--

/*!40000 ALTER TABLE `delegate_ballot` DISABLE KEYS */;
INSERT INTO `delegate_ballot` (`id`,`vote_id`,`constituency_id`,`ballot_alternative`,`vote_alternative_id`,`priority`,`median_vote_value`,`ballot_owner_id`,`delegate_id`,`delegation_level`,`delegate_priority`,`time_ballot_placed`) VALUES 
 (1,1,165,'yes',NULL,NULL,NULL,0,6,NULL,NULL,1429188717);
/*!40000 ALTER TABLE `delegate_ballot` ENABLE KEYS */;

--
-- Definition of table `delegate_user`
--

DROP TABLE IF EXISTS `delegate_user`;
CREATE TABLE `delegate_user` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `delegate_id` int(10) unsigned NOT NULL default '0',
  `user_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `delegate_user`
--

/*!40000 ALTER TABLE `delegate_user` DISABLE KEYS */;
INSERT INTO `delegate_user` (`id`,`delegate_id`,`user_id`) VALUES 
 (1,6,6),
 (2,7,5);
/*!40000 ALTER TABLE `delegate_user` ENABLE KEYS */;

--
-- Definition of table `forum`
--

DROP TABLE IF EXISTS `forum`;
CREATE TABLE `forum` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `category_id` int(10) unsigned NOT NULL default '0',
  `title` varchar(45) NOT NULL default '',
  `description` text NOT NULL,
  `last_posted_time` int(10) unsigned default NULL,
  `last_posted_post` int(10) unsigned default NULL,
  `number_of_topics` int(10) unsigned NOT NULL default '0',
  `number_of_posts` int(10) unsigned NOT NULL default '0',
  `access_type` varchar(12) NOT NULL default 'public',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=337 DEFAULT CHARSET=latin1;

--
-- Dumping data for timestamp_addedble `forum`
--

/*!40000 ALTER TABLE `forum` DISABLE KEYS */;
INSERT INTO `forum` (`id`,`category_id`,`title`,`description`,`last_posted_time`,`last_posted_post`,`number_of_topics`,`number_of_posts`,`access_type`) VALUES 
 (1,4,'Testforumet','Forum för att testa saker. ',1441614926,110,9,60,'public'),
 (2,9,'Testgruppen','Publikt forum för arbetsgruppen Testgruppen.',NULL,NULL,0,0,'public'),
 (3,9,'Testgruppen','Publikt forum för arbetsgruppen Testgruppen.',NULL,NULL,0,0,'public'),
 (4,9,'Testgruppen','Publikt forum för arbetsgruppen Testgruppen.',NULL,NULL,0,0,'public'),
 (5,8,'Testgruppen','Privat forum för arbetsgruppen Testgruppen.',NULL,NULL,0,0,'workgroup'),
 (323,9,'Styrelsen','Publikt forum för arbetsgruppenStyrelsen',NULL,NULL,0,0,'public'),
 (324,8,'Styrelsen','Privat forum för arbetsgruppenStyrelsen',NULL,NULL,0,0,'workgroup'),
 (325,9,'Styrelsen','Publikt forum för arbetsgruppenStyrelsen',1441285219,102,1,1,'public'),
 (326,8,'Styrelsen','Privat forum för arbetsgruppenStyrelsen',NULL,NULL,0,0,'workgroup'),
 (327,9,'Styrelsen','Publikt forum för arbetsgruppenStyrelsen',1441285293,103,1,1,'public'),
 (328,8,'Styrelsen','Privat forum för arbetsgruppenStyrelsen',NULL,NULL,0,0,'workgroup'),
 (329,9,'Styrelsen','Publikt forum för arbetsgruppenStyrelsen',1441285446,104,1,1,'public'),
 (330,8,'Styrelsen','Privat forum för arbetsgruppenStyrelsen',NULL,NULL,0,0,'workgroup'),
 (331,9,'Styrelsen','Publikt forum för arbetsgruppenStyrelsen',1441286282,105,1,1,'public'),
 (332,8,'Styrelsen','Privat forum för arbetsgruppenStyrelsen',NULL,NULL,0,0,'workgroup'),
 (333,9,'Test','Publikt forum för arbetsgruppenTest',1441375857,106,1,1,'public'),
 (334,8,'Test','Privat forum för arbetsgruppenTest',NULL,NULL,0,0,'workgroup'),
 (335,9,'Ytterligare testgruppen','Publikt forum för arbetsgruppenYtterligare testgruppen',NULL,NULL,0,0,'public'),
 (336,8,'Ytterligare testgruppen','Privat forum för arbetsgruppenYtterligare testgruppen',NULL,NULL,0,0,'workgroup');
/*!40000 ALTER TABLE `forum` ENABLE KEYS */;

insert into forum
(id, category_id, title, description, access_type)
select forum_id, 2, title, description, 'local_county' 
from constituency where constituency_level = 3;

insert into forum
(id, category_id, title, description, access_type)
select forum_id, 2, title, description, 'local_region' 
from constituency where constituency_level = 2;

update forum 
set 
  last_posted_time = 1441566649,
  last_posted_post = 109,
    number_of_topics = 2,
    number_of_posts = 2
where title = 'Olofström';

--
-- Definition of table `post`
--

DROP TABLE IF EXISTS `post`;
CREATE TABLE `post` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `topic_id` int(10) unsigned NOT NULL default '0',
  `user_id` int(10) unsigned NOT NULL default '0',
  `forum_id` int(10) unsigned NOT NULL default '0',
  `is_topic` tinyint(3) unsigned NOT NULL default '0',
  `posted_time` int(10) unsigned NOT NULL default '0',
  `last_edited_time` int(10) unsigned default NULL,
  `title` varchar(90) NOT NULL default '',
  `content` text NOT NULL,
  PRIMARY KEY  USING HASH (`id`),
  FULLTEXT KEY `search` (`title`,`content`)
) ENGINE=MyISAM AUTO_INCREMENT=111 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `post`
--

/*!40000 ALTER TABLE `post` DISABLE KEYS */;
INSERT INTO `post` (`id`,`topic_id`,`user_id`,`forum_id`,`is_topic`,`posted_time`,`last_edited_time`,`title`,`content`) VALUES 
 (38,38,4,1,1,1432278142,NULL,'Testtråd',''),
 (39,39,4,1,1,1432294979,NULL,'Moderator lägger sig i','Ett svar. '),
 (40,40,4,1,1,1432295280,NULL,'En till testtråd',''),
 (41,41,4,1,1,1432295423,NULL,'Tredje testtråden',''),
 (42,42,4,1,1,1432295491,NULL,'Fjärde testtråden','Ytterligare test. '),
 (48,48,6,1,1,1432645559,NULL,'tst','svar'),
 (50,50,6,1,1,1432645649,NULL,'asrta','asdf'),
 (44,38,6,1,0,1432538300,NULL,'Testtråd','<div class=\"quote_in_post\"><a class=\"quote_in_post_link\" href=\"index.php?type=forum&action=show_posts&id=39\">Gullan Katt skrev:</a>\nsvar</div>\r\nSvar med citat. '),
 (51,50,5,1,0,1439976262,1439976272,'asrta','Ett svaråäö'),
 (52,50,5,1,0,1440052928,NULL,'asrta','Svar med &amp;quot;'),
 (53,50,5,1,0,1440053117,NULL,'asrta','Svar med &amp;quot;'),
 (54,50,5,1,0,1440053963,NULL,'asrta','Svar med &quot;'),
 (102,102,4,325,1,1441285219,NULL,'Personval till arbetsgruppen Styrelsen','Denna omröstning utser medlemmarna i arbetsgruppen <a href=\"index.php?type=workgroup&action=view&id=2\">Styrelsen</a>.'),
 (56,50,4,1,0,1440937896,NULL,'asrta','asdf'),
 (57,50,4,1,0,1440937902,NULL,'asrta','asdf'),
 (58,50,4,1,0,1440937904,NULL,'asrta','sadf'),
 (59,50,4,1,0,1440937906,NULL,'asrta','asdf'),
 (60,50,4,1,0,1440937909,NULL,'asrta','sdfa'),
 (61,50,4,1,0,1440937911,NULL,'asrta','sdf'),
 (62,50,4,1,0,1440937913,NULL,'asrta','sdfasd'),
 (63,50,4,1,0,1440937916,NULL,'asrta','asdfas'),
 (64,50,4,1,0,1440937918,NULL,'asrta','sadfsa'),
 (65,50,4,1,0,1440937921,NULL,'asrta','asdf'),
 (66,50,4,1,0,1440937923,NULL,'asrta','sadf'),
 (67,50,4,1,0,1440937925,NULL,'asrta','sadf'),
 (68,50,4,1,0,1440937927,NULL,'asrta','asdf'),
 (69,50,4,1,0,1440937929,NULL,'asrta','sadfa'),
 (70,50,4,1,0,1440937931,NULL,'asrta','asdf'),
 (71,50,4,1,0,1440937934,NULL,'asrta','asdf'),
 (72,50,4,1,0,1440937937,NULL,'asrta','sdf'),
 (73,50,4,1,0,1440937938,NULL,'asrta','sadf'),
 (74,50,4,1,0,1440937940,NULL,'asrta','sadf'),
 (75,50,4,1,0,1440937942,NULL,'asrta','sadf'),
 (76,50,4,1,0,1440937944,NULL,'asrta','asdf'),
 (77,50,4,1,0,1440937946,NULL,'asrta','sadf'),
 (78,50,4,1,0,1440937948,NULL,'asrta','sadfa'),
 (79,50,4,1,0,1440937949,NULL,'asrta','asdf'),
 (80,50,4,1,0,1440937951,NULL,'asrta','sadf'),
 (81,50,4,1,0,1440937953,NULL,'asrta','asdf'),
 (82,50,4,1,0,1440937955,NULL,'asrta','asdf'),
 (83,50,4,1,0,1440937957,NULL,'asrta','asdf'),
 (84,50,4,1,0,1440937959,NULL,'asrta','sadf'),
 (85,50,4,1,0,1440937960,NULL,'asrta','asdf'),
 (86,50,4,1,0,1440937962,NULL,'asrta','asdf'),
 (87,50,4,1,0,1440937964,NULL,'asrta','sadf'),
 (88,50,4,1,0,1440937966,NULL,'asrta','asdf'),
 (89,50,4,1,0,1440937970,NULL,'asrta','sadf\r\n'),
 (90,50,4,1,0,1440937971,NULL,'asrta','sadf'),
 (91,50,4,1,0,1440937975,NULL,'asrta','\r\nsadf'),
 (92,50,4,1,0,1440937977,NULL,'asrta','sadf'),
 (93,50,4,1,0,1440937978,NULL,'asrta','asdf'),
 (94,50,4,1,0,1440937980,NULL,'asrta','sdaf'),
 (95,50,4,1,0,1440937982,NULL,'asrta','sadf'),
 (96,50,4,1,0,1440937983,NULL,'asrta','sadf'),
 (97,50,4,1,0,1440937985,NULL,'asrta','sadf'),
 (98,50,4,1,0,1440937987,NULL,'asrta','asdf'),
 (99,50,4,1,0,1440937989,NULL,'asrta','sadf'),
 (100,50,4,1,0,1440937991,NULL,'asrta','sadf'),
 (101,50,4,1,0,1440937996,NULL,'asrta','sadf'),
 (103,103,4,327,1,1441285293,NULL,'Personval till arbetsgruppen Styrelsen','Denna omröstning utser medlemmarna i arbetsgruppen <a href=\"index.php?type=workgroup&action=view&id=3\">Styrelsen</a>.'),
 (104,104,4,329,1,1441285446,NULL,'Personval till arbetsgruppen Styrelsen','Denna omröstning utser medlemmarna i arbetsgruppen <a href=\"index.php?type=workgroup&action=view&id=4\">Styrelsen</a>.'),
 (105,105,4,331,1,1441286282,NULL,'Personval till arbetsgruppen Styrelsen','Denna omröstning utser medlemmarna i arbetsgruppen <a href=\"index.php?type=workgroup&action=view&id=5\">Styrelsen</a>.'),
 (106,106,5,333,1,1441375857,NULL,'Personval till arbetsgruppen Test','Denna omröstning utser medlemmarna i arbetsgruppen <a href=\"index.php?type=workgroup&action=view&id=6\">Test</a>.'),
 (107,107,5,1,1,1441469576,NULL,'test','test'),
 (108,108,5,175,1,1441541122,NULL,'Nytt test','test\r\n'),
 (109,109,5,175,1,1441566649,NULL,'mediantest','test'),
 (110,110,5,1,1,1441614926,NULL,'fdfgd','hfgdf');
/*!40000 ALTER TABLE `post` ENABLE KEYS */;

--
-- Definition of table `post_report`
--

DROP TABLE IF EXISTS `post_report`;
CREATE TABLE `post_report` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `post_id` int(10) unsigned NOT NULL default '0',
  `reporter_id` int(10) unsigned NOT NULL default '0',
  `time_report_filed` int(10) unsigned NOT NULL default '0',
  `argument` text NOT NULL,
  `time_resolved` int(10) unsigned NOT NULL default '0',
  `resolved_by_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Definition of table `forum_user`
--

DROP TABLE IF EXISTS `forum_user`;
CREATE TABLE `forum_user` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `user_id` int(10) unsigned NOT NULL default '0',
  `forum_id` int(10) unsigned NOT NULL default '0',
  `access_type` tinyint(3) unsigned NOT NULL default '1',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=132 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `forum_user`
--

/*!40000 ALTER TABLE `forum_user` DISABLE KEYS */;
INSERT INTO `forum_user` (`id`,`user_id`,`forum_id`,`access_type`) VALUES 
 (44,13,301,1),
 (2,4,1,1),
 (3,5,1,1),
 (4,6,1,1),
 (98,4,323,1),
 (43,13,175,1),
 (7,4,4,1),
 (8,5,4,1),
 (9,6,4,1),
 (42,13,4,1),
 (11,4,5,1),
 (41,13,3,1),
 (97,4,301,1),
 (131,5,301,1),
 (16,6,175,1),
 (17,6,301,1),
 (130,5,175,1),
 (96,4,175,1),
 (40,13,2,1),
 (39,13,1,1),
 (45,14,1,1),
 (46,14,2,1),
 (47,14,3,1),
 (48,14,4,1),
 (49,14,175,1),
 (50,14,301,1),
 (51,15,1,1),
 (52,15,2,1),
 (53,15,3,1),
 (54,15,4,1),
 (55,15,175,1),
 (56,15,301,1),
 (57,16,1,1),
 (58,16,2,1),
 (59,16,3,1),
 (60,16,4,1),
 (61,16,175,1),
 (62,16,301,1),
 (63,17,1,1),
 (64,17,2,1),
 (65,17,3,1),
 (66,17,4,1),
 (67,17,175,1),
 (68,17,301,1),
 (69,18,1,1),
 (70,18,2,1),
 (71,18,3,1),
 (72,18,4,1),
 (73,18,175,1),
 (74,18,301,1),
 (99,5,323,1),
 (100,6,323,1),
 (101,13,323,1),
 (102,4,325,1),
 (103,5,325,1),
 (104,6,325,1),
 (105,13,325,1),
 (106,4,327,1),
 (107,5,327,1),
 (108,6,327,1),
 (109,13,327,1),
 (110,4,329,1),
 (111,5,329,1),
 (112,6,329,1),
 (113,13,329,1),
 (114,4,331,1),
 (115,5,331,1),
 (116,6,331,1),
 (117,13,331,1),
 (119,5,332,1),
 (120,4,333,1),
 (121,5,333,1),
 (122,6,333,1),
 (123,13,333,1),
 (124,4,335,1),
 (125,5,335,1),
 (126,6,335,1),
 (127,13,335,1);
/*!40000 ALTER TABLE `forum_user` ENABLE KEYS */;

--
-- Definition of table `membership_fee`
--

DROP TABLE IF EXISTS `membership_fee`;
CREATE TABLE `membership_fee` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `user_id` int(10) unsigned NOT NULL default '0',
  `timestamp` int(10) unsigned NOT NULL default '0',
  `sum` int(10) unsigned NOT NULL default '0',
  `to_account_id` int(10) unsigned default NULL,
  `message` varchar(255) default NULL,
  `payment_for_year` int(4) unsigned default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Definition of table `message`
--

DROP TABLE IF EXISTS `message`;
CREATE TABLE `message` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `sender_id` int(10) unsigned NOT NULL default '0',
  `recipient_id` int(10) unsigned NOT NULL default '0',
  `sent_time` int(10) unsigned NOT NULL default '0',
  `read_time` int(10) unsigned NOT NULL default '0',
  `deleted_by_sender` int(10) unsigned NOT NULL default '0',
  `deleted_by_recipient` int(10) unsigned NOT NULL default '0',
  `title` varchar(90) NOT NULL default '',
  `content` text NOT NULL,
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `search` (`title`,`content`)
) ENGINE=MyISAM AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `message`
--

/*!40000 ALTER TABLE `message` DISABLE KEYS */;
INSERT INTO `message` (`id`,`sender_id`,`recipient_id`,`sent_time`,`read_time`,`deleted_by_sender`,`deleted_by_recipient`,`title`,`content`) VALUES 
 (9,5,6,1440141538,1440831678,0,0,'test','test'),
 (10,5,0,1440141623,0,0,0,'Ingentest','test');
/*!40000 ALTER TABLE `message` ENABLE KEYS */;

--
-- Definition of table `proposition`
--

DROP TABLE IF EXISTS `proposition`;
CREATE TABLE `proposition` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `type` varchar(20) NOT NULL default '',
  `created_by_user` int(10) unsigned default NULL,
  `created_by_delegate` int(10) unsigned default NULL,
  `timestamp_created` int(10) unsigned NOT NULL default '0',
  `timestamp_ended` int(10) unsigned default NULL,
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `status` varchar(12) NOT NULL default 'pending',
  `number_of_supporters` int(10) unsigned NOT NULL default '0',
  `number_of_abstains` int(10) unsigned NOT NULL default '0',
  `title` varchar(90) NOT NULL default '',
  `description` text NOT NULL,
  `forum_topic_id` int(10) unsigned default NULL,
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `search` (`title`,`description`)
) ENGINE=MyISAM AUTO_INCREMENT=10 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `proposition`
--

/*!40000 ALTER TABLE `proposition` DISABLE KEYS */;
INSERT INTO `proposition` (`id`,`type`,`created_by_user`,`created_by_delegate`,`timestamp_created`,`timestamp_ended`,`constituency_id`,`status`,`number_of_supporters`,`number_of_abstains`,`title`,`description`,`forum_topic_id`) VALUES 
 (1,'yes-no',5,NULL,1426586078,NULL,165,'rejected',0,1,'Testvotering','Bara ett test. ',31),
 (2,'yes-no',5,NULL,1428388195,NULL,165,'affirmed',1,0,'Testvotering2','Ett test till. ',32),
 (3,'median',4,NULL,1428506873,1428506887,165,'affirmed',1,0,'Mediantest','Test av medianomröstningar.',33),
 (4,'prio-vote',6,NULL,1430116507,1430117564,165,'affirmed',1,0,'Prio-test','Det är dags att testa prioritetsomröstningar. ',34),
 (5,'candidate-election',6,NULL,1430808243,1430850944,165,'affirmed',1,0,'Personvalstest','Test av personvalsfunktionen. ',35),
 (6,'yes-no',5,NULL,1441469576,1441469588,313,'affirmed',1,0,'test','test',107),
 (7,'yes-no',5,NULL,1441541122,NULL,165,'pending',2,0,'Nytt test','test\r\n',108),
 (8,'median',5,NULL,1441566650,1441566655,165,'affirmed',1,0,'mediantest','test',109),
 (9,'yes-no',5,NULL,1441614927,1441614937,313,'affirmed',1,0,'fdfgd','hfgdf',110);
/*!40000 ALTER TABLE `proposition` ENABLE KEYS */;

--
-- Definition of table `proposition_support`
--

DROP TABLE IF EXISTS `proposition_support`;
CREATE TABLE `proposition_support` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `proposition_id` int(10) unsigned NOT NULL default '0',
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `user_code` varchar(20) default NULL,
  `voter_is_delegate_id` int(10) unsigned default NULL,
  `delegate_id` int(10) unsigned default NULL,
  `delegation_level` int(10) unsigned default NULL,
  `delegate_priority` int(10) unsigned default NULL,
  `support_type` varchar(7) NOT NULL default 'support',
  `time_ballot_placed` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=32 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `proposition_support`
--

/*!40000 ALTER TABLE `proposition_support` DISABLE KEYS */;
INSERT INTO `proposition_support` (`id`,`proposition_id`,`constituency_id`,`user_code`,`voter_is_delegate_id`,`delegate_id`,`delegation_level`,`delegate_priority`,`support_type`,`time_ballot_placed`) VALUES 
 (6,1,0,'osb8A8xrrQrGQfologrm',NULL,NULL,NULL,NULL,'reject',0),
 (7,2,0,'osb8A8xrrQrGQfologrm',NULL,NULL,NULL,NULL,'support',1428388208),
 (8,3,0,'OBc7rZoonK45KsRWs4gq',NULL,NULL,NULL,NULL,'support',1428506887),
 (9,4,0,'nNSpJccU3OdwJxq3SMBw',NULL,NULL,NULL,NULL,'support',1430117564),
 (10,5,0,'nNSpJccU3OdwJxq3SMBw',NULL,NULL,NULL,NULL,'support',1430850943),
 (11,6,0,'osb8A8xrrQrGQfologrm',NULL,NULL,NULL,NULL,'support',1441469588),
 (12,8,0,'osb8A8xrrQrGQfologrm',NULL,NULL,NULL,NULL,'support',1441566655),
 (13,9,0,'osb8A8xrrQrGQfologrm',NULL,NULL,NULL,NULL,'support',1441614937),
 (31,7,165,'nNSpJccU3OdwJxq3SMBw',NULL,7,0,1,'support',1443615670),
 (30,7,165,NULL,7,NULL,NULL,NULL,'support',1443615670),
 (27,7,165,'osb8A8xrrQrGQfologrm',NULL,NULL,NULL,NULL,'support',1443515050);
/*!40000 ALTER TABLE `proposition_support` ENABLE KEYS */;

--
-- Definition of table `user`
--

DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` varchar(45) NOT NULL default '',
  `password` varchar(128) NOT NULL default '',
  `remember_me_token` varchar(128) default NULL,
  `registration_time` int(10) unsigned NOT NULL default '0',
  `deletion_time` int(10) unsigned default NULL,
  `last_login_time` int(10) unsigned default NULL,
  `last_activity_time` int(10) unsigned default NULL,
  `first_name` varchar(45) default '',
  `last_name` varchar(45) default '',
  `street_address` varchar(45) default '',
  `zip_code` varchar(10) default '',
  `city_address` varchar(45) default '',
  `county` varchar(45) default '',
  `region` varchar(45) default '',
  `social_security_number` varchar(13) default '',
  `email` varchar(45) NOT NULL default '',
  `telephone1` varchar(20) default '',
  `telephone2` varchar(20) default '',
  `skype_name` varchar(45) default '',
  `show_email` tinyint(1) unsigned NOT NULL default '1',
  `show_telephone` tinyint(1) unsigned NOT NULL default '1',
  `show_skype` tinyint(1) unsigned NOT NULL default '1',
  `number_of_posts` int(10) unsigned NOT NULL default '0',
  `number_of_topics` int(10) unsigned NOT NULL default '0',
  `membership_fee_payed` int(10) unsigned default NULL,
  `last_contact_with_admin` int(10) unsigned default NULL,
  `acting_as_delegate` tinyint(1) unsigned default '0',
  `user_role` int(10) unsigned NOT NULL default '2',
  `admin_notes` varchar(255) default '',
  `image` varchar(90) NOT NULL default 'no_image.png',
  `description` text,
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `search` (`first_name`,`last_name`,`description`)
) ENGINE=MyISAM AUTO_INCREMENT=19 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `user`
--

/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` (`id`,`username`,`password`,`remember_me_token`,`registration_time`,`deletion_time`,`last_login_time`,`last_activity_time`,`first_name`,`last_name`,`street_address`,`zip_code`,`city_address`,`county`,`region`,`social_security_number`,`email`,`telephone1`,`telephone2`,`skype_name`,`show_email`,`show_telephone`,`show_skype`,`number_of_posts`,`number_of_topics`,`membership_fee_payed`,`last_contact_with_admin`,`acting_as_delegate`,`user_role`,`admin_notes`,`image`,`description`) VALUES 
 (13,'skutt','$2a$08$.D/rwa/4GMuDX6toO6f0S.k0l6NbHYOd5riJqLbtiNeklXN7WRtQe','$2a$08$WAzFNLCyIlWNmP3uzPqewe8phR06obIhBVeudO.vaN3zHE2gM9IWu',1432280530,NULL,1433764952,1433765659,'Skutt','Katt','','','','Olofström','Blekinge\r\n','','skutt@katt.se','','','',1,1,1,0,0,NULL,NULL,0,2,'','no_image.png',NULL),
 (4,'gullan','$2a$08$qmMitF1wFOtDsNkpQqLn8e9my0OojrDFXy3uBR9lKxVOHrbbShM/y','$2a$08$eqsqQVMQ3TD4Eedn3bZxbu.F3CYI1Bwl2fgYtivLGu.bWxEVB4Bou',1420102449,NULL,1441270294,1441305594,'Gullan','Katt','Blä 3','12345','Olle','Olofström','Blekinge\r\n','','gullan@katt.se','','','',1,1,1,55,9,NULL,NULL,0,2,'','no_image.png','Mjau.'),
 (5,'missan','$2a$08$zaaFjU/eVdew7BqSTG4oyO.5UsZ6H2F6lugaJU0Mwnvag3mPp.Vta','$2a$08$.xLTCZskLeEw3wfJNyUHBeg1eRrhYbvk/bYtmOXrpB3n2jh0BeInO',1420102512,NULL,1444481227,1444481384,'Missan','Katt','','0','','Olofström','Blekinge\r\n','110202-1234','missan@katt.se','','','',1,1,1,9,5,NULL,NULL,0,2,'','Pb8fdDccUQwOv6thRoG0.jpg',NULL),
 (6,'suddis','$2a$08$ByrId8LM06kA.4PaMj4MGu/Ftkyh/nMwj.3zFfiDLv3fAUzbLmkRC','$2a$08$E/pVVtVRuew/mflf3YJHDuHihl4TN0vlpK3fv0oSQ/Lfm2GC7mthq',1420102590,NULL,1444585621,1444729438,'Suddis','Katt','','','','Olofström','Blekinge\r\n','','suddis@katt.se','','','',1,1,1,3,2,NULL,NULL,0,2,'','no_image.png',NULL);
/*!40000 ALTER TABLE `user` ENABLE KEYS */;

--
-- Definition of table `user_application`
--

DROP TABLE IF EXISTS `user_application`;
CREATE TABLE `user_application` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `application_filed_time` int(10) unsigned default NULL,
  `first_name` varchar(45) default '',
  `last_name` varchar(45) default '',
  `street_address` varchar(45) default '',
  `zip_code` varchar(10) default '',
  `city_address` varchar(45) default '',
  `county` varchar(45) default '',
  `region` varchar(45) default '',
  `social_security_number` varchar(13) default '',
  `email` varchar(45) NOT NULL default '',
  `telephone1` varchar(20) default '',
  `telephone2` varchar(20) default '',
  `skype_name` varchar(45) default '',
  `membership_fee_payed` int(10) unsigned default NULL,
  `admin_notes` varchar(255) default '',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=latin1;

--
-- Definition of table `vote`
--

DROP TABLE IF EXISTS `vote`;
CREATE TABLE `vote` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `type` varchar(20) NOT NULL default '',
  `from_proposition_id` int(10) unsigned default NULL,
  `timestamp_created` int(10) unsigned NOT NULL default '0',
  `timestamp_delegate_ended` int(10) unsigned default NULL,
  `timestamp_ended` int(10) unsigned default NULL,
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `status` varchar(10) NOT NULL default 'active',
  `title` varchar(90) NOT NULL default '',
  `description` text NOT NULL,
  `number_of_alternatives` int(10) unsigned NOT NULL default '0',
  `number_of_ballots` int(10) unsigned NOT NULL default '0',
  `number_of_direct_ballots` int(10) unsigned NOT NULL default '0',
  `forum_topic_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `search` (`title`,`description`)
) ENGINE=MyISAM AUTO_INCREMENT=14 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `vote`
--

/*!40000 ALTER TABLE `vote` DISABLE KEYS */;
INSERT INTO `vote` (`id`,`type`,`from_proposition_id`,`timestamp_created`,`timestamp_delegate_ended`,`timestamp_ended`,`constituency_id`,`status`,`title`,`description`,`number_of_alternatives`,`number_of_ballots`,`number_of_direct_ballots`,`forum_topic_id`) VALUES 
 (1,'yes-no',2,1428388208,1434010767,1439842347,165,'ended','Testvotering2','Ett test till. ',0,4,4,32),
 (2,'median',3,1428506887,1429111687,1439842440,165,'ended','Mediantest','Test av medianomröstningar.',0,3,3,33),
 (3,'prio-vote',4,1430117564,1430722364,1439842523,165,'ended','Prio-test','Det är dags att testa prioritetsomröstningar. ',5,1,1,34),
 (4,'candidate-election',5,1430850944,1432061700,1439842560,165,'ended','Personvalstest','Test av personvalsfunktionen. ',2,1,1,35),
 (5,'yes-no',NULL,1431852086,NULL,NULL,291,'continuous','Adminskapad omröstning','Test av admin-funktioner.',0,1,0,36),
 (6,'prio-vote',NULL,1431861479,NULL,NULL,291,'continuous','Kontinuerlig prioritetsomröstning','Ännu ett test. ',1,0,0,37),
 (7,'workgroup-election',NULL,1441285293,NULL,NULL,313,'continuous','Styrelsen','Denna omröstning utser medlemmarna i arbetsgruppen &lt;a href=&quot;index.php?type=workgroup&amp;action=view&amp;id=3&quot;&gt;Styrelsen&lt;/a&gt;.',0,0,0,103),
 (8,'workgroup-election',NULL,1441285446,NULL,NULL,313,'continuous','Styrelsen','Denna omröstning utser medlemmarna i arbetsgruppen &lt;a href=&quot;index.php?type=workgroup&amp;action=view&amp;id=4&quot;&gt;Styrelsen&lt;/a&gt;.',0,1,1,104),
 (9,'workgroup-election',5,1441286283,NULL,NULL,313,'continuous','Val av medlemmar till arbetsgruppen Styrelsen','Denna omröstning utser medlemmarna i arbetsgruppen <a href=\"index.php?type=workgroup&action=view&id=5\">Styrelsen</a>.',2,1,0,105),
 (10,'workgroup-election',6,1441375857,NULL,NULL,313,'continuous','Val av medlemmar till arbetsgruppen Test','Denna omröstning utser medlemmarna i arbetsgruppen <a href=\"index.php?type=workgroup&action=view&id=6\">Test</a>.',0,0,0,106),
 (11,'yes-no',6,1441469588,1442074388,1442679188,313,'active','test','test',0,0,0,107),
 (12,'median',8,1441566655,1442171455,1442776255,165,'active','mediantest','test',0,0,0,109),
 (13,'yes-no',9,1441614937,1442219737,1442824537,313,'active','fdfgd','hfgdf',0,1,0,110);
/*!40000 ALTER TABLE `vote` ENABLE KEYS */;

--
-- Definition of table `vote_alternative`
--

DROP TABLE IF EXISTS `vote_alternative`;
CREATE TABLE `vote_alternative` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `vote_id` int(10) unsigned NOT NULL default '0',
  `added_by_user` int(10) unsigned default NULL,
  `added_by_delegate` int(10) unsigned default NULL,
  `timestamp_added` int(10) unsigned NOT NULL default '0',
  `alternative_title` varchar(90) NOT NULL default '',
  `alternative_description` text NOT NULL,
  `alternative_user_id` int(10) unsigned default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=14 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `vote_alternative`
--

/*!40000 ALTER TABLE `vote_alternative` DISABLE KEYS */;
INSERT INTO `vote_alternative` (`id`,`vote_id`,`added_by_user`,`added_by_delegate`,`timestamp_added`,`alternative_title`,`alternative_description`,`alternative_user_id`) VALUES 
 (1,3,6,NULL,1430376548,'Första alternativet','Det allra första alternativet i en prioomröstning. ',NULL),
 (2,3,6,NULL,1430390060,'Andra alternativet','Ett alternativ till. ',NULL),
 (3,3,6,NULL,1430390078,'Tredje alternativet','Och, slutligen, ännu ett alternativ. ',NULL),
 (4,3,6,NULL,1430807992,'Fjärde alternativet','Ett fjärde alternativ. ',NULL),
 (6,4,6,NULL,1430897482,'Suddis Katt','Mer katter i den flytande demokratin. ',6),
 (8,3,NULL,NULL,1432040362,'Alternativ fem','Numero cinq.',NULL),
 (10,4,4,NULL,1432053297,'Gullan Katt','Gullan är en tvångskandidat.',4),
 (11,9,4,NULL,1441305522,'Gullan Katt','Det här är Gullan.',4),
 (12,9,5,NULL,1441305636,'Missan Katt','Det här är Missan.',5),
 (13,6,5,NULL,1441363409,'Ett alternativ','Alternativ 1',NULL);
/*!40000 ALTER TABLE `vote_alternative` ENABLE KEYS */;

--
-- Definition of table `voter_delegate`
--

DROP TABLE IF EXISTS `voter_delegate`;
CREATE TABLE `voter_delegate` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `delegate_id` int(10) unsigned NOT NULL default '0',
  `user_code` varchar(20) default NULL,
  `voter_is_delegate_id` int(10) unsigned default NULL,
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `priority` int(10) unsigned NOT NULL default '1',
  `time_delegate_chosen` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=15 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `voter_delegate`
--

/*!40000 ALTER TABLE `voter_delegate` DISABLE KEYS */;
INSERT INTO `voter_delegate` (`id`,`delegate_id`,`user_code`,`voter_is_delegate_id`,`constituency_id`,`priority`,`time_delegate_chosen`) VALUES 
 (3,7,'nNSpJccU3OdwJxq3SMBw',NULL,313,1,1433765591),
 (4,7,'nNSpJccU3OdwJxq3SMBw',NULL,165,1,1433765597),
 (10,6,'9ZvUSJF2Y9binMKfwOr7',NULL,291,1,1433854555),
 (14,7,NULL,6,291,1,1434868372);
/*!40000 ALTER TABLE `voter_delegate` ENABLE KEYS */;

--
-- Definition of table `workgroup`
--

DROP TABLE IF EXISTS `workgroup`;
CREATE TABLE `workgroup` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `title` varchar(90) NOT NULL default '',
  `description` text NOT NULL,
  `is_active` tinyint(3) unsigned NOT NULL default '0',
  `number_of_members` int(10) unsigned NOT NULL default '0',
  `create_time` int(10) unsigned default NULL,
  `create_user` int(10) unsigned NOT NULL default '0',
  `public_forum_id` int(10) unsigned default NULL,
  `is_restricted` tinyint(3) unsigned NOT NULL default '0',
  `propose_time` int(10) unsigned NOT NULL default '0',
  `private_forum_id` int(10) unsigned default NULL,
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `search` (`title`,`description`)
) ENGINE=MyISAM AUTO_INCREMENT=8 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroup`
--

/*!40000 ALTER TABLE `workgroup` DISABLE KEYS */;
INSERT INTO `workgroup` (`id`,`title`,`description`,`is_active`,`number_of_members`,`create_time`,`create_user`,`public_forum_id`,`is_restricted`,`propose_time`,`private_forum_id`) VALUES 
 (1,'Testgruppen','Vi <b>testar </b><u>funktionerna</u>. ',1,3,1423038623,1,4,1,0,5),
 (5,'Styrelsen','Styrelsen was here.',1,2,1441286282,4,331,1,0,332),
 (6,'Test','test',1,2,1441375856,5,333,10,0,334),
 (7,'Ytterligare testgruppen','mer test',0,0,NULL,5,335,0,1441470863,336);
/*!40000 ALTER TABLE `workgroup` ENABLE KEYS */;

--
-- Definition of table `workgroup_candidate`
--

DROP TABLE IF EXISTS `workgroup_candidate`;
CREATE TABLE `workgroup_candidate` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `workgroup_id` int(10) unsigned NOT NULL default '0',
  `candidate_id` int(10) unsigned NOT NULL default '0',
  `number_of_supporters` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

--
-- Definition of table `workgroup_candidate_support`
--

DROP TABLE IF EXISTS `workgroup_candidate_support`;
CREATE TABLE `workgroup_candidate_support` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `workgroup_id` int(10) unsigned NOT NULL default '0',
  `candidate_id` int(10) unsigned NOT NULL default '0',
  `supporter_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroup_candidate_support`
--

/*!40000 ALTER TABLE `workgroup_candidate_support` DISABLE KEYS */;
INSERT INTO `workgroup_candidate_support` (`id`,`workgroup_id`,`candidate_id`,`supporter_id`) VALUES 
 (3,1,6,4);
/*!40000 ALTER TABLE `workgroup_candidate_support` ENABLE KEYS */;

--
-- Definition of table `workgroup_election_change`
--

DROP TABLE IF EXISTS `workgroup_election_change`;
CREATE TABLE `workgroup_election_change` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `workgroup_id` int(10) unsigned NOT NULL default '0',
  `timestamp` int(10) unsigned NOT NULL default '0',
  `user_id_in` int(10) unsigned NOT NULL default '0',
  `user_id_out` int(10) unsigned default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroup_election_change`
--

/*!40000 ALTER TABLE `workgroup_election_change` DISABLE KEYS */;
INSERT INTO `workgroup_election_change` (`id`,`workgroup_id`,`timestamp`,`user_id_in`,`user_id_out`) VALUES 
 (6,5,1441369382,4,5);
/*!40000 ALTER TABLE `workgroup_election_change` ENABLE KEYS */;

--
-- Definition of table `workgroup_member`
--

DROP TABLE IF EXISTS `workgroup_member`;
CREATE TABLE `workgroup_member` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `workgroup_id` int(10) unsigned NOT NULL default '0',
  `user_id` int(10) unsigned NOT NULL default '0',
  `member_since` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=19 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroup_member`
--

/*!40000 ALTER TABLE `workgroup_member` DISABLE KEYS */;
INSERT INTO `workgroup_member` (`id`,`workgroup_id`,`user_id`,`member_since`) VALUES 
 (15,1,6,1432278227),
 (14,1,4,1423038623),
 (16,1,13,1432280594),
 (18,5,5,1441368106);
/*!40000 ALTER TABLE `workgroup_member` ENABLE KEYS */;

--
-- Definition of table `workgroup_member_exclude`
--

DROP TABLE IF EXISTS `workgroup_member_exclude`;
CREATE TABLE `workgroup_member_exclude` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `workgroup_id` int(10) unsigned NOT NULL default '0',
  `excluded_id` int(10) unsigned NOT NULL default '0',
  `excluder_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=20 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroup_member_exclude`
--

/*!40000 ALTER TABLE `workgroup_member_exclude` DISABLE KEYS */;
INSERT INTO `workgroup_member_exclude` (`id`,`workgroup_id`,`excluded_id`,`excluder_id`) VALUES 
 (19,1,1,4);
/*!40000 ALTER TABLE `workgroup_member_exclude` ENABLE KEYS */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
