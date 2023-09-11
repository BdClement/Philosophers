/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:54:17 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/11 20:24:34 by clbernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
// #include <stdint.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is spleeping"
# define THINK "is thinking"
# define DIED "died"

struct	s_philo;

typedef struct s_data{
	int					nb_philos;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	unsigned long		start;
	int					meals_to_end;
	int					meals_finished;
	int					*fork;
	struct s_philo		*tab_philo;
	pthread_mutex_t		*mutex_fork;
	// mutex_print;
}				t_data;

typedef struct s_philo{
	int							rank;
	struct s_data				*data;
	pthread_t					tid;
	unsigned long				start_last_eat;
	int							eat_count;
	int							left;
	int							right;
	int							*fork;
}				t_philo;


// check_args.c
int					ft_isdigit(int c);
int					ft_atoi(const char *nptr);
int					check_only_positive_nb(char **av);
int					check_args(char **av);

// utils.c
unsigned long		get_timestamp_in_ms(void);
int					get_len_tab(char **tab);
void				print(t_philo *philo, char *str);
void				ft_usleep(unsigned int time);

// init_structs.c
int					*init_fork(int nb_philos);
void				init_philo_struct(t_philo *philo, int i, t_data *data);
struct s_philo		*init_tab_philo(t_data *data);
void				init_data_struct(t_data *data, char **arg);
pthread_mutex_t		*init_mutex_fork(t_data *data);

// clean.c
void				free_data(t_data *data);

#endif
