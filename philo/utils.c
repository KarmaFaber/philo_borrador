/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:38:33 by mzolotar          #+#    #+#             */
/*   Updated: 2025/05/01 10:28:57 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

/**
 * @brief 
 *
 * @param 
 * @return 
 */

/*
void print_action(t_philo *philo, const char *action)
{
	if (philosopher_dead(philo))
    {
		printf("\001\033[1;31m\002muerte detectada en print_action -> return \n\001\033[0m\002"); // 🚩 testeo
        return ;
    }
	pthread_mutex_lock(&philo->program->write_lock);
	printf("%lld %hu %s\n", timestamp() - philo->program->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->program->write_lock);
}
*/

void print_action(t_philo *philo, const char *action)
{
    pthread_mutex_lock(&philo->program->dead_num_lock);  

    if (philo->program->dead_p_num > 0 )  // Si ya hay una muerte, no imprimir más
    {
        pthread_mutex_unlock(&philo->program->dead_num_lock);
		//printf("\001\033[1;31m\002muerte detectada en print_action -> return \n\001\033[0m\002"); // 🚩 testeo
        return;
    }
    pthread_mutex_unlock(&philo->program->dead_num_lock);

    pthread_mutex_lock(&philo->program->write_lock);
    printf("%lld %hu %s\n", timestamp() - philo->program->start_time, philo->id, action);
    pthread_mutex_unlock(&philo->program->write_lock);
}
	
/*
void print_action(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->program->write_lock);
	printf("%lld %hu %s\n", timestamp() - philo->program->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->program->write_lock);
}
*/
/**
 * @brief 
 *
 * @param 
 * @return 
 */

void print_dead(t_philo *philo, const char *action)
{
	pthread_mutex_lock(&philo->program->write_lock);
	printf("%lld %hu %s\n", timestamp() - philo->program->start_time, philo->id, action);
	pthread_mutex_unlock(&philo->program->write_lock);
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */
/*
void precise_sleep(long long duration)
{
	long long start;

	start = timestamp();
	while ((timestamp() - start < duration))
		usleep(50);  // dormir por pedacitos de 50us
}
*/

void precise_sleep(t_philo *philo, long long duration)
{
	long long start;

	start = timestamp();
	while ((timestamp() - start) < duration)
	{
		if (philosopher_dead(philo) )
			break;
		//usleep(50);
		usleep(1); //revisar rango de este usleep 
	}
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

void	final_print(t_program *program)
{
	if (program->dead_p_num <= 0)
	{
		//printf("						\n");
		printf("\001\033[1;32m\002    ツ ☞ ☞ no one died today   \n\001\033[0m\002");
		//printf("						\n");
	}
}
