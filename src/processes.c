/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:32:46 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/22 15:10:28 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int child_execute(int argc, char **argv, size_t i, t_processes *prcs);

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
		if (prcs->child[i] == (pid_t)(-1))
			return (EXIT_FAILURE);
		else if (prcs->child[i] == (pid_t)0)
		{
			if (child_fds(argc, argv, i, prcs) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			if (child_execute(argc, argv, i, prcs) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int child_execute(int argc, char **argv, size_t i, t_processes *prcs)
{
	char	**arg;

	arg = ft_split(argv[i + OFFSET], ' ');
}
