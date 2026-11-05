/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabuhuss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 22:13:59 by yabuhuss          #+#    #+#             */
/*   Updated: 2026/11/05 22:14:00 by yabuhuss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	str_len(char *str);
char	*get_next_line(int fd);
char	*search_n(char *str);
char	*str_join(char *s1, char *s2);
char	*str_sub(char *s, size_t start, size_t len);

#endif