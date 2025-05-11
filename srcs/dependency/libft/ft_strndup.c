/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simonp <simonp@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:23:07 by sjossain          #+#    #+#             */
/*   Updated: 2025/01/22 15:04:14 by simonp           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *s, int n)
{
	char		*ret;

	ret = (char *)malloc(n + 1);
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, s, n + 1);
	return (ret);
}
