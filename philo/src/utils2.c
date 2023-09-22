/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:38:01 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/22 14:12:37 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	destroy_mutex_tab(pthread_mutex_t *tmp, int size)
{
	while (size >= 0)
	{
		pthread_mutex_destroy(&tmp[size]);
		size--;
	}
}

int	philo_alone(t_philo *philo)
{
	if (philo->data->nb_philos != 1)
		return (0);
	take_fork(philo);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left]);
	ft_usleep(philo->data->time_to_die);
	return (1);
}

void	even_philo_start_thinking(t_philo *philo)
{
	if ((philo->rank % 2 == 0 && philo->eat_count == 0)
		|| (philo->data->nb_philos % 2 != 0 && philo->eat_count == 0
			&& philo->rank == philo->data->nb_philos))
	{
		print(philo, THINK);
		ft_usleep(philo->data->time_to_eat * 0.2);
	}
}

int	check_time_limits(t_data *data)
{
	if (data->time_to_die > 50000 || data->time_to_eat > 50000
		|| data->time_to_sleep > 50000)
	{
		printf("Time limits are too long for this program\n");
		return (0);
	}
	else if (data->time_to_die < 50 || data->time_to_eat < 50
		|| data->time_to_sleep < 50)
	{
		printf("Time limits are too short for this program\n");
		return (0);
	}
	return (1);
}

int	fill_numbers_in_data(t_data *data, char **arg, int nb_args)
{
	data->pb_init_mutex_fork = 0;
	data->finished = 0;
	data->dead = 0;
	if (check_overflow(arg, nb_args))
		return (0);
	data->nb_philos = ft_atoi(arg[1]);
	if (data->nb_philos > 500)
	{
		printf("There is too many philo for this program\n");
		return (0);
	}
	data->time_to_die = ft_atoi(arg[2]);
	data->time_to_eat = ft_atoi(arg[3]);
	data->time_to_sleep = ft_atoi(arg[4]);
	if (!check_time_limits(data))
		return (0);
	if (nb_args == 5)
		data->meals_to_end = ft_atoi(arg[5]);
	else
		data->meals_to_end = -1;
	data->start = get_timestamp_in_ms();
	return (1);
}
