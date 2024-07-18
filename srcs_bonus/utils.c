/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:08:17 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/02 14:38:36 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * counts an returns the size of an array of strings
 * 
 * @param arr_str the array of strings to count
 */
size_t	ft_arrlen(char **arr_str)
{
	size_t	i;

	i = 0;
	while (arr_str[i])
		i++;
	return (i);
}

/**
 * free an array of strings
 * 
 * @param arr the array of strings to free
 */
void	ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

/**
 * function to free all important values of the struct
 * 
 * @param infos 
 * 
*/
void	free_struct(t_envp *infos)
{
	int	i;

	i = 0;
	while (infos->commands[i])
	{
		ft_free(infos->commands[i]);
		i++;
	}
	free(infos->commands);
	infos->commands = NULL;
	ft_free(infos->bin_paths);
}

/**
 * this function handles errors:
 * it prints error messages from errno
 * and exits the program
 * 
 * @param err if param is set, there must be a specific error
 * e.g. 1 = input error
 * @param i the struct which contains all required infos for pipex program
 * @param com_no number of command
 */
void	error_handling(int err, t_envp *i, int com_no)
{
	if (err == 4)
		ft_putstr_fd("PATH not readible from ENVP", 1);
	else if (err == 1)
	{
		errno = 5;
		ft_putstr_fd(INPUT_ERROR, 1);
	}
	else if (err == 2)
	{
		errno = 12;
		ft_putstr_fd("Problems with malloc", 1);
	}
	else if (err == 3)
	{
		ft_putstr_fd("zsh: ", 2);
		ft_printf("command not found: %s\n", i->commands[com_no][0]);
		free_struct(i);
		exit(127);
	}
	perror("Error");
	exit(EXIT_FAILURE);
}
