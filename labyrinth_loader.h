typedef struct {
    char **playground; // contiene il livello
    int rows; // righe del labirinto
    int columns; // colonne del labirinto
} labyrinth_stage;


typedef struct {
    int position[2]; // position[0] è la riga attuale, position[1] è la colonna attuale
    int origin[2];
    bool won; // flag per vedere se il giocatore ha vinto
    char *moves_storage;
    int score; // tiene conto del punteggio
    char left, up, down, right;
    int drill;
} labyrinth_player;

void show_tail(vector *tail, labyrinth_stage *stage) {
    if (tail == NULL) {
        return;
    }
    stage->playground[tail->rows][tail->columns] = 'x';
    show_tail(tail->next, stage);
}

void delete_old_tail(labyrinth_stage *stage) {
    for (int i = 0; i < stage->rows; i++) {
        for (int j = 0; j < stage->columns; j++) {
            if (stage->playground[i][j] == 'x') {
                stage->playground[i][j] = ' ';
            }
        }
    }
}

// se il livello deve ancora essere selezionato stampo tutto il file
// altrimenti stampo il livello caricato in memoria
void show_stages(bool loaded, vector *tail, labyrinth_stage *stage) {
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
        delete_old_tail(stage);
        show_tail(tail, stage);
        for (int i = 0; i < stage->rows; i++) {
            for (int j = 0; j < stage->columns; j++) {
                printf("%c", stage->playground[i][j]);
            }
            printf("\n");
        }
    }
}


void load_game (const char *stage_no, labyrinth_stage *stage, labyrinth_player *player) {
    FILE* file = fopen("labyrinth.txt", "r");

    if(!file) {
        printf("\n Unable to open file");
        exit(EXIT_FAILURE);
    }

    char line[50];
    int rows = 0, columns = 0; // numero di righe e colonne
    bool selected = false;
    char c;
    player->drill = 0;
    player->won = false;
    player->score = 1000;
    player->left = 'h';
    player->up = 'k';
    player->down = 'j';
    player->right = 'l';
    player->moves_storage = malloc(sizeof(char) * 1);

    while (fgets(line, sizeof(line), file)) { // leggo tutto il file e stoppo il ciclo dopo aver letto il labirinto
        if ((strcmp(line, stage_no)) == 0) { // se trovo il numero corrispondente al labirinto comincio a leggerlo
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

    stage->rows = rows;
    stage->columns = columns;

    // ridimensiono la matrice in base al labirinto selezionato
    stage->playground = malloc( sizeof *stage->playground * stage->rows);
    if (stage->playground) { // controllo se il malloc è riuscito
        for ( size_t i = 0; i < stage->rows; i++ ) {
            stage->playground[i] = malloc( sizeof *stage->playground[i] * stage->columns);
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
        if ((strcmp(line, stage_no)) == 0) { // se trovo il numero corrispondente al labirinto comincio a leggerlo
            selected = true;

            // metto dentro alla matrice tutti gli elementi che non sono \n
            for (int i = 0; i < stage->rows; i++) {
                for (int j = 0; j < stage->columns; j++) {
                    do {
                        c = fgetc(file);
                        stage->playground[i][j] = c;
                        if (c == 'o') {
                            player->origin[0] = i;
                            player->origin[1] = j;
                            player->position[0] = i;
                            player->position[1] = j;
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
