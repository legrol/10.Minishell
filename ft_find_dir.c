/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:53:36 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/15 10:35:30 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_find_dir(char **env, const char *str)
{
    int     i;
    char    *result;

    i = 0;
    while(env[i])
    {
        result = ft_strnstr(env[i], str, ft_strlen(str));
        if(result)
            return (ft_strchr(result, '/'));
        i++;
    }
    return (NULL);
}