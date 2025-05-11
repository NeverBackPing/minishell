/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 19:37:58 by speladea          #+#    #+#             */
/*   Updated: 2025/02/18 19:40:46 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	is_sep_in_ll(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (ft_is_separator_bis(tmp->type[0]))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
