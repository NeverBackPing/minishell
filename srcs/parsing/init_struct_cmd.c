/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:15:51 by simonp            #+#    #+#             */
/*   Updated: 2025/02/21 15:20:24 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	is_fd(t_token *tmp)
{
	if (tmp->token == HERE_DOC || tmp->token == STDIN || \
		tmp->token == STDOUT || tmp->token == STDOUT_ADD)
		return (true);
	return (false);
}

bool	loop_strutc_cmd(t_minishell *minishell, \
		t_token *tmp, int current_exec)
{
	while (tmp)
	{
		if (is_fd(tmp))
		{
			if (init_fd_struct(minishell, tmp, current_exec))
				return (free_all_executions(minishell), true);
			if (init_fd(minishell, tmp, current_exec) || g_exit_loop)
				return (true);
			init_arg_cmd(minishell, tmp, current_exec);
			current_exec++;
		}
		if (tmp->token == COMMAND || tmp->token == BUILTIN)
		{
			init_current_exec(minishell, tmp, current_exec);
			if (init_fd(minishell, tmp, current_exec) || g_exit_loop)
				return (true);
			init_arg_cmd(minishell, tmp, current_exec);
			current_exec++;
		}
		while (tmp && tmp->token != PIPE)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (false);
}

bool	init_structure_cmd(t_minishell *minishell)
{
	t_token		*tmp;
	int			cmd_count;
	int			current_exec;

	current_exec = 0;
	cmd_count = count_cmd(minishell);
	tmp = minishell->token;
	minishell->execution = malloc(sizeof(t_execution) * cmd_count);
	if (!minishell->execution)
	{
		minishell->exec.exit_code = 5;
		return (perror("malloc"), true);
	}
	ft_bzero(minishell->execution, sizeof(t_execution) * cmd_count);
	minishell->exec_count = cmd_count;
	minishell->pars.pipe = cmd_count - 1;
	if (loop_strutc_cmd(minishell, tmp, current_exec))
		return (true);
	return (false);
}
