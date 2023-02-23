#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv){

    char buf[256] = {0};

    getcwd(buf, sizeof(buf));
    printf("current working directory : %s\n", buf);

    while(1)
    {
        
    }

    return 0;
}
