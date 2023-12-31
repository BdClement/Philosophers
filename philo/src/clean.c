/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:33:59 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/22 14:28:15 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// This function is called when the initialisation part failed
// Depending on where it failed, it clears what it needs to clear
int	init_failed(t_data *data, int error_code)
{
	if (data->fork != NULL)
		free(data->fork);
	if (error_code >= 1)
		free(data->tab_philo);
	if (error_code >= 2)
		pthread_mutex_destroy(&data->mutex_print);
	if (error_code >= 3)
		pthread_mutex_destroy(&data->lock);
	if (error_code >= 4)
		free(data->mutex_fork);
	return (0);
}

// This function clear my program when the meal is done
void	free_data(t_data *data)
{
	destroy_mutex_tab(data->mutex_fork, data->nb_philos - 1);
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->lock);
	if (data->tab_philo != NULL)
		free(data->tab_philo);
	if (data->mutex_fork != NULL)
		free(data->mutex_fork);
	if (data->fork != NULL)
		free(data->fork);
}
