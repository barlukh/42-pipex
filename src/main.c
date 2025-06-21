/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:24:30 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/21 11:17:17 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_processes	prcs;

	if (argc != 5)
		return (print_user_errno(22));
	if (create_pipes(argc, &prcs) == EXIT_FAILURE)
		return (print_system_errno());
	if (create_children(argc, &prcs) == EXIT_FAILURE)
		return (print_system_errno());

	close_pipes((argc - 4), &prcs);
	free(prcs.pipefd);
	free(prcs.child);
	return (EXIT_SUCCESS);
}
