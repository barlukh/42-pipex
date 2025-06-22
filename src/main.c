/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:24:30 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/22 16:48:11 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	fork_exec(t_arguments args, t_processes *prcs);

int	main(int argc, char **argv, char **env)
{
	int			status;
	size_t		i;
	t_arguments	args;
	t_processes	prcs;

	if (argc != 5)
		return (print_user_errno(22));
	if (pipe(prcs.pipefd) == ERROR)
		return (print_system_errno());
	args.argc = argc;
	args.argv = argv;
	args.env = env;
	if (fork_exec(args, &prcs) == EXIT_FAILURE)
		return (print_system_errno());
	i = 0;
	while (i < argc - 3)
	{
		waitpid(prcs.child[i], &status, 0);
		i++;
	}
	close_pipe(&prcs);
	free(prcs.child);
	return (EXIT_SUCCESS);
}

// Main function for operating child processes.
static int	fork_exec(t_arguments args, t_processes *prcs)
{
	size_t	i;

	prcs->child = malloc(sizeof(pid_t) * (args.argc - 3));
	if (prcs->child == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < args.argc - 3)
	{
		prcs->child[i] = fork();
		if (prcs->child[i] == (pid_t)(ERROR))
			return (EXIT_FAILURE);
		else if (prcs->child[i] == (pid_t)0)
		{
			if (child_set_fds(args.argc, args.argv, prcs, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (child_execute(args, prcs, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
