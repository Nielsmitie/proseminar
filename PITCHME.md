## Programming Shared Address Space Platforms 

#### Fachgebiet System- und Rechnerarchitektur
##### Presented by Niels Nuthmann

---

## Overview

- Threads |
- POSIX thread basics |
- Synchronization |
- Advanced usage |

---

## Shared Address Space Platforms

- Memory is shared @fa[arrow-right] Communication is implicit |

- Problems: |
   * Express concurrency |
   * Handle synchronization |
   * Minimize overhead |

---
@title['Thread definition']
"A thread is a single stream of control in the flow of a program."

---?code=sample/thread.c&lang=cpp&title=What+are+threads+?

@[1,2](Loop over rows and columns)
@[4,5,6](Multiply elements from row and column vector)

---?code=sample/thread_def.c&lang=cpp&title=What+are+threads+?

@[3, 7](Each multiplication can be performed by one thread because they are independent of each other)

---

## Advantages of Threads

- Software portability |

- Latency hiding |

- Scheduling and load balancing |

- Widespread use |

---

## POSIX thread API

- IEE standard

- Used for C

- Similar to APIs of other programming languages

---

<p><span class="slide-title">Basics: Creation and termination of threads</span></p>

```cpp
// create a thread
pthread_create(
	pthread_t *thread_handle,
	void (*thread_function)(void*),
	void *arg
)
// wait for termination of a thread
pthread_join(
	pthread_t thread,
	void **ptr
)
```
@[2-6]
@[3](Pass a handle to access the thread later on)
@[4](A function pointer)
@[5](Argument for the function. Pointer to variable or struct)

@[8-11]
@[9](Thread handle)
@[10](Writes phtread_exit at ptr location. We use NULL)

---?code=sample/pthread_example_1.c&lang=cpp&title=Pthread+Example+I
@[2](Create an array entry for every thread. The results will be written to the array)
@[3](Create an array for the thread handles)
@[4-7](Initialise all threads and assign them a position in the result array)
@[8-10](Wait for every thread to terminate)

---?code=sample/pthread_example_2.c&lang=cpp&title=Pthread+Example+II

@[1,2](Cast the void* argument to int*)
@[4-7](Perform work)
@[9](Save the results)
@[11](Terminate thread)

---?code=sample/pthread_example_3.c&lang=cpp&title=Pthread+Example+III

@[5](Save results at every iteration)

---
## Synchronization

- Use a global integer instead of an integer array

	```cpp
	if(my_cost < best_cost)
		best_cost = my_cost
	```

- What is the problem when we use concurrent threads? |

---

## Mutex-lock

```cpp
// initialize lock
pthread_mutex_init(
	pthread_mutex_t *mutex_lock
)
// lock mutex
pthread_mutex_lock(
	pthread_mutex_t *mutex_lock
)
// unlock mutex
pthread_mutex_unlock(
	pthread_mutex_t *mutex_lock
)
```

@[2](Initilaize)
@[2,6](Lock)
@[2,6,10](Unlock)

@[3,7,11](Each time supply a mutex lock)

---?code=sample/mutex_lock_example_1.c&lang=cpp&title=Mutex-Lock+Example+I

@[1](Create a global lock variable)
@[2](Global varaible with minimum value)
@[4,5](Two threads with local values)
@[6](Initialize the lock)
@[7-13](Start the threats and wait for termination)

---?code=sample/mutex_lock_example_2.c&lang=cpp&title=Mutex-Lock+Example+II

@[4](Lock the critical section)
@[6,7]()
@[9](Unlock critical section to allow a different thread access)

---

## Condition variables for Synchronization

---


