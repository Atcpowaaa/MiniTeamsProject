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
    //compte que le nombre d'arguments vaut 3 (commande/arg1/arg2)
    if (argc == 3)
    {
        //Extrait le PID du premier argument et le message du deuxième
        int pid = atoi(argv[1]);
        char *msg = argv[2];
        //Appel la fonction "send_msg"
        send_msg(pid,msg);
    }
    else
    {
        //Si les arguments ne sont pas au bon nombre, il affiche une erreur
        printf("Il faut mettre en paramètre le PID du serveur et le message\n");
        return 1;
    }
}

//Prend en valeur le pid cible et le message
void send_msg(int pid, char *msg)
{
    //Tant que le message n'est pas fini
    while (*msg != '\0') {
        // Traitement des caractère
        for (int i = 7; i >= 0; i--) {
            // Envoie le message Bits par Bits au PID cible
            int bit = (*msg >> i) & 1;
            if (bit == 0)
            {
                kill(pid, SIGUSR1);
            }
            else
            {
                kill(pid, SIGUSR2);
            }
            //Attends un temps défini pour espacer chaque bits
            usleep(1000);
        }
        msg++;
    }
    //Traitement le dernier caractère du bit
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
