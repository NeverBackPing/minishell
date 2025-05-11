/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:13:34 by sjossain          #+#    #+#             */
/*   Updated: 2025/01/06 14:13:34 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pid_error(t_minishell *minishell)
{
	(void)minishell;
	write_str("\033[0;31mError\033[0m: No child processes\n", 2);
	minishell->exec.exit_code = 10;
	close(minishell->exec.pipe[0]);
	minishell->exec.pipe[0] = -1;
	close(minishell->exec.pipe[1]);
	minishell->exec.pipe[1] = -1;
}
