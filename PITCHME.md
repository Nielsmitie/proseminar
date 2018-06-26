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

Note:
Was sind “shared address space platforms”
- Tasks -> eigenen Speicher
- Threads teilen sich einen globalen Speicher
-> Kommunikation implicit(implizit)
- im Gegensatz zu Message passing

- stattdessen heute mit andern Problemen
-> Parallelität darstellen Programmierer
-> synchronisiere, verhindere Probleme (später)
-> minimiere Overhead

-> Keine Memory protection → weniger overhead
+++

@title['Thread definition']
"A thread is a single stream of control in the flow of a program."

+++?code=sample/thread.c&lang=cpp&title=What+are+threads+?

@[1,2](Loop over rows and columns)
@[4,5,6](Multiply elements from row and column vector)

Note:
Erklärung zu dem Zitat

- Male Bild zur Erklärung
	- N Zeilen
	- danach N Spalten
	- Danach das Ergebnis

- Zeige den Code daran

+++?code=sample/thread_def.c&lang=cpp&title=What+are+threads+?

@[3, 7](Each multiplication can be performed by one thread because they are independent of each other)

Note:
- Alle Prozessoren brauchen zugriff auf Speicher

- Threads Laufzeit stack erzeugt -> bad practice Speicher im lokalen Speicher zu verwenden

- Außerdem wird zugriff auf Globalen Speicher immer langsamer sein als auf Cache
+++

## Advantages of Threads

- Software portability |

- Latency hiding |

- Scheduling and load balancing |

- Widespread use |

Note:
Software portability
- Egal wie viele Kerne
- geht auch auf 1 Kern

Latency Hiding
- I/O und Kommunikation
- Wenn Thread wartet übernimmt ein anderer

Scheduling and Load Balancing
- Erstelle einfach Threads
-> scheduler kümmert sich um gleiche Auslastung
- Kein explizites Load Balancing

Widespread use
- die oben gennanten sachen
-> easier to write
- ein standard für viele Probleme
- Tools sind gut gemacht und viel benutzt

---

## POSIX thread API

- IEE standard

- Used for C

- Similar to APIs of other programming languages

Note:
Ich werde ein paar Sachen weglassen von parametern

Ich werde sehr einfache code beispiele ohne nutzen verwenden

Im Code werden aus einfachheit ein paar Details vernachlässigt

+++

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

Note:
pthread_create
- handle is referenz zu thread
- übergebe Funktion
- Übergebe argumente für die Funktion
- Funktion hat Argument void *s

pthread_join
- threa handle
- **ptr schreibt pthread_exit zu der Stelle
- ist meist NULL

+++?code=sample/pthread_example_1.c&lang=cpp&title=Pthread+Example+I
@[2](Create an array entry for every thread. The results will be written to the array)
@[3](Create an array for the thread handles)
@[4-7](Initialise all threads and assign them a position in the result array)
@[8-10](Wait for every thread to terminate)

Note:
- Jeder Prozess bekommt eigene Nummer
- Alle prozesse werden gestartet und schreiben in den Speicher ihr Ergebnis

- Warten auf Vollendung der Aufgabe mit join

+++?code=sample/pthread_example_2.c&lang=cpp&title=Pthread+Example+II

@[1,2](Cast the void* argument to int*)
@[4-7](Perform work)
@[9](Save the results)
@[11](Terminate thread)

Note:
- Funktion zum Ausführen
- Casted die number zu int pointer

- do work macht irgendwas

- update das Ergebnis im globalen Speicher

+++?code=sample/pthread_example_3.c&lang=cpp&title=Pthread+Example+III

@[5](Save results at every iteration)

Note:
- Diesmal wird Nummer direkt geändert

- Wenn so ausgeführt
- Beobachtung: Läuft viel Langsamer

- Frage ans Publikum warum?

- Array wir für jeden Prozess geladen
-> wegen Cache lines

- Wenn ein Prozess aktualisiert wird die 
Cache line invalid gesetzt

---

## Synchronization

- Use a global integer instead of an integer array

	```cpp
	if(my_cost < best_cost)
		best_cost = my_cost
	```

- What is the problem when we use concurrent threads? |

Note:
Problems:
- Nicht Deterministisch
	- Denn scheduling ist random
- inkonsisten
	- serialisierung würde zu anderem Ergebnis 			führen
