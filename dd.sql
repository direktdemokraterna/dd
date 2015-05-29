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
-- Create schema dd
--

CREATE DATABASE IF NOT EXISTS dd;
USE dd;

--
-- Definition of table `admin_roles`
--

DROP TABLE IF EXISTS `admin_roles`;
CREATE TABLE `admin_roles` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `title` varchar(90) NOT NULL default '',
  `description` text,
  `type` varchar(45) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `admin_roles`
--

/*!40000 ALTER TABLE `admin_roles` DISABLE KEYS */;
INSERT INTO `admin_roles` (`id`,`title`,`description`,`type`) VALUES 
 (1,'Superadmin','','superadmin'),
 (2,'Medlemsadministratör','','member_admin'),
 (3,'Forumadministratör','','forum_admin'),
 (4,'Valadministratör','','vote_admin'),
 (5,'Kassör','','treasurer');
/*!40000 ALTER TABLE `admin_roles` ENABLE KEYS */;


--
-- Definition of table `admin_roles_users`
--

DROP TABLE IF EXISTS `admin_roles_users`;
CREATE TABLE `admin_roles_users` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `admin_role_id` int(10) unsigned NOT NULL default '0',
  `user_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=93 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `admin_roles_users`
--

/*!40000 ALTER TABLE `admin_roles_users` DISABLE KEYS */;
INSERT INTO `admin_roles_users` (`id`,`admin_role_id`,`user_id`) VALUES 
 (89,1,5),
 (88,5,13),
 (87,4,6),
 (80,2,4),
 (86,3,6),
 (85,2,6),
 (84,1,4),
 (90,5,5),
 (91,2,5),
 (92,3,13);
/*!40000 ALTER TABLE `admin_roles_users` ENABLE KEYS */;


--
-- Definition of table `ballots`
--

DROP TABLE IF EXISTS `ballots`;
CREATE TABLE `ballots` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `vote_id` int(10) unsigned NOT NULL default '0',
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `ballot_alternative` varchar(9) default NULL,
  `prio_ranking` text,
  `median_vote_value` float default NULL,
  `user_code` varchar(20) default NULL,
  `voter_is_delegate_id` int(10) unsigned default NULL,
  `delegate_id` int(10) unsigned default NULL,
  `delegation_level` int(10) unsigned default NULL,
  `delegate_priority` int(10) unsigned default NULL,
  `time_ballot_placed` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=39 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ballots`
--

/*!40000 ALTER TABLE `ballots` DISABLE KEYS */;
INSERT INTO `ballots` (`id`,`vote_id`,`constituency_id`,`ballot_alternative`,`prio_ranking`,`median_vote_value`,`user_code`,`voter_is_delegate_id`,`delegate_id`,`delegation_level`,`delegate_priority`,`time_ballot_placed`) VALUES 
 (9,1,165,'no',NULL,NULL,'osb8A8xrrQrGQfologrm',NULL,NULL,NULL,NULL,1429079651),
 (5,1,165,'no',NULL,NULL,'OBc7rZoonK45KsRWs4gq',NULL,NULL,NULL,NULL,1428507410),
 (6,2,165,NULL,NULL,10,'OBc7rZoonK45KsRWs4gq',NULL,NULL,NULL,NULL,1428695008),
 (10,2,165,NULL,NULL,30,'osb8A8xrrQrGQfologrm',NULL,NULL,NULL,NULL,1429079955),
 (18,1,165,'no',NULL,NULL,'nNSpJccU3OdwJxq3SMBw',NULL,NULL,NULL,NULL,1430117214),
 (15,2,165,NULL,NULL,22,'nNSpJccU3OdwJxq3SMBw',NULL,NULL,NULL,NULL,1429606227),
 (32,3,165,NULL,'{\"2\":-1}',NULL,'nNSpJccU3OdwJxq3SMBw',NULL,NULL,NULL,NULL,1430802217),
 (38,4,165,NULL,'{\"6\":1}',NULL,'nNSpJccU3OdwJxq3SMBw',NULL,NULL,NULL,NULL,1431326408),
 (37,4,165,NULL,'{\"6\":1}',NULL,NULL,6,NULL,NULL,NULL,1431326316);
/*!40000 ALTER TABLE `ballots` ENABLE KEYS */;


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
) ENGINE=MyISAM AUTO_INCREMENT=4 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `calendar`
--

/*!40000 ALTER TABLE `calendar` DISABLE KEYS */;
INSERT INTO `calendar` (`id`,`timestamp`,`year`,`month`,`day`,`time`,`timestamp_added`,`added_by_user`,`location`,`title`,`content`) VALUES 
 (1,1425513599,2015,3,5,'Hela dagen',1425586448,4,'Internet','Programmering','Bara programmering, inget skoj.'),
 (2,1425599999,2015,3,6,'Hela dagen',1425586448,4,'Internet','Programmering','Bara programmering, inget skoj.'),
 (3,1425686399,2015,3,7,'Hela dagen',1425586448,4,'Internet','Programmering','Bara programmering, inget skoj.');
/*!40000 ALTER TABLE `calendar` ENABLE KEYS */;


--
-- Definition of table `calendar_participants`
--

DROP TABLE IF EXISTS `calendar_participants`;
CREATE TABLE `calendar_participants` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `calendar_id` int(10) unsigned NOT NULL default '0',
  `user_id` int(10) unsigned NOT NULL default '0',
  `timestamp_registration` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `calendar_participants`
--

/*!40000 ALTER TABLE `calendar_participants` DISABLE KEYS */;
/*!40000 ALTER TABLE `calendar_participants` ENABLE KEYS */;


--
-- Definition of table `categories`
--

DROP TABLE IF EXISTS `categories`;
CREATE TABLE `categories` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `title` varchar(45) NOT NULL default '',
  `description` text NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=10 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `categories`
--

/*!40000 ALTER TABLE `categories` DISABLE KEYS */;
INSERT INTO `categories` (`id`,`title`,`description`) VALUES 
 (4,'Testkategorin','Bara ett test. '),
 (5,'Andra testkategorin','Ännu ett test. '),
 (8,'Interna arbetsgruppsforum','Dessa forum har bara medlemmarna i den respektive arbetsgrupperna tillg†ng till.'),
 (9,'Arbetsgrupper','Publika forum f”r de olika arbetsgrupperna.');
/*!40000 ALTER TABLE `categories` ENABLE KEYS */;


--
-- Definition of table `constituencies`
--

DROP TABLE IF EXISTS `constituencies`;
CREATE TABLE `constituencies` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `title` varchar(90) NOT NULL default '',
  `description` text NOT NULL,
  `number_of_voters` int(10) unsigned default NULL,
  `forum_id` int(10) unsigned NOT NULL default '0',
  `access_type` varchar(12) NOT NULL default 'public',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=313 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `constituencies`
--

