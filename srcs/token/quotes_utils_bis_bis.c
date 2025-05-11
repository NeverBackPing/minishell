/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils_bis_bis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:11:50 by simonp            #+#    #+#             */
/*   Updated: 2025/02/11 20:38:47 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_counting_whole_quote(char *dest, char quote)
{
	int	i;
	int	q;

	i = 0;
	q = 0;
	while (dest[i])
	{
		if (dest[i] == quote)
			q++;
		i++;
	}
	return (q);
}

char	ft_find_next_quote(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	if (i == (int)ft_strlen(str))
		return (' ');
	return (str[i]);
}

void	ft_str_quotes(t_minishell *minishell, char *dest, int i, char quote)
{
	int		x;
	int		j;
	int		q;
	char	*tmp;

	x = i;
	j = 0;
	q = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(dest) + 1));
	while (dest[i])
	{
		if (q % 2 == 0)
			if (do_q(minishell, dest, quote, i))
				break ;
		if (dest[i] != quote)
			tmp[j++] = dest[i];
		q = incr_q(dest, quote, q, i);
		i++;
	}
	tmp[j] = '\0';
	add_the_new_token(minishell, dest, tmp, x);
}

void	ft_add_sep(t_minishell *minishell, char *dest, int pos, int len)
{
	t_token	*token;
	char	*tmp;
	int		i;

	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return ;
	i = 0;
	while (dest[pos] && len > 0)
	{
		tmp[i] = dest[pos];
		i++;
		pos++;
		len--;
	}
	tmp[i] = '\0';
	token = new_token(ARGUMENT, tmp);
	add_data(&minishell->token, token, false, false);
	free(tmp);
}

int	ft_is_there_sep(t_minishell *minishell, char *dest, char quote, int pos)
{
	int	i;

	i = 0;
	while (dest[pos] && ft_isalnum(dest[pos]) == 0 && dest[pos] != quote)
	{
		i++;
		pos++;
	}
	if (i > 0)
		ft_add_sep(minishell, dest, pos - i, i);
	return (i);
}
