#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "tail.h"
#include "labyrinth_loader.h"
#include "movement.h"
#include "challenges.h"

int main(int argc, char **argv) {
    if (argv[1]) {
        if (strcmp(argv[1], "--challenge") == 0) {
            challenge();
            return 0;
        }
    }
    labyrinth_stage stage;
    labyrinth_player player;
    vector *tail = NULL;

    char selected_stage[2] = "x\n";
    int mode;
    char direction, show_moves;
    int moves_counter = 0;
    srand(time(NULL));

    printf("Benvenuto su snake labyrinth\n");
    do {
        printf("Seleziona la modalità:\n1 - Singleplayer\n2 - Computer Random\n");
        printf("(input modalità): ");
        scanf("%d", &mode);
    } while (mode != 1 && mode != 2);
    show_stages(false, tail, &stage);

    do {
        printf("\nSeleziona una mappa (1 - 2 - 3)\n");
        printf("(input mappa): ");
        scanf(" %c", &selected_stage[0]);
    } while (selected_stage[0] != '1' && selected_stage[0] != '2' && selected_stage[0] != '3');

    load_game(selected_stage, &stage, &player);
    clear();
    printf("Mappa selezionata:\n");
    show_stages(true, tail, &stage);

    do {
        do {
            if (mode == 1) {
                scanf(" %c", &direction);
            } else if (mode == 2) {
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
            move(direction, &tail, &stage, &player);
            store_move(direction, &player);
            clear();
            show_stages(true, tail, &stage);

            printf("Punteggio: %d\n", player.score);
        } while (direction != player.left && direction != player.down && direction != player.up && direction != player.right);
    } while (!player.won);
    printf("Hai vinto!\nDesideri vedere le mosse eseguite?(s/n) ");

    do {
        scanf(" %c", &show_moves);
    } while (show_moves != 's' && show_moves != 'n');

    if (show_moves == 's') {
        printf("Elenco delle mosse eseguite: ");
        for (int i = 0; i < player.moves_counter; i++) {
            printf("%c",player.moves_storage[i]);
        }
        printf("\n");
    }

    for ( size_t i = 0; i < stage.rows; i++ ) {
        free(stage.playground[i]);
    }
    free(stage.playground);
    free(player.moves_storage);

    return 0;
}