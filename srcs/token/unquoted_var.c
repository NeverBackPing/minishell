/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquoted_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 14:37:50 by simonp            #+#    #+#             */
/*   Updated: 2025/02/23 14:38:22 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_quotes(char *str, int i, int pos)
{
	int		j;
	int		k;
	char	*new_str;

	j = 0;
	k = 0;
	new_str = malloc((ft_strlen(str) + 3) * sizeof(char));
	while (str[j])
	{
		if (j == pos || j == i + 1)
			new_str[k++] = '\"';
		new_str[k] = str[j];
		k++;
		j++;
	}
	new_str[k] = '\0';
	return (new_str);
}

char	*if_else_str(char *str, char *var_name, int i, int pos)
{
	if (pos == 0)
		str = ft_strjoin(var_name, str + i + 1);
	else
		str = add_quotes(str, i, pos);
	return (str);
}

static char	*handle_var_name(char *str, char **var_name, t_pars *p)
{
	char	*old_str;

	free(*var_name);
	*var_name = get_var_name_quotes(str, p->quote, p->pos);
	old_str = str;
	str = if_else_str(str, *var_name, p->i, p->pos);
	free(old_str);
	free(*var_name);
	*var_name = ft_strdup("");
	return (str);
}

void	update_quotes(char *str, char **var_name, t_pars *p)
{
	if (str[p->i] == p->quote)
		p->q++;
	if (p->q == 2)
	{
		p->pos = p->i + 1;
		p->q = 0;
		p->quote = find_first_quote(str + p->i);
		free(*var_name);
		*var_name = ft_strdup("");
	}
}

char	*find_unquoted_var(t_minishell *minishell, char *str, char quote)
{
	t_pars	*p;
	char	*var_name;
	char	*tmp;

	p = &minishell->pars;
	p->i = 0;
	p->pos = 0;
	p->q = 0;
	p->quote = quote;
	var_name = ft_strdup("");
	while (str[p->i])
	{
		tmp = var_name;
		var_name = ft_strcharjoin(var_name, str[p->i]);
		free(tmp);
		if (is_var_name(minishell, var_name) && p->q == 0)
			str = handle_var_name(str, &var_name, p);
		update_quotes(str, &var_name, p);
		p->i++;
	}
	free(var_name);
	return (str);
}
