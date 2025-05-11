/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:44:19 by simonp            #+#    #+#             */
/*   Updated: 2025/02/19 18:22:54 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	cd_util(t_minishell *minishell, t_token *token)
{
	if (cd_check_arg(token->next))
		return (false);
	if (ft_strcmp(token->next->type, "-") != 0)
		return (false);
	if (cd_arg_count(token->next) > 2)
	{
		write_str("\033[0;31mError\033[0m: invalid option\n", 2);
		minishell->exec.exit_code = 1;
		return (true);
	}
	if (!getenv("OLDPWD"))
	{
		write_str("\033[0;31mError\033[0m: OLDPWD not set or inaccessible\n"\
			, 2);
		minishell->exec.exit_code = 1;
		return (true);
	}
	chdir(getenv("OLDPWD"));
	return (true);
}

void	ft_do_cd(t_minishell *minishell, t_token *token, t_builtin *directory)
{
	if (!token->next)
	{
		if (!getenv("HOME"))
		{
			write_str("\033[0;31mError\033[0m: cd: HOME inaccessible\n", 2);
			minishell->exec.exit_code = 1;
		}
		else
			chdir(getenv("HOME"));
		return ;
	}
	else if (cd_util(minishell, token))
		return ;
	else if (cd_check_arg(token->next))
	{
		write_str("\033[0;31mError\033[0m: cd: too many arguments\n", 2);
		minishell->exec.exit_code = 1;
		return ;
	}
	token = token->next;
	ft_strlcpy(directory->change, token->type, ft_strlen(token->type));
	ft_cd(minishell, directory);
	if (minishell->exec.exit_code != 1)
		minishell->exec.exit_code = 0;
}

int	ft_len_args(t_token *token)
{
	int		len;
	t_token	*tmp;

	len = 1;
	tmp = token;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == ARGUMENT || tmp->token == FLAG)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

int	ft_count_flags(t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token != STDIN && tmp->token != HERE_DOC && \
			tmp->token != FILENAME && tmp->token != STDOUT_ADD && \
			tmp->token != STDOUT)
		{
			count++;
		}
		tmp = tmp->next;
	}
	return (count);
}

void	ft_do_builtin(t_minishell *minishell, t_token *token)
{
	if (ft_strcmp(token->type, "cd") == 0)
		ft_do_cd(minishell, token, &minishell->builtin);
	else if (ft_strcmp(token->type, "echo") == 0)
		ft_do_echo(minishell, token);
	else if (ft_strcmp(token->type, "env") == 0)
		ft_do_env(minishell, minishell->env_link, token);
	else if (ft_strcmp(token->type, "exit") == 0)
		ft_do_exit(minishell, token);
	else if (ft_strcmp(token->type, "export") == 0)
		ft_do_export(minishell, token);
	else if (ft_strcmp(token->type, "unset") == 0)
		ft_do_unset(minishell, token);
	else if (ft_strcmp(token->type, "pwd") == 0)
		ft_pwd(&minishell->builtin);
	else
		printf("ID as BUILTIN but not a builtin.\n");
}
