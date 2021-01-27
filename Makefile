name = res

option = -I includes/

cc = gcc

src = $(wildcard *.c)

obj = $(addsuffix .o, $(basename $(notdir $(src))))

all = $(name)

$name): $(obj)
	make -C libft/
	make -C mlx_linux/
	cp libft/libft.h ./includes/	
	cp libft/libft.a ./
	$(cc) -o $(name) $(option) $< libmlx_Linux.a -lXext -lX11 -lm -lz 

#$(cc) $(option) -o $(name) $(src) -L. -lft

%.o: %.c
	$(cc) $(option) -O3 -c $< -o $@	

clean:
	make clean -C libft
	rm -rf $(obj)

fclean: clean
	make fclean -C libft
	rm -rf $(name)

re: fclean $(name)
