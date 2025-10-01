#ifndef MULTIPROGRAMMING_H
#define MULTIPROGRAMMING_H

#define MAX_JOBS 3

typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int arrival_time;
} Job;

void init_jobs();
Job* get_jobs();
int get_job_count();
void simulate_job_execution();

#endif // MULTIPROGRAMMING_H
