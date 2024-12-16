/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:12:32 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/02 20:55:57 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	throw_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	send(SLEEP, philo);
	ft_sleep(philo->data->sleep_time, philo);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	send(TAKE_FORK, philo);
	if (philo->id % 2)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	send(TAKE_FORK, philo);
	usleep(300);
}

void	do_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	send(EAT, philo);
	philo->eating = 0;
	ft_sleep(philo->data->eat_time, philo);
	philo->time_to_die = philo->data->death_time + get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock);
	throw_forks(philo);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	send(TAKE_FORK, philo);
	pthread_mutex_unlock(philo->l_fork);
	ft_sleep(philo->data->death_time, philo);
}

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = philo->data->death_time + get_time();
	pthread_mutex_unlock(&philo->lock);
	while (!is_dead(philo))
	{
		eat_limits(philo);
		if (is_alone(philo))
			one_philo(philo);
		else
			do_eat(philo);
		send(THINK, philo);
	}
	return ((void *)0);
}
