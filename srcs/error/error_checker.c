/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:53:17 by simonp            #+#    #+#             */
/*   Updated: 2025/02/18 19:51:42 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	ft_do_error(t_minishell *minishell, int token)
{
	if (token == PIPE)
	{
		write_str \
		("\033[0;31mbash\033[0m: syntax error near unexpected token `|'\n", 2);
		minishell->exec.exit_code = 2;
	}
	else if (minishell->token->next == NULL)
	{
		write_str \
		("\033[0;31mbash\033[0m: syntax error near unexpected token `newline'\n"\
		, 2);
		minishell->exec.exit_code = 2;
	}
	else
	{
		write_str \
		("\033[0;31mbash\033[0m: syntax error near unexpected token\n"\
		, 2);
		minishell->exec.exit_code = 2;
	}
	clear_link_token(&(minishell->token));
}

bool	check_next_is_nullmii(t_minishell *minishell, t_token *token)
{
	if (token->next == NULL)
	{
		ft_do_error(minishell, token->token);
		return (true);
	}
	return (false);
}

bool	error_in_token(t_minishell *minishell, t_token *token)
{
	if (token->token == PIPE || token->token == STDIN || token->token == STDOUT \
		|| token->token == HERE_DOC || token->token == STDOUT_ADD || \
		token->token == STDIN_OUT)
	{
		if (check_next_is_nullmii(minishell, token))
			return (true);
	}
	if (token->token == PIPE)
	{
		if (token->prev == NULL || token->prev->token == STDOUT || \
			token->prev->token == HERE_DOC || token->prev->token == STDOUT_ADD \
			|| token->prev->token == STDIN)
			return (ft_do_error(minishell, token->token), true);
		if (token->next->token != ARGUMENT && token->next->token != COMMAND \
			&& token->next->token != BUILTIN && token->next->token != \
			FILENAME && token->next->token != ENDOFFILE && token->next == NULL)
		{
			ft_do_error(minishell, token->token);
			return (true);
		}
	}
	return (false);
}

bool	error_next_sep(t_minishell *minishell, t_token *token)
{
	if (token->next == NULL)
		return (false);
	if (token->token == PIPE)
	{
		if (token->next->token == PIPE)
		{
			ft_do_error(minishell, token->token);
			return (true);
		}
	}
	if (token->token == STDIN || token->token == STDOUT || token->token \
		== HERE_DOC || token->token == STDOUT_ADD)
	{
		if (token->next->token == STDIN || token->next->token == STDOUT || \
			token->next->token == HERE_DOC || token->next->token == \
			STDOUT_ADD || token->next->token == PIPE)
		{
			ft_do_error(minishell, token->token);
			return (true);
		}
	}
	return (false);
}

bool	ft_error_checker(t_minishell *minishell)
{
	t_token	*token;

	token = minishell->token;
	while (token)
	{
		if (error_next_sep(minishell, token))
			return (true);
		if (error_in_token(minishell, token))
			return (true);
		token = token->next;
	}
	return (false);
}
