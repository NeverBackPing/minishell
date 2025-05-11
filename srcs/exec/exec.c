/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:06:19 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/17 18:35:51 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe_builtin(t_minishell *minishell, t_token *token, \
	t_execution *execution, int pipe_fds[2])
{
	(void)pipe_fds;
	(void)execution;
	ft_do_builtin(minishell, token);
	free_resseource_children(minishell, pipe_fds);
	exit(0);
}

bool	exec_without_pipe(t_minishell *minishell)
{
	t_token	*tmp;

	tmp = minishell->token;
	second_sig();
	while (tmp)
	{
		if (tmp->token == BUILTIN || tmp->token == COMMAND)
			exec_cmd_and_builtin(minishell, tmp);
		tmp = tmp->next;
	}
	if (minishell->exec.stdout_backup != -1)
	{
		close(minishell->exec.stdout_backup);
		minishell->exec.stdout_backup = -1;
	}
	main_signal(minishell);
	return (false);
}

bool	exec_single(t_minishell *minishell)
{
	if (minishell->pars.pipe < 1)
	{
		if (!minishell->error_stdout)
		{
			exec_without_pipe(minishell);
		}
		else
		{
			close(minishell->exec.stdout_backup);
			minishell->exec.stdout_backup = -1;
		}
		return (true);
	}
	return (false);
}

bool	exec(t_minishell *minishell, t_token *token)
{
	int	pipe_fds[2];
	int	i;

	i = 0;
	minishell->exec.stdout_backup = -1;
	minishell->exec.stdout_backup = dup(STDOUT_FILENO);
	if (exec_single(minishell))
		return (true);
	while (i < minishell->pars.pipe && token)
	{
		if (create_pipe(minishell, pipe_fds))
			return (true);
		fork_exec(minishell, token, &minishell->execution[i++], \
			pipe_fds);
		dup_in(minishell, pipe_fds);
		while (token && token->token != PIPE)
			token = token->next;
		if (token)
			token = token->next;
	}
	last_exec(minishell, token, &minishell->execution[i]);
	return (get_exit_status(minishell), false);
}
