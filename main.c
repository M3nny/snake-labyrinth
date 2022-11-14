#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "labyrinth_loader.h"
#include "movement.h"

int main() {
    struct labyrinth_stage stage;
    struct labyrinth_player player;

    char selected_stage[2] = "x\n";
    int mode;
    char direction;
    int moves_counter = 0;
    srand (time(NULL));

    player.moves_storage = malloc(sizeof(char) * 1);
    player.won = false;
    player.score = 0;

    printf("Benvenuto su snake labyrinth\n");
    do {
        printf("Seleziona la modalità:\n1 - Singleplayer\n2 - Computer Random\n");
        printf("(input modalità): ");
        scanf("%d", &mode);
    } while (mode != 1 && mode != 2);
    show_stages(false, &stage);

    do {
        printf("\nSeleziona una mappa (1 - 2)\n");
        printf("(input mappa): ");
        scanf(" %c", &selected_stage[0]);
    } while (selected_stage[0] != '1' && selected_stage[0] != '2');

    load_game(selected_stage, &stage, &player);
    clear();
    printf("Mappa selezionata:\n");
    show_stages(true, &stage);

    do {
        do {
            if (mode == 1) {
                scanf(" %c", &direction);
            } else if (mode == 2) {
                direction = rand() % 4;
                switch (direction) {
                    case 0:
                        direction = 'h';
                        break;
                    case 1:
                        direction = 'j';
                        break;
                    case 2:
                        direction = 'k';
                        break;
                    case 3:
                        direction = 'l';
                        break;
                }
            }
            move(direction, &stage, &player);

            player.moves_storage[moves_counter] = direction;
            moves_counter++;
            player.moves_storage = realloc(player.moves_storage, (moves_counter + 1) * sizeof(char));

            printf("Punteggio: %d\n", player.score);
        } while (direction != 'h' && direction != 'j' && direction != 'k' && direction != 'l');
    } while (!player.won);

    printf("Elenco delle mosse eseguite: ");
    for (int i = 0; i < moves_counter; i++) {
        printf("%c",player.moves_storage[i]);
    }
    printf("\n");
    free(stage.playground);
    free(player.moves_storage);

    return 0;
}

