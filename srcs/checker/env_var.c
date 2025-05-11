/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:39:17 by simonp            #+#    #+#             */
/*   Updated: 2025/02/04 00:21:27 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join_content(char *t_type, char *var_name, char *var_content, int j)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_strdup("");
	while (t_type[i] != '\0')
	{
		if (t_type[i] == '$' && ft_count_d(t_type, i) == true && i == j)
		{
			if (ft_check_name(t_type, var_name, i + 1))
			{
				new_str = ft_do_join(new_str, var_content, t_type[i], 'C');
				i += ft_strlen(var_name);
				break ;
			}
		}
		new_str = ft_do_join(new_str, var_content, t_type[i], 'T');
		i++;
	}
	while (t_type[i] != '\0')
	{
		i++;
		new_str = ft_do_join(new_str, var_content, t_type[i], 'T');
	}
	return (new_str);
}

void	ft_get_join_content(t_minishell *minishell, t_token *token, int i)
{
	char	*var_name;
	char	*var_content;
	char	*tmp;
	char	*str;

	var_name = ft_get_var_name(token->type + i);
	var_content = ft_get_var_content(minishell->env_link, var_name);
	if (var_content[0] == '\0')
	{
		ft_del_false_var(token, var_name, i);
		free(var_name);
		return ;
	}
	str = ft_strdup(token->type);
	if (ft_strcmp(var_content, "$") != 0)
	{
		tmp = ft_join_content(str, var_name, var_content, i);
		free (token->type);
		token->type = ft_strdup(tmp);
		free (tmp);
	}
	free(var_name);
	free(var_content);
	free(str);
}

void	ft_expand(t_minishell *minishell, t_token *token, char *t_type)
{
	int	i;

	i = 0;
	while (token->type && token->type[i])
	{
		if (token->type[i] == '$' && ft_strlen(token->type) > 1)
		{
			t_type = ft_strdup(token->type);
			if (ft_count_d(token->type, i) == true)
			{
				ft_get_join_content(minishell, token, i);
				if (i >= (int)ft_strlen(token->type))
				{
					free(t_type);
					break ;
				}
			}
			if (token->type[i] == '$' && ft_strcmp(t_type, token->type) != 0)
				i--;
			free (t_type);
		}
		i++;
	}
}

int	ft_is_exit_code(t_minishell *minishell, t_token *token, int i)
{
	int	stock;

	while (token->type[i])
	{
		if (token->type[i] == '$' && token->type[i + 1] == '?')
			break ;
		i++;
	}
	if (i == (int)ft_strlen(token->type))
		return (i);
	stock = i;
	ft_exit_code_join(minishell, token, i);
	return (stock);
}

void	ft_check_expand(t_minishell *minishell)
{
	t_token	*token;
	char	*tmp;
	char	*t_type;
	int		i;

	token = minishell->token;
	t_type = ft_strdup(token->type);
	while (token)
	{
		i = 0;
		if ((ft_strchr(token->type, '$')) && token->single_q == false)
		{
			if (find_nbr(token->type))
			{
				tmp = ft_strdup(token->type);
				free(token->type);
				token->type = new_t_type(tmp);
				free(tmp);
			}
			check_exit_code(minishell, token, i);
			ft_expand(minishell, token, t_type);
		}
		token = token->next;
	}
	free (t_type);
}
