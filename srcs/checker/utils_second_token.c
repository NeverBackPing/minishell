/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_second_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:13:36 by simonp            #+#    #+#             */
/*   Updated: 2025/02/21 14:28:21 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	ft_keywords(t_token *tmp)
{
	if (ft_strcmp(tmp->type, "|") == 0 && !tmp->single_q && !tmp->double_q)
		return (tmp->token = PIPE, true);
	if (ft_strcmp(tmp->type, "<") == 0 && !tmp->single_q && !tmp->double_q)
		return (tmp->token = STDIN, true);
	if (ft_strcmp(tmp->type, ">") == 0 && !tmp->single_q && !tmp->double_q)
		return (tmp->token = STDOUT, true);
	if (ft_strcmp(tmp->type, ">>") == 0 && !tmp->single_q && !tmp->double_q)
		return (tmp->token = STDOUT_ADD, true);
	if (ft_strcmp(tmp->type, "<<") == 0 && !tmp->single_q && !tmp->double_q)
		return (tmp->token = HERE_DOC, true);
	if (tmp->type[0] == '-')
		return (tmp->token = FLAG, true);
	return (false);
}

bool	ft_isbuiltin(t_token *tmp)
{
	long unsigned int		i;
	const char				*builtin[] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	if (token_before(tmp) == ARGUMENT || (token_before(tmp) == COMMAND) \
		|| token_before(tmp) == BUILTIN || token_before(tmp) == FLAG)
		return (false);
	i = 0;
	while (i < ((sizeof(builtin) / sizeof(builtin[0])) - 1))
	{
		if (ft_strcmp((const char *)tmp->type, builtin[i]) == 0)
		{
			tmp->token = BUILTIN;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	ft_isexpansion(t_token *tmp)
{
	if (tmp->type[0] == '$')
	{
		tmp->token = EXPANSION;
		return (true);
	}
	return (false);
}

bool	ft_isfile(t_token *tmp)
{
	if (token_before(tmp) == HERE_DOC)
	{
		tmp->token = ENDOFFILE;
		return (true);
	}
	else if (token_before(tmp) != STDIN && token_before(tmp) != STDOUT && \
		token_before(tmp) != STDOUT_ADD)
		return (false);
	tmp->token = FILENAME;
	return (true);
}

bool	ft_iscmd(t_token *tmp)
{
	if (check_before(tmp))
		return (false);
	if (token_before(tmp) == FLAG || token_before(tmp) == ARGUMENT || \
		token_before(tmp) == BUILTIN \
		|| token_before(tmp) == COMMAND)
		return (false);
	if (token_before(tmp) == FILENAME && tmp->type[0] == '.')
		return (false);
	if (cmd_before(tmp) && token_before(tmp) != PIPE && \
		(token_before(tmp) != ENDOFFILE && token_before(tmp) != FILENAME))
		return (false);
	tmp->token = COMMAND;
	return (true);
}
