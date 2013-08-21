#include "eval.h"
#include "common.h"
#include <readline/readline.h>
#include <readline/history.h>


int main(){
  static char *cmdline = (char *)NULL;
  size_t path_size = sizeof(char) * 1024;
  char *path;
  path = (char *)malloc(path_size);

  //Set up signal handler for finished child processes
  if(signal(SIGCHLD,sig_handler) == SIG_ERR)
     unix_error("SIGCHLD handler init error");
   
  //Set up signal handler for keyboard interrupts
  if(signal(SIGINT,int_handler) == SIG_ERR)
     unix_error("SIGINT handler init error");

  while(1){
     cmdline = readline(get_path(path,path_size));
     
     if(cmdline && *cmdline)
       add_history(cmdline);

     if(feof(stdin)) //ends child processes
        exit(0);


     eval(cmdline);  //evalutated command

      if(cmdline){
       free(cmdline);
       cmdline = (char *)NULL;
    }

  }
}
