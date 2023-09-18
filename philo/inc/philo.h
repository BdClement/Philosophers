/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clbernar <clbernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:54:17 by clbernar          #+#    #+#             */
/*   Updated: 2023/09/18 19:13:26 by clbernar         ###   ########.fr       */
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
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"
# define INT_MIN -2147483648
# define INT_MAX 2147483647

struct	s_philo;

typedef struct s_data{
	int					pb_init_mutex_fork;
	int					nb_philos;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	unsigned long		start;
	int					dead;
	int					meals_to_end;
	int					finished;
	int					*fork;
	struct s_philo		*tab_philo;
	pthread_mutex_t		*mutex_fork;
	pthread_mutex_t		mutex_print;
	// pthread_mutex_t		mutex_dead;
	pthread_mutex_t		lock;
	pthread_t			watchdog;
}				t_data;

typedef struct s_philo{
	int							rank;
	struct s_data				*data;
	pthread_t					tid;
	unsigned long				start_last_meal;
	int							eat_count;
	int							left;
	int							right;
}				t_philo;


// check_args.c
int					ft_atoi(const char *nptr);
int					check_overflow(char **arg, int size);
int					overflow(const char *nptr);
int					check_only_positive_nb(char **av);
int					check_args(char **av);

// utils.c
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
unsigned long		get_timestamp_in_ms(void);
void				print(t_philo *philo, char *str);
void				ft_usleep(unsigned int time);

// utils2.c
void				destroy_mutex_tab(pthread_mutex_t *tmp, int size);

// init_structs.c
// int					*init_fork(int nb_philos);
int					fill_numbers_in_data(t_data *data, char **arg, int nb_args);
void				init_philo_struct(t_philo *philo, int i, t_data *data);
struct s_philo		*init_tab_philo(t_data *data);
pthread_mutex_t		*init_mutex_fork(t_data *data);
int					init_data_struct(t_data *data, char **arg, int nb_args);

// clean.c
int					init_failed(t_data *data, int error_code);
void				free_data(t_data *data);

// routine.c
void				*routine(void *data);
void				eating(t_philo *philo);
void				take_fork(t_philo *philo);
void				put_fork_back(t_philo *philo);

// dead.c
int					check_death(t_philo *philo, unsigned long time_to_die, unsigned long last_meal);
void				*watchdog(void *data);
int					is_dead(t_data *data);
// void				check_death(t_philo *philo, unsigned long time_to_die);
#endif
