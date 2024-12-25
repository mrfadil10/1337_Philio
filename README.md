# Philosophers

A multithreading project implementing the dining philosophers problem, part of the 1337 Coding School curriculum. This project demonstrates thread management, mutex usage, and process synchronization.

## Overview
The program simulates philosophers sitting at a round table, alternating between eating, thinking, and sleeping. They share forks and must coordinate to avoid deadlocks and starvation.

## Usage
```bash
# Compile
make

# Run program
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

# Example
./philo 5 800 200 200 7
```

## Arguments
- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die`: Time in milliseconds before a philosopher dies from starvation
- `time_to_eat`: Time in milliseconds to eat (needs two forks)
- `time_to_sleep`: Time in milliseconds to sleep
- `[number_of_times_each_philosopher_must_eat]`: Optional argument for simulation end condition

## Features
- Thread management for each philosopher
- Mutex protection for forks and shared data
- Death monitoring system
- Precise timing management
- Status messages for philosopher actions
- Clean memory management
- No data races

## Project Structure
```
philosophers/
├── Libft/
├── obj/
├── Makefile
├── dead_philo.c
├── life_cycle.c
├── main.c
├── philo_tools.c
├── start.c
├── utils.c
├── main.c
└── Readme.md
```

## Technical Details
- Each philosopher is a thread
- Forks are protected by mutexes
- Death check occurs every millisecond
- Timestamps are in milliseconds since simulation start
- No memory leaks
- No zombie processes

## Error Handling
- Input validation
- Memory allocation checks
- Thread creation failure handling
- Mutex initialization checks

## Norm Compliance
Follows 42 School norm:
- Functions under 25 lines
- Max 5 functions per file
- No global variables
- Error messages to STDERR

## Resources
- POSIX Threads documentation
- Unix system calls manual
