/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarunat <skarunat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:56:23 by skarunat          #+#    #+#             */
/*   Updated: 2023/09/29 15:10:21 by skarunat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_end_dining(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_join(table->philo[i]->thread_philo, NULL);
		i++;
	}
	if (table->num_philo > 1)
		pthread_join(table->thread_table, NULL);
	ft_free_table(table);
}

static bool	ft_start_dining(t_table *table)
{
	int	i;

	ft_header_pretty();
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philo[i]->thread_philo, NULL,
				&dining_routines, table->philo[i]) != 0)
			return (null_error(ERR_THREAD, table));
		i++;
	}
	if (table->num_philo > 1)
	{
		if (pthread_create(&table->thread_table, NULL, &finish_routines,
				table) != 0)
			return (null_error(ERR_THREAD, table));
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	table = NULL;
	if (is_valid_args(argc, argv) == false)
		return (EXIT_FAILURE);
	table = ft_init_table(argc, argv);
	if (!table)
		return (EXIT_FAILURE);
	if (ft_start_dining(table) == false)
		return (EXIT_FAILURE);
	ft_end_dining(table);
	return (EXIT_SUCCESS);
}
