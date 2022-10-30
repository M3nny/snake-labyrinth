#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct stage {
    char **playground;
    int rows;
    int columns;
    char directions[0];

    int position[2];
    bool won;
    int score;
};
struct stage current_stage;

void show_stages(bool loaded) {
    if (!loaded) {
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
    } else {
        for (int i = 0; i < current_stage.rows; i++) {
            for (int j = 0; j < current_stage.columns; j++) {
                printf("%c", current_stage.playground[i][j]);
            }
            printf("\n");
        }
    }
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
                        if (c == 'o') {
                            current_stage.position[0] = i;
                            current_stage.position[1] = j;
                        }
                    } while (c == '\n');
                }
            }

        }
        if (selected) {
            break;
        }
    }
}

void clear () {
    printf("\e[1;1H\e[2J");
}

void move (char direction) {
    char next_position;
    bool scored = false;
    switch (direction) {
        case 'h':
            next_position = current_stage.playground[current_stage.position[0]][current_stage.position[1]-1];

            if (next_position != '#' && next_position == '_') {
                current_stage.playground[current_stage.position[0]][current_stage.position[1]] = ' ';
                current_stage.playground[current_stage.position[0]][current_stage.position[1]-1] = 'o';
                current_stage.position[1] = current_stage.position[1]-1;

                current_stage.score--;

                clear();
                show_stages(true);
                printf("hai vinto\n");
                current_stage.won = true;
            } else if (next_position != '#') {
                if (next_position == '$') {
                    current_stage.score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    current_stage.score /= 2;
                    scored = true;
                }
                current_stage.playground[current_stage.position[0]][current_stage.position[1]] = ' ';
                current_stage.playground[current_stage.position[0]][current_stage.position[1]-1] = 'o';
                current_stage.position[1] = current_stage.position[1]-1;

                if (!scored) {
                    current_stage.score--;
                }

                clear();
                show_stages(true);
            }
            else {
                printf("mossa non valida\n");
            }
            break;
        case 'j':
            next_position = current_stage.playground[current_stage.position[0]+1][current_stage.position[1]];

            if (next_position != '#' && next_position == '_') {
                current_stage.playground[current_stage.position[0]][current_stage.position[1]] = ' ';
                current_stage.playground[current_stage.position[0]+1][current_stage.position[1]] = 'o';
                current_stage.position[0] = current_stage.position[0]+1;

                current_stage.score--;

                clear();
                show_stages(true);
                printf("hai vinto\n");
                current_stage.won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    current_stage.score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    current_stage.score /= 2;
                    scored = true;
                }
                current_stage.playground[current_stage.position[0]][current_stage.position[1]] = ' ';
                current_stage.playground[current_stage.position[0]+1][current_stage.position[1]] = 'o';
                current_stage.position[0] = current_stage.position[0]+1;

                if (!scored) {
                    current_stage.score--;
                }

                clear();
                show_stages(true);
            }
            else {
                printf("mossa non valida\n");
            }
            break;
        case 'k':
            next_position = current_stage.playground[current_stage.position[0]-1][current_stage.position[1]];
            if (next_position != '#' && next_position == '_') {
                current_stage.playground[current_stage.position[0]][current_stage.position[1]] = ' ';
                current_stage.playground[current_stage.position[0]-1][current_stage.position[1]] = 'o';
                current_stage.position[0] = current_stage.position[0]-1;

                current_stage.score--;

                clear();
                show_stages(true);
                printf("hai vinto\n");
                current_stage.won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    current_stage.score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    current_stage.score /= 2;
                    scored = true;
                }
                current_stage.playground[current_stage.position[0]][current_stage.position[1]] = ' ';
                current_stage.playground[current_stage.position[0]-1][current_stage.position[1]] = 'o';
                current_stage.position[0] = current_stage.position[0]-1;

                if (!scored) {
                    current_stage.score--;
                }

                clear();
                show_stages(true);
            }
            else {
                printf("mossa non valida\n");
            }

            break;
        case 'l':
            next_position = current_stage.playground[current_stage.position[0]][current_stage.position[1]+1];
            if (next_position != '#' && next_position == '_') {
                current_stage.playground[current_stage.position[0]][current_stage.position[1]] = ' ';
                current_stage.playground[current_stage.position[0]][current_stage.position[1]+1] = 'o';
                current_stage.position[1] = current_stage.position[1]+1;

                current_stage.score--;

                clear();
                show_stages(true);
                printf("hai vinto\n");
                current_stage.won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    current_stage.score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    current_stage.score /= 2;
                    scored = true;
                }
                current_stage.playground[current_stage.position[0]][current_stage.position[1]] = ' ';
                current_stage.playground[current_stage.position[0]][current_stage.position[1]+1] = 'o';
                current_stage.position[1] = current_stage.position[1]+1;

                if (!scored) {
                    current_stage.score--;
                }

                clear();
                show_stages(true);
            }
            else {
                printf("mossa non valida\n");
            }
            break;
    }

}

int main() {
    char stage[2] = "x\n";
    char direction;
    current_stage.won = false;
    current_stage.score = 0;

    printf("Benvenuto su snake labyrinth\n");
    show_stages(false);

    do {
        printf("Seleziona una mappa (1 - 2)\n");
        scanf("%c", &stage[0]);
    } while (stage[0] != '1' && stage[0] != '2');

    load_labyrinth(stage);
    printf("\e[1;1H\e[2JMappa selezionata:\n");
    show_stages(true);

    do {
        do {
            printf("Inserisci la tua mossa (h - j - k - l)\n");
            scanf(" %c", &direction);
            move(direction);
            printf("Punteggio attuale: %d\n", current_stage.score);
        } while (direction != 'h' && direction != 'j' && direction != 'k' && direction != 'l');
    } while (!current_stage.won);
    printf("Il tuo punteggio: %d\n", current_stage.score);

    return 0;
}
