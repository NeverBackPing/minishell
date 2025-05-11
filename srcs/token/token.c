/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:02:03 by simonp            #+#    #+#             */
/*   Updated: 2025/01/22 13:02:03 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	keywords(t_minishell *minishell, char **promt, char *arg)
{
	minishell->syntax = false;
	minishell->status = false;
	if (minishell->token_quotes)
	{
		minishell->token_quotes = false;
		return (true);
	}
	if (ispipe(minishell, promt, arg))
		return (true);
	else if (isstdin(minishell, promt, arg))
		return (true);
	else if (isstdout(minishell, promt, arg))
		return (true);
	else if (issdtout_add(minishell, promt, arg))
		return (true);
	else if (is_here_doc(minishell, promt, arg))
		return (true);
	return (false);
}

void	token_init(t_minishell *minishell, char *promt)
{
	t_token	*tmp;

	if (minishell->token_quotes)
	{
		minishell->token_quotes = false;
		return ;
	}
	if (isbuiltin(minishell, minishell->token, promt))
		return ;
	else if (isexpansion(minishell, promt))
		return ;
	else if (isfile(minishell, minishell->token, promt))
		return ;
	else if (iscmd(minishell, minishell->token, promt))
		return ;
	else
	{
		tmp = new_token(ARGUMENT, promt);
		if (!tmp)
			return ;
		add_data(&minishell->token, tmp, false, false);
	}
}

bool	token_tool(t_minishell *minishell, char **prompt, char *str)
{
	ft_check_quotes(minishell, prompt, (str));
	if (minishell->syntax)
	{
		error_quote(minishell);
		return (false);
	}
	return (true);
}

bool	token_tool2(t_minishell *minishell, char **prompt, char *str)
{
	if (!(keywords(minishell, prompt, str)) && !(minishell->status))
	{
		if (minishell->syntax)
		{
			error_lexer(minishell);
			return (false);
		}
		token_init(minishell, str);
	}
	return (true);
}

void	ft_token(t_minishell *minishell)
{
	int		i;
	char	**promt;

	promt = ft_split_token(minishell->prompt, ' ');
	if (!promt)
	{
		minishell->status = true;
		return ;
	}
	i = 0;
	while (promt[i] != NULL)
	{
		if (!token_tool(minishell, promt, promt[i]))
			break ;
		if (!token_tool2(minishell, promt, promt[i]))
			break ;
		if (minishell->status)
			break ;
		i++;
	}
	dest_free(promt);
}
