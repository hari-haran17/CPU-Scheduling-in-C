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
struct node *prioList = NULL;
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

int countTaskOfPriority(struct node *head, int pri) {
    int cnt = 0;
    while(head != NULL){
        if (head->task->priority == pri){
            cnt++;
            head = head->next;
        } else{
            head = head->next;
        }
    }
    return cnt;
}

void schedule() {
    struct node *temp;
    temp = linkedList;

    while (temp != NULL) {
        insert(&scheduleList, temp->task);
        temp = temp->next;
    }
    int watTime = 0;
    temp = scheduleList;
    while (temp != NULL){
        watTime += temp->task->burst;
        //watt = ttTime-temp->task->burst;
        temp= temp->next;
    }

    temp = scheduleList;
    sortPriority(scheduleList);
    int finishTask = 0;
    int max;
    int maxTaskCount;
    int comTime = 0, comEndTime = 0, comEnd2time = 0, totalComTime = 0, total2ComTime = 0;
    int ttat = 0, ttat2 = 0;
    int pCounter = 0, totalRtime = 0;
    double avt, wat, rt;

    //printf("%d", max);

//    while (temp != NULL){
//        if (temp->task->burst > QUANTUM){
//            run(temp->task, QUANTUM);
//            temp->task->burst -= QUANTUM;
//            if (temp->task->priority == temp->next->task->priority){
//                temp= temp->next;
//            }else{
//
//            }
//        }
//    }
    while (finishTask != countTask) {
        temp = scheduleList;
        max = maxPriority(scheduleList);
        maxTaskCount = countTaskOfPriority(scheduleList, max);
        while (maxTaskCount > 0) {
            temp = scheduleList;
            while (temp != NULL) {
                if (max == temp->task->priority && temp->task->burst > 0) {
                    if (temp->task->burst > QUANTUM) {
                        if(maxTaskCount == 1) {
                            run(temp->task, temp->task->burst);
                            if (temp->task->responseCheck == 0){
                                temp->task->responseTime = pCounter;
                                totalRtime += pCounter;
                                temp->task->responseCheck = 1;
                            }
                            pCounter += temp->task->burst;
                            comEndTime += temp->task->burst;
                            totalComTime = comEndTime + total2ComTime;
                            ttat2 += totalComTime;
                            temp->task->burst = 0;
                            temp = temp->next;
                            maxTaskCount = 0;
                            finishTask++;
                        } else {
                            run(temp->task, QUANTUM);
                            if (temp->task->responseCheck == 0){
                                temp->task->responseTime = pCounter;
                                totalRtime += pCounter;
                                temp->task->responseCheck = 1;
                            }
                            pCounter += QUANTUM;
                            comTime += QUANTUM;
                            temp->task->burst -= QUANTUM;
                            temp = temp->next;
                        }
                    } else if (temp->task->burst > 0) {
                        run(temp->task, temp->task->burst);
                        if (temp->task->responseCheck == 0){
                            temp->task->responseTime = pCounter;
                            totalRtime += pCounter;
                            temp->task->responseCheck = 1;
                        }
                        pCounter += temp->task->burst;
                        comEnd2time += temp->task->burst;
                        total2ComTime = comTime + comEnd2time;
                        ttat += total2ComTime + comEndTime;
                        temp->task->burst = 0;
                        temp = temp->next;
                        finishTask++;
                        maxTaskCount--;
                    } else {
                        //run(temp->task, temp->task->burst);
                        temp = temp->next;
                    }
                }else{
                    temp= temp->next;
                }
                //temp = temp->next;
            }
        }
        //free(scheduleList);
    }
    free(scheduleList);

    avt = (double)(ttat2+ttat)/countTask;
    wat = (double)(ttat2+ttat-watTime)/countTask;
    rt = (double)(totalRtime/countTask);
    printf("\nAverage waiting time = %.2f\n", wat);
    printf("Average turnaround time = %.2f\n", avt);
    printf("Average response time = %.2f\n", rt);



//    while (finishTask != countTask)
//    {
//        temp = scheduleList;
//
//        while (temp != NULL)
//        {
//            while (max == temp->task->priority)
//            {
//                if (temp->task->burst > QUANTUM)
//                {
//                    run(temp->task, QUANTUM);
//                    temp->task->burst -= QUANTUM;
////                    if (temp->task->burst != 0){
////                        run(temp->task, QUANTUM);
////                        temp= temp->next;
////                    }
//                    temp = temp->next;
//                }
//                else if (temp->task->burst > 0)
//                {
//                    run(temp->task, temp->task->burst);
//
//                    temp->task->burst = 0;
//                    temp = temp->next;
//                    finishTask++;
//                }
//                else
//                {
//                    temp = temp->next;
//                }
//            }
//            //temp = temp->next;
//        }
//    }
}