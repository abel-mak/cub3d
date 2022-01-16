/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 19:13:07 by abel-mak          #+#    #+#             */
/*   Updated: 2020/11/18 08:36:53 by abel-mak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# define ERO "Error\nerror parsing "
# define LEFT 123
# define RIGHT 124
# define DOWN 125
# define UP 126
# define ENTER 36
# define PI 3.14159265358979323846
# define FOV 1.0471975
# define BO 64
# define SPACE 49
# define AKEY 0
# define DKEY 2
# define WKEY 13
# define SKEY 1

/*
** FOV is 60 degree in radians
*/

typedef struct	s_point
{
	float x;
	float y;
}				t_point;

typedef struct	s_angle
{
	float start;
	float end;
}				t_angle;

typedef struct	s_player
{
	t_point	*pos;
	float	rotangle;
}				t_player;

/*
** xpositon to know sprite position on the screen
** to know where to start drawing the sprite
** dist_to_p distance to player
** offset is same as texture offset for stretching
** the image to not get the weird shape of the wall
** pos -> sprite position
*/

typedef struct	s_sprite
{
	t_point *pos;
	int		width;
	int		height;
	float	offset;
	float	angle;
	int		visible;
	float	sprite_height;
	float	dist_to_p;
	float	xposition;
	float	start;
	float	end;
	float	hei_off;
	int		code;
}				t_sprite;

typedef struct	s_wall
{
	float height;
	float offset;
	float hei_off;
}				t_wall;

typedef struct	s_ray
{
	t_point *horiz;
	t_point *verti;
	int		hitverti;
	float	raydist;
	float	angle;
}				t_ray;

typedef struct	s_file
{
	char	**map;
	int		w_width;
	int		w_height;
	int		map_w;
	int		map_h;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s1;
	char	*s2;
	int		f;
	int		c;
	int		fd;
	int		ready;
}				t_file;

typedef struct	s_animation
{
	int		frames;
	int		n;
	int		w;
	int		h;
	void	*img_ptr;
	int		*data;
}				t_animation;

/*
** dplane => distance to projection plane
** spt => sprties_table
*/

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	*player;
	char		**map;
	void		*img_ptr;
	int			*data;
	int			**textdata;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			**spritedata;
	float		dplane;
	int			num_spr;
	t_sprite	**spt;
	t_file		*cub_file;
	t_animation *animation;
	int			dark;
	float		trans_x;
	float		trans_y;
	int         key;
}				t_data;

typedef	struct	s_li
{
	void		*content;
	struct s_li	*next;
}				t_li;

int				rgb(unsigned char r, unsigned char g, unsigned char b);
void			data_pixel_put(t_data *info, int x, int y, int color);
void			swap(float *a, float *b);
void			line_verti(t_data *info, t_point *p1, t_point *p2);
void			line(t_data *info, t_point *p1, t_point *p2);
int				is_pos(char c);
void			set_player_rotangle(t_data *info, int i, int j);
void			initplayer(t_data *info);
int				is_by_player(t_data *info, int i, int j);
t_point			*pnt(float x, float y);
void			draw_rect_map(t_data *info, int i, int j);
void			draw_map(t_data *info);
void			init_sprites_pos(t_data *info);
float			normalize(float angle);
float			dist(t_point *a, t_point *b);
int				israydown(float angle);
int				israyright(float angle);
t_point			*horizint(t_player *player, t_file *cub_file, float normangle);
t_point			*verticint(t_player *player, t_file *cub_file, float normangle);
void			castrays(t_data *info);
float			minuspitopi(float angle);
void			reset_sprite(t_data *info, t_sprite *sp);
void			sprite_update(t_data *info);
t_sprite		**sprite_sort(t_data *info);
void			draw_sprite_stripe(t_data *info, t_sprite *sp, float raydist
		, int i);
void			sprite_draw(t_data *info, int i, float raydist);
float			get_wall(t_data *info, t_ray *ray, t_wall *wall, int i);
int				darken(t_data *info, int color, float value, float max_value);
void			draw_ceil_strip(t_data *info, int column, float wallheight);
void			draw_floor_strip(t_data *info, int column, float wallheight);
float			get_tex_y(int from, t_file *c, t_wall *wall);
void			draw_wall_strip(t_data *info, int column, t_wall *wall,
		t_ray *ray);
void			castwalls(t_data *info);
int				clear_gun(int key, t_data *info);
int				update_gun(int key, t_data *info);
void			check_next_pos_up(t_data *info, float xcord, float ycord);
void			get_new_image(t_data *info);
void			build_image(t_data *info, int key);
void			free_cub_file(t_file *c);
void			free_info(t_data *info);
int				free_exit(t_data *info);
int				update(int key, t_data *info);
int				reset(t_data *info);
t_sprite		**init_sprites(int num_spr);
t_animation		*init_animation(t_data *info);
t_file			*parse(char **argv);
int				scale_gun_w(t_file *c);
int				scale_gun_h(t_file *c);
void			draw_gun(t_data *info, int n);
int				keyrelease(int key, t_data *info);
t_data			*init_info(char **argv);
void			init_wall_tex(t_data *info);
void			init_sp_tex(t_data *info);
void			write_to_buff(char *buff, int *start, unsigned int input,
		int len);
void			file_type_data(t_data *info, int fd);
void			img_info_data(t_data *info, int fd);
void			raw_pixel_data(t_data *info, int fd);
int				put_error(char *code);
void			map_error(int i, int j);
t_li			*lst_new(void *content);
void			lst_add_back(t_li *head, void *content);
void			lst_free(t_li *head);
int				lst_len(t_li *head);
void			lst_add_front(t_li **head, void *content);
int				set_res(int *res, int *j);
int				check_res(int *res, int j);
int				color(int *col, char *str, char *code);
int				get_r(t_file *cub_file, char *line);
int				check_path(char *path);
int				get_path(char **path, char *line);
int				is_inner(char c);
void			check_space_neighbors(char **arr, int i, int j, t_file *c);
int				check_c(char **arr, t_file *c);
int				start_map(char *line);
void			add_space(t_li *head, size_t max_len);
size_t			add_space_top_bottom(t_li **head);
char			**map_to_array(t_li *head);
void			set_value(t_file *cub_file, t_li **head);
int				get_map(t_file *cub_file, char *line);
int				check_invalid(char *line);
int				is_set(t_file *cub_file, int nbit);
void			get_elem(t_file *c, char *line);
int				is_second_sp(t_file *c);
t_file			*parse(char **argv);
int				main(int argc, char **argv);
void			check_resolution(t_file *c);
void			game_loop(t_data *info);
void			rect(t_data *info, t_point *p, float size, int color);

#endif
