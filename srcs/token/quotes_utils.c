/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:22:43 by simonp            #+#    #+#             */
/*   Updated: 2025/02/10 16:51:52 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_quote(const char *str, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_len_without_quotes(char *dest)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (dest[i])
	{
		if (dest[i] != '\'' && dest[i] != '\"')
			len++;
		i++;
	}
	return (len);
}

char	ft_get_first_quote(char *dest)
{
	int		i;
	char	quote;

	i = 0;
	quote = '\0';
	while (dest[i])
	{
		if (dest[i] == '\'' || dest[i] == '\"')
		{
			quote = dest[i];
			break ;
		}
		i++;
	}
	return (quote);
}

int	find_first_quote(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	find_last_quote_index(char *str)
{
	int	last_index;
	int	i;

	last_index = -1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			last_index = i;
		}
		i++;
	}
	return (last_index);
}
