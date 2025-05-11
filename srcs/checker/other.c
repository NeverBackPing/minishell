/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:43:30 by simonp            #+#    #+#             */
/*   Updated: 2025/01/24 02:18:41 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

bool	ft_keyw_1len(t_token *tmp)
{
	if (ft_strcmp(tmp->type, "|") == 0)
	{
		tmp->token = PIPE;
		return (true);
	}
	else if (ft_strcmp(tmp->type, "<") == 0)
	{
		tmp->token = STDIN;
		return (true);
	}
	else if (ft_strcmp(tmp->type, ">") == 0)
	{
		tmp->token = STDOUT;
		return (true);
	}
	return (false);
}

bool	ft_keyw_2len(t_token *tmp)
{
	if (ft_strcmp(tmp->type, ">>") == 0)
	{
		tmp->token = STDOUT_ADD;
		return (true);
	}
	else if (ft_strcmp(tmp->type, "<<") == 0)
	{
		tmp->token = HERE_DOC;
		return (true);
	}
	return (false);
}

bool	ft_keywords_beta(t_token *tmp)
{
	if (ft_strlen(tmp->type) == 1)
	{
		if (ft_keyw_1len(tmp))
			return (true);
	}
	else if (ft_strlen(tmp->type) == 2)
	{
		if (ft_keyw_2len(tmp))
			return (true);
	}
	return (false);
}

void	print_before(t_minishell *minishell)
{
	int			i;
	t_token		*tmp;
	const char	*token[] = {\
		"ARGUMENT", "BUILTIN", "COMMAND", "ENDOFFILE", "EXPANSION", \
		"FILENAME", "FOLDER", "OPERATOR", \
		"HERE_DOC", "OPTION", "PIPE", "PROGRAM", "STDIN", "STDOUT", \
		"STDOUT_ADD", "STRING", "UNDEFINE", "VARIABLE", "NEW_UNDEFINE" \
	};

	i = 0;
	tmp = minishell->token;
	while (tmp)
	{
		if (i == 0)
			printf("\n\nBEFORE: NULL\nNOW: Type: %s | Content: %s\n\n", \
				token[tmp->token], tmp->type);
		else
		{
			printf("BEFORE: Type: %s | Content: %s\nNOW: Type: %s | Content: \
				%s\n\n", token[tmp->prev->token], tmp->prev->type, \
					token[tmp->token], tmp->type);
		}
		tmp = tmp->next;
		i++;
	}
}
