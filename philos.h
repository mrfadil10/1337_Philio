/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:57:33 by mfadil            #+#    #+#             */
/*   Updated: 2023/06/17 22:21:55 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include "./Libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
	struct s_philo	*philo;
	int				philo_eat;
	int				philo_nbr;
	long int		t_to_start;
	int				t_to_eat;
	int				t_to_sleep;
	int				t_to_die;
	int				nb_eat;
	int				stop;
	pthread_mutex_t	mtx_eat;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_stop;
	pthread_mutex_t	mtx_dead;
}	t_data;

typedef struct s_philo
{
	int				nbr;
	int				nb_meals;
	bool			eating;
	long int		last_meal;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
}	t_philo;

int			init_vars(t_data *data, char **av);
int			dead_philo(t_philo *philo, int nb);
long long	times(void);
void		my_usleep(int ms);
void		*life_cycle(void *ph);
void		print_philo_stat(t_philo *philo, char *str);

#endif