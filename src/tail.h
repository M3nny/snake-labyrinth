/**
 * \file tail.h
 * \brief Gestione della coda di snake
*/

/// Linked list che contiene le coordinate di ogni elemento della coda di snake
typedef struct tail {
    int rows; ///< riga dell'elemento della coda
    int columns; ///< colonna dell'elemento della coda
    struct tail *next; ///< puntatore al prossimo elemento della coda
} list;

/// Crea un nuovo elemento nella coda
list *l_create(int rows, int columns) {
    list *l = (list*) malloc(sizeof(list));
    if (!l) exit(EXIT_FAILURE);
    l->rows = rows;
    l->columns = columns;
    l->next = NULL;
    return l;
}

/// Aggiunge un nuovo elemento alla coda
void list_append(list **l_orig, int rows, int columns) {
    if (*l_orig == NULL) {
        *l_orig = l_create(rows, columns);
    } else {
        list_append(&(*l_orig)->next, rows, columns); // indirizzo nodo successivo
    }
}

/// Rimuove il primo elemento dalla lista
void pop(list **l_orig) {
    list *temp = *l_orig;
    if (temp) {
        *l_orig = temp->next;
    }
    free(temp);
}

/// Stampa i contenuti della linked list
void print_list(list *l) {
    if (l == NULL) // fine lista, cioè lista vuota
        return;
    else {
        printf("%d - %d / ", l->rows, l->columns);
        print_list(l->next);
    }
}

/// Ottiene quanti elementi sono presenti nella linked list
int get_tail_length(list *l) {
    int count = 0;
    while (l != NULL) {
        l = l->next;
        count++;
    }
    return count;
}

/// Ritorna la posizione dell'elemento della lista che possiede i valori passati come parametri alla funzione
int get_node_index(list *l, int rows, int columns) {
    int count = 0;
    while (l != NULL) {
        if (l->rows == rows && l->columns == columns) {
            return count;
        }
        l = l->next;
        count++;
    }
    return count;
}

/// Libera la memoria allocata dalla linked list, viene chiamata da free_game prima di finire il programma
void delete_tail(list *l) {
    list *temp; 
    while (l != NULL) {
        temp = l;
        l = l->next;
        free(temp);
    }
}
