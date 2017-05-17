.. _capteur:

==================================
Système d'arrosage automatique
==================================

1. Composants
===============

* Capteur d'humidité dans le sol : DFRobot soil moisture
* Emetteur/récepteur RF : GoTronic
* Carte Arduino Leonardo
* Carte Arduino Ecoduino de DFRobot
* Carte Beagle Bone Black

2. Montages
============
.. image:: Schémas/montage1.png
  :align: center

3. Programmes
================
Utilisation de la librairie RCSwitch pour Arduino : https://github.com/sui77/rc-switch

Capteur/émetteur : /Users/roselyne/dev/Arrosage/Arduino/Sensor/sensor.ino

Récepteur : /Users/roselyne/dev/Arrosage/Arduino/receiver/receiver.ino

Sur le leonardo (récepteur) on utilise pin3 (interrupt 0) pour connecter data du récepteur et sur l'ecoduino, on utilise pin D13 pour connecter le data de l’émetteur, le capteur lui (soil moisture) est connecté à pin A2

Capteur/émetteur attiny

Dans RCSwitch.h il faut forcer le mode Attiny et le #define RCSwitchDisableReceiving sinon le code est trop gros pour l'attiny. Il faut aussi mettre la fréquence à 8MHz pour que les fronts soient corrects.

Les code sont sur github dans la branche attiny : https://github.com/chorose/arrosage.git

Le montage correspondant alimenté en 5V :

.. image:: Schémas/capteur2.png
  :align: center

Récepteur BBB

.. image:: Schémas/recepteur2.png
  :align: center

On utilise la bibliothèque RCSwitch adaptée pour la BeagleBone https://bitbucket.org/hackspark/rcswitch-bbb

Les codes sont sur la BBB dans /home/roselyne/RCSwitch

On lance receive pour activer la réception

4. A faire
==========
1. Alimenter les composants via un port de l'Attiny et un transistor
2. Utiliser le Watch Dog de l'Attiny pour limiter la conso
3. Mettre un interrupteur
