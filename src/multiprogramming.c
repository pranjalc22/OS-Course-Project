#include <stdio.h>
#include <stdlib.h>
#include "multiprogramming.h"

#ifndef JOB_DEFINED
typedef struct {
    int pid;
    // Add other fields as needed
} Job;
#define JOB_DEFINED
#endif

// Dummy job array for testing
static Job dummy_jobs[] = {
    {1}, {2}, {3}
};

static Job jobs[MAX_JOBS];
static int job_count = 0;

void init_jobs() {
    job_count = MAX_JOBS;
    for(int i = 0; i < job_count; i++) {
        jobs[i].pid = i + 1;
        jobs[i].burst_time = rand() % 10 + 1;
        jobs[i].remaining_time = jobs[i].burst_time;
        jobs[i].arrival_time = i; // sequential arrival
    }

    printf("[Multiprogramming] %d jobs loaded into memory pool:\n", job_count);
    for(int i = 0; i < job_count; i++) {
        printf("  Job PID=%d, Burst=%d, Arrival=%d\n", 
               jobs[i].pid, jobs[i].burst_time, jobs[i].arrival_time);
    }
}

Job* get_jobs() {
    return dummy_jobs;
}

int get_job_count() {
    return sizeof(dummy_jobs) / sizeof(dummy_jobs[0]);
}
