/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgazur <bgazur@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 11:39:58 by bgazur            #+#    #+#             */
/*   Updated: 2025/06/19 15:12:36 by bgazur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

//------------------------------------------------------------------------------
// Library Headers
//------------------------------------------------------------------------------

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>


//------------------------------------------------------------------------------
// Macro Definitions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Type Definitions
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------

int		validate_arguments(int argc, char **argv);

/** Writes a string into the standard output followed by a newline character.
 * @param s String to write.
 * @return None.
 */
void	ft_putstr(const char *s);

/** Splits a string according to a specified delimiter.
 * @param s String to split.
 * @param c Delimiter.
 * @return Array of new strings, 'NULL' if the allocation fails.
 */
char	**ft_split(char const *s, char c);

/** Scans a string for the first instance of 'c'.
 * @param s String to search.
 * @param c Character to search for, passed as an int.
 * @return Pointer to the matching location, 'NULL' if no match.
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
 * @return New substring, 'NULL' if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);


#endif
