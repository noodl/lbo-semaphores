# Terminology used in the book

## Semaphores
Counting semaphores (the main kind discussed in the book) are integers with atomic increment and decrement operations. Attempting to decrement a semaphore below zero will block the thread until another thread performs an increment. These operations have a variety of names depending on the programming environment. Invented by Edsger Dijkstra.

## Serialization
Events must happen in a fixed order.

## Mutual exclusion
Events must not happen at the same time.

## Parallelism
Events happening at (nearly) the same moment in time.

## Concurrency
The appearance of parallelism, even if it's only emulated by switching quickly between tasks. Event happening concurrently can happen in any order.

## Non-determinism
With threads it is often not possible to tell from looking at a program in which order events will happen.

## Shared variable

### Concurrent writes
2 or more threads write to a variable without reading it first.

### Concurrent updates
2 or more threads read then write to a variable, usually with a calculation based on the read value.

## Atomicity
Atomic operations are those which cannot be interrupted and either complete or fail as a whole.

## Rendezvous
A point in a program where threads wait for each other to catch up before carrying on.

## Deadlock
A failure condition in which 2 or more threads are waiting for each other and so cannot continue.

## Multiplex
Generalization of a mutex which allows up a fixed maximum number of threads to be executing a section of code at once.

## Symmetric vs Asymmetric solutions
Concurrent algorithms which are implemented either with the same code or separate code per thread.

## Critical section
A section of code that may be executed by at most one thread at a time.
