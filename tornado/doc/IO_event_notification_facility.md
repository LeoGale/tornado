[TOC]
## poll
## epoll

 * Description
  monitoring multiple file descriptors to see if I/O is possiable on any of them.

 * mode
    * ET(edge-triggered)
    * LT(level-triggered)

 * epoll instance
 An in-kernel data structure, which from a user-space perspective
     * the interest list
        sometimes also called the epoll set, which consists of file descriptors that the process has registered an interest in monitoring.
     * the ready list
        The set of file descriptors that are <font color=red>READY</font> for I/O.
        > the ready list is a subset (a set of references) of the filre descriptors in the interest list.
### function calls
* **<font color=green>epoll_create(int size)</font>**
* **<font color=green>epoll_create1(int flags) //EPOLL_CLOEXEC</font>**
  * return a file descriptor referring to the new epoll instance.
  * When no longer required, the file descriptor mentioned above should be closed by using close().
  * ERRORS
    * **EINVAL** size is not positive
    * **EINVAL** Invalid value specified in flags
    * **EMFILE** The per-user limit on the number of epoll instances imposed by */proc/sys/fs/epoll/max_user_instances*  was encountered.
    * **ENFILE** The system-wide limit on the total number of open files has been reached.
    * **EINVAL** There was insufficient memory to create the kernel object.
* **<font color=green>epoll_ctl</font>**
This system call is used to add, modify, or remove entries in the interest list of the epoll instance referred to by the file descriptor *epfd*. It requests that the operation op be performed for the target file descriptor, *fd*.

  ```C++
  #include <sys/epoll.h>
  int epoll_ctl(int epfd, int op, int fd, struct epoll_event * event);
  ```
  * **OP**
      * **EPOLL_CTL_ADD**
        Add fd to the interest list and associate the setting specified in event with the internal file linked to fd.
      * **EPOLL_CTL_MOD**
      * **EPOLL_CTL_DEL**

  * epoll_event
  ```C++
  typedef union epoll_data {
    void *ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
  }epoll_data_t;

  struct epoll_event {
    uint32_t events; /*epoll_events*/
    epoll_data_t data;
  };
  ```
  * events
    * **EPOLLIN**
    The associated file is available for read operation
    * **EPOLLOUT**
    The associated file is available for write operation
    * **EPOLLRDHUP**
    Stream socket peer closed connection, or shut down write half of connection.
      > This flag is especially useful for writing simple code to detect peer shutdown when using edge-triggered monitoring
    * **EPOLLPRI**
    There is some exceptional condition on the file descriptor. Possibilities include:
      * There is out-of-band data on a TCP socket (see tcp(7))
      * A pseudoterminal master in packet mode has seen a state change to the slave (see ioctl_tty(2))
      * A cgroup.events file has been modified (see cgroups(7))
    * **EPOLLET**
    Sets the Edge triggered behavior for the associated file descriptor
    * **EPOLLONESHOT**
    Sets the on-shot behavior for the associated file descriptor.
      > that''s means after an event is pulled out with epoll_wait(2), the associated file descriptor is internally disable and no other events will be reported by the epoll instance.
    * **EPOLLWAKEUP**
    * **EPOLLEXCLUSIVE**
  * ERRORS
    * **EBADF**
    * **EEXIST**
    * **EINVAL**
    * **ELOOP**
    * **ENOENT**
    * **ENOMEM**
    * **ENOSPC**
    * **EPERM**

* **<font size = 5 color=green>epoll_wait</font>**

  The epoll_wait system call waits for events on the epoll instace referred to by the file desciptor epfd.

  Time is measure against the CLOCK_MONOTONIC clock.

  the call will block until either:
    * A file descriptor delivers an event;
    * the call is interrupted by a signal handlers;
    * the timeout expires
> specifying a timeout of -1 cause epoll_wait to block indefinitely, while specifying a timeout equal to zero cause epoll_wait to return immediately, even if no events are available.

```C++
#include <sys/epoll.h>
int epoll_wait(int epfd, struct epoll_event* events,
                  int maxevents, int timeout/*in millisec*/);

```
* return value
  when successful, epoll_wait returns the number of file descriptors ready for the requested I/O, or zero if no file descriptor became ready for during the requested tieout milliseconds.

  when an error occurs, epoll_wait return -1 and errno is set appropriately.

* ERROR
  * **EBADF**
  * **EFAULT**
  * **EINTR**
  * **EINVAL**

## FAQ
### The difference between level-triggered and edge-triggered
### How run when the number of file descriptors return by epoll_wait is bigger than the max_event_size.

## Reference
[Epoll]()
[Epoll_create]()
[Epoll_ctl]()
[Epoll_wait]()
