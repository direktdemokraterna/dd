<?php

mysql_connect("localhost") or die("could not connect to localhost");
mysql_create_db("dd") or die("Could not create database");
mysql_select_db("dd") or die("Could not select database");

$query = "CREATE TABLE `dd`.`kommuner` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `kommun` VARCHAR(45) NOT NULL,
  `lan` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);

// POPULATING kommuner
mysql_query("INSERT INTO kommuner VALUES (1, 'Ale', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (2, 'Alingsås', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (3, 'Alvesta', 'Kronoberg ')");
mysql_query("INSERT INTO kommuner VALUES (4, 'Aneby', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (5, 'Arboga', 'Västmanland ')");
mysql_query("INSERT INTO kommuner VALUES (6, 'Arjeplog', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (7, 'Arvidsjaur', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (8, 'Arvika', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (9, 'Askersund', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (10, 'Avesta', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (11, 'Bengtsfors', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (12, 'Berg', 'Jämtland ')");
mysql_query("INSERT INTO kommuner VALUES (13, 'Bjurholm', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (14, 'Bjuv', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (15, 'Boden', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (16, 'Bollebygd', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (17, 'Bollnäs', 'Gävleborg ')");
mysql_query("INSERT INTO kommuner VALUES (18, 'Borgholm', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (19, 'Borlänge', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (20, 'Borås', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (21, 'Botkyrka', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (22, 'Boxholm', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (23, 'Bromölla', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (24, 'Bräcke', 'Jämtland ')");
mysql_query("INSERT INTO kommuner VALUES (25, 'Burlöv', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (26, 'Båstad', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (27, 'Dals-Ed', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (28, 'Danderyd', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (29, 'Degerfors', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (30, 'Dorotea', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (31, 'Eda', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (32, 'Ekerö', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (33, 'Eksjö', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (34, 'Emmaboda', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (35, 'Enköping', 'Uppsala ')");
mysql_query("INSERT INTO kommuner VALUES (36, 'Eskilstuna', 'Södermanland ')");
mysql_query("INSERT INTO kommuner VALUES (37, 'Eslöv', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (38, 'Essunga', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (39, 'Fagersta', 'Västmanland ')");
mysql_query("INSERT INTO kommuner VALUES (40, 'Falkenberg', 'Halland ')");
mysql_query("INSERT INTO kommuner VALUES (41, 'Falköping', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (42, 'Falu', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (43, 'Filipstad', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (44, 'Finspång', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (45, 'Flen', 'Södermanland ')");
mysql_query("INSERT INTO kommuner VALUES (46, 'Forshaga', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (47, 'Färgelanda', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (48, 'Gagnef', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (49, 'Gislaved', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (50, 'Gnesta', 'Södermanland ')");
mysql_query("INSERT INTO kommuner VALUES (51, 'Gnosjö', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (52, 'Gotland', 'Gotland ')");
mysql_query("INSERT INTO kommuner VALUES (53, 'Grums', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (54, 'Grästorp', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (55, 'Gullspång', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (56, 'Gällivare', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (57, 'Gävle', 'Gävleborg ')");
mysql_query("INSERT INTO kommuner VALUES (58, 'Göteborg', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (59, 'Götene', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (60, 'Habo', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (61, 'Hagfors', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (62, 'Hallsberg', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (63, 'Hallstahammar', 'Västmanland ')");
mysql_query("INSERT INTO kommuner VALUES (64, 'Halmstad', 'Halland ')");
mysql_query("INSERT INTO kommuner VALUES (65, 'Hammarö', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (66, 'Haninge', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (67, 'Haparanda', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (68, 'Heby', 'Uppsala ')");
mysql_query("INSERT INTO kommuner VALUES (69, 'Hedemora', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (70, 'Helsingborg', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (71, 'Herrljunga', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (72, 'Hjo', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (73, 'Hofors', 'Gävleborg ')");
mysql_query("INSERT INTO kommuner VALUES (74, 'Huddinge', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (75, 'Hudiksvall', 'Gävleborg ')");
mysql_query("INSERT INTO kommuner VALUES (76, 'Hultsfred', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (77, 'Hylte', 'Halland ')");
mysql_query("INSERT INTO kommuner VALUES (78, 'Håbo', 'Uppsala ')");
mysql_query("INSERT INTO kommuner VALUES (79, 'Hällefors', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (80, 'Härjedalen', 'Jämtland ')");
mysql_query("INSERT INTO kommuner VALUES (81, 'Härnösand', 'Västernorrland ')");
mysql_query("INSERT INTO kommuner VALUES (82, 'Härryda', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (83, 'Hässleholm', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (84, 'Höganäs', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (85, 'Högsby', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (86, 'Hörby', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (87, 'Höör', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (88, 'Jokkmokk', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (89, 'Järfälla', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (90, 'Jönköping', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (91, 'Kalix', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (92, 'Kalmar', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (93, 'Karlsborg', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (94, 'Karlshamn', 'Blekinge ')");
mysql_query("INSERT INTO kommuner VALUES (95, 'Karlskoga', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (96, 'Karlskrona', 'Blekinge ')");
mysql_query("INSERT INTO kommuner VALUES (97, 'Karlstad', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (98, 'Katrineholm', 'Södermanland ')");
mysql_query("INSERT INTO kommuner VALUES (99, 'Kil', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (100, 'Kinda', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (101, 'Kiruna', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (102, 'Klippan', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (103, 'Knivsta', 'Uppsala ')");
mysql_query("INSERT INTO kommuner VALUES (104, 'Kramfors', 'Västernorrland ')");
mysql_query("INSERT INTO kommuner VALUES (105, 'Kristianstad', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (106, 'Kristinehamn', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (107, 'Krokom', 'Jämtland ')");
mysql_query("INSERT INTO kommuner VALUES (108, 'Kumla', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (109, 'Kungsbacka', 'Halland ')");
mysql_query("INSERT INTO kommuner VALUES (110, 'Kungsör', 'Västmanland ')");
mysql_query("INSERT INTO kommuner VALUES (111, 'Kungälv', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (112, 'Kävlinge', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (113, 'Köping', 'Västmanland ')");
mysql_query("INSERT INTO kommuner VALUES (114, 'Laholm', 'Halland ')");
mysql_query("INSERT INTO kommuner VALUES (115, 'Landskrona', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (116, 'Laxå', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (117, 'Lekeberg', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (118, 'Leksand', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (119, 'Lerum', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (120, 'Lessebo', 'Kronoberg ')");
mysql_query("INSERT INTO kommuner VALUES (121, 'Lidingö', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (122, 'Lidköping', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (123, 'Lilla Edet', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (124, 'Lindesberg', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (125, 'Linköping', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (126, 'Ljungby', 'Kronoberg ')");
mysql_query("INSERT INTO kommuner VALUES (127, 'Ljusdal', 'Gävleborg ')");
mysql_query("INSERT INTO kommuner VALUES (128, 'Ljusnarsberg', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (129, 'Lomma', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (130, 'Ludvika', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (131, 'Luleå', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (132, 'Lund', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (133, 'Lycksele', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (134, 'Lysekil', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (135, 'Malmö', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (136, 'Malung-Sälen', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (137, 'Malå', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (138, 'Mariestad', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (139, 'Mark', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (140, 'Markaryd', 'Kronoberg ')");
mysql_query("INSERT INTO kommuner VALUES (141, 'Mellerud', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (142, 'Mjölby', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (143, 'Mora', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (144, 'Motala', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (145, 'Mullsjö', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (146, 'Munkedal', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (147, 'Munkfors', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (148, 'Mölndal', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (149, 'Mönsterås', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (150, 'Mörbylånga', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (151, 'Nacka', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (152, 'Nora', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (153, 'Norberg', 'Västmanland ')");
mysql_query("INSERT INTO kommuner VALUES (154, 'Nordanstig', 'Gävleborg ')");
mysql_query("INSERT INTO kommuner VALUES (155, 'Nordmaling', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (156, 'Norrköping', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (157, 'Norrtälje', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (158, 'Norsjö', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (159, 'Nybro', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (160, 'Nykvarn', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (161, 'Nyköping', 'Södermanland ')");
mysql_query("INSERT INTO kommuner VALUES (162, 'Nynäshamn', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (163, 'Nässjö', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (164, 'Ockelbo', 'Gävleborg ')");
mysql_query("INSERT INTO kommuner VALUES (165, 'Olofström', 'Blekinge ')");
mysql_query("INSERT INTO kommuner VALUES (166, 'Orsa', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (167, 'Orust', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (168, 'Osby', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (169, 'Oskarshamn', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (170, 'Ovanåker', 'Gävleborg ')");
mysql_query("INSERT INTO kommuner VALUES (171, 'Oxelösund', 'Södermanland ')");
mysql_query("INSERT INTO kommuner VALUES (172, 'Pajala', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (173, 'Partille', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (174, 'Perstorp', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (175, 'Piteå', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (176, 'Ragunda', 'Jämtland ')");
mysql_query("INSERT INTO kommuner VALUES (177, 'Robertsfors', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (178, 'Ronneby', 'Blekinge ')");
mysql_query("INSERT INTO kommuner VALUES (179, 'Rättvik', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (180, 'Sala', 'Västmanland ')");
mysql_query("INSERT INTO kommuner VALUES (181, 'Salem', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (182, 'Sandviken', 'Gävleborg ')");
mysql_query("INSERT INTO kommuner VALUES (183, 'Sigtuna', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (184, 'Simrishamn', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (185, 'Sjöbo', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (186, 'Skara', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (187, 'Skellefteå', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (188, 'Skinnskatteberg', 'Västmanland ')");
mysql_query("INSERT INTO kommuner VALUES (189, 'Skurup', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (190, 'Skövde', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (191, 'Smedjebacken', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (192, 'Sollefteå', 'Västernorrland ')");
mysql_query("INSERT INTO kommuner VALUES (193, 'Sollentuna', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (194, 'Solna', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (195, 'Sorsele', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (196, 'Sotenäs', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (197, 'Staffanstorp', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (198, 'Stenungsund', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (199, 'Stockholm', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (200, 'Storfors', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (201, 'Storuman', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (202, 'Strängnäs', 'Södermanland ')");
mysql_query("INSERT INTO kommuner VALUES (203, 'Strömstad', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (204, 'Strömsund', 'Jämtland ')");
mysql_query("INSERT INTO kommuner VALUES (205, 'Sundbyberg', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (206, 'Sundsvall', 'Västernorrland ')");
mysql_query("INSERT INTO kommuner VALUES (207, 'Sunne', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (208, 'Surahammar', 'Västmanland ')");
mysql_query("INSERT INTO kommuner VALUES (209, 'Svalöv', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (210, 'Svedala', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (211, 'Svenljunga', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (212, 'Säffle', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (213, 'Säter', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (214, 'Sävsjö', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (215, 'Söderhamn', 'Gävleborg ')");
mysql_query("INSERT INTO kommuner VALUES (216, 'Söderköping', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (217, 'Södertälje', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (218, 'Sölvesborg', 'Blekinge ')");
mysql_query("INSERT INTO kommuner VALUES (219, 'Tanum', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (220, 'Tibro', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (221, 'Tidaholm', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (222, 'Tierp', 'Uppsala ')");
mysql_query("INSERT INTO kommuner VALUES (223, 'Timrå', 'Västernorrland ')");
mysql_query("INSERT INTO kommuner VALUES (224, 'Tingsryd', 'Kronoberg ')");
mysql_query("INSERT INTO kommuner VALUES (225, 'Tjörn', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (226, 'Tomelilla', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (227, 'Torsby', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (228, 'Torsås', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (229, 'Tranemo', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (230, 'Tranås', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (231, 'Trelleborg', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (232, 'Trollhättan', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (233, 'Trosa', 'Södermanland ')");
mysql_query("INSERT INTO kommuner VALUES (234, 'Tyresö', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (235, 'Täby', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (236, 'Töreboda', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (237, 'Uddevalla', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (238, 'Ulricehamn', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (239, 'Umeå', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (240, 'Upplands Väsby', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (241, 'Upplands-Bro', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (242, 'Uppsala', 'Uppsala ')");
mysql_query("INSERT INTO kommuner VALUES (243, 'Uppvidinge', 'Kronoberg ')");
mysql_query("INSERT INTO kommuner VALUES (244, 'Vadstena', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (245, 'Vaggeryd', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (246, 'Valdemarsvik', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (247, 'Vallentuna', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (248, 'Vansbro', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (249, 'Vara', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (250, 'Varberg', 'Halland ')");
mysql_query("INSERT INTO kommuner VALUES (251, 'Vaxholm', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (252, 'Vellinge', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (253, 'Vetlanda', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (254, 'Vilhelmina', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (255, 'Vimmerby', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (256, 'Vindeln', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (257, 'Vingåker', 'Södermanland ')");
mysql_query("INSERT INTO kommuner VALUES (258, 'Vårgårda', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (259, 'Vänersborg', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (260, 'Vännäs', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (261, 'Värmdö', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (262, 'Värnamo', 'Jönköping ')");
mysql_query("INSERT INTO kommuner VALUES (263, 'Västervik', 'Kalmar ')");
mysql_query("INSERT INTO kommuner VALUES (264, 'Västerå', 'Västmanland ')");
mysql_query("INSERT INTO kommuner VALUES (265, 'Växjö', 'Kronoberg ')");
mysql_query("INSERT INTO kommuner VALUES (266, 'Ydre', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (267, 'Ystad', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (268, 'Åmål', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (269, 'Ånge', 'Västernorrland ')");
mysql_query("INSERT INTO kommuner VALUES (270, 'Åre', 'Jämtland ')");
mysql_query("INSERT INTO kommuner VALUES (271, 'Årjäng', 'Värmland ')");
mysql_query("INSERT INTO kommuner VALUES (272, 'Åsele', 'Västerbotten ')");
mysql_query("INSERT INTO kommuner VALUES (273, 'Åstorp', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (274, 'Åtvidaberg', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (275, 'Älmhult', 'Kronoberg ')");
mysql_query("INSERT INTO kommuner VALUES (276, 'Älvdalen', 'Dalarna ')");
mysql_query("INSERT INTO kommuner VALUES (277, 'Älvkarleby', 'Uppsala ')");
mysql_query("INSERT INTO kommuner VALUES (278, 'Älvsbyn', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (279, 'Ängelholm', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (280, 'Öckerö', 'Västra Götaland ')");
mysql_query("INSERT INTO kommuner VALUES (281, 'Ödeshög', 'Östergötland ')");
mysql_query("INSERT INTO kommuner VALUES (282, 'Örebro', 'Örebro ')");
mysql_query("INSERT INTO kommuner VALUES (283, 'Örkelljunga', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (284, 'Örnsköldsvik', 'Västernorrland ')");
mysql_query("INSERT INTO kommuner VALUES (285, 'Östersund', 'Jämtland ')");
mysql_query("INSERT INTO kommuner VALUES (286, 'Österåker', 'Stockholm ')");
mysql_query("INSERT INTO kommuner VALUES (287, 'Östhammar', 'Uppsala ')");
mysql_query("INSERT INTO kommuner VALUES (288, 'Östra Göinge', 'Skåne ')");
mysql_query("INSERT INTO kommuner VALUES (289, 'Överkalix', 'Norrbotten ')");
mysql_query("INSERT INTO kommuner VALUES (290, 'Övertorneå', 'Norrbotten')");



