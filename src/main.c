/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:24:30 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/23 13:38:04 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	fork_exec(t_arguments args, pid_t **child, int *pipefd);

int	main(int argc, char **argv, char **env)
{
	int			pipefd[2];
	int			status;
	pid_t		*child;
	t_arguments	args;

	child = NULL;
	args.argc = argc;
	args.argv = argv;
	args.env = env;
	if (argc != 5)
		return (print_user_errno(22));
	if (pipe(pipefd) == ERROR)
		return (print_system_errno());
	child = malloc(sizeof(pid_t) * (args.argc - 3));
	if (child == NULL)
		return (print_user_errno(12));
	if (fork_exec(args, &child, pipefd) == EXIT_FAILURE)
		return (print_system_errno());
	close(pipefd[0]);
	close(pipefd[1]);
	status = parent_wait(argc, child);
	free(child);
	return (status);
}

// Main function for operating child processes.
static int	fork_exec(t_arguments args, pid_t **child, int *pipefd)
{
	int	i;

	i = 0;
	while (i < args.argc - 3)
	{
		(*child)[i] = fork();
		if ((*child)[i] == (pid_t)(ERROR))
			return (EXIT_FAILURE);
		else if ((*child)[i] == (pid_t)0)
		{
			if (child_set_fds(args.argc, args.argv, pipefd, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (child_execute(args.argv, args.env, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
