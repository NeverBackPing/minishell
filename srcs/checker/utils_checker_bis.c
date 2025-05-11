/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checker_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 16:56:31 by simonp            #+#    #+#             */
/*   Updated: 2025/02/09 16:56:36 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	while_tab_incr_i(char *token_type, int i)
{
	while (token_type[i] == '\t')
	{
		i++;
	}
	return (i);
}

void	ft_sep_tab(t_token *token)
{
	int		i;
	char	*str;
	char	*tmp;
	t_token	*new_t;
	t_token	*prev;

	prev = token;
	i = 0;
	i = while_tab_incr_i(token->type, i);
	while (token->type[i])
	{
		str = ft_strdup("");
		while (token->type[i] && token->type[i] != '\t')
		{
			tmp = ft_strcharjoin(str, token->type[i]);
			free(str);
			str = tmp;
			i++;
		}
		new_t = new_token(0, str);
		free(str);
		ft_adding_node(prev, new_t);
		prev = new_t;
		i = while_tab_incr_i(token->type, i);
	}
}

void	ft_find_tab(t_minishell *minishell)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = minishell->token;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (ft_strchr(tmp->type, '\t') && tmp->double_q == false \
			&& tmp->single_q == false)
		{
			tmp->token = IS_TAB;
			ft_sep_tab(tmp);
		}
		tmp = tmp2;
	}
}

bool	error_sep(t_minishell *minishell, t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	while (tmp)
	{
		i = 0;
		while (tmp->type[i])
		{
			if (tmp->type[i] == '|')
			{
				if (i > 0)
				{
					if (tmp->type[i - 1] == '<' || tmp->type[i - 1] == '>')
					{
						ft_do_error(minishell, PIPE);
						return (true);
					}
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
	return (false);
}
