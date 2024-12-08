#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 25

// Date structure
typedef struct {
    char month[3];
    char day[3];
    char year[5];
} Date;

// Patient structure
typedef struct {
    Date birth;
    char name[MAX_STRING];
    int ssn;
    char gender;
    int priority; // 1 = critical, 2 = high, 3 = medium, 4 = low
    char task[MAX_STRING];
} Patient;

// Priority Queue structure
typedef struct {
    Patient* heap;
    int size;
    int capacity;
} PriorityQ;


PriorityQ createPQ(int capacity);
int isEmpty(PriorityQ* pq);
void newPatient(PriorityQ* pq, Patient p);
Patient processPatient(PriorityQ* pq);
void updatePatient(PriorityQ* pq, int index, int newPriority);
void swap(Patient* a, Patient* b);
void upHeap(PriorityQ* pq, int index);
void downHeap(PriorityQ* pq, int index);

// Main function
int main(void) {
    int numpatients;
    printf("How many patients are there?\n");
    scanf("%d", &numpatients);

    // Create priority queue
    PriorityQ pq = createPQ(numpatients);

    // Input patients
    for (int i = 0; i < numpatients; i++) {
        Patient scanned;

        printf("\nPatient %d:\n", i + 1);
        printf("Enter name: ");
        fgets(scanned.name, MAX_STRING, stdin);

        printf("Enter SSN (numeric): ");
        scanf("%d", &scanned.ssn);

        printf("Enter gender (M/F): ");
        scanf(" %c", &scanned.gender);

        printf("Enter priority (1-4): ");
        scanf("%d", &scanned.priority);

        printf("Enter task: ");
        fgets(scanned.task, MAX_STRING, stdin);

        printf("Enter birth month (MM): ");
        scanf("%s", scanned.birth.month);

        printf("Enter birth day (DD): ");
        scanf("%s", scanned.birth.day);

        printf("Enter birth year (YYYY): ");
        scanf("%s", scanned.birth.year);

        newPatient(&pq, scanned);
    }

    // Process patients
    printf("\nProcessing patients in order of priority:\n");
    while (!isEmpty(&pq)) {
        Patient p = processPatient(&pq);
        printf("Processing patient: %s with priority %d\n", p.name, p.priority);
    }

    free(pq.heap);
    return 0;
}

// Create a priority queue
PriorityQ createPQ(int capacity) {
    PriorityQ pq;
    pq.size = 0;
    pq.capacity = capacity;
    pq.heap = (Patient*)malloc((capacity + 1) * sizeof(Patient));
    return pq;
}

// Check if the priority queue is empty
int isEmpty(PriorityQ* pq) {
    return pq->size == 0;
}

// Insert a new patient into the priority queue
void newPatient(PriorityQ* pq, Patient p) {
    if (pq->size >= pq->capacity) {
        pq->capacity *= 2; // Double the capacity ( because in this case, we CAN'T REFUSE more patients, It's a Hospital !!!)
        pq->heap = (Patient*)realloc(pq->heap, (pq->capacity + 1) * sizeof(Patient));
        
        if (pq->heap == NULL) { // Check for allocation failure
            printf("Memory allocation failed\n");
            exit(1);
        }
    }
    
    pq->heap[++pq->size] = p;
    upHeap(pq, pq->size);
}


Patient processPatient(PriorityQ* pq) {
    if (isEmpty(pq)) {
        printf("Underflow\n");
        exit(1);
    }
    Patient top = pq->heap[1]; //the element that has the most critical priority is on the top (at index 1) because we're going from higher priority to lower one
    pq->heap[1] = pq->heap[pq->size--];
    downHeap(pq, 1);
    return top;
}

/*
We also would like to be able to change the priority of each patient if his/her condition worsens or perhaps
gets better, so either we would lower or increase the priority. This also should be translated into a function
you should name updatePatient().
*/
void updatePatient(PriorityQ* pq, int index, int newPriority) {
    if (index < 1 || index > pq->size) {
        printf("Invalid index\n");
        return;
    }
    int oldPriority = pq->heap[index].priority;
    pq->heap[index].priority = newPriority;
    if (newPriority < oldPriority) {
        upHeap(pq, index);
    } else {
        downHeap(pq, index);
    }
}

// Swap two patients
void swap(Patient* a, Patient* b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}


void upHeap(PriorityQ* pq, int index) {
    while (index > 1) {
        int parent = index / 2;
        if (pq->heap[index].priority >= pq->heap[parent].priority) break;
        swap(&pq->heap[index], &pq->heap[parent]);
        index = parent;
    }
}


void downHeap(PriorityQ* pq, int index) {
    while (2 * index <= pq->size) {
        int left = 2 * index;
        int right = left + 1;
        int smallest = left;

        if (right <= pq->size && pq->heap[right].priority < pq->heap[left].priority) {
            smallest = right;
        }

        if (pq->heap[index].priority <= pq->heap[smallest].priority) break;
        swap(&pq->heap[index], &pq->heap[smallest]);
        index = smallest;
    }
}
