/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stderr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:54:30 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/05 13:56:02 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	write_str(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

void	write_str2(char *str, char *str2, int fd)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	tmp = ft_strjoin(str, str2);
	if (tmp == NULL)
	{
		perror("Out of memory\n");
		return ;
	}
	if (ft_strchr(tmp, '\n') == NULL)
	{
		tmp2 = ft_strjoin(tmp, "\n");
		if (tmp2 == NULL)
		{
			perror("Out of memory\n");
			return ;
		}
		write(fd, tmp2, ft_strlen(tmp2));
		free(tmp);
		free(tmp2);
		return ;
	}
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}
