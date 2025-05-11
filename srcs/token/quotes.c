/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:16:49 by simonp            #+#    #+#             */
/*   Updated: 2025/01/20 18:16:49 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_copy(char *str, char quote)
{
	int		i;
	int		j;
	char	*copy;

	copy = malloc((ft_len_without_quotes(str) + 1) * sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != quote)
		{
			copy[j] = str[i];
			j++;
		}
		i++;
	}
	copy[j] = '\0';
	return (copy);
}

bool	ft_env_var(t_minishell *minishell, char *dest)
{
	int		i;
	char	quote;
	char	*tmp;
	t_token	*token;

	i = 0;
	while (dest[i] != '=')
		i++;
	if (dest[i + 1] == '\'' || dest[i + 1] == '\"')
		quote = dest[i + 1];
	else
		return (false);
	tmp = ft_copy(dest, quote);
	token = new_token(ARGUMENT, tmp);
	add_data(&minishell->token, token, false, true);
	minishell->token_quotes = true;
	free (tmp);
	return (true);
}

bool	var_no_quotes(char *str, int q, int swtch, int dollar)
{
	int		i;
	char	quote;

	i = 0;
	quote = ft_find_next_quote(str, 0);
	while (str[i])
	{
		if (str[i] == quote)
			q++;
		if (str[i] == '$')
			dollar++;
		i++;
		if (q == 2)
		{
			swtch++;
			q = 0;
			quote = ft_find_next_quote(str, i);
		}
	}
	if (dollar >= swtch + 1)
		return (true);
	return (false);
}

bool	ft_quotes_inside(t_minishell *minishell, char *dest)
{
	int		i;
	char	quote;
	char	*new_dest;
	char	*new_dest2;

	i = 0;
	quote = ft_get_first_quote(dest);
	if (ft_is_separator(dest[i]))
		i = ft_is_there_sep(minishell, dest, quote, i);
	new_dest = rid_of_glued_quotes(dest);
	if (ft_strchr(new_dest, '$') != 0 && to_find_quote(new_dest))
	{
		new_dest2 = find_unquoted_var(minishell, new_dest, quote);
		if (var_no_quotes(new_dest2, 0, 0, 0))
			new_dest2 = find_unquoted_var(minishell, new_dest2, \
				ft_get_first_quote(new_dest2));
		ft_str_quotes(minishell, new_dest2, i, quote);
		free(new_dest2);
	}
	else
	{
		ft_str_quotes(minishell, new_dest, i, quote);
		free (new_dest);
	}
	return (true);
}

void	ft_check_quotes(t_minishell *minishell, char **promt, char *dest)
{
	unsigned long	i;

	if (to_find_quote(dest) == false)
		return ;
	if (check_prblm_quotes(dest))
	{
		minishell->syntax = true;
		return ;
	}
	i = 0;
	while (promt[i] != NULL)
	{
		if (ft_strcmp(promt[i], dest) == 0)
			break ;
		i++;
	}
	if ((ft_strchr(dest, '=') == 0) && (ft_quotes_inside(minishell, dest)))
		return ;
	if ((ft_strchr(dest, '=') != 0) && (ft_env_var(minishell, dest)))
		return ;
	return ;
}
