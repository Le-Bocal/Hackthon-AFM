Besoin de créer une croix directionnelle de clavier pour jouer sur PC. Le clavier classique est trop encombrant, on choisi d'avoir uniquement le clavir directionnel.

On a hacker un mini joystick utilisé par les résidents, puis on l'a branché sur les entrées analogiques d'un arduino micro (capable d'utiliser la bibliothèque keybard.h) pour simuler un clavier.

Le joystik déclenche des interupteurs on/off sur les 4 directions, mais on a choisi de mesurer le potentiels des 4 fils de signals par rapport au gnd. On obtient un comportement par forcement intuitif (voir photos avec mesures).
Il est sans doute possible d'avoir un comportement plus logique au niveau des directions en se branchant entre les differents fils de signal (et non -plus entre le signal et le gnd).

Des améliorations peuvent etre apportées au niveau du code pour éviter de prendre en compte les rebonds du joystick.

D'autre boutons peuvent etre ajoutés pour faire une commande plus complète
