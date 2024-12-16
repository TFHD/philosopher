/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabartho <sabartho@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 21:38:08 by sabartho          #+#    #+#             */
/*   Updated: 2024/12/02 17:17:52 by sabartho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->data->is_dead);
	value = philo->data->dead;
	pthread_mutex_unlock(&philo->data->is_dead);
	return (value);
}

int	is_alone(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(&philo->data->lock);
	value = philo->data->nb_philos;
	pthread_mutex_unlock(&philo->data->lock);
	if (value == 1)
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