$query = "CREATE TABLE `dd`.`users` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `username` VARCHAR(45) NOT NULL,
  `password` VARCHAR(128) NOT NULL,
  `remember_me_token` VARCHAR(128) DEFAULT null,
  `registration_time` INTEGER UNSIGNED NOT NULL,
  `deletion_time` INTEGER UNSIGNED DEFAULT null,
  `last_login_time` INTEGER UNSIGNED DEFAULT null,
  `last_activity_time` INTEGER UNSIGNED DEFAULT null,
  `first_name` VARCHAR(45) DEFAULT '',
  `last_name` VARCHAR(45) DEFAULT '',
  `street_address` VARCHAR(45) DEFAULT '',
  `zip_code` VARCHAR(10) DEFAULT '',
  `city_address` VARCHAR(45) DEFAULT '',
  `county` VARCHAR(45) DEFAULT '',
  `region` VARCHAR(45) DEFAULT '',
  `social_security_number` VARCHAR(13) DEFAULT '',
  `email` VARCHAR(45) NOT NULL,
  `telephone1` VARCHAR(20) DEFAULT '',
  `telephone2` VARCHAR(20) DEFAULT '',
  `skype_name` VARCHAR(45) DEFAULT '',
  `show_email` TINYINT(1) UNSIGNED NOT NULL DEFAULT 1,
  `show_telephone` TINYINT(1) UNSIGNED NOT NULL DEFAULT 1,
  `show_skype` TINYINT(1) UNSIGNED NOT NULL DEFAULT 1,
  `number_of_posts` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `number_of_topics` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `membership_fee_payed` INTEGER UNSIGNED DEFAULT null,
  `last_contact_with_admin` INTEGER UNSIGNED DEFAULT null,
  `acting_as_delegate` TINYINT(1) UNSIGNED NOT NULL DEFAULT 0,
  `user_role` INTEGER UNSIGNED NOT NULL DEFAULT 2,
  `admin_notes` VARCHAR(255) DEFAULT '',
  `image` VARCHAR(90) NOT NULL DEFAULT 'no_image.png',
  `description` TEXT DEFAULT '',
  PRIMARY KEY (`id`), 
  FULLTEXT KEY 'search' ('first_name', 'last_name', 'description')
)
ENGINE = MyISAM;";

