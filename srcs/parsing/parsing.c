/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:15:51 by simonp            #+#    #+#             */
/*   Updated: 2025/02/17 15:57:36 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	init_current_exec(t_minishell *minishell, t_token *token, \
	int current_exec)
{
	t_execution	*current;

	current = &minishell->execution[current_exec];
	current->id = token->token;
	if (current->cmd)
		free(current->cmd);
	current->cmd = ft_strdup(token->type);
	if (!current->cmd)
	{
		perror("Fail malloc");
		minishell->exec.exit_code = 5;
		return (true);
	}
	current->args = NULL;
	current->heredoc_count = 0;
	current->redirection_count = 0;
	current->heredoc_fds = NULL;
	current->redirections = NULL;
	current->pipe_in = (token->prev && token->prev->token == PIPE);
	current->pipe_out = (token->next && token->next->token == PIPE);
	return (false);
}

bool	init_fd_struct(t_minishell *minishell, t_token *token, \
	int current_exec)
{
	t_execution	*current;

	current = &minishell->execution[current_exec];
	current->id = token->token;
	if (current->cmd)
		free(current->cmd);
	current->cmd = ft_strdup(find_cmd(token));
	current->args = NULL;
	current->heredoc_count = 0;
	current->redirection_count = 0;
	current->heredoc_fds = NULL;
	current->redirections = NULL;
	current->pipe_in = (token->prev && token->prev->token == PIPE);
	current->pipe_out = (token->next && token->next->token == PIPE);
	return (false);
}

bool	init_arg_cmd(t_minishell *minishell, t_token *token, int current_exec)
{
	t_execution	*current;
	t_token		*arg;
	int			i;

	arg = token->next;
	i = count_args_or_flags(token);
	current = &minishell->execution[current_exec];
	current->args = (char **)malloc((i + 2) * sizeof(char *));
	i = 0;
	if (!current->args)
		return (perror("Fail malloc"), true);
	current->args[i++] = ft_strdup(current->cmd);
	while (arg && arg->token != PIPE)
	{
		if (arg->token == ARGUMENT || arg->token == FLAG)
		{
			current->args[i] = ft_strdup(arg->type);
			if (!current->args[i++])
				return (perror("Fail malloc"), true);
		}
		arg = arg->next;
	}
	current->args[i] = NULL;
	return (false);
}

bool	allocade_struct_fd(t_minishell *minishell, \
		t_execution *current, t_token *token)
{
	current->heredoc_count = count_here_doc(token);
	current->redirection_count = count_std(token);
	if (current->heredoc_count > 0)
	{
		current->heredoc_fds = malloc(sizeof(int) * current->heredoc_count);
		if (!current->heredoc_fds)
		{
			minishell->exec.exit_code = 5;
			write_str("Fail malloc\n", 2);
			return (true);
		}
	}
	if (current->redirection_count > 0)
	{
		current->redirections = malloc(sizeof(t_redirection) * \
			current->redirection_count);
		if (!current->redirections)
		{
			minishell->exec.exit_code = 5;
			write_str("Fail malloc\n", 2);
			return (true);
		}
	}
	return (false);
}
