# Multiprogramming OS Course Project

This repository contains a small educational operating system simulator implemented in C and a lightweight web-based simulator UI. It demonstrates basic operating systems concepts such as multiprogramming (job loading & execution), simple memory mapping (paging simulation), scheduling, inter-process communication (IPC), and I/O handling.

This README documents the purpose of the project, how to build and run the native simulator, and explains the role of each file in the repository.

## Project structure

Top-level files and folders:

- `os_sim.exe` — (binary) prebuilt executable (Windows). If present, you can run the simulator without compiling.
- `include/` — C header files (interfaces, constants, and type definitions).
- `src/` — C source files (implementation).
- `web-simulator/` — Simple browser-based simulator UI (HTML/CSS/JS) to visualize jobs, memory map and scheduling.


## How to build (native C simulator)

Requirements:

- A C compiler (GCC/MinGW, MSVC) on Windows.

Basic build (using GCC / MinGW from a PowerShell):

```powershell
gcc src/*.c -Iinclude -o os_sim.exe
```

Then run:

```powershell
.\os_sim.exe
```

Notes:

- The program is interactive. `init_jobs()` (in `multiprogramming.c`) prompts for the number of jobs and details (burst time, arrival time).
- The project is intentionally simple and geared for demonstration and learning, not production use.


## Web simulator

Files are under `web-simulator/`. Open `index.html` in a browser (no server required) to use the visual simulator. It provides a form to add jobs, runs a simple FCFS scheduling simulation, shows a memory map, and draws a Gantt-style chart using Plotly.


## Files and responsibilities (detailed)

### include/

- `io.h`
  - Purpose: Declares the I/O handling interface used by the simulator.
  - Key symbol: `void handle_io();`
  - Implementation: `src/io.c` prints I/O simulation messages. Extend this file to simulate block/character devices or asynchronously queued I/O.

- `ipc.h`
  - Purpose: Declares a small demo function for Inter-Process Communication (IPC).
  - Key symbol: `void demo_ipc();`
  - Implementation: `src/ipc.c` shows a placeholder IPC demonstration. Replace with sockets, pipes, shared memory, or message-passing logic for advanced demos.

- `memory.h`
  - Purpose: Types and functions for the memory simulation (simple paging mapping).
  - Key symbols:
    - `#define MAX_FRAMES 32` — maximum number of frames used in the simulation.
    - `typedef struct Frame { int frame_id; int pid; } Frame;` — frame metadata.
    - `void init_memory();` — initialize memory frames and map jobs.
    - `void display_memory();` — print the frame-to-job mapping.
  - Implementation: `src/memory.c` uses `Job` information from `multiprogramming` to map each job to a frame and prints the memory map.

- `multiprogramming.h`
  - Purpose: Job representation and multiprogramming utilities.
  - Key symbols:
    - `#define MAX_JOBS 3` — limit used in interactive input.
    - `typedef struct Job { int pid; int burst_time; int remaining_time; int arrival_time; } Job;` — job control block used by the simulator.
    - `void init_jobs();` — prompts user and initializes the job array.
    - `Job* get_jobs();` — returns pointer to internal job array.
    - `int get_job_count();` — returns number of jobs loaded.
    - `void simulate_job_execution();` — simple CPU busy-loop simulation that decrements remaining time and prints progress.
  - Implementation detail: `src/multiprogramming.c` stores jobs in a static array and provides simple I/O-based input and step-by-step execution logs.

- `scheduler.h`
  - Purpose: Entry point for the scheduler simulation.
  - Key symbol: `void run_scheduler();`
  - Implementation: `src/scheduler.c` currently prints placeholder scheduling messages. You can extend it to implement round-robin, SJF, priority scheduling, or configurable quantum.


### src/

- `main.c`
  - Purpose: Orchestrates the simulation pipeline (multiprogramming → memory → scheduling → IPC → I/O), presenting a linear demo of OS concepts.
  - Behavior: Calls `init_jobs()`, `simulate_job_execution()`, `init_memory()`, `run_scheduler()`, `demo_ipc()`, and `handle_io()` in sequence. The program prints status messages to the console.

- `multiprogramming.c`
  - Purpose: Implementation of job creation and a naive job-execution simulation.
  - Behavior: Interactively reads job count (max `MAX_JOBS`) and per-job burst/arrival times; stores jobs in a static array and simulates execution by decrementing `remaining_time`.
  - Extension ideas: Add support for file-based input, random job generation, multi-queue scheduling or process states (ready, waiting, terminated).

- `memory.c`
  - Purpose: Implements a simple paging-like memory simulation.
  - Behavior: Initializes `Frame` array (`MAX_FRAMES`), maps jobs to frames in order, prints a frame -> PID table and a summary (jobs mapped vs frames). Prints a warning if jobs exceed frames.
  - Extension ideas: Implement frame replacement policies (FIFO, LRU), demand paging, or per-job multi-frame allocation.

- `scheduler.c`
  - Purpose: A placeholder scheduler implementation.
  - Behavior: Prints scheduling messages. Replace with actual algorithms and use the `Job` array from `multiprogramming.c` to compute scheduling metrics (waiting times, turnaround times) and context switches.

- `ipc.c`
  - Purpose: Placeholder/demo implementation for inter-process communication.
  - Behavior: Prints IPC demo messages. Extend to simulate message passing or shared-memory updates between jobs.

- `io.c`
  - Purpose: Placeholder for device I/O handling.
  - Behavior: Prints I/O handling messages. Extend to simulate buffered I/O, device interrupts, or asynchronous callbacks.


## Web simulator files (web-simulator/)

- `index.html` — UI skeleton that contains a form for adding jobs and an area to show results.
- `style.css` — Basic styles for the UI.
- `app.js` — Client-side logic that replicates a subset of the native simulator functionality:
  - Adds job input rows dynamically.
  - Gathers job data and simulates memory assignment (one frame per job).
  - Performs FCFS scheduling calculations and computes start/finish/waiting/turnaround times.
  - Renders a table and a Gantt-style chart using Plotly.


## Extending the project (suggestions)

- Implement real scheduling algorithms in `scheduler.c` and calculate metrics (average waiting/turnaround times).
- Replace interactive `scanf` input with command-line arguments or a configuration file for easier testing.
- Add unit tests for scheduling and memory mapping logic (for example, port the scheduling logic from `app.js` into C and write tests with a small harness).
- Improve `ipc.c` to simulate producer-consumer, pipes, or message queues.


## Notes and assumptions

- The code is intentionally simple and pedagogical. It uses console I/O and static arrays for clarity.
- The repository contains a prebuilt `os_sim.exe` — if you prefer to compile from source, backing up or removing the binary is optional.


---

If you'd like, I can:

- add build scripts (Makefile or PowerShell script) to automate compile/run steps, or
- implement one of the suggested extensions (e.g., round-robin scheduler with configurable quantum and tests), or
- generate a short developer guide with