mysql_query($query);


$query = "CREATE TABLE `dd`.`membership_fees` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` INTEGER UNSIGNED NOT NULL,
  `timestamp` INTEGER UNSIGNED NOT NULL,
  `sum` INTEGER UNSIGNED NOT NULL,
  `to_account_id` INTEGER UNSIGNED,
  `message` VARCHAR(255),
  `payment_for_year` INTEGER(4) UNSIGNED,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);


$query = "CREATE TABLE `dd`.`admin_roles` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `title` VARCHAR(90) NOT NULL,
  `description` TEXT,
  `type` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);


$query = "CREATE TABLE `dd`.`admin_roles_users` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `admin_role_id` INTEGER UNSIGNED NOT NULL,
  `user_id` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);


// FILLING IN DEFAULT ADMIN ROLES
mysql_query("INSERT INTO admin_roles VALUES (1, 'Superadmin', '', 'superadmin')");
mysql_query("INSERT INTO admin_roles VALUES (2, 'Medlemsadministratör', '', 'member_admin')");
mysql_query("INSERT INTO admin_roles VALUES (3, 'Forumadministratör', '', 'forum_admin')");
mysql_query("INSERT INTO admin_roles VALUES (4, 'Valadministratör', '', 'vote_admin')");
mysql_query("INSERT INTO admin_roles VALUES (5, 'Kassör', '', 'treasurer')");


