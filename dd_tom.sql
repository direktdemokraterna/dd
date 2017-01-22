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

SET SQL_SAFE_UPDATES = 0;

--
-- Create schema dd
--

CREATE DATABASE IF NOT EXISTS dd_anders;
USE dd_anders;

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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

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
(313,'Allmänt','',4,1,1,NULL),
(314,'Utomlands','',0,323,3,315),
(315,'Utomlands','',0,324,2,313);
/*!40000 ALTER TABLE `constituency` ENABLE KEYS */;

--
-- Definition of table `voter`
--

DROP TABLE IF EXISTS `voter`;
CREATE TABLE `voter` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `voter_type` varchar(20) NOT NULL default 'user', -- user or delegate
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Definition of table `user`
--

DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `id` int(10) unsigned NOT NULL,
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
  `region_id` int(10) unsigned NOT NULL,
  `county_id` int(10) unsigned NOT NULL,
  `social_security_number` varchar(13) default '',
  `email` varchar(45) NOT NULL default '',
  `telephone1` varchar(20) default '',
  `telephone2` varchar(20) default '',
  `skype_name` varchar(45) default '',
  `show_email` tinyint(1) unsigned NOT NULL default '0',
  `show_telephone` tinyint(1) unsigned NOT NULL default '0',
  `show_skype` tinyint(1) unsigned NOT NULL default '0',
  `number_of_posts` int(10) unsigned NOT NULL default '0',
  `number_of_topics` int(10) unsigned NOT NULL default '0',
  `membership_fee_payed` int(10) unsigned default NULL,
  `last_contact_with_admin` int(10) unsigned default NULL,
  `acting_as_delegate` tinyint(1) unsigned default '0',
  `user_role` int(10) unsigned NOT NULL default '2',
  `admin_notes` varchar(255) default '',
  `image` varchar(90) NOT NULL default 'no_image.png',
  `description` text,
  `activation_code` varchar(20) default NULL,
  `activation_time` integer unsigned default 1460019477,
  `activation_first_name` varchar(45) default NULL,
  `activation_last_name` varchar(45) default NULL,
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `search` (`first_name`,`last_name`,`description`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
ALTER TABLE `dd_anders`.`user`
  ADD CONSTRAINT fk_user_voter_id FOREIGN KEY (id) REFERENCES voter(`id`);
ALTER TABLE `dd_anders`.`user`
  ADD CONSTRAINT fk_user_region_id FOREIGN KEY (region_id) REFERENCES constituency(`id`);
ALTER TABLE `dd_anders`.`user`
  ADD CONSTRAINT fk_user_county_id FOREIGN KEY (county_id) REFERENCES constituency(`id`);
CREATE UNIQUE INDEX ux_user_username ON `dd_anders`.`user` (`username`);

--
-- Dumping data for table `user`
--

--
-- Definition of table `delegate`
--

DROP TABLE IF EXISTS `delegate`;
CREATE TABLE `delegate` (
  `id` int(10) unsigned NOT NULL,
  `title` varchar(90) NOT NULL default '',
  `description` text NOT NULL,
  `timestamp_created` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
ALTER TABLE `dd_anders`.`delegate`
  ADD FOREIGN KEY (id) REFERENCES voter(`id`);

--
-- Dumping data for table `delegate`
--

--
-- Definition of table `delegate_user`
--

DROP TABLE IF EXISTS `delegate_user`;
CREATE TABLE `delegate_user` (
  `user_id` int(10) unsigned NOT NULL,
  `delegate_id` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
ALTER TABLE `dd_anders`.`delegate_user`
  ADD FOREIGN KEY (delegate_id) REFERENCES delegate(`id`);
ALTER TABLE `dd_anders`.`delegate_user`
  ADD FOREIGN KEY (user_id) REFERENCES user(`id`);

--
-- Dumping data for table `delegate_user`
--

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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `admin_role`
--

/*!40000 ALTER TABLE `admin_role` DISABLE KEYS */;
INSERT INTO `admin_role` (`id`,`title`,`description`,`type`) VALUES 
 (1,'Superadmin','','superadmin'),
 (2,'Member admin','','member_admin'),
 (3,'Forum admin','','forum_admin'),
 (4,'Vote admin','','vote_admin'),
 (5,'Treasurer','','treasurer');
/*!40000 ALTER TABLE `admin_role` ENABLE KEYS */;

--
-- Definition of table `admin_role_user`
--

DROP TABLE IF EXISTS `admin_role_user`;
CREATE TABLE `admin_role_user` (
  `admin_role_id` int(10) unsigned NOT NULL,
  `user_id` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`admin_role_id`, `user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
ALTER TABLE `dd_anders`.`admin_role_user`
  ADD FOREIGN KEY (admin_role_id) REFERENCES admin_role(`id`);
ALTER TABLE `dd_anders`.`admin_role_user`
  ADD FOREIGN KEY (user_id) REFERENCES user(`id`);

--
-- Dumping data for table `admin_role_user`
--

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
  `voter_id` int(10) unsigned default NULL,
  `delegate_id` int(10) unsigned default NULL,
  `delegation_level` int(10) unsigned default NULL,
  `delegate_priority` int(10) unsigned default NULL,
  `time_ballot_placed` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `ballot`
--

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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `calendar`
--

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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Definition of table `category`
--

DROP TABLE IF EXISTS `category`;
CREATE TABLE `category` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `title` varchar(45) NOT NULL default '',
  `description` text NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `category`
--

/*!40000 ALTER TABLE `category` DISABLE KEYS */;
INSERT INTO `category` (`id`,`title`,`description`) VALUES 
 (8,'Interna arbetsgruppsforum','Dessa forum har bara medlemmarna i den respektive arbetsgrupperna tillg†ng till.'),
 (9,'Arbetsgrupper','Publika forum f”r de olika arbetsgrupperna.'),
 (2,'Lokala forum','');
/*!40000 ALTER TABLE `category` ENABLE KEYS */;

--
-- Definition of table `constituency_voter`
--

DROP TABLE IF EXISTS `constituency_voter`;
CREATE TABLE `constituency_voter` (
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `voter_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY (`constituency_id`, `voter_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
ALTER TABLE `dd_anders`.`constituency_voter`
  ADD FOREIGN KEY (voter_id) REFERENCES voter(`id`);
ALTER TABLE `dd_anders`.`constituency_voter`
  ADD FOREIGN KEY (constituency_id) REFERENCES constituency(`id`);

--
-- Dumping data for table `constituency_voter`
--
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for timestamp_addedble `forum`
--

insert into forum
(id, category_id, title, description, access_type)
select forum_id, 2, title, description, 'local_county' 
from constituency where constituency_level = 3;

insert into forum
(id, category_id, title, description, access_type)
select forum_id, 2, title, description, 'local_region' 
from constituency where constituency_level = 2;

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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `post`
--
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `forum_user`
--
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `message`
--
--
-- Definition of table `proposition`
--

DROP TABLE IF EXISTS `proposition`;
CREATE TABLE `proposition` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `type` varchar(20) NOT NULL default '',
  `created_by_voter` int(10) unsigned default NULL,
  `timestamp_created` int(10) unsigned NOT NULL default '0',
  `timestamp_ended` int(10) unsigned default NULL,
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `status` varchar(12) NOT NULL default 'pending',
  `number_of_supporters` int(10) unsigned NOT NULL default '0',
  `title` varchar(90) NOT NULL default '',
  `description` text NOT NULL,
  `forum_topic_id` int(10) unsigned default NULL,
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `search` (`title`,`description`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `proposition`
--
--
-- Definition of table `proposition_support`
--

DROP TABLE IF EXISTS `proposition_support`;
CREATE TABLE `proposition_support` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `proposition_id` int(10) unsigned NOT NULL default '0',
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `user_code` varchar(20) default NULL,
  `voter_id` int(10) unsigned default NULL,
  `delegate_id` int(10) unsigned default NULL,
  `delegation_level` int(10) unsigned default NULL,
  `delegate_priority` int(10) unsigned default NULL,
  `support` bit NULL,
  `time_ballot_placed` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `proposition_support`
--
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
  `county_id` int(10) unsigned NOT NULL,
  `region_id` int(10) unsigned NOT NULL,
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `vote`
--
--
-- Definition of table `vote_alternative`
--

DROP TABLE IF EXISTS `vote_alternative`;
CREATE TABLE `vote_alternative` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `vote_id` int(10) unsigned NOT NULL default '0',
  `added_by_voter` int(10) unsigned default NULL,
  `timestamp_added` int(10) unsigned NOT NULL default '0',
  `alternative_title` varchar(90) NOT NULL default '',
  `alternative_description` text NOT NULL,
  `alternative_user_id` int(10) unsigned default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `vote_alternative`
--
--
-- Definition of table `voter_delegate`
--

DROP TABLE IF EXISTS `voter_delegate`;
CREATE TABLE `voter_delegate` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `user_code` varchar(20) default NULL,
  `voter_id` int(10) unsigned default NULL,
  `delegate_id` int(10) unsigned NOT NULL,
  `constituency_id` int(10) unsigned NOT NULL default '0',
  `priority` int(10) unsigned NOT NULL default '1',
  `time_delegate_chosen` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
ALTER TABLE `dd_anders`.`voter_delegate`
  ADD FOREIGN KEY (delegate_id) REFERENCES delegate(`id`);

--
-- Dumping data for table `voter_delegate`
--
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
  `membership_vote_id` int(10) unsigned NOT NULL default '0',
  `propose_time` int(10) unsigned NOT NULL default '0',
  `private_forum_id` int(10) unsigned default NULL,
  PRIMARY KEY  (`id`),
  FULLTEXT KEY `search` (`title`,`description`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroup`
--
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroup_candidate_support`
--
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroup_member`
--
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `workgroup_member_exclude`
--

DROP TABLE IF EXISTS `accounting`;
CREATE TABLE `accounting` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `type_of_transaction` VARCHAR(45) NOT NULL,
  `amount` FLOAT NOT NULL,
  `timestamp_accounting` INTEGER UNSIGNED NOT NULL,
  `timestamp_insertion` INTEGER UNSIGNED NOT NULL,
  `user_id` INTEGER UNSIGNED,
  `comment_from_bank` VARCHAR(255),
  `comment_from_admin` VARCHAR(255),
  PRIMARY KEY (`id`)
) ENGINE = InnoDB DEFAULT CHARSET=latin1;

--
-- Definition of table `user_password_reset_token`
--
DROP TABLE IF EXISTS `user_password_reset_token`;
CREATE TABLE `user_password_reset_token` (
  `reset_token` varchar(20) NOT NULL,
  `user_id` INTEGER UNSIGNED NOT NULL,
  `timestamp_insertion` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY  (`reset_token`)
) ENGINE=MyISAM AUTO_INCREMENT=221 DEFAULT CHARSET=latin1;


/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
