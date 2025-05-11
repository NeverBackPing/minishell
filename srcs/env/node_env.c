/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-19 16:46:09 by speladea          #+#    #+#             */
/*   Updated: 2024-11-19 16:46:09 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	clear_link_env(t_env_link **lst_env)
{
	t_env_link	*tmp;
	t_env_link	*tmp2;

	if (!lst_env || !*lst_env)
		return ;
	tmp = *lst_env;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp)
		{
			free(tmp->ev);
			free(tmp);
		}
		tmp = tmp2;
	}
	*lst_env = NULL;
}

t_env_link	*new_env(char *type)
{
	t_env_link	*node;

	node = malloc(sizeof(t_env_link));
	if (!node)
		return (NULL);
	node->ev = ft_strdup(type);
	if (!node->ev)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_env_link	*last_env(t_env_link *lst)
{
	t_env_link	*tmp;

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

void	add_env(t_env_link **lst, t_env_link *new)
{
	t_env_link	*end;

	end = NULL;
	if (*lst)
	{
		end = last_env(*lst);
		end->next = new;
		new->prev = end;
	}
	else
	{
		*lst = new;
		new->prev = end;
	}
}
