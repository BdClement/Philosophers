/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:00:24 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/11 20:29:27 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// valrgind --tool=helgrind ./philo
// valrgind --tool=drd ./philo
// -fsanitize=thread -g (data race)

// ROUTINE
// Les impairs prennent leur fourhcette de gauche puis leur fourchette de droite
// Ils mangent time_to_eat
// Les pairs usleep(TBD)
// Quand les impairs ont fini ils dorment time_to_sleep
// Pendant ce temps la les pairs ont fini le usleep et cherche a acceder aux fourchettes
// Une fois que c'est bon ils commencent a manger
// Les impairs pensent jusqu'a pouvoir reprendre leurs fourchettes
// Les pairs dorment time to_sleep
// Les impairs recommencent a manger
// Les pairs pensent en essayant d'acceder aux fourchettes pour remanger


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

void	eating(t_philo *philo)
{
	//lock le mutex fourchette gauche
	pthread_mutex_lock(&philo->data->mutex_fork[philo->left]);
	philo->data->fork[philo->left]++;
	print(philo, FORK);
	pthread_mutex_lock(&philo->data->mutex_fork[philo->right]);
	philo->data->fork[philo->right]--;
	print(philo, FORK);
	// Compteur a mettre a jour 
	print(philo, EAT);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->left]);
	pthread_mutex_unlock(&philo->data->mutex_fork[philo->right]);
	// if (philo->rank % 2 != 0)
	// {
	// 	// Impairs
	// }
	// else
	// {
	// 	// Pairs
	// 	// if premier tour
	// }
}

// int	ft_usleep(useconds_t time)
// {
// 	u_int64_t	start;
// 	start = get_time();
// 	while ((get_time() - start) < time)
// 		usleep(time / 10);
// 	return(0);
// }

void	*routine(void *data)
{
	t_philo		*tmp_philo;

	tmp_philo = (t_philo *)data;
	while (1)
	{
		if (tmp_philo->rank % 2 == 0 && tmp_philo->eat_count == 0)
		{
			print(tmp_philo, THINK);
			ft_usleep(tmp_philo->data->time_to_eat * 0.2);
		}
		//EATING
		eating(tmp_philo);
		break ;
		//SLEEPING
		//THINKING
	}
	return (NULL);
}

void	philo(t_data *data)
{
	int	i;

	i = 0;
	// Initialiser start ici
	data->start = get_timestamp_in_ms();
	// printf("start == %lu\n",get_timestamp_in_ms() - data->start);
	while (i < data->nb_philos)
	{
		pthread_create(&(data->tab_philo[i]).tid, NULL, routine,
			&(data->tab_philo[i]));
		pthread_join((data->tab_philo[i]).tid, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	// printf("avec fonction %lld\n", get_timestamp_in_ms());
	(void)av;
	if (ac != 5 && ac != 6)
		printf("This program needs 4 or 5 arguments\n");
	else
	{
		if (!check_args(av))
			return (1);
		else
		{
			init_data_struct(&data, av);
			philo(&data);// Si les initialisation ce sont bien passe !
			//free (*fork);
			free_data(&data);
		}
	}
	return (0);
}
