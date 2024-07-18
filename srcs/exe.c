/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstracke <mstracke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:55:40 by mstracke          #+#    #+#             */
/*   Updated: 2024/07/02 18:07:50 by mstracke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * function to handle the input / output management
 * 
 * @param file the file that has to be used
 * @param rdwr info if read (0) or write (1) is required
*/
static void	handle_dup(char *file, bool rdwr)
{
	int	fd;
	int	test_fd;

	if (rdwr == 0)
		fd = open(file, O_RDWR);
	else
	{
		open(file, O_TRUNC);
		fd = open(file, O_WRONLY);
	}
	if (fd < 0)
		error_handling(0, 0, 0);
	if (rdwr == 0)
		test_fd = dup2(fd, STDIN_FILENO);
	else
		test_fd = dup2(fd, STDOUT_FILENO);
	if (test_fd < 0)
		error_handling(0, 0, 0);
	if (close(fd) < 0)
		error_handling(0, 0, 0);
}

/**
 * function to execute command 1 within the (1st) child process
 * 
 * @param i the struct which contains all required infos for pipex program
 * @param p1 the file descriptor of pipefd[1]
 * @param envp required input for execve, 
 * holds current environment of the process
*/
static void	child_comm1(t_envp *i, int *p, char *const envp[])
{
	close(p[0]);
	if (access(i->infile, R_OK))
	{
		close(p[1]);
		free_struct(i);
		exit (127);
	}
	if (!ft_strncmp(i->bin_paths[0], "error999", 8))
	{
		close(p[1]);
		error_handling(3, i, 0);
	}
	else
	{
		handle_dup(i->infile, 0);
		dup2(p[1], STDOUT_FILENO);
		if (execve(i->bin_paths[0], i->commands[0], envp) == -1)
		{
			perror("Error executing: ");
			ft_printf(" %s\n", i->commands[0][0]);
			exit(127);
		}
	}
}

/**
 * function to execute command 2 within the (2nd) child process
 * 
 * @param i the struct which contains all required infos for pipex program
 * @param p0 the file descriptor of pipefd[0]
 * @param exe_argv the required information about command to execute
 * @param envp required input for execve, 
 * holds current environment of the process
*/
static void	child_comm2(t_envp *i, int *p, char *const envp[])
{
	close(p[1]);
	if (!ft_strncmp(i->bin_paths[1], "error999", 8))
	{
		close(p[0]);
		error_handling(3, i, 1);
	}
	else
	{
		dup2(p[0], STDIN_FILENO);
		handle_dup(i->outfile, 1);
		if (execve(i->bin_paths[1], i->commands[1], envp) == -1)
		{
			perror("Error executing: ");
			ft_printf(" %s\n", i->commands[1][0]);
			exit(127);
		}
	}
}

/**
 * function to run the 1st parent process
 * (continuing with 2nd command)
 * 
 * @param infos the struct which contains all required infos for pipex program
 * @param pipefd0 the file descriptor of pipefd[0]
 * @param envp required input for execve, 
 * holds current environment of the process
*/
static int	parent1(t_envp *infos, int *pipefd, char *const envp[], pid_t pid1)
{
	pid_t	pid2;
	size_t	i;
	int		status;
	int		exitcode;

	exitcode = 0;
	i = 0;
	pid2 = fork();
	status = 0;
	if (pid2 < 0)
		error_handling(0, 0, 0);
	else if (pid2 == 0)
		child_comm2(infos, pipefd, envp);
	else
	{
		if (ft_strncmp(infos->bin_paths[0], "error999", 8) 
			&& ft_strncmp(infos->bin_paths[1], "error999", 8))
			waitpid(pid1, &status, 0);
		waitpid(pid2, &status, 0);
		if (WIFEXITED(status))
			exitcode = WEXITSTATUS(status);
		close(pipefd[0]);
	}
	return (exitcode);
}

/**
 * function to organise execution of 2 commands
 * 
 * @param infos the struct which contains all required infos for pipex program
 * @param envp required input for execve, 
 * holds current environment of the process
*/
// int	ft_execute(t_envp *infos, char *const envp[])
int	ft_execute(t_envp *infos, char *const envp[])
{
	pid_t	pid;
	int		pipefd[2];
	int		exitcode;

	exitcode = 0;
	if (pipe(pipefd) == -1)
		error_handling(0, 0, 0);
	pid = fork();
	if (pid < 0)
		error_handling(0, 0, 0);
	else if (pid == 0)
		child_comm1(infos, pipefd, envp);
	else
	{
		close(pipefd[1]);
		if (!ft_strncmp(infos->bin_paths[0], "error999", 8)
			&& !ft_strncmp(infos->bin_paths[1], "error999", 8))
			wait(&pid);
		exitcode = parent1(infos, pipefd, envp, pid);
	}
	return (exitcode);
}
