/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_prt4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 03:25:39 by simonp            #+#    #+#             */
/*   Updated: 2025/02/09 16:31:30 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	is_valid_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

bool	ft_its_the_name(char *ev, char *unset)
{
	int	i;

	i = 0;
	while (unset[i])
	{
		if (ev[i] != unset[i])
			return (false);
		i++;
	}
	if (ev[i] == '=')
		return (true);
	return (false);
}
