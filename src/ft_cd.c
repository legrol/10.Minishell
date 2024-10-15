/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:22:05 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/15 14:04:31 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_cd(char *input, char **env)
{
    char *prompt;
    char **split;
    char *p;
    char cwd[1024];
    
    split = ft_split(input, ' ');
    if (split[1][0] == '~' && split[1][1] == '\0')
        chdir(ft_find_dir(env, "HOME"));
    else if (ft_strnstr(input, "..", ft_strlen(input)) && chdir(split[1]) != 0)
        chdir("/");
    else if(chdir(split[1]) != 0)
        ft_printf("cd: no such file or directory: %s\n", split[1]);
    else
        chdir(split[1]);
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        prompt = "pabromer-rdel-olm minishell:~";
	    p = ft_strjoin(prompt, cwd);
	    prompt = ft_strjoin(p, "$ ");
        free(p);
    } 
    else
        perror("getcwd() error");
    p_freessplit(split,p_mallocsize(input, ' '));
    return(prompt);
}
