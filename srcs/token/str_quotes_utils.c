/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_quotes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:57:33 by speladea          #+#    #+#             */
/*   Updated: 2025/02/19 20:57:34 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_struct_data(t_minishell *minishell, t_token *token)
{
	if (minishell->pars.link == 1)
	{
		minishell->pars.link = 0;
		token->link = true;
	}
}

void	add_the_new_token(t_minishell *minishell, char *dest, char *tmp, int x)
{
	t_token	*token;

	token = new_token(ARGUMENT, tmp);
	change_struct_data(minishell, token);
	ft_add_data_and_true(minishell, token, ft_find_next_quote(dest, x));
	free(tmp);
}

bool	do_q(t_minishell *minishell, char *dest, char quote, int i)
{
	char	tmp_quote;

	tmp_quote = quote;
	quote = ft_find_next_quote(dest, i);
	if (quote != tmp_quote && quote != ' ')
	{
		ft_str_quotes(minishell, dest, i, quote);
		minishell->pars.link = 1;
		return (true);
	}
	return (false);
}
