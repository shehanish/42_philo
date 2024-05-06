/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarunat <skarunat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:29:29 by skarunat          #+#    #+#             */
/*   Updated: 2023/09/29 15:26:01 by skarunat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_valid_input(int argc, char **argv)
{
	int		i;
	long	value;

	value = 0;
	i = 1;
	while (i < argc)
	{
		if (is_only_digits(argv[i]) == false)
		{
			printf("Invalid input in [%s]. Only digit accepted.\n", argv[i]);
			return (false);
		}
		value = ft_atoi_long(argv[i]);
		if (value < 0 || value > LONG_MAX)
		{
			printf("Invalid input in [%ld]. Negative or so long.\n", value);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	is_valid_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf(ERR_PARAM);
		return (false);
	}
	if (is_valid_input(argc, argv) == false)
		return (false);
	return (true);
}

bool	is_param_valid(t_table *table)
{
	if (table->num_philo > 200)
	{
		printf(ERR_WR_ARG, table->num_philo);
		return (false);
	}
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
	{
		printf(ERR_SIXTY);
		return (false);
	}
	return (true);
}
