*This project has been created as part of the 42 curriculum by jalju-be.*

# Philosophers

## Description

This project is a simulation of the classic **Dining Philosophers Problem**, originally formulated by Edsger Dijkstra in 1965. The goal is to learn about concurrent programming by managing multiple threads that share resources, while avoiding deadlocks and data races.

A number of philosophers sit at a round table with a large bowl of spaghetti. A fork is placed between each pair of adjacent philosophers. Each philosopher alternates between three states: **eating**, **thinking**, and **sleeping**. To eat, a philosopher must pick up the two forks adjacent to them (one on their left, one on their right). If a philosopher does not start eating within a given time window since their last meal (or the start of the simulation), they die and the simulation ends. The simulation also ends successfully if every philosopher has eaten a specified number of meals.

Key constraints and design choices:
- Each philosopher is represented by a separate **POSIX thread**.
- Each fork is protected by a **mutex** to prevent concurrent access.
- A dedicated **monitor thread** continuously checks for death or meal-completion conditions.
- Fork ordering is used to prevent deadlocks.
- Thread-safe getters/setters protect all shared data.

## Instructions

### Requirements

- A C compiler supporting C99 or later (e.g. `cc`, `gcc`, `clang`)
- POSIX threads (`-pthread`)
- `make`

### Compilation

```bash
cd philo
make
```

| Makefile Target | Description              |
|-----------------|--------------------------|
| `make`          | Build the project        |
| `make clean`    | Remove object files      |
| `make fclean`   | Remove objects + binary  |
| `make re`       | Rebuild from scratch     |

### Execution

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` (ms) | Maximum time since the last meal (or simulation start) before a philosopher dies. Must be ≥ 60ms |
| `time_to_eat` (ms) | Duration a philosopher spends eating. Must be ≥ 60ms |
| `time_to_sleep` (ms) | Duration a philosopher spends sleeping. Must be ≥ 60ms |
| `number_of_times_each_philosopher_must_eat` | *(optional)* Simulation stops when every philosopher has eaten at least this many times |

### Examples

```bash
# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# Same as above, but stop after each philosopher has eaten 7 times
./philo 5 800 200 200 7

# One philosopher — will always die (only one fork available)
./philo 1 800 200 200
```

### Output

Each state change is printed as a timestamped log line:

```
timestamp_in_ms  philosopher_id  has taken a fork
timestamp_in_ms  philosopher_id  is eating
timestamp_in_ms  philosopher_id  is sleeping
timestamp_in_ms  philosopher_id  is thinking
timestamp_in_ms  philosopher_id  died
```

## Project Structure

```
philo/
├── main.c            # Entry point and argument count validation
├── parsing.c         # Parses and validates command-line arguments
├── init.c            # Initializes table, philosophers, and forks
├── dinner.c          # Philosopher routine (eat, sleep, think cycle)
├── dinner_utils.c    # Dinner helper functions (synchronization, waiting)
├── monitor.c         # Death detection and meal-count monitoring
├── mutex_threads.c   # Safe wrappers for mutex and thread operations
├── print.c           # Thread-safe timestamped status printing
├── utils.c           # Time utilities and thread-safe getters/setters
├── cleanup.c         # Resource cleanup (destroy mutexes, free memory)
├── philo.h           # Header with structs, enums, and prototypes
└── Makefile          # Build rules
```


## Resources

- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — LLNL](https://hpc-tutorials.llnl.gov/posix/)
- [pthread_mutex_lock(3p) — Linux man page](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [Deadlock — Wikipedia](https://en.wikipedia.org/wiki/Deadlock)
- [CodeVault — Unix Threads in C (YouTube playlist)](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- [What is a thread, really? — Stack Overflow](https://stackoverflow.com/questions/5201852/what-is-a-thread-really)
- [Threads in Operating System — GeeksforGeeks](https://www.geeksforgeeks.org/operating-systems/thread-in-operating-system/)
- [Philosopher 42 — YouTube](https://www.youtube.com/watch?v=VSkvwzqo-Pk&pp=ygUOcGhpbG9zb3BoZXIgNDI%3D)

### AI Usage

AI (GitHub Copilot) was used to generate this README file. No AI tools were used for the implementation of the project code itself.

## Author

**jalju-be** — [42 Amman](https://www.42amman.com/)
