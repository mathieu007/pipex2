NAME = libft.a

SRC	=	ft_atoi.c		\
		ft_atoi_long.c	\
		ft_bzero.c		\
		ft_calloc.c		\
		ft_isalnum.c	\
		ft_isalpha.c	\
		ft_isascii.c	\
		ft_isdigit.c	\
		ft_isprint.c	\
		ft_itoa.c		\
		ft_itoa_temp.c	\
		ft_memchr.c		\
		ft_memcmp.c		\
		ft_memcpy.c		\
		ft_memmove.c	\
		ft_memset.c		\
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c	\
		ft_putstr_fd.c	\
		ft_split.c		\
		ft_strchr.c		\
		ft_strdup.c		\
		ft_striteri.c	\
		ft_strjoin.c	\
		ft_strlcat.c 	\
		ft_strlcpy.c	\
		ft_strlen.c 	\
		ft_strmapi.c    \
		ft_strncmp.c	\
		ft_strnstr.c	\
		ft_strrchr.c	\
		ft_strtrim.c	\
		ft_substr.c		\
		ft_tolower.c	\
		ft_toupper.c	\

SRC_BONUS = ft_lstnew.c			\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c    	\
			ft_lstadd_back.c    \
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c			\
			
SRC_LST =	lst/lst_filter_get_next.c	\
			lst/lst_filter_indices.c	\
			lst/lst_select.c	\
			lst/lst_insert.c	\
			lst/lst_reset.c	\
			lst/lst_group_by.c	\
			lst/lst_filter_avg.c	\
			lst/internal/lst_free_internal.c	\
			lst/internal/lst_new_internal.c	\
			lst/internal/lst_free_data_internal.c	\
			lst/lst_new.c	\
			lst/lst_reverse_select.c	\
			lst/ft_split_temp.c	\
			lst/_lst_group_by_add.c	\
			lst/lst_order_by.c	\
			lst/lst_utils_internal.c	\
			lst/lst_filter_index_of.c	\
			lst/lst_utils_internal2.c	\
			lst/lst_filter_contains.c	\
			lst/lst_filter_last.c	\
			lst/lst_last.c	\
			lst/func/to_str.c	\
			lst/func/to_int.c	\
			lst/func/to_long.c	\
			lst/func/inc_ptr.c	\
			lst/func/params.c	\
			lst/func/to_short.c	\
			lst/func/to_char.c	\
			lst/lst_filter_max.c	\
			lst/utils.c	\
			lst/lst_replace.c	\
			lst/lst_filter_get_nth.c	\
			lst/lst_filter_sum.c	\
			lst/lst_int_to_bool_array.c	\
			lst/lst_filter_count.c	\
			lst/lst_free.c	\
			lst/lst_swap.c	\
			lst/ft_substr_temp.c	\
			lst/lst_add.c	\
			lst/lst_sequence_equal.c	\
			lst/lst_filter.c	\
			lst/lst_filter_exclude.c	\
			lst/lst_filter_range.c	\
			lst/lst_firts.c	\
			lst/lst_new_item.c	\
			lst/lst_remove.c	\
			lst/ft_split_many_temp.c	\
			lst/lst_filter_first.c	\
			lst/lst_get_alloc_size.c	\
			lst/_lst_group_by_internal.c	\
			lst/lst_reverse.c	\
			lst/lst_rotate.c	\
			lst/lst_hashset.c	\
			lst/lst_to_array.c	\
			lst/lst_filter_min.c	\
			lst/memory_pool.c	\
			lst/lst_get.c	\
			lst/lst_group_by_get.c	\
			lst/lst_copy.c	\
			lst/_lst_group_by_new.c	\
			lst/lst_filter_include.c	\


LST_SRCDIR	= lst
SRCDIR		= .
INCDIR		= include
BUILDDIR	= obj
TARGETDIR	= bin
SRCEXT		= c
OBJEXT		= o

OBJS 		= $(patsubst %,$(BUILDDIR)/%,$(SRC:.$(SRCEXT)=.$(OBJEXT)))
OBJS_BONUS	= $(patsubst %,$(BUILDDIR)/%,$(SRC_BONUS:.$(SRCEXT)=.$(OBJEXT)))
LST_OBJS	= $(patsubst %,$(BUILDDIR)/%,$(SRC_LST:.$(SRCEXT)=.$(OBJEXT)))

CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
AR = ar crs

all: directories $(NAME) bonus lst

directories:
	mkdir -p $(TARGETDIR)
	mkdir -p $(BUILDDIR)

bonus: $(OBJS_BONUS)
	$(AR) $(NAME) $^
	
lst: $(LST_OBJS)
	$(AR) $(NAME) $^

clean:
	$(RM) -rf $(BUILDDIR)

fclean:	clean
	$(RM) $(NAME)	

re:	fclean all

# $(NAME): $(OBJS)
# 	$(AR) $@ $^
$(NAME): $(OBJS) $(LST_OBJS) $(BONUS_OBJS)
	$(AR) $@ $^

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(AR) $@ $<

.PHONY: bonus all clean fclean re
