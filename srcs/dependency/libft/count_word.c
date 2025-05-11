/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:11:39 by sjossain          #+#    #+#             */
/*   Updated: 2024/12/24 14:15:29 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/libft.h>

int	words(const char *str)
{
	int			count;
	int			in_word;
	const char	*ptr = str;

	count = 0;
	in_word = 0;
	while (*ptr)
	{
		if (*ptr == ' ')
		{
			if (in_word)
				in_word = 0;
		}
		else
		{
			if (!in_word)
			{
				in_word = 1;
				count++;
			}
		}
		ptr++;
	}
	return (count);
}
