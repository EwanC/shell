#include "history.h"
#include "common.h"

static char *history [HISTORY_MAX_SIZE];
static unsigned short int h_count = 0;

void add_command_to_history(char *cmd){
	if(h_count < HISTORY_MAX_SIZE){
       history[h_count++] = strdup(cmd);
    }
    else{
    	free(history[0]);
    	unsigned index;
    	for(index=1;index < HISTORY_MAX_SIZE;index++){
    		history[index-1] = history[index];
    	}
    	history[HISTORY_MAX_SIZE-1] = strdup(cmd);
    	h_count++;
    }
   return;
}

char *get_prev_cmd(int n){
	n--;
    char *cmd;


    if(n > h_count ||
       (h_count > HISTORY_MAX_SIZE && n < h_count - HISTORY_MAX_SIZE)){
    	 return NULL;
    }
    if(h_count < HISTORY_MAX_SIZE) {
       cmd = history[n];
   }
    else{
       int l =  HISTORY_MAX_SIZE - (h_count - n);
       cmd = history[l];
    }

   if(is_prev_command(cmd) == -1)
    return cmd;
   else
   	return NULL;
}

int is_prev_command(char *cmd){
  static int n;
  if(*cmd == '!'){
     cmd++;
     n = atoi(cmd);
     if(n > 0)
       return n;
  }
  return -1;
}


void print_history(){
   int i;
   if(h_count>HISTORY_MAX_SIZE){
     for (i = 1; i < HISTORY_MAX_SIZE; i++)
     {
    	printf("%d: %s",(h_count - HISTORY_MAX_SIZE + i +1),history[i % HISTORY_MAX_SIZE]);
     }

   }
   else{
    for (i = 0; i < h_count; i++)
    {
    	printf("%d: %s",(i+1),history[i]);
    }
   }
}