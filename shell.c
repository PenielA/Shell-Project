#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char **environ;

int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];

    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
    
    while (true) {
        // Print the shell prompt.
        printf("%s", prompt);
        fflush(stdout);
        
        // Read input from stdin and store it in command_line. If there's an
        // error, exit immediately. (If you want to learn more about this line,
        // you can Google "man fgets")
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }
        
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }
      
      // Get the executable name. 
      char* exec_name = strtok(command_line, delimiters);
      
      // Parse the arguments into the arguments array. 
      int i = 0;
      char* temp;
      while (temp = strtok(NULL, delimiters)){
        arguments[i] = temp;
        i++;
      }
      
      // Terminate the arguments array with a null pointer. 
      arguments[i] = (char*)0;
      
      if (fork() == 0){
        // Child process. 
        if (execve(exec_name, arguments, environ) == -1){
          perror(strerror(errno));
        }
      }
      else{
        // Parent process. 
        wait(NULL);
      }

        // TODO:
        // 1. Tokenize the command line input (split it on whitespace)
        // 2. Create a child process which will execute the command line input
        // 3. The parent process should wait for the child to complete
        // 
        // Hints (put these into Google):
        // man fork
        // man execve
        // man wait
        // man strtok
    }
    
    // This should never be reached.
    return -1;
}
