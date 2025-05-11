/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-19 16:46:09 by speladea          #+#    #+#             */
/*   Updated: 2024-11-19 16:46:09 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	clear_exit(t_minishell *minishell)
{
	free_all_executions(minishell);
	if (minishell->exec.stdin_backup > 0)
	{
		close(minishell->exec.stdin_backup);
		minishell->exec.stdin_backup = -1;
	}
	if (minishell->exec.stdout_backup > 0)
	{
		close(minishell->exec.stdout_backup);
		minishell->exec.stdout_backup = -1;
	}
	free(minishell->prompt);
	if (minishell->env_link)
		clear_link_env(&minishell->env_link);
	if (minishell->token)
	{
		clear_link_token(&minishell->token);
		minishell->token = NULL;
	}
}

bool	exit_minishell(t_minishell *minishell)
{
	if (!minishell->prompt)
	{
		printf("\033[1;37;5;41mC0NNECTI0N L0ST\033[0m\n");
		clear_exit(minishell);
		return (true);
	}
	return (false);
}

void	init_minishell(t_minishell *minishell, char **ev)
{
	minishell->pars.link = 0;
	minishell->save_pipe_in = -1;
	minishell->execution = NULL;
	minishell->error_stdout = false;
	minishell->exec_count = 0;
	g_exit_loop = 0;
	minishell->fd.error_stdout = 0;
	minishell->exec.exit_code = 0;
	minishell->token = NULL;
	minishell->env_link = NULL;
	minishell->env_null = NULL;
	minishell->prompt = NULL;
	minishell->status = false;
	minishell->token_quotes = false;
	minishell->syntax = false;
	minishell->cmd.cmd_path = NULL;
	minishell->exec.pid = -1;
	minishell->exec.exit_code = 0;
	minishell->exec.stdin_backup = dup(STDIN_FILENO);
	minishell->exec.stdout_backup = -1;
	init_env(minishell, ev);
	main_signal(minishell);
}

void	sig_exit_code(int signal)
{
	(void)signal;
	g_exit_loop = signal + 128;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	prompt_init(t_minishell *minishell)
{
	char	*prompt;

	signal(SIGINT, sig_exit_code);
	prompt = "\001\033[32m\002GhostInTheShell>\001\033[0m\002 ";
	rl_set_prompt(prompt);
	minishell->prompt = NULL;
	minishell->prompt = readline(prompt);
	if (g_exit_loop)
	{
		minishell->exec.exit_code = g_exit_loop;
		g_exit_loop = 0;
	}
}
