/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:24:30 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/26 09:35:38 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static void	fork_exec(t_variables *var);

int	main(int argc, char **argv, char **env)
{
	int			status;
	t_variables	var;

	var.argc = argc;
	var.argv = argv;
	var.env = env;
	if (argc != 5)
		return (print_set_errno("arguments", 22, EXIT_FAILURE));
	if (pipe(var.pipefd) == ERROR)
		return (print_system_errno("pipe", EXIT_FAILURE));
	var.child = malloc(sizeof(pid_t) * (var.argc - 3));
	if (var.child == NULL)
	{
		close_pipe(&var);
		return (print_set_errno("memory", 12, EXIT_FAILURE));
	}
	fork_exec(&var);
	close_pipe(&var);
	status = parent_wait(var);
	free(var.child);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

// Forks and executes child processes.
static void	fork_exec(t_variables *var)
{
	int	i;

	i = 0;
	while (i < var->argc - 3)
	{
		var->child[i] = fork();
		if (var->child[i] == (pid_t)(ERROR))
			return ;
		else if (var->child[i] == (pid_t)0)
		{
			child_set_fds(var, i);
			child_execute(var, i);
		}
		i++;
	}
}
