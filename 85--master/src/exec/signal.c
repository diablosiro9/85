# include "../../include/include.h"

void sig_handler(int sig) {
   struct termios	conf;
   printf("signal %d\n", sig);
    if (sig == SIGINT) {
         printf("\nCTRL+C détecté. Sortie.\n");
         ioctl(ttyslot(), TIOCGETD, &conf);
         conf.c_lflag |= ECHO;
         ioctl(ttyslot(), TIOCSETD, &conf);
    }
}

void sig_quit(int sig)
{
   printf("signal %d\n", sig);
   if (sig == SIGQUIT) {
      printf("CTRL+D détecté. Sortie.\n");
      exit(0);
   }
}
