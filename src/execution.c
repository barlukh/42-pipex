/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:32:46 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/23 15:55:32 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*find_path(char *cmd, char **env);
static char	*check_env(char **env);
static char	*build_path(char **paths_split, char *cmd);

int	child_execute(char **argv, char**env, int i)
{
	char	**arg;
	char	*path;

	arg = ft_split(argv[i + 2], ' ');
	if (arg == NULL)
		return (EXIT_FAILURE);
	path = find_path(arg[0], env);
	if (path == NULL)
	{
		free_split(arg);
		return (EXIT_FAILURE);
	}
	execve(path, arg, env);
	return (EXIT_SUCCESS);
}

static char	*find_path(char *cmd, char **env)
{
	char	**paths_split;
	char	*paths_all;
	char	*path_final;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	paths_all = check_env(env);
	if (!paths_all)
		return (NULL);
	paths_split = ft_split(paths_all, ':');
	free(paths_all);
	if (!paths_split)
		return (NULL);
	path_final = build_path(paths_split, cmd);
	free_split(paths_split);
	if (!path_final)
		return (NULL);
	return (path_final);
}

static char	*check_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (ft_substr(env[i], 5, ft_strlen(env[i]) - 5));
		i++;
	}
	return (NULL);
}

static char	*build_path(char **paths_split, char *cmd)
{
	char	*temp;
	char	*path_final;
	size_t	i;

	i = 0;
	while (paths_split[i] != NULL)
	{
		temp = ft_strjoin(paths_split[i], "/");
		if (!temp)
			return (NULL);
		path_final = ft_strjoin(temp, cmd);
		free(temp);
		if (!path_final)
			return (NULL);
		if (access(path_final, X_OK) == 0)
			return (path_final);
		else
			free(path_final);
		i++;
	}
	return (NULL);
}
