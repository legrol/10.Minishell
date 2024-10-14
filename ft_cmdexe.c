#include "libft.h"
#include <stdio.h>

char *ft_cmd_action(char **path, char *arg)
{
	int i;
	char *cmd;

	i = 0;
	while(path[i])
	{
		cmd = ft_strjoin(path[i], arg);
	    if (access(cmd, X_OK) == 0)
	        return (cmd);
        free (cmd);
        cmd = NULL;
        i++;
	}
	return NULL;
}

void ft_cmdexe(char **env, char *str)
{
    char **arg;
    char *cmd;
    char **path;
    pid_t pid;
    int status;

    pid = fork();
    if(pid == -1)
    {
        perror("fork fallo");
        EXIT_FAILURE;
    }
    else if (pid == 0)
    {
        path = ft_path(env);
        arg = ft_split(str, ' ');
        cmd = ft_cmd_action(path, arg[0]);
        execve(cmd, arg, NULL);
	    perror("execve cmd2:");
	    exit(EXIT_FAILURE);
    }
    else
        waitpid(pid, &status, 0);
}
