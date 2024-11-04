/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-31 11:43:51 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-10-31 11:43:51 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_free_split" frees the memory allocated for an array of 
 * strings. This function iterates through each string in the array, frees it, 
 * and then frees the array itself.
 * 
 * @param char **sub_tokens		An array of strings to be freed. Each string 
 * 								within the array, as well as the array itself,
 * 								will be deallocated.
 * 
 */

void	ft_free_split(char **sub_tokens)
{
	int	i;

	if (!sub_tokens)
		return ;
	i = 0;
	while (sub_tokens[i])
	{
		free(sub_tokens[i]);
		i++;
	}
	free(sub_tokens);
}
