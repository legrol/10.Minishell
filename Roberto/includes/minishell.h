/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdel-olm <rdel-olm@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:35:55 by rdel-olm          #+#    #+#             */
/*   Updated: 2024/10/15 23:27:00 by rdel-olm         ###   ########.fr       */
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
	TOKEN_ARG,
	TOKEN_PIPE,
}					t_tok_typ_enum;

typedef struct s_signal
{
	pid_t			pid;
	int				sigint;
	int				sigquit;
	int				exit;
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
// Initialization functions
// ============================================================================
t_minishell	*ft_init_minishell(char **envp);
void		ft_init_struc_sig(t_signal *signals);
void		ft_init_signals(void);
t_envp		*ft_init_list_envp(char **envp);

// ============================================================================
// Builtins functions
// ============================================================================
void		ft_cd(t_minishell *minishell);
void		ft_env(t_minishell *minishell);
void		ft_pwd(t_minishell *minishell);

// ============================================================================
// Initialization functions
// ============================================================================
void		ft_print_init(void);
void		ft_dirprompt(t_minishell	*minishell);
char		*ft_workingdir(void);
char		*ft_find_dir(t_minishell *minishell, const char *str);
void		ft_change_env(t_minishell *minishell, const char *str1, \
			const char *str2);

#endif
