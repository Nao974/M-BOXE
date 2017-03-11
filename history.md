# History / Historique

####Ver 0.3:
* ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) Lecture par I2C des valeurs analogiques PINA2 & PINA3
* ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) Lecture par I2C des valeurs numériques PIN0 -> PIN7 (PortD)
* ![#f03c15](https://placehold.it/15/f03c15/000000?text=+) ~~Lecture par I2C de la température~~ Basculé sur version 0.4
* ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) Ajout de la lecture de l'état de la protection sur code 0x44
* ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) Ajout de la lecture de l'état des contacts FW et BW sur code 0x48


* ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) I2C reading of analog values PINA2 & PINA3
* ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) I2C reading of Numeric Values PIN0 -> PIN7 (PortD)
* ![#f03c15](https://placehold.it/15/f03c15/000000?text=+) ~~I2C reading of the temperature~~ Switch to version 0.4
* ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) Added protection status reading to code 0x44
* ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) Added FW and BW contact status reading to code 0x48


####Ver 0.4:
- Intégration des fonctions de protection
	- Suivant bornes définies
	- Suivant remontée de la carte MC
	- Température ???
	- LEDs état sur PIN11


####Ver 0.5:
- Ajout du PID Vitesse
	- Intégration des données PID Kx
	- Intégration des bornes min // max
	- Remontée suivant type d'anomalie


####V 1.0:
- Ajout de la commande par PWM comme un servo
