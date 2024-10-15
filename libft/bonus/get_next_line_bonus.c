/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:27:06 by pabromer          #+#    #+#             */
/*   Updated: 2024/06/10 13:34:15 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_file(int fd, char *leftover)
{
	ssize_t	nbytes;
	char	*buffer;
	char	*temp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(leftover), NULL);
	nbytes = 1;
	while (nbytes > 0 && !ft_strchr(leftover, '\n'))
	{
		nbytes = read(fd, buffer, BUFFER_SIZE);
		if (nbytes == -1)
			return (free(buffer), free(leftover), NULL);
		buffer[nbytes] = 0;
		temp = ft_strjoin(leftover, buffer);
		if (!temp)
			return (free(buffer), free(leftover), NULL);
		free(leftover);
		leftover = temp;
	}
	free(buffer);
	return (leftover);
}

char	*find_line(char *leftover)
{
	char	*line;
	ssize_t	i;

	i = 0;
	if (!leftover[i])
		return (NULL);
	while (leftover[i] != '\n' && leftover[i] != '\0')
		i++;
	line = ft_substr(leftover, 0, i + 1);
	if (!line)
		return (free(leftover), NULL);
	return (line);
}

char	*find_leftover(char *leftover)
{
	char	*new_left;
	ssize_t	i;
	ssize_t	j;

	i = 0;
	while (leftover[i] != '\n' && leftover[i] != '\0')
		i++;
	if (leftover [i] == '\0')
		return (free(leftover), NULL);
	new_left = (char *)malloc(sizeof(char) * (ft_strlen(leftover) - i + 1));
	if (!new_left)
		return (free(leftover), NULL);
	i++;
	j = 0;
	while (leftover[i] != '\0')
		new_left[j++] = leftover[i++];
	new_left[j] = '\0';
	free(leftover);
	return (new_left);
}

char	*get_next_line(int fd)
{
	char			*newline;
	static char		*leftover[4096];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (leftover[fd])
		{
			free(leftover[fd]);
			leftover[fd] = NULL;
		}
		return (NULL);
	}
	if (!leftover[fd])
		leftover[fd] = ft_strdup("");
	leftover[fd] = read_file(fd, leftover[fd]);
	newline = find_line(leftover[fd]);
	if (!newline && !leftover[fd])
		return (free(leftover[fd]), NULL);
	leftover[fd] = find_leftover(leftover[fd]);
	if (!leftover[fd])
		free(leftover[fd]);
	if (!newline || ft_strlen(newline) <= 0 || newline == NULL)
		return (free(newline), NULL);
	return (newline);
}
