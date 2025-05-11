/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:15:51 by simonp            #+#    #+#             */
/*   Updated: 2025/02/11 21:58:01 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	close_pipe_fd(int pipe_fds[2])
{
	if (pipe_fds[0] != -1)
		close(pipe_fds[0]);
	if (pipe_fds[1] != -1)
		close(pipe_fds[1]);
	pipe_fds[0] = -1;
	pipe_fds[1] = -1;
}

void	dup_in(t_minishell *minishell, int pipe_fds[2])
{
	if (pipe_fds[1] != -1)
	{
		close(pipe_fds[1]);
		pipe_fds[1] = -1;
	}
	if (minishell->save_pipe_in != -1)
		close(minishell->save_pipe_in);
	minishell->save_pipe_in = pipe_fds[0];
}

void	dup_out(t_minishell *minishell, int pipe_fds[2])
{
	close_stdin(minishell);
	if (minishell->save_pipe_in != -1)
	{
		if (dup2(minishell->save_pipe_in, STDIN_FILENO) == -1)
		{
			write_str("Fail malloc\n", 2);
			minishell->exec.exit_code = 1;
			free_resseource_children(minishell, pipe_fds);
			exit(1);
		}
		close(minishell->save_pipe_in);
	}
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
	{
		write_str("Fail malloc\n", 2);
		minishell->exec.exit_code = 1;
		free_resseource_children(minishell, pipe_fds);
		exit(1);
	}
	close_pipe_fd(pipe_fds);
	close_stdout(minishell);
}

bool	create_pipe(t_minishell *minishell, int pipe_fds[2])
{
	if (!pipe(pipe_fds))
		return (false);
	write_str("\033[0;31mError\033[0m: broken pipe\n", 2);
	minishell->exec.exit_code = 32;
	return (true);
}

void	exec_cmd_and_builtin(t_minishell *minishell, t_token *tmp)
{
	if (dup_fd(minishell, minishell->execution, NULL))
		return ;
	if (tmp->token == BUILTIN)
	{
		ft_do_builtin(minishell, tmp);
		dup2(minishell->exec.stdout_backup, STDOUT_FILENO);
		close(minishell->exec.stdout_backup);
		minishell->exec.stdout_backup = -1;
		return ;
	}
	if (tmp->token != COMMAND)
		return ;
	minishell->pid = fork();
	if (!minishell->pid)
	{
		close_std(minishell);
		execout(minishell, minishell->execution);
		close(minishell->exec.stdout_backup);
		minishell->exec.stdout_backup = -1;
		exit(0);
	}
	get_exit_status(minishell);
	dup2(minishell->exec.stdout_backup, STDOUT_FILENO);
	close(minishell->exec.stdout_backup);
}
