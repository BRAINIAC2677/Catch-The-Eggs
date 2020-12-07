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


//colors
rgb sky_blue = {90, 219, 255};
rgb grass_green = {0, 200, 0};
rgb red = {208, 0, 0};


//clouds initialization
cloud cld_one = {450, 500, 450,610, 1, "images/cloud.bmp"};
cloud cld_two = {650, 700, 650,570, 1, "images/cloud.bmp"};
cloud cld_three = {1050, 1100, 1050,610, 1, "images/cloud.bmp"};

//global variables
int basket_X = 780, basket_Y = 100, basket_no = 0; 
int game_rectX = 400, game_rectY = 50;
int right_buttonX = 340, right_buttonY = 50;
int left_buttonX = 280, left_buttonY = 52;

int basket_len[2] = {125, 180};
char* baskets[2] = {"images/basket1.bmp", "images/basket2.bmp"};

//function prototypes
void CloudAnimation(cloud* c);
void BasketMove(int flag);
void RightShift(int mx, int my);
void LeftShift(int mx, int my);

void GamePage()
{
    iShowBMP(0, 0, "images/sky_bg.bmp");
	
	iSetColor(sky_blue.r, sky_blue.g, sky_blue.b); //game_sec
	iFilledRectangle(game_rectX, game_rectY, 1100, 720);

	iSetColor(grass_green.r, grass_green.g, grass_green.b);
	iFilledRectangle(game_rectX, game_rectY, 1100, 50);

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

void RightShift(int mx, int my)
{
    if(mx >= right_buttonX && mx <= right_buttonX + 50 && my >= right_buttonY && my <= right_buttonY + 50)
        BasketMove(1);
}

void LeftShift(int mx, int my)
{
    if(mx >= left_buttonX && mx <= left_buttonX + 50 && my >= left_buttonY && my <= left_buttonY + 50)
        BasketMove(-1);
}

#endif // FF_H_INCLUDED