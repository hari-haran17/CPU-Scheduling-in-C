/**
 * Various list operations
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "list.h"
#include "task.h"

// add a new task to the list of tasks
void insert(struct node **head, Task *newTask)
{
    // add the new task to the list
    struct node *newNode = malloc(sizeof(struct node));

    newNode->task = newTask;
    newNode->next = *head;
    *head = newNode;
}

// delete the selected task from the list
void delete (struct node **head, Task *task)
{
    struct node *temp;
    struct node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name, temp->task->name) == 0)
    {
        *head = (*head)->next;
    }
    else
    {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name, temp->task->name) != 0)
        {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

// traverse the list
void traverse(struct node *head)
{
    struct node *temp;
    temp = head;

    while (temp != NULL)
    {
        printf("[%s] [%d] [%d]\n", temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}

void sortList(struct node *head)
{
    int count;
    struct node *start;
    struct node *end = NULL;

    if (head == NULL)
    {
        return;
    }
    do
    {
        count = 0;
        start = head;

        while (start->next != end)
        {
            if (start->task->burst > start->next->task->burst)
            {
                swap(start, start->next);
                count = 1;
            }
            start = start->next;
        }
        end = start;
    } while (count);
}

void sortPriority(struct node *head)
{
    int count;
    struct node *start;
    struct node *end = NULL;

    if (head == NULL)
    {
        return;
    }
    do
    {
        count = 0;
        start = head;

        while (start->next != end)
        {
            if (start->task->priority < start->next->task->priority)
            {
                swap(start, start->next);
                count = 1;
            }
            start = start->next;
        }
        end = start;
    } while (count);
}

void swap(struct node *first, struct node *second)
{
    Task *temp = first->task;
    first->task = second->task;
    second->task = temp;
}

int maxPriority(struct node *head){
    int max = INT_MIN;
    struct node *temp= NULL;
    temp = head;
    while(temp != NULL){
        if (max < temp->task->priority && temp->task->burst > 0){
            max = temp->task->priority;
            temp = temp->next;
        }else{
            temp = temp->next;
        }

    }
    return max;
}


