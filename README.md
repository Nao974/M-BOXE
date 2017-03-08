# M-BOXE
Servo Motor DIY controled by Raspberry-pi to I2C / Servo-Moteur construction "Maison" controlé par Raspberry-py en I2C

<img src="https://github.com/Nao974/M-BOXE/blob/master/M-BOXE.jpg">

## Contents / Contenu

* [Features / Fonctionnalités](https://github.com/Nao974/M-BOXE#features--fonctionnalités)
* [Construction](https://github.com/Nao974/M-BOXE#construction)
* [Installation](https://github.com/Nao974/M-BOXE#installation)
	* [Step 1: Import Motor-Command Library / Importer la librairie de Commande Moteur](https://github.com/Nao974/M-BOXE#Step-1-Import-Motor-Command-Library--Importer-la-librairie-de-Commande-Moteur)	
	* [Step 2: Firmware Setting / Paramétrage du firmware](https://github.com/Nao974/M-Boxe#Step-2-Firmware-Setting--Paramétrage-du-firmware)
	* [Step 3: Setting the PID / Paramétrage du PID](https://github.com/Nao974/M-Boxe#Step-3-Setting-the-PID--Paramétrage-du-PID)
* [Usage](https://github.com/Nao974/M-BOXE#usage)
* [History / Historique](https://github.com/Nao974/M-BOXE#histroy--historique)

## Features / Fonctionnalités

## Construction
Go to my tutorial / Mon tutoriel sur [Oui Are Makers](http://ouiaremakers.com/posts/tutoriel-diy-maxi-servo-moteur-i2c)
## Installation

##### Step 1: Import Motor-Command Library / Importer la librairie de Commande Moteur 
You should import the control card library into the Arduino IDE:
	Sketch-> Import Library-> Add Library

Il convient d'importer la librairie de la carte de commande dans l'IDE Arduino: 
	Croquis-> importer Bibliothèque-> ajouter Bibliothèque.

##### Step 2: Firmware Setting / Paramétrage du firmware
Open the sketch firmware.ino
Set the I2C address of your Mboxe to line ``` #define SLAVE_ADRESS 0x14 ```
You can modify the parameters directly in the source code on line ```mboxeType mBoxe={....}``` or later with the program

Ouvrir le croquis firmware.ino
Définir l'adresse I2C de votre Mboxe à la ligne ``` #define SLAVE_ADRESS 0x14 ```
Vous pouvez modifier les paramétres directement dans le code source à la ligne ```mboxeType mBoxe={....}``` ou par la suite avec le programme [M-Boxe Manager TK](https://github.com/Nao974/M-BOXE_Manager_TK) ou  [M-Boxe Manager CL](https://github.com/Nao974/M-BOXE_Manager_CL).

##### Step 3: Setting the PID / Paramétrage du PID



## Usage

## History / Historique

- [History] (https://github.com/Nao974/M-BOXE/blob/master/history.md)


