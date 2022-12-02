int validate_move (char next_position, struct labyrinth_player *player);

void move (char direction, struct labyrinth_stage *stage, struct labyrinth_player *player) {
    char next_position;
    if (direction == player->left) {
        // prima di effettuare altri controlli, guardo se la mossa mi fa andare fuori dal labirinto
        if (player->position[1]-1 < 0) {
            return;
        }
        next_position = stage->playground[player->position[0]][player->position[1]-1];

        if (validate_move(next_position, player) != -1) {
            // aggiorno la posizione
            stage->playground[player->position[0]][player->position[1]] = '.';
            stage->playground[player->position[0]][player->position[1]-1] = 'o';
            player->position[1] = player->position[1]-1;
        }

    } else if (direction == player->down) {
        if (player->position[0]+1 >= stage->rows) {
            return;
        }
        next_position = stage->playground[player->position[0]+1][player->position[1]];

        if (validate_move(next_position, player) != -1) {
            stage->playground[player->position[0]][player->position[1]] = '.';
            stage->playground[player->position[0]+1][player->position[1]] = 'o';
            player->position[0] = player->position[0]+1;
        }

    } else if (direction == player->up) {
        if (player->position[0]-1 < 0) {
            return;
        }
        next_position = stage->playground[player->position[0]-1][player->position[1]];

        if (validate_move(next_position, player) != -1) {
            stage->playground[player->position[0]][player->position[1]] = '.';
            stage->playground[player->position[0]-1][player->position[1]] = 'o';
            player->position[0] = player->position[0]-1;
        }

    } else if (direction == player->right) {
        if (player->position[1]+1 >= stage->columns) {
            return;
        }
        next_position = stage->playground[player->position[0]][player->position[1]+1];

        if (validate_move(next_position, player) != -1) {
            stage->playground[player->position[0]][player->position[1]] = '.';
            stage->playground[player->position[0]][player->position[1]+1] = 'o';
            player->position[1] = player->position[1]+1;
        }
    }
}

int validate_move (char next_position, struct labyrinth_player *player) {
    int scored = 0;
    if (next_position != '#' || (next_position == '#' && player->drill > 0)) { // se la prossima cella non è un muro valuto tutte le possibili opzioni
        if (next_position == '_') { // ha vinto
            player->won = true;
        }
        if (next_position == '$') { // punti bonus
            player->score += 10;
            scored = 1;
        }
        if (next_position == '!') { // punti dimezzati
            player->score /= 2;
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
    } else {
        return -1;
    }

    return scored;
}
