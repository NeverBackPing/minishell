/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:57:54 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/18 23:22:22 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_exit_status(t_minishell *minishell)
{
	int	get_error;

	get_error = 0;
	while (waitpid(-1, &minishell->exec.status, 0) > 0)
	{
		if (WIFEXITED(minishell->exec.status))
		{
			get_error = WEXITSTATUS(minishell->exec.status);
			minishell->exec.exit_code = get_error;
		}
		else if (WIFSIGNALED(minishell->exec.status))
		{
			minishell->exec.exit_code = 128 + WTERMSIG(minishell->exec.status);
		}
	}
	minishell->exec.exit_code = get_error;
}
