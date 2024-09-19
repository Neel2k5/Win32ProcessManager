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
/*Process Description
 * This function takes the process id as a mandetory argment and displays the following details about the process:
 * Process ID
 * Process Name
 * Process Origin Path
 * RAM usage
 *
 * This may throw error if some protected process is encountered or the tool lacks permissions to acess the certain process.
 * */
void feats_psd(unsigned int pID);
/*kill
 * This function takes a process ID as unsigned integer input and terminates it.
 * The executable must have acess permissions of that specific process, or displays respective error.
 * */
void feats_kill(unsigned int pID);
#endif
