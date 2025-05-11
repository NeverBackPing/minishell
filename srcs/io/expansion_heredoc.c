/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:15:45 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/21 14:19:04 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_var_name(const char *line, int *i)
{
	int		start;
	char	*var_name;

	start = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	var_name = ft_substr(line, start, *i - start);
	return (var_name);
}

static char	*expand_var(t_minishell *minishell, const char *line, int *i)
{
	char	*var_name;
	char	*value;
	char	*tmp;

	(*i)++;
	if (line[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(minishell->exec.exit_code));
	}
	var_name = get_var_name(line, i);
	if (!var_name)
		return (NULL);
	value = getenv(var_name);
	free(var_name);
	if (!value)
		tmp = ft_strdup("");
	else
		tmp = ft_strdup(value);
	return (tmp);
}

char	*free_tmp(t_minishell *minishell, char *result, \
		char *expanded, char *tmp)
{
	(void)minishell;
	tmp = ft_strjoin(result, expanded);
	free(expanded);
	return (tmp);
}

char	*return_line(char *result, char *tmp)
{
	free(result);
	return (tmp);
}

char	*replace_env_variables(t_minishell *minishell, char *line)
{
	int		i;
	char	*result;
	char	*tmp;
	char	*expanded;
	char	single_char[2];

	i = 0;
	tmp = NULL;
	result = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'))
		{
			expanded = expand_var(minishell, line, &i);
			tmp = free_tmp(minishell, result, expanded, tmp);
		}
		else
		{
			single_char[0] = line[i++];
			single_char[1] = '\0';
			tmp = ft_strjoin(result, single_char);
		}
		result = return_line(result, tmp);
	}
	return (result);
}
