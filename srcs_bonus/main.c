/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:20:29 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/09 14:52:37 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char *const envp[])
{
	char	**paths;
	t_envp	infos;
	int		statuscode;

	paths = NULL;
	statuscode = 0;
	if (argc >= 5)
	{
		if (!*envp)
			error_handling(4, 0, 0);
		while (*envp && ft_strncmp("PATH", *envp, 4))
			envp++;
		paths = ft_split(*envp, ':');
		if (!paths)
			error_handling(2, 0, 0);
		init_check(argv, paths, &infos);
		ft_free(paths);
		statuscode = ft_execute(&infos, envp);
		free_struct(&infos);
	}
	else
		error_handling(1, 0, 0);
	return (statuscode);
}
