/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduvilla <aduvilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:57:12 by ctruchot          #+#    #+#             */
/*   Updated: 2024/04/09 17:59:05 by aduvilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

size_t	gnl_strlen(char *s);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_mallocstash(char *stash);
void	gnl_bzero(void *s, size_t size);
char	*gnl_cleanstash(char *stash, unsigned int start, size_t len);
int		gnl_isline(char *s);
char	*gnl_getline(char *s, size_t lineend);
char	*gnl_read(int fd, char *stash);
char	*get_next_line(int fd);
char	*update_stash(char *stash, char *buffer);
char	*prompted_gnl(char *prompt, int fd, int mode);

#endif
