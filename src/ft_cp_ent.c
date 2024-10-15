/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cp_ent.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:04:46 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/15 15:39:15 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_ent_malloc_size(char **env)
{
    int i;

    i = 0;
    while(env[i])
        i++;
    return (i);
}

void *ft_free_cp_ent(char **ent, int k)
{
    while (k >= 0)
	{
		free(ent[k]);
		k--;
	}
	free(ent);
	return (NULL);
}

char **ft_cp_ent(char **env)
{
    int     i;
    int     j;
    char    **cp_env;

    cp_env = (char **)malloc((ft_ent_malloc_size(env)+1)*sizeof(char *));
    if (!cp_env)
        exit(EXIT_FAILURE);
    i = 0;
    while(env[i])
    {
        j = 0;
        cp_env[i] = (char *)malloc((ft_strlen(env[i]) + 1)*sizeof(char)); 
        if (!cp_env[i])
				return (ft_free_cp_ent(cp_env, i));
        while(env[i][j])
        {
                cp_env[i][j] = env[i][j];
                j++;
        }
        cp_env[i][j] = '\0';
        i++;
    }
    cp_env[i] = NULL;
    return (cp_env);
}
