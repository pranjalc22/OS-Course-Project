#include <stdio.h>
#include "multiprogramming.h"
#include "memory.h"
#include "scheduler.h"
#include "ipc.h"
#include "io.h"

// Declare init_memory if needed
void init_memory();

int main() {
    printf("=== Multiprogramming Operating System: Stage III ===\n");

    // Step 1: Multiprogramming (load jobs)
    init_jobs();

    // Step 2: Virtual Memory
    init_memory();

    // Step 3: Process Scheduling
    run_scheduler();

    // Step 4: IPC demo
    demo_ipc();

    // Step 5: I/O Handling
    handle_io();

    printf("\n=== Execution Completed. Output delivered to user/device. ===\n");
    return 0;
}
