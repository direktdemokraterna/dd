![Alt text](http://direktdemokraterna.se/wp-content/uploads/2014/06/direktdemokraterna-logotyp.png "Direktdemokraternas Medlemsystem")

#Direktdemokraternas Medlemssystem
----

H�r beskrivs det medlemssystem f�r Direktdemokraterna som varit under utveckling sedan januari f�rra �ret. Beslut om byte av medlemssystem kommer att tas i v�rt nuvarande Medlemsforum n�r systemet och medlemmarna �r redo f�r det.

##F�r versionshantering anv�nds GitHub
----

* <https://github.com/anderslonnfalt/dd>
* <https://github.com/anderslonnfalt/dd_anon>

Utvecklare: Joakim Sigvald och Anders L�nnf�lt

#Demo
Applikationen kan k�ras f�r test p� adressen:
http://198.50.180.191/master/

#Beskrivning
------------
Detaljerad beskrivning av projektet

https://docs.google.com/document/d/1pn4kcZWrJZh8nZEder-oDbGRM67DvYZpQIrNTEIFjIk/edit

#Projekt
------------
Projektmodellen �r KanBan.

Det finns �ven en board som beskriver projektet:
https://trello.com/b/Si4VO1a3/dd-medlemssystem-projekthantering

Trello anv�nds f�r projekthantering
https://trello.com/b/oiTQ4yni/dd-medlemssystem-utveckling

Utvecklingstavlan �r uppdelad i stegen:
* Id�er
* Utvecklingspunkter
* Omstrukturering
* Brister
* Buggar
* Under utveckling
* Granskning
* Test
* Klart
* Ingen �tg�rd

# Utveckling via docker
Build docker image

``docker build -t dd/dd_image .``

Start docker container

``docker run --name dd_web -d -p 8080:80 dd/dd_image``

Set up database in docker container this should be run inside container

``./install.sh``

#Feedback
------------
Medlemmar kan ge f�ljande feedback p� systemet via f�ljande l�nk:

https://docs.google.com/spreadsheets/d/1EM-6HONBCUbahUX1Vzxuz-Fq_-Bw3MqAQbZtUtxvT3A/edit?usp=sharing

* (BUG)Bugg
* (FR�)Fr�ga
* (F�R)F�r�ndringsf�rslag
* (KOM)Kommentar

Utvecklare: Joakim Sigvald och Anders L�nnf�lt