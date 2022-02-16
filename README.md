# IN204 - Projet Composition de SMS type T9 (pour version de Qt inférieur à 5)

## Compilation

Tout d'abord, assurez vous d'avoir Qt installé sur votre ordinateur :

```bash
$ qmake --version
```

Cette commande devrait renvoyer quelque chose comme :

```bash
QMake version 3.1
Using Qt version 6.2.2 in /usr/local/lib
```

Si votre version de Qt est suppérieure à 5 (comme ici), utilisez la version originale du projet. Sinon, vous êtes dans le bon repo.


Pour compiler le projet, rendez-vous dans le dossier 'T9/vue/'

```bash
$ cd T9/vue/
```

puis lancez les commandes :

```bash
$ qmake
$ make
```

L'application devrait alors apparaitre dans ce dossier sous le nom 'T9'.