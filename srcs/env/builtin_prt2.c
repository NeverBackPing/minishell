/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:54:30 by sjossain          #+#    #+#             */
/*   Updated: 2024/12/02 16:33:40 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	ft_env_export(t_minishell *minishell, t_env_link *env)
{
	t_env_link	*tmp;

	tmp = env;
	(void)minishell;
	while (tmp)
	{
		ft_putstr("export: ");
		ft_putstr(tmp->ev);
		ft_putstr("\n");
		tmp = tmp->next;
	}
}

void	ft_export(t_minishell *minishell, char **str)
{
	t_env_link	*tmp;
	int			i;

	i = 0;
	while (str && str[i])
	{
		if (ft_is_valid_id(str[i]) && !already_env(minishell, str[i]))
		{
			tmp = new_env(str[i]);
			if (!tmp)
				minishell->error.status = true;
			add_env(&minishell->env_link, tmp);
		}
		else if (minishell->token->next->double_q == false && \
			minishell->token->next->single_q == false && \
			ft_is_valid_id(str[i]) == false)
		{
			write_str2("\033[0;31mError\033[0m: Not a valid identifier : "\
				, str[i], 2);
			minishell->exec.exit_code = 1;
			return ;
		}
		i++;
	}
	minishell->exec.exit_code = 0;
}

void	unset_variable(t_minishell *minishell, char *str)
{
	t_env_link	*current;

	current = minishell->env_link;
	while (current)
	{
		if (ft_its_the_name(current->ev, str) == true)
		{
			if (current->prev)
				current->prev->next = current->next;
			else
				minishell->env_link = current->next;
			if (current->next)
				current->next->prev = current->prev;
			free(current->ev);
			free(current);
			return ;
		}
		current = current->next;
	}
}

void	ft_unset(t_minishell *minishell, char **str)
{
	int	i;

	if (!str || !*str)
	{
		minishell->status = false;
		return ;
	}
	i = 0;
	while (str[i])
	{
		if (is_just_name(str[i]))
			unset_variable(minishell, str[i]);
		free(str[i]);
		i++;
	}
	free(str);
	minishell->exec.exit_code = 0;
}

void	ft_cd(t_minishell *minishell, t_builtin *builtin)
{
	edit_oldpwd(minishell, &minishell->env_link);
	if (chdir(builtin->change) == 0)
	{
		edit_pwd(minishell, &minishell->env_link);
	}
	else
	{
		write_str("No such file or directory\n", 2);
		minishell->exec.exit_code = 1;
	}
	if (getcwd(builtin->last_directory, PATH_MAX) == NULL)
	{
		printf("Cannot get current working directory path\n" );
	}
}
