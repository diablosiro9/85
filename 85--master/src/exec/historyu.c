/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historyu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:38:07 by dojannin          #+#    #+#             */
/*   Updated: 2023/03/29 14:31:49 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/include.h"
#include <termios.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>
#define MAX_LINE_LEN 1024


void set_raw_mode(struct termios *saved_termios)
{
    struct termios termios;

    // Récupérer les paramètres courants du terminal
    tcgetattr(STDIN_FILENO, saved_termios);

    // Copier les paramètres courants dans une nouvelle structure termios
    memcpy(&termios, saved_termios, sizeof(struct termios));

    // Configurer le mode non-canonique (raw mode)
    termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &termios);
}

void restore_terminal_mode(const struct termios *saved_termios)
{
    // Restaurer les paramètres courants du terminal
    tcsetattr(STDIN_FILENO, TCSANOW, saved_termios);
}

void handle_up_arrow(char *line, int *pos)
{
    // Cette fonction sera appelée lorsque l'utilisateur appuie sur la flèche du haut

    // Ici, vous pouvez remplacer la séquence d'échappement ^[[A par une autre valeur
    // que l'utilisateur pourra modifier avant de valider la commande

    // Par exemple, pour remplacer ^[[A par "hello", vous pouvez faire
    strcpy(line, "hello");
    *pos = strlen(line);

    // Pour afficher la nouvelle ligne de commande modifiée
    printf("\r> %s", line);
    fflush(stdout);
}

int main(int argc, char **argv)
{
    struct termios saved_termios;
    char line[MAX_LINE_LEN];
    int pos = 0;

    // Configurer le mode non-canonique (raw mode)
    set_raw_mode(&saved_termios);

    // Afficher le prompt
    printf("> ");
    fflush(stdout);

    while (1) {
        // Lire une entrée clavier
        char c;
        if (read(STDIN_FILENO, &c, 1) < 0) {
            // Gestion d'erreur
            perror("read");
            break;
        }

        if (c == '\r' || c == '\n') {
            // L'utilisateur a validé la ligne de commande
            printf("\n");

            // Ici, vous pouvez traiter la ligne de commande comme d'habitude
            // ...

            // Réinitialiser la ligne de commande et la position du curseur
            line[0] = '\0';
            pos = 0;

            // Afficher le prompt
            printf("> ");
            fflush(stdout);
        } else if (c == '\033') {
            // L'utilisateur a appuyé sur une touche de direction (flèche, etc.)

            // Lire la suite de la séquence d'échappement
            char seq[3];
            if (read(STDIN_FILENO, seq, sizeof(seq)) < 0) {
                // Gestion d'erreur
                perror("read");
                break;
            }
			 if (seq[0] == '[' && seq[1] == 'A') {
            // L'utilisateur a appuyé sur la flèche du haut
            handle_up_arrow(line, &pos);
        }
    } else if (c == '\b' || c == 127) {
        // L'utilisateur a appuyé sur la touche de suppression (backspace ou delete)

        if (pos > 0) {
            // Déplacer le curseur d'une position vers la gauche
            printf("\b");

            // Effacer le caractère à la position courante
            printf(" ");
            printf("\b");

            // Mettre à jour la ligne de commande et la position du curseur
            line[--pos] = '\0';
        }
    } else {
        // Ajouter le caractère à la position courante
        if (pos < MAX_LINE_LEN - 1) {
            printf("%c", c);
            line[pos++] = c;
            line[pos] = '\0';
        	}
   		}
	}
}