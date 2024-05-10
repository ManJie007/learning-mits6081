#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "Kernel/param.h"

#define MAX_BUFFER_SIZE 512

int main(int argc, char *argv[]) {

  char *args[MAXARG]; // record the token from input spilt by space(' ')
  int size = argc - 1;// record token number(initial is argc - 1,because xargs will bot be execute)
  int n = -1;

  // first copy initial argv argument to args
  for(int i=0;i<size;i++)
    args[i]=argv[i+1];

  char buf[MAX_BUFFER_SIZE]; // record the input from previous command
  char token[MAX_BUFFER_SIZE]; // buf for the char of all token
  char* p = token;
  int len = 0;

  while((n = read(0,buf,sizeof(buf))) > 0){
    for(int i = 0; i < n;i++){
      char c = buf[i];
      if(c == '\n'){// if read '\n', execute the command
        token[len] = 0; // set '\0' to end of token
        args[size++] = p;
        args[size] = 0; // set nullptr in the end of array

        if(fork()==0){ // open child to execute
          exec(argv[1],args);
        }
        wait(0);
        size = argc - 1;// initialize
        len = 0;
        p = token;
      }
      else if(c == ' '){
        token[len++] = 0; // mark the end of string
        args[size++] = p;
        p = token+len; // change to the start of new string
      }else{
        token[len++] = c;
      }

    }
  }
  exit(0);
}
