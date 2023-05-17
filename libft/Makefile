# Files
NAME = libft.a
Header = libft.h

# Use ls -m *.c | tr -d "," | tr -d "\n" | sed "s/ ft_[a-z_]*_bonus.c//g"
Files = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

# Use ls -m *_bonus.c | tr -d "," | tr -d "\n" 
Bonus_Files =  ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

# Replaces the .c in each file to .o
Files_O = $(Files:.c=.o)
Bonus_Files_O = $(Bonus_Files:.c=.o)

# Compiles every .c file into a .o file, $< referring to the prequisite while $@ the target
%.o: %.c 
	gcc -Wall -Wextra -Werror -c $< -o $@
	
$(NAME): $(Files_O)
	ar rcs $(NAME) $(Files_O)

all: $(NAME)

bonus: $(NAME) $(Bonus_Files_O)
	ar rcs $(NAME) $(Bonus_Files_O)

clean:
	rm -rf $(Files_O) $(Bonus_Files_O)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all bonus clean fclean re

# /////////////////////////////////////////////////////////////

# #files
# NAME = libft.a
# Header = libft.h

# #
# Files = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
# Bonus_Files_O = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

# # Replaces the .c in each file to .o

