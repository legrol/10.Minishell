/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-24 07:07:14 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-04-24 07:07:14 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>  //para typedef, malloc
# include <unistd.h> // para write()

//variable estatica
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//funciones principales
char	*get_next_line(int fd);

//funciones utiles de ayuda
size_t	ft_strlen1(const char *s);
char	*ft_strchr1(const char *s, int c);
char	*ft_strdup1(const char *s);
size_t	ft_strlcpy1(char *dest, const char *src, size_t size);
char	*ft_strjoin1(char const *s1, char const *s2);
char	*ft_substr1(char const *s, unsigned int start, size_t len);

#endif