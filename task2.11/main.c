#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    int status;

    pid1 = fork();
    if (pid1 == 0) {
        printf("[Child 1] PID = %d, sleeping 2 sec\n", getpid());
        sleep(2);
        exit(1);
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("[Child 2] PID = %d, sleeping 4 sec\n", getpid());
        sleep(4);
        exit(2);
    }

    pid_t finished_pid = wait(&status);
    if (WIFEXITED(status)) {
        printf("[Parent] wait(): PID %d exited with code %d\n",
               finished_pid, WEXITSTATUS(status));
    }

    waitpid(pid2, &status, 0);
    if (WIFEXITED(status)) {
        printf("[Parent] waitpid(): PID %d exited with code %d\n",
               pid2, WEXITSTATUS(status));
    }

    pid_t nohang_pid = waitpid(-1, &status, WNOHANG);
    if (nohang_pid == 0) {
        printf("[Parent] waitpid(WNOHANG): no children have exited yet\n");
    } else if (nohang_pid > 0) {
        printf("[Parent] waitpid(WNOHANG): PID %d exited\n", nohang_pid);
    } else {
        printf("[Parent] waitpid(WNOHANG): no more children\n");
    }

    return 0;
}
