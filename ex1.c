/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void ex1(){
    pid_t pid;
    
    pid = fork(); // Fork a child process
    
    if (pid < 0){ // Error
        fprintf(stderr, "Fork failed"); 
        // Print error to file, stderr: standard error stream
        return 1;
    }
    else if (pid == 0){ // Child process
        printf("pid: %d\n", getpid());
        printf("ppid: %d\n", getppid()); // getppid() returns parent process id
        execlp("/bin/ls", "ls", "-a", NULL);
        
        /* Arguments:
         * 
         * file
         * Used to construct a pathname that identifies the new process image file.
         * 
         * arg0, …, argn, NULL 
         * You must terminate the list with a NULL pointer. The arg0 
         * argument must point to a filename that's associated with the process 
         * being started and cannot be NULL.
         */ 
    }
    else { // Parent process
        printf("Parentpid: %d\n", getpid());
        wait(NULL); // Parent will wait for the child to complete
        printf("Child complete!");
    }
}