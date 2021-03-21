#include "cub3d.h"

int		create_spr_tabl(t_all *all)
{
	int x;
	int y;
	int i;

	all->sprite = ft_calloc(sizeof(t_sprite), (all->spr.num_spr));
	y = all->brd.map_row;        
	i = 0;
    while (all->map[y])          
    {                            
        x = 0;                    
        while (all->map[y][x])    
        {                        
            if (all->map[y][x] == '2')    
			{
				all->sprite[i].x = (double)x + 0.5;
				all->sprite[i].y = (double)y + 0.5;
				i++;
			}
            x++;    
        }    
        y++;    
    } 
	return (1);
}

void    count_sprites(t_all *all)    
{                                
    int x;                       
    int y;                       
                                 
    all->spr.num_spr = 0;        
    y = all->brd.map_row;        
	printf("inside count_sprites\n");
    while (all->map[y])          
    {                            
        x = 0;                    
        while (all->map[y][x])    
        {                        
            if (all->map[y][x] == '2')    
                all->spr.num_spr++;    
            x++;    
        }    
        y++;    
    }    
}
