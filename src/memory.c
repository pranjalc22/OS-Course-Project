#include <stdio.h>
#include "memory.h"
#include "multiprogramming.h"

#ifndef MAX_FRAMES
#define MAX_FRAMES 32
#endif

static Frame frames[MAX_FRAMES];

void init_memory() {
    Job* jobs = get_jobs();
    int job_count = get_job_count();

    if (jobs == NULL) {
        printf("[Memory] Error: jobs pointer is NULL.\n");
        return;
    }

    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i].frame_id = i;
        frames[i].pid = 0;
    }

    int jobs_mapped = 0;
    for (int i = 0; i < job_count && i < MAX_FRAMES; i++) {
        frames[i].pid = jobs[i].pid;
        jobs_mapped++;
    }

    printf("[Memory] Jobs mapped to frames (Paging Simulation):\n");
    display_memory();
    printf("\n[Memory] Summary: %d jobs mapped to %d frames.\n", jobs_mapped, MAX_FRAMES);
    if (job_count > MAX_FRAMES) {
        printf("[Memory] Warning: %d jobs could not be mapped due to insufficient frames.\n", job_count - MAX_FRAMES);
    }
}

void display_memory() {
    printf("\nFrame | Job PID\n----------------\n");
    for (int i = 0; i < MAX_FRAMES; i++) {
        if (frames[i].pid != 0)
            printf("%5d | %7d\n", frames[i].frame_id, frames[i].pid);
        else
            printf("%5d |   Empty\n", frames[i].frame_id);
    }
}