-> race condition
(kann nur im parallelen passieren)

- wir wollen also solche kritischen Stellen finden

Und

- diese als atomic operation implementieren

Atomic ist alles, was einen assembler Befehl hat

+++

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

Note:
pthread_mutex_lock
- übergib einen mutext_lock
- versucht zu locken
- wenn unlocked -> lock mutex -> fahre fort
- wenn locked -> block -> warte auf unlock

- kann in deadlock geraten
-> wirft error

Pthread_mutex_unlock
- sollte nach dem verlassen eines kritischen Bereichs ausgeführt werden
-> neuer Thread kann Sektion betreten
- sonst Deadlock

+++?code=sample/mutex_lock_example_1.c&lang=cpp&title=Mutex-Lock+Example+I

@[1](Create a global lock variable)
@[2](Global varaible with minimum value)
@[4,5](Two threads with local values)
@[6](Initialize the lock)
@[7-13](Start the threats and wait for termination)

+++?code=sample/mutex_lock_example_2.c&lang=cpp&title=Mutex-Lock+Example+II

@[4](Lock the critical section)
@[6,7]()
@[9](Unlock critical section to allow a different thread access)

---

## Condition variables for Synchronization

- Problem: Normal mutex-locks need to regularly poll the lock
- Goal: Minimize the overhead of mutex-lock

- Suspend the thread
- Wait for a condition to be fullfilled
- Wake up the thread

+++

## Condition wait and signal

```cpp
int pthread_cond_wait(
	pthread_cond_t *cond,
	pthread_mutex_t *mutex
);

int pthread_cond_signal(
	pthread_cond_t *cond
);
```

@[1,4](Suspends the thread and waits)
@[2](Condition to be fullfilled)
@[3](Reliefes the lock while waiting and requires it after wake up)

@[6,8](Signales at least one thread to wake up)
@[7](The condition that is now fullfilled)

Note:
- Damit kann man coole Sachen machen (später)
- Wait ist immer in Verbindung mit einem Mutex zu benutzen
- Weckt mind. 1 Thread. Deshalb benutzt man loop.

+++

## Producer Consumber Pipeline

- Producer loads data from disk @af[arrow-right] writes it to a queue
- Consumer takes data from list @af[arrow-right] consumes data by processing it

Note:
- AI learning
- Load with mostly idle task
- Consumer can use 100% CPU all the time
- There is always data in queue. If queue full Producer stop
- If queue empty stop consumer
- both times one is waiting
- Hier werden wir nur mit starker Vereinfachung

+++?code=sample/cond_mutex_1.c&lang=cpp&title=Producer+-+Consumer+Example+I

@[1](Conditions to signal and wait for)
@[2](One mutex lock for one critical section)
@[6](At the beginning no task is available)
@[7,8](Initialize condition varaibles)
@[9](Initialize Mutex)

+++?code=sample/cond_mutex_3.c&lang=cpp&title=Producer+-+Consumer+Example+II

@[1]()
@[2](Enter critical section)
@[3-5](While no task available wait and relief lock for producer task)
@[7](Consumer can now take data)
@[8](Set task_available to 0)
@[9](Wake up Producer)
@[10](Unlock critical section)
@[11](Process the data outside the critical section to increase performance)

Note:
- Besondere Betonung darauf, was passiert, wenn noch keine Daten da sind

+++?code=sample/cond_mutex_2.c&lang=cpp&title=Producer+-+Consumer+Example+III

@[2](Loop until done)
@[3](Placeholder for any kind of task)
@[4](Entering critical section)
@[5](Best practice to use a loop)
@[6,7](Release lock and wait for condition to be fullfilled)
@[9](Inside critical section we can insert the data)
@[10]()
@[11](Signal the consumer)
@[12](Release lock so consumer can enter the critical section)


Note:
- produce outside of critical section for better performance
- Loop: OS signal can wake up process or broadcast can wake up multiple

---

## Composite Synchronization Constructs
#### A high-level presentation
- Read-Write Locks
- Barriers

Note:
- Kein Code mehr
- Sinnvoll für die Praxis

+++ 
## Read-Write Locks

- Example: Database
- Many read operation
- Very few write operations

- Use: rlock, lock, unlock

+++?image=assets/read-write.png

+++

## Barriers







