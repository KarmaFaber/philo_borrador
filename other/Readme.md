# Philosophers

## Authorized functions

| Name                | Function Prototype                               | Description                                                                                         | Parameters                              | Return                      |
|---------------------|-------------------------------------------------|-----------------------------------------------------------------------------------------------------|----------------------------------------|-----------------------------|
| `memset` -`<string.h>`           | `void *memset(void *s, int c, size_t n)`         | Fills the first `n` bytes of the memory area pointed to by `s` with the constant byte `c`.          | `s`: memory area; `c`: byte value; `n`: number of bytes | Pointer to memory area `s` |
| `printf` -`<stdio.h>`          | `int printf(const char *format, ...)`            | Sends formatted output to the standard output stream.                                               | `format`: format string; ...: values   | Number of characters written |
| `malloc` -`<stdlib.h>`           | `void *malloc(size_t size)`                      | Allocates `size` bytes of uninitialized memory.                                                     | `size`: number of bytes                | Pointer to allocated memory or NULL |
| `free` -`<stdlib.h>`             | `void free(void *ptr)`                           | Frees the memory space pointed to by `ptr`, which must have been returned by a previous call to `malloc`. | `ptr`: pointer to memory to free       | None                        |
| `write` -`<unistd.h>`            | `ssize_t write(int fd, const void *buf, size_t count)` | Writes `count` bytes from the buffer `buf` to the file descriptor `fd`.                             | `fd`: file descriptor; `buf`: data; `count`: bytes to write | Number of bytes written or -1 |
| `usleep` -`<unistd.h>`           | `int usleep(useconds_t usec)`                    | Suspends execution of the calling thread for at least `usec` microseconds.                          | `usec`: number of microseconds         | 0 on success, -1 on error  |
| `gettimeofday` -`<sys/time.h>`    | `int gettimeofday(struct timeval *tv, struct timezone *tz)` | Gets the current time, expressed as seconds and microseconds since the Epoch.                       | `tv`: time structure; `tz`: timezone (can be NULL) | 0 on success, -1 on error  |
| `pthread_create` -`<pthread.h>`  | `int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg)` | Creates a new thread executing the function `start_routine`.                                        | `thread`: thread ID; `attr`: attributes; `start_routine`: function; `arg`: arguments | 0 on success, error code on failure |
| `pthread_detach` -`<pthread.h>`  | `int pthread_detach(pthread_t thread)`            | Detaches the specified thread, allowing its resources to be automatically released upon termination. | `thread`: thread ID                    | 0 on success, error code on failure |
| `pthread_join` -`<pthread.h>`    | `int pthread_join(pthread_t thread, void **retval)` | Waits for the specified thread to terminate.                                                       | `thread`: thread ID; `retval`: return value pointer | 0 on success, error code on failure |
| `pthread_mutex_init` -`<pthread.h>` | `int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)` | Initializes a mutex object with the given attributes.                                               | `mutex`: mutex object; `attr`: attributes (can be NULL) | 0 on success, error code on failure |
| `pthread_mutex_destroy` -`<pthread.h>` | `int pthread_mutex_destroy(pthread_mutex_t *mutex)` | Destroys a mutex object, releasing its resources.                                                   | `mutex`: mutex object                  | 0 on success, error code on failure |
| `pthread_mutex_lock` -`<pthread.h>`| `int pthread_mutex_lock(pthread_mutex_t *mutex)` | Locks the specified mutex. If the mutex is already locked, the calling thread blocks until it becomes available. | `mutex`: mutex object                  | 0 on success, error code on failure |
| `pthread_mutex_unlock` -`<pthread.h>`| `int pthread_mutex_unlock(pthread_mutex_t *mutex)` | Unlocks the specified mutex.                                                                        | `mutex`: mutex object                  | 0 on success, error code on failure |




## Notes

- Modify `commands.txt` and `special_cases.sh` to include any additional test cases specific to your implementation.
- Review `commands.txt` for a list of standard commands used during testing and `special_cases.sh` for special cases. 

## ➾ Contributing

* Check the open issues or open a new issue to start a discussion around your feature idea or the bug you found. 
* Fork the repository, make your changes, and add yourself to AUTHORS.md
* Send a pull request.

## ➾ Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 


## ➾ Authors

* [Karma Faber](https://github.com/KarmaFaber). 


## ➾ License

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or distribute this software, either in source code form or as a compiled binary, for any purpose, commercial or non-commercial, and by any means.

In jurisdictions that recognize copyright laws, the author or authors of this software dedicate any and all copyright interest in the software to the public domain. We make this dedication for the benefit of the public at large and to the detriment of our heirs and successors. We intend this dedication to be an overt act of relinquishment in perpetuity of all present and future rights to this software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
