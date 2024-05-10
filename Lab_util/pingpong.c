#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char** argv) {
  int parent_2_child[2];
  int child_2_parent[2];
  char buf;
  
  //create pipes
  if (pipe(parent_2_child) || pipe(child_2_parent)) {
    fprintf(2, "create pipe failed...\n");
    exit(1);
  }
  
  // Create child process
  if(fork() == 0){
    // Child process
    close(parent_2_child[1]); // Close write end of pipe from parent to child
    close(child_2_parent[0]); // Close read end of pipe from child to parent

    // Read byte from parent
    read(parent_2_child[0], &buf, 1);
    fprintf(1, "%d: received ping\n", getpid());

    // Write byte to parent
    write(child_2_parent[1], &buf, 1);
    close(parent_2_child[0]);
    close(child_2_parent[1]);
    exit(0);
  }
  else {
    // Parent process
    close(parent_2_child[0]); // Close read end of pipe from parent to child
    close(child_2_parent[1]); // Close write end of pipe from child to parent

    // Send byte to child
    write(parent_2_child[1], "a", 1);
    wait(0);

    // Read byte from child
    read(child_2_parent[0], &buf, 1);
    fprintf(1, "%d: received pong\n", getpid());

    close(parent_2_child[1]);
    close(child_2_parent[0]);
    exit(0);
  }

  exit(0);
}
