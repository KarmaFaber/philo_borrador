/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 20:29:00 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/30 09:42:10 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */
/*
int error_msg (char *str, int exit_no)
{
	printf("%s", str);
	return (exit_no);
}
*/
/**
 * @brief 
 *
 * @param 
 * @return 
 */

void free_all(t_program *program)
{
	int i;

    // Destruir mutexes de forks si están alocados
    if (program->forks)
    {
        i = 0;
        while (i < program->num_philos)
        {
            pthread_mutex_destroy(&program->forks[i]);
            i++;
        }
        free(program->forks);
        //program->forks = NULL;
    }
    
    // Destruir mutexes globales (protegido si se inicializaron)
    if (&program->write_lock)
        pthread_mutex_destroy(&program->write_lock);    // Destruir los mutexes globales
    if (&program->dead_num_lock)
        pthread_mutex_destroy(&program->dead_num_lock);
    if (&program->forks_lock)
        pthread_mutex_destroy(&program->forks_lock);
    
    //pthread_mutex_destroy(&program->meal_lock);
   
    // Liberar arrays si están alocados
	if (program->philos)
	{
		free(program->philos);
		//program->philos = NULL;
	}
    if (program->forks_available)
	{
		free(program->forks_available);
		//program->forks_available = NULL;
	}
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

void clean_pthreads(t_program *program, int created_threads)
{
	int j = 0;

	printf("%s", STR_ERR_THREAD);
	while (j < created_threads)
	{
		pthread_join(program->philos[j].thread, NULL);
		j++;
	}
	free_all(program);
}
