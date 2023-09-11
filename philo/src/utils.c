/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:01:11 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/11 20:24:20 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// This function is similar to usleep but it wait time ms instead of
// microseconds
// 1 microsecond == 0,001ms
void	ft_usleep(unsigned int time)
{
	unsigned long	start;

	start = get_timestamp_in_ms();
	while ((get_timestamp_in_ms() - start) < time)
		usleep(time / 10);
}

void	print(t_philo *philo, char *str)
{
	// mutex_print lock
	printf("%lu %d %s\n",get_timestamp_in_ms() - philo->data->start, philo->rank, str);
	// mutex_print unlock

}

unsigned long	get_timestamp_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	get_len_tab(char **tab)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (tab == NULL)
		return (len);
	while (tab[i] != NULL)
	{
		len++;
		i++;
	}
	return (len);
}
