/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:54:30 by sjossain          #+#    #+#             */
/*   Updated: 2024/12/02 16:33:40 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	open_stdin(t_minishell *minishell, t_token *redirect, \
		t_redirection *redir)
{
	int	fd;

	fd = -1;
	(void)minishell;
	if (redirect->token != STDIN)
		return (false);
	fd = open(redirect->next->type, O_RDONLY);
	if (fd == -1)
	{
		redir->fd = fd;
		minishell->error_stdout = true;
		if (access(redirect->next->type, F_OK))
			write_str2("\033[0;31mError\033[0m: No such file or directory ", \
				redirect->next->type, 2);
		else if (access(redirect->next->type, X_OK))
			write_str2("\033[0;31mError\033[0m: Permission denied ", \
				redirect->next->type, 2);
		minishell->exec.exit_code = 1;
		return (false);
	}
	redir->fd = fd;
	return (false);
}

bool	open_stdout(t_minishell *minishell, t_token *redirect, \
		t_redirection *redir)
{
	int	fd;

	fd = -1;
	(void)minishell;
	if (redirect->token != STDOUT)
		return (false);
	fd = open(redirect->next->type, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		redir->fd = fd;
		if (access(redirect->next->type, F_OK))
			write_str2("\033[0;31mError\033[0m: No such file or directory ", \
				redirect->next->type, 2);
		else if (access(redirect->next->type, X_OK))
			write_str2("\033[0;31mError\033[0m: Permission denied ", \
				redirect->next->type, 2);
		minishell->exec.exit_code = 1;
		return (false);
	}
	redir->fd = fd;
	return (false);
}

bool	open_std(t_minishell *minishell, t_token *redirect, \
		t_redirection *redir)
{
	int	fd;

	fd = -1;
	if (open_stdin(minishell, redirect, redir))
		return (true);
	if (open_stdout(minishell, redirect, redir))
		return (true);
	if (redirect->token != STDOUT_ADD)
		return (false);
	fd = open(redirect->next->type, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		if (access(redirect->next->type, F_OK))
			write_str2("Error: No such file or directory ", \
				redirect->next->type, 2);
		else if (access(redirect->next->type, X_OK))
		{
			write_str2("\033[0;31mError\033[0m: Permission denied ", \
				redirect->next->type, 2);
			minishell->exec.exit_code = 1;
		}
	}
	redir->fd = fd;
	return (false);
}

bool	loop_std(t_minishell *minishell, t_execution *current, \
		t_token *redirect)
{
	int	heredoc_index;
	int	redir_index;

	heredoc_index = 0;
	redir_index = 0;
	while (redirect && redirect->token != PIPE)
	{
		if (redirect->token == HERE_DOC)
			open_here_doc(minishell, current, redirect, heredoc_index++);
		if (redirect->token == STDIN || redirect->token == STDOUT || \
			redirect->token == STDOUT_ADD)
		{
			if (redirect->token == STDIN)
				current->redirections[redir_index].type = 0;
			else
				current->redirections[redir_index].type = 1;
			if (open_std(minishell, redirect, \
				&current->redirections[redir_index]))
				return (true);
			redir_index++;
		}
		redirect = redirect->next;
	}
	return (false);
}

bool	init_fd(t_minishell *minishell, t_token *token, int current_exec)
{
	t_execution	*current;
	t_token		*redirect;

	redirect = token;
	if (redirect->token == BUILTIN || redirect->token == COMMAND)
		redirect = token->next;
	current = &minishell->execution[current_exec];
	if (allocade_struct_fd(minishell, current, token))
		return (true);
	if (loop_std(minishell, current, redirect) || g_exit_loop)
		return (true);
	if (redirect && redirect->token == PIPE && current_exec == 0)
		current->pipe_out = 1;
	return (false);
}
