/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 08:21:18 by drosales          #+#    #+#             */
/*   Updated: 2024/10/09 17:28:52 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdint.h>
# include <signal.h>
# include "libft.h"
# include "ft_printf.h"

/* DATA STRUCTS */

typedef enum
{
    TOKEN_COMMAND,              /* Comando a ejecutar */
    TOKEN_ARGUMENT,             /* Argumento */
    TOKEN_OPERATOR,             /* Operadores */
    TOKEN_PATH                  /* Elemento no reconocido */
}Token_type;

typedef struct
{
    Token_type  token_type;      /* Para saber el tipo de token */
    char        *token_value;   /* Valor del token */
}Token;

typedef struct n_list           /* Estructura para lista enlazada */
{
    Token           token;      /* Estructura referente a tokens */
    struct n_list   *next;      /* Puntero al siguiente nodo */
    struct n_list   *prev;
}token_list;

typedef struct s_env            /* Estructura para variables de entorno*/
{
    char    *key;
    char    *value;
    struct s_env    *next;
}   t_env;

typedef struct s_mini           /* Estructura programa minishell*/
{
    char    **env;              /* Variables de entorno */
    t_env   *list_env;          /* Puntero a mi lista de variables de entorno */    
    int     stdin;              /* Entrada en estandar */
    int     stdout;             /* Salida estándar */    
    char    *line;              /* Línea */
    Token   *tokens;             /* Puntero a mi lista de tokens */
}   t_mini;

/* AST STRUCT */

typedef struct s_ast
{
    Token_type      type;       // TYPE OF NODE (TOKEN_ARGUMENT...)
    char            *value;     // VALUE OF NODE (PIPE = '|'...)
    struct s_ast    *right;     // RIGHT NODE
    struct s_ast    *left;      // LEFT NODE
}   t_ast;

/** FUNCTIONS **/

/* Init minishell */

t_mini  *init_mini(char **env);

/* Init environment */

t_env  *init_env_list(char **envp);

/* Lexer y tokenizer */

token_list      *ft_lexer(char  *input);
token_list      *ft_new_node_tokens(Token_type type, const char *value);
Token           ft_adding_tokens(token_list **head_list, const char *value);
char            *ft_take_element_between_quotes(char *input, int *i);
Token_type      ft_get_operator_type(char *operator);
void            ft_lexing_words(char *input, int *i, token_list **tokens);
void            ft_lexing_operators(char *input, int *i, token_list **tokens);
void            ft_lexing_double_operators(const char *input, int *i, token_list **tokens);
int             ft_strnlen(const char *str, size_t maxlen);
char	        *ft_strndup(const char *str, size_t n);
int             ft_isspace(int c);
int             ft_is_quote(int c);
int             ft_isallsimbols(int c);
int             ft_strcmp(const char *s1, const char *s2);
int             ft_is_operator(const char *value);
int             ft_is_command(const char *value);
int             ft_is_path(const char *value);
Token_type      ft_type_of_tokens(char *value);

/* Parsing AST */

t_ast           *ft_parsing_cmd(token_list *tokens);
t_ast           *ft_parsing_operator(token_list *tokens, t_ast *left_cmd);
t_ast           *ft_parsing_path(token_list *tokens);
t_ast           *ft_parsing_args(token_list *tokens);
t_ast           *ft_ast_new_node(Token_type type, char *value);
t_ast           *ft_making_ast(token_list *tokens);

#endif