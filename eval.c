#include "eval.h"
#include "common.h"
#include "history.h"
#include "builtin.h"

//Evaluates the command line
void eval(char *cmdline){
 char *argv[MAXARGS]; //list of arguments
 char buf[MAXLINE]; //holds modified command line
 int bg;  //bg == 1 if job should be run in the background, otherwise foreground
 pid_t pid; //Process id

 strcpy(buf,cmdline);
 
 add_command_to_history(buf); //Records command in history

 bg = parseline(buf, argv);

 if(argv[0]== NULL)
   return;            //Ignore empty lines

 if(!builtin_command(argv)){
     execute_cmd(argv, bg);
 } 
 return;
}

//Executes the command
void execute_cmd(char **argv, int bg){
 pid_t pid;
 if((pid = Fork()) == 0 ){  //Child job
      if(execvp(argv[0],argv) < 0){ //execute command
         printf("%s : Command not found.\n",argv[0]);
         exit(0);
      } 
    
   }
   else{
     //Parent waits for foreground jobs to terminate
    if(!bg){
     int status;
     if(waitpid(pid,&status,0)<0)
        unix_error("wait foreground: wait pid error");
    }  
     else
      printf("%d %s\n", pid, argv[0]);  
   } 

}



//Parses the command line and builds the argv array
int parseline(char *buf, char **argv){
 char *delim;    //Pointer to the first spcae delimiter
 char argc;      //# of args
 int bg;         //background job?

 buf[strlen(buf)] = ' '; //replace trailing '\n' with a space
 while (*buf && (*buf == ' ')) //Ignore leading spaces
   buf++;
 
 //Build the list of arguments, argv
 argc = 0;
 while ((delim = strchr(buf,' '))){
   argv[argc++] = buf;
   *delim = '\0';
   buf = delim + 1;
   while (*buf && (*buf == ' ')) //Ignore spaces
    buf++;

 }

 argv[argc] = NULL;
 
 if(argc == 0) //ignore blank lines
   return 1;

 //Should the job run in the background
 if((bg = (*argv[argc-1] == '&')) != 0)
   argv[--argc] = NULL;

 return bg;
}
