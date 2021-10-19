/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnessrou <tnessrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:28:27 by tnessrou          #+#    #+#             */
/*   Updated: 2021/10/18 21:31:26 by tnessrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	ft_isspace(const char *sym)
{
	if ((*sym < 14 && *sym > 8) || *sym == 32)
		return (1);
	if (*sym == '-' && ft_isdigit(*(sym + 1)))
		return (-1);
	if (*sym == '+' && ft_isdigit(*(sym + 1)))
		return (1);
	return (0);
}

static	int	num_len(long long num)
{
	int	len;

	len = 1;
	while (num / 10)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static	int	is_overflow(const long long *num, const int *sign, const int modulo)
{
	if (num_len(*num) == 19)
		return (1);
	if (*num * 10 < 9223372036854775800)
		return (0);
	if (*sign == 1)
	{
		if (*num * 10 == 9223372036854775800 && modulo < 8)
			return (0);
	}
	else
		if (*num * 10 == 9223372036854775800 && modulo < 9)
			return (0);
	return (1);
}

static	int	ll_overflow(const long long *num, const int *sign, const int modulo)
{
	int	result;

	result = is_overflow(num, sign, modulo);
	if (result)
	{
		if (*sign == 1)
			return (-2);
		return (-1);
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			space;
	int			sign;

	result = 0;
	space = 1;
	sign = 1;
	while (ft_isdigit(*str) || (ft_isspace(str) && space))
	{
		if (ft_isspace(str) && space)
			sign = ft_isspace(str);
		if (ft_isdigit(*str))
		{
			if (ll_overflow(&result, &sign, *str - 48))
				return (ll_overflow(&result, &sign, *str - 48) + 1);
			space = 0;
			result *= 10;
			result += *str - 48;
		}
		str++;
	}
	return (result * sign);
}

// int main()
// {
// 	char *str = " \t \n \f \r 00081710118101111fewf";
// 	printf("%d\n", atoi(str));
// 	printf("%d\n", ft_atoi(str));
// }
