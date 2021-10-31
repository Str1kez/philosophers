/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnessrou <tnessrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 20:14:59 by tnessrou          #+#    #+#             */
/*   Updated: 2021/10/31 18:35:47 by tnessrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// выделены forks, philos, link

int	init_link(t_link **link, t_status *status)
{
	int	i;

	*link = (t_link *)malloc(status->phil_count * sizeof(t_link));
	if (!*link)
		return (1);
	i = 0;
	while (i < status->phil_count)
	{
		(*link)[i].philo = status->philos + i;
		(*link)[i].status = status;
		i++;
	}
	return (0);
}

static int	init_forks(t_status *status)
{
	int	i;

	i = 0;
	status->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* status->phil_count);
	if (!status->forks)
		return (1);
	while (i < status->phil_count)
		pthread_mutex_init(&status->forks[i++], NULL);
	return (0);
}

static int	init_philos(t_status *status)
{
	int	i;

	status->philos = (t_philo *)malloc(sizeof(t_philo) * status->phil_count);
	if (!status->philos)
		return (1);
	i = 0;
	while (i < status->phil_count)
	{
		status->philos[i].pos = i + 1;
		status->philos[i].is_eat = 0;
		status->philos[i].time_limit = 0;
		status->philos[i].l_fork = i;
		status->philos[i].r_fork = (i + 1) % status->phil_count;
		pthread_mutex_init(&status->philos[i].mutex, NULL);
		pthread_mutex_init(&status->philos[i].eat, NULL);
		pthread_mutex_lock(&status->philos[i].eat);
		i++;
	}
	return (0);
}

int	init_status(t_status *status, int argc, char **argv)
{
	status->phil_count = ft_atoi(argv[1]);
	status->time_to_die = ft_atoi(argv[2]);
	status->time_to_eat = ft_atoi(argv[3]);
	status->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		status->eat_count = ft_atoi(argv[5]);
	else
		status->eat_count = 0;
	status->time_begin = 0;
	status->philos = NULL;
	status->forks = NULL;
	if (status->phil_count < 0 || status->time_to_die < 50
		|| status->time_to_eat < 50 || status->time_to_sleep < 50
		|| status->eat_count < 0)
		return (1);
	pthread_mutex_init(&status->is_dead, NULL);
	pthread_mutex_init(&status->output, NULL);
	pthread_mutex_lock(&status->is_dead);
	return (init_forks(status) + init_philos(status));
}
