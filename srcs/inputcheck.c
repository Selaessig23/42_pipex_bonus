/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 09:47:45 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/02 15:06:23 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * helper function for bin_paths_init
 * creates the pathname + command - structure of the binary-file
 * 
 * @param command the specific command selected from **argv
 * @param paths all the possible paths, transmitted by and 
 * selected from *envp[]
*/
static char	*helper_binpathname(char *command, char **paths)
{
	char	*temp0;
	char	*temp1;
	char	*temp2;

	temp0 = ft_strjoin(*paths, "/");
	if (!temp0)
		error_handling(2, 0, 0);
	temp1 = ft_strjoin(temp0, command);
	free (temp0);
	if (!temp1)
		error_handling(2, 0, 0);
	temp2 = ft_strtrim(temp1, "PATH=");
	free (temp1);
	if (!temp2)
		error_handling(2, 0, 0);
	return (temp2);
}

/**
 * checks if the input commands are accessible
 * and writes the full path of the command to bin_paths
 * otherwise it writes error999
 * 
 * @param command the specific command selected of **argv
 * @param paths all the possible paths, transmitted by and 
 * selected from *envp[]
 * @param bin_paths this variable will be created by integrating 
 * correct path to command (=path of binary)
*/
int	bin_paths_init(char *command, char **paths, char **bin_paths)
{
	char	*temp;
	int		i;

	i = 0;
	while (*paths)
	{
		temp = helper_binpathname(command, paths);
		if (!temp)
			error_handling(2, 0, 0);
		if (!access(temp, X_OK))
		{
			*bin_paths = ft_strdup(temp);
			free(temp);
			return (0);
		}
		free(temp);
		paths++;
		i++;
	}
	*bin_paths = ft_strdup("error999");
	return (1);
}

/**
 * checks if there are flags within the command
 * and deletes them in variable temp to
 * be able to check existence of the binary file of the common command
 * 
 * @param argv a specific string from **argv (argument vector)
*/
char	*flagcheck(const char *argv)
{
	char	*temp0;
	size_t	i;

	i = 0;
	while (argv[i] && (argv[i] != ' '))
		i++;
	if (i == ft_strlen(argv))
	{
		temp0 = ft_strdup(argv);
		if (!temp0)
			error_handling(2, 0, 0);
	}
	else
	{
		temp0 = (char *)malloc(sizeof(char) * (i + 1));
		if (!temp0)
			error_handling(2, 0, 0);
		temp0 = (ft_memmove(temp0, argv, i));
		temp0[i] = '\0';
	}
	return (temp0);
}
