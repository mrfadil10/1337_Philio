/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:34:22 by mfadil            #+#    #+#             */
/*   Updated: 2023/06/24 11:59:25 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	initial_ph_tool(t_data *data, int i)
{
	data->philo[i].nbr = i + 1;
	data->philo[i].data = data;
	data->philo[i].r_fork = NULL;
	data->philo[i].nb_meals = 0;
	data->philo[i].last_meal = 0;
}

int	initial_philo(t_data *data)
{
	int	i;

	i = 0;
	data->t_to_start = times();
	while (i < data->philo_nbr)
	{
		initial_ph_tool(data, i);
		pthread_mutex_init(&(data->philo[i].l_fork), NULL);
		if (i == data->philo_nbr - 1)
			data->philo[i].r_fork = &data->philo[0].l_fork;
		else
			data->philo[i].r_fork = &data->philo[i + 1].l_fork;
		if (pthread_create(&data->philo[i].thread, NULL, &life_cycle
				, &data->philo[i]) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

void	destroy_and_free(t_data	*data)
{
	int	i;

	pthread_mutex_destroy(&data->mtx_eat);
	pthread_mutex_destroy(&data->mtx_print);
	pthread_mutex_destroy(&data->mtx_stop);
	pthread_mutex_destroy(&data->mtx_dead);
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(data->philo[i].r_fork);
		pthread_mutex_destroy(&data->philo[i].l_fork);
		i++;
	}
	free(data->philo);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		printf("Invalid Args Count");
		return (0);
	}
	pthread_mutex_init(&data.mtx_eat, NULL);
	pthread_mutex_init(&data.mtx_stop, NULL);
	pthread_mutex_init(&data.mtx_print, NULL);
	pthread_mutex_init(&data.mtx_dead, NULL);
	if (init_vars(&data, av) == 1)
	{
		free(data.philo);
		return (0);
	}
	initial_philo(&data);
	destroy_and_free(&data);
}
