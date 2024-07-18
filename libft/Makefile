# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 13:00:58 by mstracke          #+#    #+#              #
#    Updated: 2023/11/13 15:09:34 by mstracke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#here are the declarations
CUR_DIR = $(shell pwd)

NAME = libft.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

CPPFLAGS =

#to define BUFFER_SIZE for get_next_line
#BUFFER = -D BUFFER_SIZE=3

#to create a program for testing reasons
#PROGRAM = test

HEADERS = libft.h ft_printf/ft_printf.h get_next_line/get_next_line.h

SRCS =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_bzero.c \
		ft_memset.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_memcmp.c \
		ft_memmove.c \
		ft_strnstr.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_atoi.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		$(CUR_DIR)/ft_printf/ft_printf.c \
		$(CUR_DIR)/ft_printf/ft_printint.c \
		$(CUR_DIR)/ft_printf/ft_printui_recursive.c \
		$(CUR_DIR)/ft_printf/ft_printhexa_recursive.c \
		$(CUR_DIR)/ft_printf/ft_printp_recursive.c \
		$(CUR_DIR)/ft_printf/ft_printchar.c \
		$(CUR_DIR)/ft_printf/ft_printstr.c \
		$(CUR_DIR)/get_next_line/get_next_line_bonus.c \
		$(CUR_DIR)/get_next_line/get_next_line_utils_bonus.c 
		
#variable substitution		
OBJS = $(SRCS:.c=.o)
#OBJS := $(SRC:%.c=%.o)

#The %.o: %.c pattern specifies that in order to build something whose file name ends with .o, you need to have a file that has the same prefix but then ends with .c rather than .o.
#%.o rule will compile one .c file to its correspondig object (.o) file
#automatic variables: $@ = the file name of the target of the rule, $< = the name of the prerequisite
#without this rule it would not update correctly
%.o: %.c
#	$(CC) $(CFLAGS) -o $@ -c $<
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ -c $<

# here the rules start

#to create a program: (DELETE FOR MOULINETTE)
#all: $(PROGRAM)

#$(PROGRAM): $(NAME)
#	$(CC) $^ $(CFLAGS) -o $@
#	@echo -- prog created, try it by using ./printf

#use of ar -rc or ar -rcs?
# compiles each source into an object file (c-flag); the The -I./ flag ensures that the compiler looks for header files in the current directory when compiling the source files specified in $(SRCS) (The -I. is included so that gcc will look in the current directory (.) for the include file .h ). -r  updates archive (replace or add files) or (c) create if it doesn't exist. -s could be useful for including an index
#ranlib creates and index which improves the efficiency of certain operations, such as quickly looking up symbols within the library.The index is stored in the archive itself.
$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)
	ranlib $(NAME)
	@echo -- Libft compiled, lib created / updated

#This target depends on $(NAME), making it the default target to build everything.
all: $(NAME)

#clean: This target removes the object files ($(OFILES)).
#use rm -rf or rm -f? 
#r: This option allows rm to remove directories and their contents recursively, not necessary?
#f: "force" -->prevents the command from prompting for confirmation
clean: 
	rm -f $(OBJS)
	@echo -- Deleting all .o-files
	
# fclean: this target depends on clean. Once all object files are deleted, this rule will delete the created executable / the compiled binary ('$(NAME)') 
fclean: clean
	rm -f $(NAME)
#	@rm -f $(PROGRAM)


#This target depends on fclean and all, effectively cleaning and rebuilding the project.
re: fclean all

#This line specifies that the listed targets (all, clean, fclean, re) are phony targets, meaning they don't represent actual files, and should always be considered out-of-date, triggering their recipes to be executed.
.PHONY: all clean fclean re
