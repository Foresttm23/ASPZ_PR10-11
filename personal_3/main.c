#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    fork(); 
    fork(); 

    printf("My: %d; Parent: %d\n", getpid(), getppid());
    return 0;
}
