/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:38:01 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/15 18:12:08 by clbernar         ###   ########.fr       */
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
