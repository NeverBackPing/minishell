/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:54:30 by sjossain          #+#    #+#             */
/*   Updated: 2024/12/02 16:33:40 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	free_resseource_children(t_minishell *minishell, int pipe_fds[2])
{
	(void)pipe_fds;
	if (minishell->exec.stdout_backup != -1)
	{
		close(minishell->exec.stdout_backup);
		minishell->exec.stdout_backup = -1;
	}
	free_all_executions(minishell);
	clear_link_env(&(minishell->env_link));
	clear_link_token(&(minishell->token));
}
