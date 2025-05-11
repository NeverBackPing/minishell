/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:15:53 by simonp            #+#    #+#             */
/*   Updated: 2025/01/24 02:16:09 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	ft_is_pipe(t_token *tmp)
{
	if (ft_strcmp(tmp->type, "|") == 0)
		tmp->token = PIPE;
	return (true);
}

bool	ft_is_std_in(t_token *tmp)
{
	if (ft_strcmp(tmp->type, "<") == 0)
		tmp->token = STDIN;
	return (true);
}

bool	ft_is_std_out(t_token *tmp)
{
	if (ft_strcmp(tmp->type, ">") == 0)
		tmp->token = STDOUT;
	return (true);
}

bool	ft_is_std_out_add(t_token *tmp)
{
	if (ft_strcmp(tmp->type, ">>") == 0)
		tmp->token = STDOUT_ADD;
	return (true);
}

bool	ft_is_here_doc(t_token *tmp)
{
	if (ft_strcmp(tmp->type, "<<") == 0)
		tmp->token = HERE_DOC;
	return (true);
}
