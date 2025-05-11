/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-19 16:46:09 by speladea          #+#    #+#             */
/*   Updated: 2024-11-19 16:46:09 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (true);
		i++;
	}
	return (false);
}

bool	change_shlvl(t_minishell *minishell, t_env_link *env, char *tmp_num)
{
	char	*new_shlvl;

	new_shlvl = ft_strjoin("SHLVL=", tmp_num);
	if (!new_shlvl)
	{
		minishell->status = true;
		write_str("\033[0;31mError\033[0m: Out of memory", 2);
		minishell->exec.exit_code = errno;
		return (true);
	}
	free(env->ev);
	env->ev = ft_strdup(new_shlvl);
	if (!env->ev)
	{
		free(new_shlvl);
		minishell->status = true;
		write_str("\033[0;31mError\033[0m: Out of memory", 2);
		minishell->exec.exit_code = errno;
		return (true);
	}
	free(new_shlvl);
	return (false);
}

bool	get_digit(t_minishell *minishell, t_env_link *env, int index_satrt)
{
	int		num;
	char	*tmp_num;

	num = 0;
	tmp_num = NULL;
	if (ft_isnum((env->ev + index_satrt)))
		return (false);
	num = ft_atoi((env->ev + index_satrt));
	tmp_num = ft_itoa(++num);
	if (!tmp_num)
	{
		minishell->status = true;
		write_str("\033[0;31mError\033[0m: Out of memory", 2);
		minishell->exec.exit_code = errno;
		return (false);
	}
	if (change_shlvl(minishell, env, tmp_num))
		return (free(tmp_num), false);
	return (free(tmp_num), true);
}

bool	ft_edit_shelvl_(t_minishell *minishell, t_env_link *env, int i_start)
{
	bool	pass;

	pass = true;
	if (env->ev[i_start + 1] == '\0')
		pass = false;
	i_start++;
	if (pass && get_digit(minishell, env, i_start))
		return (false);
	else
	{
		free(env->ev);
		env->ev = ft_strdup("SHLVL=1");
		if (!env->ev)
		{
			minishell->status = true;
			write_str("\033[0;31mError\033[0m: Out of memory", 2);
			minishell->exec.exit_code = errno;
			return (true);
		}
	}
	return (false);
}

bool	ft_init_shlvl(t_minishell *minishell, t_env_link **env)
{
	int			i;
	t_env_link	*tmp_link;

	i = 0;
	tmp_link = *env;
	while (tmp_link)
	{
		if (!ft_strncmp(tmp_link->ev, "SHLVL=", ft_strlen("SHLVL=")))
			break ;
		tmp_link = tmp_link->next;
	}
	if (!tmp_link)
		return (false);
	while (tmp_link->ev[i] && tmp_link->ev[i] != '=')
		i++;
	ft_edit_shelvl_(minishell, tmp_link, i);
	return (false);
}
