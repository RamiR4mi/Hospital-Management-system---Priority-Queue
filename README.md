# Hospital-Management-system---Priority-Queue



## Hospital Priority Queue System
Overview

This program implements a hospital management system using a priority queue to manage patient records based on their medical urgency. The queue is structured as a min-heap, where patients with smaller priority values (higher urgency) are given precedence.

Key functionalities include:

    •Adding new patients to the queue (newPatient).
    •Processing the most urgent patient (processPatient).
    •Updating a patient's priority (updatePatient).

The system dynamically manages memory for the priority queue and maintains its heap properties using helper functions (upHeap and downHeap).
Features and Functions
1. Priority Queue Structure

The priority queue is implemented as a dynamic array:

    PriorityQ: A structure containing:
        heap: A dynamically allocated array of Patient structures.
        size: The current number of patients in the queue.
        capacity: The maximum number of patients the queue can hold.

2. Patient Structure

The program uses a Patient structure to store individual patient details:

    name: The patient's name.
    ssn: Social Security Number.
    gender: Gender of the patient (M/F).
    priority: An integer representing the urgency of the condition (1 = critical, 2 = high, etc.).
    task: The assigned medical task (e.g., surgery, X-ray).
    birth: A nested structure (Date) containing the patient's birth date (month, day, year).

Functions
Priority Queue Management
PriorityQ createPQ(int capacity)

Initializes a priority queue with the specified capacity. Allocates memory for the heap dynamically.
int isEmpty(PriorityQ* pq)

Returns 1 if the queue is empty, otherwise 0.
Adding and Processing Patients
void newPatient(PriorityQ* pq, Patient p)

Inserts a new patient into the queue:

    Adds the patient to the end of the heap.
    Calls upHeap to restore the min-heap structure.

Patient processPatient(PriorityQ* pq)

Removes and returns the patient with the highest priority:

    Replaces the root element (most urgent patient) with the last element.
    Reduces the queue size.
    Calls downHeap to restore the heap property.

Updating Patient Priority
void updatePatient(PriorityQ* pq, int index, int newPriority)

Updates the priority of a patient at a given index:

    Updates the priority value.
    Calls upHeap if the priority improves (decreases) or downHeap if it worsens (increases).

Heap Management
void upHeap(PriorityQ* pq, int index)

Restores the heap property by moving a node up the tree if its priority is less than its parent's priority.
void downHeap(PriorityQ* pq, int index)

Restores the heap property by moving a node down the tree if it has a higher priority than its children.
void swap(Patient* a, Patient* b)

Swaps the contents of two Patient nodes.
