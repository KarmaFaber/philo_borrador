/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:40:27 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/28 09:16:32 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 * @return 
 */

int main (int argc, char **argv)
{
    t_program program;

    if (!check_argvs(argc, argv))
        return (1);
    if (!init_program(&program, argv) || !init_philo(&program))
        return (1);
    final_print(&program);  //revisar si lo meto
    free_all(&program);
    return (0);
}