/*!40000 ALTER TABLE `constituencies` DISABLE KEYS */;
INSERT INTO `constituencies` (`id`,`title`,`description`,`number_of_voters`,`forum_id`,`access_type`) VALUES 
 (1,'Ale','',0,11,'local_county'),
 (2,'Alingsås','',0,12,'local_county'),
 (3,'Alvesta','',0,13,'local_county'),
 (4,'Aneby','',0,14,'local_county'),
 (5,'Arboga','',0,15,'local_county'),
 (6,'Arjeplog','',0,16,'local_county'),
 (7,'Arvidsjaur','',0,17,'local_county'),
 (8,'Arvika','',0,18,'local_county'),
 (9,'Askersund','',0,19,'local_county'),
 (10,'Avesta','',0,20,'local_county'),
 (11,'Bengtsfors','',0,21,'local_county'),
 (12,'Berg','',0,22,'local_county'),
 (13,'Bjurholm','',0,23,'local_county'),
 (14,'Bjuv','',0,24,'local_county'),
 (15,'Boden','',0,25,'local_county'),
 (16,'Bollebygd','',0,26,'local_county'),
 (17,'Bollnäs','',0,27,'local_county'),
 (18,'Borgholm','',0,28,'local_county'),
 (19,'Borlänge','',0,29,'local_county'),
 (20,'Borås','',0,30,'local_county'),
 (21,'Botkyrka','',0,31,'local_county'),
 (22,'Boxholm','',0,32,'local_county'),
 (23,'Bromölla','',0,33,'local_county'),
 (24,'Bräcke','',0,34,'local_county'),
 (25,'Burlöv','',0,35,'local_county'),
 (26,'Båstad','',0,36,'local_county'),
 (27,'Dals-Ed','',0,37,'local_county'),
 (28,'Danderyd','',0,38,'local_county'),
 (29,'Degerfors','',0,39,'local_county'),
 (30,'Dorotea','',0,40,'local_county'),
 (31,'Eda','',0,41,'local_county'),
 (32,'Ekerö','',0,42,'local_county'),
 (33,'Eksjö','',0,43,'local_county'),
 (34,'Emmaboda','',0,44,'local_county'),
 (35,'Enköping','',0,45,'local_county'),
 (36,'Eskilstuna','',0,46,'local_county'),
 (37,'Eslöv','',0,47,'local_county'),
 (38,'Essunga','',0,48,'local_county'),
 (39,'Fagersta','',0,49,'local_county'),
 (40,'Falkenberg','',0,50,'local_county'),
 (41,'Falköping','',0,51,'local_county'),
 (42,'Falu','',0,52,'local_county'),
 (43,'Filipstad','',0,53,'local_county'),
 (44,'Finspång','',0,54,'local_county'),
 (45,'Flen','',0,55,'local_county'),
 (46,'Forshaga','',0,56,'local_county'),
 (47,'Färgelanda','',0,57,'local_county'),
 (48,'Gagnef','',0,58,'local_county'),
 (49,'Gislaved','',0,59,'local_county'),
 (50,'Gnesta','',0,60,'local_county'),
 (51,'Gnosjö','',0,61,'local_county'),
 (52,'Gotland','',0,62,'local_county'),
 (53,'Grums','',0,63,'local_county'),
 (54,'Grästorp','',0,64,'local_county'),
 (55,'Gullspång','',0,65,'local_county'),
 (56,'Gällivare','',0,66,'local_county'),
 (57,'Gävle','',0,67,'local_county'),
 (58,'Göteborg','',0,68,'local_county'),
 (59,'Götene','',0,69,'local_county'),
 (60,'Habo','',0,70,'local_county'),
 (61,'Hagfors','',0,71,'local_county'),
 (62,'Hallsberg','',0,72,'local_county'),
 (63,'Hallstahammar','',0,73,'local_county'),
 (64,'Halmstad','',0,74,'local_county'),
 (65,'Hammarö','',0,75,'local_county'),
 (66,'Haninge','',0,76,'local_county'),
 (67,'Haparanda','',0,77,'local_county'),
 (68,'Heby','',0,78,'local_county'),
 (69,'Hedemora','',0,79,'local_county'),
 (70,'Helsingborg','',0,80,'local_county'),
 (71,'Herrljunga','',0,81,'local_county'),
 (72,'Hjo','',0,82,'local_county'),
 (73,'Hofors','',0,83,'local_county'),
 (74,'Huddinge','',0,84,'local_county'),
 (75,'Hudiksvall','',0,85,'local_county'),
 (76,'Hultsfred','',0,86,'local_county'),
 (77,'Hylte','',0,87,'local_county'),
 (78,'Håbo','',0,88,'local_county'),
 (79,'Hällefors','',0,89,'local_county'),
 (80,'Härjedalen','',0,90,'local_county'),
 (81,'Härnösand','',0,91,'local_county'),
 (82,'Härryda','',0,92,'local_county'),
 (83,'Hässleholm','',0,93,'local_county'),
 (84,'Höganäs','',0,94,'local_county'),
 (85,'Högsby','',0,95,'local_county'),
 (86,'Hörby','',0,96,'local_county'),
 (87,'Höör','',0,97,'local_county'),
 (88,'Jokkmokk','',0,98,'local_county'),
 (89,'Järfälla','',0,99,'local_county'),
 (90,'Jönköping','',0,100,'local_county'),
 (91,'Kalix','',0,101,'local_county'),
 (92,'Kalmar','',0,102,'local_county'),
 (93,'Karlsborg','',0,103,'local_county'),
 (94,'Karlshamn','',0,104,'local_county'),
 (95,'Karlskoga','',0,105,'local_county'),
 (96,'Karlskrona','',0,106,'local_county'),
 (97,'Karlstad','',0,107,'local_county'),
 (98,'Katrineholm','',0,108,'local_county'),
 (99,'Kil','',0,109,'local_county'),
 (100,'Kinda','',0,110,'local_county'),
 (101,'Kiruna','',0,111,'local_county'),
 (102,'Klippan','',0,112,'local_county'),
 (103,'Knivsta','',0,113,'local_county'),
 (104,'Kramfors','',0,114,'local_county'),
 (105,'Kristianstad','',0,115,'local_county'),
 (106,'Kristinehamn','',0,116,'local_county'),
 (107,'Krokom','',0,117,'local_county'),
 (108,'Kumla','',0,118,'local_county'),
 (109,'Kungsbacka','',0,119,'local_county'),
 (110,'Kungsör','',0,120,'local_county'),
 (111,'Kungälv','',0,121,'local_county'),
 (112,'Kävlinge','',0,122,'local_county'),
 (113,'Köping','',0,123,'local_county'),
 (114,'Laholm','',0,124,'local_county'),
 (115,'Landskrona','',0,125,'local_county'),
 (116,'Laxå','',0,126,'local_county'),
 (117,'Lekeberg','',0,127,'local_county'),
 (118,'Leksand','',0,128,'local_county'),
 (119,'Lerum','',0,129,'local_county'),
 (120,'Lessebo','',0,130,'local_county'),
 (121,'Lidingö','',0,131,'local_county'),
 (122,'Lidköping','',0,132,'local_county'),
 (123,'Lilla Edet','',0,133,'local_county'),
 (124,'Lindesberg','',0,134,'local_county'),
 (125,'Linköping','',0,135,'local_county'),
 (126,'Ljungby','',0,136,'local_county'),
 (127,'Ljusdal','',0,137,'local_county'),
 (128,'Ljusnarsberg','',0,138,'local_county'),
 (129,'Lomma','',0,139,'local_county'),
 (130,'Ludvika','',0,140,'local_county'),
 (131,'Luleå','',0,141,'local_county'),
 (132,'Lund','',0,142,'local_county'),
 (133,'Lycksele','',0,143,'local_county'),
 (134,'Lysekil','',0,144,'local_county'),
 (135,'Malmö','',0,145,'local_county'),
 (136,'Malung-Sälen','',0,146,'local_county'),
 (137,'Malå','',0,147,'local_county'),
 (138,'Mariestad','',0,148,'local_county'),
 (139,'Mark','',0,149,'local_county'),
 (140,'Markaryd','',0,150,'local_county'),
 (141,'Mellerud','',0,151,'local_county'),
 (142,'Mjölby','',0,152,'local_county'),
 (143,'Mora','',0,153,'local_county'),
 (144,'Motala','',0,154,'local_county'),
 (145,'Mullsjö','',0,155,'local_county'),
 (146,'Munkedal','',0,156,'local_county'),
 (147,'Munkfors','',0,157,'local_county'),
 (148,'Mölndal','',0,158,'local_county'),
 (149,'Mönsterås','',0,159,'local_county'),
 (150,'Mörbylånga','',0,160,'local_county'),
 (151,'Nacka','',0,161,'local_county'),
 (152,'Nora','',0,162,'local_county'),
 (153,'Norberg','',0,163,'local_county'),
 (154,'Nordanstig','',0,164,'local_county'),
 (155,'Nordmaling','',0,165,'local_county'),
 (156,'Norrköping','',0,166,'local_county'),
 (157,'Norrtälje','',0,167,'local_county'),
 (158,'Norsjö','',0,168,'local_county'),
 (159,'Nybro','',0,169,'local_county'),
 (160,'Nykvarn','',0,170,'local_county'),
 (161,'Nyköping','',0,171,'local_county'),
 (162,'Nynäshamn','',0,172,'local_county'),
 (163,'Nässjö','',0,173,'local_county'),
 (164,'Ockelbo','',0,174,'local_county'),
 (165,'Olofström','',4,175,'local_county'),
 (166,'Orsa','',0,176,'local_county'),
 (167,'Orust','',0,177,'local_county'),
 (168,'Osby','',0,178,'local_county'),
 (169,'Oskarshamn','',0,179,'local_county'),
 (170,'Ovanåker','',0,180,'local_county'),
 (171,'Oxelösund','',0,181,'local_county'),
 (172,'Pajala','',0,182,'local_county'),
 (173,'Partille','',0,183,'local_county'),
 (174,'Perstorp','',0,184,'local_county'),
 (175,'Piteå','',0,185,'local_county'),
 (176,'Ragunda','',0,186,'local_county'),
 (177,'Robertsfors','',0,187,'local_county'),
 (178,'Ronneby','',0,188,'local_county'),
 (179,'Rättvik','',0,189,'local_county'),
 (180,'Sala','',0,190,'local_county'),
 (181,'Salem','',0,191,'local_county'),
 (182,'Sandviken','',0,192,'local_county'),
 (183,'Sigtuna','',0,193,'local_county'),
 (184,'Simrishamn','',0,194,'local_county'),
 (185,'Sjöbo','',0,195,'local_county'),
 (186,'Skara','',0,196,'local_county'),
 (187,'Skellefteå','',0,197,'local_county'),
 (188,'Skinnskatteberg','',0,198,'local_county'),
 (189,'Skurup','',0,199,'local_county'),
 (190,'Skövde','',0,200,'local_county'),
 (191,'Smedjebacken','',0,201,'local_county'),
 (192,'Sollefteå','',0,202,'local_county'),
 (193,'Sollentuna','',0,203,'local_county'),
 (194,'Solna','',0,204,'local_county'),
 (195,'Sorsele','',0,205,'local_county'),
 (196,'Sotenäs','',0,206,'local_county'),
 (197,'Staffanstorp','',0,207,'local_county'),
 (198,'Stenungsund','',0,208,'local_county'),
 (199,'Stockholm','',0,209,'local_county'),
 (200,'Storfors','',0,210,'local_county'),
 (201,'Storuman','',0,211,'local_county'),
 (202,'Strängnäs','',0,212,'local_county'),
 (203,'Strömstad','',0,213,'local_county'),
 (204,'Strömsund','',0,214,'local_county'),
 (205,'Sundbyberg','',0,215,'local_county'),
 (206,'Sundsvall','',0,216,'local_county'),
 (207,'Sunne','',0,217,'local_county'),
 (208,'Surahammar','',0,218,'local_county'),
 (209,'Svalöv','',0,219,'local_county'),
 (210,'Svedala','',0,220,'local_county'),
 (211,'Svenljunga','',0,221,'local_county'),
 (212,'Säffle','',0,222,'local_county'),
 (213,'Säter','',0,223,'local_county'),
 (214,'Sävsjö','',0,224,'local_county'),
 (215,'Söderhamn','',0,225,'local_county'),
 (216,'Söderköping','',0,226,'local_county'),
 (217,'Södertälje','',0,227,'local_county'),
 (218,'Sölvesborg','',0,228,'local_county'),
 (219,'Tanum','',0,229,'local_county'),
 (220,'Tibro','',0,230,'local_county'),
 (221,'Tidaholm','',0,231,'local_county'),
 (222,'Tierp','',0,232,'local_county'),
 (223,'Timrå','',0,233,'local_county'),
 (224,'Tingsryd','',0,234,'local_county'),
 (225,'Tjörn','',0,235,'local_county'),
 (226,'Tomelilla','',0,236,'local_county'),
 (227,'Torsby','',0,237,'local_county'),
 (228,'Torsås','',0,238,'local_county'),
 (229,'Tranemo','',0,239,'local_county'),
 (230,'Tranås','',0,240,'local_county'),
 (231,'Trelleborg','',0,241,'local_county'),
 (232,'Trollhättan','',0,242,'local_county'),
 (233,'Trosa','',0,243,'local_county'),
 (234,'Tyresö','',0,244,'local_county'),
 (235,'Täby','',0,245,'local_county'),
 (236,'Töreboda','',0,246,'local_county'),
 (237,'Uddevalla','',0,247,'local_county'),
 (238,'Ulricehamn','',0,248,'local_county'),
 (239,'Umeå','',0,249,'local_county'),
 (240,'Upplands Väsby','',0,250,'local_county'),
 (241,'Upplands-Bro','',0,251,'local_county'),
 (242,'Uppsala','',0,252,'local_county'),
 (243,'Uppvidinge','',0,253,'local_county'),
 (244,'Vadstena','',0,254,'local_county'),
 (245,'Vaggeryd','',0,255,'local_county'),
 (246,'Valdemarsvik','',0,256,'local_county'),
 (247,'Vallentuna','',0,257,'local_county'),
 (248,'Vansbro','',0,258,'local_county'),
 (249,'Vara','',0,259,'local_county'),
 (250,'Varberg','',0,260,'local_county'),
 (251,'Vaxholm','',0,261,'local_county'),
 (252,'Vellinge','',0,262,'local_county'),
 (253,'Vetlanda','',0,263,'local_county'),
 (254,'Vilhelmina','',0,264,'local_county'),
 (255,'Vimmerby','',0,265,'local_county'),
 (256,'Vindeln','',0,266,'local_county'),
 (257,'Vingåker','',0,267,'local_county'),
 (258,'Vårgårda','',0,268,'local_county'),
 (259,'Vänersborg','',0,269,'local_county'),
 (260,'Vännäs','',0,270,'local_county'),
 (261,'Värmdö','',0,271,'local_county'),
 (262,'Värnamo','',0,272,'local_county'),
 (263,'Västervik','',0,273,'local_county'),
 (264,'Västerå','',0,274,'local_county'),
 (265,'Växjö','',0,275,'local_county'),
 (266,'Ydre','',0,276,'local_county'),
 (267,'Ystad','',0,277,'local_county'),
 (268,'Åmål','',0,278,'local_county'),
 (269,'Ånge','',0,279,'local_county'),
 (270,'Åre','',0,280,'local_county'),
 (271,'Årjäng','',0,281,'local_county'),
 (272,'Åsele','',0,282,'local_county'),
 (273,'Åstorp','',0,283,'local_county'),
 (274,'Åtvidaberg','',0,284,'local_county'),
 (275,'Älmhult','',0,285,'local_county'),
 (276,'Älvdalen','',0,286,'local_county'),
 (277,'Älvkarleby','',0,287,'local_county'),
 (278,'Älvsbyn','',0,288,'local_county'),
 (279,'Ängelholm','',0,289,'local_county'),
 (280,'Öckerö','',0,290,'local_county'),
 (281,'Ödeshög','',0,291,'local_county'),
 (282,'Örebro','',0,292,'local_county'),
 (283,'Örkelljunga','',0,293,'local_county'),
 (284,'Örnsköldsvik','',0,294,'local_county'),
 (285,'Östersund','',0,295,'local_county'),
 (286,'Österåker','',0,296,'local_county'),
 (287,'Östhammar','',0,297,'local_county'),
 (288,'Östra Göinge','',0,298,'local_county'),
 (289,'Överkalix','',0,299,'local_county'),
 (290,'Övertorneå','',0,300,'local_county'),
 (291,'Blekinge\r\n','',4,301,'local_region'),
 (292,'Dalarna\r\n','',0,302,'local_region'),
 (293,'Gotland\r\n','',0,303,'local_region'),
 (294,'Gävleborg\r\n','',0,304,'local_region'),
 (295,'Halland\r\n','',0,305,'local_region'),
 (296,'Jämtland\r\n','',0,306,'local_region'),
 (297,'Jönköping\r\n','',0,307,'local_region'),
 (298,'Kalmar\r\n','',0,308,'local_region'),
 (299,'Kronoberg\r\n','',0,309,'local_region'),
 (300,'Norrbotten\r\n','',0,310,'local_region'),
 (301,'Norrbotten','',0,311,'local_region'),
 (302,'Skåne\r\n','',0,312,'local_region'),
 (303,'Stockholm\r\n','',0,313,'local_region'),
 (304,'Södermanland\r\n','',0,314,'local_region'),
 (305,'Uppsala\r\n','',0,315,'local_region'),
 (306,'Värmland\r\n','',0,316,'local_region'),
 (307,'Västerbotten\r\n','',0,317,'local_region'),
 (308,'Västernorrland\r\n','',0,318,'local_region'),
 (309,'Västmanland\r\n','',0,319,'local_region'),
 (310,'Västra Götaland\r\n','',0,320,'local_region'),
 (311,'Örebro\r\n','',0,321,'local_region'),
 (312,'Östergötland\r\n','',0,322,'local_region');
