/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:34:22 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/04 18:30:42 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	initial_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
	{
		data->philo[i].pos = i + 1;
		data->philo[i].str = ft_itoa(i + 1);
		if (!data->philo[i].str)
			break ;
		data->philo[i].r_fork = i;
		data->philo[i].l_fork = (i + 1) % data->philo_nbr;
		data->philo[i].nb_meals = 0;
		data->philo[i].data = data;
	}
	if (i != data->philo_nbr)
	{
		while (i >= 0)
		{
			free(data->philo[i].str);
			i--;
		}
		return (1);
	}
	return (0);
}

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	data.max_eat = 0;
	data.stop = 0;
	if (ac < 5 || ac > 6)
		return (ft_error("Args Error.\n"));
	if (!init_vars(&data, ac, av))
		return (0);
	if (!initalize(&data))
		return (ft_error("Error.\n"));
	if (!setting_routine(&data))
		return (ft_error("Threads error. \n"));
	return (0);
}
