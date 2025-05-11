/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:54:30 by sjossain          #+#    #+#             */
/*   Updated: 2024/12/02 16:33:40 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

char	*put_str_env(t_minishell *minishell, t_env_link **env, char *str)
{
	t_env_link	*head;

	head = *env;
	(void)minishell;
	while (head)
	{
		if (ft_strncmp(str, head->ev, ft_strlen(str)) == 0)
			return (head->ev);
		head = head->next;
	}
	return (NULL);
}

int	count_nodes(t_env_link *env)
{
	int			count;
	t_env_link	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**convert_env_to_array(t_minishell *minishell, t_env_link *head)
{
	char			**env_array;
	size_t			i;
	const size_t	count = count_nodes(head);

	i = 0;
	env_array = (char **)malloc((count + 1) * sizeof(char *));
	if (!env_array)
	{
		minishell->status = true;
		clear_link_token(&(minishell->token));
		clear_link_env(&(minishell->env_link));
		write_str("\033[0;31merror\033[0m: Out of memory\n", 2);
		return (NULL);
	}
	while (head)
	{
		env_array[i] = head->ev;
		head = head->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
