/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:15:51 by simonp            #+#    #+#             */
/*   Updated: 2025/02/15 15:58:17 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	count_args_or_flags(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == ARGUMENT || tmp->token == FLAG)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	count_here_doc(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == HERE_DOC)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	count_std(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == STDIN || tmp->token == STDOUT_ADD || \
			tmp->token == STDOUT)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	count_cmd(t_minishell *minishell)
{
	t_token	*tmp;
	int		cmd_count;

	cmd_count = 1;
	tmp = minishell->token;
	while (tmp)
	{
		if (tmp->token == PIPE)
		{
			cmd_count++;
		}
		tmp = tmp->next;
	}
	minishell->exec_count = cmd_count;
	return (cmd_count);
}

char	*find_cmd(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == COMMAND || tmp->token == BUILTIN)
			return (tmp->type);
		tmp = tmp->next;
	}
	return (NULL);
}
