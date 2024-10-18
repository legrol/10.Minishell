/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-02 11:37:10 by rdel-olm          #+#    #+#             */
/*   Updated: 2024-10-02 11:37:10 by rdel-olm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * 
 * 
 * 
 * 
 */

void	ft_pwd(t_minishell *minishell)
{
	ft_printf("%s\n", ft_find_dir(minishell, "OLDPWD"));
}
