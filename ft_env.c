#include <stdio.h>
#include "libft.h"

void ft_env(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}