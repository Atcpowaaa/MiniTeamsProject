#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


// PROTOS
void    print_pid(void);
void    print_msg(int signum);

int binary = 0;

// MESSAGE
int main()
{
    print_pid();
    printf("En attente de nouveaux messages\n");

    signal(SIGUSR1, print_msg);
    signal(SIGUSR2, print_msg);
    while (1)
    {
        sleep(1);
    }
    
    return 0;
}

// AFFICHER LE MESSAGE
void    print_msg(int signum)
{
    static int bits = 0;
    static char msg[] = {0};
    static int size = 0;

    if (signum == SIGUSR1)
    {
        binary = (binary << 1) | 0;
    }   
    else if (signum == SIGUSR2)
    {
        binary = (binary << 1) | 1;
    }
    bits++;

    if (bits == 8)
    {
        msg[size++] = (char)binary;

        if (binary == '\0')
        {
            printf("Message : %s\n", msg);
            memset(msg,0,sizeof(msg));
            size = 0;
        }
        bits = 0;
        binary = 0;
    }
}


// Afficher PID SERV
void    print_pid(void)
{
    int pid;
    
    pid = getpid();
    printf("PID SERVEUR : %i\n", pid);
}
