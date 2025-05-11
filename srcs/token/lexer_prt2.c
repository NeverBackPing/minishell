/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_prt2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:11:39 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/01 18:27:17 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	isbuiltin(t_minishell *minishell, t_token *token, char *promt)
{
	long unsigned int		i;
	t_token					*tmp;
	const char				*builtin[] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	if (last_token(token) == ARGUMENT || (last_token(token) == COMMAND))
		return (false);
	i = 0;
	tmp = NULL;
	while (i < ((sizeof(builtin) / sizeof(builtin[0])) - 1))
	{
		if (ft_strcmp((const char *)promt, builtin[i]) == 0)
		{
			if (promt[ft_strlen(promt)] != '\0')
				return (false);
			tmp = new_token(BUILTIN, promt);
			if (!tmp)
				return (true);
			add_data(&minishell->token, tmp, false, false);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	isexpansion(t_minishell *minishell, char *promt)
{
	int8_t	type;
	t_token	*tmp;

	if (promt[0] != '$')
		return (false);
	tmp = NULL;
	if (promt[0] == '$' && promt[1] == '$')
	{
		tmp = new_token(ARGUMENT, promt);
		if (!tmp)
			return (true);
		add_data(&minishell->token, tmp, false, false);
		return (true);
	}
	minishell->arg = EXPANSION;
	type = EXPANSION;
	tmp = new_token(type, promt);
	if (!tmp)
		return (true);
	add_data(&minishell->token, tmp, false, false);
	return (true);
}

bool	isfile(t_minishell *minishell, t_token *token, char *promt)
{
	int8_t	type;
	t_token	*tmp;

	if (last_token(token) == HERE_DOC)
	{
		tmp = new_token(ENDOFFILE, promt);
		if (!tmp)
			return (true);
		return (add_data(&minishell->token, tmp, false, false), true);
	}
	else if (last_token(token) != STDIN && last_token(token) != STDOUT && \
		last_token(token) != STDOUT_ADD)
		return (false);
	tmp = NULL;
	minishell->arg = FILENAME;
	type = FILENAME;
	tmp = new_token(type, promt);
	if (!tmp)
		return (true);
	add_data(&minishell->token, tmp, false, false);
	return (true);
}

bool	ispipe(t_minishell *minishell, char **promt, char *arg)
{
	int8_t	type;
	t_token	*tmp;

	(void)promt;
	tmp = NULL;
	minishell->arg = PIPE;
	type = PIPE;
	if (ft_strncmp(arg, "|", ft_strlen(arg)) != 0)
	{
		if (!count_keyword(arg))
		{
			minishell->syntax = true;
			return (false);
		}
		return (false);
	}
	tmp = new_token(type, arg);
	if (!tmp)
		return (true);
	add_data(&minishell->token, tmp, false, false);
	return (true);
}

bool	issdtout_add(t_minishell *minishell, char **promt, char *arg)
{
	int8_t	type;
	t_token	*tmp;

	(void)promt;
	tmp = NULL;
	minishell->arg = STDOUT_ADD;
	type = STDOUT_ADD;
	if (ft_strncmp(arg, ">>", ft_strlen(arg)) != 0)
	{
		if (!count_multi_keywords(arg))
		{
			minishell->syntax = true;
			return (false);
		}
		return (false);
	}
	tmp = new_token(type, arg);
	if (!tmp)
		return (true);
	add_data(&minishell->token, tmp, false, false);
	return (true);
}
