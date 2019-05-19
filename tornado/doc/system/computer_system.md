[TOC]
# computer systems
A major theme in computer systems is to provide abstract representations at different levels to hide the complexity of the actual implementations.

Languages provide different forms and levels of support for abstraction.

One of the most important lesson in this book is that application programmers who are aware of cache memories can exploit them to improve the performance of their programs by an order of magnitude.

## main memory
> The main memory is a temporary storage device.

    * Physically, main memory consists of a collection of dynamic random access memory(DRAM) chips.
    * Logically, memory is organized as a linear array of bytes, each with its own unique address(array index) starting at zero.
    
## processor
> From the time that power is applied to the system util the time that the power is shut off, a processor repeatedly executes the instruction(interprets the bits in the instruction) pointed at by the program counter and updates the program counter to point to the next instruction, which may or may not be contiguous In memory.


    * The central processing unit(CPU), or simply processor, is the engine that interprets (or executes) instructions stored in main memory.
    * At its core is a word-size storage device (or register) called the program counter(PC).

## A few of these simple operations that revolve around the main memory
    * Register file
        * A small storage device that consists of a collection of word-size registers, each with own unique name
    * Arithmetic/logic unit(ALU)
        * The ALU computes new data and address values.
## Simple Operations
    * Load: copy a byte or a word from main memory into a register.
    * Store: copy a byte or a word from a register to a location in main memory
    * Operate: Copy the contents of two registers to the ALU, perform an arithmetic operation on the two words, and store the results tin a register.
    * Jump: Extract a word from the instruction itself and copy that word into the program counter(PC).
### Example
#### Hello
    * Figure1.5 Reading the Hello command from the keyboard.
    * Figure1.6 Using a technique known as direct memory access(DMA), the data travel directly from disk to main memory, without passing through the processor.
    * Figure1.7 Once the code and data in the hello object file are loaded into main memory, the processor begin executing the machine-language instructions in the hello program’s main routine.
#### Overhead of cache matter
    * Copied hello program to main memory
        * Disk --> Disk Controller --> I/O bridge --> Main memory
    * instructions are copied to processor
        * N/A
    * Writing the output string from main memory to the display device
        * main memory --> memory bus --> I/O bridge --> system bus --> bus interface(CPU) --> register file --> bus interface(CPU) --> system bus --> I/O bridge --> I/O bus --> Graphics adapter --> display
    > There are cache memories (cahches) between bus interface(CPU) and register files
    
### Cache memory
To deal with the processor-memory gap, system designers include smaller, faster storage devices called cache memories that serve as temporary staging areas for information that the processor is likely to need in the future.

L1 cache, L2 cache: implemented with a hardware technology known as static random access memory(SRAM)
It might take 5 times longer for the processor to access L2 cache than the L1 cache, but is still 5~10 times faster than accessing the main memory.
L3 cache, L4 cache: ….

Disk drive—> main memory : might be 1,000 times larger than
Disk drive—> main memory : might take the processor 10,000,000 times longer to read a word from disk.
Processor —> main memory : read data from the register file almost 100 times faster than from memory


### The operation system manages the hardware

-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                      Application programs                         |
-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-++      Software
|                      Operating System                               |
-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|    Processor   |   Main memory   |     I/O devices    |    Hardware
-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

#### Primary purpose
    * To protect the hardware from misuse by runaway applications
    * To provide applications with simple and uniform mechanism for manipulating complicated  and often widely different low-level hardware devices
#### Fundamental abstractions
##### Processes
> they are abstractions for the processor, main memory, and I/O devices.

    *  The operating system keeps track of all the state information that the process need in order to run, this state, which is known as **context**.
    *  Context which includes information, such as the current values of the PC, the register file, and the contents of main memory.
    * Context Switching
     Multi process on a uniprocessor system
         * User code —> kernel code —> user code
         * A particular case is oversubscription.
     * kernel
     It is the portion of operation system code that is always resident in memory.
     * Threads
      Although we normally think of a process as having a single control flow, in modern systems a process can actually consist of multiple execution units, called threads
          * Each running in the context of the process
          * Sharing the same code and global data
          * It is more easier to share data between multiple threads and multiple process.
          * Threads are typically more efficient than process.(Why?tiny?)
          
##### virtual memory
 it is an abstraction for both the main memory and disk I/O devices.
 
     * Virtual memory is an abstraction that provides each process with the illusion that it has exclusive use of the main memory.
     * Virtual address space.
     Each process has the same uniform view of memory, which is known as its virtual address space
     * Layout
     The address increate from the bottom to the top, the topmost region of system that is. common to all processes.
     - ++++++++++++++++++++++++++++++++++++++
     - +                 Kernel virtual memory
     - ++++++++++++++++++++++++++++++++++++++
     - +          User stack(created at run time)
     - ++++++++++++++++++++++++++++++++++++++
     - +               #################
     - ++++++++++++++++++++++++++++++++++++++
     - + Memory-mapped region for shared libraries
     - ++++++++++++++++++++++++++++++++++++++
     - +               #################
     - ++++++++++++++++++++++++++++++++++++++
     - +             Run-time heap(created by malloc)
     - ++++++++++++++++++++++++++++++++++++++++++++++++
     - +                Read/Write data                                       +
     - ++++++++++++++++++++++++++++++++++++++Loaded from the hello executable file
     - +               Read-only code and data                         +
     - ++++++++++++++++++++++++++++++++++++++<— program start
     * Discuss each well-defined areas, starting with the lowest addressed and working our way up.
     * program code and data
     * Heap
     * shared libraries
     * stack
     In particular, each time we call a function, the stack grows. Each time we return from a function, it contracts.
     * Kernel virtual memory
    
