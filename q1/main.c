#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = new_value;
    new_node->next = NULL;

    assert(new_node);
    while (*indirect)
        indirect = &(*indirect)->next;
    *indirect = new_node;
}

void freeList(node_t* head)
{
    node_t* tmp;
    while (head != NULL){
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

void calc_time_complexity(){
    FILE *fptr;
    fptr = fopen("time.txt","w");
    for(int i=1;i<15000;i+=50){
        printf("%d\n", i);
        node_t *head = NULL;
        for(int j=0;j<i;j++){
            add_entry(&head, j);
        }
        clock_t t; 
        t = clock(); 
        fy_shuffle(&head);
        t = clock() - t; 
        fprintf(fptr,"%d %f\n", i, time_taken);
        freeList(head);
    }
    fclose(fptr);
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

void swap_pair(node_t **head)
{
    for (node_t **node = head; *node && (*node)->next; node = &((*node)->next)->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}

node_t* rev_recursive(node_t *curr, node_t **rev_h){
    if(!(curr)->next){
        *rev_h = curr;
        return curr;
    }
    node_t* prev = rev_recursive(curr->next, rev_h);
    prev->next = curr;
    curr->next = NULL;
    return curr;
}

void reverse(node_t **head)
{
    node_t* rev_h;
    rev_recursive(*head, &rev_h);
    *head = rev_h;
}

void fy_shuffle(node_t** head){
    node_t* tail = NULL, *rand_ptr = NULL;
    node_t** tmp;
    time_t t;
    int len, tmp_value, rand_idx;

    while(tail != *head){
        tmp = head;
        len = 1;

        // find the tail of the list
        while((*tmp)->next != tail){
            len++;
            tmp = &((*tmp)->next); 
        }
        tail = *tmp;

        // find the random index pointer
        srand((unsigned) time(&t));
        rand_idx = (rand() % len);
        rand_ptr = *head;
        for(int i=0;i<rand_idx;i++){
            rand_ptr = rand_ptr->next;
        }

        // swap the value of two nodes
        tmp_value = rand_ptr->value;
        rand_ptr->value = tail->value;
        tail->value = tmp_value;
    }
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;

    print_list(head);

    add_entry(&head, 72);
    add_entry(&head, 101);
    add_entry(&head, 108);
    add_entry(&head, 109);
    add_entry(&head, 110);
    add_entry(&head, 111);

    print_list(head);

    node_t *entry = find_entry(head, 101);
    remove_entry(&head, entry);

    entry = find_entry(head, 111);
    remove_entry(&head, entry);

    print_list(head);

    /* swap pair.
     * See https://leetcode.com/problems/swap-nodes-in-pairs/
     */
    swap_pair(&head);
    print_list(head);

    printf("\nReverse list\n");
    reverse(&head);
    print_list(head);

    fy_shuffle(&head);
    printf("\nFisher–Yates shuffle algorithm\n");
    print_list(head);
    return 0;
}