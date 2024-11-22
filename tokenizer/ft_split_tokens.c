/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:01:14 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/22 16:07:51 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * The function "ft_split_and_update_tokens" combines the process of splitting 
 * a token and updating the types of tokens in the linked list.
 * 
 * @param t_token *token		A pointer to the token to be processed. This 
 *								function updates the list by splitting the 
 *								token and adjusting their types.
 * 
 * The function "ft_split_tokens" splits the value of the given token by a 
 * delimiter (e.g., '|') and creates a linked list of new tokens for each 
 * part. It modifies the original token and adds new tokens as needed.
 * 
 * @param t_token *token		A pointer to the token to be split.
 * @return t_token*				A pointer to the last token created in the 
 *								list or NULL if memory allocation fails.
 *
 * The function "ft_create_new_token" creates a new token, sets its value, 
 * links it to the previous token, and returns the newly created token.
 * 
 * @param t_token *current		A pointer to the current token, which will be 
 *								linked to the new token.
 * @param char *value			A string containing the value for the new token.
 * @return t_token*				A pointer to the newly created token, or NULL 
 *								if memory allocation fails.
 * 
 * The function "ft_update_tokens" iterates through a linked list of tokens
 * and updates their types based on their values and positions.
 * 
 * @param t_token *token		A pointer to the starting token in the 
 *								linked list. Each token's type will be updated.
 * 
 */

static void	ft_update_tokens(t_token *token)
{
	while (token)
	{
		ft_update_type_tokens(token);
		token = token->next;
	}
}



/*static t_token	*ft_create_new_token(t_token *current, char *value)
{
	current->next = malloc(sizeof(t_token));
	if (!current->next)
		return (NULL);
	current->next->prev = current;
	current = current->next;
	current->token_value = ft_strdup(value);
	current->next = NULL;
	return (current);
}*/

