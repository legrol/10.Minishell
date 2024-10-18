/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-14 09:58:51 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-05-14 09:58:51 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

/**
 * The get_next_line() function write a function that returns the line read 
 * from a file descriptor.
 * 
 * @param int fd    file descriptor to read from.
 * 
 * returns  If all goes well: the line read
 *          On failure or if reading ends: NULL
 * 
*/

char	*ft_strchr1(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char) c)
			return ((char *) s);
		else
			s++;
	}
	if ((char) c == '\0')
		return ((char *)s);
	return (0);
}

static void	ft_free(char *buffer_readed, char *buffer_print)
{
	free(buffer_readed);
	free(buffer_print);
}

static char	*manage_readed_line(char	*treat_line)
{
	char	*new_buffer_print;	
	size_t	i;

	i = 0;
	while (treat_line[i] != '\n' && treat_line[i] != '\0')
		i++;
	if (treat_line[i] == 0 || treat_line[1] == 0)
	{
		free(treat_line);
		return (NULL);
	}
	new_buffer_print = ft_substr1(treat_line, i + 1, ft_strlen1(treat_line) \
	- i);
	if (*new_buffer_print == 0 || *new_buffer_print == '\0')
	{
		free(new_buffer_print);
		new_buffer_print = NULL;
	}
	treat_line[i + 1] = '\0';
	return (new_buffer_print);
}

static char	*read_fill_line(int fd, char *buffer_readed, char *buffer_print)
{
	ssize_t			bytes_readed;	
	char			*buffer_tmp;

	bytes_readed = 1;
	while (bytes_readed > 0)
	{
		bytes_readed = read(fd, buffer_readed, BUFFER_SIZE);
		if (bytes_readed < 0)
		{
			ft_free(buffer_readed, buffer_print);
			return (NULL);
		}
		else if (bytes_readed == 0)
			break ;
		buffer_readed[bytes_readed] = '\0';
		if (!buffer_print)
			buffer_print = ft_strdup1("");
		buffer_tmp = buffer_print;
		buffer_print = ft_strjoin1(buffer_tmp, buffer_readed);
		free(buffer_tmp);
		buffer_tmp = NULL;
		if (ft_strchr1(buffer_readed, '\n'))
			break ;
	}
	return (buffer_print);
}

char	*get_next_line(int fd)
{
	char			*buffer_readed;
	char			*line_print;
	static char		*buffer_print;

	buffer_readed = (void *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, 0, 0) < 0)
	{
		free(buffer_print);
		free(buffer_readed);
		buffer_print = NULL;
		buffer_readed = NULL;
		return (NULL);
	}
	if (!buffer_readed)
		return (NULL);
	line_print = read_fill_line(fd, buffer_readed, buffer_print);
	free(buffer_readed);
	buffer_readed = NULL;
	if (!line_print)
		return (NULL);
	buffer_print = manage_readed_line(line_print);
	return (line_print);
}
