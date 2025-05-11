/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:11:39 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/19 19:32:55 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	check_double(t_env_link	*env, char *str)
{
	t_env_link	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp((str), tmp->ev, ft_strlen(str)) == 0)
		{
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

int	lim_name(t_env_link	*env, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	if (check_double(env, str))
		return (i);
	return (0);
}

bool	edit_env(t_minishell *minishell, t_env_link	*tmp, \
		char *str, size_t lim)
{
	size_t	i;

	i = 0;
	while (tmp->ev[i] && tmp->ev[i] != '=')
		i++;
	if (lim == i)
	{
		free(tmp->ev);
		tmp->ev = ft_strdup(str);
		if (!tmp)
		{
			minishell->status = true;
			minishell->exec.exit_code = 5;
			return (true);
		}
		return (true);
	}
	return (false);
}
