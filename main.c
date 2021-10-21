#include "philo.h"

int	main(int argc, char **argv)
{
	t_status	status;
	t_link		*link;

	link = NULL;
	if (argc != 5 && argc != 6)
		return (clear_all(&status, link));
	if (init_status(&status, argc, argv))
		return (clear_all(&status, link));
	if (threads(&status, link))
		return (clear_all(&status, link));
	// printf("lets fun\n");
	pthread_mutex_lock(&status.is_dead);
	// printf("unlock is_dead in main\n");
	// pthread_mutex_unlock(&status.is_dead);
	clear_all(&status, link);
	return (0);
}
