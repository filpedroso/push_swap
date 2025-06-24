/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:49:08 by filpedroso        #+#    #+#             */
/*   Updated: 2025/06/24 11:49:08 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_numlen(int num)
{
	int	len;

	if (num == INT_MIN)
		return (11);
	len = 1;
	if (num < 0)
	{
		num = -num;
		len++;
	}
	while (num >= 10)
	{
		num /= 10;
		len++;
	}
	return (len);
}

long	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ')
		str++;
	if (*str == '-')
	{
		str++;
		sign = -sign;
	}
	if (!*str || *str < '0' || *str > '9')
		return (LONG_MAX);
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result * sign);
}

int	ft_max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

void	ft_putstr_fd(const char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}
