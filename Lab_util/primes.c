#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define READ 0
#define WRITE 1

void sieve(int in_fd) {
    int prime;
    int pipe_fd[2];

    // Read the first prime number from the input pipe
    if (read(in_fd, &prime, sizeof(prime)) == 0) {
        // If no more input, close the pipe and exit
        close(in_fd);
        exit(0);
    }

    // Print the prime number
    fprintf(1, "prime %d\n", prime);

    // Create a new pipe
    pipe(pipe_fd);

    if (fork() == 0) {
        // Child process
        close(pipe_fd[WRITE]);
        sieve(pipe_fd[READ]);
    } else {
        // Parent process
        close(pipe_fd[READ]);

        // Filter out multiples of the current prime number
        int num;
        while (read(in_fd, &num, sizeof(num)) != 0) {
            if (num % prime != 0) {
                write(pipe_fd[WRITE], &num, sizeof(num));
            }
        }

        // Close the input pipe and wait for the child to finish
        close(in_fd);
        close(pipe_fd[WRITE]);
        wait(0);
        exit(0);
    }
}

int main(int argc, char** argv) {

  int pipe_fd[2];
  pipe(pipe_fd);

  if (fork() == 0) {
    // Child process
    close(pipe_fd[WRITE]);
    sieve(pipe_fd[READ]);
  
  }else {
    // Parent process
    close(pipe_fd[READ]);

    // Write numbers 2 through 35 to the pipe
    int num;
    for (num = 2; num <= 35; num++) {
        write(pipe_fd[WRITE], &num, sizeof(num));
    }

    // Close the pipe and wait for the child to finish
    close(pipe_fd[WRITE]);
    wait(0);
    exit(0);
  }

  exit(0);
}
