/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:56:36 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/24 09:57:13 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	child_first_set_fds(char **argv, int *pipefd);
static void	child_last_set_fds(int argc, char **argv, int *pipefd);

void	child_set_fds(int argc, char **argv, int *pipefd, int i)
{
	if (i == 0)
		child_first_set_fds(argv, pipefd);
	else if (i == argc - 4)
		child_last_set_fds(argc, argv, pipefd);
}

// Sets file descriptors of the first child process (argument).
static void	child_first_set_fds(char **argv, int *pipefd)
{
	int	fd;

	close(pipefd[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == ERROR)
	{
		close(pipefd[1]);
		exit (print_system_errno(argv[1]));
	}
	if (dup2(fd, STDIN_FILENO) == ERROR
		|| dup2(pipefd[1], STDOUT_FILENO) == ERROR)
	{
		close(pipefd[1]);
		close(fd);
		exit (print_system_errno("dup2"));
	}
	close(pipefd[1]);
	close(fd);
}

// Sets file descriptors of the last child process (argument).
static void	child_last_set_fds(int argc, char **argv, int *pipefd)
{
	int	fd;

	close(pipefd[1]);
	fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == ERROR)
	{
		close(pipefd[0]);
		print_system_errno(argv[argc - 1]);
		exit (EXIT_FAILURE);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == ERROR
		|| dup2(fd, STDOUT_FILENO) == ERROR)
	{
		close(pipefd[0]);
		close(fd);
		exit (print_system_errno("dup2"));
	}
	close(pipefd[0]);
	close(fd);
}
