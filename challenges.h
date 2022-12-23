int find_best_track (char direction, vector **tail, labyrinth_stage *stage_AI, labyrinth_player *bot) {
    int checkpoint[] = {bot->position[0], bot->position[1], bot->score};
    int track_score;
    if (direction == bot->left) {
        while (stage_AI->playground[bot->position[0]][bot->position[1] - 1] == '#') {
            move(bot->up, tail, stage_AI, bot);
            stage_AI->playground[bot->position[0] + 1][bot->position[1]] = ' ';
            if (stage_AI->playground[bot->position[0] - 1][bot->position[1]] == '#') {
                break;
            }
        }
        track_score = bot->score;
        bot->score = checkpoint[2];
        bot->position[0] = checkpoint[0];
        bot->position[1] = checkpoint[1];

        while (stage_AI->playground[bot->position[0]][bot->position[1] - 1] == '#') {
            move(bot->down, tail, stage_AI, bot);
            stage_AI->playground[bot->position[0] - 1][bot->position[1]] = ' ';
            if (stage_AI->playground[bot->position[0] + 1][bot->position[1]] == '#') {
                break;
            }
        }
        bot->position[0] = checkpoint[0];
        bot->position[1] = checkpoint[1];

        if (track_score > bot->score) {
            bot->score = checkpoint[2];
            return 1;
        } else {
            bot->score = checkpoint[2];
            return 2;
        }
    }

    if (direction == bot->right) {
        while (stage_AI->playground[bot->position[0]][bot->position[1] + 1] == '#') {
            move(bot->up, tail, stage_AI, bot);
            stage_AI->playground[bot->position[0] + 1][bot->position[1]] = ' ';
            if (stage_AI->playground[bot->position[0] - 1][bot->position[1]] == '#') {
                break;
            }
        }
        track_score = bot->score;
        bot->score = checkpoint[2];
        bot->position[0] = checkpoint[0];
        bot->position[1] = checkpoint[1];

        while (stage_AI->playground[bot->position[0]][bot->position[1] + 1] == '#') {
            move(bot->down, tail, stage_AI, bot);
            stage_AI->playground[bot->position[0] - 1][bot->position[1]] = ' ';
            if (stage_AI->playground[bot->position[0] + 1][bot->position[1]] == '#') {
                break;
            }
        }
        bot->position[0] = checkpoint[0];
        bot->position[1] = checkpoint[1];

        if (track_score > bot->score) {
            bot->score = checkpoint[2];
            return 1;
        } else {
            bot->score = checkpoint[2];
            return 2;
        }
    }

    if (direction == bot->up) {
        while (stage_AI->playground[bot->position[0] - 1][bot->position[1]] == '#') {
            move(bot->left, tail, stage_AI, bot);
            stage_AI->playground[bot->position[0]][bot->position[1] + 1] = ' ';
            if (stage_AI->playground[bot->position[0]][bot->position[1] - 1] == '#') {
                break;
            }
        }
        track_score = bot->score;
        bot->score = checkpoint[2];
        bot->position[0] = checkpoint[0];
        bot->position[1] = checkpoint[1];

        while (stage_AI->playground[bot->position[0] - 1][bot->position[1]] == '#') {
            move(bot->right, tail, stage_AI, bot);
            stage_AI->playground[bot->position[0]][bot->position[1] - 1] = ' ';
            if (stage_AI->playground[bot->position[0]][bot->position[1] + 1] == '#') {
                break;
            }
        }
        bot->position[0] = checkpoint[0];
        bot->position[1] = checkpoint[1];

        if (track_score > bot->score) {
            bot->score = checkpoint[2];
            return 1;
        } else {
            bot->score = checkpoint[2];
            return 2;
        }
    }

    if (direction == bot->down) {
        while (stage_AI->playground[bot->position[0] + 1][bot->position[1]] == '#') {
            move(bot->left, tail, stage_AI, bot);
            stage_AI->playground[bot->position[0]][bot->position[1] + 1] = ' ';
            if (stage_AI->playground[bot->position[0]][bot->position[1] - 1] == '#') {
                break;
            }
        }
        track_score = bot->score;
        bot->score = checkpoint[2];
        bot->position[0] = checkpoint[0];
        bot->position[1] = checkpoint[1];

        while (stage_AI->playground[bot->position[0] + 1][bot->position[1]] == '#') {
            move(bot->right, tail, stage_AI, bot);
            stage_AI->playground[bot->position[0]][bot->position[1] - 1] = ' ';
            if (stage_AI->playground[bot->position[0]][bot->position[1] + 1] == '#') {
                break;
            }
        }
        bot->position[0] = checkpoint[0];
        bot->position[1] = checkpoint[1];

        if (track_score > bot->score) {
            bot->score = checkpoint[2];
            return 1;
        } else {
            bot->score = checkpoint[2];
            return 2;
        }
    }

    return 1;
}
// aggiro il muro in base alla direzione da cui proviene il bot
void avoid_wall (char direction, vector **tail, labyrinth_stage *stage_AI, labyrinth_player *bot) {
    int choice = 0;
    if (direction == bot->left) {
        while (stage_AI->playground[bot->position[0]][bot->position[1] - 1] == '#') {
            if (stage_AI->playground[bot->position[0] + 1][bot->position[1]] == '.' || stage_AI->playground[bot->position[0] + 1][bot->position[1]] == 'x' || choice == 1) {
                move(bot->up, tail, stage_AI, bot);
                store_move(bot->up, bot);
            } else if (stage_AI->playground[bot->position[0] - 1][bot->position[1]] == '.' || stage_AI->playground[bot->position[0] - 1][bot->position[1]] == 'x' || choice == 2){
                move(bot->down, tail, stage_AI, bot);
                store_move(bot->down, bot);
            } else {
                choice = find_best_track(direction, tail, stage_AI, bot);
            }
        }
    }

    if (direction == bot->right) {
        while (stage_AI->playground[bot->position[0]][bot->position[1] + 1] == '#') {
            if (stage_AI->playground[bot->position[0] + 1][bot->position[1]] == '.' || stage_AI->playground[bot->position[0] + 1][bot->position[1]] == 'x' || choice == 1) {
                move(bot->up, tail, stage_AI, bot);
                store_move(bot->up, bot);
            } else if (stage_AI->playground[bot->position[0] - 1][bot->position[1]] == '.' || stage_AI->playground[bot->position[0] - 1][bot->position[1]] == 'x' || choice == 2) {
                move(bot->down, tail, stage_AI, bot);
                store_move(bot->down, bot);
            } else {
                choice = find_best_track(direction, tail, stage_AI, bot);
            }
        }
    }

    if (direction == bot->up) {
        while (stage_AI->playground[bot->position[0] - 1][bot->position[1]] == '#') {
            if (stage_AI->playground[bot->position[0]][bot->position[1] + 1] == '.' || stage_AI->playground[bot->position[0]][bot->position[1] + 1] == 'x' || choice == 1) {
                move(bot->left, tail, stage_AI, bot);
                store_move(bot->left, bot);
            } else if (stage_AI->playground[bot->position[0]][bot->position[1] - 1] == '.' || stage_AI->playground[bot->position[0]][bot->position[1] - 1] == 'x' || choice == 2) {
                move(bot->right, tail, stage_AI, bot);
                store_move(bot->right, bot);
            } else {
                choice = find_best_track(direction, tail, stage_AI, bot);
            }
        }
    }

    if (direction == bot->down) {
        while (stage_AI->playground[bot->position[0] + 1][bot->position[1]] == '#') {
            if (stage_AI->playground[bot->position[0]][bot->position[1] + 1] == '.' || stage_AI->playground[bot->position[0]][bot->position[1] + 1] == 'x' || choice == 1) {
                move(bot->left, tail, stage_AI, bot);
                store_move(bot->left, bot);
            } else if (stage_AI->playground[bot->position[0]][bot->position[1] - 1] == '.' || stage_AI->playground[bot->position[0]][bot->position[1] - 1] == 'x' || choice == 2) {
                move(bot->right, tail, stage_AI, bot);
                store_move(bot->right, bot);
            } else {
                choice = find_best_track(direction, tail, stage_AI, bot);
            }
        }
    }
}

