/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils_bis_bis_bis.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:37:00 by simonp            #+#    #+#             */
/*   Updated: 2025/02/11 20:38:14 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	incr_q(char *new_dest, char quote, int q, int i)
{
	if (new_dest[i] != quote)
		return (q);
	else
		q++;
	return (q);
}

bool	to_find_quote(char *dest)
{
	int	i;

	i = 0;
	while (dest[i])
	{
		if (dest[i] == '\'' || dest[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

bool	ft_is_only_quotes(char *dest)
{
	int	i;

	i = 0;
	while (dest[i])
	{
		if (dest[i] != '\'' && dest[i] != '\"')
			return (false);
		i++;
	}
	return (true);
}

bool	check_prblm_quotes(char *str)
{
	int		i;
	int		q;
	char	quote;

	i = 0;
	q = 0;
	quote = ft_find_next_quote(str, i);
	while (str[i])
	{
		if (q == 2)
		{
			q = 0;
			quote = ft_find_next_quote(str, i);
		}
		if (str[i] == quote)
			q++;
		i++;
	}
	if (q == 1)
		return (true);
	return (false);
}

void	ft_add_data_and_true(t_minishell *minishell, t_token *token, char quote)
{
	ft_data_adding(minishell, token, quote);
	minishell->token_quotes = true;
}
