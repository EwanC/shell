#include "common.h"
#include "completer.h"

static char** shell_completion(const char*, int, int);
char* command_generator(const char*, int);

//list of builtin commands
char *commands[] = {
   "history",
    "help",
    "quit",
    "exit",
    "setenv",
    (char *)NULL
};

//intialise completion
void init_readline(){
 //Allow confitional parsing of the ~/.inputrc file. */
 rl_readline_name = "Shell";
 
 //tell the completer that we want a crack first
 rl_attempted_completion_function = shell_completion;


}

//calls generator and returns list of matches
static char** shell_completion(const char* text,int start,int end){
 char **matches;
 matches = (char **)NULL;

 if(start==0)
   matches = rl_completion_matches((char*)text, &command_generator);
 else
  rl_bind_key('\t',rl_abort);

 return matches;
}

//Generates list of portential matches
char* command_generator(const char *text, int state){
  static int list_index,len;
  char *name;

  if(!state){
  	list_index =0;
  	len = strlen(text);
  }

  //searches for matches
  while(name = commands[list_index]){
  	list_index++;

  	if(!strncmp(name,text,len))
      return dupstr(name);
  }

  //If no matches
  return ((char *)NULL);

}

//duplicates a string
char *dupstr (char *s) {
  char *r;
 
  r = (char*) Malloc ((strlen (s) + 1));
  strcpy (r, s);
  return (r);
}
 
