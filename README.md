# Cub3d
Resources:
 -> https://www.desmos.com/calculator
 -> https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
 -> pikuma drive
*m    **************

-> make a good modular makefile + add the gnl libft and mlx42 librarie 
-> read documentation of mlx42 and make prototypes to see how things work
-> ask about the difference between mlx42 and mlx

> it's really important to have good "reperage" meaning know what left right top and down means in the context of your program's map  

-> start by making a 2d map and try to fix collisions and ray casting  
-> raise walls with distinct color   s for each side to make things easy at the start
-> let textures be the very last thing you add

# things to note

-> watch pikuma videos
-> reviser les relations de : tan / cos / sin
-> les limites de tan a gauche et a droite de pi/2(use desmos.com)

# DDA ALGORITHM

1- you have the current point location (x1, y1)
2- you take the other point head of the line location (x2, y2)
3- we applicate on the both points the diff operation x's with the x's and the y's with the other
4- so we have *diff_x*  = (x2 - x1), and *diff_y* =(y2 - y1) 
5- to know the *steps* we take the greater from the diffs 
6 -  the steps we use them in this operation to know how we should be increment with
7 - so we do :  X_increment = diff_x / steps
8 - and  we do :  Y_increment = diff_y / steps
9 - so know we have to increment with the locations and round the values of the locations (if (0.5 < the number it takes the greater))
10 - congrats you have the line 