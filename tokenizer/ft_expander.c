/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/23 20:34:52 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char ft_find_special_char(char *s)
{
	ft_printf("SPECIAL CHAR ENTER\n");
	int i;
	if (!s)
		return ('\0');
	i=0;
	while(s[i])
	{
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
			return (s[i]);
		i++;
	}
	return ('\0');
}

static char *ft_change_token(char *temp, char *sp)
{
	char *t;
	char *join;

	ft_printf("CHANGE TOKEN ENTER\n");
	if (!temp)
		join = ft_strdup(sp);
	else
		join = ft_strjoin(temp, sp);
	t = ft_strdup(join);
	if (temp)
		free(temp);
	free(join);
	free(sp);
	return (t);
}

static char *ft_only_expand(t_minishell *minishell, char *s)
{
	char *temp;
	char *join;
	char *sp;
	char a;
	int f;

	f = 0;
	ft_printf("ONLY EXPAND ENTER\n");
	temp = ft_strchr_exp(s, '$');
	a = ft_find_special_char(temp);
	temp = ft_strdup(temp);
	if (temp && temp[0] == '?')
	{
		f = 1;
		sp = ft_strchr_exp(temp, '?');
	}
	else
		sp = ft_strchr(temp, a);
	sp = ft_strdup(sp);
	join = ft_strtrim(temp, sp);
	free(temp);
	if (f == 1)
		temp = ft_strdup(ft_itoa(minishell->exit));
	else
	{
		if (ft_find_dir(minishell, join))
			temp = ft_strdup(ft_find_dir(minishell, join));
		else
		temp = NULL;
	}
	free (join);
	return (ft_change_token(temp, sp));
}

static int ft_count_dollar(char *s)
{
	int c;
	int i;

	i = 0;
	c = 0;
	ft_printf("COUNT ENTER\n");
	while(s[i])
	{
		if(s[i] == '$')
			c++;
		i++;
	}
	return (i+c+1);
}

static char *ft_prepare_split(char *s)
{
	int c;
	int i;
	char *temp;

	ft_printf("Prepare SPLIT ENTER\n");
	temp = malloc(ft_count_dollar(s)*sizeof(char));
	i = 0;
	c = 0;
	while(s[i])
	{
		if(s[i] == '$')
		{
			temp[c+i] = '\n';
			c++;
		}
		temp[c+i] = s[i];
		i++;
	}
	temp[c+i] = '\0';
	return (temp);
}

static char *ft_split_expand(t_minishell *minishell, char *s)
{
	char *temp;
	char **split;
	char *temp2;
	char *temp3;
	int i;

	ft_printf("split EXPAND ENTER\n");
	temp = ft_prepare_split(s);
	split = ft_split(temp, '\n');
	i = 0;
	while(split[i])
	{
		if (ft_strchr(split[i], '$'))
		{
			temp2 = ft_only_expand(minishell, split[i]);
			ft_printf("ONLY EXPAND EXIT\n");
			free(split[i]);
			split[i] = ft_strdup(temp2);
			free(temp2);
		}
		else 
			ft_printf("ONLY EXPAND NO ENTER NEXT SPLIT\n");
		i++;
	}
	if (temp)
		free(temp);
	temp = ft_strdup(split[0]);
	free (split[0]);
	i = 1;
	while(split[i])
	{
		temp2 = ft_strjoin(temp, split[i]);
		temp3 = ft_strdup(temp2);
		free(temp);
		free(temp2);
		free(split[i]);
		temp = ft_strdup(temp3);
		free(temp3);
		i++;
	}
	free(split);
	ft_printf("split EXPAND EXIT\n");
	return (temp);
}

