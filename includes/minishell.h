/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:35:55 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/11/18 11:51:42 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ============================================================================
// Libraries
// ============================================================================
# include <unistd.h>			// for write...
# include <stdlib.h>			// for typedef, malloc...
# include <math.h>				// for PI, etc.
# include <fcntl.h>				// for open, O_RDONLY, etc.
# include <stdio.h>				// for printf...
# include <stdbool.h>			// for booleans...
# include <signal.h>			// for SIGINT, SIGQUIT...
# include <readline/readline.h> // for readline...
# include <readline/history.h>	// for clear_history...
# include <sys/wait.h> 			// for wait, waitpid, WIFSIGNALED(status)...
# include <string.h>			// for strchr, strcpy, etc.
# include <termios.h>			// for terminal I/O interfaces.

// ============================================================================
// Define ECHOCTL (if it's not already defined)
// ============================================================================
# ifndef ECHOCTL
#  define ECHOCTL 0001000
# endif

// ============================================================================
// Access to my libraries
// ============================================================================
# include "colors.h"
# include "examft.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include "get_next_line.h"
# include "libft.h"
# include "ft_macros.h"

// ============================================================================
// Structures
// ============================================================================
typedef enum e_tok_typ_enum
{
	TOKEN_EMPTY,
	TOKEN_REDIR_STDIN,
	TOKEN_REDIR_STDOUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_COMMAND,
	TOKEN_OPTION,
	TOKEN_ARG,
	TOKEN_PIPE,
}					t_tok_typ_enum;

typedef struct s_ast
{
	t_tok_typ_enum	type;
	char			*value;
	struct s_ast	*right;
	struct s_ast	*left;
}					t_ast;

typedef struct s_signal
{
	pid_t			pid;
	int				sigint;
	int				sigquit;
	int				exit;
	int				start;
	char			*dupdirprompt;
}					t_signal;

typedef struct s_token
{
	t_tok_typ_enum	token_type;
	char			*token_value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}					t_envp;

typedef struct s_minishell
{
	char			**envp;
	t_envp			*list_envp;
	int				stdin;
	int				stdout;
	char			*line;
	t_token			*tokens;
	int				exit;
	char			*dirprompt;
}					t_minishell;

// ============================================================================
// Global variable
// ============================================================================
extern	t_signal g_signals;

// ============================================================================
// Management errors
// ============================================================================
void		ft_manage_err(const char *err);

// ============================================================================
// Release funtions
// ============================================================================
void		ft_free_envp_list(t_envp *head);
void		ft_free_minishell(t_minishell *minishell);
void		ft_free_split(char **sub_tokens);
void		ft_free_tokens(t_token *token);
void		ft_free_ast(t_ast *ast);

// ============================================================================
// Initialization functions
// ============================================================================
void		ft_enable_print(void);
void		ft_handle_eof(char *line);
t_envp		*ft_init_list_envp(char **envp);
void		ft_init_minishell(t_minishell *minishell);
void		ft_init_struc_sig(t_signal *signals);
void		ft_init_signals(t_minishell *minishell);
void		ft_init_envp(t_minishell *minishell, char **envp);

// ============================================================================
// Builtins functions
// ============================================================================
void		ft_cd(t_minishell *minishell, t_ast *ast);
void		ft_echo(t_minishell *minishell, t_ast *ast);
void		ft_env(t_minishell *minishell);
void		ft_export(t_minishell *minishell, t_ast *ast);
void		ft_pwd(void);
void		ft_unset(t_minishell *minishell, t_ast *ast);

// ============================================================================
// Tokenizer functions
// ============================================================================
void		ft_check_empty_line(t_minishell *minishell);
int			ft_checker_quotes_unclosed(t_minishell *minishell);
int			ft_checker_quotes(char *line, int lenght);
int			ft_check_operators(char *line, int index);
void		ft_print_tokens(t_token *tokens);
void		ft_skip_spaces(char *line, int *index);
void		ft_split_and_update_tokens(t_token *token);
int			ft_token_size(char *line, int *index);
void		*ft_tokenizer(t_minishell *minishell);
// t_ast		*ft_tokenizer(t_minishell *minishell);
void		ft_update_type_tokens(t_token *token);

// ============================================================================
// Utils functions
// ============================================================================
void		ft_change_env(t_minishell *minishell, const char *str1, \
			const char *str2);
void		ft_dirprompt(t_minishell	*minishell);
char		*ft_find_dir(t_minishell *minishell, const char *str);
void		ft_print_init(void);
t_ast		*ft_ast(t_minishell *minishell);

// ============================================================================
// Exec functions
// ============================================================================
char		**ft_path(t_minishell *minishell);
void		ft_cmdexe(t_minishell *minishell, t_ast *ast);
int 		ft_exec(t_minishell *minishell, t_ast *ast);
void		ft_exec_pipe(t_minishell *minishell, t_ast *ast);
char		*ft_cmd_action(char **path, char *arg);
char		*ft_cmd_maker(t_minishell *minishell, t_ast *ast);
char		**ft_arg_maker(t_ast *ast);
void		ft_exec_ast(t_minishell *minishell, t_ast *ast);
void		ft_free_ast(t_ast *ast);
void		ft_exec_redir_in(t_minishell *minishell, t_ast *ast);
void		ft_exec_redir_out(t_minishell *minishell, t_ast *ast);
void		ft_exec_redir_append(t_minishell *minishell, t_ast *ast);

#endif
