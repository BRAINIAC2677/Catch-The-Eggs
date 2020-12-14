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
    Vector position, dimension, speed;
    double boundary_X;
    int show, color;
    char* filename;
    int egg_lay[50], next_egg;
} chicken;

typedef struct 
{
    Vector origin, co_ordinate, dimension, velocity;
    int color, flock_no;
}projectile;


typedef struct 
{
    Vector origin, dimension;
    chicken white, blue, golden;
} flock;


typedef struct 
{
    Vector dimension;
    char* filename;
}basket;



//global variables
Vector game_origin = {400, 50}, game_dimension = {1100, 720};
int ground_height = 50;
Vector basket_origin = AddVector(game_origin, {game_dimension.x/2, ground_height}), basket_speed = {12, 0};
int basket_no = 0;  
Vector right_button_origin = SubVector(game_origin, {60, 0});
Vector left_button_origin = SubVector(game_origin, {120, -2});
int scoreboard_X = 70, scoreboard_Y = 400, scoreboard_dx = 300, scoreboard_dy = 370;
int score = 0,target_score = 300;
int white_egg_cnt = 0, blue_egg_cnt = 0, golden_egg_cnt = 0;
int white_egg_point = 5, blue_egg_point = 10, golden_egg_point = 15;
int stopwatch_min = 0, stopwatch_sec = 0, stopwatch_end_min = 1, stopwatch_end_sec = 0;
Vector net_accleration = {0, -.1};

/* int basket_len[2] = {125, 180};
char* baskets[2] = {"images/basket1.bmp", "images/basket2.bmp"}; */

projectile floating_eggs[100];
int floating_eggs_size = 0, floating_eggs_front = 0;

//colors
rgb black = {50, 48, 49};
rgb white = {255, 255, 255};
rgb white2 = {248, 249, 250};
rgb sky_blue = {90, 219, 255};
rgb grass_green = {0, 200, 0};
rgb turquoise = {2, 195, 154};
rgb red1 = {255, 0, 0};
rgb red2 = {203, 1, 1};
rgb red3 = {153, 6, 17};
rgb blue1 = {10, 133, 237};
rgb blue2 = {12, 99, 231};
rgb blue3 = {13, 65, 225};
rgb violet1 = {114, 9, 183};
rgb violet2 = {86, 11, 173};
rgb violet3 = {72, 12, 168};
rgb brown = {255, 182, 0};



//clouds initialization
cloud cld_one = {450, 500, 450,game_origin.y + 610, 1, "images/cloud.bmp"};
cloud cld_two = {650, 700, 650,game_origin.y + 560, 1, "images/cloud.bmp"};
cloud cld_three = {1050, 1100, 1050,game_origin.y + 610, 1, "images/cloud.bmp"};


//chicken initialization
chicken white_chick = {{game_origin.x + 100, -1}, {84, 91}, {chicken_speed[0], 0}, game_origin.x + 800,show_chicken[0], 0, "images/chicken-white.bmp"};
chicken blue_chick = {{game_origin.x + 550, -1}, {74, 107}, {-1*chicken_speed[1],0}, game_origin.x + 300, show_chicken[1], 1, "images/chicken-blue.bmp"};
chicken golden_chick = {{game_origin.x + 1000, -1}, {59, 94}, {-1*chicken_speed[2],0}, game_origin.x + 300, show_chicken[2], 2, "images/chicken-golden.bmp"};

//flock initialization
flock flock_arr[] = {{AddVector(game_origin, {0, 500}),{game_dimension.x, 3},white_chick, blue_chick, golden_chick},
{AddVector(game_origin, {0, 400}), {game_dimension.x, 3}, white_chick, blue_chick, golden_chick}};
int flock_arr_size = 2;

//basket initialization
basket basket_arr[] = {{{115, 60},"images/basket10.bmp"},
{{180, 161}, "images/basket11.bmp"}};

//function prototypes
void CloudAnimation(cloud* c);
void BasketMove(int flag);
void BasketDraw(basket jhuri);
void RightShift(int mx, int my);
void LeftShift(int mx, int my);
void ChickenDraw(chicken* chick);
void FlockDraw(flock* fk);
void GenerateRandom(int arr[], int start, int end, int no_of_rand);
void ChangeColor(rgb color);
void ScoreBoardDraw();
void StopwatchUpdate();
void PopFrontEgg(projectile arr[], int* size);
void FloatingEggDraw();
int ProjectileDraw(projectile* dim);
int FallingObjectUpdate(projectile* obj);


int ck = 1; //test

