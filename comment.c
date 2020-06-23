##################################INCLUDE#######################################

/*
**###########_RAYCASTING_#################
*/

typedef struct	s_rting
{
	double	posx; //position du joueur en X
	double	posy; //position du joueur en Y
	double	dirx; //direction du joueur vers X
	double	diry; //direction du joueur vers Y
	double	planecamx; //plan de la camera en x
	double	planecamy; //plan de la camera en y
	double	time; //l'heure actuelle de l'image;
	double	oldtime; //l'heure de l'image precedente
	double	camerax; //coordonnees de la camera sur x
	double	raydirx; //direction du rayon sur X
	double	raydiry; //direction du rayon sur Y
	double	distx; /*distance que le rayon doit parcourir de sa position de depart au premier
						cote de x*/
	double	disty; /*distance que le rayon doit parcourir de sa position de depart au premier
						cote de y*/
	double	deltadistx; //distance que le rayon doit parcourir du cote x au suivant deltaDistX
	double	deltadisty; //distance que le rayon doit parcourir du cote y au suivant deltaDistY
	double	perpwalldist; //calculer la taille du rayon perpwalldist
	int		mapx; /*carre actuel ou se trouve le rayon sur x (le carre mais aussi ou on est
					dans le carre*/
	int		mapy; /*carre actuel ou se trouve le rayon sur y (le carre mais aussi ou on est
					dans le carre*/
	int		stepx; //stocker si le deplacement de x est de -1 (gauche) ou +1 (droite) stepX
	int		stepy; //stocker si le deplacement de x est de -1 (haut) ou +1 (bas) stepY
	int		hit; //0 si un mur n'a pas ete touche, 1 si un mur a ete touche
	int		side; //le mur touche est-il au nord, sud, ouest ou a l'est
	int		mv_update;
	char	pad[4]

###############################LOOK UTILS MOOVE#################################

cos = deplacements en x / sin = deplacements en y

#################################RAYCASTING#####################################

gr->rting.camerax = 2 * x / (double)map->recup.resolution[AXE_X] - 1;
//si 1 = droite / 0 = centre / -1 = gauche
//correspond que l'on voit, se deplace de gauche a droite en fonction de x*/

gr->rting.deltadistx = 	gr->rting.raydirx == 0 ? 1.0 : fabs(1 / gr->rting.raydirx);
gr->rting.deltadisty = 	gr->rting.raydiry == 0 ? 1.0 : fabs(1 / gr->rting.raydiry);
/*distance que le rayon doit parcourir du cote x/y au suivant*/

static void	init_step_distray(t_graph *gr)
{
	if (gr->rting.raydirx < 0) //si le rayon est a gauche
	{	
		gr->rting.stepx = -1; //on se decale a gauche
		gr->rting.distx = (gr->rting.posx - gr->rting.mapx)
							* gr->rting.deltadistx;
		/*si la direction du rayon est negative (gauche),
		  distx (distance du rayon entre sa position et le cote x du carre)
		  sera le premier cote a gauche*/
	}
	else
	{
		gr->rting.stepx = 1; //on se decale a droite
		gr->rting.distx = (gr->rting.mapx + 1.0 - gr->rting.posx)
							* gr->rting.deltadistx;
		/*si la direction du rayon est positive (droite),
		  distx (distance du rayon entre sa position et le cote x du carre)
		  sera le premier cote a droite*/
	}
	if (gr->rting.raydiry < 0)
	{
		gr->rting.stepy = -1; //on se decale en haut
		gr->rting.disty = (gr->rting.posy - gr->rting.mapy)
							* gr->rting.deltadisty;
		/*si la direction du rayon est negative (monte),
		  disty (distance du rayon entre sa position et le cote y du carre)
		  sera le premier cote en haut*/
	}
	else
	{
		gr->rting.stepy = 1; //on se decale en bas
		gr->rting.disty = (gr->rting.mapy + 1.0 - gr->rting.posy)
							* gr->rting.deltadisty;
		/*si la direction du rayon est positive (descend),
		  disty (distance du rayon entre sa position et le cote y du carre)
		  sera le premier cote en bas*/
	}
}

if (gr->rting.distx < gr->rting.disty)
{
	gr->rting.distx += gr->rting.deltadistx; /*on ajoute la distance du
	rayon a la distance du prochain rayon*/
	gr->rting.mapx += gr->rting.stepx; /*on ajoute au carre actuel ou
	se trouve le rayon sur x et on y ajoute step (si on se deplace a
	gauche ou a droite)*/
	gr->rting.side = gr->rting.stepx == 1 ? EA : WE;
}

static void	calcul_draw(t_map *map, t_graph *gr)
{
	gr->draw.height_line = (int)(map->recup.resolution[AXE_Y]
			/ gr->rting.perpwalldist); /*la hauteur du mur == resolution sur y
	divise par la distance du rayon*/
	gr->draw.start = -gr->draw.height_line / 2
							+ map->recup.resolution[AXE_Y] / 2;
	/*le debut des pixels == la negative de la hauteur du mur / 2 + la
	resolution sur Y / 2*/
	if (gr->draw.start < 0)
		gr->draw.start = 0;
	gr->draw.end = gr->draw.height_line / 2
							+ map->recup.resolution[AXE_Y] / 2;
	//le fin des pixels == la hauteur du mur / 2 + la resolution sur Y / 2
	if (gr->draw.end >= map->recup.resolution[AXE_Y])
		gr->draw.end = map->recup.resolution[AXE_Y] - 1;
	else if (gr->draw.end < 0)
		gr->draw.end = 0;
}
		
if (gr->rting.side == EA || gr->rting.side == WE)
{
	gr->rting.perpwalldist = (gr->rting.mapx - gr->rting.posx
			+ (1 - gr->rting.stepx) / 2) / gr->rting.raydirx;
	/*si un cote X est atteind, perpwalldist = nombre de carres que
	  le rayon a traverse dans la direction de X*/
}
else
{

	gr->rting.perpwalldist = (gr->rting.mapy - gr->rting.posy
			+ (1 - gr->rting.stepy) / 2) / gr->rting.raydiry;
	/*si un cote Y est atteind, perpwalldist = nombre de carres que
	 le rayon a traverse dans la direction de Y*/
}

#################################SAVE_MODE######################################
	
/*la boucle se fait a l'envers pour pas que le bmp soit affiche a l'envers 
	en little indian*/
	
pad = (PIXOFFSET - ((int)map->recup.resolution[AXE_X] * 3) % PIXOFFSET) % 4;
	//permet d'alligner en memoire
	
filesize = HEADERSIZE + (OCTET3 * ((int)map->recup.resolution[AXE_X]
					+ pad) * (int)map->recup.resolution[AXE_Y]);
	/*taille du headersize + AXE_X * AXE_Y // on a 24 bits (3 octets) par pixel,
	il se peut que la somme des pixels d'une ligne ne soit pas un multiple de 4.
	Dans ce cas, on rajoute a la fin de la ligne, entre 0 et 3 octets bidons
	pour assurer que la ligne est un multiple de 4 octets*/

####################################SPRITE######################################

distx = ft_lfpow(gr->rting.posx - gr->sp.pos[i].x, POW_2);
disty = ft_lfpow(gr->rting.posy - gr->sp.pos[i].y, POW_2);
		/*pour trouver la distance entre la position actuelle et la position
		du sprite il faut faire la position - la position du sprite
		pow 2 car on est sur 2 axes (x et y)*/

static void	calcpos_sprite(t_graph *gr, size_t i, t_map *map)
{	
	gr->sp.x = gr->sp.pos[i].x - gr->rting.posx;
	gr->sp.y = gr->sp.pos[i].y - gr->rting.posy;
	//position en x et en y par rapport au personnage
	gr->sp.rot = 1.0 / (gr->rting.planecamx * gr->rting.diry - gr->rting.dirx
						* gr->rting.planecamy);
	//permet de faire la rotation/inverstion en fonction du deplacement
	gr->sp.playposx = gr->sp.rot * (gr->rting.diry * gr->sp.x - gr->rting.dirx
						* gr->sp.y);
	/*position du jour sur x par rapport au sprite
	->negt = a gauche du sprite donc joueur a droite
	->post = a droite du sprite donc joueur a gauche*/
	gr->sp.playposy = gr->sp.rot * (-gr->rting.planecamy * gr->sp.x
						+ gr->rting.planecamx * gr->sp.y);
	/*position du jour sur y par rapport au sprite
	->negt = en haut du sprite
	->post = en bas du sprite*/
	gr->sp.screen_where = ((map->recup.resolution[AXE_X] / 2)
						* (1 + gr->sp.playposx / gr->sp.playposy));
	/*permet de savoir vers quel direction on regarde, valeurs changent en
	fonction de quel mur on regarde/quel combinaison de mur on regarde
	-> des qu'on regarde le NORD/SUD valeur positive
	-> ouest = premiere moitie negative / deuxieme positive
	-> est = premiere moitie positive / deuxieme negative
	= plus on va vers l'ouest, plus la valeur augmente
	= plus on va vers l'est, plus la valeur diminue*/
}

#################################SPRITE DRAW####################################
		
while (tmp_starty < gr->sp.endy)
{
	dim = tmp_starty * PIXEL - map->recup.resolution[AXE_Y]
			* PIXEL_DIV2 + gr->sp.height * PIXEL_DIV2;
	/*permet d'avoir la dimension de la texture
	-> 1er mult = largeur en pixel du sprite
	-> 2eme mult = quel pixel position moitie ecran
	-> 3eme mult = hauteur en pixel du sprite
	== largeur - position moitie ecran + hauteur*/
	gr->sp.texty = ((dim * gr->text.size[S][HEIGHT] / gr->sp.height)
						/ PIXEL);
	/*permet de de savoir sur quel pixel sur Y on se situe
	(dimension du pixel * taille de l'image du pixel / hauteur du sprite
	reel / 256 (nombre de pixel))*/
	colorisation_sprite(gr, tmp_starty, startx, map);
	tmp_starty++;	
}

void	calcdraw_sprite(t_graph *gr, t_map *map)
{
	gr->sp.height = abs((long)(map->recup.resolution[AXE_Y] / gr->sp.playposy));
	/*permet d'avoir la hauteur du sprite selon la hauteur de l'ecran et surtout
	la position du player par rapport au sprite pour avoir de la perspective*/
	gr->sp.starty = -gr->sp.height / 2 + map->recup.resolution[AXE_Y] / 2;
	if (gr->sp.starty < 0)
		gr->sp.starty = 0;
	gr->sp.endy = gr->sp.height / 2 + map->recup.resolution[AXE_Y] / 2;
	if (gr->sp.endy >= map->recup.resolution[AXE_Y])
		gr->sp.endy	= map->recup.resolution[AXE_Y] - 1;
	gr->sp.width = abs((int)(map->recup.resolution[AXE_Y] / gr->sp.playposy));
	/*permet de savoir combien de pixel du point le plus a gauche d'au plus a
	droite il y a*/
	gr->sp.startx = -gr->sp.width / 2 + gr->sp.screen_where;
	if (gr->sp.startx < 0)
		gr->sp.startx = 0;
	gr->sp.endx = gr->sp.width / 2 + gr->sp.screen_where;
	if (gr->sp.endx >= map->recup.resolution[AXE_X])
			gr->sp.endx = map->recup.resolution[AXE_X];	
