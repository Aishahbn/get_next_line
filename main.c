/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaninas <abaninas@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 15:10:50 by abaninas          #+#    #+#             */
/*   Updated: 2026/11/19 15:41:23 by abaninas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.c"
#include <stdio.h>
#include <fcntl.h>

int main()
 {
   int fd;
   int fd1;
   char s;
   char s1

	fd (open "f.txt", O_RNDOLY);
	fd1 (open "f1.txt", O_RNDOLY);
	 while((s = get_next_line(fd)) != NULL)
	 {
		 printf("%s", s);
		 free (s);
	 }
	 printf("\n \n");
	 while((s1 = get_next_line(fd1)) != NULL)
	 {
		 printf("%s", s1);
		 free (s1);
	}
	close(fd);
	close (fd1);
	 return (0);
 }
