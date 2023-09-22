/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:01:11 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/22 15:36:25 by clbernar         ###   ########.fr       */
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

// This function is more precise than the existing usleep function
// The existing function usleep is a non deterministic function
// that can sleep a different time when called two times with the same
// input. The function ft_usleep avoid it
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
	if (meal_is_over(philo->data))
		printf(" %lu %s\n", get_timestamp_in_ms() - philo->data->start, str);
	else
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
