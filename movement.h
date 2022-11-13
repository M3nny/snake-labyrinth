void move (char direction, struct stage *current_stage) {
    char next_position;
    bool scored = false;
    switch (direction) {
        case 'h':
            // prima di effettuare altri controlli, guardo se la mossa mi fa andare fuori da dove sono entrato
            if (current_stage->starting_wall == 'w') {
                if (current_stage->position[1]-1 == current_stage->origin[1]-1) {
                    break;
                }
            }
            next_position = current_stage->playground[current_stage->position[0]][current_stage->position[1]-1];

            if (next_position != '#' && next_position == '_') { // se ha raggiunto l'uscita
                current_stage->playground[current_stage->position[0]][current_stage->position[1]] = ' ';
                current_stage->playground[current_stage->position[0]][current_stage->position[1]-1] = 'o';
                current_stage->position[1] = current_stage->position[1]-1;

                current_stage->score--;

                clear();
                show_stages(true, current_stage);
                printf("hai vinto\n");
                current_stage->won = true;
            } else if (next_position != '#') {
                if (next_position == '$') {
                    current_stage->score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    current_stage->score /= 2;
                    scored = true;
                }
                current_stage->playground[current_stage->position[0]][current_stage->position[1]] = ' ';
                current_stage->playground[current_stage->position[0]][current_stage->position[1]-1] = 'o';
                current_stage->position[1] = current_stage->position[1]-1;

                if (!scored) {
                    current_stage->score--;
                }

                clear();
                show_stages(true, current_stage);
            }
            break;
        case 'j':
            if (current_stage->starting_wall == 's') {
                if (current_stage->position[0]+1 == current_stage->origin[0]+1) {
                    break;
                }
            }
            next_position = current_stage->playground[current_stage->position[0]+1][current_stage->position[1]];

            if (next_position != '#' && next_position == '_') {
                current_stage->playground[current_stage->position[0]][current_stage->position[1]] = ' ';
                current_stage->playground[current_stage->position[0]+1][current_stage->position[1]] = 'o';
                current_stage->position[0] = current_stage->position[0]+1;

                current_stage->score--;

                clear();
                show_stages(true, current_stage);
                printf("hai vinto\n");
                current_stage->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    current_stage->score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    current_stage->score /= 2;
                    scored = true;
                }
                current_stage->playground[current_stage->position[0]][current_stage->position[1]] = ' ';
                current_stage->playground[current_stage->position[0]+1][current_stage->position[1]] = 'o';
                current_stage->position[0] = current_stage->position[0]+1;

                if (!scored) {
                    current_stage->score--;
                }

                clear();
                show_stages(true, current_stage);
            }
            break;
        case 'k':
            if (current_stage->starting_wall == 'n') {
                if (current_stage->position[0]-1 == current_stage->origin[0]-1) {
                    break;
                }
            }
            next_position = current_stage->playground[current_stage->position[0]-1][current_stage->position[1]];
            if (next_position != '#' && next_position == '_') {
                current_stage->playground[current_stage->position[0]][current_stage->position[1]] = ' ';
                current_stage->playground[current_stage->position[0]-1][current_stage->position[1]] = 'o';
                current_stage->position[0] = current_stage->position[0]-1;

                current_stage->score--;

                clear();
                show_stages(true, current_stage);
                printf("hai vinto\n");
                current_stage->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    current_stage->score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    current_stage->score /= 2;
                    scored = true;
                }
                current_stage->playground[current_stage->position[0]][current_stage->position[1]] = ' ';
                current_stage->playground[current_stage->position[0]-1][current_stage->position[1]] = 'o';
                current_stage->position[0] = current_stage->position[0]-1;

                if (!scored) {
                    current_stage->score--;
                }

                clear();
                show_stages(true, current_stage);
            }
            break;
        case 'l':
            if (current_stage->starting_wall == 'e') {
                if (current_stage->position[1]+1 == current_stage->origin[1]+1) {
                    break;
                }
            }
            next_position = current_stage->playground[current_stage->position[0]][current_stage->position[1]+1];
            if (next_position != '#' && next_position == '_') {
                current_stage->playground[current_stage->position[0]][current_stage->position[1]] = ' ';
                current_stage->playground[current_stage->position[0]][current_stage->position[1]+1] = 'o';
                current_stage->position[1] = current_stage->position[1]+1;

                current_stage->score--;

                clear();
                show_stages(true, current_stage);
                printf("hai vinto\n");
                current_stage->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    current_stage->score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    current_stage->score /= 2;
                    scored = true;
                }
                current_stage->playground[current_stage->position[0]][current_stage->position[1]] = ' ';
                current_stage->playground[current_stage->position[0]][current_stage->position[1]+1] = 'o';
                current_stage->position[1] = current_stage->position[1]+1;

                if (!scored) {
                    current_stage->score--;
                }

                clear();
                show_stages(true, current_stage);
            }
            break;
    }
}
