/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:12:31 by simonp            #+#    #+#             */
/*   Updated: 2025/01/28 03:37:11 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	ft_token_type(t_token *tmp)
{
	if (ft_isfile(tmp))
		return ;
	else if (ft_isbuiltin(tmp))
		return ;
	else if (ft_iscmd(tmp))
		return ;
	else if (tmp->token == STRING)
		tmp->token = ARGUMENT;
}

void	ft_reset_type(t_minishell *minishell)
{
	t_token	*tmp;

	tmp = minishell->token;
	while (tmp)
	{
		tmp->token = STRING;
		tmp = tmp->next;
	}
}

void	ft_second_token(t_minishell *minishell)
{
	t_token	*tmp;

	ft_reset_type(minishell);
	tmp = minishell->token;
	while (tmp)
	{
		if (tmp->token == STRING)
		{
			if (!ft_keywords(tmp))
				ft_token_type(tmp);
		}
		tmp = tmp->next;
	}
}
