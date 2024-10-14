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
    char **arg;
    char *cmd;
    char **path;

    while (1) 
    { 
        input = readline("Escribe su comando: ");
        ft_cmdexe(env, input);
    }

    return 0;
}
