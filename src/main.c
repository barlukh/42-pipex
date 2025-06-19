/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 13:24:30 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/19 15:13:12 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/pipex.h"

int	main(int argc, char **argv)
{
	if (validate_arguments(argc, argv) == EXIT_FAILURE);
	{
		perror("Invalid input");
		ft_putstr(strerror(errno));
		exit(errno);
	}
	return (0);
}
