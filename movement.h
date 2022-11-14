void move (char direction, struct labyrinth_stage *stage) {
    char next_position;
    bool scored = false;

    switch (direction) {
        case 'h':
            // prima di effettuare altri controlli, guardo se la mossa mi fa andare fuori da dove sono entrato
            next_position = stage->playground[stage->position[0]][stage->position[1]-1];
            if (next_position == 0) {
                return;
            }

            if (next_position != '#' && next_position == '_') { // se ha raggiunto l'uscita
                stage->playground[stage->position[0]][stage->position[1]] = ' ';
                stage->playground[stage->position[0]][stage->position[1]-1] = 'o';
                stage->position[1] = stage->position[1]-1;

                stage->score--;

                clear();
                show_labyrinth_stages(true, stage);
                printf("hai vinto\n");
                stage->won = true;
            } else if (next_position != '#') {
                if (next_position == '$') {
                    stage->score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    stage->score /= 2;
                    scored = true;
                }
                stage->playground[stage->position[0]][stage->position[1]] = ' ';
                stage->playground[stage->position[0]][stage->position[1]-1] = 'o';
                stage->position[1] = stage->position[1]-1;

                if (!scored) {
                    stage->score--;
                }

                clear();
                show_labyrinth_stages(true, stage);
            }
            break;
        case 'j':
            next_position = stage->playground[stage->position[0]+1][stage->position[1]];
            if (next_position == stage->rows - 1) {
                return;
            }

            if (next_position != '#' && next_position == '_') {
                stage->playground[stage->position[0]][stage->position[1]] = ' ';
                stage->playground[stage->position[0]+1][stage->position[1]] = 'o';
                stage->position[0] = stage->position[0]+1;

                stage->score--;

                clear();
                show_labyrinth_stages(true, stage);
                printf("hai vinto\n");
                stage->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    stage->score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    stage->score /= 2;
                    scored = true;
                }
                stage->playground[stage->position[0]][stage->position[1]] = ' ';
                stage->playground[stage->position[0]+1][stage->position[1]] = 'o';
                stage->position[0] = stage->position[0]+1;

                if (!scored) {
                    stage->score--;
                }

                clear();
                show_labyrinth_stages(true, stage);
            }
            break;
        case 'k':
            next_position = stage->playground[stage->position[0]-1][stage->position[1]];
            if (next_position == 0) {
                return;
            }

            if (next_position != '#' && next_position == '_') {
                stage->playground[stage->position[0]][stage->position[1]] = ' ';
                stage->playground[stage->position[0]-1][stage->position[1]] = 'o';
                stage->position[0] = stage->position[0]-1;

                stage->score--;

                clear();
                show_labyrinth_stages(true, stage);
                printf("hai vinto\n");
                stage->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    stage->score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    stage->score /= 2;
                    scored = true;
                }
                stage->playground[stage->position[0]][stage->position[1]] = ' ';
                stage->playground[stage->position[0]-1][stage->position[1]] = 'o';
                stage->position[0] = stage->position[0]-1;

                if (!scored) {
                    stage->score--;
                }

                clear();
                show_labyrinth_stages(true, stage);
            }
            break;
        case 'l':
            next_position = stage->playground[stage->position[0]][stage->position[1]+1];
            if (next_position == stage->columns - 1) {
                return;
            }

            if (next_position != '#' && next_position == '_') {
                stage->playground[stage->position[0]][stage->position[1]] = ' ';
                stage->playground[stage->position[0]][stage->position[1]+1] = 'o';
                stage->position[1] = stage->position[1]+1;

                stage->score--;

                clear();
                show_labyrinth_stages(true, stage);
                printf("hai vinto\n");
                stage->won = true;
            } else if (next_position != '#'){
                if (next_position == '$') {
                    stage->score += 3;
                    scored = true;
                }
                if (next_position == '!') {
                    stage->score /= 2;
                    scored = true;
                }
                stage->playground[stage->position[0]][stage->position[1]] = ' ';
                stage->playground[stage->position[0]][stage->position[1]+1] = 'o';
                stage->position[1] = stage->position[1]+1;

                if (!scored) {
                    stage->score--;
                }

                clear();
                show_labyrinth_stages(true, stage);
            }
            break;
    }
}
