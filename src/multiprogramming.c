#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "multiprogramming.h"

static Job jobs[MAX_JOBS];
static int job_count = 0;

void init_jobs() {
    printf("Enter number of jobs (max %d): ", MAX_JOBS);
    scanf("%d", &job_count);
    if (job_count < 1 || job_count > MAX_JOBS) {
        printf("Invalid job count. Using default: %d\n", MAX_JOBS);
        job_count = MAX_JOBS;
    }
    for(int i = 0; i < job_count; i++) {
        printf("Enter details for Job %d:\n", i+1);
        jobs[i].pid = i + 1;
        printf("  Burst time: ");
        scanf("%d", &jobs[i].burst_time);
        printf("  Arrival time: ");
        scanf("%d", &jobs[i].arrival_time);
        jobs[i].remaining_time = jobs[i].burst_time;
    }

    printf("[Multiprogramming] %d jobs loaded into memory pool:\n", job_count);
    for(int i = 0; i < job_count; i++) {
        printf("  Job PID=%d, Burst=%d, Arrival=%d, Remaining=%d\n", 
               jobs[i].pid, jobs[i].burst_time, jobs[i].arrival_time, jobs[i].remaining_time);
    }
}

void simulate_job_execution() {
    printf("[Multiprogramming] Simulating job execution...\n");
    for(int i = 0; i < job_count; i++) {
        printf("  Executing Job PID=%d\n", jobs[i].pid);
        while(jobs[i].remaining_time > 0) {
            jobs[i].remaining_time--;
            printf("    Remaining time: %d\n", jobs[i].remaining_time);
        }
        printf("  Job PID=%d completed!\n", jobs[i].pid);
    }
}

Job* get_jobs() {
    return jobs;
}

int get_job_count() {
    return job_count;
}
