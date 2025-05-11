/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:54:57 by sjossain          #+#    #+#             */
/*   Updated: 2024/12/02 18:35:55 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*last(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_data(t_token **lst, t_token *new, bool s_quote, bool d_quote)
{
	t_token	*end;

	end = NULL;
	if (*lst)
	{
		end = last(*lst);
		end->next = new;
		new->prev = end;
	}
	else
	{
		*lst = new;
		new->prev = end;
	}
	new->single_q = s_quote;
	new->double_q = d_quote;
}

t_token	*new_token(int token, char *type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = token;
	node->type = ft_strdup(type);
	if (!node->type)
	{
		free(node);
		return (NULL);
	}
	node->link = false;
	node->single_q = false;
	node->double_q = false;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	data_delone(t_token *lst_token)
{
	if (lst_token)
	{
		lst_token->token = 0;
		free(lst_token->type);
		free(lst_token);
	}
}

void	clear_link_token(t_token **lst_token)
{
	t_token	*tmp;
	t_token	*tmp2;

	if (!lst_token || !*lst_token)
		return ;
	tmp = *lst_token;
	while (tmp)
	{
		tmp2 = tmp->next;
		data_delone(tmp);
		tmp = tmp2;
	}
	*lst_token = NULL;
}
