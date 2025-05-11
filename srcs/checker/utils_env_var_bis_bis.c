/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_var_bis_bis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:16:01 by speladea          #+#    #+#             */
/*   Updated: 2025/02/19 19:16:02 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_exit_code(t_minishell *minishell, t_token *token, int i)
{
	while (token->type[i])
		i = ft_is_exit_code(minishell, token, i);
}

bool	find_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (true);
		i++;
	}
	return (false);
}

bool	is_nbr(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	is_no_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			while (isalpha(str[i]))
				i++;
			if (str[i] == ' ')
				return (false);
		}
		i++;
	}
	return (true);
}

char	*new_t_type(char *str)
{
	int		i;
	char	*new_s;
	char	*tmp;

	i = 0;
	new_s = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && find_nbr(str + i) && is_no_space(str + i))
		{
			while (str[i] && !is_nbr(str[i]))
				i++;
			while (str[i] && is_nbr(str[i]))
				i++;
		}
		else
		{
			tmp = new_s;
			new_s = ft_strcharjoin(new_s, str[i]);
			free(tmp);
			i++;
		}
	}
	return (new_s);
}
