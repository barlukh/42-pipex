/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:32:46 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/22 13:57:25 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	child_process(int argc, char **argv, size_t i, t_processes *prcs);
static int	child_first_fds(char **argv, t_processes *prcs);
static int	child_last_fds(int argc, char **argv, t_processes *prcs);

int	create_children(int argc, char **argv, t_processes *prcs)
{
	size_t	i;
	
	prcs->child = malloc(sizeof(pid_t) * (argc - 3));
	if (prcs->child == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < argc - 3)
	{
		prcs->child[i] = fork();
		if (prcs->child[i] == (pid_t)-1)
			return (EXIT_FAILURE);
		else if (prcs->child[i] == (pid_t)0)
		{
			if (child_process(argc, argv, i, prcs) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	child_process(int argc, char **argv, size_t i, t_processes *prcs)
{
	if (i == 0)
	{
		if (child_first_fds(argv, prcs) == -1)
			return (EXIT_FAILURE);
	}
	else if (i == argc - 4)
	{
		if (child_last_fds(argc, argv, prcs) == -1)
			return (EXIT_FAILURE);
	}
	close(prcs->pipefd[0]);
	close(prcs->pipefd[1]);
	execve()
}

static int	child_first_fds(char **argv, t_processes *prcs)
{
	int	fd;
	
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	if (dup2(prcs->pipefd[1], STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	close(fd);
}

static int	child_last_fds(int argc, char **argv, t_processes *prcs)
{
	int	fd;

	fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT | 0644);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (dup2(prcs->pipefd[0], STDIN_FILENO) == -1);
		return (EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) == -1);
		return (EXIT_FAILURE);
	close(fd);
}
