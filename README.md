# Linux-Process-Visualiser
This Linux kernel module demonstrates the creation of multiple child kernel threads from a parent context (the module's init function). It simulates a basic process tree structure using kernel threads and logs their process information via printk.
Features
Initializes a kernel module as the root of a process tree.

Dynamically allocates memory for thread IDs.

Spawns 3 child kernel threads.

Logs PID and memory information for each thread.

Frees allocated memory after use.

