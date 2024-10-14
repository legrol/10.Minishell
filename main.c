#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

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
char    *ft_strjoin(char const *s1, char const *s2)
{
        char    *join;
        int             i;
        int             j;

        if (!s1 || !s2)
                return (NULL);
        join = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
        if (!join)
                return (NULL);
        i = 0;
        while (s1[i] != '\0')
        {
                join[i] = s1[i];
                i++;
        }
        j = 0;
        while (s2[j] != '\0')
        {
                join[i + j] = s2[j];
                j++;
        }
        join[i + j] = '\0';
        return (join);
}

char    *ft_strdup(const char *s1)
{
        size_t  count;
        char    *dest;
        int             i;

        i = 0;
        count = ft_strlen(s1) + 1;
        dest = (char *)malloc(count);
        if (!dest)
                return (NULL);
        while (s1[i] != 0)
        {
                dest[i] = s1[i];
                i++;
        }
        dest[i] = '\0';
        return (dest);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
        char    *subs;
        size_t  i;

        if (!s)
                return (NULL);
        if (start >= ft_strlen(s))
                return (ft_strdup(""));
        if (ft_strlen(s) - start < len)
                len = ft_strlen(s) - start;
        subs = (char *) malloc(len + 1);
        if (!subs)
                return (NULL);
        i = 0;
        while (i < len)
        {
                subs[i] = s[start + i];
                i++;
        }
        subs[i] = '\0';
        return (subs);
}

int main(int argc, char **argv, char **env) {
    
	char *input;
	char *p;
	char *prompt;
	char *prueba;
	
	
	prompt = "pabromer-rdel-olm minishell:~";
	p = ft_strjoin(prompt, ft_find_dir(env, "PWD"));
	prompt = ft_strjoin(p, "$ ");
	free (p);
    while (1) 
    { 
        input = readline(prompt);
		if (input[0] == 'e' && input[1] == 'c' && input[2] == 'h' && input[3] == 'o' && input[4] == '\0')
			ft_echo;
		else if (input[0] == 'c' && input[1] == 'd' && input[2] == '\0')
			ft_cd;
		else if (input[0] == 'e' && input[1] == 'x' && input[2] == 'p' && input[3] == 'o' && input[4] == 'r' && input[5] == 't' && input[6] == '\0')
			ft_export;
		else if (input[0] == 'u' && input[1] == 'n' && input[2] == 's' && input[3] == 'e' && input[4] == 't' && input[5] == '\0')
			ft_unset;
		else if (input[0] == 'e' && input[1] == 'n' && input[2] == 'v' && input[3] == '\0')
			ft_env(env);
		else if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input[3] == 't' && input[4] == '\0')
			break;
		else
        	ft_cmdexe(env, input);
		free(input);
    }
	free(prompt);
	free(input);
    return 0;
}

