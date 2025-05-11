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

bool	loop_env(t_minishell *minishell, char **ev)
{
	t_env_link	*tmp;
	int			i;

	i = 0;
	tmp = NULL;
	while (ev[i])
	{
		tmp = new_env(ev[i]);
		if (!tmp)
		{
			clear_link_env(&minishell->env_link);
			minishell->status = true;
			write_str("Fail malloc\n", 2);
			return (true);
		}
		add_env(&minishell->env_link, tmp);
		i++;
	}
	return (false);
}

bool	check_env(char **ev)
{
	int	i;

	i = 0;
	while (ev[i])
	{
		if (ft_strncmp(ev[i], "USER", ft_strlen("USER")) == 0)
			return (true);
		i++;
	}
	return (false);
}

char	**init_path(char **str)
{
	int		i;
	char	**dest;

	i = 0;
	dest = (char **)malloc(5 * sizeof(char *));
	if (!dest)
		return (NULL);
	while (str[i])
	{
		dest[i] = ft_strdup(str[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

bool	init_new_env(t_minishell *minishell, char *pwd, char **ev)
{
	char	**str;

	minishell->error.env_null = true;
	pwd = getcwd(pwd, sizeof(minishell->builtin.directory));
	str = (char **)malloc(5 * sizeof(char *));
	if (!str)
	{
		minishell->exec.exit_code = 5;
		return (write_str("Fail malloc\n", 2), true);
	}
	str[0] = ft_strjoin("PWD=", pwd);
	str[1] = ft_strdup("SHLVL=1");
	str[2] = ft_strjoin("OLDPWD=", pwd);
	str[3] = ft_strdup("_=/usr/bin/env");
	str[4] = NULL;
	ev = init_path(str);
	if (!ev)
	{
		minishell->exec.exit_code = 5;
		return (write_str("Fail malloc\n", 2), true);
	}
	dest_free(str);
	free(pwd);
	loop_env(minishell, ev);
	return (dest_free(ev), true);
}

void	init_env(t_minishell *minishell, char **ev)
{
	char	*pwd;

	pwd = NULL;
	if (!getenv("USER"))
	{
		if (init_new_env(minishell, pwd, ev))
			return ;
	}
	if (loop_env(minishell, ev))
		return ;
	ft_init_shlvl(minishell, &minishell->env_link);
}
