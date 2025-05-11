/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 03:38:19 by simonp            #+#    #+#             */
/*   Updated: 2025/01/27 03:43:24 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_q(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool	check_closed(char *prompt)
{
	int		i;
	char	first_q;

	i = 0;
	while (prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '\"')
		{
			first_q = prompt[i];
			break ;
		}
		i++;
	}
	i++;
	while (prompt[i])
	{
		if ((prompt[i] == '\'' || prompt[i] == '\"') && \
			prompt[i] != first_q && count_quote(prompt, prompt[i]) % 2 != 0)
			return (false);
		i++;
	}
	return (true);
}

char	*rid_of_glued_quotes(char *dest)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(dest) + 1));
	while (dest[i])
	{
		if (is_q(dest[i]) && is_q(dest[i + 1]) && dest[i] == dest[i + 1] && \
			check_closed(dest + i))
			i++;
		else
			tmp[j++] = dest[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

void	ft_data_adding(t_minishell *minishell, t_token *token, char quote)
{
	if (quote == '\'')
		add_data(&minishell->token, token, true, false);
	else if (quote == '\"')
		add_data(&minishell->token, token, false, true);
	else
		add_data(&minishell->token, token, false, false);
}
