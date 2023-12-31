/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:58:09 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/22 13:56:17 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	*init_fork(int nb_philos)
{
	int	*tmp;
	int	i;

	tmp = NULL;
	i = 0;
	tmp = malloc(sizeof(int) * nb_philos);
	if (tmp == NULL)
	{
		printf("Memory allocation problem on fork tab\n");
		return (NULL);
	}
	while (i < nb_philos)
	{
		*(tmp + i) = 0;
		i++;
	}
	return (tmp);
}

void	init_philo_struct(t_philo *philo, int i, t_data *data)
{
	philo->rank = i + 1;
	philo->data = data;
	philo->left = philo->rank - 1;
	if (philo->rank == philo->data->nb_philos)
		philo->right = 0;
	else
		philo->right = philo->rank;
	philo->start_last_meal = philo->data->start;
	philo->eat_count = 0;
	return ;
}

struct s_philo	*init_tab_philo(t_data *data)
{
	struct s_philo	*tmp;
	int				i;

	i = 0;
	tmp = NULL;
	tmp = malloc(sizeof(t_philo) * data->nb_philos);
	if (tmp == NULL)
	{
		printf("Memory allocation problem on philo tab\n");
		return (NULL);
	}
	while (i < data->nb_philos)
	{
		init_philo_struct(&(tmp[i]), i, data);
		i++;
	}
	return (tmp);
}

pthread_mutex_t	*init_mutex_fork(t_data *data)
{
	pthread_mutex_t	*tmp;
	int				i;

	i = 0;
	tmp = NULL;
	tmp = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (tmp == NULL)
	{
		printf("Memory allocation problem on mutex_fork\n");
		return (NULL);
	}
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&(tmp[i]), NULL) != 0)
		{
			printf("Pthread_mutex_init failed\n");
			destroy_mutex_tab(tmp, i - 1);
			data->pb_init_mutex_fork++;
			return (tmp);
		}
		i++;
	}
	return (tmp);
}

int	init_data_struct(t_data *data, char **arg, int nb_args)
{
	if (!fill_numbers_in_data(data, arg, nb_args))
		return (0);
	data->fork = init_fork(data->nb_philos);
	if (data->fork == NULL)
		return (0);
	data->tab_philo = init_tab_philo(data);
	if (data->tab_philo == NULL)
		return (init_failed(data, 0));
	if (pthread_mutex_init(&(data->mutex_print), NULL) != 0)
		return (init_failed(data, 1));
	if (pthread_mutex_init(&(data->lock), NULL) != 0)
		return (init_failed(data, 2));
	data->mutex_fork = init_mutex_fork(data);
	if (data->mutex_fork == NULL)
		return (init_failed(data, 3));
	if (data->pb_init_mutex_fork != 0)
		return (init_failed(data, 4));
	return (1);
}
