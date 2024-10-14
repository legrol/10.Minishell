/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drosales <drosales@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:27:17 by drosales          #+#    #+#             */
/*   Updated: 2024/10/12 11:41:00 by drosales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_cd(t_ast *cmd)
{
    const char  *path;
    char        *oldpwd;
    char        cwd[1024];
    char        previous_cwd[1024];
    char        new_cwd[1024];

    if (!getcwd(previous_cwd, sizeof(previous_cwd)))
        return (ft_printf("Error: unable to get current directory.\n"), ERROR);
    oldpwd = getenv("PWD");
    if (!oldpwd)
    {
        oldpwd = getcwd(cwd, sizeof(cwd));
        if (!oldpwd)
            return (ERROR);
    }
    if (cmd->left == NULL || cmd->left->value == NULL)
    {
        path = getenv("HOME");
        if (!path)
            return (ft_printf("Error: HOME not set.\n"), ERROR);
        ft_printf("%s\n", path); // Imprimir el directorio HOME
    }
    else if (ft_strcmp(cmd->left->value, "-") == 0)
    {
        path = getenv("HOME");  // Cambiar siempre a HOME con cd -
        if (!path)
            return (ft_printf("Error: HOME not set.\n"), ERROR);
        ft_printf("%s\n", path); // Imprimir el directorio HOME
    }
    else
        path = cmd->left->value;
    if (chdir(path) != 0)
        return (ft_printf("Error: cannot change to %s.\n", path), ERROR);
    if (ft_strcmp(path, "..") == 0)
    {
        if (getcwd(new_cwd, sizeof(new_cwd)) && ft_strcmp(previous_cwd, new_cwd) != 0)
            ft_printf("Moved back from: %s to %s\n", previous_cwd, new_cwd);
    }
    setenv("OLDPWD", oldpwd, 1);
    if (getcwd(cwd, sizeof(cwd)))
        setenv("PWD", cwd, 1);
    return (OK);
}

int ft_pwd(t_ast *cmd)
{
    char    cwd[1024];

    if (cmd->left != NULL) // SIGNIFICA QUE HAY MAS QUE "PWD"
    {
        ft_printf("Error : PWD must be alone...\n");
        return (ERROR);
    }
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        ft_printf("Error : Value of PWD is NULL...\n");
        return (1);
    }
    ft_putstr_fd(cwd, STDOUT);
    ft_putstr_fd("\n", STDOUT);
    return (OK);
}

int ft_clear(t_ast *cmd)
{
    if (cmd->left == NULL)
        ft_printf("\033[H\033[J");
    else
    {
        ft_printf("Error : To many arguments for 'clear' command...\n");
        return (ERROR);
    }
    return (OK);
}

int ft_exit(t_ast *cmd)
{
    if (cmd->left == NULL)
    {
        ft_putstr_fd("You left minihell succesfully! 🫰\n", STDOUT);
        exit(0);
    }
    else
    {
        ft_printf("Error : To many arguments for 'clear' command...\n");
        return (ERROR);
    }
    return (OK);
}

