/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoted_var_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:38:54 by simonp            #+#    #+#             */
/*   Updated: 2025/02/23 14:38:55 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_var_name(t_minishell *minishell, char *name)
{
	t_env_link	*env;

	env = minishell->env_link;
	while (env)
	{
		if (ft_strncmp(env->ev, name + 1, ft_strlen(name + 1)) == 0)
		{
			if (env->ev[ft_strlen(name + 1)] == '=')
				return (true);
		}
		env = env->next;
	}
	return (false);
}

char	*get_var_name_quotes(char *str, char quote, int i)
{
	char	*new_str;
	char	*temp;

	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	temp = new_str;
	new_str = ft_strcharjoin(new_str, '\"');
	free(temp);
	while (str[i])
	{
		if (str[i] == quote || (str[i] == '$' && i > 0))
			break ;
		temp = new_str;
		new_str = ft_strcharjoin(new_str, str[i]);
		free(temp);
		i++;
	}
	temp = new_str;
	new_str = ft_strcharjoin(new_str, '\"');
	free(temp);
	return (new_str);
}
