#include "eval.h"
#include "common.h"
#include "completer.h"


int main(){
  static char *cmdline = (char *)NULL;   //Holds command line input
  size_t path_size = sizeof(char) * 1024; //Max length of path
  char *path;  
  path = (char *)malloc(path_size);  //Holds the path of the current working directory

  //Set up signal handler for finished child processes
  if(signal(SIGCHLD,sig_handler) == SIG_ERR)
     unix_error("SIGCHLD handler init error");
   
  //Set up signal handler for keyboard interrupts
  if(signal(SIGINT,int_handler) == SIG_ERR)
     unix_error("SIGINT handler init error");

  init_readline(); //bind our completion handler

  //Main infinte loop
  while(1){
     cmdline = readline(get_path(path,path_size)); //reads user input

     if(cmdline && *cmdline)
       add_history(cmdline);          //adds input to history

     if(feof(stdin)) //ends child processes 
        exit(0);


     eval(cmdline);  //evalutated input

      if(cmdline){         //Prepares for next command
       free(cmdline);
       cmdline = (char *)NULL;
    }

  }
}
