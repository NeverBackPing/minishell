/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:44:19 by simonp            #+#    #+#             */
/*   Updated: 2025/02/19 18:25:16 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	cd_arg_count(t_token *token)
{
	int		i;
	int		count;
	t_token	*tmp;

	i = 0;
	count = 0;
	tmp = token;
	while (tmp->type[i])
	{
		if (tmp->type[i] == '-')
			count++;
		i++;
	}
	return (count);
}

bool	cd_check_arg(t_token *token)
{
	t_token	*tmp;

	if (!token->next)
		return (false);
	tmp = token->next;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == ARGUMENT || tmp->token == FLAG)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
