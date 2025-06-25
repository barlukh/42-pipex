/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:39:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/25 11:53:08 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------

# define ERROR -1

# define NO_PREFIX 0
# define BASH 1

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

/** Variables for the main operation of the program.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param env Environmental variables.
 * @param pipefd Pipe (read end pipefd[0], write end pipefd[1]).
 * @param child Array of children process IDs.
 */
typedef struct s_variables
{
	int		argc;
	char	**argv;
	char	**env;
	int		pipefd[2];
	pid_t	*child;
}	t_variables;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/** Executes a command from the argument vector, replacing the child process.
 * @param var Variables for the main operation of the program.
 * @param i Index of a child process (argument).
 * @return None.
 */
void	child_execute(t_variables *var, int i);

/** Sets file descriptors for a child process.
 * @param var Variables for the main operation of the program.
 * @param i Index of a child process (argument).
 * @return None.
 */
void	child_set_fds(t_variables *var, int i);

/** Closes both ends of a pipe and frees a child array.
 * @param var Variables for the main operation of the program.
 * @return None.
 */
void	clean_struct(t_variables *var);

/** Closes both ends of a pipe.
 * @param var Variables for the main operation of the program.
 * @return None.
 */
void	close_pipe(t_variables *var);

/** Frees memory allocated by ft_split().
 * @param arr Allocated array of strings.
 * @return None.
 */
void	free_split(char **arr);

/** Copies bytes from one memory area to another; the areas must not overlap.
 * @param dest Pointer to the destination memory area.
 * @param src Pointer to the source memory area.
 * @param n Number of bytes to copy.
 * @return Pointer to the destination memory area.
 */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/** Outputs a string to a specified file descriptor
 * @param s String to output
 * @param fd File descriptor
 * @return None
 */
void	ft_putstr_fd(char *s, int fd);

/** Splits a string according to a specified delimiter.
 * @param s String to split.
 * @param c Delimiter.
 * @return Array of new strings, NULL if the allocation fails.
 */
char	**ft_split(char const *s, char c);

/** Scans a string for the first instance of a character.
 * @param s String to search.
 * @param c Character to search for, passed as an int.
 * @return Pointer to the matching location, NULL if no match.
 */
char	*ft_strchr(const char *s, int c);

/** Concatenates two strings using dynamic memory allocation.
 * @param s1 First string.
 * @param s2 Second string.
 * @return Pointer to the new string, NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2);

/** Calculates the length of a string.
 * @param s String to calculate the length of.
 * @return Number of bytes in the passed string.
 */
size_t	ft_strlen(const char *s);

/** Compares two strings.
 * @param s1 First string.
 * @param s2 Second string.
 * @param n Number of bytes to compare.
 * @return 0 if equal, negative if s1 < s2, positive if s1 > s2.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/** Creates a substring using dynamic memory allocation.
 * @param s Source string for the substring.
 * @param start Starting index.
 * @param len Length of the substring.
 * @return New substring, NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/** Waits for children processes to finish.
 * @param var Variables for the main operation of the program.
 * @return Termination status of the last process.
 */
int		parent_wait(t_variables var);

/** Prints a custom error message.
 * @param s1 First string.
 * @param s2 Second string.
 * @param status Exit status.
 * @return Exit status.
 */
int		print_custom_error(char *s1, char *s2, int status);

/** Sets errno and prints its error message.
 * @param prefix_flag Flag to signal the usage of shell prefix_flag.
 * @param s Custom string addition to the error message.
 * @param err Errno.
 * @param status Exit status.
 * @return Exit status.
 */
int		print_set_errno(int prefix_flag, char *s, int err, int status);

/** Prints an error message of the current errno.
 * @param prefix_flag Flag to signal the usage of shell prefix_flag.
 * @param s Custom string addition to the error message.
 * @param status Exit status.
 * @return Exit status.
 */
int		print_system_errno(int prefix_flag, char *s, int status);

#endif
