.. _humiscope:

================
HumiScope
================
Appareil permettant de mesurer l’humidité dans le sol et affichage sur 7 segments (0 : sec, 9 : très humide).

1. Composants
=============
* Capteur d'humidité dans le sol : DFRobot soil moisture
* Arduino-nano
* Afficheur 7 segments
* Résistance 22 Ω
* Pile 9V
* Interrupteur

2. Montage
============
.. image:: Schémas/humiscope.png
  :align: center

Alimentation par une pile 9V reliée aux pins GND et VIN de l’arduino-nano. Prévoir un interrupteur.

3. Programme
==============
Fichier humiscope.ino

Lecture de la valeur de la sonde d’humidité (pin A0), ramener à un nombre entre 0 et 9 (0 : sec, 9 : très humide) par une multiplication par 9/800 (9 : afficheur 7 segments, 800 : valeur max de la sonde), puis affichage du chiffre correspondant.

Les LEDs de l’afficheur sont allumées tour à tour pendant un temps T (T=3) permettant la rémanence de la pupille, ce qui fait qu’on a l’impression d’un affichage continu (fonction ``void allumer(int segment)``).
Petit algo pour afficher les segments corrects en fonction du chiffre (fonction ``void afficher(int n)``) :

* a : n ≠ 1 et n ≠ 4
* b : n ≠ 5 et n ≠ 6
* etc.

4. A faire
==========
1. Ajouter un interrupteur
2. Boitier en impression 3D
3. Schéma sur KiCad puis impression de la carte à Polytech
