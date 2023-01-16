
#ifndef TCAPS_H
#define TCAPS_H

# include <termcap.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <string.h>
# include <limits.h>
# include <ctype.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/ioctl.h>

# define DEL		0
# define BCK		1
# define ENTER      10
# define CTRL_C		3
# define CTRL_D		4
# define CTRL_L		12
# define CTRL_W		23
# define CTRL_U		21
# define CTRL_Y		25
# define D_QUO		34
# define S_QUO		39
# define ESCAPE     27
# define LINE_MV    49
# define KEY_SHIFT  50
# define ARROW_UP   65
# define ARROW_DOWN	66
# define ARROW_LFT	67
# define ARROW_RGHT	68
# define CURS_END	70
# define CURS_BIGIN	72
# define ALT_LFT	98
# define ALT_RGHT	102
# define DOWN		261
# define UP			262
# define LEFT       263
# define RIGHT      264
# define BACKSPACE	127
# define TAB		9
# define COPY		0
# define CUT		1

# define BUFFSIZE   2048

typedef struct clipboard
{
	int		type;
	char	*buff;
}			t_clipboard;

typedef struct s_term
{
	struct termios	orig_termios;
	struct termios	raw;

	char			inp[BUFFSIZE];
	char			history_buff[BUFFSIZE];
	char			**history;
	int				history_size;
	t_clipboard		clipboard;
	char			**nl_addr;
	char			*history_file;
	char			*input_cpy;
	char			*delim;
	int				ch;
	int				history_row;
	ssize_t			ws_col;
	ssize_t			ws_row;
	ssize_t			index;
	ssize_t			bytes;
	ssize_t			start_row;
	ssize_t			c_col;
	ssize_t			c_row;
	ssize_t			total_row;
	ssize_t			total_row_cpy;
	ssize_t			prompt_len;
	ssize_t			m_prompt_len;
	ssize_t			q_qty;
	ssize_t			bslash;
	ssize_t			heredoc;
	ssize_t			his;
	ssize_t			sigint;
	char			quote;
}			t_term;

// misc
void	init_tcaps(t_term *t);
void	init_signals(void);
int		ft_getent(void);
void	run_capability(char *cap);
void	get_window_size(t_term *t);
int		get_linenbr(void);

// input cycle
int		input_cycle(t_term *t);
void	restart_cycle(t_term *t);
void	end_cycle(t_term *t);
int		get_input(void);
void	insertion(t_term *t);
void	add_new_line(t_term *t, char *array, ssize_t pos);

// cursor
void	set_cursor(ssize_t col, ssize_t row);
void	cursor_beginning(t_term *t);
void	cursor_end(t_term *t);
void	move_cursor_left(t_term *t);
void	move_cursor_right(t_term *t);


void	delete_char(t_term *t);

void	esc_parse(t_term *t);

void	word_mv(t_term *t);
void	line_up(t_term *t);
void	line_down(t_term *t);

//clipboard
void	clipboard(t_term *t);
void	ctrl_cut(t_term *t);
void	ctrl_copy(t_term *t);
void	ctrl_paste(t_term *t);

int		is_space(const char *str);
void	backspace(t_term *t);
void	deletion_shift(t_term *t, ssize_t index);
int		ft_putc(int c);
void	shift_insert(t_term *t);


// prompt and nl management
ssize_t	row_lowest_line(t_term *t);
char	*is_prompt_line(t_term *t, ssize_t row);
ssize_t	len_lowest_line(t_term *t, ssize_t row);
void	trigger_nl(t_term *t);
void	add_nl_last_row(t_term *t, char *array, ssize_t pos);
void	add_nl_mid_row(t_term *t, ssize_t row, ssize_t pos);
void	update_nl_addr_del(t_term *t);
void	shift_nl_addr(t_term *t, int num);
void	reset_nl_addr(t_term *t);
void	remove_nl_addr(t_term *t, ssize_t row);

void	print_prompt(ssize_t row);
void	print_trail(t_term *t);
void	create_prompt_line(t_term *t, ssize_t loc);
ssize_t	get_prompt_len(t_term *t, ssize_t row);
void	print_input(t_term *t, ssize_t row, int mode);

// history
void	get_history(t_term *t);
void	history_to_array(t_term *t);
void	history_trigger(t_term *t, ssize_t pos);
void	write_history_to_file(t_term *t);
void	add_command_to_history(t_term *t, char *line);
void	history_command(t_term *t);
void	history_reset_nl(t_term *t, char *inp);

void	scroll_down(void);
void	nl_removal(t_term *t);

//backslash and delim
int		backslash_escape_check(t_term *t, ssize_t pos);
int		delim_fetch(t_term *t);

//quotes
void	quote_handling(t_term *t, char ch);
void	quote_flag_reset(t_term *t);
void	quote_flag_check(t_term *t, ssize_t index);
void	quote_decrement(t_term *t, int num);

void	heredoc_handling(t_term *t);

//ctrl_d
int		ctrl_d_exit(t_term *t);
int		ctrl_d(t_term *t);

#endif
