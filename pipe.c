//Checks for and handles piped commands
#include "pipe.h"
#include "common.h"


//Handles piped commands
int check_pipe(char **argv){
  int pipe_index = pipe_at(argv);
  
  if(pipe_index == -1)   //More than one pipe present
  	return 1;
  if (pipe_index == 0)  //Not a pipe command
  {
  	return 0;
  }
  
  argv[pipe_index] = NULL;  //replace pipe symbol with Null
                            //as a delimiter between the two commands
  int filedes[2], status;
  if(pipe(filedes)){        
  	unix_error("pipe error");
  }

  pid_t pid;
  if((pid = Fork()) == 0 ){  
      dup2(filedes[1],1);   //Direction output to pipe
      if(execvp(argv[0],argv) < 0){ //execute first command
         printf("%s : Command not found.\n",argv[0]);
         exit(0);
      } 
       
    
   } else{
      close(filedes[1]);  //parent closes output
   } 


   while(*argv != NULL)   //point to start of second command
   	 *argv++;
   *argv++;
 
   if(pid = Fork() ==0){
     dup2(filedes[0],0); //get input from pipe
     if(execvp(argv[0],argv) < 0){ //execute second command
         printf("%s : Command not found.\n",argv[0]);
         exit(0);
      } 
      
   }
   else{
      close(filedes[0]);  //close input
   }

    if(waitpid(pid,&status,0)<0) 
        unix_error("wait foreground: wait pid error");
     
   return 1;
}

//Seachs for pipe symbol '/' and returns it location if found
//If no symbol is found 0 is returned
//There is an error is more than one symbol is found and -1 is returned
int pipe_at(char **argv){
   int n =0;
   int found = 0;
   while(*argv != NULL){
    if(!strcmp(*argv,"|")){
      if((*(argv+1) != NULL)&&(*(argv-1) != NULL)) //token must be have a argument before and after
        if(found > 0){
        	printf("Only one pipe per command is supported\n");
            return -1;
        }
        else
          found = n;
    }
    n++;
    *argv++;
   }
   return found;
}
