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
