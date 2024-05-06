/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarunat <skarunat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:34:11 by skarunat          #+#    #+#             */
/*   Updated: 2023/09/29 15:10:56 by skarunat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*ft_init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	long			i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!forks)
		return (null_error(ERR_MALLOC, NULL));
	while (i < table->num_philo)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			return (null_error(ERR_MUTEX, NULL));
		i++;
	}
	return (forks);
}

static void	sort_fork_by_philo(t_philo *philo)
{
	philo->fork[0] = philo->id;
	if (philo->table->num_philo > 1)
	{
		philo->fork[1] = (philo->id + 1) % philo->table->num_philo;
		if (philo->id % 2 != 0)
		{
			philo->fork[0] = (philo->id + 1) % philo->table->num_philo;
			philo->fork[1] = philo->id;
		}
	}
}

static bool	ft_init_philo(t_table *table)
{
	t_philo	**philos;
	long	i;

	i = 0;
	philos = malloc(sizeof(t_philo) * table->num_philo);
	if (philos == NULL)
		return (null_error(ERR_MALLOC, NULL));
	while (i < table->num_philo)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (philos[i] == NULL)
			return (null_error(ERR_MALLOC, NULL));
		philos[i]->table = table;
		philos[i]->id = i;
		philos[i]->times_meals_done = 0;
		sort_fork_by_philo(philos[i]);
		if (pthread_mutex_init(&philos[i]->general_meal_lock, 0) != 0)
			return (null_error(ERR_MUTEX, NULL));
		i++;
	}
	table->philo = philos;
	return (true);
}

static bool	ft_init_mutex(t_table *table)
{
	table->fork_lock = ft_init_forks(table);
	if (!table->fork_lock)
		return (false);
	if (pthread_mutex_init(&table->dinner_end_lock, 0) != 0)
		return (null_error(ERR_MUTEX, NULL));
	if (pthread_mutex_init(&table->long_lock, 0) != 0)
		return (null_error(ERR_MUTEX, NULL));
	return (true);
}

t_table	*ft_init_table(int argc, char **argv)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (null_error(ERR_MALLOC, NULL));
	table->num_philo = ft_atoi_long(argv[1]);
	table->time_to_die = ft_atoi_long(argv[2]);
	table->time_to_eat = ft_atoi_long(argv[3]);
	table->time_to_sleep = ft_atoi_long(argv[4]);
	table->time_must_eat = -1;
	if (argc == 6)
		table->time_must_eat = ft_atoi_long(argv[5]);
	table->dinner_end = false;
	table->start_dining = datetime_now();
	if (ft_init_philo(table) == false || table->philo == NULL)
		return (NULL);
	if (ft_init_mutex(table) == false || is_param_valid(table) == false)
		return (NULL);
	return (table);
}
