/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/26 12:15:16 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *extract_quoted(char **start, int *size, char substrings[100][256]) {
    char quote = **start;
    char *end = ++(*start);
    while (*end && *end != quote) end++;
    if (*end != quote) return NULL;

    size_t len = end - *start + 2; // Incluir comillas
    if (len >= 256) return NULL;

    substrings[*size][0] = quote;
    ft_strcpy(&substrings[*size][1], *start);
    substrings[*size][len - 1] = quote;
    substrings[*size][len] = '\0';

    *start = end + 1;
    return substrings[(*size)++];
}

char *extract_unquoted(char **start, int *size, char substrings[100][256]) {
    char *end = *start;
    while (*end && *end != '"' && *end != '\'' && *end != ' ' && *end != '\t') end++;
    size_t len = end - *start;
    if (len >= 256) return NULL;

    ft_strcpy(substrings[*size], *start);
    substrings[*size][len] = '\0';
    *start = end;
    return substrings[(*size)++];
}

void process_substrings_else(t_minishell *minishell, char *substring_ptrs[100], int i , char *trim)
{
	char *expanded;

	//free(trim);
    trim = ft_strtrim(substring_ptrs[i], "\'");
    if (ft_strcmp(trim, substring_ptrs[i]) != 0)
        substring_ptrs[i] = trim;
	else if (ft_strchr(substring_ptrs[i], '$')) 
	{
        expanded = ft_split_expand(minishell, substring_ptrs[i]);
        substring_ptrs[i] = expanded;
    }
	free(trim);
}

void process_substrings(t_minishell *minishell, char *substring_ptrs[100])
{
    int i;
	char *trim;

	i = 0;
    while (substring_ptrs[i])
	{
        trim = ft_strtrim(substring_ptrs[i], "\"");
        if (ft_strcmp(trim, substring_ptrs[i]) != 0) 
		{ 
			//free(substring_ptrs[i]);
            substring_ptrs[i] = ft_strchr(trim, '$') ?
                                ft_split_expand(minishell, trim) : ft_strdup(trim);
        } 
		else 
			process_substrings_else(minishell, substring_ptrs, i , trim);
        if (trim)
			free(trim);
        i++;
    }
}

/*char *join_substrings(char *substring_ptrs[100]) 
{
    char *result;
	char *temp;

	result = substring_ptrs[0];
    for (int i = 1; substring_ptrs[i]; i++) {
        temp = ft_strjoin(result, substring_ptrs[i]);
        free(result);
        result = temp;
        //free(substring_ptrs[i]);
    }
    return result;
}*/

char *split_substrings(t_minishell *minishell, char *input)
{
    static char substrings[100][256];
    static char *substring_ptrs[100];
    int size = 0;
    char *start = input;
	int i;

	start = input;
    while (*start) 
	{
        if (size >= 100) 
			break;
        if (*start == '"' || *start == '\'')
            extract_quoted(&start, &size, substrings);
        else if (*start != ' ' && *start != '\t')
            extract_unquoted(&start, &size, substrings);
        else
            start++;
    }
    i = 0;
    while (i < size) {
        substring_ptrs[i] = substrings[i];
        i++;
    }
    process_substrings(minishell, substring_ptrs);
    return ft_split_expand_join(substring_ptrs);
}
