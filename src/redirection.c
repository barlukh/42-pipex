/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 14:56:36 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/26 07:25:33 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	child_first_set_fds(t_variables *var);
static void	child_last_set_fds(t_variables *var);

void	child_set_fds(t_variables *var, int i)
{
	if (i == 0)
		child_first_set_fds(var);
	else if (i == var->argc - 4)
		child_last_set_fds(var);
}

// Sets file descriptors of the first child process (argument).
static void	child_first_set_fds(t_variables *var)
{
	int	fd;

	close(var->pipefd[0]);
	fd = open(var->argv[1], O_RDONLY);
	if (fd == ERROR)
	{
		close(var->pipefd[1]);
		free(var->child);
		exit(print_system_errno(var->argv[1], EXIT_FAILURE));
	}
	if (dup2(fd, STDIN_FILENO) == ERROR
		|| dup2(var->pipefd[1], STDOUT_FILENO) == ERROR)
	{
		close(fd);
		close(var->pipefd[1]);
		free(var->child);
		exit(print_system_errno("dup2", EXIT_FAILURE));
	}
	close(var->pipefd[1]);
	close(fd);
}

// Sets file descriptors of the last child process (argument).
static void	child_last_set_fds(t_variables *var)
{
	int	fd;

	close(var->pipefd[1]);
	fd = open(var->argv[var->argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == ERROR)
	{
		close(var->pipefd[0]);
		free(var->child);
		exit(print_system_errno(var->argv[var->argc - 1], EXIT_FAILURE));
	}
	if (dup2(var->pipefd[0], STDIN_FILENO) == ERROR
		|| dup2(fd, STDOUT_FILENO) == ERROR)
	{
		close(fd);
		close(var->pipefd[0]);
		free(var->child);
		exit(print_system_errno("dup2", EXIT_FAILURE));
	}
	close(var->pipefd[0]);
	close(fd);
}
