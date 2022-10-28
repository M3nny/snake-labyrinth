#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct stage {
    char **playground;
    int rows;
    int columns;
    char moves[0];

    int current_position[1][1];
    int score;
};
struct stage current_stage;

void show_stages() {
    FILE* file = fopen("labyrinth.txt", "r");

    if(!file) {
        printf("\n Unable to open file");
        exit(EXIT_FAILURE);
    }

    char line[50];

    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);

}

void load_labyrinth (const char *stage) {
    FILE* file = fopen("labyrinth.txt", "r");

    if(!file) {
        printf("\n Unable to open file");
        exit(EXIT_FAILURE);
    }

    char line[50];
    int rows = 0, columns = 0; // numero di righe e colonne
    bool selected = false;
    char c;

    while (fgets(line, sizeof(line), file)) { // leggo tutto il file e stoppo il ciclo dopo aver letto il labirinto
        if ((strcmp(line, stage)) == 0) { // se trovo il numero corrispondente al labirinto comincio a leggerlo
            selected = true;
            while (fgets(line, sizeof(line), file)) { // leggo il labirinto finchè non trovo end
                if ((strcmp(line, "end\n")) == 0) {
                    break;
                }
                columns = strlen(line) - 1;
                rows++;
            }
        }
        if (selected) {
            break;
        }
    }

    current_stage.rows = rows;
    current_stage.columns = columns;

    // ridimensiono la matrice in base al labirinto selezionato
    current_stage.playground = malloc( sizeof *current_stage.playground *current_stage.rows);
    if (current_stage.playground) {
        for ( size_t i = 0; i < current_stage.rows; i++ ) {
            current_stage.playground[i] = malloc( sizeof *current_stage.playground[i] * current_stage.columns);
        }
    }

    rewind(file);
    selected = false;

    while (fgets(line, sizeof(line), file)) { // leggo tutto il file e stoppo il ciclo dopo aver letto il labirinto
        if ((strcmp(line, stage)) == 0) { // se trovo il numero corrispondente al labirinto comincio a leggerlo
            selected = true;

            // metto dentro alla matrice tutti gli elementi che non sono \n
            for (int i = 0; i < current_stage.rows; i++) {
                for (int j = 0; j < current_stage.columns; j++) {
                    do {
                        c = fgetc(file);
                        current_stage.playground[i][j] = c;
                    } while (c == '\n');
                }
            }

        }
        if (selected) {
            break;
        }
    }
}

int main() {
    char stage[2] = "x\n";

    printf("Benvenuto su snake labyrinth\n");
    show_stages();

    do {
        printf("Seleziona una mappa (1 - 2)\n");
        scanf("%c", &stage[0]);
    } while (stage[0] != '1' && stage[0] != '2');

    load_labyrinth(stage);

    for (int i = 0; i < current_stage.rows; i++) {
        for (int j = 0; j < current_stage.columns; j++) {
            printf("%c", current_stage.playground[i][j]);
        }
        printf("\n");
    }

    printf("righe: %d\ncolonne: %d\n", current_stage.rows, current_stage.columns);

    return 0;
}
