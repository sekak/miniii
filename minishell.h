/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:29:14 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/16 10:22:48 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_heredoc
{
	int				her_doc;
	char			*cmd;
	char			**delemiter;
}					t_heredoc;

typedef struct s_redr
{
	char			**input;
	char			**output;
	char			**in_file;
	char			**out_file;
	int				*input_expanded;
	int				*output_expanded;
	int				old_output;
	int				old_input;
	int				in;
	int				out;
	t_heredoc		heredoc;
	int				ambugius;
}					t_redr;

typedef struct s_cmd
{
	char			*cmd;
	int				flags;
	char			**args;
	t_redr			redir;
	int				error;
	char			*error_file;
}					t_cmd;

typedef struct s_mshel
{
	t_cmd			**cmd;
	char			**env;
	char			**x_env;
	int				pipes;
	int				cmd_number;
	int				exit_status;
	int				*exapnd_herdoc;
	int				*status;
	int				stat;
	int				hdoc_num;
	char			*store_input;
	int				cmd_position;
	int				start;
	int				i;
	int				r;
	int				o;
	int				j;
	int 			quotes;
	int 			prev_symbol;
}					t_mshel;

//************* lexer **************

typedef struct s_table
{
	char			*name_file;
	char			*token_redire;
	int				redire;
}					t_table;

typedef struct s_env
{
	char			*dollar;
	int				i;
}					t_env;

typedef struct s_lexer
{
	char			**str;
	struct s_lexer	*next;
	char			*cmd;
	int				flag;
	int				pipe;
	t_table			*table;
	t_env			*env;
}					t_lexer;
//*****************************

//* *********parser****************
void				parser(t_lexer *lst, t_mshel *shel, char *input);
//********************************
t_lexer				*add_node(char **content, int start, int end);
void				ft_add_back(t_lexer **lst, t_lexer *new);
void				ft_sringcpy(char **str, char *content);
void				function(void);
void				transfer_to_array(t_lexer *lexer, int size_arrays,
						t_mshel *shel);

//***********piping***********
void				close_all_pipes(int (*pipe)[2], int cmd_numbers);
void				pipe_and_start(t_mshel *mshel);
int					redirect_to_pipe(t_mshel *shel, int (*pipe)[2], int i,
						int red_status, int status);
//****************************

//*********execution**********
void				execute_cmd(t_mshel *shel, int (*pipe)[2], int cmd_index,
						int status);
void				ech_o(t_mshel *shel, int i);
void				execute_shell(char **cmd, t_mshel *shel);
void				p_w_d(void);
int					c_d(t_mshel *shel, char *a);
void				print_env(t_mshel *shel, int stat);
char				*ft_getenv(t_mshel *mshel, char *a);
int					ft_export(t_mshel *shel, int cmd_index);
void				dup_env(t_mshel *shel, char **env);
void				ft_unset(t_mshel *shel, int cmd_index);
void				run_cmd(t_mshel *shel, int cmd_index, char *cmd);
//****************************

//*******redirection**********
int					redirect_input(t_mshel *mshel, int cmd_index, int status);
int					redirect_output(t_mshel *mshel, int cmd_index);
int					check_redirect_place(int in, int out);
void				ft_heredoc(int cmd_index, t_mshel *shel);
//****************************

//********utils***************
void				print_errors(char *a);
//****************************

char				*check_expanding(t_mshel *shel, char *str);
char				**better_parsing(char *a, t_mshel *shel);
long				checking_overwrite(t_mshel *shel, int cmd_index);
void				error_to_print(int error, char *file);
char				*parsse_redirection(char *input, int *s);
char				*substr(char const *s, unsigned int start, size_t len);

////testing
void				hendel_no_quotes(t_mshel *shel, char **new, int *j,
						char *tmp);
void				handel_sing_quote(t_mshel *shel, char *a, int *i,
						char **new, int *j);
int					check_space_place(char *a);
char				*ft_strtr(char *s1, char *set);
int					theres_is_red(char *a);
void				handel_double_quotes(t_mshel *shel, char *a, int *i, int *j,
						char **new);
void				handel_no_quotes_expand(char *tempo, char **new, int *j,
						char a, t_mshel *shel);
void				hendel_no_quotes_spand_j(t_mshel *shel, char *tempo,
						char **new, int *j, char a);
void				hande_no_quoet_expand_n(t_mshel *shel, char **new, int *j,
						char *a, int check_point, int i);
int					array_lenth(char **a);
void				open_n_close_p(int (*pipes)[2], int cs, int p_number);
void	free_lexer(t_lexer *lexer);
void	free_all(t_mshel *shel, int size);
int	exit_function(char **a, t_mshel *shel);


//check_syntax.c
int check_syntax(char *a, t_mshel *shel);


//lexer part
void lexer(char *input, t_mshel *shel);

//node_lk_list
t_lexer *add_node(char **content, int start, int end);
void ft_add_back(t_lexer **lst, t_lexer *new);


// file parser/parser.c
int check_redirection(t_lexer *lexer);
int check_flag(t_lexer *head);
int check_cmd(t_lexer *head);
int check_pipe(t_lexer *head);
char *choose_red(char *red);
char *all_cmd(char *cmd);
char *all_redir(char *redir);
 int	find_dollar(char *a);
 char *check_expanding(t_mshel *shel, char *str);

//count malloc
int  count_arg(t_mshel *mshel);
int  count_expand(t_mshel *mshel, int num);



//separate_copy_to_array
void transfer_herdoc_args(t_mshel *shel, int i, t_lexer *head);
void alloc_redirect(t_mshel *shel, int i, char **a);
void transfer(t_lexer *lexer, t_mshel *shel, int k, int flag);
int find_cmd(char **a, t_mshel *shel);



//utils_transfer
void transfer_herdoc_args(t_mshel *shel, int i , t_lexer *head);
void transfer_redirection(t_lexer *lexer, t_mshel *shel, int k);

//transfer input output
void	transfer_input(t_lexer *lexer, t_mshel *shel, int k);
void transfer_output(t_lexer *lexer, t_mshel *shel, int k);

#endif
