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

void	free_redirections_heredoc(t_execution *exec)
{
	int	j;

	j = 0;
	while (j < exec->heredoc_count)
	{
		close(exec->heredoc_fds[j++]);
	}
	free(exec->heredoc_fds);
	exec->heredoc_fds = NULL;
}

void	free_redirections_std(t_execution *exec)
{
	int	j;

	j = 0;
	while (j < exec->redirection_count)
	{
		close(exec->redirections[j].fd);
		j++;
	}
	free(exec->redirections);
	exec->redirections = NULL;
}
