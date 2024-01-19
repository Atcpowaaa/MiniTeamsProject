#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>


// PROTOS
void    send_msg(int pid, char *msg);


// MESSAGE
int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        int pid = atoi(argv[1]);
        char *msg = argv[2];
        send_msg(pid,msg);
    }
    else
    {
        printf("Il faut mettre en paramètre le PID du serveur et le message\n");
        return 1;
    }
}

void send_msg(int pid, char *msg)
{
    while (*msg != '\0') {
        // Traitement des caractère
        for (int i = 7; i >= 0; i--) {
            // Bits 1
            int bit = (*msg >> i) & 1;
            if (bit == 0)
            {
                kill(pid, SIGUSR1);
            }
            else
            {
                kill(pid, SIGUSR2);
            }
            usleep(1000);
        }
        msg++;
    }
    for (int i = 7; i >= 0; i--) {
    // Bits 1
    int bit = (*msg >> i) & 1;
    if (bit == 0)
    {
        kill(pid, SIGUSR1);
    }
    else
    {
        kill(pid, SIGUSR2);
    }
    usleep(1000);
}}
