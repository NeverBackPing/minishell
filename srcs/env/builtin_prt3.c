/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_prt3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 03:25:39 by simonp            #+#    #+#             */
/*   Updated: 2025/02/19 18:30:36 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	ft_do_exit_bis(t_minishell *minishell, t_token *token)
{
	if (!token->next)
		ft_exit(minishell, minishell->exec.exit_code);
}

bool	ft_is_valid_id(char *str)
{
	int	i;

	if (str[0] == '=' && ft_strlen(str) == 1)
		return (false);
	if (str[0] >= 48 && str[0] <= 57)
		return (false);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	is_just_name(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	i = 1;
	while (str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	ft_nothing_after_eq(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (str[i + 1] == '\0')
		return (true);
	return (false);
}

bool	is_valid_name(const char *str)
{
	int		i;
	char	*equal_sign;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (false);
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign || equal_sign == str)
		return (false);
	if (ft_nothing_after_eq((char *)str))
		return (true);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (true);
		if (!is_valid_char(str[i]))
			return (false);
		i++;
	}
	return (true);
}
