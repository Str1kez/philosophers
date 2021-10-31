/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnessrou <tnessrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 20:15:46 by tnessrou          #+#    #+#             */
/*   Updated: 2021/10/31 18:07:16 by tnessrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_status	status;
	t_link		*link;

	link = NULL;
	status.philos = NULL;
	status.forks = NULL;
	if (argc != 5 && argc != 6)
	{
		printf("Mistake in number of args\n");
		return (clear_all(&status, link));
	}
	if (init_status(&status, argc, argv))
	{
		printf("Error in initialization of main structure\n");
		return (clear_all(&status, link));
	}
	if (threads(&status, link))
	{
		printf("Internal error in threads\n");
		return (clear_all(&status, link));
	}
	pthread_mutex_lock(&status.is_dead);
	pthread_mutex_unlock(&status.is_dead);
	clear_all(&status, link);
	return (0);
}
