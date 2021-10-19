/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnessrou <tnessrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:29:18 by tnessrou          #+#    #+#             */
/*   Updated: 2021/10/19 19:08:45 by tnessrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct timeval	g_time;

int	ft_isdigit(int c)
{
	if ((c < 58) && (c > 47))
		return (1);
	return (0);
}

unsigned long	get_time(void)
{
	gettimeofday(&g_time, NULL);
	return (g_time.tv_sec * 1000 + g_time.tv_usec / 1000);
}

void	output(t_philo *philo, t_status *status, char *str)
{
	pthread_mutex_lock(&status->output);
	printf("Time: %lu\n", get_time() - status->time_begin);
	printf("%u %s\n", philo->pos, str);
	pthread_mutex_unlock(&status->output);
}

int	clear_all(t_status *status, t_link *link)
{
	unsigned int	i;

	i = 0;
	if (status->philos)
	{
		while (i < status->phil_count)
		{
			pthread_mutex_destroy(&status->philos[i].mutex);
			pthread_mutex_destroy(&status->philos[i].eat);
			i++;
		}
		free(status->philos);
	}
	i = 0;
	if (status->forks)
	{
		while (i < status->phil_count)
			pthread_mutex_destroy(&status->forks[i++]);
		free(status->forks);
	}
	if (link)
		free(link);
	return (1);
}
