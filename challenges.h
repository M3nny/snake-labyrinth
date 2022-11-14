void challenge1() {
    struct labyrinth_stage stage_AI;
    struct labyrinth_player bot;
    scanf("%d", &stage_AI.columns);
    scanf("%d", &stage_AI.rows);
    char input[stage_AI.rows];
    int gate[2];
    bool aligned = false;
    int moves_counter = 0;
    char last_move = '\0';
    bot.moves_storage = malloc(sizeof(char) * 1);


    stage_AI.playground = malloc( sizeof *stage_AI.playground * stage_AI.rows);
    if (stage_AI.playground) { // controllo se il malloc è riuscito
        for ( size_t i = 0; i < stage_AI.rows; i++ ) {
            stage_AI.playground[i] = malloc( sizeof *stage_AI.playground[i] * stage_AI.columns);
        }
    } else {
        printf("Caricamento del livello non riuscito\n");
        exit(EXIT_FAILURE);
    }

    bot.won = false;
    bot.score = 0;
    bot.left = 'O';
    bot.down = 'S';
    bot.up = 'N';
    bot.right = 'E';

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

    if (bot.position[0] == 0) {
        move(bot.down, &stage_AI, &bot);
        last_move = bot.down;
    } else if (bot.position[0] == stage_AI.rows - 1) {
        move(bot.up, &stage_AI, &bot);
        last_move = bot.up;
    } else if (bot.position[1] == 0) {
        move(bot.right, &stage_AI, &bot);
        last_move = bot.right;
    } else if (bot.position[1] == stage_AI.columns - 1) {
        move(bot.left, &stage_AI, &bot);
        last_move = bot.left;
    }

    bot.moves_storage[moves_counter] = last_move;
    moves_counter++;
    bot.moves_storage = realloc(bot.moves_storage, (moves_counter + 1) * sizeof(char));

    while (!aligned) {
        if (bot.position[0] == gate[0] || bot.position[1] == gate[1]) {
            aligned = true;
            break;
        }
        if (gate[0] == 0 || gate[0] == stage_AI.rows - 1) {
            // allineo orizzontalmente
            if(bot.position[1] < gate[1]) {
                move(bot.right, &stage_AI, &bot);
                last_move = bot.right;
            } else if (bot.position[1] > gate[1]) {
                move(bot.left, &stage_AI, &bot);
                last_move = bot.left;
            }
        } else {
            // allineo verticalmente
            if (bot.position[0] < gate[0]) {
                move(bot.down, &stage_AI, &bot);
                last_move = bot.down;
            } else if (bot.position[0] > gate[0]) {
                move(bot.up, &stage_AI, &bot);
                last_move = bot.up;
            }
        }
        bot.moves_storage[moves_counter] = last_move;
        moves_counter++;
        bot.moves_storage = realloc(bot.moves_storage, (moves_counter + 1) * sizeof(char));
    };

    do {
        if (bot.position[0] == gate[0]) {
            if (bot.position[1] < gate[1]) {
                move(bot.right, &stage_AI, &bot);
                last_move = bot.right;
            } else {
                move(bot.left, &stage_AI, &bot);
                last_move = bot.left;
            }
        } else {
            if (bot.position[0] < gate[0]) {
                move(bot.down, &stage_AI, &bot);
                last_move = bot.down;
            } else {
                move(bot.up, &stage_AI, &bot);
                last_move = bot.up;
            }
        }
        bot.moves_storage[moves_counter] = last_move;
        moves_counter++;
        bot.moves_storage = realloc(bot.moves_storage, (moves_counter + 1) * sizeof(char));
    } while (!bot.won);

    for (int i = 0; i < moves_counter; i++) {
        printf("%c",bot.moves_storage[i]);
    }
}
