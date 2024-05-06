/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skarunat <skarunat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:34:17 by skarunat          #+#    #+#             */
/*   Updated: 2023/09/29 15:10:50 by skarunat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h> //long_max
# include <pthread.h>
# include <stdbool.h> // boolean
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> //get time
# include <unistd.h>

# define ERR_PARAM "Wrong argument.\n"
# define ERR_THREAD "Error: Could not create thread.\n"
# define ERR_MALLOC "Error: Could not allocate memory.\n"
# define ERR_MUTEX "Error: Could not create mutex.\n"
# define ERR_WR_ARG "Wront input in [%li].\n"
# define ERR_SIXTY "Error: Must be greater than 60.\n"

# ifndef PRETTY
#  define PRETTY 0
# endif

typedef struct s_table	t_table;

typedef enum e_fork
{
	F_LEFT = 0,
	F_RIGHT = 1
}						t_fork;

typedef enum e_state
{
	S_EATING,
	S_SLEEPING,
	S_THINKING,
	S_DEAD,
	S_LEFT_FORK,
	S_RIGHT_FORK,
	S_END_DINING
}						t_state;

typedef struct s_philo
{
	pthread_t			thread_philo;
	long				id;
	int					fork[2];
	t_table				*table;
	long				times_meals_done;
	pthread_mutex_t		general_meal_lock;
	time_t				last_meal;
}						t_philo;

typedef struct s_table
{
	pthread_t			thread_table;
	time_t				start_dining;
	long				num_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				time_must_eat;
	t_philo				**philo;
	bool				dinner_end;
	pthread_mutex_t		dinner_end_lock;
	pthread_mutex_t		*fork_lock;
	pthread_mutex_t		long_lock;
}						t_table;

void					*dining_routines(void *data);

int						datetime_now(void);
int						get_time_ms(int start_dining);
void					thread_sleep(t_table *table, time_t duration);
long					ft_thinking_time(t_philo *philo);

bool					is_param_valid(t_table *table);
bool					is_valid_args(int argc, char **argv);

bool					ft_isdigit(int c);
void					*null_error(char *str, t_table *table);
long					ft_atoi_long(const char *str);

t_table					*ft_init_table(int argc, char **argv);

void					*ft_free_table(t_table *table);

void					set_last_meal(t_philo *philo, time_t value);
void					set_dinner_end(t_table *table, bool value);
void					increment_eat_times(t_philo *philo);
bool					dinner_finished(t_table *table);

void					ft_header_pretty(void);
void					log_status(t_philo *philo, t_state status);

void					*dining_routines(void *data);

void					*finish_routines(void *data);

#endif
