/**
 * list data structure containing the tasks in the system
 */

#include "task.h"

struct node
{
    Task *task;
    struct node *next;
};

// insert and delete operations.
void insert(struct node **head, Task *task);
void delete (struct node **head, Task *task);
void traverse(struct node *head);
void sortList(struct node *head);
void swap(struct node *a, struct node *b);
void sortPriority(struct node *head);
int maxPriority(struct node *head);