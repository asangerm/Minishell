# Minishell

## Description

Minishell est une reproduction d'un shell en C qui imite le fonctionnement de bash. Ce projet inclut le parsing, l'exécution et les commandes intégrées (builtins).

## Fonctionnalités

- Affichage d'un prompt en attente d'une nouvelle commande.
- Historique des commandes fonctionnel.
- Recherche et lancement du bon exécutable (basé sur la variable PATH ou utilisant un chemin relatif ou absolu).
- Gestion des redirections (`<`, `>`, `<<`, `>>`).
- Gestion des pipes (`|`).
- Gestion des variables d'environnement (`$`).
- Gestion du statut de sortie (`$?`).
- Gestion des signaux `ctrl-C`, `ctrl-D` et `ctrl-\` en mode interactif.
- Implémentation des commandes intégrées suivantes :
  - `echo` avec l'option `-n`
  - `cd` avec uniquement un chemin relatif ou absolu
  - `pwd` sans options
  - `export` sans options
  - `unset` sans options
  - `env` sans options ni arguments
  - `exit` sans options

## Installation

Clonez le repository et compilez le projet :

```sh
git clone git@github.com:asangerm/Minishell.git
cd Minishell
make
```

## Utilisation

Après l'installation, exécutez le programme avec :

```sh
./minishell
```

## Contribution

Le projet Minishell est développé par asangerm et nfradet, étudiants à l'école 42. Les contributions externes ne sont pas acceptées pour le moment.

## Consignes du projet

- Le projet doit être écrit en C.
- Respect strict de la Norme de codage de l'école 42.
- Les fonctions ne doivent pas quitter de manière inattendue (segmentation fault, bus error, double free, etc.).
- Toute mémoire allouée sur le tas doit être correctement libérée.
- Un Makefile doit être fourni avec les règles $(NAME), all, clean, fclean et re.
- Les fonctions bonus doivent être dans des fichiers séparés avec un Makefile qui inclut une règle bonus.
- Utilisation autorisée de la bibliothèque libft.

## Supprimer les leaks de readline

Créez une fichier `valgrind.supp' avec le contenu suivant :

```
{
   ignore_libreadline_leaks
   Memcheck:Leak
   ...
   obj:*/libreadline.so.*
}
```

Ensuite éxecutez le programme de la sorte :
```sh
valgrind --suppressions=valgrind.supp ./minishell
```

## Contact

Pour toute question ou problème, vous pouvez nous contacter :

- 'asangerm@student.42perpignan.fr'
- 'nfradet@student.42perpignan.fr'
