/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:56:57 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/18 19:47:23 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_fork(t_philo *philo)
{
	if (philo->rank % 2 != 0)
	{
		pthread_mutex_lock(&philo->data->mutex_fork[philo->left]);
		philo->data->fork[philo->left]++;
		if (is_dead(philo->data) || philo->data->finished == 1)
		{
			pthread_mutex_unlock(&philo->data->mutex_fork[philo->left]);
			return ;
		}
		print(philo, FORK);
		pthread_mutex_lock(&philo->data->mutex_fork[philo->right]);
		philo->data->fork[philo->right]--;
		if (is_dead(philo->data) || philo->data->finished == 1)
		{
			pthread_mutex_unlock(&philo->data->mutex_fork[philo->left]);
			pthread_mutex_unlock(&philo->data->mutex_fork[philo->right]);
			return ;
		}
	}
	else
	{
		pthread_mutex_lock(&philo->data->mutex_fork[philo->right]);
		philo->data->fork[philo->right]++;
		if (is_dead(philo->data) || philo->data->finished == 1)
		{
			pthread_mutex_unlock(&philo->data->mutex_fork[philo->right]);
			return ;
		}
		print(philo, FORK);
		pthread_mutex_lock(&philo->data->mutex_fork[philo->left]);
		philo->data->fork[philo->left]--;
		if (is_dead(philo->data) || philo->data->finished == 1)
		{
			pthread_mutex_unlock(&philo->data->mutex_fork[philo->right]);
			pthread_mutex_unlock(&philo->data->mutex_fork[philo->left]);
			return ;
		}
	}
	print(philo, FORK);
}

void	put_fork_back(t_philo *philo)
{
	if (philo->rank % 2 != 0)
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->left]);
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->right]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->right]);
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->left]);
	}
}

void	eating(t_philo *philo)
{
	if (!is_dead(philo->data) || philo->data->finished != 1)
	{
		take_fork(philo);
		if (is_dead(philo->data) || philo->data->finished == 1) // A supprimer ?
			return ;
		print(philo, EAT);
		pthread_mutex_lock(&philo->data->lock);
		philo->start_last_meal = get_timestamp_in_ms();
		pthread_mutex_unlock(&philo->data->lock);
		ft_usleep(philo->data->time_to_eat);
		pthread_mutex_lock(&philo->data->lock);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->data->lock);
		put_fork_back(philo);
	}
}

void	*routine(void *data)
{
	t_philo		*tmp_philo;

	tmp_philo = (t_philo *)data;
	// Les philos pairs et le derniers philo si le nb de philo est impair
	// commencent par penser
	if ((tmp_philo->rank % 2 == 0 && tmp_philo->eat_count == 0)
		|| (tmp_philo->data->nb_philos % 2 != 0 && tmp_philo->eat_count == 0
			&& tmp_philo->rank == tmp_philo->data->nb_philos))
	{
		print(tmp_philo, THINK);
		ft_usleep(tmp_philo->data->time_to_eat * 0.2);
		// Plus indispensable puisque on a modifie l'ordre des lock/unlock
	}
	while (1)
	{
		eating(tmp_philo);
		if (!is_dead(tmp_philo->data) || tmp_philo->data->finished != 1)
		{
			print(tmp_philo, SLEEP);
			ft_usleep(tmp_philo->data->time_to_sleep);
		}
		if (!is_dead(tmp_philo->data) || tmp_philo->data->finished != 1)
			print(tmp_philo, THINK);
		if (is_dead(tmp_philo->data) || tmp_philo->data->finished != 1)
			break ;
	}
	return (NULL);
}
