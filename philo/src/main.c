/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:00:24 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/22 14:16:37 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// valgrind --tool=helgrind ./philo
// valgrind --tool=drd ./philo
// -fsanitize=thread -g (data race)

void	*routine(void *data)
{
	t_philo		*tmp_philo;

	tmp_philo = (t_philo *)data;
	if (philo_alone(tmp_philo))
		return (NULL);
	even_philo_start_thinking(tmp_philo);
	while (1)
	{
		eating(tmp_philo);
		if (!is_dead(tmp_philo->data) && !meal_is_over(tmp_philo->data))
		{
			print(tmp_philo, SLEEP);
			ft_usleep(tmp_philo->data->time_to_sleep);
		}
		if (!is_dead(tmp_philo->data) && !meal_is_over(tmp_philo->data))
			print(tmp_philo, THINK);
		if (is_dead(tmp_philo->data) || meal_is_over(tmp_philo->data))
			break ;
	}
	return (NULL);
}

void	philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&(data->tab_philo[i]).tid, NULL, routine,
			&(data->tab_philo[i]));
		i++;
	}
	i = 0;
	pthread_create(&data->watchdog, NULL, watchdog, data->tab_philo);
	while (i < data->nb_philos)
	{
		pthread_join((data->tab_philo[i]).tid, NULL);
		i++;
	}
	pthread_join(data->watchdog, NULL);
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	if (ac != 5 && ac != 6)
		printf("This program needs 4 or 5 arguments\n");
	else
	{
		if (!check_args(av))
			return (1);
		else
		{
			if (init_data_struct(&data, av, ac - 1))
			{
				philo(&data);
				free_data(&data);
			}
			else
				return (1);
		}
	}
	return (0);
}