#### Files
They are abstractions for I/O devices.

    * A file is a sequence of bytes, nothing more and nothing less.
    * System provides applications with a uniform view of all the varied I/O devices that might be contained in the system.(benefits)
        * The application programmers can manipulate the contents of a disk file even they are blissfully unaware of  the specific dis technology.
        * Further, the same program will run on different systems that use different disk technology.
    
### System communicate with other systems using networks.
    * Up to this point, we have trated a system as an isolated collection of hardware and software. In practice, modern systems are often linked to other systems by networks
    * using telnet to run hello remotely over a network.
### important thems
    * Amdahl’s law
    * Concurrency and parallelism( Parallelism can be exploited at multiple levels of abstraction in computer system)
    * highlight three levels here, working from the highest to the lowest level in the system hierarchy.
    * Thread-level concurrency
        *  Hyperthreading, sometime called simultaneous multi-threading, is a technique that allows a single CPU to execute multiple flows of control.
    * Instruction-level Parallelism
        * At a much lower level of abstraction, modern processors can execute multiple instructions at one time, a property known as instruction-level parallelism.
        * Pipelining
    * Single-Instruction, Multiple-Data(SIMD) Parallelism
    
## Representing and manipulating information
### The three most important representations of numbers
    * Unsigned encodings
    Unsigned encodings are based on traditional binary notation, representing numbers greater than or equal to 0.
    * Two’s-complement encodings
    Two’s-complement encodings are the most common way to represent singed integers, that is, number that may be either positive or negative.
    * Floating-point encodings
    Floating-point encodings are a base-2 version of scientific notation for representing real numbers.
### overflow
Computer representations use a limited number of bits to encode a number and hence some operations can overflow when the results are too large to be represented.
### information storage
>The compiler and run-time system partitions the virtual memory space into more manageable units to store the different program objects, that is, program data, instructions, and control information.

    * Blocks of 8 bits, or bytes, as the smallest addressable unit of memory.
    * Virtual memory
    A machine-level program views memory as a very large array of bytes, referred to as virtual memory
    * Address
    Every byte of memory is identified by a unique number, known as its address.
    * Virtual address space
    It is a set of all possible addresses. It is just a conceptual image presented to the machine-level program.
    
#### data sizes
##### Word size
Every computer has a word size, indicating the nominal size of pointer data.

    * Virtual address
    since a virtual address is encoded by such a word, the most important system parameter determined by the word size is the maximum size of virtual address space.
    * A w-bit word size, the virtual address can range from 0 ~ 2^w -1
        * it means the program access to at most 2**w bytes.
        * 32-bit word size limits the virtual address space to 4 gigabytes (4G) that is, just over 4 x 10^9 bytes.
            * 2^32 =     4294967296
            * 4*10^9 = 4000000000
            * Gcc -m32 prog.c
        * 64-bit word size leads to a virtual address space of 16 exabytes, or around 1.84 x 10^19 bytes.
            * Gcc -m64 prog.c
##### multiple data formats
    * Integer data
    * Floating-point data
        - Single precision ( declared in C as float), 4 bytes
        - Double precision (declared in C as double) 8 bytes
> The typical size relies on compiler(char is singed char ?) and system settings(32-bit or 64-bit). C99 fixed data size(int64_t) regardless of compiler and system setting.

##### Addressing and Byte ordering
For program objects that span multiple bytes, we must establish two conventions

    * What the address of the object will be
    * How we will order the bytes in memory
        * Little endian (0x01234567)
        - +++++++++++++++++++++++++++++++++++
        - +.  67.    +     45      +.       23      +.      01.           +
        - +++++++++++++++++++++++++++++++++++
        - +. 0x100+    0x101 +      0x102.   +.     0x103.     +
        - +++++++++++++++++++++++++++++++++++
        
        * Big endian(0x01234567)
        - +++++++++++++++++++++++++++++++++++
        - +.  01.    +     23      +.       45       +.      67.          +
        - +++++++++++++++++++++++++++++++++++
        - +. 0x100+    0x101 +      0x102.   +.     0x103.     +
        - +++++++++++++++++++++++++++++++++++
    * That's why we should conver hosted-bytes-order to network-bytes-order //TODO chinese english ?
## instructions set architecture

## thread
Posix thread.

A single process can contain multiple threads, all of which are executing the same program.

The attributes are process-wide rather than per-thread.

    - Process id, Parent process id, process group id and session id
    - User and group IDs, controlling terminal
    - Open file descriptors, record locks(see fcntl(2)), file mode creation mask(umask(2)),current directory(chdir(2)) and root directory(chroot(2))
    - Interval timers(setitimer(2)) and POSIX timers(timer_create(2))
    - Nice value(setpriority(2)), resource limits(setrlimit(2))
    - Measurements of the consumption of CPU time(times(2)) and resources(getrusage(2))
    
The attributes are distinct for each thread.

    - Stack
    - Thread id
    - Signal mask(pthred_sigmask(3))
    - The errno variable
    - Alternate signal stack(sigaltstack(2))
    - Real-time scheduling policy and priority (sched(7))
    - capabilities( see capabilities(7))
    - CPU affinity(scheduler’s-setaffinity(2))
