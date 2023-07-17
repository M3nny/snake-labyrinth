/**
 * \file main.c
 * \brief File principale
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "tail.c"
#include "game_manager.c"
#include "movement.c"
#include "bot.c"

/**
 * 1. Se non è presente --challenge come parametro, faccio scegliere la modalità interattiva/random all'utente
 * 2. Viene chiesto come si vuole selezionare il livello: input da tastiera specificando righe e colonne del livello, oppure un livello già esistente sul file labyrinth.txt
 * 3. Viene caricata la matrice in memoria e si comincia a giocare
 * 4. Dopo ogni mossa l'interfaccia del terminale viene pulita
 * 5. Alla fine viene chiesto se si vogliono vedere le mosse eseguite (potrebbero essere tante)
 * 6. Viene deallocato dalla memoria quello che è stato allocato precedentemente (matrice, coda, storage delle mosse eseguite)
*/
int main(int argc, char **argv) {
    labyrinth_stage stage;
    labyrinth_player player;
    list *tail = NULL;

    char selected_stage[2] = "x\n";
    int mode, method; // mode: selezione modalità, method: selezione metodo di input del livello
    char direction, show_moves; // direction: direzione impartita dal giocatore, show_moves: per decidere se mostrare le mosse eseguite a fine partita 
    srand(time(NULL)); // do un seme casuale al random

    clear();
    printf("Benvenuto su snake labyrinth\n");

    do { // scelgo la mdalità
        printf("Seleziona la modalità:\n1 - Interattiva\n2 - Casuale\n3 - Algoritmo\n");
        printf("(input modalità): ");
        scanf("%d", &mode);
    } while (mode != 1 && mode != 2 && mode != 3);
    clear();

    do { // scelgo il metodo di input della mappa
        printf("Come vuoi selezionare il livello:\n1 - Manuale\n2 - Livelli già esistenti\n");
        printf("(input metodo): ");
        scanf("%d", &method);
    } while (method != 1 && method != 2);
    clear();

    if (method == 1) {
        selected_stage[0] = '0';
        load_game(selected_stage, &stage, &player);
    } else {
        show_stages(false, tail, &stage);
        do {
            printf("\nSeleziona una mappa (1 - 5)\n");
            printf("(input mappa): ");
            scanf(" %c", &selected_stage[0]);
        } while (selected_stage[0] < '1' || selected_stage[0] > '5');
        load_game(selected_stage, &stage, &player);
    }

    clear();
    printf("Mappa selezionata:\n");
    show_stages(true, tail, &stage);

    if (mode == 1 || mode == 2) {

        do {
            do { // inserisco la mossa e la memorizzo
                if (mode == 1) {
                    scanf(" %c", &direction);
                } else {
                    direction = rand() % 4;
                    switch (direction) {
                        case 0:
                            direction = player.left;
                            break;
                        case 1:
                            direction = player.down;
                            break;
                        case 2:
                            direction = player.up;
                            break;
                        case 3:
                            direction = player.right;
                            break;
                    }
                }
            } while (direction != player.left && direction != player.down && direction != player.up && direction != player.right);
            move(direction, &tail, &stage, &player);
            store_move(direction, &player);
            clear();
            show_stages(true, tail, &stage);

            printf("Punteggio: %d\n", player.score);
        } while (!player.won);

        printf("Hai vinto!\nDesideri vedere le mosse eseguite?(s/n) ");

        do {
            scanf("%c", &show_moves);
        } while (show_moves != 's' && show_moves != 'n');

        if (show_moves == 's') {
            printf("Elenco delle mosse eseguite: ");
            for (int i = 0; i < player.moves_counter; i++) {
                printf("%c", player.moves_storage[i]);
            }
            printf("\n");
        }
    } else {
        bot_algorithm(tail, stage, player);
    }

    // libero la memoria allocata
    free_game(&stage, &player, tail);

    return 0;
}
