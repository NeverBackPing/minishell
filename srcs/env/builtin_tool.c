/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:11:39 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/19 19:38:15 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	edit_pwd(t_minishell *minishell, t_env_link **env)
{
	t_env_link	*head;
	char		*pwd;

	pwd = NULL;
	head = *env;
	while (head)
	{
		if (ft_strncmp("PWD=", head->ev, ft_strlen("PWD=")) == 0)
		{
			free(head->ev);
			pwd = getcwd(pwd, sizeof(minishell->builtin.change));
			head->ev = ft_strjoin("PWD=", pwd);
			free(pwd);
			if (!head->ev)
			{
				write_str("Fail malloc\n", 2);
				minishell->exec.exit_code = 5;
				return (true);
			}
			return (false);
		}
		head = head->next;
	}
	return (true);
}

bool	edit_oldpwd(t_minishell *minishell, t_env_link **env)
{
	t_env_link	*head;
	char		*oldpwd;

	oldpwd = NULL;
	head = *env;
	while (head)
	{
		if (ft_strncmp("OLDPWD=", head->ev, ft_strlen("OLDPWD=")) == 0)
		{
			free(head->ev);
			oldpwd = getcwd (oldpwd, sizeof(minishell->builtin.oldpwd));
			head->ev = ft_strjoin("OLDPWD=", oldpwd);
			free(oldpwd);
			if (!head->ev)
			{
				write_str("Fail malloc\n", 2);
				minishell->exec.exit_code = 5;
				return (true);
			}
			return (false);
		}
		head = head->next;
	}
	return (true);
}

bool	already_env(t_minishell *minishell, char *str)
{
	t_env_link	*tmp;
	size_t		lim;

	if (check_double(minishell->env_link, str) && ft_strchr(str, '=') == NULL)
		return (true);
	lim = lim_name(minishell->env_link, str);
	if (lim == 0)
	{
		if (check_double(minishell->env_link, str))
			return (true);
		else
			return (false);
	}
	tmp = minishell->env_link;
	while (tmp)
	{
		if (ft_strncmp((str), tmp->ev, lim) == 0)
		{
			edit_env(minishell, tmp, str, lim);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

bool	ft_echo_tool(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
		i = 1;
	else
		return (false);
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}
