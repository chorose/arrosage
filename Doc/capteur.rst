.. _capteur:

==================================
Systèmes d'arrosage automatique
==================================

Cette page décrit un ensemble de systèmes de monitorage de l'humidité
dans le sol avec arrosage automatique.

Premier montage :
==========================

Ce premier montage tout simple permet d'envoyer par RF 433 la valeur
donnée par la sonde d'humidité dans le sol en utilisant des cartes arduino.

1. Composants
------------------

* Capteur d'humidité dans le sol : DFRobot soil moisture
* Emetteur/récepteur RF : GoTronic
* Carte Arduino Leonardo
* Carte Arduino Ecoduino de DFRobot

2. Montage
----------------

Ce premier montage illustré par la schéma suivant, utilise l'ecoduino pour capter l'humidité du sol
grâce à la sonde et transmettre la valeur en RF 433 à un arduino
(leonardo) équipé d'un récepteur RF 433.

La sonde d'humidité se relie aux pins VCC, GND et A1 de l'ecoduino et
l'émetteur RF aux pins VCC,GND et D0.

Le récepteur RF se connecte aux ports VCC,GND et sur le port
d'interruption 0 (pin 3) du leonardo pour les données (port ``data``
du récepteur).

.. image:: Schémas/montage1.png
  :align: center

3. Programmes
-------------------

Pour les transferts en RF, on utilise de la librairie RCSwitch pour Arduino : https://github.com/sui77/rc-switch

**Capteur/émetteur**
Le code source se trouve à l'adresse suivante :
https://github.com/chorose/arrosage/blob/master/Arduino/sensor/sensor.ino

On commence par l'ensemble des déclarations::
  
  #include <RCSwitch.h>
  RCSwitch mySwitch = RCSwitch();

  int analogInPin = A1;
  int transmitterPin = 0;

Puis on configure les ports dans la partie ``setup()``::
  
  pinMode(analogInPin, INPUT);
  mySwitch.enableTransmit(transmitterPin);

Enfin, la valeur de l'humidité est lue sur le port analogique
correspondant de l'ecoduino et transmise en RF::
  
     int sensorValue = analogRead(analogInPin);
     mySwitch.send(sensorValue, 16);

**Récepteur**

Le code source se trouve à l'adresse suivante :
https://github.com/chorose/arrosage/blob/master/Arduino/receiver/receiver.ino

Dans ce code, on utilise la communication série à des fins de debug.

On commence par les déclarations::
  
  #include <RCSwitch.h>
  RCSwitch mySwitch = RCSwitch();

Puis la configuration du récepteur dans la partie ``setup()``::
  
  mySwitch.enableReceive(0);

Pour la réception de données, il faut d'abord s'assurer que la
connexion soit établie::
  
  if (mySwitch.available())

Puis la réception se fait par l'instruction::
  
  int value = mySwitch.getReceivedValue();

A la fin, on réinitialise la connexion::
  
      mySwitch.resetAvailable();
  
Deuxième montage
===================
Le principe de ce montage est le même que le précédent, mais on
cherche à miniaturiser et simplifier le capteur/émetteur en utilisant
un Attiny 45 qui coûte nettement moins cher qu'un arduino et se
programme avec l'environnement arduino. De plus, il va permettre de
commander une prise RF 433 sur laquelle on branche une pompe pour
déclencher un arrosage automatique.

On utilise cette fois comme récepteur une
carte Beagle Bone Black qui a l'avantage d'avoir un OS linux. On
pourra ainsi y faire tourner un serveur http et la programmer en Python.

1. Composants
------------------

* Capteur d'humidité dans le sol : DFRobot soil moisture
* Emetteur/récepteur RF : GoTronic
* Carte Beagle Bone Black
* Attiny 45
* Prise télécommandée RF 433

2. Montage
----------------

La sonde d'humidité est branchée sur les ports VCC (pin 8), GND
(pin 4) et A1 (pin 7) de
l'Attiny. L'émetteur RF est branché sur les ports VCC, GND et 0
(pin 5). Le tout est alimenté par 3 piles rechargeables et présenté par le schéma suivant:

.. image:: Schémas/capteur2.png
  :align: center

Le récepteur se branche sur les prots VCC, GND et GPIO1 (PIN 30) de la BBB comme
montré par le schéma suivant:

.. image:: Schémas/recepteur2.png
  :align: center

3. Programmes
-------------------
Les codes sources se trouvent à l'adresse suivante :
https://github.com/chorose/arrosage.git
Cette première version correspond au tag V0 

**Capteur/émetteur**

Dans ``RCSwitch.h`` il faut forcer le mode Attiny et le ``#define
RCSwitchDisableReceiving`` sinon le code est trop gros pour
l'attiny. Il faut aussi mettre la fréquence à 8MHz pour que les fronts
soient corrects.

Le code arduino (tag V0) présent à l'adresse :
https://github.com/chorose/arrosage/tree/V0/Arduino/prise/prise.ino
est sensiblement le même que pour l'émetteur du premier
montage utilisant l'ecoduino, si ce n'est la fonction ``void
arroser(int sensorValue)`` qui permet de déclencher l'arrosage via la
prise télécommandée selon la valeur retournée par la sonde (``sensorValue``) et un seuil
préétabli. Ici le code ``10001`` correspond au code constructeur de la
prise permettant de l'activer::
  
  void arroser(int sensorValue) {
    if (sensorValue < seuil) {
      mySwitch.switchOn("10001", 1);
      delay(10000); // 1 min
      mySwitch.switchOff("10001", 1);
    }
  }

**Récepteur BBB**

Le code pour la BBB se trouve à l'adresse:
https://github.com/chorose/arrosage/blob/V0/BeagleBone/receive.cpp
C'est sensiblement le même que pour le leonardo du premier montage,
sauf qu'on utilise la bibliothèque RCSwitch adaptée pour la BBB https://bitbucket.org/hackspark/rcswitch-bbb

On lance ``receive`` pour activer la réception.

Troisième montage
===================

Ce troisième montage est sensiblement le même que le précedent sauf
qu'on alimente les composants via le port 4 (pin 3) de l'Attiny plutôt
que VCC. Cela permettra de les allumer uniquement lorsqu'on prendra
les mesures afin de limiter la consommation. Il utilise donc les mêmes
composants selon le schéma suivant:

.. image:: Schémas/capteur3.png
  :align: center

Au niveau code (tag V1), il suffit d'allumer ``digitalWrite(4,HIGH)`` avant
d'appeler la fonction ``arroser()`` et d'éteindre ensuite ``digitalWrite(4,LOW)``.

A faire
------------
1. Utiliser le Watch Dog de l'Attiny pour limiter la conso
2. Mettre un interrupteur
