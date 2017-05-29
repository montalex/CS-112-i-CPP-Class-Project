# Présentation du programme

Le programme permet de simuler l'évolution d'un environnement peuplé par des Animaux (brebis, loups) et de la
vegetation. Les animaux intéragissent entre en formant des troupeaux, en se mangeant et en se reproduisant.
Ils peuvent se nourrir de plantes (les brebis) ou de brebis (les loups).

Les animuax dans un troupeau restent proches les uns des autres et suivent leur chef.
Les animaux peuvent aussi être infectés par des virus, et l'infection se propagera entre les animaux qui sont proches.
Les animaux possèdent un système immunitaire qui leur permet de combattre l'infection.

Les programme fournit aussi un mécanisme de recolte et d'affichage des statistiques.

# Compilation du programme

Pour lancer le programme final (`FinalApplication`) il suffit d'executer:

`scons application-run --cfg=appPPS.json`

à la racine du projet.

# Utilisation du programme
Interaction au moyen du clavier:

 - **w** crée un loup à l'emplacement du pointeur de la souris
 - **s** crée une brebis à l'emplacement du pointeur de la souris
 - **g** crée une plante à l'emplacement du pointeur de la souris
 - **1** crée une brebis appartenant au troupeau 1 à l'emplacement du pointeur de la souris
 - **2** crée une brebis appartenant au troupeau 2 à l'emplacement du pointeur de la souris
 - **k** Tue l'entité à l'emplacement du pointeur de la souris
 - **i** Infecte l'entité à l'emplacement du pointeur de la souris avec un virus au profil de virulence random.
 - **r** Redemarre la simulation avec un monde vide.
 - **t** Suit le statistiques de l'animal le plus proche au pointeur de la souris.
 - **espace** Met en pause la simulation.
 - **d** entre en mode debug.

# Parties implémentées
Nous avons terminé les parties obligatoires du programme, soit jusqu'à la fin de l'étape 5.3
