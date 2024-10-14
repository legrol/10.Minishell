#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *ft_find_dir(char ** env, const char *str);
unsigned int	p_mallocsize(char const *s, char c);
void	*p_freessplit(char **ssplit, int k);
char **ft_path(char **env);

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *) s;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return (&str[i]);
		i++;
	}
	if ((char) c == '\0')
		return (&str[i]);
	return (NULL);
}
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*r;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (needle[j] != '\0' && haystack[i + j] == needle[j])
		{
			j++;
		}
		if (needle[j] == '\0' && i + j <= len)
		{
			r = (char *)haystack;
			return (&r[i]);
		}
		i++;
	}
	return (NULL);
}

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

int main(int argc, char **argv, char **env) {
    char *input;          // Puntero para la entrada del usuario
    char *ultima_entrada = NULL;  // Guardará la última entrada
    char **arg;
    char *cmd;
    char **path;

    while (1) 
    { 
        input = readline("Escribe su comando: ");
        path = ft_path(env);
        arg = ft_split(input, ' ');
        cmd = ft_cmd_action(path, arg[0]);
        execve(cmd, arg, NULL);
		perror("execve cmd2:");
		exit(EXIT_FAILURE);
    }

    return 0;
}
