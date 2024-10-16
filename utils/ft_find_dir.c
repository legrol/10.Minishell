/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:53:36 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/16 12:09:26 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_find_dir(t_minishell *minishell, const char *str)
{
    int         i;
    char        *result;
    t_envp *temp;

    temp = minishell->list_envp;
    i = 0;
    while(minishell->list_envp)
    {
        if (ft_strcmp(minishell->list_envp->key, (char *)str) == 0)
        {
            result = minishell->list_envp->value;
            minishell->list_envp = temp;
            return (result);
        }
        minishell->list_envp = minishell->list_envp->next;
    }
    minishell->list_envp = temp;
    return (NULL);
}