// CREATING DEFAULT ADMIN USER
mysql_query("INSERT INTO users (id, username, first_name, password, registration_time, email, show_email) VALUES (1, 'admin', 'Admin', '$2a$08$e.8wjns479C6my6mBkWBUey/cCK5iY3zO1e5dO15AkJgCi6mVVA.C', " . time() . ", 'admin@direktdemokraterna.se', 0)");
mysql_query("INSERT INTO admin_roles_users VALUES (null, 1, 1)");


$query = "CREATE TABLE `dd`.`messages` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `sender_id` INTEGER UNSIGNED NOT NULL,
  `recipient_id` INTEGER UNSIGNED NOT NULL,
  `sent_time` INTEGER UNSIGNED NOT NULL,
  `read_time` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `deleted_by_sender` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `deleted_by_recipient` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `title` VARCHAR(90) NOT NULL DEFAULT '',
  `content` TEXT NOT NULL DEFAULT '',
  PRIMARY KEY (`id`), 
  FULLTEXT KEY 'search' ('title', 'content')
)
ENGINE = MyISAM;";

mysql_query($query);



$query = "CREATE TABLE `dd`.`kommuner` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `kommun` VARCHAR(45) NOT NULL,
  `lan` VARCHAR(45) NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);



$query = "CREATE TABLE `dd`.`workgroups` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `title` VARCHAR(90) NOT NULL,
  `description` TEXT NOT NULL,
  `is_active` TINYINT(1) UNSIGNED NOT NULL DEFAULT 0,
  `number_of_members` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `propose_time` INTEGER UNSIGNED NOT NULL,
  `create_time` INTEGER UNSIGNED DEFAULT null,
  `create_user` INTEGER UNSIGNED NOT NULL,
  `public_forum_id` INTEGER UNSIGNED NOT NULL,
  `private_forum_id` INTEGER UNSIGNED NOT NULL,
  `is_restricted` TINYINT(1) UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`), 
  FULLTEXT KEY 'search' ('title', 'description')
)
ENGINE = MyISAM;"

mysql_query($query);


// FILLING IN DEFAULT WORKGROUPS
mysql_query("INSERT INTO workgroups VALUES (1, 'Styrelsen', 'Styrelsen har det yttersta ansvaret för den löpande driften av Direktdemokraterna.', 1, 0, 0, 0, null, null, null, 1)");



$query = "CREATE TABLE `dd`.`workgroups_members` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `workgroup_id` INTEGER UNSIGNED NOT NULL,
  `user_id` INTEGER UNSIGNED NOT NULL,
  `member_since` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);




$query = "CREATE TABLE `dd`.`workgroups_candidates` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `workgroup_id` INTEGER UNSIGNED NOT NULL,
  `candidate_id` INTEGER UNSIGNED NOT NULL,
  `number_of_supporters` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);




$query = "CREATE TABLE `dd`.`workgroups_candidates_support` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `workgroup_id` INTEGER UNSIGNED NOT NULL,
  `candidate_id` INTEGER UNSIGNED NOT NULL,
  `supporter_id` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);




$query = "CREATE TABLE `dd`.`workgroups_members_exclude` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `workgroup_id` INTEGER UNSIGNED NOT NULL,
  `excluded_id` INTEGER UNSIGNED NOT NULL,
  `excluder_id` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);




$query = "CREATE TABLE `dd`.`categories` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `title` VARCHAR(45) NOT NULL,
  `description` TEXT NOT NULL DEFAULT '',
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);


// FILLING IN DEFAULT CATEGORIES
mysql_query("INSERT INTO categories VALUES (1, 'Allmänt', 'Allmänna frågor.')");
mysql_query("INSERT INTO categories VALUES (2, 'Valkretsar', 'Nya omröstningar och förslag presenteras i dessa forum.')");
mysql_query("INSERT INTO categories VALUES (3, 'Administration', 'Forum för administratörer.')");
mysql_query("INSERT INTO categories VALUES (8, 'Interna arbetsgruppsforum', 'Dessa forum har bara medlemmarna i den respektive arbetsgrupperna tillgång till.')");
mysql_query("INSERT INTO categories VALUES (9, 'Arbetsgrupper', 'Publika forum för de olika arbetsgrupperna.')");


$query = "CREATE TABLE `dd`.`forums` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `category_id` INTEGER UNSIGNED NOT NULL,
  `title` VARCHAR(45) NOT NULL,
  `description` TEXT NOT NULL DEFAULT '',
  `last_posted_time` INTEGER UNSIGNED,
  `last_posted_post` INTEGER UNSIGNED,
  `number_of_topics` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `number_of_posts` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `access_type` VARCHAR(12) NOT NULL DEFAULT 'public',
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);

// FILLING IN DEFAULT FORUMS
mysql_query("INSERT INTO forums VALUES (1, 1, 'Allmänt', '', null, null, 0, 0, 'public')");
// FILLING IN CONSTITUENCY FORÛMS 
mysql_query("INSERT INTO forums VALUES (null, 2, 'DD Riks', '', null, null, 0, 0, 'public')");



$query = "CREATE TABLE `dd`.`forums_users` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` INTEGER UNSIGNED NOT NULL,
  `forum_id` INTEGER UNSIGNED NOT NULL,
  `access_type` TINYINT(1) UNSIGNED NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);




