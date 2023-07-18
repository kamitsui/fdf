/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamitsui <kamitsui@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 12:04:40 by kamitsui          #+#    #+#             */
/*   Updated: 2023/07/04 20:39:55 by kamitsui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ_END	0
# define WRITE_END	1
# define HERE_DOC	"here_doc"
# define PROMPT		">"

# define BIT_NORMAL		0x00
# define BIT_HERE_DOC	0x01
# define BIT_OVER_RIDE	0x02
# define BIT_APPEND		0x04

typedef struct s_pipex
{
	char	*in_file;
	char	*out_file;
	char	**cmds;
	int		num_cmds;
	char	**env;
	int		status;
	int		mode;
	char	*limiter;
	char	*dir;
}	t_pipex;

void	initialize_pipex(int argc, char **argv, char **env, t_pipex *pipex);
void	check_argc(int argc);
int		set_input(t_pipex *pipex);
void	set_output(t_pipex *pipex);
void	ft_perr_exit(char *message);
void	ft_errno_exit(char *cause);
int		ft_errno_set_status(char *cause);
void	parent_process(int pipefd[2]);
void	child_process(t_pipex *pipex, int pipefd[2], char *arguments[], int i);
void	exec_file(char *file, char *arguments[], char *env[]);
char	*substr_env(char *name, char *env[]);

#endif