/*!40000 ALTER TABLE `constituencies` ENABLE KEYS */;


--
-- Definition of table `constituencies_delegates`
--

DROP TABLE IF EXISTS `constituencies_delegates`;
CREATE TABLE `constituencies_delegates` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `delegate_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=8 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `constituencies_delegates`
--

/*!40000 ALTER TABLE `constituencies_delegates` DISABLE KEYS */;
INSERT INTO `constituencies_delegates` (`id`,`constituency_id`,`delegate_id`) VALUES 
 (7,291,6),
 (6,165,6);
/*!40000 ALTER TABLE `constituencies_delegates` ENABLE KEYS */;


--
-- Definition of table `constituencies_users`
--

DROP TABLE IF EXISTS `constituencies_users`;
CREATE TABLE `constituencies_users` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `user_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=13 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `constituencies_users`
--

/*!40000 ALTER TABLE `constituencies_users` DISABLE KEYS */;
INSERT INTO `constituencies_users` (`id`,`constituency_id`,`user_id`) VALUES 
 (12,291,13),
 (2,165,4),
 (3,165,5),
 (4,165,6),
 (5,291,6),
 (6,291,5),
 (7,291,4),
 (11,165,13);
/*!40000 ALTER TABLE `constituencies_users` ENABLE KEYS */;


--
-- Definition of table `delegate_ballots`
--

