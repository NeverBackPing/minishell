/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:52:07 by simonp            #+#    #+#             */
/*   Updated: 2025/02/21 14:27:52 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	ft_is_separator(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

void	ft_adding_node(t_token *current, t_token *new_node)
{
	if (!current || !new_node)
		return ;
	new_node->next = current->next;
	new_node->prev = current;
	if (current->next)
		current->next->prev = new_node;
	current->next = new_node;
}

int	token_before(t_token *tmp)
{
	if (tmp->prev == NULL)
		return (-1);
	return (tmp->prev->token);
}

bool	cmd_before(t_token *tmp)
{
	if (tmp->prev == NULL)
		return (false);
	while (tmp->prev != NULL)
	{
		if (tmp->token == COMMAND)
			return (true);
		tmp = tmp->prev;
	}
	if (tmp->token == COMMAND)
		return (true);
	return (false);
}

bool	check_before(t_token *tmp)
{
	int		pipe;
	t_token	*token;

	pipe = 0;
	token = tmp;
	while (token)
	{
		if (token->token == PIPE)
			pipe++;
		if ((token->token == COMMAND || token->token == BUILTIN) && \
			pipe == 0)
		{
			return (true);
		}
		token = token->prev;
	}
	return (false);
}
