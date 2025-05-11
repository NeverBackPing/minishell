/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:11:03 by simonp            #+#    #+#             */
/*   Updated: 2025/02/12 22:25:29 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	ft_do_both_split(t_token *tmp, int i, int sep_len, int len)
{
	ft_splitting(tmp, tmp->type, i + sep_len, len);
	ft_splitting(tmp, tmp->type, i, i + sep_len);
}

int	ft_do_idk(t_token *tmp, int i, int len)
{
	int		sep_len;

	sep_len = 1;
	if (i > 0 && (tmp->type[i] == '<' || tmp->type[i] == '>') && \
		tmp->type[i] == tmp->type[i - 1])
	{
		sep_len = 2;
		i--;
	}
	if (i + sep_len < len)
		ft_do_both_split(tmp, i, sep_len, len);
	return (i);
}

void	ft_add_separator(t_token *tmp, int i)
{
	char	*c;
	t_token	*new_t;

	c = "";
	c = ft_strcharjoin(c, tmp->type[i]);
	new_t = new_token(15, c);
	tmp = tmp->next;
	ft_adding_node(tmp, new_t);
}

void	ft_find_separator(t_token *t)
{
	int	i;

	while (t)
	{
		if (t->single_q == false && t->double_q == false)
		{
			i = 0;
			while (t->type[i])
			{
				if (t->type[i] == '|' || t->type[i] == '<' || t->type[i] == '>')
				{
					if (t->type[i + 1] == '<' || t->type[i + 1] == '>')
					{
						t->token = HEREADD;
						i++;
					}
					else
						if (ft_strlen(t->type) >= 2)
							t->token = STDIN_OUT;
				}
				i++;
			}
		}
		t = t->next;
	}
}

bool	ft_check_separate(t_token *tmp)
{
	if (tmp->token == HEREADD)
	{
		if (ft_strlen(tmp->type) == 2)
		{
			if (ft_strcmp(tmp->type, "<<") == 0)
				tmp->token = HERE_DOC;
			if (ft_strcmp(tmp->type, ">>") == 0)
				tmp->token = STDOUT_ADD;
			return (true);
		}
		else
			return (false);
	}
	return (false);
}