DROP TABLE IF EXISTS `delegate_ballots`;
CREATE TABLE `delegate_ballots` (
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
-- Dumping data for table `delegate_ballots`
--

/*!40000 ALTER TABLE `delegate_ballots` DISABLE KEYS */;
INSERT INTO `delegate_ballots` (`id`,`vote_id`,`constituency_id`,`ballot_alternative`,`vote_alternative_id`,`priority`,`median_vote_value`,`ballot_owner_id`,`delegate_id`,`delegation_level`,`delegate_priority`,`time_ballot_placed`) VALUES 
 (1,1,165,'yes',NULL,NULL,NULL,0,6,NULL,NULL,1429188717);
/*!40000 ALTER TABLE `delegate_ballots` ENABLE KEYS */;


--
-- Definition of table `delegates`
--

DROP TABLE IF EXISTS `delegates`;
CREATE TABLE `delegates` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `title` varchar(90) NOT NULL default '',
  `description` text NOT NULL,
  `timestamp_created` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `delegates`
--

/*!40000 ALTER TABLE `delegates` DISABLE KEYS */;
INSERT INTO `delegates` (`id`,`title`,`description`,`timestamp_created`) VALUES 
 (6,'Suddis Katt','',0);
/*!40000 ALTER TABLE `delegates` ENABLE KEYS */;


--
-- Definition of table `delegates_delegates`
--

DROP TABLE IF EXISTS `delegates_delegates`;
CREATE TABLE `delegates_delegates` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `delegate_id` int(10) unsigned NOT NULL default '0',
  `delegand_id` int(10) unsigned NOT NULL default '0',
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `priority` int(10) unsigned NOT NULL default '1',
  `time_delegate_chosen` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `delegates_delegates`
--

/*!40000 ALTER TABLE `delegates_delegates` DISABLE KEYS */;
/*!40000 ALTER TABLE `delegates_delegates` ENABLE KEYS */;


--
-- Definition of table `delegates_users`
--

DROP TABLE IF EXISTS `delegates_users`;
CREATE TABLE `delegates_users` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `delegate_id` int(10) unsigned NOT NULL default '0',
  `user_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `delegates_users`
--

/*!40000 ALTER TABLE `delegates_users` DISABLE KEYS */;
INSERT INTO `delegates_users` (`id`,`delegate_id`,`user_id`) VALUES 
 (1,6,6);
/*!40000 ALTER TABLE `delegates_users` ENABLE KEYS */;


--
-- Definition of table `forums`
--

DROP TABLE IF EXISTS `forums`;
CREATE TABLE `forums` (
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
) ENGINE=MyISAM AUTO_INCREMENT=323 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `forums`
--

/*!40000 ALTER TABLE `forums` DISABLE KEYS */;
INSERT INTO `forums` (`id`,`category_id`,`title`,`description`,`last_posted_time`,`last_posted_post`,`number_of_topics`,`number_of_posts`,`access_type`) VALUES 
 (1,4,'Testforumet','Forum för att testa saker. ',1432645649,50,7,8,'public'),
 (2,9,'Testgruppen','Publikt forum för arbetsgruppen Testgruppen.',NULL,NULL,0,0,'public'),
 (3,9,'Testgruppen','Publikt forum för arbetsgruppen Testgruppen.',NULL,NULL,0,0,'public'),
 (4,9,'Testgruppen','Publikt forum för arbetsgruppen Testgruppen.',NULL,NULL,0,0,'public'),
 (5,8,'Testgruppen','Privat forum för arbetsgruppen Testgruppen.',NULL,NULL,0,0,'workgroup'),
 (12,2,'Alingsås','',NULL,NULL,0,0,'local_county'),
 (11,2,'Ale','',NULL,NULL,0,0,'local_county'),
 (13,2,'Alvesta','',NULL,NULL,0,0,'local_county'),
 (14,2,'Aneby','',NULL,NULL,0,0,'local_county'),
 (15,2,'Arboga','',NULL,NULL,0,0,'local_county'),
 (16,2,'Arjeplog','',NULL,NULL,0,0,'local_county'),
 (17,2,'Arvidsjaur','',NULL,NULL,0,0,'local_county'),
 (18,2,'Arvika','',NULL,NULL,0,0,'local_county'),
 (19,2,'Askersund','',NULL,NULL,0,0,'local_county'),
 (20,2,'Avesta','',NULL,NULL,0,0,'local_county'),
 (21,2,'Bengtsfors','',NULL,NULL,0,0,'local_county'),
 (22,2,'Berg','',NULL,NULL,0,0,'local_county'),
 (23,2,'Bjurholm','',NULL,NULL,0,0,'local_county'),
 (24,2,'Bjuv','',NULL,NULL,0,0,'local_county'),
 (25,2,'Boden','',NULL,NULL,0,0,'local_county'),
 (26,2,'Bollebygd','',NULL,NULL,0,0,'local_county'),
 (27,2,'Bollnäs','',NULL,NULL,0,0,'local_county'),
 (28,2,'Borgholm','',NULL,NULL,0,0,'local_county'),
 (29,2,'Borlänge','',NULL,NULL,0,0,'local_county'),
 (30,2,'Borås','',NULL,NULL,0,0,'local_county'),
 (31,2,'Botkyrka','',NULL,NULL,0,0,'local_county'),
 (32,2,'Boxholm','',NULL,NULL,0,0,'local_county'),
 (33,2,'Bromölla','',NULL,NULL,0,0,'local_county'),
 (34,2,'Bräcke','',NULL,NULL,0,0,'local_county'),
 (35,2,'Burlöv','',NULL,NULL,0,0,'local_county'),
 (36,2,'Båstad','',NULL,NULL,0,0,'local_county'),
 (37,2,'Dals-Ed','',NULL,NULL,0,0,'local_county'),
 (38,2,'Danderyd','',NULL,NULL,0,0,'local_county'),
 (39,2,'Degerfors','',NULL,NULL,0,0,'local_county'),
 (40,2,'Dorotea','',NULL,NULL,0,0,'local_county'),
 (41,2,'Eda','',NULL,NULL,0,0,'local_county'),
 (42,2,'Ekerö','',NULL,NULL,0,0,'local_county'),
 (43,2,'Eksjö','',NULL,NULL,0,0,'local_county'),
 (44,2,'Emmaboda','',NULL,NULL,0,0,'local_county'),
 (45,2,'Enköping','',NULL,NULL,0,0,'local_county'),
 (46,2,'Eskilstuna','',NULL,NULL,0,0,'local_county'),
 (47,2,'Eslöv','',NULL,NULL,0,0,'local_county'),
 (48,2,'Essunga','',NULL,NULL,0,0,'local_county'),
 (49,2,'Fagersta','',NULL,NULL,0,0,'local_county'),
 (50,2,'Falkenberg','',NULL,NULL,0,0,'local_county'),
 (51,2,'Falköping','',NULL,NULL,0,0,'local_county'),
 (52,2,'Falu','',NULL,NULL,0,0,'local_county'),
 (53,2,'Filipstad','',NULL,NULL,0,0,'local_county'),
 (54,2,'Finspång','',NULL,NULL,0,0,'local_county'),
 (55,2,'Flen','',NULL,NULL,0,0,'local_county'),
 (56,2,'Forshaga','',NULL,NULL,0,0,'local_county'),
 (57,2,'Färgelanda','',NULL,NULL,0,0,'local_county'),
 (58,2,'Gagnef','',NULL,NULL,0,0,'local_county'),
 (59,2,'Gislaved','',NULL,NULL,0,0,'local_county'),
 (60,2,'Gnesta','',NULL,NULL,0,0,'local_county'),
 (61,2,'Gnosjö','',NULL,NULL,0,0,'local_county'),
 (62,2,'Gotland','',NULL,NULL,0,0,'local_county'),
 (63,2,'Grums','',NULL,NULL,0,0,'local_county'),
 (64,2,'Grästorp','',NULL,NULL,0,0,'local_county'),
 (65,2,'Gullspång','',NULL,NULL,0,0,'local_county'),
 (66,2,'Gällivare','',NULL,NULL,0,0,'local_county'),
 (67,2,'Gävle','',NULL,NULL,0,0,'local_county'),
 (68,2,'Göteborg','',NULL,NULL,0,0,'local_county'),
 (69,2,'Götene','',NULL,NULL,0,0,'local_county'),
 (70,2,'Habo','',NULL,NULL,0,0,'local_county'),
 (71,2,'Hagfors','',NULL,NULL,0,0,'local_county'),
 (72,2,'Hallsberg','',NULL,NULL,0,0,'local_county'),
 (73,2,'Hallstahammar','',NULL,NULL,0,0,'local_county'),
 (74,2,'Halmstad','',NULL,NULL,0,0,'local_county'),
 (75,2,'Hammarö','',NULL,NULL,0,0,'local_county'),
 (76,2,'Haninge','',NULL,NULL,0,0,'local_county'),
 (77,2,'Haparanda','',NULL,NULL,0,0,'local_county'),
 (78,2,'Heby','',NULL,NULL,0,0,'local_county'),
 (79,2,'Hedemora','',NULL,NULL,0,0,'local_county'),
 (80,2,'Helsingborg','',NULL,NULL,0,0,'local_county'),
 (81,2,'Herrljunga','',NULL,NULL,0,0,'local_county'),
 (82,2,'Hjo','',NULL,NULL,0,0,'local_county'),
 (83,2,'Hofors','',NULL,NULL,0,0,'local_county'),
 (84,2,'Huddinge','',NULL,NULL,0,0,'local_county'),
 (85,2,'Hudiksvall','',NULL,NULL,0,0,'local_county'),
 (86,2,'Hultsfred','',NULL,NULL,0,0,'local_county'),
 (87,2,'Hylte','',NULL,NULL,0,0,'local_county'),
 (88,2,'Håbo','',NULL,NULL,0,0,'local_county'),
 (89,2,'Hällefors','',NULL,NULL,0,0,'local_county'),
 (90,2,'Härjedalen','',NULL,NULL,0,0,'local_county'),
 (91,2,'Härnösand','',NULL,NULL,0,0,'local_county'),
 (92,2,'Härryda','',NULL,NULL,0,0,'local_county'),
 (93,2,'Hässleholm','',NULL,NULL,0,0,'local_county'),
 (94,2,'Höganäs','',NULL,NULL,0,0,'local_county'),
 (95,2,'Högsby','',NULL,NULL,0,0,'local_county'),
 (96,2,'Hörby','',NULL,NULL,0,0,'local_county'),
 (97,2,'Höör','',NULL,NULL,0,0,'local_county'),
 (98,2,'Jokkmokk','',NULL,NULL,0,0,'local_county'),
 (99,2,'Järfälla','',NULL,NULL,0,0,'local_county'),
 (100,2,'Jönköping','',NULL,NULL,0,0,'local_county'),
 (101,2,'Kalix','',NULL,NULL,0,0,'local_county'),
 (102,2,'Kalmar','',NULL,NULL,0,0,'local_county'),
 (103,2,'Karlsborg','',NULL,NULL,0,0,'local_county'),
 (104,2,'Karlshamn','',NULL,NULL,0,0,'local_county'),
 (105,2,'Karlskoga','',NULL,NULL,0,0,'local_county'),
 (106,2,'Karlskrona','',NULL,NULL,0,0,'local_county'),
 (107,2,'Karlstad','',NULL,NULL,0,0,'local_county'),
 (108,2,'Katrineholm','',NULL,NULL,0,0,'local_county'),
 (109,2,'Kil','',NULL,NULL,0,0,'local_county'),
 (110,2,'Kinda','',NULL,NULL,0,0,'local_county'),
 (111,2,'Kiruna','',NULL,NULL,0,0,'local_county'),
 (112,2,'Klippan','',NULL,NULL,0,0,'local_county'),
 (113,2,'Knivsta','',NULL,NULL,0,0,'local_county'),
 (114,2,'Kramfors','',NULL,NULL,0,0,'local_county'),
 (115,2,'Kristianstad','',NULL,NULL,0,0,'local_county'),
 (116,2,'Kristinehamn','',NULL,NULL,0,0,'local_county'),
 (117,2,'Krokom','',NULL,NULL,0,0,'local_county'),
 (118,2,'Kumla','',NULL,NULL,0,0,'local_county'),
 (119,2,'Kungsbacka','',NULL,NULL,0,0,'local_county'),
 (120,2,'Kungsör','',NULL,NULL,0,0,'local_county'),
 (121,2,'Kungälv','',NULL,NULL,0,0,'local_county'),
 (122,2,'Kävlinge','',NULL,NULL,0,0,'local_county'),
 (123,2,'Köping','',NULL,NULL,0,0,'local_county'),
 (124,2,'Laholm','',NULL,NULL,0,0,'local_county'),
 (125,2,'Landskrona','',NULL,NULL,0,0,'local_county'),
 (126,2,'Laxå','',NULL,NULL,0,0,'local_county'),
 (127,2,'Lekeberg','',NULL,NULL,0,0,'local_county'),
 (128,2,'Leksand','',NULL,NULL,0,0,'local_county'),
 (129,2,'Lerum','',NULL,NULL,0,0,'local_county'),
 (130,2,'Lessebo','',NULL,NULL,0,0,'local_county'),
 (131,2,'Lidingö','',NULL,NULL,0,0,'local_county'),
 (132,2,'Lidköping','',NULL,NULL,0,0,'local_county'),
 (133,2,'Lilla Edet','',NULL,NULL,0,0,'local_county'),
 (134,2,'Lindesberg','',NULL,NULL,0,0,'local_county'),
 (135,2,'Linköping','',NULL,NULL,0,0,'local_county'),
 (136,2,'Ljungby','',NULL,NULL,0,0,'local_county'),
 (137,2,'Ljusdal','',NULL,NULL,0,0,'local_county'),
 (138,2,'Ljusnarsberg','',NULL,NULL,0,0,'local_county'),
 (139,2,'Lomma','',NULL,NULL,0,0,'local_county'),
 (140,2,'Ludvika','',NULL,NULL,0,0,'local_county'),
 (141,2,'Luleå','',NULL,NULL,0,0,'local_county'),
 (142,2,'Lund','',NULL,NULL,0,0,'local_county'),
 (143,2,'Lycksele','',NULL,NULL,0,0,'local_county'),
 (144,2,'Lysekil','',NULL,NULL,0,0,'local_county'),
 (145,2,'Malmö','',NULL,NULL,0,0,'local_county'),
 (146,2,'Malung-Sälen','',NULL,NULL,0,0,'local_county'),
 (147,2,'Malå','',NULL,NULL,0,0,'local_county'),
 (148,2,'Mariestad','',NULL,NULL,0,0,'local_county'),
 (149,2,'Mark','',NULL,NULL,0,0,'local_county'),
 (150,2,'Markaryd','',NULL,NULL,0,0,'local_county'),
 (151,2,'Mellerud','',NULL,NULL,0,0,'local_county'),
 (152,2,'Mjölby','',NULL,NULL,0,0,'local_county'),
 (153,2,'Mora','',NULL,NULL,0,0,'local_county'),
 (154,2,'Motala','',NULL,NULL,0,0,'local_county'),
 (155,2,'Mullsjö','',NULL,NULL,0,0,'local_county'),
 (156,2,'Munkedal','',NULL,NULL,0,0,'local_county'),
 (157,2,'Munkfors','',NULL,NULL,0,0,'local_county'),
 (158,2,'Mölndal','',NULL,NULL,0,0,'local_county'),
 (159,2,'Mönsterås','',NULL,NULL,0,0,'local_county'),
 (160,2,'Mörbylånga','',NULL,NULL,0,0,'local_county'),
 (161,2,'Nacka','',NULL,NULL,0,0,'local_county'),
 (162,2,'Nora','',NULL,NULL,0,0,'local_county'),
 (163,2,'Norberg','',NULL,NULL,0,0,'local_county'),
 (164,2,'Nordanstig','',NULL,NULL,0,0,'local_county'),
 (165,2,'Nordmaling','',NULL,NULL,0,0,'local_county'),
 (166,2,'Norrköping','',NULL,NULL,0,0,'local_county'),
 (167,2,'Norrtälje','',NULL,NULL,0,0,'local_county'),
 (168,2,'Norsjö','',NULL,NULL,0,0,'local_county'),
 (169,2,'Nybro','',NULL,NULL,0,0,'local_county'),
 (170,2,'Nykvarn','',NULL,NULL,0,0,'local_county'),
 (171,2,'Nyköping','',NULL,NULL,0,0,'local_county'),
 (172,2,'Nynäshamn','',NULL,NULL,0,0,'local_county'),
 (173,2,'Nässjö','',NULL,NULL,0,0,'local_county'),
 (174,2,'Ockelbo','',NULL,NULL,0,0,'local_county'),
 (175,2,'Olofström','',1430808242,35,5,5,'local_county'),
 (176,2,'Orsa','',NULL,NULL,0,0,'local_county'),
 (177,2,'Orust','',NULL,NULL,0,0,'local_county'),
 (178,2,'Osby','',NULL,NULL,0,0,'local_county'),
 (179,2,'Oskarshamn','',NULL,NULL,0,0,'local_county'),
 (180,2,'Ovanåker','',NULL,NULL,0,0,'local_county'),
 (181,2,'Oxelösund','',NULL,NULL,0,0,'local_county'),
 (182,2,'Pajala','',NULL,NULL,0,0,'local_county'),
 (183,2,'Partille','',NULL,NULL,0,0,'local_county'),
 (184,2,'Perstorp','',NULL,NULL,0,0,'local_county'),
 (185,2,'Piteå','',NULL,NULL,0,0,'local_county'),
 (186,2,'Ragunda','',NULL,NULL,0,0,'local_county'),
 (187,2,'Robertsfors','',NULL,NULL,0,0,'local_county'),
 (188,2,'Ronneby','',NULL,NULL,0,0,'local_county'),
 (189,2,'Rättvik','',NULL,NULL,0,0,'local_county'),
 (190,2,'Sala','',NULL,NULL,0,0,'local_county'),
 (191,2,'Salem','',NULL,NULL,0,0,'local_county'),
 (192,2,'Sandviken','',NULL,NULL,0,0,'local_county'),
 (193,2,'Sigtuna','',NULL,NULL,0,0,'local_county'),
 (194,2,'Simrishamn','',NULL,NULL,0,0,'local_county'),
 (195,2,'Sjöbo','',NULL,NULL,0,0,'local_county'),
 (196,2,'Skara','',NULL,NULL,0,0,'local_county'),
 (197,2,'Skellefteå','',NULL,NULL,0,0,'local_county'),
 (198,2,'Skinnskatteberg','',NULL,NULL,0,0,'local_county'),
 (199,2,'Skurup','',NULL,NULL,0,0,'local_county'),
 (200,2,'Skövde','',NULL,NULL,0,0,'local_county'),
 (201,2,'Smedjebacken','',NULL,NULL,0,0,'local_county'),
 (202,2,'Sollefteå','',NULL,NULL,0,0,'local_county'),
 (203,2,'Sollentuna','',NULL,NULL,0,0,'local_county'),
 (204,2,'Solna','',NULL,NULL,0,0,'local_county'),
 (205,2,'Sorsele','',NULL,NULL,0,0,'local_county'),
 (206,2,'Sotenäs','',NULL,NULL,0,0,'local_county'),
 (207,2,'Staffanstorp','',NULL,NULL,0,0,'local_county'),
 (208,2,'Stenungsund','',NULL,NULL,0,0,'local_county'),
 (209,2,'Stockholm','',NULL,NULL,0,0,'local_county'),
 (210,2,'Storfors','',NULL,NULL,0,0,'local_county'),
 (211,2,'Storuman','',NULL,NULL,0,0,'local_county'),
 (212,2,'Strängnäs','',NULL,NULL,0,0,'local_county'),
 (213,2,'Strömstad','',NULL,NULL,0,0,'local_county'),
 (214,2,'Strömsund','',NULL,NULL,0,0,'local_county'),
 (215,2,'Sundbyberg','',NULL,NULL,0,0,'local_county'),
 (216,2,'Sundsvall','',NULL,NULL,0,0,'local_county'),
 (217,2,'Sunne','',NULL,NULL,0,0,'local_county'),
 (218,2,'Surahammar','',NULL,NULL,0,0,'local_county'),
 (219,2,'Svalöv','',NULL,NULL,0,0,'local_county'),
 (220,2,'Svedala','',NULL,NULL,0,0,'local_county'),
 (221,2,'Svenljunga','',NULL,NULL,0,0,'local_county'),
 (222,2,'Säffle','',NULL,NULL,0,0,'local_county'),
 (223,2,'Säter','',NULL,NULL,0,0,'local_county'),
 (224,2,'Sävsjö','',NULL,NULL,0,0,'local_county'),
 (225,2,'Söderhamn','',NULL,NULL,0,0,'local_county'),
 (226,2,'Söderköping','',NULL,NULL,0,0,'local_county'),
 (227,2,'Södertälje','',NULL,NULL,0,0,'local_county'),
 (228,2,'Sölvesborg','',NULL,NULL,0,0,'local_county'),
 (229,2,'Tanum','',NULL,NULL,0,0,'local_county'),
 (230,2,'Tibro','',NULL,NULL,0,0,'local_county'),
 (231,2,'Tidaholm','',NULL,NULL,0,0,'local_county'),
 (232,2,'Tierp','',NULL,NULL,0,0,'local_county'),
 (233,2,'Timrå','',NULL,NULL,0,0,'local_county'),
 (234,2,'Tingsryd','',NULL,NULL,0,0,'local_county'),
 (235,2,'Tjörn','',NULL,NULL,0,0,'local_county'),
 (236,2,'Tomelilla','',NULL,NULL,0,0,'local_county'),
 (237,2,'Torsby','',NULL,NULL,0,0,'local_county'),
 (238,2,'Torsås','',NULL,NULL,0,0,'local_county'),
 (239,2,'Tranemo','',NULL,NULL,0,0,'local_county'),
 (240,2,'Tranås','',NULL,NULL,0,0,'local_county'),
 (241,2,'Trelleborg','',NULL,NULL,0,0,'local_county'),
 (242,2,'Trollhättan','',NULL,NULL,0,0,'local_county'),
 (243,2,'Trosa','',NULL,NULL,0,0,'local_county'),
 (244,2,'Tyresö','',NULL,NULL,0,0,'local_county'),
 (245,2,'Täby','',NULL,NULL,0,0,'local_county'),
 (246,2,'Töreboda','',NULL,NULL,0,0,'local_county'),
 (247,2,'Uddevalla','',NULL,NULL,0,0,'local_county'),
 (248,2,'Ulricehamn','',NULL,NULL,0,0,'local_county'),
 (249,2,'Umeå','',NULL,NULL,0,0,'local_county'),
 (250,2,'Upplands Väsby','',NULL,NULL,0,0,'local_county'),
 (251,2,'Upplands-Bro','',NULL,NULL,0,0,'local_county'),
 (252,2,'Uppsala','',NULL,NULL,0,0,'local_county'),
 (253,2,'Uppvidinge','',NULL,NULL,0,0,'local_county'),
 (254,2,'Vadstena','',NULL,NULL,0,0,'local_county'),
 (255,2,'Vaggeryd','',NULL,NULL,0,0,'local_county'),
 (256,2,'Valdemarsvik','',NULL,NULL,0,0,'local_county'),
 (257,2,'Vallentuna','',NULL,NULL,0,0,'local_county'),
 (258,2,'Vansbro','',NULL,NULL,0,0,'local_county'),
 (259,2,'Vara','',NULL,NULL,0,0,'local_county'),
 (260,2,'Varberg','',NULL,NULL,0,0,'local_county'),
 (261,2,'Vaxholm','',NULL,NULL,0,0,'local_county'),
 (262,2,'Vellinge','',NULL,NULL,0,0,'local_county'),
 (263,2,'Vetlanda','',NULL,NULL,0,0,'local_county'),
 (264,2,'Vilhelmina','',NULL,NULL,0,0,'local_county'),
 (265,2,'Vimmerby','',NULL,NULL,0,0,'local_county'),
 (266,2,'Vindeln','',NULL,NULL,0,0,'local_county'),
 (267,2,'Vingåker','',NULL,NULL,0,0,'local_county'),
 (268,2,'Vårgårda','',NULL,NULL,0,0,'local_county'),
 (269,2,'Vänersborg','',NULL,NULL,0,0,'local_county'),
 (270,2,'Vännäs','',NULL,NULL,0,0,'local_county'),
 (271,2,'Värmdö','',NULL,NULL,0,0,'local_county'),
 (272,2,'Värnamo','',NULL,NULL,0,0,'local_county'),
 (273,2,'Västervik','',NULL,NULL,0,0,'local_county'),
 (274,2,'Västerå','',NULL,NULL,0,0,'local_county'),
 (275,2,'Växjö','',NULL,NULL,0,0,'local_county'),
 (276,2,'Ydre','',NULL,NULL,0,0,'local_county'),
 (277,2,'Ystad','',NULL,NULL,0,0,'local_county'),
 (278,2,'Åmål','',NULL,NULL,0,0,'local_county'),
 (279,2,'Ånge','',NULL,NULL,0,0,'local_county'),
 (280,2,'Åre','',NULL,NULL,0,0,'local_county'),
 (281,2,'Årjäng','',NULL,NULL,0,0,'local_county'),
 (282,2,'Åsele','',NULL,NULL,0,0,'local_county'),
 (283,2,'Åstorp','',NULL,NULL,0,0,'local_county'),
 (284,2,'Åtvidaberg','',NULL,NULL,0,0,'local_county'),
 (285,2,'Älmhult','',NULL,NULL,0,0,'local_county'),
 (286,2,'Älvdalen','',NULL,NULL,0,0,'local_county'),
 (287,2,'Älvkarleby','',NULL,NULL,0,0,'local_county'),
 (288,2,'Älvsbyn','',NULL,NULL,0,0,'local_county'),
 (289,2,'Ängelholm','',NULL,NULL,0,0,'local_county'),
 (290,2,'Öckerö','',NULL,NULL,0,0,'local_county'),
 (291,2,'Ödeshög','',NULL,NULL,0,0,'local_county'),
 (292,2,'Örebro','',NULL,NULL,0,0,'local_county'),
 (293,2,'Örkelljunga','',NULL,NULL,0,0,'local_county'),
 (294,2,'Örnsköldsvik','',NULL,NULL,0,0,'local_county'),
 (295,2,'Östersund','',NULL,NULL,0,0,'local_county'),
 (296,2,'Österåker','',NULL,NULL,0,0,'local_county'),
 (297,2,'Östhammar','',NULL,NULL,0,0,'local_county'),
 (298,2,'Östra Göinge','',NULL,NULL,0,0,'local_county'),
 (299,2,'Överkalix','',NULL,NULL,0,0,'local_county'),
 (300,2,'Övertorneå','',NULL,NULL,0,0,'local_county'),
 (301,2,'Blekinge\r\n','',1431861479,37,2,2,'local_region'),
 (302,2,'Dalarna\r\n','',NULL,NULL,0,0,'local_region'),
 (303,2,'Gotland\r\n','',NULL,NULL,0,0,'local_region'),
 (304,2,'Gävleborg\r\n','',NULL,NULL,0,0,'local_region'),
 (305,2,'Halland\r\n','',NULL,NULL,0,0,'local_region'),
 (306,2,'Jämtland\r\n','',NULL,NULL,0,0,'local_region'),
 (307,2,'Jönköping\r\n','',NULL,NULL,0,0,'local_region'),
 (308,2,'Kalmar\r\n','',NULL,NULL,0,0,'local_region'),
 (309,2,'Kronoberg\r\n','',NULL,NULL,0,0,'local_region'),
 (310,2,'Norrbotten\r\n','',NULL,NULL,0,0,'local_region'),
 (311,2,'Norrbotten','',NULL,NULL,0,0,'local_region'),
 (312,2,'Skåne\r\n','',NULL,NULL,0,0,'local_region'),
 (313,2,'Stockholm\r\n','',NULL,NULL,0,0,'local_region'),
 (314,2,'Södermanland\r\n','',NULL,NULL,0,0,'local_region'),
 (315,2,'Uppsala\r\n','',NULL,NULL,0,0,'local_region'),
 (316,2,'Värmland\r\n','',NULL,NULL,0,0,'local_region'),
 (317,2,'Västerbotten\r\n','',NULL,NULL,0,0,'local_region'),
 (318,2,'Västernorrland\r\n','',NULL,NULL,0,0,'local_region'),
 (319,2,'Västmanland\r\n','',NULL,NULL,0,0,'local_region'),
 (320,2,'Västra Götaland\r\n','',NULL,NULL,0,0,'local_region'),
 (321,2,'Örebro\r\n','',NULL,NULL,0,0,'local_region'),
 (322,2,'Östergötland\r\n','',NULL,NULL,0,0,'local_region');
/*!40000 ALTER TABLE `forums` ENABLE KEYS */;


--
-- Definition of table `forums_users`
--

DROP TABLE IF EXISTS `forums_users`;
CREATE TABLE `forums_users` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `user_id` int(10) unsigned NOT NULL default '0',
  `forum_id` int(10) unsigned NOT NULL default '0',
  `access_type` tinyint(3) unsigned NOT NULL default '1',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=45 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `forums_users`
--

/*!40000 ALTER TABLE `forums_users` DISABLE KEYS */;
INSERT INTO `forums_users` (`id`,`user_id`,`forum_id`,`access_type`) VALUES 
 (44,13,301,1),
 (2,4,1,1),
 (3,5,1,1),
 (4,6,1,1),
 (5,5,0,1),
 (43,13,175,1),
 (7,4,4,1),
 (8,5,4,1),
 (9,6,4,1),
 (42,13,4,1),
 (11,4,5,1),
 (41,13,3,1),
 (14,4,175,1),
 (15,5,175,1),
 (16,6,175,1),
 (17,6,301,1),
 (18,5,301,1),
 (19,4,301,1),
 (40,13,2,1),
 (39,13,1,1);
/*!40000 ALTER TABLE `forums_users` ENABLE KEYS */;


--
-- Definition of table `kommuner`
--

DROP TABLE IF EXISTS `kommuner`;
CREATE TABLE `kommuner` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `kommun` varchar(45) NOT NULL default '',
  `lan` varchar(45) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=291 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `kommuner`
--

/*!40000 ALTER TABLE `kommuner` DISABLE KEYS */;
INSERT INTO `kommuner` (`id`,`kommun`,`lan`) VALUES 
 (1,'Ale','Västra Götaland\r\n'),
 (2,'Alingsås','Västra Götaland\r\n'),
 (3,'Alvesta','Kronoberg\r\n'),
 (4,'Aneby','Jönköping\r\n'),
 (5,'Arboga','Västmanland\r\n'),
 (6,'Arjeplog','Norrbotten\r\n'),
 (7,'Arvidsjaur','Norrbotten\r\n'),
 (8,'Arvika','Värmland\r\n'),
 (9,'Askersund','Örebro\r\n'),
 (10,'Avesta','Dalarna\r\n'),
 (11,'Bengtsfors','Västra Götaland\r\n'),
 (12,'Berg','Jämtland\r\n'),
 (13,'Bjurholm','Västerbotten\r\n'),
 (14,'Bjuv','Skåne\r\n'),
 (15,'Boden','Norrbotten\r\n'),
 (16,'Bollebygd','Västra Götaland\r\n'),
 (17,'Bollnäs','Gävleborg\r\n'),
 (18,'Borgholm','Kalmar\r\n'),
 (19,'Borlänge','Dalarna\r\n'),
 (20,'Borås','Västra Götaland\r\n'),
 (21,'Botkyrka','Stockholm\r\n'),
 (22,'Boxholm','Östergötland\r\n'),
 (23,'Bromölla','Skåne\r\n'),
 (24,'Bräcke','Jämtland\r\n'),
 (25,'Burlöv','Skåne\r\n'),
 (26,'Båstad','Skåne\r\n'),
 (27,'Dals-Ed','Västra Götaland\r\n'),
 (28,'Danderyd','Stockholm\r\n'),
 (29,'Degerfors','Örebro\r\n'),
 (30,'Dorotea','Västerbotten\r\n'),
 (31,'Eda','Värmland\r\n'),
 (32,'Ekerö','Stockholm\r\n'),
 (33,'Eksjö','Jönköping\r\n'),
 (34,'Emmaboda','Kalmar\r\n'),
 (35,'Enköping','Uppsala\r\n'),
 (36,'Eskilstuna','Södermanland\r\n'),
 (37,'Eslöv','Skåne\r\n'),
 (38,'Essunga','Västra Götaland\r\n'),
 (39,'Fagersta','Västmanland\r\n'),
 (40,'Falkenberg','Halland\r\n'),
 (41,'Falköping','Västra Götaland\r\n'),
 (42,'Falu','Dalarna\r\n'),
 (43,'Filipstad','Värmland\r\n'),
 (44,'Finspång','Östergötland\r\n'),
 (45,'Flen','Södermanland\r\n'),
 (46,'Forshaga','Värmland\r\n'),
 (47,'Färgelanda','Västra Götaland\r\n'),
 (48,'Gagnef','Dalarna\r\n'),
 (49,'Gislaved','Jönköping\r\n'),
 (50,'Gnesta','Södermanland\r\n'),
 (51,'Gnosjö','Jönköping\r\n'),
 (52,'Gotland','Gotland\r\n'),
 (53,'Grums','Värmland\r\n'),
 (54,'Grästorp','Västra Götaland\r\n'),
 (55,'Gullspång','Västra Götaland\r\n'),
 (56,'Gällivare','Norrbotten\r\n'),
 (57,'Gävle','Gävleborg\r\n'),
 (58,'Göteborg','Västra Götaland\r\n'),
 (59,'Götene','Västra Götaland\r\n'),
 (60,'Habo','Jönköping\r\n'),
 (61,'Hagfors','Värmland\r\n'),
 (62,'Hallsberg','Örebro\r\n'),
 (63,'Hallstahammar','Västmanland\r\n'),
 (64,'Halmstad','Halland\r\n'),
 (65,'Hammarö','Värmland\r\n'),
 (66,'Haninge','Stockholm\r\n'),
 (67,'Haparanda','Norrbotten\r\n'),
 (68,'Heby','Uppsala\r\n'),
 (69,'Hedemora','Dalarna\r\n'),
 (70,'Helsingborg','Skåne\r\n'),
 (71,'Herrljunga','Västra Götaland\r\n'),
 (72,'Hjo','Västra Götaland\r\n'),
 (73,'Hofors','Gävleborg\r\n'),
 (74,'Huddinge','Stockholm\r\n'),
 (75,'Hudiksvall','Gävleborg\r\n'),
 (76,'Hultsfred','Kalmar\r\n'),
 (77,'Hylte','Halland\r\n'),
 (78,'Håbo','Uppsala\r\n'),
 (79,'Hällefors','Örebro\r\n'),
 (80,'Härjedalen','Jämtland\r\n'),
 (81,'Härnösand','Västernorrland\r\n'),
 (82,'Härryda','Västra Götaland\r\n'),
 (83,'Hässleholm','Skåne\r\n'),
 (84,'Höganäs','Skåne\r\n'),
 (85,'Högsby','Kalmar\r\n'),
 (86,'Hörby','Skåne\r\n'),
 (87,'Höör','Skåne\r\n'),
 (88,'Jokkmokk','Norrbotten\r\n'),
 (89,'Järfälla','Stockholm\r\n'),
 (90,'Jönköping','Jönköping\r\n'),
 (91,'Kalix','Norrbotten\r\n'),
 (92,'Kalmar','Kalmar\r\n'),
 (93,'Karlsborg','Västra Götaland\r\n'),
 (94,'Karlshamn','Blekinge\r\n'),
 (95,'Karlskoga','Örebro\r\n'),
 (96,'Karlskrona','Blekinge\r\n'),
 (97,'Karlstad','Värmland\r\n'),
 (98,'Katrineholm','Södermanland\r\n'),
 (99,'Kil','Värmland\r\n'),
 (100,'Kinda','Östergötland\r\n'),
 (101,'Kiruna','Norrbotten\r\n'),
 (102,'Klippan','Skåne\r\n'),
 (103,'Knivsta','Uppsala\r\n'),
 (104,'Kramfors','Västernorrland\r\n'),
 (105,'Kristianstad','Skåne\r\n'),
 (106,'Kristinehamn','Värmland\r\n'),
 (107,'Krokom','Jämtland\r\n'),
 (108,'Kumla','Örebro\r\n'),
 (109,'Kungsbacka','Halland\r\n'),
 (110,'Kungsör','Västmanland\r\n'),
 (111,'Kungälv','Västra Götaland\r\n'),
 (112,'Kävlinge','Skåne\r\n'),
 (113,'Köping','Västmanland\r\n'),
 (114,'Laholm','Halland\r\n'),
 (115,'Landskrona','Skåne\r\n'),
 (116,'Laxå','Örebro\r\n'),
 (117,'Lekeberg','Örebro\r\n'),
 (118,'Leksand','Dalarna\r\n'),
 (119,'Lerum','Västra Götaland\r\n'),
 (120,'Lessebo','Kronoberg\r\n'),
 (121,'Lidingö','Stockholm\r\n'),
 (122,'Lidköping','Västra Götaland\r\n'),
 (123,'Lilla Edet','Västra Götaland\r\n'),
 (124,'Lindesberg','Örebro\r\n'),
 (125,'Linköping','Östergötland\r\n'),
 (126,'Ljungby','Kronoberg\r\n'),
 (127,'Ljusdal','Gävleborg\r\n'),
 (128,'Ljusnarsberg','Örebro\r\n'),
 (129,'Lomma','Skåne\r\n'),
 (130,'Ludvika','Dalarna\r\n'),
 (131,'Luleå','Norrbotten\r\n'),
 (132,'Lund','Skåne\r\n'),
 (133,'Lycksele','Västerbotten\r\n'),
 (134,'Lysekil','Västra Götaland\r\n'),
 (135,'Malmö','Skåne\r\n'),
 (136,'Malung-Sälen','Dalarna\r\n'),
 (137,'Malå','Västerbotten\r\n'),
 (138,'Mariestad','Västra Götaland\r\n'),
 (139,'Mark','Västra Götaland\r\n'),
 (140,'Markaryd','Kronoberg\r\n'),
 (141,'Mellerud','Västra Götaland\r\n'),
 (142,'Mjölby','Östergötland\r\n'),
 (143,'Mora','Dalarna\r\n'),
 (144,'Motala','Östergötland\r\n'),
 (145,'Mullsjö','Jönköping\r\n'),
 (146,'Munkedal','Västra Götaland\r\n'),
 (147,'Munkfors','Värmland\r\n'),
 (148,'Mölndal','Västra Götaland\r\n'),
 (149,'Mönsterås','Kalmar\r\n'),
 (150,'Mörbylånga','Kalmar\r\n'),
 (151,'Nacka','Stockholm\r\n'),
 (152,'Nora','Örebro\r\n'),
 (153,'Norberg','Västmanland\r\n'),
 (154,'Nordanstig','Gävleborg\r\n'),
 (155,'Nordmaling','Västerbotten\r\n'),
 (156,'Norrköping','Östergötland\r\n'),
 (157,'Norrtälje','Stockholm\r\n'),
 (158,'Norsjö','Västerbotten\r\n'),
 (159,'Nybro','Kalmar\r\n'),
 (160,'Nykvarn','Stockholm\r\n'),
 (161,'Nyköping','Södermanland\r\n'),
 (162,'Nynäshamn','Stockholm\r\n'),
 (163,'Nässjö','Jönköping\r\n'),
 (164,'Ockelbo','Gävleborg\r\n'),
 (165,'Olofström','Blekinge\r\n'),
 (166,'Orsa','Dalarna\r\n'),
 (167,'Orust','Västra Götaland\r\n'),
 (168,'Osby','Skåne\r\n'),
 (169,'Oskarshamn','Kalmar\r\n'),
 (170,'Ovanåker','Gävleborg\r\n'),
 (171,'Oxelösund','Södermanland\r\n'),
 (172,'Pajala','Norrbotten\r\n'),
 (173,'Partille','Västra Götaland\r\n'),
 (174,'Perstorp','Skåne\r\n'),
 (175,'Piteå','Norrbotten\r\n'),
 (176,'Ragunda','Jämtland\r\n'),
 (177,'Robertsfors','Västerbotten\r\n'),
 (178,'Ronneby','Blekinge\r\n'),
 (179,'Rättvik','Dalarna\r\n'),
 (180,'Sala','Västmanland\r\n'),
 (181,'Salem','Stockholm\r\n'),
 (182,'Sandviken','Gävleborg\r\n'),
 (183,'Sigtuna','Stockholm\r\n'),
 (184,'Simrishamn','Skåne\r\n'),
 (185,'Sjöbo','Skåne\r\n'),
 (186,'Skara','Västra Götaland\r\n'),
 (187,'Skellefteå','Västerbotten\r\n'),
 (188,'Skinnskatteberg','Västmanland\r\n'),
 (189,'Skurup','Skåne\r\n'),
 (190,'Skövde','Västra Götaland\r\n'),
 (191,'Smedjebacken','Dalarna\r\n'),
 (192,'Sollefteå','Västernorrland\r\n'),
 (193,'Sollentuna','Stockholm\r\n'),
 (194,'Solna','Stockholm\r\n'),
 (195,'Sorsele','Västerbotten\r\n'),
 (196,'Sotenäs','Västra Götaland\r\n'),
 (197,'Staffanstorp','Skåne\r\n'),
 (198,'Stenungsund','Västra Götaland\r\n'),
 (199,'Stockholm','Stockholm\r\n'),
 (200,'Storfors','Värmland\r\n'),
 (201,'Storuman','Västerbotten\r\n'),
 (202,'Strängnäs','Södermanland\r\n'),
 (203,'Strömstad','Västra Götaland\r\n'),
 (204,'Strömsund','Jämtland\r\n'),
 (205,'Sundbyberg','Stockholm\r\n'),
 (206,'Sundsvall','Västernorrland\r\n'),
 (207,'Sunne','Värmland\r\n'),
 (208,'Surahammar','Västmanland\r\n'),
 (209,'Svalöv','Skåne\r\n'),
 (210,'Svedala','Skåne\r\n'),
 (211,'Svenljunga','Västra Götaland\r\n'),
 (212,'Säffle','Värmland\r\n'),
 (213,'Säter','Dalarna\r\n'),
 (214,'Sävsjö','Jönköping\r\n'),
 (215,'Söderhamn','Gävleborg\r\n'),
 (216,'Söderköping','Östergötland\r\n'),
 (217,'Södertälje','Stockholm\r\n'),
 (218,'Sölvesborg','Blekinge\r\n'),
 (219,'Tanum','Västra Götaland\r\n'),
 (220,'Tibro','Västra Götaland\r\n'),
 (221,'Tidaholm','Västra Götaland\r\n'),
 (222,'Tierp','Uppsala\r\n'),
 (223,'Timrå','Västernorrland\r\n'),
 (224,'Tingsryd','Kronoberg\r\n'),
 (225,'Tjörn','Västra Götaland\r\n'),
 (226,'Tomelilla','Skåne\r\n'),
 (227,'Torsby','Värmland\r\n'),
 (228,'Torsås','Kalmar\r\n'),
 (229,'Tranemo','Västra Götaland\r\n'),
 (230,'Tranås','Jönköping\r\n'),
 (231,'Trelleborg','Skåne\r\n'),
 (232,'Trollhättan','Västra Götaland\r\n'),
 (233,'Trosa','Södermanland\r\n'),
 (234,'Tyresö','Stockholm\r\n'),
 (235,'Täby','Stockholm\r\n'),
 (236,'Töreboda','Västra Götaland\r\n'),
 (237,'Uddevalla','Västra Götaland\r\n'),
 (238,'Ulricehamn','Västra Götaland\r\n'),
 (239,'Umeå','Västerbotten\r\n'),
 (240,'Upplands Väsby','Stockholm\r\n'),
 (241,'Upplands-Bro','Stockholm\r\n'),
 (242,'Uppsala','Uppsala\r\n'),
 (243,'Uppvidinge','Kronoberg\r\n'),
 (244,'Vadstena','Östergötland\r\n'),
 (245,'Vaggeryd','Jönköping\r\n'),
 (246,'Valdemarsvik','Östergötland\r\n'),
 (247,'Vallentuna','Stockholm\r\n'),
 (248,'Vansbro','Dalarna\r\n'),
 (249,'Vara','Västra Götaland\r\n'),
 (250,'Varberg','Halland\r\n'),
 (251,'Vaxholm','Stockholm\r\n'),
 (252,'Vellinge','Skåne\r\n'),
 (253,'Vetlanda','Jönköping\r\n'),
 (254,'Vilhelmina','Västerbotten\r\n'),
 (255,'Vimmerby','Kalmar\r\n'),
 (256,'Vindeln','Västerbotten\r\n'),
 (257,'Vingåker','Södermanland\r\n'),
 (258,'Vårgårda','Västra Götaland\r\n'),
 (259,'Vänersborg','Västra Götaland\r\n'),
 (260,'Vännäs','Västerbotten\r\n'),
 (261,'Värmdö','Stockholm\r\n'),
 (262,'Värnamo','Jönköping\r\n'),
 (263,'Västervik','Kalmar\r\n'),
 (264,'Västerå','Västmanland\r\n'),
 (265,'Växjö','Kronoberg\r\n'),
 (266,'Ydre','Östergötland\r\n'),
 (267,'Ystad','Skåne\r\n'),
 (268,'Åmål','Västra Götaland\r\n'),
 (269,'Ånge','Västernorrland\r\n'),
 (270,'Åre','Jämtland\r\n'),
 (271,'Årjäng','Värmland\r\n'),
 (272,'Åsele','Västerbotten\r\n'),
 (273,'Åstorp','Skåne\r\n'),
 (274,'Åtvidaberg','Östergötland\r\n'),
 (275,'Älmhult','Kronoberg\r\n'),
 (276,'Älvdalen','Dalarna\r\n'),
 (277,'Älvkarleby','Uppsala\r\n'),
 (278,'Älvsbyn','Norrbotten\r\n'),
 (279,'Ängelholm','Skåne\r\n'),
 (280,'Öckerö','Västra Götaland\r\n'),
 (281,'Ödeshög','Östergötland\r\n'),
 (282,'Örebro','Örebro\r\n'),
 (283,'Örkelljunga','Skåne\r\n'),
 (284,'Örnsköldsvik','Västernorrland\r\n'),
 (285,'Östersund','Jämtland\r\n'),
 (286,'Österåker','Stockholm\r\n'),
 (287,'Östhammar','Uppsala\r\n'),
 (288,'Östra Göinge','Skåne\r\n'),
 (289,'Överkalix','Norrbotten\r\n'),
 (290,'Övertorneå','Norrbotten');
/*!40000 ALTER TABLE `kommuner` ENABLE KEYS */;


--
-- Definition of table `membership_fees`
--

DROP TABLE IF EXISTS `membership_fees`;
CREATE TABLE `membership_fees` (
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
-- Dumping data for table `membership_fees`
--

/*!40000 ALTER TABLE `membership_fees` DISABLE KEYS */;
/*!40000 ALTER TABLE `membership_fees` ENABLE KEYS */;


--
-- Definition of table `messages`
--

DROP TABLE IF EXISTS `messages`;
CREATE TABLE `messages` (
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
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `messages`
--

/*!40000 ALTER TABLE `messages` DISABLE KEYS */;
/*!40000 ALTER TABLE `messages` ENABLE KEYS */;


--
-- Definition of table `post_reports`
--

DROP TABLE IF EXISTS `post_reports`;
CREATE TABLE `post_reports` (
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
-- Dumping data for table `post_reports`
--

/*!40000 ALTER TABLE `post_reports` DISABLE KEYS */;
/*!40000 ALTER TABLE `post_reports` ENABLE KEYS */;


--
-- Definition of table `posts`
--

DROP TABLE IF EXISTS `posts`;
CREATE TABLE `posts` (
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
) ENGINE=MyISAM AUTO_INCREMENT=51 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `posts`
--

/*!40000 ALTER TABLE `posts` DISABLE KEYS */;
INSERT INTO `posts` (`id`,`topic_id`,`user_id`,`forum_id`,`is_topic`,`posted_time`,`last_edited_time`,`title`,`content`) VALUES 
 (38,38,4,1,1,1432278142,NULL,'Testtråd',''),
 (39,39,4,1,1,1432294979,NULL,'Moderator lägger sig i','Ett svar. '),
 (40,40,4,1,1,1432295280,NULL,'En till testtråd',''),
 (41,41,4,1,1,1432295423,NULL,'Tredje testtråden',''),
 (42,42,4,1,1,1432295491,NULL,'Fjärde testtråden','Ytterligare test. '),
 (48,48,6,1,1,1432645559,NULL,'tst','svar'),
 (50,50,6,1,1,1432645649,NULL,'asrta','asdf'),
 (44,38,6,1,0,1432538300,NULL,'Testtråd','<div class=\"quote_in_post\"><a class=\"quote_in_post_link\" href=\"index.php?type=forum&action=show_posts&id=39\">Gullan Katt skrev:</a>\nsvar</div>\r\nSvar med citat. ');
/*!40000 ALTER TABLE `posts` ENABLE KEYS */;


--
-- Definition of table `propositions`
--

DROP TABLE IF EXISTS `propositions`;
CREATE TABLE `propositions` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `type` varchar(20) NOT NULL default '',
  `created_by_user` int(10) unsigned default NULL,
  `created_by_delegate` int(10) unsigned default NULL,
  `timestamp_created` int(10) unsigned NOT NULL default '0',
  `timestamp_ended` int(10) unsigned default NULL,
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `status` varchar(12) NOT NULL default 'pending',
  `number_of_supporters` int(10) unsigned NOT NULL default '0',
  `number_of_enemies` int(10) unsigned NOT NULL default '0',
  `title` varchar(90) NOT NULL default '',
  `description` text NOT NULL,
  `forum_topic_id` int(10) unsigned default NULL,
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `search` (`title`,`description`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `propositions`
--

/*!40000 ALTER TABLE `propositions` DISABLE KEYS */;
INSERT INTO `propositions` (`id`,`type`,`created_by_user`,`created_by_delegate`,`timestamp_created`,`timestamp_ended`,`constituency_id`,`status`,`number_of_supporters`,`number_of_enemies`,`title`,`description`,`forum_topic_id`) VALUES 
 (1,'yes-no',5,NULL,1426586078,NULL,165,'rejected',0,1,'Testvotering','Bara ett test. ',31),
 (2,'yes-no',5,NULL,1428388195,NULL,165,'affirmed',1,0,'Testvotering2','Ett test till. ',32),
 (3,'median',4,NULL,1428506873,1428506887,165,'affirmed',1,0,'Mediantest','Test av medianomröstningar.',33),
 (4,'prio-vote',6,NULL,1430116507,1430117564,165,'affirmed',1,0,'Prio-test','Det är dags att testa prioritetsomröstningar. ',34),
 (5,'candidate-election',6,NULL,1430808243,1430850944,165,'affirmed',1,0,'Personvalstest','Test av personvalsfunktionen. ',35);
/*!40000 ALTER TABLE `propositions` ENABLE KEYS */;


--
-- Definition of table `propositions_support`
--

DROP TABLE IF EXISTS `propositions_support`;
CREATE TABLE `propositions_support` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `proposition_id` int(10) unsigned NOT NULL default '0',
  `user_code` varchar(20) NOT NULL default '',
  `delegate_id` int(10) unsigned default NULL,
  `support_type` varchar(7) NOT NULL default 'support',
  `time_ballot_placed` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `propositions_support`
--

/*!40000 ALTER TABLE `propositions_support` DISABLE KEYS */;
INSERT INTO `propositions_support` (`id`,`proposition_id`,`user_code`,`delegate_id`,`support_type`,`time_ballot_placed`) VALUES 
 (6,1,'osb8A8xrrQrGQfologrm',NULL,'reject',0),
 (7,2,'osb8A8xrrQrGQfologrm',NULL,'support',1428388208),
 (8,3,'OBc7rZoonK45KsRWs4gq',NULL,'support',1428506887),
 (9,4,'nNSpJccU3OdwJxq3SMBw',NULL,'support',1430117564),
 (10,5,'nNSpJccU3OdwJxq3SMBw',NULL,'support',1430850943);
/*!40000 ALTER TABLE `propositions_support` ENABLE KEYS */;


--
-- Definition of table `user_applications`
--

DROP TABLE IF EXISTS `user_applications`;
CREATE TABLE `user_applications` (
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `user_applications`
--

/*!40000 ALTER TABLE `user_applications` DISABLE KEYS */;
/*!40000 ALTER TABLE `user_applications` ENABLE KEYS */;


--
-- Definition of table `users`
--

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
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
) ENGINE=MyISAM AUTO_INCREMENT=14 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `users`
--

/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` (`id`,`username`,`password`,`remember_me_token`,`registration_time`,`deletion_time`,`last_login_time`,`last_activity_time`,`first_name`,`last_name`,`street_address`,`zip_code`,`city_address`,`county`,`region`,`social_security_number`,`email`,`telephone1`,`telephone2`,`skype_name`,`show_email`,`show_telephone`,`show_skype`,`number_of_posts`,`number_of_topics`,`membership_fee_payed`,`last_contact_with_admin`,`acting_as_delegate`,`user_role`,`admin_notes`,`image`,`description`) VALUES 
 (13,'skutt','$2a$08$.D/rwa/4GMuDX6toO6f0S.k0l6NbHYOd5riJqLbtiNeklXN7WRtQe',NULL,1432280530,NULL,1432280541,1432280562,'Skutt','Katt','','','','Olofström','Blekinge\r\n','','skutt@katt.se','','','',1,1,1,0,0,NULL,NULL,0,2,'','no_image.png',NULL),
 (4,'gullan','$2a$08$qmMitF1wFOtDsNkpQqLn8e9my0OojrDFXy3uBR9lKxVOHrbbShM/y','$2a$08$2Iz.i7jKVIz3VApiTTb4OOfbW4t.mJriq6vvJ1NceI7zExjMtZyjC',1420102449,NULL,1432285333,1432311720,'Gullan','Katt','','','','Olofström','Blekinge\r\n','','gullan@katt.se','','','',1,1,1,5,5,NULL,NULL,0,2,'','no_image.png','Mjau.'),
 (5,'missan','$2a$08$zaaFjU/eVdew7BqSTG4oyO.5UsZ6H2F6lugaJU0Mwnvag3mPp.Vta','$2a$08$H/sPTWXHbSpnCeSaKKy7s.NnNGio2oc.XCGr7ePBJq4RWMeG/u/x.',1420102512,NULL,1432280590,1432280917,'Missan','Katt','','','','Olofström','Blekinge\r\n','','missan@katt.se','','','',1,1,1,2,2,NULL,NULL,0,2,'','no_image.png',NULL),
 (6,'suddis','$2a$08$ByrId8LM06kA.4PaMj4MGu/Ftkyh/nMwj.3zFfiDLv3fAUzbLmkRC','$2a$08$P/.wif2iQv1Mf2ogk2g9we7.tCvTjKFbkIKl0J2CyyWbo1n7Dw6mu',1420102590,NULL,1432311727,1432896196,'Suddis','Katt','','','','Olofström','Blekinge\r\n','','suddis@katt.se','','','',1,1,1,3,2,NULL,NULL,0,2,'','no_image.png',NULL);
/*!40000 ALTER TABLE `users` ENABLE KEYS */;


--
-- Definition of table `voters_delegates`
--

DROP TABLE IF EXISTS `voters_delegates`;
CREATE TABLE `voters_delegates` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `delegate_id` int(10) unsigned NOT NULL default '0',
  `user_code` varchar(20) default NULL,
  `voter_id_delegate_id` int(10) unsigned default NULL,
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `priority` int(10) unsigned NOT NULL default '1',
  `time_delegate_chosen` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `voters_delegates`
--

/*!40000 ALTER TABLE `voters_delegates` DISABLE KEYS */;
/*!40000 ALTER TABLE `voters_delegates` ENABLE KEYS */;


--
-- Definition of table `votes`
--

DROP TABLE IF EXISTS `votes`;
CREATE TABLE `votes` (
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
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `votes`
--

/*!40000 ALTER TABLE `votes` DISABLE KEYS */;
INSERT INTO `votes` (`id`,`type`,`from_proposition_id`,`timestamp_created`,`timestamp_delegate_ended`,`timestamp_ended`,`constituency_id`,`status`,`title`,`description`,`number_of_alternatives`,`number_of_ballots`,`number_of_direct_ballots`,`forum_topic_id`) VALUES 
 (1,'yes-no',2,1428388208,1429393008,1430397808,165,'active','Testvotering2','Ett test till. ',0,3,3,32),
 (2,'median',3,1428506887,1429111687,1429716487,165,'del_ended','Mediantest','Test av medianomröstningar.',0,3,3,33),
 (3,'prio-vote',4,1430117564,1430722364,1431327164,165,'active','Prio-test','Det är dags att testa prioritetsomröstningar. ',5,1,1,34),
 (4,'candidate-election',5,1430850944,1432061700,1432148100,165,'active','Personvalstest','Test av personvalsfunktionen. ',2,1,1,35),
 (5,'yes-no',NULL,1431852086,1432471243,1433090400,291,'active','Adminskapad omröstning','Test av admin-funktioner.',0,0,0,36),
 (6,'prio-vote',NULL,1431861479,NULL,NULL,291,'continuous','Kontinuerlig prioritetsomröstning','Ännu ett test. ',0,0,0,37);
/*!40000 ALTER TABLE `votes` ENABLE KEYS */;


--
-- Definition of table `votes_alternatives`
--

DROP TABLE IF EXISTS `votes_alternatives`;
CREATE TABLE `votes_alternatives` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `vote_id` int(10) unsigned NOT NULL default '0',
  `added_by_user` int(10) unsigned default NULL,
  `added_by_delegate` int(10) unsigned default NULL,
  `timestamp_added` int(10) unsigned NOT NULL default '0',
  `alternative_title` varchar(90) NOT NULL default '',
  `alternative_description` text NOT NULL,
  `alternative_user_id` int(10) unsigned default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=11 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `votes_alternatives`
--

/*!40000 ALTER TABLE `votes_alternatives` DISABLE KEYS */;
INSERT INTO `votes_alternatives` (`id`,`vote_id`,`added_by_user`,`added_by_delegate`,`timestamp_added`,`alternative_title`,`alternative_description`,`alternative_user_id`) VALUES 
 (1,3,6,NULL,1430376548,'Första alternativet','Det allra första alternativet i en prioomröstning. ',NULL),
 (2,3,6,NULL,1430390060,'Andra alternativet','Ett alternativ till. ',NULL),
 (3,3,6,NULL,1430390078,'Tredje alternativet','Och, slutligen, ännu ett alternativ. ',NULL),
 (4,3,6,NULL,1430807992,'Fjärde alternativet','Ett fjärde alternativ. ',NULL),
 (6,4,6,NULL,1430897482,'Suddis Katt','Mer katter i den flytande demokratin. ',6),
 (8,3,NULL,NULL,1432040362,'Alternativ fem','Numero cinq.',NULL),
 (10,4,4,NULL,1432053297,'Gullan Katt','Gullan är en tvångskandidat.',4);
/*!40000 ALTER TABLE `votes_alternatives` ENABLE KEYS */;


--
-- Definition of table `workgroups`
--

DROP TABLE IF EXISTS `workgroups`;
CREATE TABLE `workgroups` (
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
) ENGINE=MyISAM AUTO_INCREMENT=2 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroups`
--

/*!40000 ALTER TABLE `workgroups` DISABLE KEYS */;
INSERT INTO `workgroups` (`id`,`title`,`description`,`is_active`,`number_of_members`,`create_time`,`create_user`,`public_forum_id`,`is_restricted`,`propose_time`,`private_forum_id`) VALUES 
 (1,'Testgruppen','Vi testar funktionerna. ',1,3,1423038623,1,4,0,0,5);
/*!40000 ALTER TABLE `workgroups` ENABLE KEYS */;


--
-- Definition of table `workgroups_candidates`
--

DROP TABLE IF EXISTS `workgroups_candidates`;
CREATE TABLE `workgroups_candidates` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `workgroup_id` int(10) unsigned NOT NULL default '0',
  `candidate_id` int(10) unsigned NOT NULL default '0',
  `number_of_supporters` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroups_candidates`
--

/*!40000 ALTER TABLE `workgroups_candidates` DISABLE KEYS */;
/*!40000 ALTER TABLE `workgroups_candidates` ENABLE KEYS */;


--
-- Definition of table `workgroups_candidates_support`
--

DROP TABLE IF EXISTS `workgroups_candidates_support`;
CREATE TABLE `workgroups_candidates_support` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `workgroup_id` int(10) unsigned NOT NULL default '0',
  `candidate_id` int(10) unsigned NOT NULL default '0',
  `supporter_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=6 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroups_candidates_support`
--

/*!40000 ALTER TABLE `workgroups_candidates_support` DISABLE KEYS */;
INSERT INTO `workgroups_candidates_support` (`id`,`workgroup_id`,`candidate_id`,`supporter_id`) VALUES 
 (3,1,6,4);
/*!40000 ALTER TABLE `workgroups_candidates_support` ENABLE KEYS */;


--
-- Definition of table `workgroups_members`
--

DROP TABLE IF EXISTS `workgroups_members`;
CREATE TABLE `workgroups_members` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `workgroup_id` int(10) unsigned NOT NULL default '0',
  `user_id` int(10) unsigned NOT NULL default '0',
  `member_since` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=17 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroups_members`
--

/*!40000 ALTER TABLE `workgroups_members` DISABLE KEYS */;
INSERT INTO `workgroups_members` (`id`,`workgroup_id`,`user_id`,`member_since`) VALUES 
 (15,1,6,1432278227),
 (14,1,4,1423038623),
 (16,1,13,1432280594);
/*!40000 ALTER TABLE `workgroups_members` ENABLE KEYS */;


--
-- Definition of table `workgroups_members_exclude`
--

DROP TABLE IF EXISTS `workgroups_members_exclude`;
CREATE TABLE `workgroups_members_exclude` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `workgroup_id` int(10) unsigned NOT NULL default '0',
  `excluded_id` int(10) unsigned NOT NULL default '0',
  `excluder_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=20 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroups_members_exclude`
--

/*!40000 ALTER TABLE `workgroups_members_exclude` DISABLE KEYS */;
INSERT INTO `workgroups_members_exclude` (`id`,`workgroup_id`,`excluded_id`,`excluder_id`) VALUES 
 (19,1,1,4);
/*!40000 ALTER TABLE `workgroups_members_exclude` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
