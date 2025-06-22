/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:24:30 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/22 12:29:39 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **env)
{
	int			status;
	size_t		i;
	t_processes	prcs;

	if (argc != 5)
		return (print_user_errno(22));
	if (pipe(prcs.pipefd) == -1)
		return (print_system_errno());
	if (create_children(argc, argv, &prcs) == EXIT_FAILURE)
		return (print_system_errno());
	
	i = 0;
	while (i < argc - 3)
	{
		waitpid(prcs.child[i], &status, 0);
		i++;
	}
	free(prcs.child);
	close(prcs.pipefd[0]);
	close(prcs.pipefd[1]);
	return (EXIT_SUCCESS);
}
