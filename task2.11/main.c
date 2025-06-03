#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;

    pid1 = fork();
    if (pid1 == 0) {
        printf("Child1 %d;\n", getpid());
        exit(11); 
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("Child2 %d;\n", getpid());
        exit(22);
    }

    // wait(NULL)
    pid_t wpid = wait(&status);
    if (WIFEXITED(status)) {
        printf("Parent: %d ; code: %d\n", wpid, WEXITSTATUS(status));
    }

    // PID
    waitpid(pid2, &status, 0);
    if (WIFEXITED(status)) {
        printf("Parent: %d; code: %d\n", pid2, WEXITSTATUS(status));
    }

    // WNOHANG
    pid_t pid3 = fork();
    if (pid3 == 0) {
        printf("Child3 %d;\n", getpid());
        exit(33);
    }

    sleep(1);

    int nohang_status;
    pid_t result = waitpid(pid3, &nohang_status, WNOHANG);
    if (result == 0) {
        printf("Child %d is running WNOHANG\n", pid3);
    } else if (result > 0 && WIFEXITED(nohang_status)) {
        printf("Child %d; code %d WNOHANG\n", pid3, WEXITSTATUS(nohang_status));
    }

    waitpid(pid3, &nohang_status, 0);

    return 0;
}
