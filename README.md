#M-BOXE
BIG SERVO-MOTOR DIY

# Rédaction en cours



## RoadMap
###Ver 0.3:
- ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) Remontée des valeurs analogiques PINA2 & PINA3
- ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) Remontée des valeurs numériques PIN0 -> PIN7 (PortD)
- Remontée de la température
  - Test de la fonction seule: OK
  - Intégration dans le firmware : !KO!
  - ![#f03c15](https://placehold.it/15/f03c15/000000?text=+) Basculé sur version 0.4
- ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) Ajout de la remontée de l'état de la protection sur code 0x44
- ![#c5f015](https://placehold.it/15/c5f015/000000?text=+) Ajout de la remontée de l'état des contacts FW et BW sur code 0x48


###Ver 0.4:
- Intégration des fonctions de protection
	- Suivant bornes définies
	- Suivant remontée de la carte MC
	- Température ???
	- LEDs état sur PIN11


###Ver 0.5:
- Ajout du PID Vitesse
	- Intégration des données PID Kx
	- Intégration des bornes min // max
	- Remontée suivant type d'anomalie


###V 1.0:
- Ajout de la commande par PWM comme un servo

