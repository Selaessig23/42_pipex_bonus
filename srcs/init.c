/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:24:54 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/02 15:12:37 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * checks if infile is accessible
 * 
 * @param infos the struct with all required variables
 * @param infile the infile path or document
*/
int	init_infile(t_envp *infos, char *infile)
{
	if (!infile)
		infos->infile = infile;
	else if (access(infile, F_OK))
	{
		ft_putstr_fd("zsh: ", STDERR_FILENO);
		ft_printf("no such file or directory: %s\n", infile);
	}
	else if (access(infile, R_OK))
	{
		ft_putstr_fd("zsh: ", STDERR_FILENO);
		ft_printf("permission denied: %s\n", infile);
	}
	infos->infile = infile;
	return (0);
}

/**
 * function to initiate the commands & pathnames for struct infos
 * 
 * @param the struct to input the required data
 * @param argv all input arguments (argument vector)
 * @param paths all the possible paths, transmitted by and 
 * selected from *envp[]
*/
void	init_compath(t_envp *infos, char **argv, char **paths)
{
	char	*temp0;
	size_t	i;
	size_t	j;

	i = 2;
	j = 0;
	while (i < (infos->commands_no + 2))
	{
		temp0 = flagcheck(argv[i]);
		bin_paths_init(temp0, paths, &infos->bin_paths[j]);
		free(temp0);
		infos->commands[j] = ft_split(argv[i], ' ');
		if (!*infos->commands)
			error_handling(2, 0, 0);
		i++;
		j++;
	}
	infos->bin_paths[j] = NULL;
	infos->commands[j] = NULL;
}

/**
 * checks if outfile exists and if not creates outfile,
 * 
 * @param infos the struct which contains the outfile
*/
void	init_outfile(t_envp *infos)
{
	int	fd_out;

	fd_out = 0;
	if (access(infos->outfile, F_OK))
	{
		fd_out = open(infos->outfile, O_CREAT, 0644);
		if (fd_out == -1)
			error_handling(0, 0, 0);
	}
	else if (!access(infos->outfile, W_OK))
	{
		fd_out = open(infos->outfile, O_TRUNC);
		if (fd_out == -1)
			error_handling(0, 0, 0);
	}
	else
	{
		ft_putstr_fd("zsh: ", 2);
		ft_printf("permission denied: %s\n", infos->outfile);
		exit(1);
	}
	close(fd_out);
}

/**
 * checks the validity of all input parameters
 * and initiate the values for struct infos
 * 
 * this seems to be not necessary at this point
 * (located above "return"): 
 * 
 * 
 * @param argv all input arguments (argument vector)
 * @param paths all the possible paths, transmitted by and 
 * selected from *envp[]
 * @param infos the struct to input the required data
*/
int	init_check(char **argv, char **paths, t_envp *infos)
{
	infos->commands_no = (ft_arrlen(argv) - 1 - 2);
	infos->outfile = argv[ft_arrlen(argv) - 1];
	infos->bin_paths = (char **)malloc(sizeof(char *) 
			* (infos->commands_no + 1));
	if (!infos->bin_paths)
		error_handling(2, 0, 0);
	infos->commands = (char ***)malloc(sizeof(char **) 
			* (infos->commands_no + 1));
	if (!infos->commands)
		error_handling(2, 0, 0);
	init_infile(infos, argv[1]);
	init_outfile(infos);
	init_compath(infos, argv, paths);
	return (0);
}
