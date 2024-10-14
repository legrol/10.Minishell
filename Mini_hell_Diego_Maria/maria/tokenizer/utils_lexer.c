/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:53:53 by drosales          #+#    #+#             */
/*   Updated: 2024/10/08 12:39:40 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

token_list  *ft_new_node_tokens(Token_type type, const char *value)
{
    token_list  *new_node;

    new_node = (token_list *)malloc(sizeof(token_list));
    if (!new_node)
        return (NULL);
    new_node->token.token_value = ft_strdup(value);
    new_node->token.token_type = type;
    new_node->next = NULL;
    new_node->prev = NULL;
    return (new_node);
}

Token ft_adding_tokens(token_list **head_list, const char *value)
{
    token_list  *new_node;
    token_list  *current;
    Token_type  type;

    type = ft_type_of_tokens((char *)value);
    new_node = ft_new_node_tokens(type, value);
    if (new_node == NULL)
    {
        ft_printf("Error en el nuevo nodo!");
        exit(EXIT_FAILURE);
    }
    if (*head_list == NULL)
    {
        *head_list = new_node;
        return (new_node->token);
    }
    current = *head_list;
    while (current->next) 
        current = current->next;
    current->next = new_node;
    new_node->prev = current;
    return (new_node->token);
}

Token_type ft_type_of_tokens(char *value)
{
    if (ft_is_command(value))
        return (TOKEN_COMMAND);
    else if (ft_is_operator(value))
        return (TOKEN_OPERATOR);
    else if (ft_is_path(value))
        return (TOKEN_PATH);
    else
        return (TOKEN_ARGUMENT);
}
