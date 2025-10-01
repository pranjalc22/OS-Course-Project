#ifndef MEMORY_H
#define MEMORY_H

#define MAX_FRAMES 32

typedef struct {
    int frame_id;
    int pid;
} Frame;

void init_memory();
void display_memory();

#endif // MEMORY_H
