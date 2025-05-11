/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcharjoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-01 16:53:54 by speladea          #+#    #+#             */
/*   Updated: 2024-12-01 16:53:54 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

size_t	ft_strlen1(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*charjoin(char *dest, const char *s1, char c)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = c;
	i++;
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcharjoin(char const *s1, char c)
{
	char	*dest;
	size_t	total_size;

	if (s1 == NULL)
		return (NULL);
	total_size = ft_strlen1(s1) + 1;
	dest = malloc((total_size + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	dest = charjoin(dest, s1, c);
	return (dest);
}

/*
int	main(void)
{
	char	*str1;
	char	c;
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str1 = "my favorite animal is";
	c = 'c';
	result = ft_strcharjoin(str1, c);
	printf("%s", result);
}
*/
