/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:58:09 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/11 19:04:14 by clbernar         ###   ########.fr       */
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
	// philo->tid =
	philo->left = philo->rank - 1;
	if (philo->rank == philo->data->nb_philos)
		philo->right = 0;
	else
		philo->right = philo->rank;
	philo->start_last_eat = 0;
	philo->eat_count = 0;
	philo->fork = data->fork;
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
		// printf("philo rank no %d\n", tmp[i].rank);
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
		pthread_mutex_init(&(tmp[i]), NULL);
		i++;
	}
	return (tmp);
}

void	init_data_struct(t_data *data, char **arg)
{
	data->nb_philos = ft_atoi(arg[1]);
	data->time_to_die = ft_atoi(arg[2]);
	data->time_to_eat = ft_atoi(arg[3]);
	data->time_to_sleep = ft_atoi(arg[4]);
	if (get_len_tab(arg) == 6)
		data->meals_to_end = ft_atoi(arg[5]);
	else
		data->meals_to_end = 0;
	data->meals_finished = 0;
	data->start = 0;// Attendre pour lancer le start ??
	data->fork = init_fork(data->nb_philos);
	data->tab_philo = init_tab_philo(data);
	data->mutex_fork = init_mutex_fork(data);
	if (data->fork == NULL || data->tab_philo == NULL
		|| data->mutex_fork == NULL)
		free_data(data);
}
