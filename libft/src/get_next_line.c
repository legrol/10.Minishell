/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 13:27:06 by pabromer          #+#    #+#             */
/*   Updated: 2024/09/24 14:15:50 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


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
	static char		*leftover;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (leftover)
			free(leftover);
		return (NULL);
	}
	if (!leftover)
		leftover = ft_strdup("");
	leftover = read_file(fd, leftover);
	newline = find_line(leftover);
	if (!newline && !leftover)
		return (free(leftover), NULL);
	leftover = find_leftover(leftover);
	if (!leftover)
		free(leftover);
	if (!newline || ft_strlen(newline) <= 0 || newline == NULL)
		return (free(newline), NULL);
	return (newline);
}
