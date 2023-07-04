/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 22:29:46 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/04 22:30:27 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	die_check(t_philo *philo, t_data *data, int i)
{
	pthread_mutex_lock(&data->meal);
	if ((int)(get_time() - philo[i].last_meal) >= data->t_to_die)
	{
		print_philo_etat(" died", &philo[i], 0);
		pthread_mutex_lock(&data->stop_mtx);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mtx);
	}
	pthread_mutex_unlock(&data->meal);
}

void	check_nb_meals(t_philo *philo, t_data *data, int cond, int i)
{
	pthread_mutex_lock(&data->nb_meals_mtx);
	while (data->max_count && i < data->philo_nbr
		&& philo[i].nb_meals >= data->max_count)
		i++;
	pthread_mutex_unlock(&data->nb_meals_mtx);
	pthread_mutex_lock(&data->max_eat_mut);
	data->max_eat = (i == data->philo_nbr);
	cond = data->max_eat;
	pthread_mutex_unlock(&data->max_eat_mut);
}

int	test(t_philo *philo, t_data *data, int *cond)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->stop_mtx);
		*cond = !data->stop;
		pthread_mutex_unlock(&data->stop_mtx);
		if (!(*cond))
			return (1);
		die_check(philo, data, i);
	}
	return (0);
}

void	dead_philo(t_philo *philo, t_data *data)
{
	int	cond;
	int	cond2;

	while (1)
	{
		if (test(philo, data, &cond))
			break ;
		pthread_mutex_lock(&data->stop_mtx);
		cond2 = data->stop;
		pthread_mutex_unlock(&data->stop_mtx);
		if (cond2)
			break ;
		data->i = 0;
		pthread_mutex_lock(&data->nb_meals_mtx);
		while (data->max_count && data->i < data->philo_nbr
			&& philo[data->i].nb_meals >= data->max_count)
			data->i++;
		pthread_mutex_unlock(&data->nb_meals_mtx);
		pthread_mutex_lock(&data->max_eat_mut);
		data->max_eat = (data->i == data->philo_nbr);
		cond = data->max_eat;
		pthread_mutex_unlock(&data->max_eat_mut);
		if (cond)
			break ;
	}
}
