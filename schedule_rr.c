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
//int QUANTUM = 10;

// add a task to the list
void add(char *name, int priority, int burst)
{
    Task *nTask;
    nTask = malloc(sizeof(Task));
    nTask->name = malloc(sizeof(char));
    nTask->name = name;
    nTask->priority = priority;
    nTask->burst = burst;
    nTask->responseCheck = 0;

    insert(&linkedList, nTask);
    countTask++;
}

void schedule()
{
    struct node *temp;
    temp = linkedList;
    int qTime = 0, fTime = 0, tTime = 0, ttTime = 0, watt = 0, watTime = 0;
    int  totalRtime = 0;
    int pCounter = 0;
    double avt, wat, rt;

    while (temp != NULL)
    {
        insert(&scheduleList, temp->task);
        temp = temp->next;
    }

    temp = scheduleList;
    while (temp != NULL){
        watTime += temp->task->burst;
        //watt = ttTime-temp->task->burst;
        temp= temp->next;
    }



    temp = scheduleList;
    int finishTask = 0;
    while (finishTask != countTask)
    {
        temp = scheduleList;

        while (temp != NULL)
        {
            if (temp->task->burst > QUANTUM)
            {
                run(temp->task, QUANTUM);
                if (temp->task->responseCheck == 0){
                    temp->task->responseTime = pCounter;
                    totalRtime += pCounter;
                    temp->task->responseCheck = 1;
                }
                pCounter += QUANTUM;
                qTime += QUANTUM;
                temp->task->burst -= QUANTUM;
                temp = temp->next;
            }
            else if (temp->task->burst > 0)
            {
                run(temp->task, temp->task->burst);
                if (temp->task->responseCheck == 0){
                    temp->task->responseTime = pCounter;
                    totalRtime += pCounter;
                    temp->task->responseCheck = 1;
                }
                pCounter += temp->task->burst;
                fTime += temp->task->burst;
                tTime = qTime + fTime;
                ttTime += tTime;
                temp->task->burst = 0;
                temp = temp->next;
                finishTask++;
            }
            else
            {
                temp = temp->next;
            }
        }
    }
    temp = scheduleList;

    watt = ttTime - watTime;
    avt = ((double)ttTime / countTask);
    wat = (double)watt / countTask;
    rt = (double)totalRtime/countTask;
    //wat = ((double)sum2 + (double)sum4) / countTask;

    printf("\nAverage waiting time = %.2f\n", wat);
    printf("Average turnaround time = %.2f\n", avt);
    printf("Average response time = %.2f\n", rt);
}