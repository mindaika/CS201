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
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int 	fd[2];
    pid_t 	childpid;
    
    // set up pipe
    pipe(fd);

    // call fork()
    childpid = fork();

    if ( childpid == 0 ) {
            // -- running in child process --


            // Receive characters from parent process via pipe
            // one at a time, and count them.
            // Return number of characters counted to parent process.
        int     nChars = 0; // Counter for characters
        char    buffer;     // Character buffer
        
        // Close unused end of pipe
            close(fd[1]);

        // Read characters one at a time from pipe
        while ( read(fd[0], &buffer, 1) > 0 )
            nChars++; // Increment count per character read

        // Close current end of pipe
        close(fd[0]);
        exit(nChars);
    } else {
        // -- running in parent process --
        
        int 	nChars = 0; // To store exit code form child process
        int 	status;     // Honestly, I'm not 100% clear on how this works
        int     i;          // Loop variable for argument number
        int     j;          // Loop varuabel for character number
        printf("CS201 - Assignment 3 - Randall Sewell\n");
        
        // Send characters from command line arguments starting with
        // argv[1] one at a time through pipe to child process.
        // Wait for child process to return. Reap child process.
        // Receive number of characters counted via the value
        // returned when the child process is reaped.

        // Close unused end of pipe
        close(fd[0]);
        
        // Write characters to pipe one at a time
        for (i = 1; i < argc; i++ ) {
            for (j = 0; j < strlen(argv[i]); j++) {
                write(fd[1], &argv[i][j], 1);
            }
        }

        // Close used end of pipe
        close(fd[1]);

        // Wait for child to terminate and reap with exit status equal to number of characters counted
        while ((childpid = waitpid(-1, &status, 0)) > 0 ) {
            if ( WIFEXITED(status) )
                nChars = WEXITSTATUS(status);
            else
                printf("Abnormal termination of child %d", childpid);
        }
        // Output characters counted
        // Interesting, but not surprising, behavior: some characters aren't counted unless escaped
        // e.g. "./a03" ### returns 0, but "./a03 \#" returns 1
        printf("child counted %d chars\n", nChars);
        return 0;
    }
}
