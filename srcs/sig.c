/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:23:58 by hzaz              #+#    #+#             */
/*   Updated: 2024/05/14 13:12:52 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	return_if_sig(int status)
{
	if (WTERMSIG(status) == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (WTERMSIG(status) == SIGQUIT)
		ft_putstr_fd("QUIT (core dumped)\n", STDOUT_FILENO);
	return (128 + WTERMSIG(status));
}

static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/* signal handling for the parent process*/
void	main_signals(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_flags = 0;
	sigint.sa_handler = &handle_sigint;
	sigquit.sa_handler = SIG_IGN;
	sigquit.sa_flags = 0;
	sigemptyset(&sigint.sa_mask);
	sigaction(SIGINT, &sigint, NULL);
	sigemptyset(&sigquit.sa_mask);
	sigaction(SIGQUIT, &sigquit, NULL);
}

void	execute_signals(int pid)
{
	struct sigaction	sig;

	sig.sa_flags = 0;
	sigemptyset(&sig.sa_mask);
	if (pid == 0)
		sig.sa_handler = SIG_DFL;
	else
		sig.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	heredoc_signals(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_flags = 0;
	sigemptyset(&sigint.sa_mask);
	sigquit.sa_flags = 0;
	sigemptyset(&sigquit.sa_mask);
	sigint.sa_handler = &heredoc_sigint;
	sigquit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sigint, NULL);
	sigaction(SIGQUIT, &sigquit, NULL);
}
