#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "labyrinth_loader.h"
#include "movement.h"

int main() {
    struct stage current_stage;

    char selected_stage[2] = "x\n";
    int mode;
    char direction;
    int moves_counter = 0;
    srand (time(NULL));

    current_stage.moves_storage = malloc(sizeof *current_stage.moves_storage * 1);
    current_stage.won = false;
    current_stage.score = 0;

    printf("Benvenuto su snake labyrinth\n");
    do {
        printf("Seleziona la modalità:\n1 - Singleplayer\n2 - Computer Random\n");
        printf("(input modalità): ");
        scanf("%d", &mode);
    } while (mode != 1 && mode != 2);
    show_stages(false, &current_stage);

    do {
        printf("\nSeleziona una mappa (1 - 2)\n");
        printf("(input mappa): ");
        scanf(" %c", &selected_stage[0]);
    } while (selected_stage[0] != '1' && selected_stage[0] != '2');

    load_labyrinth(selected_stage, &current_stage);
    clear();
    printf("Mappa selezionata:\n");
    show_stages(true, &current_stage);

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
            move(direction, &current_stage);

            current_stage.moves_storage[moves_counter] = direction;
            moves_counter++;
            current_stage.moves_storage = realloc(current_stage.moves_storage, (moves_counter + 1) * sizeof *current_stage.moves_storage);

            printf("Punteggio: %d\n", current_stage.score);
        } while (direction != 'h' && direction != 'j' && direction != 'k' && direction != 'l');
    } while (!current_stage.won);

    printf("Elenco delle mosse eseguite: ");
    for (int i = 0; i < moves_counter; i++) {
        printf("%c",current_stage.moves_storage[i]);
    }
    printf("\n");
    free(current_stage.playground);
    free(current_stage.moves_storage);

    return 0;
}

