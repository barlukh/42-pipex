/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:24:30 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/24 09:30:57 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	fork_exec(t_arguments args, pid_t **child, int *pipefd);

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
		return (print_user_errno("arguments", 22));
	if (pipe(pipefd) == ERROR)
	{
		print_system_errno("pipe");
		return (EXIT_FAILURE);
	}
	child = malloc(sizeof(pid_t) * (args.argc - 3));
	if (child == NULL)
		return (print_user_errno("memory", 12));
	fork_exec(args, &child, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	status = parent_wait(argc, child);
	free(child);
	if (WIFEXITED(status))
    	return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

// Main function for operating child processes.
static void	fork_exec(t_arguments args, pid_t **child, int *pipefd)
{
	int	i;

	i = 0;
	while (i < args.argc - 3)
	{
		(*child)[i] = fork();
		if ((*child)[i] == (pid_t)(ERROR))
			return ;
		else if ((*child)[i] == (pid_t)0)
		{
			child_set_fds(args.argc, args.argv, pipefd, i);
			child_execute(args.argv, args.env, i);
		}
		i++;
	}
}
