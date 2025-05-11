/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_part2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:43:28 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/15 16:32:04 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	access_program_test(t_minishell *minishell, t_execution *execution)
{
	if (execution->cmd[0] != '.' && execution->cmd[1] != '/')
		return ;
	if (access(execution->cmd, X_OK) != 0)
	{
		free_all_executions(minishell);
		clear_link_token(&(minishell->token));
		clear_link_env(&(minishell->env_link));
		write_str2(execution->cmd, ": permission denied\n", 2);
		exit(13);
	}
}

void	exec_program_test(t_minishell *minishell, t_execution *execution)
{
	char	**env;

	env = convert_env_to_array(minishell, minishell->env_link);
	if (!env)
		exit(12);
	if (execve(execution->cmd, execution->args, env) == -1)
	{
		free(env);
		access_program_test(minishell, execution);
		clear_link_token(&(minishell->token));
		clear_link_env(&(minishell->env_link));
		if (ft_strchr(execution->cmd, '/') != NULL && \
			execution->cmd[ft_strlen(execution->cmd)] != '/')
		{
			write_str2(execution->cmd, ": Is a directory\n", 2);
			free_all_executions(minishell);
			exit(126);
		}
		free_all_executions(minishell);
		write_str("Operation not permitted\n", 2);
		exit(127);
	}
	free(env);
	exit(0);
}
