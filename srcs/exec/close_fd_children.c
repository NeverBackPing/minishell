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

void	close_std(t_minishell *minishell)
{
	if (minishell->exec.stdin_backup != -1)
	{
		close(minishell->exec.stdin_backup);
		minishell->exec.stdin_backup = -1;
	}
	if (minishell->exec.stdout_backup != -1)
	{
		close(minishell->exec.stdout_backup);
		minishell->exec.stdout_backup = -1;
	}
}

void	close_stdin(t_minishell *minishell)
{
	if (minishell->exec.stdin_backup != -1)
	{
		close(minishell->exec.stdin_backup);
		minishell->exec.stdin_backup = -1;
	}
}

void	close_stdout(t_minishell *minishell)
{
	if (minishell->exec.stdout_backup != -1)
	{
		close(minishell->exec.stdout_backup);
		minishell->exec.stdout_backup = -1;
	}
}

void	close_fd(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->exec_count)
	{
		free_redirections(&minishell->execution[i]);
		i++;
	}
}
