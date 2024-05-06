/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_finish_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarunat <skarunat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:39:43 by skarunat          #+#    #+#             */
/*   Updated: 2023/09/29 15:10:43 by skarunat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	kill_philo(t_philo *philo)
{
	if ((datetime_now() - philo->last_meal) >= philo->table->time_to_die)
	{
		log_status(philo, S_DEAD);
		set_dinner_end(philo->table, true);
		pthread_mutex_unlock(&philo->general_meal_lock);
		return (true);
	}
	return (false);
}

static bool	end_dinner(t_table *table)
{
	int		i;
	bool	done_eating;

	i = 0;
	done_eating = true;
	while (i < table->num_philo)
	{
		pthread_mutex_lock(&table->philo[i]->general_meal_lock);
		if (kill_philo(table->philo[i]) == true)
			return (true);
		if (table->time_must_eat != -1)
			if (table->philo[i]->times_meals_done < table->time_must_eat)
				done_eating = false;
		pthread_mutex_unlock(&table->philo[i]->general_meal_lock);
		i++;
	}
	if (table->time_must_eat != -1 && done_eating == true)
	{
		set_dinner_end(table, true);
		return (true);
	}
	return (false);
}

void	*finish_routines(void *data)
{
	t_table		*table;

	table = (t_table *)data;
	if (table->time_must_eat == 0)
		return (NULL);
	set_dinner_end(table, false);
	while (true)
	{
		if (end_dinner(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
