/**
 * \file challenges.c
 * \brief Contiene l'algoritmo usato per la soluzione delle challenge
*/

/// Trovato un muro provo ad aggirarlo sia da un lato e sia dall'altro, poi valuto quale è l'opzione più conveniente
int find_best_track(char direction, list **tail, labyrinth_stage *stage_AI, labyrinth_player *bot) {
    int checkpoint[] = {bot->position[0], bot->position[1], bot->score}; // prima di provare ad aggirare il muro in entrambre le direzioni, mi salvo lo stato attuale di snake al momento in cui trova il muro
    int track_score;

    if (direction == bot->left) { // se incontro il muro da sinistra
        while (stage_AI->playground[bot->position[0]][bot->position[1] - 1] == '#') { // controllo che punteggio ottengo aggirando il muro andando in su
            move(bot->up, tail, stage_AI, bot);
            stage_AI->playground[bot->position[0] + 1][bot->position[1]] = ' ';
            if (stage_AI->playground[bot->position[0] - 1][bot->position[1]] == '#') {
                break;
            }
        }
        track_score = bot->score; // tengo conto del punteggio ottenuto aggirando il muro andando verso su
        // resetto la posizione di snake a dove era prima di aggirare il muro
        bot->score = checkpoint[2];
        bot->position[0] = checkpoint[0];
        bot->position[1] = checkpoint[1];

        while (stage_AI->playground[bot->position[0]][bot->position[1] - 1] == '#') { // controllo che punteggio ottengo aggirando il muro andando in giù
            move(bot->down, tail, stage_AI, bot);
            stage_AI->playground[bot->position[0] - 1][bot->position[1]] = ' ';
            if (stage_AI->playground[bot->position[0] + 1][bot->position[1]] == '#') {
                break;
            }
        }
        bot->position[0] = checkpoint[0];
        bot->position[1] = checkpoint[1];

        if (track_score > bot->score) { // se andare in su mi ha generato un punteggio maggiore di andare in giù, allora dico che la scelta da fare è andare su
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

/// Aggiro il muro in base alla direzione da cui proviene il bot
void avoid_wall(char direction, list **tail, labyrinth_stage *stage_AI, labyrinth_player *bot) {
    int choice = 0;
    if (direction == bot->left) { // se incontro il muro da sinistra
        while (stage_AI->playground[bot->position[0]][bot->position[1] - 1] == '#') { // finchè a sinistra ho il muro
            // se sono arrivato da sotto oppure la strada più breve è andare su allora vado su
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

/// Esegue l'algoritmo usato nella risoluzione della challenges
/**
 * 1. Inizializzo il necessario
 * 2. Prendo in input la matrice di gioco
 * 3. Eseguo la mossa che mi consente di uscire dal punto di partenza
 * 4. Mi allineo orizzontalmente/verticalmente in base a dove è il bot e l'uscita (evitando i muri)
 * 5. Quando mi sono allineato vado dritto verso l'uscita (evitando i muri)
 * 6. Libero la memoria allocata
*/
void bot_algorithm(list *tail, labyrinth_stage stage_AI, labyrinth_player bot) {
    int gate[2];
    bool aligned = false;

    for (int i = 0; i < stage_AI.rows; i++) {
        for (int j = 0; j < stage_AI.columns; j++) {
            if (stage_AI.playground[i][j] == 'o') {
                bot.position[0] = i;
                bot.position[1] = j;
            } else if (stage_AI.playground[i][j] == '_') {
                gate[0] = i;
                gate[1] = j;

            }
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
        }

        // se sono allineato verticalmente o orizzontalmente, vado verso l'uscita
        // se trovo un muro e non ho il trapano, lo aggiro
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
    clear();
    show_stages(true, tail, &stage_AI);
    printf("Elenco delle mosse eseguite: ");
    for (int i = 0; i < bot.moves_counter; i++) {
        printf("%c", bot.moves_storage[i]);
    }
    printf("\n");
}
