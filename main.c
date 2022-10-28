#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct stage {
    char playground[0][0];
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

void get_labyrinth_size (const char *stage) {
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

    rewind(file);
    selected = false;

    while (fgets(line, sizeof(line), file)) { // leggo tutto il file e stoppo il ciclo dopo aver letto il labirinto
        if ((strcmp(line, stage)) == 0) { // se trovo il numero corrispondente al labirinto comincio a leggerlo
            selected = true;
            while ((c = fgetc(file)) != EOF){ // leggo il labirinto finchè non trovo end
                if (c == 'e') {
                    break;
                }
                // mettere i valori dentro alla matrice
                printf("%c", c);
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

    get_labyrinth_size(stage);
    printf("righe: %d\ncolonne: %d\n", current_stage.rows, current_stage.columns);

    return 0;
}
