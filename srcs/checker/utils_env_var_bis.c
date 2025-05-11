/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_var_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:10:46 by simonp            #+#    #+#             */
/*   Updated: 2025/02/03 01:22:21 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_count_d(char *str, int i)
{
	int	count;

	count = 0;
	if (str[i] == '$' && i >= 0)
	{
		while (str[i] == '$')
		{
			count++;
			i--;
			if (i < 0)
				break ;
		}
	}
	if (count % 2 != 0)
		return (true);
	return (false);
}

char	*ft_do_join(char *new_str, char *var_content, char c, char type)
{
	char	*tmp;

	tmp = new_str;
	if (type == 'C')
		new_str = ft_strjoin(new_str, var_content);
	else if (type == 'T')
		new_str = ft_strcharjoin(new_str, c);
	free(tmp);
	return (new_str);
}

void	ft_del_false_var(t_token *token, char *var_name, int i)
{
	int		j;
	char	*new_str;
	char	*tmp;

	j = 0;
	new_str = ft_strdup("");
	while (j < i)
	{
		tmp = new_str;
		new_str = ft_strcharjoin(new_str, token->type[j]);
		free(tmp);
		j++;
	}
	j = j + ft_strlen(var_name) + 1;
	while (token->type[j])
	{
		tmp = new_str;
		new_str = ft_strcharjoin(new_str, token->type[j]);
		free(tmp);
		j++;
	}
	free(token->type);
	token->type = new_str;
}

char	*ft_exit_code_tmp(t_token *token, int i)
{
	int		j;
	char	*tmp;
	char	*new_tmp;

	j = 0;
	tmp = ft_strdup("");
	while (j < i)
	{
		new_tmp = ft_strcharjoin(tmp, token->type[j]);
		free(tmp);
		tmp = new_tmp;
		j++;
	}
	return (tmp);
}

void	ft_exit_code_join(t_minishell *minishell, t_token *token, int i)
{
	char	*tmp;
	char	*itoa_str;
	char	*new_tmp;

	tmp = ft_exit_code_tmp(token, i);
	itoa_str = ft_itoa(minishell->exec.exit_code);
	new_tmp = ft_strjoin(tmp, itoa_str);
	free(tmp);
	free(itoa_str);
	tmp = new_tmp;
	i = i + 2;
	while (token->type[i])
	{
		new_tmp = ft_strcharjoin(tmp, token->type[i]);
		free(tmp);
		tmp = new_tmp;
		i++;
	}
	free(token->type);
	token->type = tmp;
}
