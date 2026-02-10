# Task Scheduler Project

## Overview
This project implements a **Task Scheduler** system in C. It provides a mechanism to manage and execute scheduled tasks at specified intervals, similar to a cron job or timer system.

## Project Structure

```
Scheduler_project/
├── dynamic_vector/       - Dynamic array implementation
├── heap/                - Min-heap data structure
├── include/            - Header files for all modules
├── pq_heap/            - Priority queue implementation using heap
├── scheduler_main/     - Main scheduler implementation and tests
├── task/               - Task/tasker module
└── uid/                - Unique ID generator for tasks
```

## Core Components

### 1. **Scheduler** (`scheduler.h`)
The main module that orchestrates task execution. It manages:
- Creating and destroying schedulers
- Adding tasks with specified intervals
- Running scheduled tasks
- Removing and clearing tasks
- Checking scheduler status (empty, size)

### 2. **Task/Tasker** (`tasker.h`)
Represents individual tasks that can be scheduled. A task consists of:
- A callback function to execute
- Parameters to pass to the function
- An execution interval (in seconds)

### 3. **Priority Queue with Heap** (`pq_heap.h`)
Uses a min-heap to efficiently manage task execution order based on next execution time.

### 4. **Dynamic Vector** (`dynamic_vector.h`)
A dynamically resizable array used for storing data efficiently.

### 5. **UID System** (`uid.h`)
Generates unique IDs for each scheduled task, allowing individual task management.

## Key Functions

| Function | Description |
|----------|-------------|
| `SchedulerCreate()` | Create a new scheduler |
| `SchedulerAdd()` | Add a task to run every N seconds |
| `SchedulerRun()` | Start executing scheduled tasks |
| `SchedulerStop()` | Stop the scheduler |
| `SchedulerRemove()` | Remove a specific task by UID |
| `SchedulerClear()` | Remove all tasks |
| `SchedulerDestroy()` | Free all scheduler resources |
| `SchedulerIsEmpty()` | Check if scheduler has tasks |
| `SchedulerSize()` | Get number of scheduled tasks |

## Usage Example

```c
#include "scheduler.h"

int my_task(void *param) {
    printf("Task executed!\n");
    return 0;  // return 0 for success, 1 to remove task
}

int main() {
    scheduler_ty *scheduler = SchedulerCreate();
    
    // Add a task to run every 5 seconds
    uid_ty task_id = SchedulerAdd(scheduler, 5, my_task, NULL);
    
    // Run the scheduler
    SchedulerRun(scheduler);
    
    // Cleanup
    SchedulerDestroy(scheduler);
    
    return 0;
}
```

## Building the Project

Each module has its own Makefile. To compile:

```bash
cd scheduler_main
make
```

## Testing

Each module includes test files:
- `scheduler_test.c` - Tests for the main scheduler
- `tasker_test.c` - Tests for tasks
- `pq_heap_test.c` - Tests for priority queue
- `heap_test.c` - Tests for heap data structure
- `dynamic_vector_test.c` - Tests for dynamic vector
- `uid_test.c` - Tests for UID generation

## Data Structures Used

1. **Min-Heap** - Efficiently manages task execution order
2. **Dynamic Vector** - Resizable storage for heap elements
3. **Priority Queue** - Wrapper around heap for task prioritization
4. **UID** - Unique identifier system for task management

## Purpose

This is an educational project demonstrating:
- Memory management in C
- Data structure implementation (heap, vector)
- Task scheduling algorithms
- Modular C programming practices