static char *split_substrings(t_minishell *minishell, char *input)
{
    static char substrings[100][256]; // Arreglo fijo de substrings
    static char *substring_ptrs[100];        // Punteros a cada substring
    int size = 0;                                       // Número de substrings encontrados
    char *start = input;                          // Puntero al inicio del string

    while (*start) {
        // Detectar inicio de una subcadena entre comillas simples o dobles
        if (*start == '"' || *start == '\'') {
            if (size >= 100) {
                ft_printf("Error: Número máximo de substrings alcanzado.\n");
                break;
            }

            char quote = *start;   // Tipo de comilla encontrada
            char *end = ++start; // Avanzar después de la comilla inicial

            // Buscar la comilla de cierre
            while (*end && *end != quote) {
                end++;
            }

            if (*end == quote) {
                // Copiar incluyendo comillas
                size_t len = end - start + 2; // Incluir ambas comillas
                if (len >= 256) {
                    ft_printf("Error: Longitud máxima de substring excedida.\n");
                    break;
                }

                substrings[size][0] = quote;            // Agregar la comilla inicial
                ft_strcpy(&substrings[size][1], start); // Copiar el contenido
                substrings[size][len - 1] = quote;      // Agregar la comilla final
                substrings[size][len] = '\0';           // Cerrar el string

                substring_ptrs[size] = substrings[size];
                size++;
            }
            start = end + 1; // Avanzar después de la comilla de cierre
        } 
        // Detectar texto no entrecomillado
        else if (*start != ' ' && *start != '\t') {
            if (size >= 100) {
                ft_printf("Error: Número máximo de substrings alcanzado.\n");
                break;
            }

            char *end = start;
            while (*end && *end != '"' && *end != '\'' && *end != ' ' && *end != '\t') {
                end++;
            }

            size_t len = end - start;
            if (len >= 256) {
                ft_printf("Error: Longitud máxima de substring excedida.\n");
                break;
            }

            ft_strcpy(substrings[size], start);
            substrings[size][len] = '\0';

            substring_ptrs[size] = substrings[size];
            size++;
            start = end;
        } 
        else {
            start++;
        }
    }
	int i;
	char *trim;
	
	i = 0;
	while(substring_ptrs[i])
	{
		trim = ft_strtrim(substring_ptrs[i],"\"");
		if (ft_strcmp(trim, substring_ptrs[i]) != 0)
		{
			if (ft_strchr(trim, '$'))
				substring_ptrs[i] = ft_split_expand(minishell, trim);
			else
				substring_ptrs[i] = ft_strdup(trim);
			free(trim);
		}
		else
		{
			free(trim);
			trim = ft_strtrim(substring_ptrs[i],"\'");
			if (ft_strcmp(trim, substring_ptrs[i]) != 0)
				substring_ptrs[i] = ft_strdup(trim);
			else
			{
				if (ft_strchr(trim, '$'))
					substring_ptrs[i] = ft_split_expand(minishell, substring_ptrs[i]);
				else
					substring_ptrs[i] = ft_strdup(trim);
			}
			free(trim);
		}
		i++;
	}
	char *temp;
	char *temp2;
	char *temp3;

	temp = ft_strdup(substring_ptrs[0]);
	free (substring_ptrs[0]);
	i = 1;
	while(substring_ptrs[i])
	{
		ft_printf("%s\n" , substring_ptrs[i]);
		temp2 = ft_strjoin(temp, substring_ptrs[i]);
		temp3 = ft_strdup(temp2);
		free(temp);
		free(temp2);
		free(substring_ptrs[i]);
		temp = ft_strdup(temp3);
		free(temp3);
		i++;
	}
	return (temp);
}


void	ft_expander(t_minishell *minishell)
{
	t_token *temp;
	int i;
	char *t;

	i = 1;
	temp = minishell->tokens;
	while(minishell->tokens)
	{
		if (!ft_strchr(minishell->tokens->token_value, '$') && !ft_strchr(minishell->tokens->token_value, '\"') && !ft_strchr(minishell->tokens->token_value, '\''))
			ft_printf("Token %i: %s OKEY\n", i, minishell->tokens->token_value);
		else
		{
			if (ft_strchr(minishell->tokens->token_value, '$') && !ft_strchr(minishell->tokens->token_value, '\"') && !ft_strchr(minishell->tokens->token_value, '\''))
			{
				ft_printf("Token %i: %s NECESITA SOLO EXPANSION\n", i, minishell->tokens->token_value);
				t = ft_split_expand(minishell, minishell->tokens->token_value);
				free(minishell->tokens->token_value);
				minishell->tokens->token_value = ft_strdup(t);
				free(t);
			}
			/*else if (ft_strchr(minishell->tokens->token_value, '$') && (ft_strchr(minishell->tokens->token_value, '\"') || ft_strchr(minishell->tokens->token_value, '\'')))
				ft_printf("Token %i: %s NECESITA GESTIONAR COMILLAS Y EXPANSION\n", i, minishell->tokens->token_value);*/
			else
			{
				ft_printf("Token %i: %s NECESITA SOLO GESTIONAR COMILLAS\n", i, minishell->tokens->token_value);
				t = split_substrings(minishell, minishell->tokens->token_value);
				free(minishell->tokens->token_value);
				minishell->tokens->token_value = ft_strdup(t);
				free(t);
			}
		}
		i++;
		minishell->tokens = minishell->tokens->next; 
	}
	minishell->tokens = temp;
	ft_print_tokens(minishell->tokens);
}
