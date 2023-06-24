/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:14:16 by mfadil            #+#    #+#             */
/*   Updated: 2023/06/17 22:22:21 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long long	times(void)
{
	struct timeval	t_val;

	gettimeofday(&t_val, NULL);
	return (t_val.tv_sec * 1000 + t_val.tv_usec / 1000);
}

void	my_usleep(int ms)
{
	long int	time;

	time = times();
	while (times() - time < ms)
		usleep(ms / 10);
}

void	print_philo_stat(t_philo *philo, char *str)
{
	long int	time;

	pthread_mutex_lock(&(philo->data->mtx_print));
	time = times() - philo->data->t_to_start;
	if (!philo->data->stop && time >= 0 && time <= INT_MAX
		&& !dead_philo(philo, 0))
		printf("%lld %d %s", times() - philo->data->t_to_start, philo->nbr, str);
	pthread_mutex_unlock(&(philo->data->mtx_print));
}