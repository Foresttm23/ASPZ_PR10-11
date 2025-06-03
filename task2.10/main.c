#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("Child %d, PID = %d\n", i, getpid());
            exit(0);
        }
    }

    while (wait(NULL) > 0);
    printf("All children finished.\n");

    return 0;
}



// :(){ :|:& };: