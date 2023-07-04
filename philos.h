/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:57:33 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/04 22:06:34 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	struct s_data	*data;
	int				pos;
	int				r_fork;
	int				l_fork;
	int				nb_meals;
	unsigned int	last_meal;
	char			*str;
	pthread_t		thread;
	pthread_mutex_t	nb_meals_mtx;
}	t_philo;

typedef struct s_data
{
	int				i;
	int				philo_nbr;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				max_count;
	long			t_to_start;
	int				stop;
	int				max_eat;
	t_philo			*philo;
	pthread_mutex_t	stop_mtx;
	pthread_mutex_t	nb_meals_mtx;
	pthread_mutex_t	*fork_mtx;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal;
	pthread_mutex_t	max_eat_mut;
}	t_data;

int				init_vars(t_data *data, int ac, char **av);
void			dead_philo(t_philo *philo, t_data *data);
unsigned long	get_time(void);
void			my_usleep(unsigned long ms, t_data *data);
void			*life_cycle(void *ph);
void			print_philo_etat(char *str, t_philo *philo, int unlock);
int				initial_philo(t_data *data);
int				setting_routine(t_data *data);
int				initial_philo(t_data *data);
int				initalize(t_data *data);
void			is_eating(t_philo *philo);

//

size_t			ft_strlen(const char *str);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);

#endif
