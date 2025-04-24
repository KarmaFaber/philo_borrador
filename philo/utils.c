/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:38:33 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/24 12:16:25 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Converts a digit-only string into a positive integer.
 *
 * @param sptr: sring to convert
 * @return Returns the converted number between 0 and INT MAX.
 * @return	Returns -1 if the converted number exceeds INT MAX.
 */

int	atol_unsigned(const char *nptr)
{
	unsigned long int	number;
	int i;

	i=0;
	number = 0;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	if (number > INT_MAX)
		return (-1);
	return ((int)number);
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/*
long	timestamp(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}
*/

/**
 * @brief 
 *
 * @param 
 * @return 
 */

void print_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->program->write_lock);
	printf("%lld %hu %s\n", timestamp() - philo->program->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->program->write_lock);
}


/*
void print_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->program->write_lock);
	if (!philo->program->dead)
		printf("%lld %hu %s\n", timestamp() - philo->program->start_time, philo->id, action);
	else 
		printf("%lld %hu %s\n", timestamp() - philo->program->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->program->write_lock);
}
*/

