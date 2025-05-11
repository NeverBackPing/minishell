/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checker_bis_bis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:40:26 by speladea          #+#    #+#             */
/*   Updated: 2025/02/19 19:40:27 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	add_link(t_minishell *minishell, t_token *pos, char *str)
{
	t_token	*token;
	t_token	*new_t;

	token = minishell->token;
	while (token)
	{
		if (token->token == NEW_UNDEFINE)
		{
			new_t = new_token(ARGUMENT, str);
			ft_adding_node(pos, new_t);
			break ;
		}
		token = token->next;
	}
}

char	*link_eq_true(t_token *token, char *str)
{
	char	*tmp;
	char	*new_str;

	if (token->prev && token->prev->link == false)
	{
		token->prev->token = NEW_UNDEFINE;
		token->token = NEW_UNDEFINE;
		tmp = ft_strjoin(token->type, token->prev->type);
		new_str = ft_strjoin(str, tmp);
		free(str);
		free(tmp);
	}
	if (token->prev && token->prev->link == true)
	{
		token->token = NEW_UNDEFINE;
		new_str = ft_strjoin(token->type, str);
		free(str);
	}
	return (new_str);
}

void	navi_link(t_minishell *minishell)
{
	char	*str;
	t_token	*token;
	t_token	*l_false;

	str = ft_strdup("");
	token = minishell->token;
	while (token)
	{
		if (token->link == false)
			l_false = token;
		if (token->link == true)
			str = link_eq_true(token, str);
		if (token->link == false && token->prev && token->prev->link == true)
		{
			add_link(minishell, token->prev, str);
			free(str);
			str = ft_strdup("");
		}
		token = token->next;
	}
	add_link(minishell, l_false, str);
	free(str);
}

t_token	*erase_link(t_minishell *minishell)
{
	t_token	*tmp;
	t_token	*head;
	t_token	*next_node;

	tmp = minishell->token;
	head = tmp;
	while (tmp)
	{
		next_node = tmp->next;
		if (tmp->token == NEW_UNDEFINE)
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
