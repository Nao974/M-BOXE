# M-BOXE

Servo Motor DIY controled by Raspberry-pi to I2C / Servo-Moteur construction "Maison" controlé par Raspberry-py en I2C

<img src="https://github.com/Nao974/M-BOXE/blob/master/M-BOXE.jpg" title="Photo M-BOXE" alt="Photo M-Boxe">


## Contents / Contenu

* [Directory / Repertoire](https://github.com/Nao974/M-BOXE#directory--répertoire)
* [Features / Fonctionnalités](https://github.com/Nao974/M-BOXE/blob/master/README.md#features--fonctionnalités)
* [Construction](https://github.com/Nao974/M-BOXE#construction)
* [Installation](https://github.com/Nao974/M-BOXE#installation)
	* [Step 1: Import Motor-Command Library / Importer la librairie de Commande Moteur](https://github.com/Nao974/M-Boxe#step-1-import-motor-command-library--importer-la-librairie-de-commande-moteur)	
	* [Step 2: Firmware Setting / Paramétrage du firmware](https://github.com/Nao974/M-Boxe#step-2-firmware-setting--paramétrage-du-firmware)
* [Usage](https://github.com/Nao974/M-BOXE#usage)
* [History / Historique](https://github.com/Nao974/M-BOXE#history--historique)


## Directory / Répertoire

* ```Doc/```       Documentation
* ```firmware/```  Skecth for download to Arduino / Croquis à télécharger dans l'Arduino
* ```Library_MotorDriver/```  Library to order the card Engine to install in your IDE / Librairie pour commander la carte Moteur à installer dans votre IDE
* ```Library_I2C-Master_Python/```   Library in Python to order M-Boxes in I2C / Librairie en Python pour commander les M-Boxe en I2C


## Features / Fonctionnalités

* Reach and maintain a position (Angle) at a constant given speed
* Receive position setpoint by I2C link
* Security in case of exceeding values:
	* Temperature
	* Power consumption
	* Blocking of the motor shaft
	* Activation of the sensor (on / off) inversely to the movement in progress
	* Return to normal operation once the value is below the trip threshold.
* Transmit the data following the command received by I2C: 
	* State
	* Current position
	* Value of a given analog input
	* Value of registers Digital inputs
* Parameterization by I2C: 
	* Sending configuration
	* Integration of a new configuration
* Saving / Loading Parameters in the EEPROM  


* Atteindre et maintenir une position (Angle) à une vitesse donnée constante
* Recevoir la consigne de position par liaison I2C
* Mise en Sécurité en cas de dépassement des valeurs:
	* Température
	* Consommation électrique
	* Blocage de l’arbre moteur
	* Activation du capteur (tout/rien) inversement au mouvement en cours
	* Retour au fonctionnement normal une fois la valeur en dessous du seuil de déclenchement
* Transmettre les données suivant la commande reçue par I2C:
	* Etat
	* Position actuelle
	* Valeur d’une entrée analogique donnée
	* Valeur des registres Entrées numériques
* Paramétrage par I2C:
	* Envoi de la configuration
	* Intégration d’une nouvelle configuration
* Sauvegarde/Chargement des paramètres dans l’EEPROM


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
In USB connection, set the I2C address of your Mboxe to line ``` #define SLAVE_ADRESS 0x14 ```
You can enable debug mode to ```#define DEBUG false``` by passing it to 'true'. This will bring up the current position, setpoint position and PID calculations on a time scale in the Series monitor of your IDE. It is enough to subsequently COPY/PASTE this data in a spreadsheet and make a graph.  
This graphical visualization will help you to find the best coefficients kp, kd and ki of your PID.  
Details of the parameters in the document [Parameter_M-BOXE.jpg](https://github.com/Nao974/M-BOXE/blob/master/doc/Parameter_M-BOXE.pdf)


Ouvrir le croquis firmware.ino  
Par connexion USV, définir l'adresse I2C de votre Mboxe à la ligne ``` #define SLAVE_ADRESS 0x14 ```
Vous pouvez activer le mode debug à la ligne ```#define DEBUG false``` en la passant à 'true'. Cela fera remonter dans le moniteur Serie de votre IDE la position courante, la position de consigne et les calculs du PID sur une échelle de temps. Il suffit par la suite de COPIER/COLLER ces données dans un tableur et faire un graphique.  
Cette visualisation graphique vous aidera à trouver les meilleurs coefficants kp, kd et ki de votre PID.  
Detail des paramètres dans le document [Parameter_M-BOXE.jpg](https://github.com/Nao974/M-BOXE/blob/master/doc/Parameter_M-BOXE.pdf)


## Usage

Once your construction and firmware settings have been made, connect your M-BOXE to the I2C bus.  
As for power, I use an ATX molex 4P connector and a desktop power supply. It is important to separate the power supply from the motor from the Arduino power supply and the MC board.  

The `MBOXE.PY` library allows you to control your M-BOXE from the I2C bus.
Detail of registers (command) I2C in document [Register_M-BOXE.jpg](https://github.com/Nao974/M-BOXE/blob/master/doc/Register_I2C_M-BOXE.pdf)  
See examples [M-Boxe Manager TK](https://github.com/Nao974/M-BOXE_Manager_TK) in graphic mode or [M-Boxe Manager CL](https://github.com/Nao974/M-BOXE_Manager_CL) in command line.  


Une fois votre construction et le paramétrage du firmware effectué, connecter votre M-BOXE au bus I2C.  
Concernant l'alimentation, j'utilise un connecteur ATX molex 4P et une alimentation d'ordinateur de bureau. Il est important de séparer l'alimentation de puissance du moteur de l'alimentation de l'Arduino et de la carte MC.  

La libriairie `MBOXE.PY` permet de commander votre M-BOXE à partir du bus I2C.  
Detail des registres (commande) I2C dans le document [Register_M-BOXE.jpg](https://github.com/Nao974/M-BOXE/blob/master/doc/Register_I2C_M-BOXE.pdf)  

Voir les exemples [M-Boxe Manager TK](https://github.com/Nao974/M-BOXE_Manager_TK) en mode graphique ou  [M-Boxe Manager CL](https://github.com/Nao974/M-BOXE_Manager_CL) en ligne de commande.  


## History / Historique

- [History] (https://github.com/Nao974/M-BOXE/blob/master/history.md)


