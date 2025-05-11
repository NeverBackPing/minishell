/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:43:28 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/19 22:28:33 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	access_path_test(t_minishell *minishell, t_command *cmd, \
		t_execution *execution)
{
	if (access(cmd->cmd_path, F_OK) == 0)
	{
		if (access(cmd->cmd_path, X_OK) == 0)
			return (1);
		else
		{
			write_str2(execution->cmd, ": permission denied\n", 2);
			minishell->exec.exit_code = 1;
			free(cmd->cmd_path);
			return (true);
		}
	}
	return (false);
}

bool	find_path_test(t_minishell *minishell, t_execution *execution)
{
	char	*env_path;

	if (execution->cmd == NULL)
		return (true);
	env_path = ft_strtok(put_str_env(minishell, \
		&minishell->env_link, "PATH"), ':');
	if (env_path == NULL)
		return (true);
	if (minishell->exec.stdout_backup != -1)
	{
		close(minishell->exec.stdout_backup);
		minishell->exec.stdout_backup = -1;
	}
	while (env_path != NULL)
	{
		minishell->cmd.cmd_path = ft_strjoin(env_path, execution->cmd);
		if (minishell->cmd.cmd_path == NULL)
			return (free(env_path), true);
		if (access_path_test(minishell, &minishell->cmd, execution))
			return (free(env_path), false);
		free(minishell->cmd.cmd_path);
		env_path = ft_strtok(NULL, ':');
	}
	minishell->cmd.cmd_path = NULL;
	return (true);
}

void	get_cmd_test(t_minishell *minishell, t_execution *execution)
{
	if (find_path_test(minishell, execution))
	{
		if (ft_strchr(execution->cmd, '/'))
			write_str2(execution->cmd, ":  No such file or directory", 2);
		else
			write_str2(execution->cmd, ": command not found", 2);
		free_all_executions(minishell);
		if (minishell->cmd.cmd_path)
			free(minishell->cmd.cmd_path);
		if (minishell->exec.stdout_backup != -1)
		{
			close(minishell->exec.stdout_backup);
			minishell->exec.stdout_backup = -1;
		}
		clear_link_env(&(minishell->env_link));
		clear_link_token(&(minishell->token));
		exit(127);
	}
}

void	fail_execve(t_minishell *minishell, char **env)
{
	free(env);
	if (minishell->exec.stdout_backup != -1)
		close(minishell->exec.stdout_backup);
	minishell->exec.stdout_backup = -1;
	free_all_executions(minishell);
	clear_link_token(&(minishell->token));
	clear_link_env(&(minishell->env_link));
	write_str("Operation not permitted\n", 2);
	exit(1);
}

void	execout(t_minishell *minishell, t_execution *execution)
{
	char	**env;

	if (!execution->cmd)
	{
		free_all_executions(minishell);
		exit(0);
	}
	if (access(execution->cmd, F_OK) == 0 && \
		(((execution->cmd[0] == '.' && execution->cmd[1] == '/') \
		|| execution->cmd[0] == '/')))
		exec_program_test(minishell, execution);
	get_cmd_test(minishell, execution);
	env = convert_env_to_array(minishell, minishell->env_link);
	if (!env)
		exit(12);
	if (execve(minishell->cmd.cmd_path, execution->args, env) == -1)
		fail_execve(minishell, env);
}
