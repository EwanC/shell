#include "common.h"
#include "eval.h"
#include "history.h"
#include "builtin.h"
#include "pipe.h"

//If first arg is a built in command run it and return true
int builtin_command(char **argv){
 
 if(!strcmp(argv[0],"quit") || !(strcmp(argv[0],":q"))|| !(strcmp(argv[0],"exit")))  //Quit command
    exit(0);
 if(!strcmp(argv[0], "&"))    //Ignore singleton '&'
    return 1;
 if(!strcmp(argv[0], "help")){    //print help info
    print_help();
    return 1;
 }
 if(!strcmp(argv[0], "history")){    //prints command history
    if(argv[1] && !(strcmp(argv[1],"--help")))
       printf("prints history of recent commands\nPrevious commands can be repeated using !follwed by the command index\nNo arguments are available\n");
    else
       print_history();
    return 1;
  }
  if(!strcmp(argv[0],"cd")){   //Change directory
      if(argv[1] && !(strcmp(argv[1],"--help")))
        printf("cd [path] - changes the current working directory\nLeave path blank to go to home directory\n");
      else
        change_dir(argv);
     return 1;
  }
  if(prev_cmd(argv) == 1)    //user want to repeat previous command
    return 1;

  if(IO_redirect(argv)==1)  //user wants to redirect IO
     return 1;

  if(check_pipe(argv) ==1) //user command cointains pipe
    return 1;

 return 0;      //Not builtin command
}

//Handles requests for commands at previous timesteps
int prev_cmd(char **argv){
  int n;
  char *buf;
 
  if((n=parse_prev_command(argv[0])) > 0){ //repeat prevoious command
       buf = get_prev_cmd(n);
       if(buf == NULL)
         printf("No command record at %d\n",n);
       else
         eval(buf);
       return 1;    
  }
  return 0;
}

//Hanldes IO redirection
int IO_redirect(char **argv){
   int fdout, fdin,defin,defout;
   int in,out;

   in =stdin_redirect(argv);  //finds pos of stdin redirect symbol
   out =stdout_redirect(argv); //finds pos of stdout redirect symbol
   
   fflush(0);

   //Case where there is both stdin and stdout redirection
   if(in > 0 && out > 0){
     if(in > out)  //stdout must precede stdin
       printf("Only simple IO redirection is supported\n");
     else{
        defin = dup(0);
        defout = dup(1);
        fdin = open(argv[in+1],O_RDONLY); //open input file
        fdout = creat(argv[out+1],0644); //file to write stdout to
        dup2(fdin,0);  //redirect input to the file
        dup2(fdout,1); //redirect output to the file
        argv[in] = NULL;  //execute command before redirect symbol
        execute_cmd(argv,0);
        dup2(defin,0);  //redirect input back to stdin
        dup2(defout,1); //redirect output back to stdout
        close(fdin);
        close(fdout);
        close(defin);
        close(defout);
     }
    return 1;
   }
   //case where there is only stdin redirection
   else if (in > 0){
      defin = dup(0);
      fdin = open(argv[in+1],O_RDONLY);
      dup2(fdin,0);
      argv[in] = NULL;
      execute_cmd(argv,0);
      dup2(defin,0);
      close(fdin);
      close(defin);
      return 1;
   }  
   //case where there is onlt stdout redirection
   else if(out > 0){
      defout = dup(1);
      fdout = creat(argv[out+1],0644);
      dup2(fdout,1); 
      argv[out] = NULL;
      execute_cmd(argv,0);
      dup2(defout,1); 
      close(fdout);
      close(defout);
      return 1;
   }
   return 0;

}

//returns position of stdin redirect token '<' or 0 if not present
int stdin_redirect(char **argv){
   int n =0;
   while(*argv != NULL){
    if(!strcmp(*argv,"<")){
      if((*(argv+1) != NULL)&&(*(argv-1) != NULL)) //token must be have a argument before and after
       return n;
    }
    n++;
    *argv++;
   }
  return 0;
}

//returns position of stdout redirect token '>' or 0 if not present
int stdout_redirect(char **argv){
 int n =0;
 while(*argv != NULL){
    if(!strcmp(*argv,">")){
      if((*(argv+1) != NULL)&&(*(argv-1) != NULL)) //token must be have a argument before and after
       return n;
    }
    n++;
   *argv++;
   }
  return 0;
}

//Changes directory
//If no directoy or '.' is specified go to home dir
void change_dir(char **argv){
   if(argv[1] && strcmp(argv[1],".")){
    if(chdir(argv[1]) < 0)
       printf("Could not find directory\n");
  }
  else{
      char *home = malloc(50 * sizeof(char));
      home = getenv("HOME");
      if(chdir(home) < 0)
       printf("Could not find directory\n");
  }
}

//Prints help info
void print_help(){
  printf("UNXI Shell 1.0 - developed by Ewan Crawford\n\n");
  printf("Builtin Commands\n");
  printf("------------------------\n");
  printf("cd [path] [--help] - Changes the current working directory\n");
  printf("[command] & - This creates a background process with specifies pid. All processes can be seen with command 'ps'\n");
  printf("history [--help] - Displays a list of previous recent commands\n");
  printf("![n] - Repeates the command at index n from command history\n");
  printf("[command] > [file] - The '>' symbol redirects the output of a command to a specified file\n");
  printf("[command] < [file] - The '<' symbol takes the input of a command from a specified file\n");
  printf("[command] | [command] - '|' uses the output of the first command as the output of the second, called piping. e.g. ls | grep .txt'\n");
  printf("\nTo quit the shell use ':q','quit' or 'exit'. NOTE:This will not end background processes\n");

}