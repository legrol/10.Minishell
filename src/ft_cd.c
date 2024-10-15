/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:22:05 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/15 16:41:40 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *ft_free_env_all(char **ent, int k)
{
    int i;
    
    i = k+1;
    while (k >= 0)
	{
		free(ent[k]);
		k--;
	}
    while (ent[i])
	{
		free(ent[i]);
		i++;
	}
	free(ent);
	return (NULL);
}

char *ft_change_env(char **ent, char *cwd)
{
    char *p;
    char *prompt;
    int     i;
    int     j;

    prompt = "pabromer-rdel-olm minishell:~";
	p = ft_strjoin(prompt, cwd);
	prompt = ft_strjoin(p, "$ ");
    free(p);
    i = 0;
    while(ent[i])
    {
        if (ft_strnstr(ent[i], "PWD", ft_strlen(ent[i])))
        {
            free(ent[i]);
            ent[i] = (char *)malloc((ft_strlen(cwd)+5)*sizeof(char));
            if (!ent[i])
                return(ft_free_env_all(ent, i));
            j = 0;
            p = ft_strjoin("PWD=", cwd);
            while(p[j])
            {
                ent[i][j] = p[j];
                j++;
            }
            ent[i][j] = '\0';
            free(p);
        }
        i++;
    }
    return (prompt); 
}

char *ft_cd(char *input, char **env)
{
    char **split;
    char cwd[1024];
    char *prompt;
    
    split = ft_split(input, ' ');
    if (split[1][0] == '~' && split[1][1] == '\0')
        chdir(ft_find_dir(env, "HOME"));
    else if (ft_strnstr(input, "..", ft_strlen(input)) && chdir(split[1]) != 0)
        chdir("/");
    else if (ft_strnstr(input, "..", ft_strlen(input)))
        chdir("..");
    else if(chdir(split[1]) != 0)
        ft_printf("cd: no such file or directory: %s\n", split[1]);
    else
        chdir(split[1]);
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
        prompt = ft_change_env(env, cwd);
    else
        perror("getcwd() error");
    p_freessplit(split,p_mallocsize(input, ' '));
    return(prompt);
}
