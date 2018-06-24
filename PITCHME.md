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

"A thread is a single stream of control in the flow of a program."

---?code=sample/thread.c&lang=c&title=What+are+threads+?

@[1,2](Loop over rows and columns)
@[4,5,6](Multiply elements from row and column vector)

---?code=sample/thread_def.c&lang=c&title=What+are+threads+?

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

---?code=sample/pthread_example_1.c&lang=c&title=Pthread+Example+I
@[2](Create an array entry for every thread. The results will be written to the array)
@[3](Create an array for the thread handles)
@[4-7](Initialise all threads and assign them a position in the result array)
@[8-10](Wait for every thread to terminate)

---?code=sample/pthread_example_2.c&lang=c&title=Pthread+Example+II

@[1,2](Cast the void* argument to int*)
@[4-7](Perform work)
@[9](Save the results)
@[11](Terminate thread)

---?code=sample/pthread_example_3.c&lang=c&title=Pthread+Example+III

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

@title[JavaScript Block]

<p><span class="slide-title">JavaScript Block</span></p>

```javascript
// Include http module.
var http = require("http");

// Create the server. Function passed as parameter
// is called on every request made.
http.createServer(function (request, response) {
  // Attach listener on end event.  This event is
  // called when client sent, awaiting response.
  request.on("end", function () {
    // Write headers to the response.
    // HTTP 200 status, Content-Type text/plain.
    response.writeHead(200, {
      'Content-Type': 'text/plain'
    });
    // Send data and end response.
    response.end('Hello HTTP!');
  });

// Listen on the 8080 port.
}).listen(8080);
```

@[1,2](You can present code inlined within your slide markdown too.)
@[9-17](Displayed using code-syntax highlighting just like your IDE.)
@[19-20](Again, all of this without ever leaving your slideshow.)

---?gist=onetapbeyond/494e0fecaf0d6a2aa2acadfb8eb9d6e8&lang=scala&title=Scala GIST

@[23](You can even present code found within any GitHub GIST.)
@[41-53](GIST source code is beautifully rendered on any slide.)
@[57-62](And code-presenting works seamlessly for GIST too, both online and offline.)

---

## Template Help

- [Code Presenting](https://github.com/gitpitch/gitpitch/wiki/Code-Presenting)
  + [Repo Source](https://github.com/gitpitch/gitpitch/wiki/Code-Delimiter-Slides), [Static Blocks](https://github.com/gitpitch/gitpitch/wiki/Code-Slides), [GIST](https://github.com/gitpitch/gitpitch/wiki/GIST-Slides) 
- [Custom CSS Styling](https://github.com/gitpitch/gitpitch/wiki/Slideshow-Custom-CSS)
- [Slideshow Background Image](https://github.com/gitpitch/gitpitch/wiki/Background-Setting)
- [Slide-specific Background Images](https://github.com/gitpitch/gitpitch/wiki/Image-Slides#background)
- [Custom Logo](https://github.com/gitpitch/gitpitch/wiki/Logo-Setting) [TOC](https://github.com/gitpitch/gitpitch/wiki/Table-of-Contents) [Footnotes](https://github.com/gitpitch/gitpitch/wiki/Footnote-Setting)

---

## Go GitPitch Pro!

<br>
<div class="left">
    <i class="fa fa-user-secret fa-5x" aria-hidden="true"> </i><br>
    <a href="https://gitpitch.com/pro-features" class="pro-link">
    More details here.</a>
</div>
<div class="right">
    <ul>
        <li>Private Repos</li>
        <li>Private URLs</li>
        <li>Password-Protection</li>
        <li>Image Opacity</li>
        <li>SVG Image Support</li>
    </ul>
</div>

---

### Questions?

<br>

@fa[twitter gp-contact](@gitpitch)

@fa[github gp-contact](gitpitch)

@fa[medium gp-contact](@gitpitch)

---?image=assets/image/gitpitch-audience.jpg&opacity=100

@title[Download this Template!]

### <span class="white">Get your presentation started!</span>
### [Download this template @fa[external-link gp-download]](https://gitpitch.com/template/download/white)

