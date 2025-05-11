/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:13:42 by speladea          #+#    #+#             */
/*   Updated: 2025/02/18 14:25:28 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	stop_child(t_minishell *minishell, t_token *token, char *line)
{
	free(line);
	write_str2(\
	"\033[0;31mWarning\033[0m: delimited by end-of-file wanted ", \
	token->next->type, 2);
	line = NULL;
	minishell->exec.exit_code = 131;
}

void	ft_exit_here_doc(int signal)
{
	if (signal == SIGINT)
	{
		g_exit_loop = 1;
		ft_putchar_fd('\n', STDOUT_FILENO);
		close(STDIN_FILENO);
	}
}
