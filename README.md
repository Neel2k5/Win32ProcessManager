# Win32 Process Manager
### A multipurpose process managing CLI tool for windows.

___

## Features 
This CLI tool written in C that uses ihe Win32 API to display the processes in the system and perform a few other basic operations
It provides the following features:

- **List Processes**

    A colour coded version of the 'tasklist' command with a few limited attributes
    *Limitations:*  
    (Certain processes that are protected or require higher perms may not be displayed)


- **Process Display**

    Displays important info of processes by their psid. the info includes the origin path and ram usage  
    *Limitations:*  
    (Certain processes that are protected or require higher perms may not be displayed)



- **Kill process**

    Simple wrapper for the system call to terminate an accesisable process by its psid.
    *Limitations*
    (Certain processes that are protected or require higher perms may not be terminated)

- **Process Tree**

    Stores the processes from a snapshot and displays them in a tree format.
    *Limitations*
    (Certain processes that are protected or require higher perms may not be displayed and the tree may have branches missing)


---

## Installation

## Using without modification

Ensure you have the following installed on your system:

- [Git](https://git-scm.com/downloads) (for cloning the repository)
- Windows Operating System (The exe was tested on Windows 10)

### Cloning the Repository

1. Open your terminal or command prompt.

2. Navigate to the directory where you want to clone the project.

3. Run the following command to clone the repository:

    ```bash
    git clone https://github.com/Neel2k5/Win32ProcessMannager.git
    ```

4. Navigate into the project's executable directory:

    ```bash
    cd repository\executable
    ```
5. This directory contains the executable file 'wpm.exe' along with the user guide 'ug\_wpm.txt'.
   These two files must be kept in the same directory for effective usage.
   You may set your enviornment variable path to this directory or copy these two files in some other directory and use the respective path.

6. Open Command Prompt and run the following commands to get started:
    ```bash
    wpm help
    ```
    
    ```bash
    wpm
    ```
## For Modification and usage

Additional Requirement:
- [MinGW](https://sourceforge.net/projects/mingw/)(Or any other c compiler set up on your machine)
- psapi.h header file. (Can be linked from your device's own Kit directory or can be separately downloaded)
After Following upto step 4 above, you now have acess to the source files. Here is how they are structured:
- **inp_prsr.c** : Contains the main for taking and processing cli inputs and calling respective header functions.
- **feats.c** : Contains the core features of the tool, functions are prototyped in *feats.h*
- **helper.c** : Contains the genral functions that are used by the core feature functions of the tool, functions are prototyped in *helper.h*

After making necessary changes to source, compile the three files:
```bash
gcc inp_prsr.c feats.c helper.c -o wpm -lpsapi
```

NOTE: The 'wpm help' command will not execute if the "ug\_wpm.txt" is not present with it in the same directory. Also to display newly made features in user guide, the text file must be edited.

NOTE: The psapi.h file needs to be linked if you have it in your system.

## Contributions
Sorry we do not support contributions yet!! 
**COMING SOON**

## License

This project is licensed under the [Apache License 2.0](LICENSE.md).
