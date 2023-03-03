#Compiler and Linker
CC          := gcc

#The Target Binary Program
NAME		:= push_swap
BONUS_NAME	:= checker
COMMONS_NAME	:= commons

#The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR			:= src/pipex
FINDIR			:= src
BONUSDIR		:= src/bonus
COMMONSDIR		:= src/common
INCDIR			:= include
BUILDDIR		:= obj
BUILDDIR_BONUS	:= obj_bonus
BUILDDIR_COMMONS:= obj_common
TARGETDIR		:= bin
SRCEXT			:= c
OBJEXT			:= o
LIBFT_DIR		:= libft
LIBFT_FILE		:= libft.a
LIBFT			:= $(LIBFT_DIR)/$(LIBFT_FILE)
INCLUDE			:= -I$(LIBFT_DIR)

#Flags, Libraries and Includes
CFLAGS      := -Wall -Wextra -Werror -g
LIB         := -L./$(LIBFT_DIR) -lm
# INC       := -I$(INCDIR) -I/usr/local/include
INCDEP      := -I$(INCDIR)


SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT)")
# SOURCES     :=  src/push_swap/push_swap.c	\

SRC_COMMONS := $(shell find $(COMMONSDIR) -type f -name *.$(SRCEXT)")

BONUS_SRC   :=	$(shell find $(BONUSDIR) -type f -name *.$(SRCEXT)")

OBJECTS				:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT))) $(patsubst $(COMMONSDIR)/%,$(BUILDDIR_COMMONS)/%,$(SRC_COMMONS:.$(SRCEXT)=.$(OBJEXT)))
OBJECTS_BONUS		:= $(patsubst $(BONUSDIR)/%,$(BUILDDIR_BONUS)/%,$(BONUS_SRC:.$(SRCEXT)=.$(OBJEXT))) $(patsubst $(COMMONSDIR)/%,$(BUILDDIR_COMMONS)/%,$(SRC_COMMONS:.$(SRCEXT)=.$(OBJEXT)))

all: directories $(NAME) $(BONUS_NAME)

#Remake
remake: cleaner all
	
directories:
	mkdir -p $(TARGETDIR)
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR_BONUS)
	mkdir -p $(BUILDDIR_COMMONS)

#Clean only Objecst
clean:
	$(RM) -rf $(BUILDDIR)
	$(RM) -rf $(BUILDDIR_BONUS)
	$(RM) -rf $(BUILDDIR_COMMONS)
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(LIBFT_DIR)/$(LIBFT_FILE)
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	

#Full Clean, Objects and Binaries
cleaner: clean
	$(RM) -rf $(TARGETDIR)
	
fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(LIBFT)
	$(RM) -rf $(TARGETDIR)
	
bonus: $(OBJECTS_BONUS) $(BONUS_NAME) 

#Link
$(NAME): $(OBJECTS) 
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGETDIR)/$(NAME) $^ $(LIBFT)

$(BONUS_NAME): $(OBJECTS_BONUS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(TARGETDIR)/$(BONUS_NAME) $^ $(LIBFT)	

$(BUILDDIR_COMMONS)/%.$(OBJEXT): $(COMMONSDIR)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCDEP) -c -o $@ $<

$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCDEP) -c -o $@ $<

$(BUILDDIR_BONUS)/%.$(OBJEXT): $(BONUSDIR)/%.$(SRCEXT)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCDEP) -c -o $@ $<


.PHONY: bonus all remake clean cleaner resources