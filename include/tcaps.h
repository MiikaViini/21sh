
#ifndef TCAPS_H
#define TCAPS_H

# include <termcap.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
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
	char			inp[BUFFSIZE];
	struct termios	orig_termios;
	t_clipboard		clipboard;
	char			**nl_addr;
	char			**history;
	char			*history_file;
	int				history_size;
	char			*input_cpy;
	char			*delim;
	int				ch;
	ssize_t			ws_col;
	ssize_t			ws_row;
	ssize_t			index;
	ssize_t			bytes;
	ssize_t			c_col;
	ssize_t			c_row;
	ssize_t			start_row;
	ssize_t			total_row;
	ssize_t			total_row_cpy;
	ssize_t			prompt_len;
	ssize_t			m_prompt_len;
	ssize_t			slash;
	ssize_t			q_qty;
	ssize_t			bslash;
	ssize_t			heredoc;
	ssize_t			his;
	char			quote;
}			t_term;

void	init_tcaps(t_term *t);
int		ft_getent(void);
void	run_capability(char *cap);
void	get_window_size(t_term *t);
void	get_history(t_term *t);

// input cycle
t_term	*input_cycle(t_term *t);
int		get_input(void);
void	insertion(t_term *t);
void	add_new_line(t_term *t, int pos);
char	*ft_is_prompt_line(t_term *t, int row);
void	set_cursor(ssize_t col, ssize_t row);
int		get_linenbr(void);
void	ft_reset_nl_addr(t_term *t);
ssize_t	ft_row_lowest_line(t_term *t);

void	ft_restart_cycle(t_term *t);

//signals
void	init_signals();

//dunno
void	ft_esc_parse(t_term *t);

void	ft_word_mv(t_term *t);
void	ft_line_up(t_term *t);
void	ft_line_down(t_term *t);
void	ft_scroll_down(void);

//clipboard
void	ft_cut(t_term *t);
void	ft_copy(t_term *t);
void	ft_paste(t_term *t);

//to be modified or moved
int		ft_sspace(const char *str);
void	ft_backspace(t_term *t);
void	ft_print_trail(t_term *t);
void	ft_quote_decrement(t_term *t, int num);
void	ft_deletion_shift(t_term *t, int mode);
void	ft_shift_nl_addr(t_term *t, int num);
void	ft_remove_nl_addr(t_term *t, ssize_t row);
int		ft_putc(int c);
void	ft_shift_insert(t_term *t);

void	trigger_nl(t_term *t); //XD

void	ft_trigger_nl(t_term *t); //XD
ssize_t	ft_row_lowest_line(t_term *t);
ssize_t	ft_len_lowest_line(t_term *t, ssize_t row); //maybe refactor with lowest
void	ft_add_nl_last_row(t_term *t, ssize_t pos);
void	ft_add_nl_mid_row(t_term *t, ssize_t row, ssize_t pos);

#endif
