/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 02:09:08 by simonp            #+#    #+#             */
/*   Updated: 2025/02/02 20:08:52 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_return_var_name(char *var_name)
{
	char	*result;

	result = ft_strdup(var_name);
	free (var_name);
	return (result);
}

char	*ft_get_var_name(char *token_type)
{
	int			i;
	int			j;
	char		*var_name;

	var_name = malloc((ft_strlen(token_type) + 1) * sizeof(char));
	j = 0;
	i = 1;
	while (token_type[i])
	{
		if (ft_isalpha(token_type[i]) != 1 && token_type[i] != '_')
			break ;
		var_name[j] = token_type[i];
		i++;
		j++;
	}
	var_name[j] = '\0';
	return (ft_return_var_name(var_name));
}

char	*ft_get_var_content(t_env_link *env, char *var_name)
{
	size_t	len;

	if (var_name[0] == '\0')
		return (ft_strdup("$"));
	len = ft_strlen(var_name);
	while (env)
	{
		if (ft_strncmp(env->ev, var_name, len) == 0)
		{
			if (env->ev[len] == '=')
				return (ft_strdup(env->ev + len + 1));
		}
		env = env->next;
	}
	return ("");
}

bool	ft_check_name(char *token_type, char *var_name, int pos)
{
	if (token_type[pos] != '\0')
		if (ft_strncmp(token_type + pos, var_name, ft_strlen(var_name)) == 0)
			return (true);
	return (false);
}

bool	ft_free_false(char *var_name)
{
	free(var_name);
	return (false);
}
