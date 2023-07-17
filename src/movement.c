/**
 * \file movement.c
 * \brief Movimento di snake
*/

int validate_move (char next_position, int *next_coordinates, list **tail, labyrinth_player *player);

/// Muove la testa di snake
/**
 * Se non ha ancora una coda, lascierà dietro di sè il simbolo '.' inoltre prima di eseguire una mossa verifica se è possibile eseguirla
*/
void move (char direction, list **tail, labyrinth_stage *stage, labyrinth_player *player) {
    char next_position;
    int next_coordinates[2];

    if (direction == player->left) {
        // prima di effettuare altri controlli, guardo se la mossa mi fa andare fuori dal labirinto
        if (player->position[1]-1 < 0) {
            return;
        }
        next_position = stage->playground[player->position[0]][player->position[1]-1];
        next_coordinates[0] = player->position[0];
        next_coordinates[1] = player->position[1]-1;

        if (validate_move(next_position, next_coordinates, tail, player) != -1) {
            // aggiorno la posizione, se la coda non è presente, verrà visualizzato un . come traccia del percorso fatto
            stage->playground[player->position[0]][player->position[1]] = '.';
            stage->playground[player->position[0]][player->position[1]-1] = 'o';
            player->position[1] = player->position[1]-1;
        }

    } else if (direction == player->down) {
        if (player->position[0]+1 >= stage->rows) {
            return;
        }
        next_position = stage->playground[player->position[0]+1][player->position[1]];
        next_coordinates[0] = player->position[0]+1;
        next_coordinates[1] = player->position[1];

        if (validate_move(next_position, next_coordinates, tail, player) != -1) {
            stage->playground[player->position[0]][player->position[1]] = '.';
            stage->playground[player->position[0]+1][player->position[1]] = 'o';
            player->position[0] = player->position[0]+1;
        }

    } else if (direction == player->up) {
        if (player->position[0]-1 < 0) {
            return;
        }
        next_position = stage->playground[player->position[0]-1][player->position[1]];
        next_coordinates[0] = player->position[0]-1;
        next_coordinates[1] = player->position[1];

        if (validate_move(next_position, next_coordinates, tail, player) != -1) {
            stage->playground[player->position[0]][player->position[1]] = '.';
            stage->playground[player->position[0]-1][player->position[1]] = 'o';
            player->position[0] = player->position[0]-1;
        }

    } else if (direction == player->right) {
        if (player->position[1]+1 >= stage->columns) {
            return;
        }
        next_position = stage->playground[player->position[0]][player->position[1]+1];
        next_coordinates[0] = player->position[0];
        next_coordinates[1] = player->position[1]+1;

        if (validate_move(next_position, next_coordinates, tail, player) != -1) {
            stage->playground[player->position[0]][player->position[1]] = '.';
            stage->playground[player->position[0]][player->position[1]+1] = 'o';
            player->position[1] = player->position[1]+1;
        }
    }
}

/// Muove la coda di snake
void move_tail(list **tail, int rows, int columns) {
    if (*tail == NULL) { // se la coda non esiste
        return;
    }
    if (((*tail)->next) == NULL) { // se è l'ultimo nodo della coda copio l'ultima posizione del giocatore prima di fare la mossa
        (*tail)->rows = rows;
        (*tail)->columns = columns;
        return;
    }
    (*tail)->rows = ((*tail)->next)->rows;
    (*tail)->columns = ((*tail)->next)->columns;
    move_tail(&(*tail)->next, rows, columns);
}

/// Gestisce i vari casi che si possono verificare prima di muovere effettivamente snake
/**
 * Se trovo:\n
 * $: aggiungo un elemento alla coda e aggiungo 10 punti al giocatore\n
 * _: il giocatore ha vinto\n
 * !: i punti vengono dimezzati, lo stesso per la coda\n
 * x: trovo quale è l'indice di quell'elemento della coda ed eseguo n volte la funzione pop in base al valore dell'indice\n
 * T: il giocatore può attraversare altre 3 pareti (non può andare fuori dal labirinto)\n
 * #: avendo il trapano posso superare la parete, inoltre diminuisco gli usi possibili del trapano di 1
*/
int validate_move (char next_position, int *next_coordinates, list **tail, labyrinth_player *player) {
    int scored = 0;
    if (next_position != '#' || (next_position == '#' && player->drill > 0)) { // se la prossima cella non è un muro valuto tutte le possibili opzioni
        if (next_position == '$') { // punti bonus
            list_append(tail, player->position[0], player->position[1]);
            player->score += 10;
            scored = 1;
        } else {
            if (next_position == '_') { // ha vinto
                player->won = true;
            }
            if (next_position == '!') { // punti dimezzati
                int snake_length = get_tail_length(*tail) ;
                for (int i = 0; i < snake_length/2; i++) { // dimezzo la lunghezza della coda di snake
                    pop(tail);
                }
                player->score /= 2;
                scored = 1;
            }
            if (next_position == 'x') {
                int index = get_node_index(*tail, next_coordinates[0], next_coordinates[1]);
                for (int i = 0; i < index; i++) {
                    pop(tail);
                    player->score -= 10;
                }
                scored = 1;
            }
            if (next_position == 'T') {
                player->drill += 3;
            }
            if (next_position == '#') {
                player->drill--;
            }

            if (scored != 1) {
                player->score--;
            }
            move_tail(tail, player->position[0], player->position[1]);
        }
    } else {
        return -1;
    }

    return scored;
}
