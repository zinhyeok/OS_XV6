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

    //print all arguments
    // Check args (for testing purposes)
    // for (int i = 0; i < MAX_ARG_SIZE; i++) {
    //   printf(1, "%dth is: %s\n", i, args[i]);
    // }

    // Check if the command is "exit"
    if (strcmp(args[0], "exit") == 0) {
      printf(1, "Shutting down... pmanager\n");
      exit();
      break;
    }

    // Process other commands with arguments

    // Check if the command is "list"
    //list command print information about running processes
    //information include pid, number of stackpage, memory size, memory limit
    //include thread information
    //thread does not print
    if (strcmp(args[0], "list") == 0) {
      list();
    }

    // Check if the command is "kill"
    //kill command kill a process with a given pid
    //if the process is a thread, kill all threads in the same process
    //if kill is successful, print "kill completed"
    //if pmanager is killed, kill completed does not print
    if (strcmp(args[0], "kill") == 0) {
      int pid = atoi(args[1]);
      if(kill(pid)==0)
        printf(1, "kill %d completed \n", pid);
    }

    // Check if the command is "execute"
    //execute command execute a given program in given path
    //if the program is already running, print error message
    //if execute is failed, print error message
    if (strcmp(args[0], "execute") == 0) {
      printf(1,"executing\n");
      char *path = args[1];
      char* argv[] = {path, 0};
      int stacksize = atoi(args[2]);

      int pid = fork();
      if (pid < 0) {
      // Forking failed
      printf(1, "Error: Forking failed\n");
      }else if (pid == 0){
      if(exec2(path, argv, stacksize) == -1){
        printf(1, "execute failed \n");
      }
      }

      // if(exec2(path, (char**)&path, stacksize)== -1)
      //   printf(1, "execute failed \n");
    }

    // Check if the command is "memlim"
    //limit the memory size of a process with a given pid
    //process memoty should consider thread memory
    // if setmemorylimit is successful, print "set memory limit completed"
    if (strcmp(args[0], "memlim") == 0) {
      int pid = atoi(args[1]);
      int limit = atoi(args[2]);
      if(setmemorylimit(pid, limit)==0)
        printf(1, "set memory limt of porcess pid: %d to limit %d \n", pid, limit);
    }
  }
  return 0;
}