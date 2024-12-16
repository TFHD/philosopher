/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_limits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:22:49 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/02 21:11:14 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_limits(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(&philo->data->lock);
	if (philo->eat_count == philo->data->nb_eat)
	{
		philo->data->finished++;
		philo->eat_count++;
	}
	if (philo->data->nb_eat > 0
		&& philo->data->finished >= philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo->data->is_dead);
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->is_dead);
	}
	pthread_mutex_unlock(&philo->data->lock);
}

void	*manager(t_data *data)
{
	int	i;
	int	i_tmp;

	i = 0;
	while (!is_dead(&data->philos[i]))
	{
		pthread_mutex_lock(&data->philos[i].lock);
		if (get_time() >= data->philos[i].time_to_die
			&& !data->philos[i].eating)
			send(DEAD, &data->philos[i]);
		i_tmp = i;
		i++;
		if (i == data->nb_philos)
			i = 0;
		pthread_mutex_unlock(&data->philos[i_tmp].lock);
	}
	return ((void *)0);
}
