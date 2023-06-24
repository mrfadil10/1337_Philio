/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 19:56:34 by mfadil            #+#    #+#             */
/*   Updated: 2023/06/24 11:55:56 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	is_numbers(char	**av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (1);
			j++;
		}
	}
	return (0);
}

int	init_vars(t_data *data, char **av)
{
	data->philo = ft_calloc(sizeof(t_philo), data->philo_nbr);
	if (!(data->philo))
		return (2);
	if (is_numbers(av))
	{
		printf("Invalid Args\n");
		return (1);
	}
	data->philo_eat = 0;
	data->stop = 0;
	data->philo_nbr = ft_atoi(av[1]);
	data->t_to_die = ft_atoi(av[2]);
	data->t_to_eat = ft_atoi(av[3]);
	data->t_to_sleep = ft_atoi(av[4]);
	if (av[5])
	{
		data->nb_eat = ft_atoi(av[5]);
		if (data->nb_eat == 0)
			return (1);
	}
	return (0);
}
