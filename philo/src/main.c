/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:00:24 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/18 17:46:03 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// valgrind --tool=helgrind ./philo
// valgrind --tool=drd ./philo
// -fsanitize=thread -g (data race)

// Exemple d'acces a toutes mes variables a partir de la structure philo
// du thread en question qui contient lui meme la strucute t_data
// void	*routine(void *data)
// {
// 	pthread_t	tid;
// 	t_philo		*tmp_philo;

// 	tmp_philo = (t_philo *)data;
// 	tid = pthread_self();
// 	printf("Thread %ld fonctionne\n", tid);
// 	printf("rank = %d\n", tmp_philo->rank);
// 	printf("time_to_die = %lld\n", tmp_philo->data->time_to_die);
// 	return (NULL);
// }

void	philo(t_data *data)
{
	int	i;

	i = 0;
	// data->start = get_timestamp_in_ms();
	while (i < data->nb_philos)
	{
		pthread_create(&(data->tab_philo[i]).tid, NULL, routine,
			&(data->tab_philo[i]));
		i++;
	}
	i = 0;
	ft_usleep(20);
	pthread_create(&data->watchdog, NULL, watchdog, data->tab_philo);
	while (i < data->nb_philos)
	{
		pthread_join((data->tab_philo[i]).tid, NULL);
		i++;
	}
	pthread_join(data->watchdog, NULL);
	// Apres La creation des autres threads ?

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
				// Gerer le cas d'un seul philo
				philo(&data);
				free_data(&data);
			}
			else
				return (1);
		}
	}
	return (0);
}
