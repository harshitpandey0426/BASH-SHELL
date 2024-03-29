# About
Developed a working POSIX compatible shell with a subset of feature support of your default shell. Apart from basic working, required features to be implemented are listed below.

# This shell supports following features:
* Multiprocess approach using fork syscall.
* Pipes for execution chaining and I/O redirection.
* Environment variables and export.
* Understanding of “.bashrc” and “.profile”.
* Following functions will be of help - fork, exec, execvp, wait, waitpid, kill, dup, pipe, strncmp
   malloc, free, getcwd,chdir , open, close, readline, gets, fgets, getchar, signal
* Files permissions and ownership in *nix or derived systems.
* Prompt and it’s meaning for each field, E.g. user@ubuntu:~$

# Syntax to be used for this shell:
* IO redirection with ‘>>’ and ‘>’ will be done for one source and one destination only.

* For ‘|’, a minimum 3 programs must be in pipe. E.g. cat file1.txt| sort | uniq > save.txt.

* Prompt must change for distinguishing users($) @hostname and root(#)@hostname and also while searching in extended features.

* Support for Aliasing is provided.

* History command is added.

* Shell.c contains execution of code.

* Function.h contains some important functions like redirection, environment setup etc.

# To Run shell:
> Run shell.c
