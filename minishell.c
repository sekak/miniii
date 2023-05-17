/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asekkak <asekkak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:28:46 by asekkak           #+#    #+#             */
/*   Updated: 2023/05/16 10:22:53 by asekkak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler_c(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_handler_quit(int sig)
{
	(void)sig;
}
void minishell_separate(t_mshel *shell,char *input,char ** env)
{
	int i;

	i = 0;
	while(input[i])
		i++;
	shell->store_input = ft_strdup(input);
	dup_env(shell, env);
	shell->exit_status = 0;
	shell->cmd_position = 0;
	shell->i = 0;
	shell->start = 0;
	shell->o = 0;
	shell->r = 0;
	shell->j= 0;
	shell->quotes= 0;
	shell->prev_symbol= 0;
	shell->exapnd_herdoc = malloc(sizeof(int) * (count_expand(shell, 0) + 1));
	shell->status = malloc(sizeof(int) * (count_arg(shell) + 2) );
}

void	minishell(char **env)
{
	char	*input;
	char	*tmp;
	t_mshel	*shel;
    
	signal(SIGQUIT, sigint_handler_quit);
	signal(SIGINT, sigint_handler_c);
	shel = malloc(sizeof(t_mshel));
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			exit(shel->exit_status);
		minishell_separate(shel,input, env);
		add_history(input);
		tmp = ft_strtrim(input, " ");
		if (check_syntax(tmp, shel))
			lexer(input, shel);
		else
			shel->exit_status = 2;
		free(tmp);
		free(input);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	minishell(env);
}
