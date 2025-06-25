/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:47:32 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/25 09:37:23 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	print_system_errno(int prefix_flag, char *s, int status)
{
	char	*err_s;

	if (prefix_flag == BASH)
	{
		err_s = ft_strjoin("bash: ", s);
		if (!err_s)
			return (EXIT_FAILURE);
		perror(err_s);
		free(err_s);
	}
	else
		perror(s);
	return (status);
}

int	print_set_errno(int prefix_flag, char *s, int err, int status)
{
	char	*err_s;

	errno = err;
	if (prefix_flag == BASH)
	{
		err_s = ft_strjoin("bash: ", s);
		if (!err_s)
			return (EXIT_FAILURE);
		perror(err_s);
		free(err_s);
	}
	else
		perror(s);
	return (status);
}

int	print_custom_error(char *s1, char *s2, int status)
{
	char	*err_s;

	err_s = ft_strjoin(s1, s2);
	if (!err_s)
		return (EXIT_FAILURE);
	ft_putstr_fd(err_s, STDERR_FILENO);
	free(err_s);
	return (status);
}

void	close_pipe(t_variables *var)
{
	close(var->pipefd[0]);
	close(var->pipefd[1]);
}
