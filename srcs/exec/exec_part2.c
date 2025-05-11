/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_part2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:06:19 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/18 20:51:49 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	children_dup_fd(t_minishell *minishell, t_execution *execution)
{
	if (dup_fd(minishell, execution, NULL))
	{
		free_all_executions(minishell);
		clear_link_env(&(minishell->env_link));
		clear_link_token(&(minishell->token));
		exit(1);
	}
}

void	fork_exec(t_minishell *minishell, t_token *token, \
		t_execution *execution, int pipe_fds[2])
{
	second_sig();
	minishell->pid = fork();
	if (!minishell->pid)
	{
		dup_out(minishell, pipe_fds);
		children_dup_fd(minishell, execution);
		while (token && (token->token != COMMAND && token->token != BUILTIN))
		{
			if (token->token == PIPE)
			{
				free_all_executions(minishell);
				clear_link_env(&(minishell->env_link));
				clear_link_token(&(minishell->token));
				exit(0);
			}
			token = token->next;
		}
		if (token->token == BUILTIN)
			ft_pipe_builtin(minishell, token, execution, NULL);
		else if (token->token == COMMAND)
			execout(minishell, execution);
		exit(0);
	}
	dup2(minishell->exec.stdout_backup, 1);
}

void	check_token_is_null(t_minishell *minishell, t_token *token)
{
	if (!token)
	{
		free_all_executions(minishell);
		clear_link_env(&(minishell->env_link));
		clear_link_token(&(minishell->token));
		exit(0);
	}
}

void	dup_save_in(t_minishell *minishell)
{
	if (minishell->exec.stdin_backup != -1)
	{
		close(minishell->exec.stdin_backup);
		minishell->exec.stdin_backup = -1;
	}
	if (minishell->save_pipe_in != -1)
	{
		if (dup2(minishell->save_pipe_in, STDIN_FILENO) == -1)
		{
			perror("dup2 stdout");
			minishell->exec.exit_code = 1;
			free_resseource_children(minishell, NULL);
			exit(1);
		}
		close(minishell->save_pipe_in);
	}
}

void	last_exec(t_minishell *minishell, t_token *token, \
	t_execution *execution)
{
	minishell->pid = fork();
	if (minishell->pid == 0)
	{
		dup_save_in(minishell);
		dup2(minishell->exec.stdout_backup, STDOUT_FILENO);
		close(minishell->exec.stdout_backup);
		minishell->exec.stdout_backup = -1;
		children_dup_fd(minishell, execution);
		minishell->exec.stdout_backup = -1;
		while (token && (token->token != COMMAND \
			&& token->token != BUILTIN))
			token = token->next;
		check_token_is_null(minishell, token);
		if (token->token == BUILTIN)
			ft_pipe_builtin(minishell, token, execution, NULL);
		else if (token->token == COMMAND)
			execout(minishell, execution);
	}
	close(minishell->exec.stdout_backup);
	minishell->exec.stdout_backup = -1;
	if (minishell->save_pipe_in != -1)
		close(minishell->save_pipe_in);
	minishell->save_pipe_in = -1;
}
