/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:11:39 by sjossain          #+#    #+#             */
/*   Updated: 2025/01/26 05:26:55 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

char	*ft_strchr_without_end(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	return (NULL);
}

bool	count_keyword(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '|' || arg[i] == '<' || arg[i] == '>')
		{
			count++;
			if (count > 1 && (arg[i - 1] == '|' && arg[i - 1] != '<' \
				&& arg[i - 1] != '>'))
				return (false);
		}
		i++;
		if (arg[i] != '|' && arg[i] != '<' && arg[i] != '>')
			count = 0;
	}
	return (true);
}

bool	count_multi_keywords(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '<' || arg[i] == '>')
		{
			count++;
			if (count > 2)
				return (false);
		}
		i++;
		if (arg[i] != '<' && arg[i] != '>')
			count = 0;
	}
	return (true);
}
