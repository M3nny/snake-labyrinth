#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct stage {
    char **playground; // contiene il livello
    int rows; // righe del labirinto
    int columns; // colonne del labirinto

    int position[2]; // position[0] è la riga attuale, position[1] è la colonna attuale
    char starting_wall;
    bool won; // flag per vedere se il giocatore ha vinto

    char *moves_storage;
    int score; // tiene conto del punteggio
};
struct stage current_stage;

// se il livello deve ancora essere selezionato stampo tutto il file
// altrimenti stampo il livello caricato in memoria
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
    current_stage.playground = malloc( sizeof *current_stage.playground * current_stage.rows);
    if (current_stage.playground) { // controllo se il malloc è riuscito
        for ( size_t i = 0; i < current_stage.rows; i++ ) {
            current_stage.playground[i] = malloc( sizeof *current_stage.playground[i] * current_stage.columns);
        }
    } else {
        printf("Caricamento del livello non riuscito\n");
        exit(EXIT_FAILURE);
    }

    // rimando all'inizio il puntatore del file
    // poi con un'operazione analoga alla precedente, metto dentro alla matrice il livello selezionato
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

                            if (current_stage.position[1] == 0) {
                                current_stage.starting_wall = 'w';
                            } else if (current_stage.position[0] == (current_stage.rows - 1))
                                current_stage.starting_wall = 's';
                            else if (current_stage.position[0] == 0) {
                                current_stage.starting_wall = 'n';
                            }
                            else if (current_stage.position[1] == (current_stage.columns - 1)) {
                                current_stage.starting_wall = 'e';
                            }
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
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void move (char direction) {
    char next_position;
    bool pierced_wall;
    bool scored = false;
    switch (direction) {
        case 'h':
            next_position = current_stage.playground[current_stage.position[0]][current_stage.position[1]-1];

            if (next_position != '#' && next_position == '_') { // se ha raggiunto l'uscita
                current_stage.playground[current_stage.position[0]][current_stage.position[1]] = ' ';
                current_stage.playground[current_stage.position[0]][current_stage.position[1]-1] = 'o';
                current_stage.position[1] = current_stage.position[1]-1;

                current_stage.score--;

                clear();
                show_stages(true);
                printf("hai vinto\n");
                current_stage.won = true;
            } else if (next_position != '#') { // se non va contro un muro e fuori per l'entrata
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
            if (current_stage.starting_wall == 'w') {
                pierced_wall = true;
                printf("muro iniziale a ovest\n");
            }
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
    int mode;
    char stage[2] = "x\n";
    char direction;
    int moves_counter = 0;

    current_stage.moves_storage = malloc(sizeof *current_stage.moves_storage * 1);
    current_stage.won = false;
    current_stage.score = 0;

    printf("Benvenuto su snake labyrinth\n");
    do {
        printf("Seleziona la modalità:\n1 - Singleplayer\n2 - Computer Random\n");
        printf("(input modalità): ");
        scanf("%d", &mode);
    } while (mode != 1 && mode != 2);
    show_stages(false);

    do {
        printf("\nSeleziona una mappa (1 - 2)\n");
        printf("(input mappa): ");
        scanf(" %c", &stage[0]);
    } while (stage[0] != '1' && stage[0] != '2');

    load_labyrinth(stage);
    clear();
    printf("Mappa selezionata:\n");
    show_stages(true);

    do {
        do {
            printf("Inserisci la tua mossa (h - j - k - l)\n");
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
            move(direction);

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
