/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 19:33:59 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/08 19:36:46 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_data(t_data *data)
{
	if (data->fork != NULL)
		free(data->fork);
	if (data->tab_philo != NULL)
		free(data->tab_philo);
	if (data->mutex_fork != NULL)
		free(data->mutex_fork);
}
