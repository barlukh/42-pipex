/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:32:46 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/26 07:25:11 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*find_exec_path(t_variables *var);
static char	*check_env(t_variables *var);
static char	*build_path(t_variables *var, char **paths_split);

void	child_execute(t_variables *var, int i)
{
	while (var->argv[i + 2][var->offset] == ' ')
		var->offset++;
	if (var->argv[i + 2][var->offset] == '\0')
	{
		clean_struct(var);
		exit(0);
	}
	var->cmd = ft_split(var->argv[i + 2], ' ');
	if (var->cmd == NULL)
	{
		clean_struct(var);
		exit(print_set_errno("memory", 12, EXIT_FAILURE));
	}
	var->path = find_exec_path(var);
	if (var->path == NULL)
	{
		free_split(var->cmd);
		clean_struct(var);
		exit(print_set_errno("memory", 12, EXIT_FAILURE));
	}
	execve(var->path, var->cmd, var->env);
	print_system_errno(var->cmd[0], 127);
	free_split(var->cmd);
	clean_struct(var);
	exit(127);
}

// Finds if the passed command has an executable path in env.
static char	*find_exec_path(t_variables *var)
{
	char	**paths_split;
	char	*paths_all;
	char	*path_final;

	if (ft_strchr(var->cmd[0], '/'))
		return (var->cmd[0]);
	paths_all = check_env(var);
	if (!paths_all)
		return (NULL);
	paths_split = ft_split(paths_all, ':');
	free(paths_all);
	if (!paths_split)
		return (NULL);
	path_final = build_path(var, paths_split);
	free_split(paths_split);
	if (!path_final)
		return (NULL);
	return (path_final);
}

// Checks if PATH exists in env.
static char	*check_env(t_variables *var)
{
	char	*subs;
	size_t	i;

	i = 0;
	while (var->env[i] != NULL)
	{
		if (ft_strncmp(var->env[i], "PATH=", 5) == 0)
		{
			subs = ft_substr(var->env[i], 6, ft_strlen(var->env[i]) - 5);
			if (subs == NULL)
				return (NULL);
			return (subs);
		}
		i++;
	}
	print_set_errno(var->cmd[0], 2, 127);
	free_split(var->cmd);
	clean_struct(var);
	exit(127);
}

// Builds the executable path and checks its access rights.
static char	*build_path(t_variables *var, char **paths_split)
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
		path_final = ft_strjoin(temp, var->cmd[0]);
		free(temp);
		if (!path_final)
			return (NULL);
		if (access(path_final, X_OK) == 0)
			return (path_final);
		else
			free(path_final);
		i++;
	}
	print_custom_error(var->cmd[0], ": command not found\n", 127);
	free_split(var->cmd);
	free_split(paths_split);
	clean_struct(var);
	exit(127);
}
