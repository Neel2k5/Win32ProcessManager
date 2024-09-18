#ifndef FEATS_H
#define FEATS_H


/*List Processes
 * This function Lists all the processes running at that instant on the machine with the following attributes:
 * Process ID
 * Base Priority
 * Executable Name
 * Threads
 * Parent ID
 *
 * The argument limit can be set to a nonzero positive integer to fetch that many processes,
 * or it can be set to a negative integer to list all processes.
 * */
void feats_lp(int limit);



#endif
