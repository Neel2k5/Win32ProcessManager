
/**
 *  Copyright 2024 Swapnaneel Dutta

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   limitations under the License.

 */


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
 * @limit is to be taken from input signifying the number of process to be displayed. (-1 to display all)
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

/*tree
 * Displays the snapshotted processes running in the system and their respective accisable children in a tree like format
 * @depth is to be initialised to 0 
 * @limit is to be taken from input signifying the number of process to be displayed. (-1 to display all)
 * */

void feats_tree(unsigned int depth,int limit);
#endif
