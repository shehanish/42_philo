/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarunat <skarunat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:59:08 by skarunat          #+#    #+#             */
/*   Updated: 2023/09/29 15:10:03 by skarunat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*parse_status(t_state status)
{
	if (status == S_EATING)
		return ("is eating");
	else if (status == S_LEFT_FORK || status == S_RIGHT_FORK)
		return ("has taken a fork");
	else if (status == S_SLEEPING)
		return ("is sleeping");
	else if (status == S_THINKING)
		return ("is thinking");
	else if (status == S_DEAD)
		return ("died");
	else
		return ("");
}

void	ft_header_pretty(void)
{
	if (PRETTY == 1)
		printf("\n\e[32m%s \t%s\t%s\e[0m\n", "[Milliseconds]", "[Philo Number]",
			"[Action]");
}

static char	*parse_format_pretty(t_state status)
{
	if (status == S_EATING)
		return ("\e[35m%i \t\t%ld\t\t %s\e[0m\n");
	else if (status == S_LEFT_FORK)
		return ("\e[36m%i \t\t%ld\t\t %s\e[0m - [Left ]\n");
	else if (status == S_RIGHT_FORK)
		return ("\e[36m%i \t\t%ld\t\t %s\e[0m - [Right]\n");
	else if (status == S_SLEEPING)
		return ("\e[33m%i \t\t%ld\t\t %s\e[0m\n");
	else if (status == S_THINKING)
		return ("\e[34m%i \t\t%ld\t\t %s\e[0m\n");
	else if (status == S_DEAD)
		return ("\e[31m%i \t\t%ld\t\t %s\e[0m\n");
	else
		return ("%i \t%ld\t %s\n");
}

void	log_status(t_philo *philo, t_state status)
{
	if (dinner_finished(philo->table) == true)
		return ;
	pthread_mutex_lock(&philo->table->long_lock);
	if (PRETTY == 1)
	{
		printf(parse_format_pretty(status),
			get_time_ms(philo->table->start_dining), philo->id + 1,
			parse_status(status));
	}
	else
		printf("%i %ld %s\n", get_time_ms(philo->table->start_dining), philo->id
			+ 1, parse_status(status));
	pthread_mutex_unlock(&philo->table->long_lock);
}
