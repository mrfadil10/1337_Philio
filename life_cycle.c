/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:46:42 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/04 22:45:25 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_mtx[philo->r_fork]);
	print_philo_etat(" has taken a fork", philo, 1);
	pthread_mutex_lock(&philo->data->fork_mtx[philo->l_fork]);
	print_philo_etat(" has taken a fork", philo, 1);
	pthread_mutex_lock(&philo->data->meal);
	print_philo_etat(" is eating", philo, 1);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal);
	my_usleep(philo->data->t_to_eat, philo->data);
	pthread_mutex_lock(&philo->data->nb_meals_mtx);
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->data->nb_meals_mtx);
	pthread_mutex_unlock(&philo->data->fork_mtx[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->fork_mtx[philo->l_fork]);
}

void	sleep_think(t_philo *philos, t_data *data)
{
	print_philo_etat(" is sleeping", philos, 1);
	my_usleep(data->t_to_sleep, data);
	print_philo_etat(" is thinking", philos, 1);
}

void	*life_cycle(void *ph)
{
	int		cond;
	int		cond2;
	t_data	*data;
	t_philo	*philos;

	philos = (t_philo *)ph;
	data = philos->data;
	if (philos->pos % 2 && data->philo_nbr > 1)
		my_usleep(data->t_to_eat / 50, data);
	while (1)
	{
		pthread_mutex_lock(&data->stop_mtx);
		cond2 = data->stop;
		pthread_mutex_unlock(&data->stop_mtx);
		if (cond2)
			break ;
		pthread_mutex_lock(&data->max_eat_mut);
		cond = data->max_eat;
		pthread_mutex_unlock(&data->max_eat_mut);
		if (cond)
			break ;
		is_eating(philos);
		sleep_think(philos, data);
	}
	return (NULL);
}

void	free_and_destroy(t_data *data)
{
	int	i;

	if (data->philo_nbr == 1)
		pthread_detach(data->philo[0].thread);
	else
	{
		i = -1;
		while (++i < data->philo_nbr)
			pthread_join(data->philo[i].thread, NULL);
	}
	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&data->fork_mtx[i]);
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->meal);
	i = -1;
	while (++i < data->philo_nbr)
		free(data->philo[i].str);
	free(data->philo);
	free(data->fork_mtx);
}

int	setting_routine(t_data *data)
{
	int	i;

	i = -1;
	data->t_to_start = get_time();
	while (++i < data->philo_nbr)
	{
		data->philo[i].last_meal = get_time();
		if (pthread_create(&data->philo[i].thread,
				NULL, life_cycle, &(data->philo[i])))
			return (0);
	}
	dead_philo(data->philo, data);
	pthread_mutex_unlock(&data->writing);
	free_and_destroy(data);
	return (1);
}
