/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarunat <skarunat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:38:25 by skarunat          #+#    #+#             */
/*   Updated: 2023/09/29 15:09:56 by skarunat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_last_meal(t_philo *philo, time_t value)
{
	pthread_mutex_lock(&philo->general_meal_lock);
	philo->last_meal = value;
	pthread_mutex_unlock(&philo->general_meal_lock);
}

void	set_dinner_end(t_table *table, bool value)
{
	pthread_mutex_lock(&table->dinner_end_lock);
	table->dinner_end = value;
	pthread_mutex_unlock(&table->dinner_end_lock);
}

void	increment_eat_times(t_philo *philo)
{
	pthread_mutex_lock(&philo->general_meal_lock);
	philo->times_meals_done++;
	pthread_mutex_unlock(&philo->general_meal_lock);
}

bool	dinner_finished(t_table *table)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&table->dinner_end_lock);
	if (table->dinner_end == true)
		result = true;
	pthread_mutex_unlock(&table->dinner_end_lock);
	return (result);
}
