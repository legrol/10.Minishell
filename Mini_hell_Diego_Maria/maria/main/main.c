/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:01:18 by drosales          #+#    #+#             */
/*   Updated: 2024/10/09 17:32:25 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static void handle_sigint(int sig) 
{
    (void)sig;

    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static void ft_print_ast(t_ast *node)
{
    if (!node)
        return;

    if (node->type == TOKEN_COMMAND)
        printf("Comando: %s\n", node->value);
    else if (node->type == TOKEN_ARGUMENT)
        printf("Argumento: %s\n", node->value);
    else if (node->type == TOKEN_OPERATOR)
        printf("Operador: %s\n", node->value);
    else if (node->type == TOKEN_PATH)
        printf("Archivo/Path: %s\n", node->value);
    if (node->left)
        printf("  └ Left: ");
    ft_print_ast(node->left);
    if (node->right)
        printf("  └ Right: ");
    ft_print_ast(node->right);
}


static void print_tokens(token_list *tokens) 
{
    token_list *current = tokens;
    while (current) 
    {
        ft_printf("####Tokenizing in progress...####\n");
        ft_printf("Token: [%s]\n Type: [%d]\n\n", current->token.token_value, current->token.token_type);
        current = current->next;
    }
}

int main(int ac, char **argv, char **env) 
{
    (void)ac;
    (void)argv;
    t_mini  *minishell;
    token_list *tokens;
    t_env   *current; // Esto es para que lo printee (Luego lo borramos)
    t_ast   *cmd_ast;


    ft_printf("Welcome to marigome a drosales Minishell!\n\n");
    minishell = init_mini(env);
    if (!minishell)
        return (EXIT_FAILURE);
    current = minishell->list_env;
    while (current) // Bucle para que lo muestre por pantalla (Borrar)
    {
        printf("Variable: %s=%s\n", current->key, current->value);
        current = current->next;
    }
    signal(SIGINT, handle_sigint);
    while (1) 
    {
        minishell->line = readline("minishell@drosales ~ ");
        if (!minishell->line)
            continue ;
        if (*minishell->line)
            add_history(minishell->line);

        tokens = ft_lexer(minishell->line);
        printf("Tokens generados:\n");
        print_tokens(tokens);
        // Parsear el comando y generar AST
        cmd_ast = ft_making_ast(tokens);
        if (cmd_ast)
        {
            printf("AST generado:\n");
            ft_print_ast(cmd_ast);  // Imprimir el AST generado
        }
        else
        {
            printf("Error al generar el AST\n");
        }
        // Liberar la memoria (tokens y AST)
        //free_token_list(tokens);
        //free_ast(cmd_ast);
        free(minishell->line);
    }
    clear_history();
    return (0);
}