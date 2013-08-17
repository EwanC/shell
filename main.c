#include "eval.h"
#include "common.h"

int main(){
  char cmdline[MAXARGS]; //command line
  size_t path_size = sizeof(char) * 1024;
  char *path;
  path = (char *)malloc(path_size);
  
  //Set up handler for finishes child processes
  if(signal(SIGCHLD,sig_handler) == SIG_ERR)
     unix_error("signal handler init error");
  


  while(1){
  printf("%s> ",get_path(path,path_size));
  fgets(cmdline, MAXLINE, stdin); //read command line
  
  if(feof(stdin)) //ends child processes
    exit(0);

  eval(cmdline);  //Evalutate command
 }
}
