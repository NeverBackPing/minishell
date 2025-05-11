/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:14:49 by simonp            #+#    #+#             */
/*   Updated: 2025/02/16 03:35:42 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	track_arg_(t_minishell *minishell, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->token != PIPE)
	{
		if (tmp->token == ARGUMENT || tmp->token == FLAG)
			return (false);
		tmp = tmp->next;
	}
	minishell->builtin.echo = NULL;
	ft_echo(&minishell->builtin);
	return (true);
}

void	ft_do_echo(t_minishell *minishell, t_token *token)
{
	int	i;

	if (track_arg_(minishell, token))
		return ;
	token = token->next;
	i = 0;
	minishell->builtin.echo = (char **)malloc((ft_len_args(token) + 1) * \
		sizeof(char *));
	while (token && token->token != PIPE)
	{
		if (token->token == ARGUMENT || token->token == FLAG)
		{
			minishell->builtin.echo[i] = ft_strdup(token->type);
			i++;
		}
		token = token->next;
	}
	minishell->builtin.echo[i] = NULL;
	ft_echo(&minishell->builtin);
	dest_free(minishell->builtin.echo);
	minishell->builtin.echo = NULL;
	minishell->exec.exit_code = 0;
}

void	ft_do_env(t_minishell *minishell, t_env_link *env, t_token *token)
{
	if (token->next != NULL)
	{
		if (token->next->token == ARGUMENT)
		{
			write_str("Error: No such file or directory.\n", 2);
			minishell->exec.exit_code = 127;
			return ;
		}
		if (token->next->token == FLAG)
		{
			write_str("Error: Invalid option.\n", 2);
			minishell->exec.exit_code = 125;
			return ;
		}
	}
	ft_env(minishell, env);
	minishell->exec.exit_code = 0;
}

void	ft_do_export(t_minishell *minishell, t_token *token)
{
	int	i;

	i = 0;
	if (token->next == NULL || token->next->token == STDOUT_ADD || \
		token->next->token == STDOUT)
	{
		ft_env_export(minishell, minishell->env_link);
		return ;
	}
	token = token->next;
	minishell->builtin.arg_export = malloc((ft_len_args(token) \
		+ 1) * sizeof(char *));
	while (token && (token->token == ARGUMENT || token->token == FLAG))
	{
		minishell->builtin.arg_export[i] = ft_strdup(token->type);
		token = token->next;
		i++;
	}
	minishell->builtin.arg_export[i] = NULL;
	ft_export(minishell, minishell->builtin.arg_export);
	dest_free(minishell->builtin.arg_export);
	minishell->builtin.arg_export = NULL;
}

void	ft_do_unset(t_minishell *minishell, t_token *token)
{
	int	i;

	if (token->next == NULL)
		return ;
	token = token->next;
	i = 0;
	minishell->builtin.arg_unset = malloc((ft_len_args(token) \
		+ 1) * sizeof(char *));
	while (token && token->token == ARGUMENT)
	{
		minishell->builtin.arg_unset[i] = ft_strdup(token->type);
		i++;
		token = token->next;
	}
	minishell->builtin.arg_unset[i] = NULL;
	ft_unset(minishell, minishell->builtin.arg_unset);
}
