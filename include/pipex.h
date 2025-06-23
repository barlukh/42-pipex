/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:39:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/23 13:14:35 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

/** Command line arguments.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param env Environmental variables.
 */
typedef struct s_arguments
{
	int		argc;
	char	**argv;
	char	**env;
}	t_arguments;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/** Executes a command from the argument vector, replacing the child process.
 * @param argv Argument vector.
 * @param env Environmental variables.
 * @param i Index of a child process (argument).
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int		child_execute(char **argv, char**env, int i);

/** Sets file descriptors for a child process.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param pipefd Pipe (read end pipefd[0], write end pipefd[1]).
 * @param i Index of a child process (argument).
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int		child_set_fds(int argc, char **argv, int *pipefd, int i);

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

/** Writes a string into a file descriptor followed by a newline character.
 * @param s String to write.
 * @param fd File descriptor.
 * @return Number of characters written, -1 on error.
 */
int		ft_putstr(const char *s, int fd);

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
 * @param argc Argument count.
 * @param child Array of child processes.
 * @return Termination status of the last process.
 */
int		parent_wait(int argc, pid_t *child);

/** Prints an error message of the current errno.
 * @return Errno.
 */
int		print_system_errno(void);

/** Sets errno passed as an argument and prints its error message.
 * @param err Errno.
 * @return Errno.
 */
int		print_user_errno(int err);

#endif