void challenge() {
    // inizializzo/dichiaro tutto il necessario
    labyrinth_stage stage_AI;
    labyrinth_player bot;
    vector *tail = NULL;

    scanf("%d", &stage_AI.columns);
    scanf("%d", &stage_AI.rows);
    char input[stage_AI.rows];
    int gate[2];
    bool aligned = false;
    bot.moves_storage = malloc(sizeof(char) * 1);

    // creo la matrice
    stage_AI.playground = malloc( sizeof *stage_AI.playground * stage_AI.rows);
    if (stage_AI.playground) { // controllo se il malloc è riuscito
        for ( size_t i = 0; i < stage_AI.rows; i++ ) {
            stage_AI.playground[i] = malloc( sizeof *stage_AI.playground[i] * stage_AI.columns);
        }
    } else {
        printf("Caricamento del livello non riuscito\n");
        exit(EXIT_FAILURE);
    }

    // inizializzo i campi all'interno della struct
    bot.won = false;
    bot.score = 1000;
    bot.drill = 0;
    bot.left = 'O';
    bot.down = 'S';
    bot.up = 'N';
    bot.right = 'E';

    // riempio la matrice e trovo il punto di partenza
    for (int i = 0; i < stage_AI.rows; i++) {
        scanf(" %[^\n]%*c", input);
        for (int j = 0; j < stage_AI.columns; j++) {
            if (input[j] == 'o') {
                bot.origin[0] = i;
                bot.origin[1] = j;
                bot.position[0] = i;
                bot.position[1] = j;
            } else if (input[j] == '_') {
                gate[0] = i;
                gate[1] = j;

            }

            stage_AI.playground[i][j] = input[j];
        }
    }

    // faccio la prima mossa per uscire dal punto di partenza
    if (bot.position[0] == 0) {
        move(bot.down, &tail, &stage_AI, &bot);
        store_move(bot.down, &bot);
    } else if (bot.position[0] == stage_AI.rows - 1) {
        move(bot.up, &tail, &stage_AI, &bot);
        store_move(bot.up, &bot);
    } else if (bot.position[1] == 0) {
        move(bot.right, &tail, &stage_AI, &bot);
        store_move(bot.right, &bot);
    } else if (bot.position[1] == stage_AI.columns - 1) {
        move(bot.left, &tail, &stage_AI, &bot);
        store_move(bot.left, &bot);
    }

    do {
        // cerco di allinearmi all'uscita, se non ci riesco  e non ho un trapano, aggiro il muro
        while (!aligned) {
            if (bot.position[0] == gate[0] || bot.position[1] == gate[1]) {
                aligned = true;
                break;
            }
            if (gate[0] == 0 || gate[0] == stage_AI.rows - 1) {
                // allineo orizzontalmente
                if(bot.position[1] < gate[1]) {
                    if (stage_AI.playground[bot.position[0]][bot.position[1] + 1] == '#' && bot.drill <= 0) {
                        avoid_wall(bot.right, &tail, &stage_AI, &bot);
                    }
                    move(bot.right, &tail, &stage_AI, &bot);
                    store_move(bot.right, &bot);
                } else if (bot.position[1] > gate[1]) {
                    if (stage_AI.playground[bot.position[0]][bot.position[1] - 1] == '#' && bot.drill <= 0) {
                        avoid_wall(bot.left, &tail, &stage_AI, &bot);
                    }
                    move(bot.left, &tail, &stage_AI, &bot);
                    store_move(bot.left, &bot);
                }
            } else {
                // allineo verticalmente
                if (bot.position[0] < gate[0]) {
                    if (stage_AI.playground[bot.position[0] + 1][bot.position[1]] == '#' && bot.drill <= 0) {
                        avoid_wall(bot.down, &tail, &stage_AI, &bot);
                    }
                    move(bot.down, &tail, &stage_AI, &bot);
                    store_move(bot.down, &bot);
                } else if (bot.position[0] > gate[0]) {
                    if (stage_AI.playground[bot.position[0] - 1][bot.position[1]] == '#' && bot.drill <= 0) {
                        avoid_wall(bot.up, &tail, &stage_AI, &bot);
                    }
                    move(bot.up, &tail, &stage_AI, &bot);
                    store_move(bot.up, &bot);
                }
            }
        };

        // se sono allineato verticalmente o orizzontalmente, vado verso l'uscita
        // se trovo un muro  e non ho il trapano, lo aggiro
        if (bot.position[0] == gate[0]) {
            if (bot.position[1] < gate[1]) {
                if (stage_AI.playground[bot.position[0]][bot.position[1] + 1] == '#' && bot.drill <= 0) {
                    avoid_wall(bot.right, &tail, &stage_AI, &bot);
                    aligned = false;
                }
                move(bot.right, &tail, &stage_AI, &bot);
                store_move(bot.right, &bot);
            } else {
                if (stage_AI.playground[bot.position[0]][bot.position[1] - 1] == '#' && bot.drill <= 0) {
                    avoid_wall(bot.left, &tail, &stage_AI, &bot);
                    aligned = false;
                }
                move(bot.left, &tail, &stage_AI, &bot);
                store_move(bot.left, &bot);
            }
        } else {
            if (bot.position[0] < gate[0]) {
                if (stage_AI.playground[bot.position[0] + 1][bot.position[1]] == '#' && bot.drill <= 0) {
                    avoid_wall(bot.down, &tail, &stage_AI, &bot);
                    aligned = false;
                }
                move(bot.down, &tail, &stage_AI, &bot);
                store_move(bot.down, &bot);
            } else {
                if (stage_AI.playground[bot.position[0] - 1][bot.position[1]] == '#' && bot.drill <= 0) {
                    avoid_wall(bot.up, &tail, &stage_AI, &bot);
                    aligned = false;
                }
                move(bot.up, &tail, &stage_AI, &bot);
                store_move(bot.up, &bot);
            }
        }
    } while (!bot.won);

    // stampo le mosse
    for (int i = 0; i < bot.moves_counter; i++) {
        printf("%c",bot.moves_storage[i]);
    }
    printf("\n");

    // libero la memoria allocata
    for ( size_t i = 0; i < stage_AI.rows; i++ ) {
        free(stage_AI.playground[i]);
    }
    free(stage_AI.playground);
    free(bot.moves_storage);
}
