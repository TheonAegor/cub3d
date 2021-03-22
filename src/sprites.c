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

void sort_sprites(int *so, double *sd, t_all *all)    
{                 
    int i = 0;    
    int j = 0;        
    int tmp_order;      
    double tmp_dist;                        
    t_sprites sprites[all->spr.num_spr];    
                                    
    while (i < all->spr.num_spr)    
    {                                
        sprites[i].first = sd[i];     
        sprites[i].second = so[i];
		i++;            
    }                                       
    while (j < all->spr.num_spr / 2 + 1)    
    {                                       
        i = 0;                              
        while (i < all->spr.num_spr - 1)    
        {                                                   
            if (sprites[i].first < sprites[i + 1].first)    
            {
				tmp_dist = sprites[i].first;
				tmp_order = sprites[i].second;
				sprites[i].first = sprites[i + 1].first;
				sprites[i].second = sprites[i + 1].second;    
				sprites[i + 1].first = tmp_dist;
				sprites[i + 1].second = tmp_order;    
            }                                         
            i++;                                    
        }                                             
        j++;     
    }               
    i = 0;                          
    while (i < all->spr.num_spr)    
    {                                     
        all->sd[i] = sprites[i].first;     
        all->so[i] = sprites[i].second;
        i++;
    }
}  
