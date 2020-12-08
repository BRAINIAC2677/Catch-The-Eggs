#ifndef FF_H_INCLUDED
#define FF_H_INCLUDED


#define dbg(a) cout<<#a<<" ->->->-> "<<a<<"\n"

typedef struct 
{
	double r, g, b;
} rgb;

typedef struct 
{
	double start_X, end_X, x, y, dx;
	char* filename;
} cloud;

typedef struct 
{
    double x, y, dx, dy, boundary_X, speed;
    int show, color;
    char* filename;
} chicken;

typedef struct 
{
    double x, y, dx, dy;
    chicken white, blue, golden;
} flock;

//global variables
int basket_X = 780, basket_Y = 100, basket_no = 0; 
int game_rectX = 400, game_rectY = 50, game_rect_dx = 1100, game_rect_dy = 720;
int right_buttonX = game_rectX - 60, right_buttonY = game_rectY;
int left_buttonX = game_rectX - 120, left_buttonY = game_rectY + 2;

int basket_len[2] = {125, 180};
char* baskets[2] = {"images/basket1.bmp", "images/basket2.bmp"};

//colors
rgb sky_blue = {90, 219, 255};
rgb grass_green = {0, 200, 0};
rgb red = {208, 0, 0};


//clouds initialization
cloud cld_one = {450, 500, 450,game_rectY + 610, 1, "images/cloud.bmp"};
cloud cld_two = {650, 700, 650,game_rectY + 560, 1, "images/cloud.bmp"};
cloud cld_three = {1050, 1100, 1050,game_rectY + 610, 1, "images/cloud.bmp"};


//chicken initialization
chicken white_chick = {game_rectX + 100, -1, 84, 91, game_rectX + 800,chicken_speed[0], show_chicken[0], 0, "images/chicken-white.bmp"};
chicken blue_chick = {game_rectX + 550, -1, 74, 107, game_rectX + 300, chicken_speed[1],show_chicken[1], 1, "images/chicken-blue.bmp"};
chicken golden_chick = {game_rectX + 1000, -1, 59, 94, game_rectX + 300,chicken_speed[2], show_chicken[2], 2, "images/chicken-golden.bmp"};

//flock initialization
flock flock_one = {game_rectX, game_rectY + 500, game_rect_dx, 3, white_chick, blue_chick, golden_chick};
flock flock_two = {game_rectX, game_rectY + 400, game_rect_dx, 3, white_chick, blue_chick, golden_chick};


//function prototypes
void CloudAnimation(cloud* c);
void BasketMove(int flag);
void RightShift(int mx, int my);
void LeftShift(int mx, int my);
void ChickenDraw(chicken* chick);
void FlockDraw(flock* fk);

void GamePage()
{
    iShowBMP(0, 0, "images/sky_bg.bmp");

	
	iSetColor(sky_blue.r, sky_blue.g, sky_blue.b); //game_sec
	iFilledRectangle(game_rectX, game_rectY, game_rect_dx, game_rect_dy);

	iSetColor(grass_green.r, grass_green.g, grass_green.b);
	iFilledRectangle(game_rectX, game_rectY, game_rect_dx, 50);

	iShowBMP2(basket_X, basket_Y, baskets[basket_no], 0xFFFFFF);

    iShowBMP2(left_buttonX, left_buttonY, "images/left-arrow.bmp", 0xFFFFFF);
    iShowBMP2(right_buttonX, right_buttonY, "images/right-arrow.bmp", 0xFFFFFF);

	iSetColor(red.r, red.g, red.b); //info_sec
	iFilledRectangle(50, 400, 300, 370);
	 
    //animated clouds
	iShowBMP2(cld_one.x ,cld_one.y, cld_one.filename, 0);
	CloudAnimation(&cld_one);

	iShowBMP2(cld_two.x ,cld_two.y, cld_two.filename, 0);
	CloudAnimation(&cld_two);

	iShowBMP2(cld_three.x ,cld_three.y, cld_three.filename, 0);
	CloudAnimation(&cld_three);
    //end of animated clouds

    FlockDraw(&flock_one);
    FlockDraw(&flock_two);
}

void CloudAnimation(cloud *c)
{
	c->x += c->dx;
	if(c->x == c->end_X || c->x == c->start_X)
		c->dx *= -1;
}

void BasketMove(int flag)
{
    int basket_speed = 8;
    if(flag == 1)
    {
        basket_X += basket_speed;
        int end_offset = basket_len[basket_no];
        if(basket_X > 1500 - end_offset)
            basket_X = 1500 - end_offset;
    }

    else
    {
        basket_X -= basket_speed;
        if(basket_X < 390)
            basket_X = 390;
    }
}

//basket rightshift
void RightShift(int mx, int my)
{
    if(mx >= right_buttonX && mx <= right_buttonX + 50 && my >= right_buttonY && my <= right_buttonY + 50)
        BasketMove(1);
}

//basket leftshift
void LeftShift(int mx, int my)
{
    if(mx >= left_buttonX && mx <= left_buttonX + 50 && my >= left_buttonY && my <= left_buttonY + 50)
        BasketMove(-1);
}

void ChickenDraw(chicken* chick)
{
    if(!chick->show)
        return;
    iShowBMP2(chick->x, chick->y, chick->filename, 0XFFFFFF);

    //motion update
    if(chick->boundary_X > chick->x)
    {
        chick->x += chick->speed;
        if(chick->x > chick->boundary_X)
            chick->x = chick->boundary_X;
    }
    else if(chick->boundary_X < chick->x)
    {
        chick->x -= chick->speed;
        if(chick->x < chick->boundary_X)
            chick->x = chick->boundary_X;
    }
    else
    { 
        chick->boundary_X = game_rectX + (int)rand()%(int)(game_rect_dx - chick->dx);
    }

}

void FlockDraw(flock* fk)
{
    iSetColor(0, 0, 0);
    iFilledRectangle(fk->x, fk->y, fk->dx, fk->dy);

    fk->white.y = fk->blue.y = fk->golden.y = fk->y;
    ChickenDraw(&fk->white);
    ChickenDraw(&fk->blue);
    ChickenDraw(&fk->golden);
}


#endif // FF_H_INCLUDED