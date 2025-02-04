/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:42:33 by mzolotar          #+#    #+#             */
/*   Updated: 2025/02/04 12:08:38 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */

int init_program(t_program *program, char **argv)
{
	//...
	
	program->start_time = timestamp();
	program->dead = 0;				
	program->num_philos = atol_unsigned(argv[1]);
	program->time_to_die = atol_unsigned(argv[2]);
	program->time_to_eat =  atol_unsigned(argv[3]);
	program->time_to_sleep = atol_unsigned(argv[4]);
	if (argv[5])
		program->num_philos = atol_unsigned(argv[5]);
	if (argv[5] && program->num_times_to_eat == 0)
		return (0);
	return (1);
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

int init_philo(t_philo *philo, t_program *program, char **argv)
{
	
	

	//..
	return (1);
}