void GamePage()
{
    iShowBMP(0, 0, "images/sky_bg.bmp");
    if(ck)
    {
        ck = 0;
        for(int j = 0; j < 2; j++)
        {
            GenerateRandom(flock_arr[j].white.egg_lay, 0, 59, 30);
            GenerateRandom(flock_arr[j].blue.egg_lay, 0, 59, 30);
            GenerateRandom(flock_arr[j].golden.egg_lay, 0, 59, 30);
        }
    }//testing purpose


	ChangeColor(sky_blue); //game_sec
	iFilledRectangle(game_origin.x,game_origin.y, game_dimension.x, game_dimension.y);

	ChangeColor(grass_green);
	iFilledRectangle(game_origin.x,game_origin.y, game_dimension.x, ground_height);

	BasketDraw(basket_arr[basket_no]);

    iShowBMP2(left_button_origin.x, left_button_origin.y, "images/left-arrow.bmp", 0xFFFFFF);
    iShowBMP2(right_button_origin.x, right_button_origin.y, "images/right-arrow.bmp", 0xFFFFFF);

    ScoreBoardDraw();
	 
    //animated clouds
	iShowBMP2(cld_one.x ,cld_one.y, cld_one.filename, 0);
	CloudAnimation(&cld_one);

	iShowBMP2(cld_two.x ,cld_two.y, cld_two.filename, 0);
	CloudAnimation(&cld_two);

	iShowBMP2(cld_three.x ,cld_three.y, cld_three.filename, 0);
	CloudAnimation(&cld_three);
    //end of animated clouds

    FloatingEggDraw();

    for(int i = 0;i< 2; i++)
    {
        flock_arr[i].white.position.y = flock_arr[i].blue.position.y = flock_arr[i].golden.position.y = flock_arr[i].origin.y;
        FlockDraw(&flock_arr[i]);
    }
 

}

void CloudAnimation(cloud *c)
{
	c->x += c->dx;
	if(c->x == c->end_X || c->x == c->start_X)
		c->dx *= -1;
}

void BasketMove(int flag)
{
    if(flag == 1)
    {
        basket_origin = AddVector(basket_origin, basket_speed);
        int end_offset = basket_arr[basket_no].dimension.x;
        if(basket_origin.x > game_origin.x + game_dimension.x - end_offset)
            basket_origin.x = game_origin.x + game_dimension.x - end_offset;
    }

    else
    {
        basket_origin = SubVector(basket_origin, basket_speed);
        if(basket_origin.x < game_origin.x)
            basket_origin.x = game_origin.x;
    }
}

void BasketDraw(basket jhuri)
{
    iShowBMP2(basket_origin.x, basket_origin.y, jhuri.filename, 0xFFFFFF);
}

//basket rightshift
void RightShift(int mx, int my)
{
    if(mx >= right_button_origin.x && mx <= right_button_origin.x + 50 && my >= right_button_origin.y && my <= right_button_origin.y + 50)
        BasketMove(1);
}

//basket leftshift
void LeftShift(int mx, int my)
{
    if(mx >= left_button_origin.x && mx <= left_button_origin.x + 50 && my >= left_button_origin.y && my <= left_button_origin.y + 50)
        BasketMove(-1);
}

void ChickenDraw(chicken* chick)
{
    if(!chick->show)
        return;
    iShowBMP2(chick->position.x, chick->position.y, chick->filename, 0XFFFFFF);

    //motion update
    chick->position.x += chick->speed.x;
    if(chick->speed.x > 0)
    {
        if(chick->position.x > chick->boundary_X)
            chick->position.x = chick->boundary_X;
    }
    else
    {
        if(chick->position.x < chick->boundary_X)
            chick->position.x = chick->boundary_X;
    }
    
    if(chick->position.x == chick->boundary_X)
    { 
        chick->boundary_X = game_origin.x + (int)rand()%(int)(game_dimension.x - chick->dimension.x);
        if(chick->position.x < chick->boundary_X)
            chick->speed.x = fabs(chick->speed.x);
        else
            chick->speed.x = -fabs(chick->speed.x);
        
    }

}

void FlockDraw(flock* fk)
{
    iSetColor(0, 0, 0);
    iFilledRectangle(fk->origin.x, fk->origin.y, fk->dimension.x, fk->dimension.y);

    ChickenDraw(&fk->white);
    ChickenDraw(&fk->blue);
    ChickenDraw(&fk->golden);
}

