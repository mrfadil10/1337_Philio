/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:56:34 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/04 18:59:04 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		if (pthread_mutex_init(&(data->fork_mtx[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&data->meal, NULL))
		return (1);
	if (pthread_mutex_init(&data->writing, NULL))
		return (1);
	if (pthread_mutex_init(&data->max_eat_mut, NULL))
		return (1);
	if (pthread_mutex_init(&data->nb_meals_mtx, NULL))
		return (1);
	if (pthread_mutex_init(&data->stop_mtx, NULL))
		return (1);
	return (0);
}

int	initalize(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		return (0);
	data->fork_mtx = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->fork_mtx)
	{
		free(data->philo);
		return (0);
	}
	if (mutex(data))
	{
		free(data->philo);
		free(data->fork_mtx);
		return (0);
	}
	if (initial_philo(data))
	{
		free(data->philo);
		free(data->fork_mtx);
		return (0);
	}
	return (1);
}

int	init_vars(t_data *data, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) < 0)
			return (0);
		i++;
	}
	data->philo_nbr = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_count = ft_atoi(av[5]);
	else
		data->max_count = 0;
	if (data->philo_nbr < 1 || data->t_to_die < 0 || data->t_to_eat < 0
		|| data->t_to_sleep < 0 || (ac == 6 && data->max_count <= 0))
		return (0);
	return (1);
}
