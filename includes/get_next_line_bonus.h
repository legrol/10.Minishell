/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-27 11:32:17 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-05-27 11:32:17 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>  //para typedef, malloc
# include <unistd.h> // para write()

//variable estatica para Buffer
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//funciones principales
char	*get_next_line2(int fd);

//funciones utiles de ayuda
size_t	ft_strlen2(const char *s);
char	*ft_strchr2(const char *s, int c);
char	*ft_strdup2(const char *s);
size_t	ft_strlcpy2(char *dest, const char *src, size_t size);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_substr2(char const *s, unsigned int start, size_t len);

#endif 