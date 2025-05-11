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

bool	get_fd(t_minishell *minishell, t_redirection redir, int pipe_fds[2])
{
	if (redir.type == 0)
	{
		if (dup2(redir.fd, STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			minishell->exec.exit_code = 1;
			free_resseource_children(minishell, pipe_fds);
			return (true);
		}
	}
	else if (redir.type == 1)
	{
		if (dup2(redir.fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			minishell->exec.exit_code = 1;
			free_resseource_children(minishell, pipe_fds);
			return (true);
		}
	}
	return (false);
}

bool	dup_fd_out(t_minishell *minishell, t_execution *tmp_exec, \
		int pipe_fds[2])
{
	t_redirection	redir;
	int				i;

	i = 0;
	while (i < tmp_exec->redirection_count)
	{
		redir = tmp_exec->redirections[i];
		if (redir.fd > 0)
		{
			if (get_fd(minishell, redir, pipe_fds))
				return (true);
		}
		i++;
	}
	return (false);
}

bool	check_fd_is_valide(t_execution *execution)
{
	t_execution		*tmp_exec;
	int				i;

	i = 0;
	if (!execution)
		return (false);
	tmp_exec = execution;
	while (i < execution->redirection_count)
	{
		if (tmp_exec->redirections[i].fd < 0)
			return (true);
		i++;
	}
	return (false);
}

bool	dup_here_doc(t_minishell *minishell, t_execution *tmp_exec, \
		int pipe_fds[2])
{
	int	heredoc_fd;

	heredoc_fd = -1;
	heredoc_fd = tmp_exec->heredoc_fds[tmp_exec->heredoc_count - 1];
	if (dup2(heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 stdout");
		minishell->exec.exit_code = 1;
		free_resseource_children(minishell, pipe_fds);
		clear_link_env(&(minishell->env_link));
		clear_link_token(&(minishell->token));
		return (true);
	}
	return (false);
}

bool	dup_fd(t_minishell *minishell, t_execution *execution, int pipe_fds[2])
{
	t_execution		*tmp_exec;

	if (check_fd_is_valide(execution))
	{
		close_fd(minishell);
		return (true);
	}
	tmp_exec = execution;
	if (tmp_exec->redirection_count > 0)
	{
		if (dup_fd_out(minishell, tmp_exec, pipe_fds))
			return (true);
	}
	if (tmp_exec->heredoc_count > 0)
		dup_here_doc(minishell, tmp_exec, pipe_fds);
	close_fd(minishell);
	return (false);
}
