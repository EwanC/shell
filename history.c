#include "history.h"
#include "common.h"

static char *history [HISTORY_MAX_SIZE]; //Array of pointers storing previous commands
static unsigned short int h_count = 0; //counts # of commands

//Stores the most recent command in the array
void add_command_to_history(char *cmd){
	if(h_count < HISTORY_MAX_SIZE){
      history[h_count++] = strdup(cmd);
  }
  else{   //case where there have been more commands than out array can store
      free(history[0]);
    	unsigned index;
    	for(index=1;index < HISTORY_MAX_SIZE;index++){ //Move every command down the array
    		history[index-1] = history[index];           //deleting the oldest from the bottom
    	}
    	history[HISTORY_MAX_SIZE-1] = strdup(cmd);     //add the most recent command
    	h_count++;
  }
  return;
}

//Finds and returns the command entered at count n+1
char *get_prev_cmd(int n){
	n--;     //Decrement n, since the first command is at 0 not 1
  char *cmd;  //Pointer to command, if found 

  //Error cases where command n is out of range, this can either be
  //that it doesn't exist of it has been retired form the array
  if(n > h_count ||
    (h_count > HISTORY_MAX_SIZE && n < h_count - HISTORY_MAX_SIZE)){
    	return NULL;
  }
      
  if(h_count < HISTORY_MAX_SIZE) {
      cmd = history[n];
  }
  //Case where our array has filled up and old commands sink to the bottom
  else{
       int l =  HISTORY_MAX_SIZE - (h_count - n);
       cmd = history[l];
  }

  //If the command that has been found is a command that also 
  //access a previous command then we return an error to prevent recursions
  if(parse_prev_command(cmd) == -1)
    return cmd;
  else
   	return NULL;
}

//Given an input checks that it matches the correct format
//to access preious commands which is '!%d' where %d is a positive int
int parse_prev_command(char *cmd){
  static int n;
  if(*cmd == '!'){
      cmd++;
      n = atoi(cmd);
      if(n > 0)
        return n;    //returns the count of the command the user want's to repeat
  }
  return -1;  //command doesn't match the format  
}

//Prints the array of commands to the terminal, indexed by count
void print_history(){
   int i;
   if(h_count>HISTORY_MAX_SIZE){
     for (i = 1; i < HISTORY_MAX_SIZE; i++)
     {
    	printf("%d: %s\n",(h_count - HISTORY_MAX_SIZE + i +1),history[i % HISTORY_MAX_SIZE]);
     }

   }
   else{
    for (i = 0; i < h_count; i++)
    {
    	printf("%d: %s\n",(i+1),history[i]);
    }
   }
}