/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:12:03 by simonp            #+#    #+#             */
/*   Updated: 2025/02/17 17:41:46 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	free_command_args(t_execution *exec)
{
	int	j;

	j = 0;
	if (exec->cmd != NULL)
	{
		free(exec->cmd);
		exec->cmd = NULL;
	}
	if (exec->args != NULL)
	{
		while (exec->args[j] != NULL)
		{
			free(exec->args[j]);
			j++;
		}
		free(exec->args);
		exec->args = NULL;
	}
}

void	free_redirections(t_execution *exec)
{
	int	j;

	j = 0;
	if (exec->heredoc_fds != NULL)
	{
		while (j < exec->heredoc_count)
		{
			close(exec->heredoc_fds[j++]);
		}
		free(exec->heredoc_fds);
		exec->heredoc_fds = NULL;
	}
	j = 0;
	if (exec->redirections != NULL)
	{
		while (j < exec->redirection_count)
		{
			if (exec->redirections[j].fd != -1)
				close(exec->redirections[j].fd);
			j++;
		}
		free(exec->redirections);
		exec->redirections = NULL;
	}
}

void	free_execution(t_execution *exec, int cmd_count)
{
	int	i;

	i = 0;
	if (exec == NULL)
		return ;
	while (i < cmd_count)
	{
		free_command_args(&exec[i]);
		free_redirections(&exec[i]);
		if (exec[i].pipe_in != 0)
		{
			close(exec[i].pipe_fd[0]);
			exec[i].pipe_fd[0] = -1;
		}
		if (exec[i].pipe_out != 0)
		{
			close(exec[i].pipe_fd[1]);
			exec[i].pipe_fd[1] = -1;
		}
		i++;
	}
	free(exec);
}

void	free_all_executions(t_minishell *minishell)
{
	if (minishell == NULL || minishell->execution == NULL)
		return ;
	free_execution(minishell->execution, minishell->exec_count);
	minishell->exec_count = 0;
	minishell->execution = NULL;
}

void	reset(t_minishell *minishell)
{
	if (minishell->save_pipe_in != -1)
	{
		close(minishell->save_pipe_in);
		minishell->save_pipe_in = -1;
	}
	minishell->error_stdout = false;
	free_all_executions(minishell);
	g_exit_loop = 0;
	minishell->fd.error_stdout = 0;
	main_signal(minishell);
	dup2(minishell->exec.stdin_backup, STDIN_FILENO);
	minishell->exec.stdout_backup = -1;
	minishell->syntax = false;
	minishell->status = false;
	free(minishell->prompt);
	minishell->prompt = NULL;
	minishell->token_quotes = false;
	minishell->status = false;
	minishell->syntax = false;
	if (minishell->token)
	{
		clear_link_token(&minishell->token);
		minishell->token = NULL;
	}
}
