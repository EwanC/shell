#include "common.h"

//Unix style error
void unix_error(char *msg){
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(0);
}

//Error handling wrapper for fork()
pid_t Fork(void){
   pid_t pid;
   if((pid = fork()) < 0)
   	unix_error("Fork error");
   return pid;
}


//Gets the current directory from $Path
char *get_path(char *path, size_t size){
  if(getcwd(path,size) == NULL)
      unix_error("Error getting working directory");
  
  return path;
}

//Catches SIG_CHILD signal and reaps child
void sig_handler(int sig){
	pid_t pid;
	while ((pid = waitpid(-1,NULL,WNOHANG)) > 0)
              ;
    if(errno != ECHILD)
    	unix_error("Error reaping child");
    return;
}

//Catches keyboard interrupt to keep parent shell process from exiting
void int_handler(int sig){
    printf("\n");
    return;
}
