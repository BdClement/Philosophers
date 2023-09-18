/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:50:45 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/18 19:32:32 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*watchdog(void *data)
{
	t_philo	*tmp_philo;
	int		i;
	int		eat_count;
	unsigned long	last_meal;


	tmp_philo = (t_philo *)data;
	last_meal = 0;
	while (1)
	{
		i = 0;
		eat_count = 0;
		while (i < tmp_philo->data->nb_philos)
		{
			pthread_mutex_lock(&tmp_philo->data->lock);
			last_meal = (tmp_philo + i)->start_last_meal;
			pthread_mutex_unlock(&tmp_philo->data->lock);
			if (check_death((tmp_philo + i), tmp_philo->data->time_to_die
					, last_meal) == 1)
				return (NULL);
			if (tmp_philo->data->meals_to_end != -1 && tmp_philo->eat_count >= tmp_philo->data->meals_to_end)
				eat_count++;
			i++;
		}
		if (eat_count >= tmp_philo->data->meals_to_end)
		{
			print(tmp_philo, "LE REPAS EST FINI\n");
			tmp_philo->data->finished++;
			return (NULL);
		}
		ft_usleep(2);
	}
	return (NULL);
}

int	check_death(t_philo *philo, unsigned long time_to_die, unsigned long last_meal)
{
	if ((get_timestamp_in_ms() - last_meal) > time_to_die)
	{
		// pthread_mutex_lock(&philo->data->mutex_dead);
		pthread_mutex_lock(&philo->data->lock);
		philo->data->dead++;
		// pthread_mutex_unlock(&philo->data->mutex_dead);
		pthread_mutex_unlock(&philo->data->lock);
		print(philo, DIED);
		return (1);
	}
	return (0);
}

int	is_dead(t_data *data)
{
	int	ret;

	ret = 0;
	// pthread_mutex_lock(&data->mutex_dead);
	pthread_mutex_lock(&data->lock);
	if (data->dead == 1)
		ret = 1;
	// pthread_mutex_unlock(&data->mutex_dead);
	pthread_mutex_unlock(&data->lock);
	return (ret);
}
