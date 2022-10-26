#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {

    FILE* file = fopen("labyrinth.txt", "r");

    if(!file) {
        printf("\n Unable to open file");
        return -1;
    }

    char line[50];
    int rows = 0, columns = 0; // numero di righe e colonne
    bool selected = false;

    while (fgets(line, sizeof(line), file)) { //leggo tutto il file e stoppo il ciclo dopo aver letto il labirinto
        if ((strcmp(line, "1\n")) == 0) { // se trovo il numero corrispondente al labirinto comincio a leggerlo
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
    return 0;
}
