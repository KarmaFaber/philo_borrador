/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:29:00 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/24 12:34:43 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */

int error_msg (char *str, int exit_no)
{
	printf("%s", str);
	return (exit_no);
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

void free_all(t_program *program)
{
	int i;

	i=0;
    // Destruir los mutexes de los tenedores
    while (i < program->num_philos)
	{
        pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	
    // Destruir los mutexes globales
    pthread_mutex_destroy(&program->write_lock);
    pthread_mutex_destroy(&program->dead_num_lock);
    pthread_mutex_destroy(&program->meal_lock);

    // Liberar memoria reservada
    free(program->forks);
    free(program->philos);
    free(program->forks_available);
}
