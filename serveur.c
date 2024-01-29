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
    //Affiche le PID du serveur
    print_pid();
    //Affiche qu'il attend les nouveaux messages
    printf("En attente de nouveaux messages\n");

    //Quand SIGUSRX reçu appel la fonction "print_msg" avec le numéro du signal
    signal(SIGUSR1, print_msg);
    signal(SIGUSR2, print_msg);
    while (1)
    {
        pause();
    }
    
    return 0;
}

// AFFICHER LE MESSAGE
void    print_msg(int signum)
{
    //Initialisation des variables
    static int bits = 0;
    static char msg[] = {0};
    static int size = 0;

    //Transforme les signaux reçus en binaires
    if (signum == SIGUSR1)
    {
        binary = (binary << 1) | 0;
    }   
    else if (signum == SIGUSR2)
    {
        binary = (binary << 1) | 1;
    }
    bits++;

    //Quand 8bits reçus transforme en caractères 
    if (bits == 8)
    {
        //Transforme les caractères décodés en chaine de caractères
        msg[size++] = (char)binary;

        if (binary == '\0')
        {
            //Affiche le message décodé
            printf("Message : %s\n", msg);
            //memset remet le message à 0
            memset(msg,0,sizeof(msg));
            size = 0;
        }
        //Remet les valeurs à 0
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
