// Characters from command line arguments are sent to child process
// from parent process one at a time through pipe.
//
// Child process counts number of characters sent through pipe.
//
// Child process returns number of characters counted to parent process.
//
// Parent process prints number of characters counted by child process.

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int 	fd[2];
    pid_t 	childpid;
    char 	readbuffer[80] = { 0 };
    
    // set up pipe
    pipe(fd);

    // call fork()
    childpid = fork();

    if ( childpid == 0 ) {
        // -- running in child process --


        // Receive characters from parent process via pipe
        // one at a time, and count them.
        // Return number of characters counted to parent process.
        int     nChars = 0;
        close(fd[1]);
        nChars = read(fd[0], readbuffer, sizeof(readbuffer));

        exit(nChars);
    } else {
        // -- running in parent process --
        
        int 	nChars = 0;
        int 	status;
        printf("CS201 - Assignment 3 - Randall Sewell\n");
        
        // Send characters from command line arguments starting with
        // argv[1] one at a time through pipe to child process.
        // Wait for child process to return. Reap child process.
        // Receive number of characters counted via the value
        // returned when the child process is reaped.
        close(fd[0]);
        write(fd[1], argv[1], (strlen(argv[1])));
        
        while ((childpid = waitpid(-1, &status, 0)) > 0 ) {
            if ( WIFEXITED(status) )
                nChars = WEXITSTATUS(status);
            else
                printf("Abnormal termination of child %d", childpid);
        }
        
        printf("child counted %d chars\n", nChars);
        return 0;
    }
}
