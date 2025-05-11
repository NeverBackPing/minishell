/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-19 16:46:09 by speladea          #+#    #+#             */
/*   Updated: 2024-11-19 16:46:09 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	g_exit_loop = 0;

int	main(int ac, char **av, char *ev[])
{
	t_minishell	minishell;

	(void)ac;
	(void)av;
	init_minishell(&minishell, ev);
	while (1)
	{
		prompt_init(&minishell);
		if (exit_minishell(&minishell))
			break ;
		add_history(minishell.prompt);
		ft_token(&minishell);
		ft_checker(&minishell);
		if (minishell.token && !ft_error_checker(&minishell))
		{
			if (!(minishell.syntax) || !(minishell.status))
			{
				if (!init_structure_cmd(&minishell))
					exec(&minishell, minishell.token);
			}
		}
		reset(&minishell);
	}
	return (0);
}
