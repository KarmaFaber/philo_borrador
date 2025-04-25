/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:40:27 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/25 10:14:14 by mzolotar         ###   ########.fr       */
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
static void see_struct_data(t_program *program)   // borrar testeo
{
    printf("\n\n=== Datos del programa ===\n");
    printf("Número de filósofos       : %hu\n", program->num_philos);
    printf("Tiempo para morir         : %ld ms\n", program->time_to_die);
    printf("Tiempo para comer         : %ld ms\n", program->time_to_eat);
    printf("Tiempo para dormir        : %ld ms\n", program->time_to_sleep);
    printf("Número de comidas requeridas: %u\n", program->num_times_to_eat);
    printf("Simulación iniciada en    : %ld ms\n", program->start_time);
    printf("Estado de muerte global   : %d\n", program->dead_p_num);

    printf("\n=== Datos de los filósofos ===\n");
    for (int i = 0; i < program->num_philos; i++)
    {
        t_philo *philo = &program->philos[i];
        printf("\n--- Filósofo %d ---\n", philo->id);
        printf("ID                        : %hu\n", philo->id);
        printf("Comidas consumidas        : %u\n", philo->meals_eaten);
        printf("Última comida             : %ld ms\n", philo->last_meal);
        printf("Estado de muerte          : %s\n", philo->dead_philo ? "Sí" : "No");

    }
}
*/

int main (int argc, char **argv)
{
	t_program program;

	if (!check_argvs(argc, argv))
		return (1);
	
	if (!init_program(&program, argv))
		return (1);
    
    //program.start_time = timestamp();
	if(!init_philo(&program))   
        return (1);

	//see_struct_data(&program);   // borrar testeo
	
    final_print(&program);
    
	free_all(&program);

	return (0);
}
