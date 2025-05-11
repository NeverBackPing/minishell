/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:04:21 by speladea          #+#    #+#             */
/*   Updated: 2025/02/19 22:32:14 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	ft_splitting(t_token *tmp, const char *str, int start, int end)
{
	char	*new_str;
	t_token	*new_t;

	new_str = ft_substr(str, start, end - start);
	if (!new_str)
		exit(EXIT_FAILURE);
	new_t = new_token(15, new_str);
	free(new_str);
	ft_adding_node(tmp, new_t);
}

void	ft_sep_hereadd(t_token *tmp)
{
	char	*new_str;
	t_token	*new_t;
	char	*sep_str;
	t_token	*sep_t;

	sep_str = ft_strdup(tmp->type + ft_strlen(tmp->type) - 2);
	if (!sep_str)
		exit(EXIT_FAILURE);
	sep_t = new_token(15, sep_str);
	free(sep_str);
	ft_adding_node(tmp, sep_t);
	new_str = ft_substr(tmp->type, 0, ft_strlen(tmp->type) - 2);
	if (!new_str)
		exit(EXIT_FAILURE);
	new_t = new_token(15, new_str);
	free(new_str);
	ft_adding_node(tmp, new_t);
}

void	ft_do_separation(t_token *tmp)
{
	int		i;
	int		len;

	len = ft_strlen(tmp->type);
	i = len - 1;
	if (len > 0 && ft_is_separator(tmp->type[len - 1]))
	{
		ft_splitting(tmp, tmp->type, len - 1, len);
		len--;
	}
	while (i >= 0)
	{
		if (ft_is_separator(tmp->type[i]))
		{
			i = ft_do_idk(tmp, i, len);
			len = i;
		}
		i--;
	}
	if (i + 1 < len)
		ft_splitting(tmp, tmp->type, 0, len);
}

t_token	*ft_separate(t_minishell *minishell)
{
	t_token	*tmp;
	t_token	*tmp2;
	int		i;

	tmp = minishell->token;
	tmp2 = tmp;
	i = 0;
	while (tmp)
	{
		if (tmp->token == HEREADD || tmp->token == STDIN_OUT)
		{
			if (!ft_check_separate(tmp))
			{
				if (tmp->token == HEREADD && \
					ft_is_separator(tmp->type[ft_strlen(tmp->type) - 1]))
					ft_sep_hereadd(tmp);
				else
					ft_do_separation(tmp);
			}
		}
		tmp = tmp->next;
		i++;
	}
	return (tmp2);
}

void	ft_checker(t_minishell *minishell)
{
	t_token	*tmp;

	ft_find_tab(minishell);
	minishell->token = ft_delete_tab_nodes(minishell);
	tmp = minishell->token;
	if (error_sep(minishell, tmp))
		return ;
	ft_find_separator(tmp);
	minishell->token = ft_separate(minishell);
	minishell->token = ft_delete_leftover(minishell);
	ft_second_token(minishell);
	if (!minishell->token)
		return ;
	ft_check_expand(minishell);
	navi_link(minishell);
	minishell->token = erase_link(minishell);
	minishell->token = ft_third_token(minishell);
	ft_second_token(minishell);
	ft_fourth_token(minishell);
}
