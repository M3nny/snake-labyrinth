struct labyrinth_stage {
    char **playground; // contiene il livello
    int rows; // righe del labirinto
    int columns; // colonne del labirinto

    int position[2]; // position[0] è la riga attuale, position[1] è la colonna attuale
    int origin[2];
    bool won; // flag per vedere se il giocatore ha vinto

    char *moves_storage;
    int score; // tiene conto del punteggio
};

// se il livello deve ancora essere selezionato stampo tutto il file
// altrimenti stampo il livello caricato in memoria
void show_labyrinth_stages(bool loaded, struct labyrinth_stage *stage) {
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
        for (int i = 0; i < stage->rows; i++) {
            for (int j = 0; j < stage->columns; j++) {
                printf("%c", stage->playground[i][j]);
            }
            printf("\n");
        }
    }
}

void load_labyrinth (const char *labyrinth_stage, struct labyrinth_stage *stage) {
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
        if ((strcmp(line, labyrinth_stage)) == 0) { // se trovo il numero corrispondente al labirinto comincio a leggerlo
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
        if ((strcmp(line, labyrinth_stage)) == 0) { // se trovo il numero corrispondente al labirinto comincio a leggerlo
            selected = true;

            // metto dentro alla matrice tutti gli elementi che non sono \n
            for (int i = 0; i < stage->rows; i++) {
                for (int j = 0; j < stage->columns; j++) {
                    do {
                        c = fgetc(file);
                        stage->playground[i][j] = c;
                        if (c == 'o') {
                            stage->origin[0] = i;
                            stage->origin[1] = j;
                            stage->position[0] = i;
                            stage->position[1] = j;
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
