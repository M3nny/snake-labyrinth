/**
 * \file game_manager.h
 * \brief Logica del gioco
*/

/// Contiene la matrice su cui si svolge il gioco e la sua grandezza
typedef struct {
    char **playground; ///< contiene il livello
    int rows; ///< righe del labirinto
    int columns; ///< colonne del labirinto
} labyrinth_stage;

/// Contiene tutti i valori attuali del giocatore
typedef struct {
    int position[2]; ///< position[0] è la riga attuale, position[1] è la colonna attuale
    bool won; ///< flag per vedere se il giocatore ha vinto
    char *moves_storage; ///< contiene tutte le mosse eseguite
    int moves_counter; ///< contiene il numero di mosse eseguite
    int score; ///< tiene conto del punteggio
    char left, up, down, right; ///< contiene il simbolo usato per andare nella rispettiva direzione
    int drill; ///< tiene conto di quanti muri si possono attraversare 
} labyrinth_player;

/// Per ogni elemento della coda, mette il simbolo x nella matrice di gioco
void show_tail(list *tail, labyrinth_stage *stage) {
    if (tail == NULL) {
        return;
    }
    stage->playground[tail->rows][tail->columns] = 'x';
    show_tail(tail->next, stage);
}

/// Cancella la coda (all'occhio dell'utente) dalla matrice
void delete_old_tail(labyrinth_stage *stage) {
    for (int i = 0; i < stage->rows; i++) {
        for (int j = 0; j < stage->columns; j++) {
            if (stage->playground[i][j] == 'x') {
                stage->playground[i][j] = ' ';
            }
        }
    }
}

/// Stampa la matrice di gioco
/** 
 * se il livello deve ancora essere selezionato stampo tutto il file
 * contenente i livelli, altrimenti stampo il livello caricato in memoria
*/
void show_stages(bool loaded, list *tail, labyrinth_stage *stage) {
    if (!loaded) {
        FILE* file = fopen("labyrinths/labyrinths.txt", "r");

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

/// Carica in memoria la matrice di gioco e inizializza i valori della struct labyrinth_player
/**
 * la matrice può essere caricata in due modi: 
 * inserendola manualmente oppure
 * caricandola dal file contenente alcuni livelli già fatti
*/
void load_game(char *stage_no, labyrinth_stage *stage, labyrinth_player *player) {

    player->won = false;
    player->score = 1000;
    player->drill = 0;
    player->left = 'h';
    player->up = 'k';
    player->down = 'j';
    player->right = 'l';
    player->moves_storage = malloc(sizeof(char) * 1);
    player->moves_counter = 0;

    if (stage_no[0] != '0') {
        char line[50];
        int rows = 0, columns = 0; // numero di righe e colonne
        char c;

        FILE* file = fopen("labyrinths/labyrinths.txt", "r");

        if(!file) {
            printf("\n Unable to open file");
            exit(EXIT_FAILURE);
        }
        
        while (fgets(line, sizeof(line), file)) { // leggo tutto il file e stoppo il ciclo dopo aver letto il labirinto
            if ((strcmp(line, stage_no)) == 0) { // se trovo il numero corrispondente al labirinto comincio a leggerlo
                while (fgets(line, sizeof(line), file)) { // leggo il labirinto finchè non trovo end
                    if ((strcmp(line, "end\n")) == 0) {
                        break;
                    }
                    columns = strlen(line) - 1;
                    rows++;
                }
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

        while (fgets(line, sizeof(line), file)) { // leggo tutto il file e stoppo il ciclo dopo aver letto il labirinto
            if ((strcmp(line, stage_no)) == 0) { // se trovo il numero corrispondente al labirinto comincio a leggerlo
                // metto dentro alla matrice tutti gli elementi
                for (int i = 0; i < stage->rows; i++) {
                    for (int j = 0; j < stage->columns; j++) {
                        do {
                            c = fgetc(file);
                            stage->playground[i][j] = c;
                            if (c == 'o') {
                                player->position[0] = i;
                                player->position[1] = j;
                            }
                        } while (c == '\n');
                    }
                }
                break;
            }
        }
    } else {
        scanf("%d", &stage->columns);
        scanf("%d", &stage->rows);
        char input[stage->rows];

        stage->playground = malloc( sizeof *stage->playground * stage->rows);
        if (stage->playground) { // controllo se il malloc è riuscito
            for ( size_t i = 0; i < stage->rows; i++ ) {
                stage->playground[i] = malloc( sizeof *stage->playground[i] * stage->columns);
            }
        } else {
            printf("Caricamento del livello non riuscito\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < stage->rows; i++) {
            scanf(" %[^\n]%*c", input);
            for (int j = 0; j < stage->columns; j++) {
                if (input[j] == 'o') {
                    player->position[0] = i;
                    player->position[1] = j;
                }
                stage->playground[i][j] = input[j];
            }
        }
    }
}

/// Inserisce dentro a moves_storage la mossa passata come parametro
void store_move(char direction, labyrinth_player *player) {
    player->moves_storage[player->moves_counter] = direction;
    player->moves_counter++;
    player->moves_storage = realloc(player->moves_storage, (player->moves_counter + 1) * sizeof(char));
}

/// Dealloca dalla memoria la matrice di gioco e gli altri dati precedentementi allocati prima di finire l'esecuzione del programma
void free_game(labyrinth_stage *stage, labyrinth_player *player, list *tail) {
    for (size_t i = 0; i < stage->rows; i++ ) {
        free(stage->playground[i]);
    }
    free(stage->playground);
    free(player->moves_storage);
    delete_tail(tail);
}

/// Pulisco l'interfaccia del terminale
/**
 * se l'OS è unix like, verrà usato il comando clear, altrimenti viene usato cls per windows
*/
void clear () {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
