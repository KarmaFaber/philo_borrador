/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzolotar <mzolotar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:55:39 by mzolotar          #+#    #+#             */
/*   Updated: 2025/04/23 10:03:05 by mzolotar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief 
 *
 * @param 
 *
 * @return 
 */
// 1 -true
// 0- false

static bool contain_digits_only(char *str)
{
	 int i;
	 
	 i=0;
	 while (str[i])
	 {
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	 }
	return (1);
}

/**
 * @brief 
 *
 * @param 
 * @return 
 */

// 0 -false
// 1 - true

bool check_argvs (int argc_var, char **argv_var)
{
	int i;
	int number;
	
	i = 1;
	if (argc_var - 1 < 4 || argc_var - 1 > 5) // argc != 5 y  argc != 6
		return (error_msg (STR_ERR_ARG, 0));
		
	while (i < argc_var)
	{
		if (!contain_digits_only(argv_var[i])) // solo digitos 
			return (error_msg (STR_ERR_INPUT_DIGIT, 0));
		number = atol_unsigned (argv_var[i]);
		if (i == 1 && (number <= 0 || number > MAX_PHILOS)) // numero de philos limitado a max_philos argv [1]
			return (error_msg(STR_ERR_P_NUM, 0));
		if (i != 1 && number == -1) // number > INT_MAX
			return (error_msg(STR_ERR_INPUT_DIGIT, 0));
		i++;
	}
	return (1);
}
