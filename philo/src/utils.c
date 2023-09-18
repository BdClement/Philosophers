/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:01:11 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/15 13:15:10 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void	ft_usleep(unsigned int time)
{
	unsigned long	start;

	start = get_timestamp_in_ms();
	while ((get_timestamp_in_ms() - start) < time)
		usleep(time / 10);
}

void	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	printf(" %lu %d %s\n", get_timestamp_in_ms() - philo->data->start,
		philo->rank, str);
	pthread_mutex_unlock(&philo->data->mutex_print);
}

unsigned long	get_timestamp_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
