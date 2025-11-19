# philosophers
**philosophers** is a concurrency project from the 42 curriculum that simulates the classic Dining Philosophers problem. The program creates multiple philosopher threads that alternate between thinking, eating, and sleeping, while ensuring proper synchronization to avoid deadlocks and race conditions.  

## Features
- Multi-threaded implementation using `pthread`  
- Proper synchronization with mutexes  
- Accurate timing for actions (think, eat, sleep)  
- Deadlock prevention and resource management  
- Supports any number of philosophers with flexible timing  
- Clean memory management and graceful termination  

## Program Rules
- Each philosopher must eat and think in cycles  
- Forks are shared resources; a philosopher must pick up two forks to eat  
- The simulation ends when a philosopher dies (if they don't eat in time) or all required meals are completed  
- Actions and timestamps are printed to standard output  

## Project Structure*
```
.
├── include
│ └── philo.h
├── Makefile
├── Notes
└── src
├── parsing.c
├── philo.c
├── preparsing.c
├── routine.c
└── utils.c
```

## Build & Run

1. Navigate to the project directory:  
```bash
cd philosophers
```
2. Compile using the provided Makefile:

```
make        # Generates the executable philo
Available make commands:
make clean   # Remove object files
make fclean  # Remove object files and executable
make re      # Recompile everything from scratch
```

3. Running the Program
```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_meals_optional]

Example:
./philo 5 800 200 200 7

This runs a simulation with 5 philosophers, where each dies after 800ms without eating, eats for 200ms, sleeps for 200ms, and stops after 7 meals per philosopher.
```
