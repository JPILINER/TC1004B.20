#include <unistd.h>
#include <ctype.h>
#include <stdio.h>

int main(){
    char c;
    char upper;
    int n;
    do{
        read(STDIN_FILENO,&c,1);
        upper = toupper(c);
        write(STDOUT_FILENO,&upper,1);
    }while(n != 0);
    return 0;
}