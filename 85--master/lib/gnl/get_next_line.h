/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mla-rosa <mla-rosa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 11:21:33 by mehdi             #+#    #+#             */
/*   Updated: 2023/01/27 10:59:42 by mla-rosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 1000000
# include <stdlib.h>
# include <unistd.h>
# include "../../include/include.h"

char	*get_next_line(int fd);

/*  
    Mimi - Je change les noms de ses fonctions afin qu'il n'y ait pas de conflit avec les fonctions de la libft
    J'aurai include ceux de la libft directement mais les fonctions sont codées différemment donc j'avais peur qu'il est une incidence sur le fonctionnement de la fonction get_next_line
    size_t	ft_strlen(char const *s)
    char	*ft_strjoin(char const *s1, char const *s2);
    char	*ft_strchr(const char *s, int c);
    char	*ft_strdup(const char *s1);
    size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
*/

size_t	ft_gnl_strlen(char const *s);
char	*ft_gnl_strjoin(char const *s1, char const *s2);
char	*ft_gnl_strchr(const char *s, int c);
char	*ft_gnl_strdup(const char *s1);
size_t	ft_gnl_strlcpy(char *dst, const char *src, size_t dstsize);

#endif
