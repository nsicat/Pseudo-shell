# Project 1: Pseudo-shell

## Overview:

This project is a pseudo-shell implemented in C, designed to handle basic shell commands with two operational modes, Interactive Mode, and File Mode. The pseudo-shell recognizes commands such as ls, pwd, cd, cp, mv, and cat. In this shell, the user also has the capabilities to apply multiple commands in one line seperated by semicolons(;)

In interactive mode, the shell accepts users commands through the terminal and executes as soon as the user hits enter. In the other hand, file mode, the shell reads commands from a specified input file, executes them from left to right, starting from top to bottom. 

### How to run this program: Two modes

#### Interactive mode: 

1. Go to the same folder as these files
2. Open up the terminal, and make sure you are in the right directory
3. Type "make" into the terminal. This should compile the code
4. type "./pseudo-shell" into the command line, and this should trigger interactive mode


#### File mode:
1. Follow steps 1 - 3 from Interactive mode.
2. Type "./pseudo-shell <arg1>" with arg1 being the file containing the commands.
3. After execution, there should be a file called "output.txt" with your output.


### Supported Commands
The shell supports the following commands:
    * ls: list all directory
    * pwd: prints current working directory
    * cd: change directory
    * cp: copy files
    * mv: move or rename files
    * cat: print content of file in terminal
    * exit: exit shell

The shell also supports multiple commands in one line, and can still execute them

### List of allowed system calls used in porgram:
    * Readdir
    * Getcwd
    * Write
    * Closedir
    * Stat
    * Mkdir
    * Chdir
    * Opendir
    * Basename
    * Open
    * Read
    * Remove
    * Getopt


    