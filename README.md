# sda2-projet

Projet de 2è année pour la matière Structure de Données et Algortihmes.

## Prérecquis

Cloner le répertoire avec un :
```
git clone 'lien_pour_le_clonage'
```

### Comment ça marche ?

```
make
```

C'est aussi simple que ça. Et un :
```
./the_coloriage
```
pour le lancer.

### Mais que fait ce projet ?

Il va créer des images en noir et blanc aléatoires, puis va les colorier. Pour cela, il va regrouper chaque zone blanche, délimitée elle-même par une zone noire, et va colorier, d'une couleur aléatoire, chaque zone blanche. Il va jusqu'à une image de taille 5120 * 5120 pixels.

### Bon à savoir

* Développer en langage C.
* Pas de compilation séparée, car très petit projet et l'un des premiers pour moi.
* Une partie rapport, qui explique les différents complexités des algorithmes utilisés.
* Un script, qui utilise gnuplot, pour afficher la courbe de temps de l'aglorithme.
```
sh courbe.sh
```

## Auteurs
* **Bocquet Thomas**
* **Ventura Joaquim**
