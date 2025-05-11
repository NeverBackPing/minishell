/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:08:46 by sjossain          #+#    #+#             */
/*   Updated: 2025/02/02 22:00:24 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp_ascii(const char *s1, int ascii)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' )
	{
		if ((unsigned char)s1[i] != ascii)
			return ((unsigned char)(s1[i]) - (unsigned char)ascii);
		i++;
	}
	return (0);
}