$query = "CREATE TABLE `dd`.`posts` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `topic_id` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `user_id` INTEGER UNSIGNED NOT NULL,
  `forum_id` INTEGER UNSIGNED NOT NULL,
  `is_topic` TINYINT(1) UNSIGNED NOT NULL DEFAULT 0,
  `posted_time` INTEGER UNSIGNED NOT NULL,
  `last_edited_time` INTEGER UNSIGNED DEFAULT null,
  `title` VARCHAR(90) NOT NULL,
  `content` TEXT NOT NULL,
  PRIMARY KEY (`id`), 
  FULLTEXT KEY 'search' ('title', 'content')
)
ENGINE = MyISAM;";

mysql_query($query);




$query = "CREATE TABLE `dd`.`error_messages` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` INTEGER UNSIGNED NOT NULL,
  `message` VARCHAR(90) NOT NULL,
  `color` VARCHAR(9) NOT NULL DEFAULT 'green',
  `timestamp` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);




$query = "CREATE TABLE `dd`.`post_reports` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `post_id` INTEGER UNSIGNED NOT NULL,
  `reporter_id` INTEGER UNSIGNED NOT NULL,
  `time_report_filed` INTEGER UNSIGNED NOT NULL,
  `argument` TEXT NOT NULL,
  `time_resolved` INTEGER UNSIGNED NOT NULL,
  `resolved_by_id` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);





