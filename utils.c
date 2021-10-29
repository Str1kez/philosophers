/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnessrou <tnessrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 21:29:18 by tnessrou          #+#    #+#             */
/*   Updated: 2021/10/25 19:58:04 by tnessrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

struct timeval	g_time;
int				g_isend = 0;

int	ft_isdigit(int c)
{
	if ((c < 58) && (c > 47))
		return (1);
	return (0);
}

int	my_cmp(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 == *s2);
}

unsigned long	get_time(void)
{
	gettimeofday(&g_time, NULL);
	return (g_time.tv_sec * 1000 + g_time.tv_usec / 1000);
}

void	output(t_philo *philo, t_status *status, char *str)
{
	pthread_mutex_lock(&status->output);
	if (!g_isend)
	{
		printf("Time: %lu\t", get_time() - status->time_begin);
		printf("%u %s\n", philo->pos, str);
		if (my_cmp(str, DEATH) || my_cmp(str, NOT_EAT))
			g_isend = 1;
	}
	pthread_mutex_unlock(&status->output);
}

int	clear_all(t_status *status, t_link *link)
{
	int	i;

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
