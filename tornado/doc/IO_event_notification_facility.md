## poll
## epoll
 
 * description
 
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
* system calls
    * epoll_create(int size);//size should be a
    * epoll_create1(int flags); //EPOLL_CLOEXEC

## FAQ
The difference between level-tiggered and edge-triggered
