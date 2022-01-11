/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 18:37:09 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/01/10 14:35:03 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	if (str)
	{
		i = 0;
		while (str[i])
			i++;
	}
	return (i);
}

void	send_mssj(char *mssj, int pid)
{
	int	i;
	int	shift;

	i = -1;
	while (++i <= ft_strlen(mssj))
	{
		shift = -1;
		while (++shift < 8)
		{
			if (mssj[i] & (128 >> shift))
			{
				if (kill(pid, SIGUSR1) == -1)
					exit(1);
			}
			else
			{
				if (kill(pid, SIGUSR2) == -1)
					exit(1);
			}
			usleep(800);
		}
	}
}

void	handler(int signum)
{
	(void)signum;
	ft_putstr("OK");
}

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	sa;

	if (argc != 3)
	{
		ft_putstr("Error, Invalid Parametters!");
		exit(1);
	}
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;
	sigaction(SIGUSR1, &sa, NULL);
	pid = ft_atoi(argv[1]);
	send_mssj(argv[2], pid);
	return (0);
}
