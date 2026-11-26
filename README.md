# Tests pour GNL (get_next_line)

Un petit mémo de commandes pour tester GNL rapidement sans se prendre la tête.

1. Générer quelques fichiers de test

mkdir -p tests_gnl

## fichier vide
: > tests_gnl/empty.txt

## 1 ligne sans \n
printf "salut" > tests_gnl/one_no_nl.txt

## 1 ligne avec \n
printf "salut\n" > tests_gnl/one_nl.txt

## plusieurs lignes + lignes vides + pas de \n à la fin
printf "premiere ligne\n\ntroisieme\nfin" > tests_gnl/multi.txt

## grosse ligne de 50 000 caractères
python3 -c 'print("a" * 50000, end="")' > tests_gnl/big.txt


2. Compiler avec différents BUFFER_SIZE

Penser à vérifier si les .c sont à la racine ou dans un dossier src/.

## BUFFER_SIZE = 1 (le classique pour tout casser)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl

## BUFFER_SIZE = 42
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

## gros buffer
cc -Wall -Wextra -Werror -D BUFFER_SIZE=100000 get_next_line.c get_next_line_utils.c main.c -o gnl


3. Lancer les tests

Si le main.c prend le nom du fichier en argument (argv[1]) :

./gnl tests_gnl/empty.txt
./gnl tests_gnl/one_no_nl.txt
./gnl tests_gnl/one_nl.txt
./gnl tests_gnl/multi.txt
./gnl tests_gnl/big.txt


Tester sur l'entrée standard (fd = 0) :

printf "ligne 1\nligne 2\n" | ./gnl


4. Check des leaks

Avec Valgrind :

valgrind --leak-check=full --show-leak-kinds=all ./gnl tests_gnl/multi.txt


Si sur Mac / sans Valgrind, compiler avec -fsanitize=address :

cc -Wall -Wextra -Werror -fsanitize=address -g -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
./gnl tests_gnl/multi.txt


5. Tout nettoyer

rm -rf gnl tests_gnl