/*static int ft_count_nothing(t_token *token, int i, int *c)
{
	int j;

	j = 0;
	while(token->token_value[i] && token->token_value[i] != 32 && token->token_value[i] != '\"' && token->token_value[i] != '\'')
	{
		i++;
		j++;
	}
	if (j != 0)
		(*c)++;
	return (i);
}

static int ft_count_double(t_token *token, int i, int *c)
{
	int j;
	int f;

	f = 0;
	if (token->token_value[i] == '\"')
		{
			f = 1;
			i++;
		}
	j = 0;
	while(token->token_value[i] && f == 1)
	{
		if (token->token_value[i] == '\"')
			f = 0;
		i++;
		j++;
	}
	if (j != 0)
		(*c)++;
	return (i);
}

static int ft_count_simple(t_token *token, int i, int *c)
{
	int j;
	int f;

	f = 0;
	if (token->token_value[i] == '\'')
		{
			f = 1;
			i++;
		}
	j = 0;
	while(token->token_value[i] && f == 1)
	{
		if (token->token_value[i] == '\'')
			f = 0;
		i++;
		j++;
	}
	if (j != 0)
		(*c)++;
	return (i);
}

static char **ft_fill_sub(t_token *token, int c)
{
	char	**sub;
	int		i;
	int		j;
	int		k;
	int		f;
	int		start;
	int		end;

	sub = (char **)malloc((c+1) * sizeof(char*));
	if (!sub)
		return NULL;
	i = 0;
	k = 0;
	f = 0;
	while(k < c)
	{
		j = 0;
		while(token->token_value[i] && token->token_value[i] == 32)
			i++;
		start = i;
		while(token->token_value[i] && token->token_value[i] != 32 && token->token_value[i] != '\"' && token->token_value[i] != '\'')
			i++;
		end = i;
		if (end - start > 0)
			sub[k] = (char *)malloc((end - start + 1)*sizeof(char));
		i = start;
		while(token->token_value[i] && token->token_value[i] != 32 && token->token_value[i] != '\"' && token->token_value[i] != '\'')
		{
			sub[k][j] = token->token_value[i];
			i++;
			j++;
		}
		if (j != 0)
		{
			sub[k][j] = '\0';
			k++;
		}
		start = i;
		if (token->token_value[i] == '\"')
		{
			f = 1;
			i++;
		}
		j = 0;
		while(token->token_value[i] && f == 1)
		{
			if (token->token_value[i] == '\"')
				f = 0;
			i++;
			j++;
		}
		end = i;
		if (end - start > 0)
			sub[k] = (char *)malloc((end - start + 1)*sizeof(char));
		i = start;
		j = 0;
		if(token->token_value[i] && token->token_value[i] == '\"')
		{
			f = 1;
			sub[k][j] = token->token_value[i];
			i++;
			j++;
		}
		while (token->token_value[i] && f == 1)
		{
			if (token->token_value[i] == '\"')
				f = 0;
			sub[k][j] = token->token_value[i];
			i++;
			j++;
		}
		if (j != 0)
		{
			sub[k][j] = '\0';
			k++;
		}
		start = i;
		if (token->token_value[i] == '\'')
		{
			f = 1;
			i++;
		}
		j = 0;
		while(token->token_value[i] && f == 1)
		{
			if (token->token_value[i] == '\'')
				f = 0;
			i++;
			j++;
		}
		end = i;
		if (end - start > 0)
			sub[k] = (char *)malloc((end - start + 1)*sizeof(char));
		i = start;
		j = 0;
		if(token->token_value[i] && token->token_value[i] == '\'')
		{
			f = 1;
			sub[k][j] = token->token_value[i];
			i++;
			j++;
		}
		while (token->token_value[i] && f == 1)
		{
			if (token->token_value[i] == '\'')
				f = 0;
			sub[k][j] = token->token_value[i];
			i++;
			j++;
		}
		if (j != 0)
		{
			sub[k][j] = '\0';
			k++;
		}
	}
	sub[k] = NULL;
	return (sub);
}

static char ft_find_special_char(char *s)
{
	int i;

	i=0;
	while(s[i])
	{
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
			return (s[i]);
		i++;
	}
	return ('\0');
}

static char	*ft_expand_var(t_minishell *minishell, char *sub)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while(sub[i])
	{
		if(sub[i] == '$')
			c++;
		i++;
	}
	ft_printf("%i\n",c);
	ft_printf("%s\n", minishell->list_envp->value);
	return (sub);
	
}

static char *ft_expand_simplequote(char *exp_token, char *sub)
{
	char *trim;
	char *temp;

	trim = ft_strtrim(sub, "\'");
	if(exp_token == NULL)
	{
		if (ft_strcmp(trim, sub) != 0)
			exp_token = ft_strdup(trim);
	}
	else
	{
		if (ft_strcmp(trim, sub) != 0)
		{
			temp = ft_strdup(exp_token);
			free(exp_token);
			exp_token = ft_strjoin(temp, trim);
			free(temp);
		}
	}
	if (ft_strcmp(trim, sub) != 0)
		free(sub);
	free(trim);
	return (exp_token);
}

static char *ft_expand_noquote(t_minishell *minishell, char *exp_token, char *sub)
{
	char *temp;

	if(exp_token == NULL)
	{
		if (!ft_strchr(sub, '$'))
			exp_token = ft_strdup(sub);
		else
			exp_token = ft_expand_var(minishell, sub);
	}
	else
	{
		if (!ft_strchr(sub, '$'))
		{
			temp = ft_strdup(exp_token);
			free(exp_token);
			exp_token = ft_strjoin(temp, sub);
			free(temp);
		}
		else
		{
			temp = ft_strdup(exp_token);
			free(exp_token);
			exp_token = ft_strjoin(temp, ft_expand_var(minishell, sub));
			free(temp);
		}
	}
	free(sub);
	return (exp_token);
}

static void ft_expand_token(char **sub, t_token *token, t_minishell *minishell)
{
	char *exp_token;
	int i;

	i = 0;
	exp_token = NULL;
	while(sub[i])
	{
		ft_printf("%s\n", sub[i]);
		i++;
	}
	if (!exp_token && !ft_strchr(sub[0], '\'') && !ft_strchr(sub[0], '\"'))
		exp_token = ft_expand_noquote(minishell, exp_token, sub[0]);
	else
		exp_token = ft_expand_simplequote(exp_token, sub[0]);
	i = 1;
	while (sub[i])
	{
		if (exp_token && !ft_strchr(sub[i], '\'') && !ft_strchr(sub[i], '\"'))
			exp_token = ft_expand_noquote(minishell, exp_token, sub[i]);
		else
			exp_token = ft_expand_simplequote(exp_token, sub[i]);
		i++;
		ft_printf("%s\n", exp_token);
	}
	free(token->token_value);
	free(sub);
	token->token_value = ft_strdup(exp_token);
	ft_printf("%s\n", token->token_value);
	ft_printf("%s\n", exp_token);
	free(exp_token);
}

static char **ft_sub_one_value(t_token *token)
{
	char **sub;

	sub = (char **)malloc(2*sizeof(char*));
	if (!sub)
		return NULL;
	sub[0] = ft_strdup(token->token_value);
	sub[1] = NULL;
	return (sub);
}

static char **ft_divide_token(t_token *token, t_minishell *minishell)
{
	int 	i;
	int 	c;
	char	**sub;

	i = 0;
	c = 0;
	sub = NULL;
	while (token->token_value[i])
	{
		while(token->token_value[i] && token->token_value[i] == 32)
			i++;
		i = ft_count_nothing(token, i, &c);
		i = ft_count_double(token, i, &c);
		i = ft_count_simple(token, i, &c);
	}
	if (c == 1)
		sub = ft_sub_one_value(token);
	else
		sub = ft_fill_sub(token, c);
	//ft_expand_token(sub, token, minishell);
	ft_printf("%s\n", minishell->list_envp->value);
	return (sub);

}*/

/*static t_token	*ft_split_tokens(t_token *token, t_minishell *minishell)
{
	int		i;
	char	**sub_tokens;
	t_token	*current;

	sub_tokens = NULL;
	ft_printf("%s\n", minishell->list_envp->value);
	if (ft_strchr(token->token_value, '|'))
		sub_tokens = ft_split(token->token_value, '|');
	else if (ft_strchr(token->token_value, '$'))
		sub_tokens = ft_divide_token(token, minishell);
	if (!sub_tokens)
		return (token);
	current = token;
	i = 0;
	while (sub_tokens[i])
	{
		free(current->token_value);
		current->token_value = ft_strdup(sub_tokens[i++]);
		if (!current->token_value)
			return (ft_free_split(sub_tokens), NULL);
		if (sub_tokens[i])
		{
			current = ft_create_new_token(current, sub_tokens[i]);
			if (!current)
				return (ft_free_split(sub_tokens), NULL);
		}
	}
	return (ft_free_split(sub_tokens), token);
}*/

void	ft_split_and_update_tokens(t_token *token, t_minishell *minishell)
{
	//t_token	*last_token;

	//last_token = ft_split_tokens(token, minishell);
	ft_update_tokens(token);
	ft_printf("%s\n", minishell->list_envp->value);
	//ft_update_tokens(token);
}