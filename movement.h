void move (char direction, struct labyrinth_stage *stage, struct labyrinth_player *player) {
    char next_position;
    bool scored = false;
        if (direction == player->left) {
            // prima di effettuare altri controlli, guardo se la mossa mi fa andare fuori da dove sono entrato
            next_position = stage->playground[player->position[0]][player->position[1]-1];
            if (next_position == 0) {
                return;
            }

            if (next_position != '#' && next_position == '_') { // se ha raggiunto l'uscita
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]][player->position[1]-1] = 'o';
                player->position[1] = player->position[1]-1;

                player->score--;
                player->won = true;
            } else if (next_position != '#') {
                if (next_position == '$') {
                    player->score += 3;
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
            next_position = stage->playground[player->position[0]+1][player->position[1]];
            if (next_position == stage->rows - 1) {
                return;
            }

            if (next_position != '#' && next_position == '_') {
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]+1][player->position[1]] = 'o';
                player->position[0] = player->position[0]+1;

                player->score--;
                player->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    player->score += 3;
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
            next_position = stage->playground[player->position[0]-1][player->position[1]];
            if (next_position == 0) {
                return;
            }

            if (next_position != '#' && next_position == '_') {
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]-1][player->position[1]] = 'o';
                player->position[0] = player->position[0]-1;

                player->score--;
                player->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    player->score += 3;
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
            next_position = stage->playground[player->position[0]][player->position[1]+1];
            if (next_position == stage->columns - 1) {
                return;
            }

            if (next_position != '#' && next_position == '_') {
                stage->playground[player->position[0]][player->position[1]] = ' ';
                stage->playground[player->position[0]][player->position[1]+1] = 'o';
                player->position[1] = player->position[1]+1;

                player->score--;
                player->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    player->score += 3;
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
