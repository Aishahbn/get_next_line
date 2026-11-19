/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaninas <abaninas@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 15:06:18 by abaninas          #+#    #+#             */
/*   Updated: 2026/11/19 15:09:41 by abaninas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	str_len(char *str);
char	*get_next_line(int fd);
char	*search_n(char *str);
char	*str_join(char *s1, char *s2);
char	*str_sub(char *s, size_t start, size_t len);

#endif