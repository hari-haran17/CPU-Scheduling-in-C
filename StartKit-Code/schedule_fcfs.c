#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "task.h"
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

struct node *linkedList = NULL;
struct node *scheduleList = NULL;
int countTask = 0;

// add a task to the list
void add(char *name, int priority, int burst)
{
    Task *nTask;
    nTask = malloc(sizeof(Task));
    nTask->name = malloc(sizeof(char));
    nTask->name = name;
    nTask->priority = priority;
    nTask->burst = burst;

    insert(&linkedList, nTask);
    countTask++;
}

void schedule()
{
    struct node *temp;
    temp = linkedList;
    int totalBurst = 0;
    int sum, watt, sum2 = 0;
    double avt, wat;

    while (temp != NULL)
    {
        insert(&scheduleList, temp->task);
        temp = temp->next;
    }

    temp = scheduleList;

    while (temp != NULL)
    {
        run(temp->task, temp->task->burst);
        totalBurst = totalBurst + temp->task->burst;
        watt = totalBurst - temp->task->burst;
        sum = sum + totalBurst;
        sum2 = sum2 + watt;
        temp = temp->next;
    }
    avt = (double)sum / countTask;
    wat = (double)sum2 / countTask;
    printf("\nAverage waiting time = %.2f\n", wat);
    printf("Average turnaround time = %.2f\n", avt);
    printf("Average response time = %.2f\n", wat);
}
