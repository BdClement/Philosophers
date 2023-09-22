/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 13:49:23 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/22 14:26:30 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_overflow(char **arg, int size)
{
	int	i;

	i = 1;
	while (i <= size)
	{
		if (overflow(arg[i]))
		{
			printf("This program takes only int as argument\n");
			return (1);
		}
		i++;
	}
	return (0);
}

// Check if the atoi of the string is bigger than an int
int	overflow(const char *nptr)
{
	long int	value;
	int			sign;

	value = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	if (ft_strlen(nptr) == 0 || ft_isdigit(*nptr) == 0)
		return (1);
	while (*nptr >= '0' && *nptr <= '9')
	{
		value = value * 10 + (*nptr - 48);
		nptr++;
		if ((value * sign) > INT_MAX || (value * sign) < INT_MIN)
			return (1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	if (!nptr)
		return (res * sign);
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = res * 10 + nptr[i] - 48;
		i++;
	}
	return (res * sign);
}

// This function checks if there is differents characters
// than digits, and if the no arg is 0
int	check_only_positive_nb(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av != NULL && av[i])
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		if (ft_atoi(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char **av)
{
	if (!check_only_positive_nb(av))
	{
		printf("This program should only take strictly ");
		printf("potive numbers as arguments\n");
		return (0);
	}
	return (1);
}
