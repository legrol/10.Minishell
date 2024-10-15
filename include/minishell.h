/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:40:32 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/15 13:51:50 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_printf.h"
# include <string.h>
# include <sys/wait.h> 
# include <stdio.h>
# include <readline/readline.h>

char *ft_find_dir(char ** env, const char *str);
unsigned int	p_mallocsize(char const *s, char c);
void	*p_freessplit(char **ssplit, int k);
char **ft_path(char **env);
char *ft_cmd_action(char **path, char *arg);
void ft_cmdexe(char **env, char *str);
void ft_env(char **env);
char *ft_cd(char *input, char **env);

#endif