$query = "CREATE TABLE `dd`.`calendar` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `timestamp` INTEGER UNSIGNED NOT NULL,
  `year` INTEGER(4) UNSIGNED NOT NULL,
  `month` INTEGER(2) UNSIGNED NOT NULL,
  `day` INTEGER(2) UNSIGNED NOT NULL,
  `time` VARCHAR(20) NOT NULL
  `timestamp_added` INTEGER UNSIGNED NOT NULL,
  `added_by_user` INTEGER UNSIGNED NOT NULL,
  `location` VARCHAR(45) NOT NULL,
  `title` VARCHAR(90) NOT NULL,
  `content` TEXT NOT NULL,
  PRIMARY KEY (`id`), 
  FULLTEXT KEY 'search' ('title', 'content')
)
ENGINE = MyISAM;";

mysql_query($query);





$query = "CREATE TABLE `dd`.`calendar_participants` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `calendar_id` INTEGER UNSIGNED NOT NULL,
  `user_id` INTEGER UNSIGNED NOT NULL,
  `timestamp_registration` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);





$query = "CREATE TABLE `dd`.`user_applications` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `application_filed_time` INTEGER UNSIGNED DEFAULT null,
  `first_name` VARCHAR(45) DEFAULT '',
  `last_name` VARCHAR(45) DEFAULT '',
  `street_address` VARCHAR(45) DEFAULT '',
  `zip_code` VARCHAR(10) DEFAULT '',
  `city_address` VARCHAR(45) DEFAULT '',
  `county` VARCHAR(45) DEFAULT '',
  `region` VARCHAR(45) DEFAULT '',
  `social_security_number` VARCHAR(13) DEFAULT '',
  `email` VARCHAR(45) NOT NULL,
  `telephone1` VARCHAR(20) DEFAULT '',
  `telephone2` VARCHAR(20) DEFAULT '',
  `skype_name` VARCHAR(45) DEFAULT '',
  `membership_fee_payed` INTEGER UNSIGNED DEFAULT null,
  `admin_notes` VARCHAR(255) DEFAULT '',
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);