void GenerateRandom(int arr[], int start, int end, int no_of_rand)
{
    arr[no_of_rand] = -1; //indicate the end of the eggs

    int check_duplicate[end-start+10] = {0};
    for(int i = 0; i< no_of_rand; i++)
    {
        int random = (int)rand()%(end - start+1);
        while(check_duplicate[random])
            random = (int)rand()%(end - start+1);

        check_duplicate[random] = 1;
        arr[i] = start + random;
    }

    for(int pos = no_of_rand - 1; pos; pos--)
    {
        int maxi_ind = 0;
        for(int j = 0; j <= pos; j++)
            if(arr[j] > arr[maxi_ind])
                maxi_ind = j;
        
        int temp = arr[maxi_ind];
        arr[maxi_ind] = arr[pos];
        arr[pos] = temp;
    }

}

void ChangeColor(rgb color)
{
    iSetColor(color.r, color.g, color.b);
}


void ScoreBoardDraw()
{
    ChangeColor(black);
    iFilledRectangle(scoreboard_X, scoreboard_Y, scoreboard_dx, scoreboard_dy);

    int low_cell = 110, mid_cell = 210,high_cell = 300, horizontal_padding = 20, vertical_padding = 30;
    
    ChangeColor(red1);
    iLine(scoreboard_X + horizontal_padding, scoreboard_Y + low_cell, scoreboard_X + scoreboard_dx - horizontal_padding, scoreboard_Y + low_cell);
    iLine(scoreboard_X + horizontal_padding, scoreboard_Y + mid_cell, scoreboard_X + scoreboard_dx - horizontal_padding, scoreboard_Y + mid_cell);
    iLine(scoreboard_X + horizontal_padding, scoreboard_Y + high_cell, scoreboard_X + scoreboard_dx - horizontal_padding, scoreboard_Y + high_cell);
    
    ChangeColor(turquoise);
    iText(scoreboard_X + horizontal_padding, scoreboard_Y + high_cell + vertical_padding, "SCORE-BOARD", GLUT_BITMAP_TIMES_ROMAN_24);

    ChangeColor(red1);
    char score_str[20], target_score_str[20];
    sprintf(score_str, "SCORE: %d", score);
    sprintf(target_score_str, "TARGET: %d", target_score);
    iText(scoreboard_X + horizontal_padding, scoreboard_Y + high_cell - vertical_padding, score_str, GLUT_BITMAP_HELVETICA_18);
    iText(scoreboard_X + horizontal_padding, scoreboard_Y + high_cell - 2*vertical_padding, target_score_str, GLUT_BITMAP_HELVETICA_18);
    
    char stopwatch_str[20];
    sprintf(stopwatch_str, "TIME: %02d : %02d", stopwatch_min, stopwatch_sec);
    iText(scoreboard_X + horizontal_padding, scoreboard_Y + low_cell - vertical_padding, stopwatch_str, GLUT_BITMAP_HELVETICA_18);

    iText(scoreboard_X + horizontal_padding, scoreboard_Y + mid_cell - vertical_padding, "WHITE        BLUE      GOLDEN", GLUT_BITMAP_HELVETICA_18);
    char egg_cnt_str[50];
    sprintf(egg_cnt_str, "     %d            %d            %d", white_egg_cnt, blue_egg_cnt, golden_egg_cnt);
    iText(scoreboard_X + horizontal_padding, scoreboard_Y + mid_cell - vertical_padding - 35, egg_cnt_str, GLUT_BITMAP_TIMES_ROMAN_24);
}

