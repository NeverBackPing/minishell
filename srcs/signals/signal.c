/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speladea <speladea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:13:42 by speladea          #+#    #+#             */
/*   Updated: 2024/11/20 18:13:42 by speladea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void	ft_sig_handler(int signal)
{
	(void)signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sig_ctrl_backslash(int signal)
{
	(void)signal;
	printf("Quit (core dumped)\n");
}

void	ft_sig_cmd(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\0', STDOUT_FILENO);
		close(STDIN_FILENO);
	}
}

void	second_sig(void)
{
	signal(SIGINT, ft_sig_cmd);
	signal(SIGQUIT, ft_sig_ctrl_backslash);
	signal(SIGTSTP, SIG_IGN);
}

void	main_signal(t_minishell *minishell)
{
	(void)minishell;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
