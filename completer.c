#include "common.h"
#include "completer.h"
#include "dirent.h"

static char** shell_completion(const char*, int, int);
char* command_generator(const char*, int);

static char *commands[2500]; //holds list of possible commands

//intialise completion
void init_readline(){
 //Allow confitional parsing of the ~/.inputrc file. */
 rl_readline_name = "Shell";
 
 get_command_list(); //populates the list of possible commands

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

void get_command_list(){
  char** path;
  DIR *dir;
  char *temp = (char *)Malloc(100 * sizeof(char));
  struct dirent *ent;
  struct stat filestat;
  int n =0;
  path = split_path(); //gets list of directorys conataing commands

  while(**path){
    if((dir = opendir(*path))==NULL){
      printf("%s\n",*path );
      unix_error("ERROR Opening dir");
    }
    else{
      while((ent = readdir(dir)) != NULL){
          if((ent->d_type == DT_REG)){
            strcpy(temp,*path);
            strcat(temp,"/");
            if(stat(strcat(temp,ent->d_name),&filestat)==0 && (filestat.st_mode & S_IXUSR)){
                //if commands is execeutable, adds it to list
                commands[n++]= ent->d_name;
            }
          }
       }
       closedir(dir);
    }
    *path++;
  }
  free(temp);
  commands[n++] = "\0";
}


char **split_path(){
  char* pPath;
  static char *dirs[MAX_PATHS];
  pPath = dupstr(getenv ("PATH")); //finds enivoronmental variable $PATH
  if (pPath==NULL){
    printf ("Could not get Path variable");
    return;
  }
  int n=0;
  char* result;
  result = strtok((pPath),":"); 
  dirs[n] = result; 

 //splits path into it's component directorys
  while(result!=NULL){
    n++;
    result = strtok(NULL,":");
    if(result !=NULL)
      dirs[n] = result; 
    else
      dirs[n] = "\0";
  }

return dirs;
} 