$query = "CREATE TABLE `dd`.`propositions` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` VARCHAR(20) NOT NULL,
  `created_by_user` INTEGER UNSIGNED,
  `created_by_delegate` INTEGER UNSIGNED,
  `timestamp_created` INTEGER UNSIGNED NOT NULL,
  `timestamp_ended` INTEGER UNSIGNED,
  `constituency_id` INTEGER UNSIGNED NOT NULL,
  `status` VARCHAR(12) NOT NULL DEFAULT 'pending',
  `number_of_supporters` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `number_of_enemies` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `title` VARCHAR(90) NOT NULL,
  `description` TEXT NOT NULL,
  `forum_topic_id` INTEGER UNSIGNED,
  PRIMARY KEY (`id`),
  FULLTEXT KEY `search`(`title`, `description`)
)
ENGINE = MyISAM;";

mysql_query($query);






$query = "CREATE TABLE `dd`.`propositions_support` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `proposition_id` INTEGER UNSIGNED NOT NULL,
  `user_code` VARCHAR(20) NOT NULL,
  `delegate_id` INTEGER UNSIGNED,
  `support_type` VARCHAR(7) NOT NULL DEFAULT 'support',
  `time_ballot_placed` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);






$query = "CREATE TABLE `dd`.`votes` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `type` VARCHAR(20) NOT NULL,
  `from_proposition_id` INTEGER UNSIGNED,
  `timestamp_created` INTEGER UNSIGNED NOT NULL,
  `timestamp_delegate_ended` INTEGER UNSIGNED,
  `timestamp_ended` INTEGER UNSIGNED,
  `constituency_id` INTEGER UNSIGNED NOT NULL,
  `status` VARCHAR(10) NOT NULL DEFAULT 'active',
  `title` VARCHAR(90) NOT NULL,
  `description` TEXT NOT NULL,
  `number_of_alternatives` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `number_of_ballots` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `number_of_direct_ballots` INTEGER UNSIGNED NOT NULL DEFAULT 0,
  `forum_topic_id` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`),
  FULLTEXT KEY `search`(`title`, `description`)
)
ENGINE = MyISAM;";

mysql_query($query);






$query = "CREATE TABLE `dd`.`votes_alternatives` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `vote_id` INTEGER UNSIGNED NOT NULL,
  `added_by_user` INTEGER UNSIGNED,
  `added_by_delegate` INTEGER UNSIGNED,
  `timestamp_added` INTEGER UNSIGNED NOT NULL,
  `alternative_title` VARCHAR(90) NOT NULL,
  `alternative_description` TEXT NOT NULL,
  `alternative_user_id` INTEGER UNSIGNED,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);






$query = "CREATE TABLE `dd`.`delegates` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `title` VARCHAR(90) NOT NULL,
  `description` TEXT NOT NULL,
  `timestamp_created` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);






$query = "CREATE TABLE `dd`.`delegates_users` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `delegate_id` INTEGER UNSIGNED NOT NULL,
  `user_id` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);






$query = "CREATE TABLE `dd`.`constituencies` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `title` VARCHAR(90) NOT NULL,
  `description` TEXT NOT NULL,
  `number_of_voters` INTEGER UNSIGNED,
  `forum_id` INTEGER UNSIGNED NOT NULL,
  `access_type` VARCHAR(12) NOT NULL DEFAULT 'public',
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);



// FILLING IN LOCAL FORUMS AND CONSTITUENCIES
$kommuner = mysql_fetch_array(mysql_query("SELECT kommun FROM kommuner ORDER BY kommun ASC"));
foreach($kommuner as $row){
  mysql_query("INSERT INTO forums VALUES (null, 2, '$row[kommun]', null, null, 0, 0, 'local_county')");
  $insert_id = mysql_insert_id();
  mysql_query("INSERT INTO constituencies VALUES (null, '$row[kommun]', 0, $insert_id, 'local_county')");
}
$lan = mysql_fetch_array(mysql_query("SELECT DISTINCT lan FROM kommuner ORDER BY lan ASC"));
foreach($lan as $row){
  mysql_query("INSERT INTO forums VALUES (null, 2, '$row[lan]', null, null, 0, 0, 'local_region')");
  $insert_id = mysql_insert_id();
  mysql_query("INSERT INTO constituencies VALUES (null, '$row[lan]', 0, $insert_id, 'local_region')");
}




$query = "CREATE TABLE `dd`.`constituencies_users` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `constituency_id` INTEGER UNSIGNED NOT NULL,
  `user_id` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);






$query = "CREATE TABLE `dd`.`constituencies_delegates` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `constituency_id` INTEGER UNSIGNED NOT NULL,
  `delegate_id` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);





$query = "CREATE TABLE `dd`.`ballots` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `vote_id` INTEGER UNSIGNED NOT NULL,
  `constituency_id` INTEGER UNSIGNED NOT NULL,
  `ballot_alternative` VARCHAR(9),
  `prio_ranking` TEXT DEFAULT NULL,
  `median_vote_value` FLOAT,
  `user_code` VARCHAR(20),
  `voter_is_delegate_id` INTEGER UNSIGNED,
  `delegate_id` INTEGER UNSIGNED,
  `delegation_level` INTEGER UNSIGNED,
  `delegate_priority` INTEGER UNSIGNED,
  `time_ballot_placed` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);




$query = "CREATE TABLE `dd`.`delegate_ballots` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `vote_id` INTEGER UNSIGNED NOT NULL,
  `constituency_id` INTEGER UNSIGNED NOT NULL,
  `ballot_alternative` VARCHAR(9),
  `vote_alternative_id` INTEGER UNSIGNED,
  `priority` INTEGER UNSIGNED,
  `median_vote_value` FLOAT,
  `ballot_owner_id` INTEGER UNSIGNED NOT NULL,
  `delegate_id` INTEGER UNSIGNED,
  `delegation_level` INTEGER UNSIGNED,
  `delegate_priority` INTEGER UNSIGNED,
  `time_ballot_placed` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);




$query = "CREATE TABLE `dd`.`voters_delegates` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `delegate_id` INTEGER UNSIGNED NOT NULL,
  `user_code` VARCHAR(20),
  `voter_id_delegate_id` INTEGER UNSIGNED,
  `constituency_id` INTEGER UNSIGNED NOT NULL,
  `priority` INTEGER UNSIGNED NOT NULL DEFAULT 1,
  `time_delegate_chosen` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);




$query = "CREATE TABLE `dd`.`delegates_delegates` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `delegate_id` INTEGER UNSIGNED NOT NULL,
  `delegand_id` INTEGER UNSIGNED NOT NULL,
  `constituency_id` INTEGER UNSIGNED NOT NULL,
  `priority` INTEGER UNSIGNED NOT NULL DEFAULT 1,
  `time_delegate_chosen` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = MyISAM;";

mysql_query($query);




$query = "";

mysql_query($query);




$query = "";

mysql_query($query);




$query = "";

mysql_query($query);




$query = "";

mysql_query($query);




$query = "";

mysql_query($query);





mysql_create_db("dd_anon") or die("Could not create database");
mysql_select_db("dd_anon") or die("Could not select database");



$query = "CREATE TABLE `dd_anon`.`users` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `user_id` INTEGER UNSIGNED NOT NULL,
  `active_user_code` VARCHAR(20) NOT NULL,
  `passive_user_code1` VARCHAR(20) NOT NULL,
  `passive_user_code2` VARCHAR(20) NOT NULL,
  `passive_user_code3` VARCHAR(20) NOT NULL,
  `timestamp_last_login` INTEGER UNSIGNED,
  `timestamp_last_activity` INTEGER UNSIGNED,
  PRIMARY KEY (`id`)
)
ENGINE = InnoDB;";

mysql_query($query);


$query = "CREATE TABLE `dd_anon`.`user_temp_codes` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `temp_code` VARCHAR(45) NOT NULL,
  `user_id` INTEGER UNSIGNED,
  `timestamp_created` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = InnoDB;";

mysql_query($query);




$query = "CREATE TABLE `dd_anon`.`temp_codes_constituencies` (
  `id` INTEGER UNSIGNED NOT NULL AUTO_INCREMENT,
  `temp_code` VARCHAR(45) NOT NULL,
  `constituency_id` INTEGER UNSIGNED NOT NULL,
  `timestamp_created` INTEGER UNSIGNED NOT NULL,
  PRIMARY KEY (`id`)
)
ENGINE = InnoDB;";

mysql_query($query);




