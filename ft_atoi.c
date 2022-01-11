/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhadiri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:54:13 by ykhadiri          #+#    #+#             */
/*   Updated: 2022/01/09 15:09:47 by ykhadiri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	getsign(char c)
{
	int	signn;

	signn = 1;
	if (c == '-')
		return (-1);
	return (signn);
}

static int	rslt(int _signcount, int _number, int _sign)
{
	if (_signcount > 1)
		return (0);
	return (_number * _sign);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	number;
	int	signcount;

	i = 0;
	sign = 1;
	number = 0;
	signcount = 0;
	while ((str[i] >= '\t' && str[i] <= '\r')
		|| str[i] == '\n' || str[i] == ' ')
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		signcount++;
		sign *= getsign(str[i]);
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (rslt(signcount, number, sign));
}
