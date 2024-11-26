// Shortest Remaining Time First or Round Robin Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define SORT_BY_ARRIVAL 0
#define SORT_BY_PID 1
#define SORT_BY_BURST 2
#define SORT_BY_START 3
typedef struct {
    int iPID;
    int iArrival, iBurst;
    int iStart, iFinish, iWaiting, iResponse, iTaT;
}
PCB;
void inputProcess(int n, PCB P[]) {
    int i;
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        P[i].iPID = i + 1;
        P[i].iArrival = rand() % 21;
        P[i].iBurst = rand() % 11 + 2;
        P[i].iStart = P[i].iFinish = P[i].iWaiting = P[i].iResponse = P[i].iTaT = 0;
    }
}
void printProcess(int n, PCB P[]) {
    printf("\n_________________________________________________________\n");
    printf("| PID | Arrival | Burst | Start | Finish | Turnaround | \n");
    printf("---------------------------------------------------------\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("| P%-4d | %-7d | %-5d | %-5d | %-6d | %-10d |\n", P[i].iPID, P[i].iArrival, P[i].iBurst, P[i].iStart, P[i].iFinish, P[i].iTaT);
    }
    printf("\n");
}
void exportGanttChart(int n, PCB P[], int m, int timeArray[]) {
    int nameArray[100];
    // Khoi tao gia tri cho mang luu ten cac tien trinh
    for (int i = 0; i < n; i++) {
      nameArray[i] = P[i].iPID;
    }
    // In ten tien trinh
    int nameSize = n;
    int timeSize = m;
    int timeIndex = 0;
    int nameIndex = 0;
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
    printf("%d", timeArray[timeIndex]);
};
void pushProcess(int * n, PCB P[], PCB Q) {
    P[ * n] = Q;
    ( * n) ++;
}
void removeProcess(int * n, int index, PCB P[]) {
    for (int i = index; i < * n - 1; i++) {
        P[i] = P[i + 1];
    }
    ( * n) --;
}
int swapProcess(PCB * P, PCB * Q) {
    PCB temp;
    temp = * P;
    * P = * Q;
    * Q = temp;
};
int partition(PCB P[], int low, int high, int iCriteria) {
    int vt = low - 1;
    switch (iCriteria) {
        case SORT_BY_ARRIVAL: {
            int pivot = P[high].iArrival;
            for (int i = low; i < high; i++) {
                if (P[i].iArrival < pivot) {
                    vt++;
                    swapProcess( & P[vt], & P[i]);
                }
            }
        }
        break;
        case SORT_BY_BURST: {
            int pivot = P[high].iBurst;
            int pivot1 = P[high].iArrival;
            for (int i = low; i < high; i++) {
                if (P[i].iBurst < pivot) {
                    vt++;
                    swapProcess( & P[vt], & P[i]);
                } else if (P[i].iBurst == pivot && P[i].iArrival < pivot1) {
                    vt++;
                    swapProcess( & P[vt], & P[i]);
                }
            }
        }
        break;
        case SORT_BY_PID: {
            int pivot = P[high].iPID;
            for (int i = low; i < high; i++) {
                if (P[i].iPID < pivot) {
                    vt++;
                    swapProcess( & P[vt], & P[i]);
                }
            }
        }
        break;
        case SORT_BY_START: {
            int pivot = P[high].iStart;
            for (int i = low; i < high; i++) {
                if (P[i].iStart < pivot) {
                    vt++;
                    swapProcess( & P[vt], & P[i]);
                }
            }
        }
        break;
        default:
        break;
    }
    vt++;
    swapProcess( & P[vt], & P[high]);
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
    PCB PreemptiveArray[100];

    int iNumberOfProcess;
    int timeArray[100];
    int quantumnTime;
    
    printf("Please input number of Process: ");
    scanf("%d", & iNumberOfProcess);
    printf("Please input quantumn time: ");
    scanf("%d", & quantumnTime);
    int iRemain = iNumberOfProcess, iReady = 0, iTerminated = 0, timeIndex = -1, iPreemptive = 0;
    inputProcess(iNumberOfProcess, Input);
    quickSort(Input, 0, iNumberOfProcess - 1, SORT_BY_ARRIVAL);
    pushProcess( & iReady, ReadyQueue, Input[0]);
    removeProcess( & iRemain, 0, Input);
    pushProcess( & iPreemptive, PreemptiveArray, ReadyQueue[0]);
    timeIndex++;
    timeArray[timeIndex] = ReadyQueue[0].iArrival;

    // kiem tra neu cac tien trinh van chua thuc thi xong het
    while (iTerminated < iNumberOfProcess) {
        if (ReadyQueue[0].iBurst <= quantumnTime) {
            // truong hop tien trinh dang thuc thi co thoi gian thuc thi
            // con lai be hon quantumnTime
            while (iRemain > 0) {
                // them tien trinh vao ReadyQueue neu thoa dieu kien
                if (Input[0].iArrival <= timeArray[timeIndex] + ReadyQueue[0].iBurst) {
                    pushProcess( & iReady, ReadyQueue, Input[0]);
                    removeProcess( & iRemain, 0, Input);
                    continue;
                } else {
                    break;
                }
            }
            // tien trinh da thuc hien xong va duoc dua vao TerminatedArray[]
            pushProcess( & iTerminated, TerminatedArray, ReadyQueue[0]);
            timeIndex++;
            timeArray[timeIndex] = timeArray[timeIndex - 1] + ReadyQueue[0].iBurst;
            removeProcess( & iReady, 0, ReadyQueue);
            TerminatedArray[iTerminated - 1].iFinish = timeArray[timeIndex];
            if (iReady > 0) {
                // neu trong ReadyQueue[] van con tien trinh thi
                // them tien trinh do vao PreemptiveArray[]
                pushProcess( & iPreemptive, PreemptiveArray, ReadyQueue[0]);
            } else if (iRemain > 0) {
                // neu nhu trong ReadyQueue[] khong con tien trinh nao va
                // van con tien trinh trong
                // input[] thi them tien trinh do vao ReadyQueue[] 
                pushProcess( & iReady, ReadyQueue, Input[0]);
                removeProcess( & iRemain, 0, Input);
                timeIndex++;
                timeArray[timeIndex] = ReadyQueue[0].iArrival;
                PCB tmp;
                tmp.iPID = 0;
                pushProcess( & iPreemptive, PreemptiveArray, tmp);
                pushProcess( & iPreemptive, PreemptiveArray, ReadyQueue[0]);
            }
        } else {
            // truong hop tien trinh dang thuc thi co thoi gian thuc thi
            // con lai lon hon quantumnTime
            while (iRemain > 0) {
                // them tien trinh vao ReadyQueue neu thoa dieu kien
                if (Input[0].iArrival <= timeArray[timeIndex] + quantumnTime) {
                    pushProcess( & iReady, ReadyQueue, Input[0]);
                    removeProcess( & iRemain, 0, Input);
                    continue;
                } else {
                    break;
                }
            }
            // tien trinh da thuc hien het quantumnTime va
            // nhuong quyen thuc thi cho tien trinh khac
            ReadyQueue[0].iBurst -= quantumnTime;
            PCB tmp = ReadyQueue[0];
            removeProcess( & iReady, 0, ReadyQueue);
            pushProcess( & iReady, ReadyQueue, tmp);
            pushProcess( & iPreemptive, PreemptiveArray, ReadyQueue[0]);
            timeIndex++;
            timeArray[timeIndex] = timeArray[timeIndex - 1] + quantumnTime;
        }
    }
    // cap nhat lai cac gia tri cho tien trinh
    for (int i = 0; i < iTerminated; i++) {
        for (int j = 0; j < iPreemptive; j++) {
            if (TerminatedArray[i].iPID == PreemptiveArray[j].iPID) {
                TerminatedArray[i].iBurst = PreemptiveArray[j].iBurst;
                TerminatedArray[i].iStart = timeArray[j];
                TerminatedArray[i].iTaT = TerminatedArray[i].iFinish - TerminatedArray[i].iArrival;
                TerminatedArray[i].iWaiting = TerminatedArray[i].iTaT - TerminatedArray[i].iBurst;
                TerminatedArray[i].iResponse = TerminatedArray[i].iStart - TerminatedArray[i].iArrival;
                break;
            }
        }
    }
    printf("\n===== Round Robin Scheduling =====\n");
    exportGanttChart(iPreemptive, PreemptiveArray, timeIndex + 1, timeArray);
    printf("\n");
    quickSort(TerminatedArray, 0, iTerminated - 1, SORT_BY_PID);
    printProcess(iTerminated, TerminatedArray);
    calculateAWT(iTerminated, TerminatedArray);
    calculateATaT(iTerminated, TerminatedArray);
    return 0;
}
