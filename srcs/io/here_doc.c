/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:15:45 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/21 15:43:15 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_pipe(t_minishell *minishell, char *line, int pipe_fd)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strchr(line, '$'))
	{
		tmp = replace_env_variables(minishell, line);
		write(pipe_fd, tmp, ft_strlen(tmp));
		write(pipe_fd, "\n", ft_strlen("\n"));
		free(tmp);
		return ;
	}
	write(pipe_fd, line, ft_strlen(line));
	write(pipe_fd, "\n", ft_strlen("\n"));
}

bool	check_lim_for_exit(t_minishell *minishell, char *line, \
	t_token *token, int pipe_fds[2])
{
	(void)pipe_fds;
	if (!line)
	{
		stop_child(minishell, token, line);
		return (true);
	}
	if (ft_strncmp(line, token->next->type, \
		ft_strlen(token->next->type)) == 0)
	{
		if (!line[ft_strlen(token->next->type)])
		{
			free(line);
			return (true);
		}
	}
	return (false);
}

bool	break_and_free(t_minishell *minishell, char *line, int pipe_fds[2])
{
	if (g_exit_loop)
	{
		if (line)
			free(line);
		close(pipe_fds[1]);
		close(pipe_fds[0]);
		minishell->exec.exit_code = 130;
		return (true);
	}
	return (false);
}

void	here_doc(t_minishell *minishell, t_execution *exec, \
		t_token *token, int heredoc_index)
{
	char	*line;
	int		pipe_fds[2];

	line = NULL;
	if (g_exit_loop)
		return ;
	if (create_pipe(minishell, pipe_fds))
		return ;
	while (1)
	{
		line = readline("\033[0;34mheredoc>\033[0m ");
		if (break_and_free(minishell, line, pipe_fds))
			return ;
		if (check_lim_for_exit(minishell, line, token, pipe_fds))
			break ;
		write_pipe(minishell, line, pipe_fds[1]);
		if (line)
			free(line);
	}
	close(pipe_fds[1]);
	exec->heredoc_fds[heredoc_index] = pipe_fds[0];
}

bool	open_here_doc(t_minishell *minishell, t_execution *exec, \
		t_token *token, int heredoc_index)
{
	signal(SIGINT, ft_exit_here_doc);
	here_doc(minishell, exec, token, heredoc_index);
	if (g_exit_loop)
		exec->heredoc_count--;
	main_signal(minishell);
	return (false);
}
