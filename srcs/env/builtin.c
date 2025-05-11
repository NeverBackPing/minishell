/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:54:30 by sjossain          #+#    #+#             */
/*   Updated: 2024/12/02 16:33:40 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	ft_exit(t_minishell *minishell, int exit_code)
{
	clear_exit(minishell);
	printf("exit\n");
	exit(exit_code);
}

void	ft_do_exit(t_minishell *minishell, t_token *token)
{
	ft_do_exit_bis(minishell, token);
	if (ft_isdigit(token->next->type) == 1 || (token->next->type[0] == '+' \
				&& ft_isdigit(token->next->type + 1) == 1))
	{
		if (!token->next->next)
			ft_exit(minishell, ft_atoi(token->next->type));
		else if (ft_is_separator(token->next->next->type[0]) == false)
		{
			write_str("exit\nbash: exit: too many arguments\n", 2);
			minishell->exec.exit_code = 1;
		}
	}
	else if (ft_is_separator(token->next->type[0]) == false)
	{
		if (token->next->type[0] == '-' && token->next->type[1] >= '0' && \
			token->next->type[1] <= '9')
			ft_exit(minishell, 256 - ft_atoi(token->next->type + 1));
		else
		{
			write_str("bash: exit: numeric argument required\n", 2);
			ft_exit(minishell, 2);
		}
	}
}

void	ft_env(t_minishell *minishell, t_env_link *env)
{
	t_env_link	*tmp;

	tmp = env;
	(void)minishell;
	while (tmp)
	{
		if (ft_strchr(tmp->ev, '=') != NULL)
		{
			ft_putstr(tmp->ev);
			ft_putstr("\n");
		}
		tmp = tmp->next;
	}
}

void	ft_echo(t_builtin *builtin)
{
	int	i;

	if (!builtin->echo)
	{
		printf("\n");
		return ;
	}
	i = 0;
	while (builtin->echo[i])
	{
		if (ft_echo_tool(builtin->echo[i]))
			i++;
		else
			break ;
	}
	while (builtin->echo[i])
	{
		ft_putstr(builtin->echo[i]);
		if (builtin->echo[i] != NULL && builtin->echo[i + 1] != NULL)
			ft_putstr(" ");
		i++;
	}
	if (!ft_echo_tool(builtin->echo[0]))
		printf("\n");
}

void	ft_pwd(t_builtin *builtin)
{
	if (getcwd(builtin->directory, PATH_MAX) == NULL)
	{
		printf("pwd: error retrieving current directory\n" );
	}
	else
		printf("%s\n", builtin->directory);
}
