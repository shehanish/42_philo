/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_routine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarunat <skarunat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:56:10 by skarunat          #+#    #+#             */
/*   Updated: 2023/09/29 15:44:12 by skarunat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_sleeping(t_philo *philo)
{
	log_status(philo, S_SLEEPING);
	thread_sleep(philo->table, philo->table->time_to_sleep);
}

static void	ft_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_lock[philo->fork[F_LEFT]]);
	log_status(philo, S_LEFT_FORK);
	pthread_mutex_lock(&philo->table->fork_lock[philo->fork[F_RIGHT]]);
	log_status(philo, S_RIGHT_FORK);
	log_status(philo, S_EATING);
	set_last_meal(philo, datetime_now());
	thread_sleep(philo->table, philo->table->time_to_eat);
	if (dinner_finished(philo->table) == false)
		increment_eat_times(philo);
	pthread_mutex_unlock(&philo->table->fork_lock[philo->fork[F_RIGHT]]);
	pthread_mutex_unlock(&philo->table->fork_lock[philo->fork[F_LEFT]]);
}

static void	ft_thinking(t_philo *philo, bool log)
{
	time_t	time_thinking;

	time_thinking = ft_thinking_time(philo);
	if (log == true)
		log_status(philo, S_THINKING);
	thread_sleep(philo->table, time_thinking);
}

static void	*one_philo(t_philo *philo)
{
	log_status(philo, S_LEFT_FORK);
	thread_sleep(philo->table, philo->table->time_to_die);
	log_status(philo, S_DEAD);
	return (NULL);
}

void	*dining_routines(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	if (philo->table->time_must_eat == 0)
		return (NULL);
	set_last_meal(philo, philo->table->start_dining);
	if (philo->table->num_philo == 1)
		return (one_philo(philo));
	if (philo->id % 2 != 0)
		ft_thinking(philo, false);
	while (dinner_finished(philo->table) == false)
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo, true);
	}
	return (NULL);
}
