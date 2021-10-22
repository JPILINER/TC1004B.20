#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handleTerm(int signal){
    printf("Recieved signal %d\n", signal);
}

int main(){
    signal(15, handleTerm);
    while (1){
        printf("Working \n");
        sleep(1);
    }
    return 0;
}