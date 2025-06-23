/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:32:46 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/23 12:38:18 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*find_path(char *cmd, char **env);
static char	*ft_getenv(char **env, char *name);
static char	*get_full_cmd(char **arr, char *cmd);

int	child_execute(char **argv, char**env, int i)
{
	char	**arg;
	char	*path;

	arg = ft_split(argv[i + 2], ' ');
	if (arg == NULL)
		return (EXIT_FAILURE);
	path = find_path(arg[0], env);
	if (path == NULL)
		return (EXIT_FAILURE);
	execve(path, arg, env);
	return (EXIT_SUCCESS);
}

static char	*find_path(char *cmd, char **env)
{
	char	**arr;
	char	*path;
	char	*full_cmd;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	path = ft_getenv(env, "PATH");
	if (!path)
		return (NULL);
	arr = ft_split(path, ':');
	if (!arr)
		return (free(path), NULL);
	free(path);
	full_cmd = get_full_cmd(arr, cmd);
	if (!full_cmd)
		return (free_split(arr), free(full_cmd), NULL);
	return (free_split(arr), full_cmd);
}

static char	*ft_getenv(char **env, char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0)
			return (ft_substr(env[i], len + 1, ft_strlen(env[i]) - len - 1));
		i++;
	}
	return (NULL);
}

static char	*get_full_cmd(char **arr, char *cmd)
{
	int		i;
	char	*tmp_cmd;
	char	*full_cmd;

	i = 0;
	while (arr[i])
	{
		tmp_cmd = ft_strjoin(arr[i], "/");
		if (!tmp_cmd)
			return (NULL);
		full_cmd = ft_strjoin(tmp_cmd, cmd);
		if (!full_cmd)
			return (free(tmp_cmd), NULL);
		free(tmp_cmd);
		if (access(full_cmd, X_OK) == 0)
			return (full_cmd);
		else
			free(full_cmd);
		i++;
	}
	return (NULL);
}
