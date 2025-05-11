/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deleting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:49:31 by speladea          #+#    #+#             */
/*   Updated: 2025/01/13 01:19:04 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	ft_delete_first_node(t_token **head)
{
	t_token	*temp;

	if (!head || !*head)
		return ;
	temp = *head;
	*head = (*head)->next;
	if (*head)
		(*head)->prev = NULL;
	free(temp->type);
	free(temp);
}

void	ft_delete_node(t_token *node)
{
	if (!node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->type);
	free(node);
}

bool	ft_has_separator(t_token *token)
{
	int	i;

	i = 0;
	while (token->type[i] != '\0')
	{
		if (ft_is_separator(token->type[i]))
		{
			if (i == 0 && ft_strlen(token->type) == 1)
				return (false);
			else
				return (true);
		}
		else
			i++;
	}
	return (false);
}

t_token	*ft_delete_leftover(t_minishell *minishell)
{
	t_token	*tmp;
	t_token	*head;
	t_token	*next_node;

	tmp = minishell->token;
	head = tmp;
	while (tmp)
	{
		next_node = tmp->next;
		if ((tmp->token == 20 || tmp->token == 21) && ft_has_separator(tmp))
		{
			if (tmp == head)
				ft_delete_first_node(&head);
			else
				ft_delete_node(tmp);
		}
		tmp = next_node;
	}
	return (head);
}

t_token	*ft_delete_tab_nodes(t_minishell *minishell)
{
	t_token	*tmp;
	t_token	*head;
	t_token	*next_node;

	tmp = minishell->token;
	head = tmp;
	while (tmp)
	{
		next_node = tmp->next;
		if (tmp->token == IS_TAB)
		{
			if (tmp == head)
				ft_delete_first_node(&head);
			else
				ft_delete_node(tmp);
		}
		tmp = next_node;
	}
	return (head);
}
