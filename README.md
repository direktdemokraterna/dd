![Alt text](http://direktdemokraterna.se/wp-content/uploads/2014/06/direktdemokraterna-logotyp.png "Direktdemokraternas Medlemsystem")

#Direktdemokraternas Medlemssystem

Här beskrivs det medlemssystem för Direktdemokraterna som varit under utveckling sedan januari förra året. Beslut om byte av medlemssystem kommer att tas i vårt nuvarande Medlemsforum när systemet och medlemmarna är redo för det.

##För versionshantering används GitHub

* <https://github.com/direktdemokraterna/dd>
* <https://github.com/direktdemokraterna/dd_anon>

Utvecklare: Joakim Sigvald, Anders Lönnfält, Daniel Kihlgren och Peter Hjorthammar

#Beskrivning

Detaljerad beskrivning av projektet

https://docs.google.com/document/d/1pn4kcZWrJZh8nZEder-oDbGRM67DvYZpQIrNTEIFjIk/edit

#Projekt

Projektmodellen är KanBan.

Det finns även en board som beskriver projektet:
https://trello.com/b/Si4VO1a3/dd-medlemssystem-projekthantering

Trello används för projekthantering
https://trello.com/b/oiTQ4yni/dd-medlemssystem-utveckling

Utvecklingstavlan är uppdelad i stegen:
* Idéer
* Utvecklingspunkter
* Omstrukturering
* Brister
* Buggar
* Under utveckling
* Granskning
* Test
* Klart
* Ingen åtgärd

# Utveckling via docker

Build docker image

``docker build -t dd/dd_image .``

Start docker container

``docker run --name dd_web -d -p 8080:80 dd/dd_image``

Set up database in docker container this should be run inside container

``./install.sh``

#Feedback

Medlemmar kan ge följande feedback på systemet via följande länk:

https://docs.google.com/spreadsheets/d/1EM-6HONBCUbahUX1Vzxuz-Fq_-Bw3MqAQbZtUtxvT3A/edit?usp=sharing

* (BUG)Bugg
* (FRÅ)Fråga
* (FÖR)Förändringsförslag
* (KOM)Kommentar
