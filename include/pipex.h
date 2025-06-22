/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:39:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/22 15:09:23 by bgazur           ###   ########.fr       */
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

# define OFFSET 2

//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------

/** Variables for handling processes.
 * @param pipfd Pipe (pipefd[0] read end, pipefd[1] write end).
 * @param child Array of child processes.
 */
typedef struct s_processes
{
	int		pipefd[2];
	pid_t	*child;
}	t_processes;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

/** Sets redirection of file descriptors for a child process.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param i Index of a child process (argument).
 * @param prcs Variables for handling processes.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int		child_fds(int argc, char **argv, size_t i, t_processes *prcs);

/** Closes both ends of a pipe.
 * @param prcs Variables for handling processes.
 * @return None.
 */
void	close_pipe(t_processes *prcs);

/** Creates all child processes.
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param prcs Variables for handling processes.
 * @return EXIT_SUCCESS or EXIT_FAILURE.
 */
int		create_children(int argc, char **argv, t_processes *prcs);

/** Prints an error message of the current errno.
 * @return Errno.
 */
int		print_system_errno(void);

/** Sets errno passed as an argument and prints its error message.
 * @param err Errno.
 * @return Errno.
 */
int		print_user_errno(int err);

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

/** Calculates the length of a string.
 * @param s String to calculate the length of.
 * @return Number of bytes in the passed string.
 */
size_t	ft_strlen(const char *s);

/** Creates a substring using dynamic memory allocation.
 * @param s Source string for the substring.
 * @param start Starting index.
 * @param len Length of the substring.
 * @return New substring, NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
