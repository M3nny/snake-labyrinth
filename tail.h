typedef struct list {
  int rows;
  int columns;
  struct list *next;
} vector;

vector *l_create(int rows, int columns) {
  vector *l = (vector*) malloc (sizeof(vector));
  if (!l) exit(EXIT_FAILURE);
  l->rows = rows;
  l->columns = columns;
  l->next = NULL;
  return l;
}

void vector_append(vector **l_orig, int rows, int columns) {
  if (*l_orig==NULL) {
    *l_orig = l_create(rows, columns);
  } else {
    vector_append(&((*l_orig)->next), rows, columns); // indirizzo nodo successivo
  }
}

void pop(vector **l_orig) {
    vector *temp = *l_orig;
    if (temp) {
        *l_orig= temp->next;
    }
}

void print_vector(vector *l) {
  if (l==NULL) // fine lista, cioè lista vuota
    return;
  else {
    printf("%d - %d / ", l->rows, l->columns);
    print_vector(l->next);
  }
}

int get_tail_length(vector *l_orig) {
    int count = 0;
    vector *current = l_orig;
    while (current != NULL) {
        current = current->next;
        count++;
    }
    return count;
}

int get_node_index(vector *l_orig, int rows, int columns) {
    int count = 0;
    vector *current = l_orig;
    while (current != NULL) {
        if (current->rows == rows && current->columns == columns) {
            return count;
        }
        current = current->next;
        count++;
    }
    return count;
}
