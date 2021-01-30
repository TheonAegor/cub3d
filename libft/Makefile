NAME =	libft.a

SRCS =	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c ft_memcmp.c ft_memchr.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c  ft_putstr.c get_next_line.c get_next_line_utils.c

OBJS	= $(SRCS:.c=.o)

BONUSS	= ft_lstadd_back.c  ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c


BONUSO	= $(BONUSS:.c=.o)

CC		= gcc

RM		= rm -f

FLAGS	= -Wall -Wextra -Werror

%.c.o:
		@$(CC) -I./ $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(BONUSO)
		@ar rcs $(NAME) $(OBJS) $(BONUSO)

all:	$(NAME)


bonus:	$(BONUSO)
		ar rcs $(NAME) $(BONUSO)

clean:
		@$(RM) $(OBJS) $(BONUSO)

fclean: clean
	@$(RM) $(NAME)

re:		fclean all

.PHONY:
		all, clean, fclean, re, bonus, norm
