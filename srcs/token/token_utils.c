/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 05:18:05 by simonp            #+#    #+#             */
/*   Updated: 2025/01/30 23:19:06 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	printer_list(t_token **head)
{
	t_token		*current;
	int			i;
	const char	*token[] = {"ARGUMENT", "BUILTIN", "COMMAND", "ENDOFFILE", \
		"EXPANSION", "FILENAME", "FOLDER", "OPERATOR", \
		"HERE_DOC", "OPTION", "PIPE", "PROGRAM", "STDIN", "STDOUT", \
		"STDOUT_ADD", "STRING", "UNDEFINE", "VARIABLE", "FLAG", "NEW_UNDEFINE", \
		"HEREADD", "STDIN_OUT", "IS_TAB"};

	i = 0;
	current = *head;
	while (current != NULL)
	{
		printf("Nb: %d| Type: %d %s | Content: %s\n", i, current->token, \
			token[current->token], current->type);
		current = current->next;
		i++;
	}
}

int	last_token(t_token *lst)
{
	t_token	*tmp;
	int		token;

	if (!lst)
		return (-1);
	tmp = lst;
	token = 0;
	token = tmp->token;
	while (tmp)
	{
		if (tmp->next == NULL)
			return (token);
		tmp = tmp->next;
		token = tmp->token;
	}
	return (token);
}
