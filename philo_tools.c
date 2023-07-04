/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:14:16 by mfadil            #+#    #+#             */
/*   Updated: 2023/07/04 22:39:58 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

unsigned long	get_time(void)
{
	struct timeval	t_val;

	gettimeofday(&t_val, NULL);
	return ((t_val.tv_sec * (unsigned long)1000) + (t_val.tv_usec / 1000));
}

void	my_usleep(unsigned long ms, t_data *data)
{
	unsigned long	time;

	time = get_time();
	while (1)
	{
		if (get_time() - time >= ms)
			break ;
		usleep(data->philo_nbr * 2);
	}
}

void	print_philo_etat(char *message, t_philo *philo, int unlock)
{
	int		cond;
	char	*str;

	str = ft_itoa(get_time() - philo->data->t_to_start);
	pthread_mutex_lock(&philo->data->writing);
	pthread_mutex_lock(&philo->data->max_eat_mut);
	cond = philo->data->max_eat;
	pthread_mutex_unlock(&philo->data->max_eat_mut);
	pthread_mutex_lock(&philo->data->stop_mtx);
	if (!philo->data->stop && !cond)
		printf("%s %s %s\n", str, philo->str, message);
	pthread_mutex_unlock(&philo->data->stop_mtx);
	if (unlock)
		pthread_mutex_unlock(&(philo->data->writing));
	free(str);
}
