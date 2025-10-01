#include <stdio.h>
#include "memory.h"
#include "multiprogramming.h"

// Make sure MAX_FRAMES is defined in memory.h
#ifndef MAX_FRAMES
    #define MAX_FRAMES 32 // Default value if not defined elsewhere
#endif

// Make sure Frame is defined
#ifndef FRAME_DEFINED
typedef struct {
    int frame_id;
    int pid;
} Frame;
#define FRAME_DEFINED
#endif

// Make sure Job is defined
#ifndef JOB_DEFINED
typedef struct {
    int pid;
    // Add other fields as needed
} Job;
#define JOB_DEFINED
#endif

// Dummy declarations if not provided elsewhere
#ifndef GET_JOBS_DECLARED
Job* get_jobs();
int get_job_count();
#define GET_JOBS_DECLARED
#endif

static Frame frames[MAX_FRAMES];

// Function prototype
void display_memory();

void init_memory() {
    Job* jobs = get_jobs();
    int job_count = get_job_count();

    if (jobs == NULL) {
        printf("[Memory] Error: jobs pointer is NULL.\n");
        return;
    }

    // Initialize all frames as empty
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i].frame_id = i;
        frames[i].pid = 0;
    }

    // Map jobs to frames (simple paging)
    for (int i = 0; i < job_count && i < MAX_FRAMES; i++) {
        frames[i].pid = jobs[i].pid;
    }

    printf("[Memory] Jobs mapped to frames (Paging Simulation):\n");
    display_memory();
}

void display_memory() {
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i].pid != 0)
            printf("  Frame %d -> Job PID=%d\n", frames[i].frame_id, frames[i].pid);
        else
            printf("  Frame %d -> Empty\n", frames[i].frame_id);
    }
}
