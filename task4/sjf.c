// Shortest Job First Algorithm
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SORT_BY_ARRIVAL 0
#define SORT_BY_PID 1
#define SORT_BY_BURST 2
#define SORT_BY_START 3
typedef struct {
    int iPID;
    int iArrival, iBurst;
    int iStart, iFinish, iWaiting, iResponse, iTaT;
} PCB;
void inputProcess(int n, PCB P[]) {
    int i;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        P[i].iPID = i + 1;
        P[i].iArrival = rand() % 20 + 0;
        P[i].iBurst = rand() % 11 + 2;
        P[i].iStart = P[i].iFinish = P[i].iWaiting = P[i].iResponse = P[i].iTaT = 0;
    }
}
void printProcess(int n, PCB P[]) {
    // printf("\n_________________________________________________________\n");
    printf("| PID | Arrival | Burst | Start | Finish | Turnaround |\n");
    printf("---------------------------------------------------------\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("| P%-4d | %-7d | %-5d | %-5d | %-6d | %-10d |\n", P[i].iPID, P[i].iArrival, P[i].iBurst, P[i].iStart, P[i].iFinish, P[i].iTaT);
    }
    printf("\n");
}
void exportGanttChart(int n, PCB P[]) {
    printf("Gian Do Gantt\n");
    int timeArray[100];
    int nameArray[n];
    timeArray[0] = P[0].iArrival;
    timeArray[1] = P[0].iFinish;
    nameArray[0] = P[0].iPID;
    int timeIndex = 2;
    int pcbIndex = 1;
    int nameIndex = 1;
    while (pcbIndex < n) {
        if (P[pcbIndex].iArrival > timeArray[timeIndex - 1]) {
            timeArray[timeIndex] = P[pcbIndex].iArrival;
            timeArray[timeIndex + 1] = P[pcbIndex].iFinish;
            timeIndex += 2;
            nameArray[nameIndex] = 0;
            nameArray[nameIndex + 1] = P[pcbIndex].iPID;
            nameIndex += 2;
        } else {
            timeArray[timeIndex] = timeArray[timeIndex - 1] + P[pcbIndex].iBurst;
            timeIndex++;
            nameArray[nameIndex] = P[pcbIndex].iPID;
            nameIndex++;
        }
        pcbIndex++;
    }
    // In ten tien trinh
    int nameSize = nameIndex;
    int timeSize = timeIndex;
    timeIndex = 0;
    nameIndex = 0;
    pcbIndex = 0;
    while (timeIndex < timeSize - 1) {
        int count = timeArray[timeIndex + 1] - timeArray[timeIndex];
        if (nameArray[nameIndex] == 0) {
        for (int i = 0; i <= count; i++) {
            printf(" ");
        }
        } else {
            count = (count - 2) / 2;
            for (int i = 0; i <= count; i++) {
            printf(" ");
            }
            printf("P%d", nameArray[nameIndex]);
            if ((timeArray[timeIndex + 1] - timeArray[timeIndex]) % 2 == 0) {
                count -= 1;
            }
            for (int i = 0; i <= count; i++) {
                printf(" ");
            }
        }
        nameIndex++;
        timeIndex++;
    }
    printf("\n");
    // In gian do gantt
    timeIndex = 0;
    while (timeIndex < timeSize - 1) {
        int count = timeArray[timeIndex + 1] - timeArray[timeIndex];
        printf("|");
        for (int i = 0; i < count; i++) {
            printf("-");
        }
        timeIndex++;
    }
    printf("|");
    printf("\n");
    // In chi so
    timeIndex = 0;
    while (timeIndex < timeSize - 1) {
        int count = timeArray[timeIndex + 1] - timeArray[timeIndex];
        if (timeArray[timeIndex] >= 10) {
            count--;
        }
        printf("%d", timeArray[timeIndex]);
        for (int i = 0; i < count; i++) {
            printf(" ");
        }
    timeIndex++;
    }
    printf("%d\n\n", timeArray[timeIndex]);
}
void pushProcess(int *n, PCB P[], PCB Q) {
    P[*n] = Q;
    (*n)++;
}
void removeProcess(int *n, int index, PCB P[]) {
    for (int i = index; i < *n - 1; i++) {
        P[i] = P[i + 1];
    }
    (*n)--;
}
int swapProcess(PCB *P, PCB *Q) {
    if (P == NULL | Q == NULL) {
        return -1;
    }
    PCB temp = *P;
    *P = *Q;
    *Q = temp;
    return 0;
}
int partition(PCB P[], int low, int high, int iCriteria) {
    int vt = low - 1;
    switch (iCriteria) {
        case SORT_BY_ARRIVAL: {
            int pivot = P[high].iArrival;
            for (int i = low; i < high; i++) {
                if (P[i].iArrival < pivot) {
                    vt++;
                    swapProcess(&P[vt], &P[i]);
                }
            }
        } break;
        case SORT_BY_BURST: {
            int pivot = P[high].iBurst;
            int pivot1 = P[high].iArrival;
            for (int i = low; i < high; i++) {
                if (P[i].iBurst < pivot) {
                    vt++;
                    swapProcess(&P[vt], &P[i]);
                } else if (P[i].iBurst == pivot && P[i].iArrival < pivot1)
                {
                    vt++;
                    swapProcess(&P[vt], &P[i]);
                }
            }
        } break;
        case SORT_BY_PID: {
            int pivot = P[high].iPID;
            for (int i = low; i < high; i++) {
                if (P[i].iPID < pivot) {
                    vt++;
                    swapProcess(&P[vt], &P[i]);
                }
            }
        } break;
        case SORT_BY_START: {
            int pivot = P[high].iStart;
            for (int i = low; i < high; i++) {
                if (P[i].iStart < pivot) {
                    vt++;
                    swapProcess(&P[vt], &P[i]);
                }
            }
        } break;
        default:
        break;
    }
    vt++;
    swapProcess(&P[vt], &P[high]);
    return vt;
}
void quickSort(PCB P[], int low, int high, int iCriteria) {
    if (low < high) {
        int index = partition(P, low, high, iCriteria);
        quickSort(P, low, index - 1, iCriteria);
        quickSort(P, index + 1, high, iCriteria);
    }
}
void calculateAWT(int n, PCB P[]) {
    float awt = 0;
    for (int i = 0; i < n; i++) {
        awt += P[i].iWaiting;
    }
    awt /= n;
    printf("\nThoi gian doi trung binh: %f", awt);
}
void calculateATaT(int n, PCB P[]) {
    float atat = 0;
    for (int i = 0; i < n; i++) {
        atat += P[i].iTaT;
    }
    atat /= n;
    printf("\nThoi gian hoan thanh: %f", atat);
    printf("\n");
}
int main() {
    PCB Input[10];
    PCB ReadyQueue[10];
    PCB TerminatedArray[10];
    int iNumberOfProcess;
    printf("Please input number of Process: ");
    scanf("%d", &iNumberOfProcess);
    int iRemain = iNumberOfProcess, iReady = 0, iTerminated = 0;
    inputProcess(iNumberOfProcess, Input);
    quickSort(Input, 0, iNumberOfProcess - 1, SORT_BY_ARRIVAL);
    pushProcess(&iReady, ReadyQueue, Input[0]);
    removeProcess(&iRemain, 0, Input);
    ReadyQueue[0].iStart = ReadyQueue[0].iArrival;
    ReadyQueue[0].iFinish = ReadyQueue[0].iStart + ReadyQueue[0].iBurst;
    ReadyQueue[0].iResponse = ReadyQueue[0].iStart - ReadyQueue[0].iArrival;
    ReadyQueue[0].iWaiting = ReadyQueue[0].iResponse;
    ReadyQueue[0].iTaT = ReadyQueue[0].iFinish - ReadyQueue[0].iArrival;
    while (iTerminated < iNumberOfProcess) {
        while (iRemain > 0) {
            if (Input[0].iArrival <= ReadyQueue[0].iFinish) {
                pushProcess(&iReady, ReadyQueue, Input[0]);
                quickSort(ReadyQueue, 1, iReady - 1, SORT_BY_BURST);
                removeProcess(&iRemain, 0, Input);
                continue;
            } 
            break;
        }
        if (iReady > 0) {
            pushProcess(&iTerminated, TerminatedArray, ReadyQueue[0]);
            removeProcess(&iReady, 0, ReadyQueue);
            ReadyQueue[0].iStart = TerminatedArray[iTerminated - 1].iFinish;
            ReadyQueue[0].iFinish = ReadyQueue[0].iStart + ReadyQueue[0].iBurst;
            ReadyQueue[0].iResponse = ReadyQueue[0].iStart - ReadyQueue[0].iArrival;
            ReadyQueue[0].iWaiting = ReadyQueue[0].iResponse;
            ReadyQueue[0].iTaT = ReadyQueue[0].iFinish - ReadyQueue[0].iArrival;
        }
        if (iReady == 0 && iRemain > 0) {
            pushProcess(&iReady, ReadyQueue, Input[0]);
            ReadyQueue[0].iStart = ReadyQueue[0].iArrival;
            ReadyQueue[0].iFinish = ReadyQueue[0].iStart + ReadyQueue[0].iBurst;
            ReadyQueue[0].iResponse = ReadyQueue[0].iStart - ReadyQueue[0].iArrival;
            ReadyQueue[0].iWaiting = ReadyQueue[0].iResponse;
            ReadyQueue[0].iTaT = ReadyQueue[0].iFinish - ReadyQueue[0].iArrival;
            removeProcess(&iRemain, 0, Input);
        }
    }
    printf("\n===== SJF Scheduling =====\n");
    exportGanttChart(iTerminated, TerminatedArray);
    quickSort(TerminatedArray, 0, iTerminated - 1, SORT_BY_PID);
    printProcess(iTerminated, TerminatedArray);
    calculateAWT(iTerminated, TerminatedArray);
    calculateATaT(iTerminated, TerminatedArray);
    return 0;
}
