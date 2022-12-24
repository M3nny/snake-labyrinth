/**
 * \file tail.h
 * \brief Gestione della coda di snake
*/

/// Linked list che contiene le coordinate di ogni elemento della coda di snake
typedef struct tail {
    int rows;
    int columns;
    struct tail *next;
} vector;

/// Crea un nuovo elemento nella coda
vector *l_create(int rows, int columns) {
    vector *l = (vector*) malloc(sizeof(vector));
    if (!l) exit(EXIT_FAILURE);
    l->rows = rows;
    l->columns = columns;
    l->next = NULL;
    return l;
}

/// Aggiunge un nuovo elemento alla coda
void vector_append(vector **l_orig, int rows, int columns) {
    if (*l_orig == NULL) {
        *l_orig = l_create(rows, columns);
    } else {
        vector_append(&(*l_orig)->next, rows, columns); // indirizzo nodo successivo
    }
}

/// Rimuove l'ultimo elemento dalla coda
void pop(vector **l_orig) {
    vector *temp = *l_orig;
    if (temp) {
        *l_orig = temp->next;
    }
}

/// Stampa i contenuti della linked list
void print_vector(vector *l) {
    if (l == NULL) // fine lista, cioè lista vuota
        return;
    else {
        printf("%d - %d / ", l->rows, l->columns);
        print_vector(l->next);
    }
}

/// Ottiene quanti elementi sono presenti nella linked list
int get_tail_length(vector *l) {
    int count = 0;
    vector *current = l;
    while (current != NULL) {
        current = current->next;
        count++;
    }
    return count;
}

/// Ritorna la posizione dell'elemento della lista che possiede i valori passati come parametri alla funzione
int get_node_index(vector *l, int rows, int columns) {
    int count = 0;
    vector *current = l;
    while (current != NULL) {
        if (current->rows == rows && current->columns == columns) {
            return count;
        }
        current = current->next;
        count++;
    }
    return count;
}

/// Libera la memoria allocata dalla linked list, viene chiamata da free_game prima di finire il programma
void delete_tail(vector *l) {
    while (l != NULL) {
        vector *temp = l; 
        l = l->next;
        free(temp);
    }
}