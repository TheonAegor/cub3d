name = cub3D

option = -Iincludes

cc = gcc

files = src/*.c

src = $(wildcard src/*.c)

OBJDIR = obj/

obj = $(addprefix $(OBJDIR),$(addsuffix .o, $(basename $(notdir $(src)))))

all = $(name)

$(name): $(obj)
	@make -C libft/
#	make -C mlx_mac/
#	cp libft/libft.h ./includes/	
	@cp libft/libft.a ./libs
	@$(cc) -o $(name) $(option) $^ libs/libmlx_Linux.a libs/libft.a libs/libftprintf.a -lXext -lX11 -lm -lz 

#$(cc) $(option) -o $(name) $(src) -L. -lft

$(OBJDIR)%.o:  src/%.c
	$(cc) $(option) -O3 -c $< -o $@

clean:
	make clean -C libft
	rm -rf $(obj)

fclean: clean
	make fclean -C libft
	rm -rf $(name)

shot:
	rm -rf *.bmp

re: fclean $(name)
