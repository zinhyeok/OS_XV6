#include "types.h"
#include "stat.h"
#include "user.h"

#define MAX_INPUT_SIZE 256
#define MAX_ARG_SIZE 10

int main() {
  
  while (1) {
    printf(1, "Enter a command: ");
    char command[MAX_INPUT_SIZE];
    char *token = command;  // Initialize token inside the while loop
    //read user input for command line

    memset(command, 0, sizeof(command));
    gets(command, sizeof(command));

    // Split the command into arguments
    int argCount = 0;
    char *args[MAX_ARG_SIZE]; // Assuming a maximum of 10 arguments
    memset(args, 0, sizeof(args));

    //split the command into arguments
    for (int i = 0; i < sizeof(command) && argCount < MAX_ARG_SIZE; i++) {
      if (command[i] == ' ' || command[i] == '\0' || command[i] == 10) {
        command[i] = '\0';
        args[argCount++] = token;
        token = &command[i + 1];
      }
    }

    // Check if the command is "exit"
    if (strcmp(args[0], "exit") == 0) {
      printf(1, "Shutting down... pmanager\n");
      break;
    }

    // Process other commands with arguments

    // Check if the command is "list"
    //list command print information about running processes
    //information include pid, number of stackpage, memory size, memory limit
    //include thread information
    //thread does not print
    if (strcmp(args[0], "list") == 0) {
      printf(1, "list working\n");
    }

    // Check if the command is "kill"
    //kill command kill a process with a given pid
    //if the process is a thread, kill all threads in the same process
    if (strcmp(args[0], "kill") == 0) {
      int pid = *args[1] - '0';
      kill(pid);
    }

    // Check if the command is "execute"
    //execute command execute a given program in given path
    //if the program is already running, print error message
    if (strcmp(args[0], "execute") == 0) {
      char *path = args[1];
      int stacksize = *args[2] - '0';
      exec2(path, (char**)&path, stacksize);
    }

    // Check if the command is "memlim"
    //limit the memory size of a process with a given pid
    //process memoty should consider thread memory
    if (strcmp(args[0], "memlim") == 0) {
      int pid = *args[1] - '0';
      int limit = *args[2] - '0';
      setmemorylimit(pid, limit);
    }
  }
  return 0;
}