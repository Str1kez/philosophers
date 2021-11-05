/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnessrou <tnessrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:02:21 by tnessrou          #+#    #+#             */
/*   Updated: 2021/11/05 20:44:46 by tnessrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DEATH "died"
# define FORK "has taken a fork"
# define SLEEP "is sleeping"
# define EAT "is eating"
# define THINK "is thinking"
# define NOT_EAT "can't eat anymore"

# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				pos;
	int				is_eat;
	unsigned long	time_limit;
	int				l_fork;
	int				r_fork;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat;
}				t_philo;

typedef struct s_status
{
	int				phil_count;
	unsigned long	time_begin;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	is_dead;
	pthread_mutex_t	output;
}				t_status;

typedef struct s_link
{
	t_philo		*philo;
	t_status	*status;
}				t_link;

int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				init_status(t_status *status, int argc, char **argv);
int				init_link(t_link **link, t_status *status);
int				threads(t_status *status, t_link *link);
unsigned long	get_time(void);
void			eat_action(t_link *link);
void			output(t_philo *philo, t_status *status, char *str);
int				clear_all(t_status *status, t_link *link);

#endif
