/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfadil <mfadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:46:42 by mfadil            #+#    #+#             */
/*   Updated: 2023/06/17 22:31:47 by mfadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

int	dead_philo(t_philo *philo, int nb)
{
	pthread_mutex_lock(&philo->data->mtx_dead);
	if (nb)
		philo->data->stop = 1;
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->mtx_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mtx_dead);
	return (0);
}

void	*check_is_dead(void *phi)
{
	t_philo	*philo;

	philo = (t_philo *)phi;
	my_usleep(philo->data->t_to_die + 1);
	pthread_mutex_lock(&philo->data->mtx_eat);
	pthread_mutex_lock(&philo->data->mtx_stop);
	if (!dead_philo(philo, 0)
		&& (times() - philo->last_meal) >= (long)(philo->data->t_to_die))
	{
		pthread_mutex_unlock(&philo->data->mtx_eat);
		pthread_mutex_unlock(&philo->data->mtx_stop);
		print_philo_stat(philo, " died\n");
		dead_philo(philo, 1);
	}
	pthread_mutex_unlock(&philo->data->mtx_eat);
	pthread_mutex_unlock(&philo->data->mtx_stop);
	return (NULL);
}

void	taking_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork);
	print_philo_stat(philo, " has taken a fork\n");
	if (philo->data->philo_nbr == 1)
	{
		my_usleep(philo->data->t_to_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	print_philo_stat(philo, " has taken a fork\n");
}

void	is_eating(t_philo *philo)
{
	print_philo_stat(philo, " is eating\n");
	pthread_mutex_lock(&philo->data->mtx_eat);
	philo->last_meal = times();
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->data->mtx_eat);
	my_usleep(philo->data->t_to_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_philo_stat(philo, " is sleeping\n");
	my_usleep(philo->data->t_to_sleep);
	print_philo_stat(philo, " is thinking\n");
}

void	*life_cycle(void *ph)
{
	pthread_t	thread;
	t_philo		*philo;

	philo = ph;
	if (philo->nbr % 2 == 0)
		my_usleep(philo->data->t_to_eat / 10);
	while (!dead_philo(philo, 0))
	{
		pthread_create(&thread, NULL, check_is_dead, ph);
		taking_fork(philo);
		is_eating(philo);
		pthread_detach(thread);
		if (philo->nb_meals == philo->data->nb_eat)
		{
			pthread_mutex_lock(&philo->data->mtx_stop);
			if (++philo->data->philo_eat == philo->data->philo_nbr)
			{
				pthread_mutex_unlock(&philo->data->mtx_stop);
				dead_philo(philo, 2);
			}
			pthread_mutex_unlock(&philo->data->mtx_stop);
			return (NULL);
		}
	}
	return (NULL);
}
