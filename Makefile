name = res

option = -Iincludes

cc = gcc

files = src/*.c

src = $(wildcard src/*.c)

obj = $(addsuffix .o, $(basename $(notdir $(src))))

all = $(name)

$(name): $(obj)
	make -C libft/
	make -C mlx_mac/
	cp libft/libft.h ./includes/	
	cp libft/libft.a ./
	$(cc) -o $(name) $(option) $^ libmlx_Linux.a libft.a -lXext -lX11 -lm -lz 

#$(cc) $(option) -o $(name) $(src) -L. -lft

%.o:  src/%.c
	$(cc) $(option) -O3 -c $< -o $@

clean:
	make clean -C libft
	rm -rf $(obj)

fclean: clean
	make fclean -C libft
	rm -rf $(name)

re: fclean $(name)
