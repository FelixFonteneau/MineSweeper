# MineSweeper
Projet visant à implementer un algorithme de résolution de démineur.

### Interface 
L'intérface est simple, elle est géré dans le terminal (UNIX). <br>
La classe Grille, permet la gestion du jeu. 

### Implémentation
La résolution du jeu se situe dans le main. <br>
L'algorithme de résolution récupères les informations concernant la grille par un tableau d'entiers de -2 à 8. <br>
Chaque entier positif sur une case donne l'information du nombre de bombes sur les cases adjacentes. <br>
-1 symbolise une case non ouverte, soit aucune informations. -2 symbolise un drapeau planté par le joueur sur une case non ouverte.

### Algorithme
L'algo comporte 3 grandes étapes,

- La première est de poser des drapeau sur les cases bombes trouvées par la résolution des cas triviaux. On pose des flags sur toutes les cases non ouvertes adjacentes d'une case ouverte ayant le même nombre de bombes à proximité que de cases fermées.

- La seconde est d'ouvrir toutes les cases adjacentes à une case ouverte qui comporte autant de drapeaux que de bombes à proximité.

- La troixième est de gerer tous les cas non triviaux. (en cours).
