/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:02:48 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/01/10 14:31:19 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_pid = 0;

void	reset(char *c, int *a, int pid)
{
	*c = 0xff;
	*a = 0;
	g_pid = pid;
}

void	handler(int sig, siginfo_t *info, void *context)
{
	static char	c = 0xff;
	static int	shifter;

	(void)context;
	if (g_pid != info->si_pid)
		reset(&c, &shifter, info->si_pid);
	if (sig == SIGUSR1)
		c = c | 128 >> shifter;
	else if (sig == SIGUSR2)
		c = c ^ 128 >> shifter;
	shifter++;
	if (shifter == 8)
	{
		write(1, &c, 1);
		c = 0xff;
		shifter = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putnbr(getpid());
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
