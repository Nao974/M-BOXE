# M-BOXE

Servo-Moteur construction "Maison" controlé par Raspberry-py en I2C

<img src="https://github.com/Nao974/M-BOXE/blob/master/EVOLUTION.jpg" title="Photo M-BOXE" alt="Photo M-Boxe">  


[![](https://github.com/Nao974/M-BOXE/blob/master/doc/M-BOXE_Video.png)](https://youtu.be/asLjmGtZqu0)
[![](https://github.com/Nao974/M-BOXE/blob/master/doc/CONSTRUCTION_V1_Video.png)](https://youtu.be/vx16dWJ84GE)

## [English version](https://github.com/Nao974/M-BOXE/blob/master/README.md)  

## Contenu

* [Repertoire](https://github.com/Nao974/M-BOXE/blob/master/README_FR.md#répertoire)
* [Fonctionnalités](https://github.com/Nao974/M-BOXE/blob/master/README_FR.md#fonctionnalités)
* [Construction](https://github.com/Nao974/M-BOXE/blob/master/README_FR.md#construction)
* [Installation](https://github.com/Nao974/M-BOXE/blob/master/README_FR.md#installation)
	* [Step 1: Importer la librairie de Commande Moteur](https://github.com/Nao974/M-BOXE/blob/master/README_FR.md#step-1-importer-la-librairie-de-commande-moteur)	
	* [Step 2: Paramétrage du firmware](https://github.com/Nao974/M-BOXE/blob/master/README_FR.md#step-2-paramétrage-du-firmware)
* [Usage](https://github.com/Nao974/M-BOXE/blob/master/README_FR.md#usage)
* [Historique](https://github.com/Nao974/M-BOXE/blob/master/README_FR.md#historique)


## Répertoire

* ```Doc/```       Documentation
* ```firmware/```  Croquis à télécharger dans l'Arduino
* ```Library_MotorDriver/```  Librairie pour commander la carte Moteur à installer dans votre IDE
* ```Library_I2C-Master_Python/```   Librairie en Python pour commander les M-Boxe en I2C


## Fonctionnalités

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

Mon tutoriel sur [Oui Are Makers](http://ouiaremakers.com/posts/tutoriel-diy-maxi-servo-moteur-i2c)  
Cablage [Diagram](https://github.com/Nao974/M-BOXE/blob/master/doc/Wiring.png)

## Installation

##### Step 1: Importer la librairie de Commande Moteur 

Il convient d'importer la librairie de la carte de commande dans l'IDE Arduino: 
	Croquis-> importer Bibliothèque-> ajouter Bibliothèque.


##### Step 2: Paramétrage du firmware

Ouvrir le croquis firmware.ino  
Par connexion USV, définir l'adresse I2C de votre Mboxe à la ligne ``` #define SLAVE_ADRESS 0x14 ```
Vous pouvez activer le mode debug à la ligne ```#define DEBUG false``` en la passant à 'true'. Cela fera remonter dans le moniteur Serie de votre IDE la position courante, la position de consigne et les calculs du PID sur une échelle de temps. Il suffit par la suite de COPIER/COLLER ces données dans un tableur et faire un graphique.  
Cette visualisation graphique vous aidera à trouver les meilleurs coefficants kp, kd et ki de votre PID.  
Detail des paramètres dans le document [Parameter_M-BOXE.pdf](https://github.com/Nao974/M-BOXE/blob/master/doc/Parameter_M-BOXE.pdf)


## Usage

Une fois votre construction et le paramétrage du firmware effectué, connecter votre M-BOXE au bus I2C.  
Concernant l'alimentation, j'utilise un connecteur ATX molex 4P et une alimentation d'ordinateur de bureau. Il est important de séparer l'alimentation de puissance du moteur de l'alimentation de l'Arduino et de la carte MC.  

La libriairie [M-BOXE.py](https://github.com/Nao974/M-BOXE/blob/master/Library_I2C-Master_Python/M-BOXE.py) dans le repertoire `Library_I2C-Master_Python` permet de commander votre M-BOXE à partir du bus I2C.  
Detail des registres (commande) I2C dans le document [Register_M-BOXE.pdf](https://github.com/Nao974/M-BOXE/blob/master/doc/Register_I2C_M-BOXE.pdf)  

Les programmes [M-Boxe Manager TK](https://github.com/Nao974/M-BOXE_Manager_TK) en mode graphique ou  [M-Boxe Manager CL](https://github.com/Nao974/M-BOXE_Manager_CL) en ligne de commande sont des implémentations de cette librairie.


## Historique

- [Historique](https://github.com/Nao974/M-BOXE/blob/master/history.md)


