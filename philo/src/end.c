/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:50:45 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/22 14:30:22 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_death(t_philo *philo, unsigned long time_to_die,
	unsigned long last_meal)
{
	if ((get_timestamp_in_ms() - last_meal) > time_to_die)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->dead++;
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
	pthread_mutex_lock(&data->lock);
	if (data->dead == 1)
		ret = 1;
	pthread_mutex_unlock(&data->lock);
	return (ret);
}

int	meal_is_over(t_data *data)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&data->lock);
	if (data->finished == 1)
		ret = 1;
	pthread_mutex_unlock(&data->lock);
	return (ret);
}

// This function is the wathdog routine that checks if
// a philo died or if they all have eaten enough
void	*watchdog(void *data)
{
	t_philo			*tmp_philo;
	int				nb_finished;
	unsigned long	last_meal;

	tmp_philo = (t_philo *)data;
	last_meal = 0;
	while (1)
	{
		nb_finished = 0;
		if (check_watchdog(tmp_philo, &nb_finished))
			return (NULL);
		if (tmp_philo->data->meals_to_end != -1
			&& nb_finished >= tmp_philo->data->nb_philos)
		{
			pthread_mutex_lock(&tmp_philo->data->lock);
			tmp_philo->data->finished++;
			pthread_mutex_unlock(&tmp_philo->data->lock);
			print(tmp_philo, "Meal is over");
			return (NULL);
		}
		ft_usleep(2);
	}
	return (NULL);
}

int	check_watchdog(t_philo *tmp_philo, int *nb_finished)
{
	int				i;
	int				meals_completed;
	unsigned long	last_meal;

	i = 0;
	last_meal = 0;
	meals_completed = 0;
	while (i < tmp_philo->data->nb_philos)
	{
		pthread_mutex_lock(&tmp_philo->data->lock);
		last_meal = (tmp_philo + i)->start_last_meal;
		pthread_mutex_unlock(&tmp_philo->data->lock);
		if (check_death((tmp_philo + i), tmp_philo->data->time_to_die
				, last_meal) == 1)
			return (1);
		pthread_mutex_lock(&tmp_philo->data->lock);
		meals_completed = tmp_philo[i].eat_count;
		pthread_mutex_unlock(&tmp_philo->data->lock);
		if (tmp_philo->data->meals_to_end != -1
			&& meals_completed >= tmp_philo->data->meals_to_end)
				*nb_finished += 1;
		i++;
	}
	return (0);
}
