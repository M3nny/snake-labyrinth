void move (char direction, struct labyrinth_stage *stage, struct labyrinth_player *player) {
    char next_position;
    bool scored = false;
        if (direction == player->left) {
            // prima di effettuare altri controlli, guardo se la mossa mi fa andare fuori dal labirinto
            if (player->position[1]-1 < 0) {
                return;
            }

            next_position = stage->playground[player->position[0]][player->position[1]-1];

            if (next_position != '#' && next_position == '_') { // se ha raggiunto l'uscita
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]][player->position[1]-1] = 'o';
                player->position[1] = player->position[1]-1;

                player->score--;
                player->won = true;
            } else if (next_position != '#') {
                if (next_position == '$') {
                    player->score += 10;
                    scored = true;
                }
                if (next_position == '!') {
                    player->score /= 2;
                    scored = true;
                }
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]][player->position[1]-1] = 'o';
                player->position[1] = player->position[1]-1;

                if (!scored) {
                    player->score--;
                }
            }
        } else if (direction == player->down) {
            if (player->position[0]+1 >= stage->rows) {
                return;
            }

            next_position = stage->playground[player->position[0]+1][player->position[1]];

            if (next_position != '#' && next_position == '_') {
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]+1][player->position[1]] = 'o';
                player->position[0] = player->position[0]+1;

                player->score--;
                player->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    player->score += 10;
                    scored = true;
                }
                if (next_position == '!') {
                    player->score /= 2;
                    scored = true;
                }
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]+1][player->position[1]] = 'o';
                player->position[0] = player->position[0]+1;

                if (!scored) {
                    player->score--;
                }
            }
        } else if (direction == player->up) {
            if (player->position[0]-1 < 0) {
                return;
            }

            next_position = stage->playground[player->position[0]-1][player->position[1]];

            if (next_position != '#' && next_position == '_') {
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]-1][player->position[1]] = 'o';
                player->position[0] = player->position[0]-1;

                player->score--;
                player->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    player->score += 10;
                    scored = true;
                }
                if (next_position == '!') {
                    player->score /= 2;
                    scored = true;
                }
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]-1][player->position[1]] = 'o';
                player->position[0] = player->position[0]-1;

                if (!scored) {
                    player->score--;
                }
            }
        } else if (direction == player->right) {
            if (player->position[1]+1 >= stage->columns) {
                return;
            }

            next_position = stage->playground[player->position[0]][player->position[1]+1];

            if (next_position != '#' && next_position == '_') {
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]][player->position[1]+1] = 'o';
                player->position[1] = player->position[1]+1;

                player->score--;
                player->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    player->score += 10;
                    scored = true;
                }
                if (next_position == '!') {
                    player->score /= 2;
                    scored = true;
                }
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]][player->position[1]+1] = 'o';
                player->position[1] = player->position[1]+1;

                if (!scored) {
                    player->score--;
                }
            }
    }
}
