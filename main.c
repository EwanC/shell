#include "eval.h"
#include "common.h"

int main(){
  char cmdline[MAXARGS]; //command line input
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
     printf("%s> ",get_path(path,path_size));
     fgets(cmdline, MAXLINE, stdin); //read command line
  
     if(feof(stdin)) //ends child processes
        exit(0);

     eval(cmdline);  //evalutated command
  }
}
