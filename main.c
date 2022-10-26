#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void get_labyrinth_size (const char *stage) {
    FILE* file = fopen("labyrinth.txt", "r");

    if(!file) {
        printf("\n Unable to open file");
        exit(EXIT_FAILURE);
    }

    char line[50];
    int rows = 0, columns = 0; // numero di righe e colonne
    bool selected = false;

    while (fgets(line, sizeof(line), file)) { //leggo tutto il file e stoppo il ciclo dopo aver letto il labirinto
        if ((strcmp(line, stage)) == 0) { // se trovo il numero corrispondente al labirinto comincio a leggerlo
            selected = true;
            while (fgets(line, sizeof(line), file)) { // leggo il labirinto finchè non trovo end
                if ((strcmp(line, "end\n")) == 0) {
                    break;
                }
                columns = strlen(line) - 1;
                rows++;
            }
        }
        if (selected) {
            break;
        }
    }
    fclose(file);
    printf("righe: %d\ncolonne: %d\n", rows, columns);

}
int main() {
    char stage[2] = "x\n";
    scanf("%c", &stage[0]);
    get_labyrinth_size(stage);

    return 0;
}