void StopwatchUpdate()
{
/*     if(!stopwatch_min && !stopwatch_sec)
    {
        //game over code
        return;
    }

    if(stopwatch_sec)
        stopwatch_sec--;
    else
    {
        stopwatch_min--;
        stopwatch_sec = 59;    
    } */

    if(stopwatch_min == stopwatch_end_min && stopwatch_sec == stopwatch_end_sec)
    {
        //game over code
        return;
    }

    stopwatch_sec++;
    if(stopwatch_sec == 60)
    {
        stopwatch_sec = 0;
        stopwatch_min++;
    }

    //adding eggs laid by the chickens
    int time_in_sec = stopwatch_min*60 + stopwatch_sec;

    for(int i = 0; i < flock_arr_size; i++)
    {

        if(flock_arr[i].white.egg_lay[flock_arr[i].white.next_egg] == time_in_sec)
        {
            flock_arr[i].white.next_egg++;
            floating_eggs[floating_eggs_size++] = {.origin = AddVector(flock_arr[i].white.position, {flock_arr[i].white.dimension.x/2, 0}),.co_ordinate = AddVector(flock_arr[i].white.position, {flock_arr[i].white.dimension.x/2, 0}),.dimension = {5.0, 10.0},.velocity = flock_arr[i].white.speed,.color = flock_arr[i].white.color};            
        }


        if(flock_arr[i].blue.egg_lay[flock_arr[i].blue.next_egg] == time_in_sec)
        {
            flock_arr[i].blue.next_egg++;
            floating_eggs[floating_eggs_size++] = {.origin = AddVector(flock_arr[i].blue.position, {flock_arr[i].blue.dimension.x/2, 0}),.co_ordinate = AddVector(flock_arr[i].blue.position, {flock_arr[i].blue.dimension.x/2, 0}),.dimension = {5.0, 10.0},.velocity = flock_arr[i].blue.speed,.color = flock_arr[i].blue.color};            
        }

        if(flock_arr[i].golden.egg_lay[flock_arr[i].golden.next_egg] == time_in_sec)
        {
            flock_arr[i].golden.next_egg++;
            floating_eggs[floating_eggs_size++] = {.origin = AddVector(flock_arr[i].golden.position, {flock_arr[i].golden.dimension.x/2, 0}),.co_ordinate = AddVector(flock_arr[i].golden.position, {flock_arr[i].golden.dimension.x/2, 0}),.dimension = {5.0, 10.0},.velocity = flock_arr[i].golden.speed,.color = flock_arr[i].golden.color};
        }
    }
}

void PopFrontEgg(projectile arr[], int* size, int ind)
{
    if(size == 0)
        return;
    
    for(int i = ind+1; i < *size; i++)
        arr[i-1] = arr[i];
    
    (*size)--;
}

void FloatingEggDraw()
{
    int rmv[50], next = 0;

    for(int i = 0; i< floating_eggs_size; i++)
    {
        if(ProjectileDraw(&floating_eggs[i]))
        {
            rmv[next++] = i;
        }
    }

    //sorting rmv
    for(int i = 0; i< next-1; i++)
    {
        int mini_ind = i;
        for(int j = i+1; j < next; j++)
            if(rmv[j] < rmv[mini_ind])
                mini_ind = j;

        int temp = rmv[i];
        rmv[i] = rmv[mini_ind];
        rmv[mini_ind] = temp;
    }
    
    for(int i = 0;i< next; i++)
        PopFrontEgg(floating_eggs, &floating_eggs_size, rmv[i] - i);
    
    /* floating_eggs_front += rmv; */
/*     dbg(floating_eggs_front);
    dbg(floating_eggs_size); */
}

int ProjectileDraw(projectile* obj)
{
    int res = 0;

    if(obj->color < 3)
    {
        ChangeColor(black);
        iFilledEllipse(obj->co_ordinate.x, obj->co_ordinate.y, obj->dimension.x+1, obj->dimension.y+1);
        
        if(obj->color == 0)
            ChangeColor(white);
        else if(obj->color==1)
            ChangeColor(blue1);
        else
            ChangeColor(brown);

        iFilledEllipse(obj->co_ordinate.x, obj->co_ordinate.y, obj->dimension.x, obj->dimension.y);
        res = FallingObjectUpdate(obj);
    }
    else
    {
        //other projectile
    }
    
    
    return res;
}

int FallingObjectUpdate(projectile* obj)
{
    double prev_Y = obj->co_ordinate.y;
    obj->velocity = AddVector(obj->velocity, net_accleration);
    obj->co_ordinate = AddVector(obj->co_ordinate, obj->velocity);


    int ret = 0;
   /*  obj->origin = AddVector(obj->origin, obj->co_ordinate); */
    if(obj->co_ordinate.x >= basket_origin.x && obj->co_ordinate.x <= basket_origin.x + basket_arr[basket_no].dimension.x && prev_Y >= basket_origin.y + basket_arr[basket_no].dimension.y && obj->co_ordinate.y <= basket_origin.y + basket_arr[basket_no].dimension.y)
    {
        ret = 1;
        if(obj->color == 0)
            white_egg_cnt++;
        else if(obj->color == 1)
            blue_egg_cnt++;
        else if(obj->color == 2)
            golden_egg_cnt++;
        score = white_egg_cnt*white_egg_point + blue_egg_cnt*blue_egg_point + golden_egg_cnt*golden_egg_point;
    }
    else if(obj->co_ordinate.y <= game_origin.y + ground_height)
    {
        ret = 1;
    }
    else if(obj->co_ordinate.x <= game_origin.x || obj->co_ordinate.x >= game_origin.x + game_dimension.x)
        obj->velocity.x*= -1;

    return ret;
}






#endif // FF_H_INCLUDED