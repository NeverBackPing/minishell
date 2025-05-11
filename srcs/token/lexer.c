/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:11:39 by sjossain          #+#    #+#             */
/*   Updated: 2024/12/24 14:15:29 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	isstdin(t_minishell *minishell, char **promt, char *arg)
{
	int8_t	type;
	t_token	*tmp;

	(void)promt;
	tmp = NULL;
	minishell->arg = STDIN;
	type = STDIN;
	if (ft_strncmp(arg, "<", ft_strlen(arg)) != 0)
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

bool	isstdout(t_minishell *minishell, char **promt, char *arg)
{
	int8_t	type;
	t_token	*tmp;

	(void)promt;
	tmp = NULL;
	minishell->arg = STDOUT;
	type = STDOUT;
	if (ft_strncmp(arg, ">", ft_strlen(arg)) != 0)
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

bool	is_here_doc(t_minishell *minishell, char **promt, char *arg)
{
	int8_t	type;
	t_token	*tmp;

	(void)promt;
	tmp = NULL;
	minishell->arg = HERE_DOC;
	type = HERE_DOC;
	if (ft_strncmp(arg, "<<", ft_strlen(arg)) != 0)
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

bool	token_pipe(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return (false);
	tmp = lst;
	while (tmp)
	{
		if (tmp->token == COMMAND)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

bool	iscmd(t_minishell *minishell, t_token *token, char *promt)
{
	int8_t	type;
	t_token	*tmp;

	if (last_token(token) == ARGUMENT || (last_token(token) == BUILTIN))
		return (false);
	if (last_token(token) == COMMAND || last_token(token) == FILENAME)
		return (false);
	if (token_pipe(token) && last_token(token) != PIPE)
		return (false);
	tmp = NULL;
	minishell->arg = COMMAND;
	type = COMMAND;
	tmp = new_token(type, promt);
	if (!tmp)
		return (true);
	add_data(&minishell->token, tmp, false, false);
	return (true);
}
