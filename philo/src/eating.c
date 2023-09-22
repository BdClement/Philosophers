/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 17:56:57 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/22 13:54:55 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_fork(t_philo *philo)
{
	if (philo->rank % 2 != 0)
		odd_philo_take_fork(philo);
	else
		even_philo_take_fork(philo);
	if (philo->data->nb_philos != 1 && !is_dead(philo->data)
		&& !meal_is_over(philo->data))
		print(philo, FORK);
}

void	odd_philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_fork[philo->left]);
	philo->data->fork[philo->left]++;
	if (is_dead(philo->data) || meal_is_over(philo->data))
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->left]);
		return ;
	}
	print(philo, FORK);
	if (philo->data->nb_philos != 1)
	{
		pthread_mutex_lock(&philo->data->mutex_fork[philo->right]);
		philo->data->fork[philo->right]--;
		if (is_dead(philo->data) || meal_is_over(philo->data))
		{
			pthread_mutex_unlock(&philo->data->mutex_fork[philo->left]);
			pthread_mutex_unlock(&philo->data->mutex_fork[philo->right]);
			return ;
		}
	}
}

void	even_philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_fork[philo->right]);
	philo->data->fork[philo->right]++;
	if (is_dead(philo->data) || meal_is_over(philo->data))
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->right]);
		return ;
	}
	print(philo, FORK);
	pthread_mutex_lock(&philo->data->mutex_fork[philo->left]);
	philo->data->fork[philo->left]--;
	if (is_dead(philo->data) || meal_is_over(philo->data))
	{
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->right]);
		pthread_mutex_unlock(&philo->data->mutex_fork[philo->left]);
		return ;
	}
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
	if (!is_dead(philo->data) && !meal_is_over(philo->data))
	{
		take_fork(philo);
		if (is_dead(philo->data) || meal_is_over(philo->data))
			return ;
		print(philo, EAT);
		pthread_mutex_lock(&philo->data->lock);
		philo->start_last_meal = get_timestamp_in_ms();
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_lock(&philo->data->lock);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->data->lock);
		ft_usleep(philo->data->time_to_eat);
		put_fork_back(philo);
	}
}
