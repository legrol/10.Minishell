/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:37:10 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/05 09:59:44 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_pwd" prints the current working directory (CWD) to the
 * standard output. It uses the `getcwd` function to retrieve the CWD and 
 * outputs it using `ft_printf`. The CWD is a key concept in a shell, as it 
 * represents the directory where commands and file paths are resolved.
 * 
 * - The function uses a buffer of size 1024 (`cwd`) to store the directory
 *   path returned by `getcwd`.
 * - If the CWD cannot be retrieved (e.g., due to permission issues or an 
 *   invalid working directory), `getcwd` would return `NULL`. However, 
 *   this is not explicitly handled in this implementation.
 * 
 * @return void						This function does not return a value. 
 * 
 */

void	ft_pwd(void)
{
	char	cwd[1024];

	ft_printf("%s\n", getcwd(cwd, sizeof(cwd)));
}
