/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 13:02:03 by simonp            #+#    #+#             */
/*   Updated: 2025/02/18 19:47:22 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	error_lexer(t_minishell *minishell)
{
	if (minishell->token)
	{
		clear_link_token(&minishell->token);
		minishell->token = NULL;
	}
	write_str("\033[0;31mbash\033[0m: syntax error near unexpected token\n", 2);
	minishell->exec.exit_code = 2;
}

void	error_quote(t_minishell *minishell)
{
	if (minishell->token)
	{
		clear_link_token(&minishell->token);
		minishell->token = NULL;
	}
	write_str("\033[0;31mbash\033[0m: wrong EOF while looking for match\n", 2);
}
