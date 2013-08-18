#include "eval.h"
#include "common.h"
#include "history.h"

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
   if((pid = Fork()) == 0 ){  //Child job

    //Set up handler for keyboard interrupts
  if(signal(SIGINT,int_handler) == SIG_ERR)
     unix_error("SIGINT handler init error");

      if(execvp(argv[0],argv) < 0){
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
 return;
}

//If first arg is a built in command run it and return true
int builtin_command(char **argv){
 int n;
 char *buf;
 if(!strcmp(argv[0],"quit") || !(strcmp(argv[0],":q")))  //Quit command
    exit(0);
 if(!strcmp(argv[0], "&"))    //Ignore singleton '&'
    return 1;
 if(!strcmp(argv[0], "history")){    //prints command history
    print_history();
    return 1;
  }
  if((n=is_prev_command(argv[0])) > 0){
       buf = get_prev_cmd(n);
       if(buf == NULL)
         printf("No command record at %d\n",n);
       else
         eval(buf);
       return 1;    
  }
 
 return 0;      //Not builtin command
}

//Parses the command line and builds the argv array
int parseline(char *buf, char **argv){
 char *delim;    //Pointer to the first spcae delimiter
 char argc;      //# of args
 int bg;         //background job?

 buf[strlen(buf)-1] = ' '; //replace trailing '\n' with a space
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
