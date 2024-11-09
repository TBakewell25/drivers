# Linux Kernel Library Reference Guide

## Core Kernel Headers

### Essential Infrastructure
- `<linux/kernel.h>`
  - Core kernel definitions and macros
  - printk() and other basic utilities
  - Basic type definitions

- `<linux/module.h>`
  - Module loading/unloading infrastructure
  - Module parameters
  - Module license declarations
  - Module dependencies

- `<linux/init.h>`
  - Initialization and cleanup macros
  - __init and __exit markers
  - Module initialization sequencing

- `<linux/types.h>`
  - Basic kernel type definitions
  - Platform-independent types
  - Common type utilities

### Memory Management
- `<linux/slab.h>`
  - Kernel memory allocation
  - kmalloc/kfree functions
  - Memory caching
  - SLAB/SLUB allocator interface

- `<linux/vmalloc.h>`
  - Virtual memory allocation
  - Non-contiguous memory allocation
  - Large memory block handling

- `<linux/mm.h>`
  - Memory management subsystem
  - Page allocation
  - Memory zones
  - Memory policies

- `<linux/dma-mapping.h>`
  - DMA operations
  - DMA buffer management
  - DMA address mapping
  - Coherent DMA handling

- `<linux/mm_types.h>`
  - Memory management types
  - Page structs
  - Memory descriptors
  - VMA definitions

### Device Management
- `<linux/device.h>`
  - Device model
  - Device registration
  - Device attributes
  - Device classes

- `<linux/fs.h>`
  - File system operations
  - VFS interface
  - File operations
  - inode handling

- `<linux/cdev.h>`
  - Character device support
  - Character device registration
  - Device numbers

- `<linux/pci.h>`
  - PCI bus operations
  - PCI device handling
  - PCI configuration space
  - PCI driver model

- `<linux/usb.h>`
  - USB subsystem
  - USB device handling
  - USB protocols
  - USB driver interface

### Synchronization
- `<linux/mutex.h>`
  - Mutual exclusion
  - Sleeping locks
  - Basic synchronization

- `<linux/spinlock.h>`
  - Spin-based locking
  - Non-sleeping locks
  - IRQ-safe locking

- `<linux/rwlock.h>`
  - Read-write locks
  - Multiple reader support
  - Writer exclusion

- `<linux/semaphore.h>`
  - Counting semaphores
  - Resource management
  - Thread synchronization

- `<linux/completion.h>`
  - Completion waiting
  - Event signaling
  - Thread coordination

### Interrupt Handling
- `<linux/interrupt.h>`
  - Interrupt handling
  - IRQ management
  - Tasklets
  - Bottom-half processing

- `<linux/irq.h>`
  - IRQ chip abstraction
  - IRQ flow handling
  - IRQ configuration

- `<linux/irqdesc.h>`
  - IRQ descriptor handling
  - IRQ metadata
  - IRQ configuration data

### Time Management
- `<linux/time.h>`
  - Time operations
  - Timestamps
  - Time conversion

- `<linux/timer.h>`
  - Kernel timers
  - Timer management
  - Delayed execution

- `<linux/jiffies.h>`
  - System tick counter
  - Time conversion
  - Timing utilities

- `<linux/ktime.h>`
  - High-resolution time
  - Nanosecond timing
  - Time arithmetic

### Networking
- `<linux/netdevice.h>`
  - Network device handling
  - Network interface management
  - Protocol registration

- `<linux/skbuff.h>`
  - Socket buffer management
  - Network data handling
  - Packet manipulation

- `<linux/etherdevice.h>`
  - Ethernet device support
  - Ethernet protocols
  - MAC address handling

- `<linux/wireless.h>`
  - Wireless extensions
  - Wireless configuration
  - Wireless protocols

### Data Structures
- `<linux/list.h>`
  - Linked list implementation
  - List manipulation
  - List iteration

- `<linux/rbtree.h>`
  - Red-black tree implementation
  - Balanced tree operations
  - Tree traversal

- `<linux/hashtable.h>`
  - Hash table implementation
  - Hash functions
  - Hash table operations

- `<linux/radix-tree.h>`
  - Radix tree implementation
  - Sparse array handling
  - ID management

### Debug and Trace
- `<linux/debug.h>`
  - Debugging facilities
  - Debug macros
  - Assertion support

- `<linux/trace_events.h>`
  - Event tracing
  - Performance monitoring
  - Debug tracing

- `<linux/kallsyms.h>`
  - Kernel symbol lookup
  - Symbol resolution
  - Address translation

### Power Management
- `<linux/pm.h>`
  - Power management
  - System sleep states
  - Device power states

- `<linux/cpufreq.h>`
  - CPU frequency scaling
  - Frequency governors
  - Power policies

- `<linux/suspend.h>`
  - System suspend
  - Hibernation
  - Resume handling

### Platform and Architecture
- `<linux/platform_device.h>`
  - Platform device support
  - Platform driver model
  - Resource management

- `<linux/gpio.h>`
  - GPIO handling
  - Pin control
  - GPIO interrupts

- `<linux/i2c.h>`
  - I2C bus support
  - I2C device handling
  - I2C protocols

- `<linux/spi/spi.h>`
  - SPI bus support
  - SPI device handling
  - SPI protocols

### Resource Management
- `<linux/resource.h>`
  - Resource allocation
  - Memory regions
  - IO ports

- `<linux/idr.h>`
  - ID allocation
  - Resource numbering
  - ID management

- `<linux/kref.h>`
  - Reference counting
  - Object lifecycle
  - Memory management

### Input/Output
- `<linux/uaccess.h>`
  - User space access
  - Copy to/from user
  - Access checking

- `<linux/io.h>`
  - I/O memory mapping
  - Port I/O
  - Memory barriers

- `<linux/ioctl.h>`
  - I/O control commands
  - Device control
  - User interface

### Security
- `<linux/security.h>`
  - Security framework
  - LSM hooks
  - Access control

- `<linux/cred.h>`
  - Credential management
  - Process credentials
  - Security context

- `<linux/capability.h>`
  - Capability system
  - Process capabilities
  - Security checks

### File System Specific
- `<linux/proc_fs.h>`
  - procfs interface
  - Process information
  - System statistics

- `<linux/sysfs.h>`
  - sysfs interface
  - Device attributes
  - Kernel objects

- `<linux/debugfs.h>`
  - Debug filesystem
  - Runtime debugging
  - Debug interfaces

### Miscellaneous
- `<linux/random.h>`
  - Random number generation
  - Entropy gathering
  - Cryptographic operations

- `<linux/sched.h>`
  - Process scheduling
  - Task management
  - Scheduling classes

- `<linux/wait.h>`
  - Wait queues
  - Sleep/wake mechanisms
  - Event waiting

## Usage Notes

1. Include Order
- System headers first
- Subsystem-specific headers
- Local headers last

2. Dependencies
- Check for header dependencies
- Use include guards
- Minimize header inclusion

3. Feature Testing
```c
#ifdef CONFIG_SOMETHING
    /* Feature-specific code */
#endif
```

4. Architecture Specifics
```c
#ifdef CONFIG_X86
    /* x86-specific code */
#endif
```

5. Version Checking
```c
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,0,0)
    /* Version-specific code */
#endif
```

