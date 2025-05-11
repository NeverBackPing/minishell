/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 22:55:19 by simonp            #+#    #+#             */
/*   Updated: 2025/02/18 19:41:29 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	ft_is_separator_bis(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

int	len_after_sep(t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	i = 0;
	while (tmp)
	{
		if (tmp->token == PIPE)
			break ;
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	ft_is_sep_first(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (ft_is_separator_bis(tmp->type[0]) == false)
		return ;
	if ((ft_strlen(tmp->type) >= 2) && tmp->type[1] == '<')
		return ;
	if (len_after_sep(tmp) < 3)
		return ;
	if (tmp->next != NULL && tmp->next->next != NULL)
		tmp = tmp->next->next;
	if (ft_isbuiltin(tmp))
		tmp->token = BUILTIN;
	else if (tmp->prev->token != FILENAME && tmp->prev->token != ENDOFFILE)
		tmp->token = COMMAND;
}

void	ft_fourth_token(t_minishell *minishell)
{
	t_token	*tmp;
	t_token	*head;

	tmp = minishell->token;
	head = minishell->token;
	if (is_sep_in_ll(minishell->token) == false)
		return ;
	ft_is_sep_first(head);
	while (tmp)
	{
		if (tmp->token == PIPE && tmp->next != NULL)
		{
			head = tmp->next;
			ft_is_sep_first(head);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

t_token	*ft_third_token(t_minishell *minishell)
{
	t_token	*tmp;
	t_token	*head;
	t_token	*next_node;

	tmp = minishell->token;
	head = tmp;
	while (tmp)
	{
		next_node = tmp->next;
		if (ft_strlen(tmp->type) == 0)
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
