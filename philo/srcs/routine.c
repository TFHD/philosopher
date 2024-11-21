/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:12:32 by sabartho          #+#    #+#             */
/*   Updated: 2024/11/12 16:39:59 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void throw_forks(t_philo *philo)
{
	if (!is_alone(philo))
		pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (!is_alone(philo))
		send(SLEEP, philo);
	ft_sleep(philo->data->sleep_time);
}
void	take_forks(t_philo *philo)
{
	if (!is_alone(philo))
	{
		pthread_mutex_lock(philo->r_fork);
		send(TAKE_FORK, philo);
	}
	pthread_mutex_lock(philo->l_fork);
	send(TAKE_FORK, philo);
}

void	do_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	if (!is_alone(philo))
	{
		philo->eating = 1;
		philo->time_to_die = philo->data->death_time + get_time();
		send(EAT, philo);
		philo->eat_count++;
		philo->eating = 0;
		ft_sleep(philo->data->eat_time);
	}
	pthread_mutex_unlock(&philo->lock);
	throw_forks(philo);
}

void	*routine(void *philo_ptr)
{
	t_philo *philo;

	philo = (t_philo *)philo_ptr;
	if (pthread_create(&philo->thread, NULL, &manager, (void *)philo))
		return ((void *)1);
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = philo->data->death_time + get_time();
	pthread_mutex_unlock(&philo->lock);
	while (is_dead(philo) == 0)
	{
		do_eat(philo);
		if (is_alone(philo))
			ft_sleep(philo->data->death_time);
		send(THINK, philo);
	}
	if (pthread_join(philo->thread, NULL))
		return ((void *)1);
	return ((void *)0);
}
