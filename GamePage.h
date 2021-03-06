#ifndef FF_H_INCLUDED
#define FF_H_INCLUDED

#define dbg(a) cout << #a << " ->->->-> " << a << "\n"

#define poop_color 3
#define basket_speed_perks_color 4
#define basket_size_perks_color 5
#define extra_time_perks_color 6

typedef struct
{
    double r, g, b;
} rgb;

//x, y are the moving co-ordinates between start_X and end_X with speed dx
typedef struct
{
    double start_X, end_X, x, y, dx;
    char *filename;
} cloud;

typedef struct
{
    Vector position, dimension, speed;
    double boundary_X;
    int show, color;
    char *filename;
    int egg_lay[50], poop_lay[50], next_poop, next_egg, no_of_egg;
} chicken;

typedef struct
{
    Vector origin, co_ordinate, dimension, velocity;
    int color, flock_no;
} projectile;

typedef struct
{
    Vector origin, dimension;
    chicken white, blue, golden;
} flock;

//TODO: Showing different baskets at different levels
typedef struct
{
    Vector dimension;
    char *filename;
} basket;

typedef struct
{
    Vector origin, dimension;
    char *str;
    int active, page_no;
    void (*function_pointer)();
} button;

typedef struct
{
    Vector origin, dimension;
    char *title, *label;
    char input[50];
    int next_input, active, page_no;
} placeholder;

typedef struct
{
    int one, two, three;
} int_tuple;

Vector game_origin = {400, 50}, game_dimension = {1100, 720};
Vector basket_origin = AddVector(game_origin, {game_dimension.x / 2, 0}), basket_speed = {15, 0};
int basket_no = 0; //*for different baskets for different level
int scoreboard_X = 70, scoreboard_Y = 400, scoreboard_dx = 300, scoreboard_dy = 370;
int score = 0, win_score = 300;
int white_egg_cnt = 0, blue_egg_cnt = 0, golden_egg_cnt = 0, poop_cnt = 0;
int white_egg_point = 5, blue_egg_point = 10, golden_egg_point = 20, poop_point = 5;
int stopwatch_current_min = 0, stopwatch_current_sec = 0, stopwatch_end_min = 1, stopwatch_end_sec = 0;
Vector net_accleration = {0, -.101};

Vector home_origin = {500, 0}, home_dimension = {550, screen_height}; //for middle black part in UI pages
int HEL_font_size = 13;
int button_height = 50, button_grid = 70;
int placeholder_height = 30, placeholder_grid = 100;

//functions from homepage
void ButtonDraw(button btn, rgb col);
void LoginPage();
void SignUp();
void PlaceholderDraw(placeholder *pl, rgb col);
void AddProfileInfo();
void LoginInfo();
void GetProfileInfo();
int UsernameMatch(char *user_name);
int PassMatch(char *pass);
void ProfileAccess();
void LevelPage();
void LevelOne();
void LevelTwo();
void LevelThree();
void LevelFour();
void LevelFive();
void Intro();
void LoginPress();
void SignupPress();
void Prompt();
void PromptPress();
void LeaderboardDraw();
void BackPress1();
void LeaderboardPress();
void ExitPress();
void StartPress();
void PausePress();
void ResumePress();
void BackPress2();
void XPress();
void HelpPage();
void HelpPress();
void SettingsPage();
void SettingsPress();
void ProfilePress();
void ProfilePage();
void CancelPress();

//buttons initialization
button button_arr[] = {{AddVector(home_origin, {0, button_grid}), {100, button_height}, "EXIT", .page_no = HomePageNo, .function_pointer = ExitPress},
                       {AddVector(home_origin, {0, 2 * button_grid}), {100, button_height}, "HELP", .page_no = HomePageNo, .function_pointer = HelpPress},
                       {AddVector(home_origin, {0, 3 * button_grid}), {200, button_height}, "SETTINGS", .page_no = HomePageNo, .function_pointer = SettingsPress},
                       {AddVector(home_origin, {0, 4 * button_grid}), {250, button_height}, "LEADERBOARD", .page_no = HomePageNo, .function_pointer = LeaderboardPress},
                       {AddVector(home_origin, {0, 5 * button_grid}), {200, button_height}, "PROFILE", .page_no = HomePageNo, .function_pointer = ProfilePress},
                       {AddVector(home_origin, {0, 6 * button_grid}), {200, button_height}, "START", .page_no = HomePageNo, .function_pointer = StartPress},
                       {AddVector(home_origin, {0, 7 * button_grid}), {200, button_height}, "RESUME", .page_no = HomePageNo, .function_pointer = ResumePress},
                       {AddVector(home_origin, {0, 4 * button_grid}), {200, button_height}, "SIGN UP", .page_no = LoginPageNo, .function_pointer = SignupPress},
                       {AddVector(home_origin, {0, 5 * button_grid}), {200, button_height}, "LOG IN", .page_no = LoginPageNo, .function_pointer = LoginPress},
                       {AddVector(home_origin, {0, button_grid}), {130, button_height - 10}, "CREATE", .page_no = SignUpPageNo, .function_pointer = AddProfileInfo},
                       {AddVector(home_origin, {0, button_grid}), {150, button_height - 10}, "SIGN IN", .page_no = LoginInfoPageNo, .function_pointer = ProfileAccess},
                       {AddVector(home_origin, {0, 2 * button_grid}), {250, button_height - 10}, "LEVEL 5", .page_no = LevelPageNo, .function_pointer = LevelFive},
                       {AddVector(home_origin, {0, 3 * button_grid}), {250, button_height - 10}, "LEVEL 4", .page_no = LevelPageNo, .function_pointer = LevelFour},
                       {AddVector(home_origin, {0, 4 * button_grid}), {250, button_height - 10}, "LEVEL 3", .page_no = LevelPageNo, .function_pointer = LevelThree},
                       {AddVector(home_origin, {0, 5 * button_grid}), {250, button_height - 10}, "LEVEL 2", .page_no = LevelPageNo, .function_pointer = LevelTwo},
                       {AddVector(home_origin, {0, 6 * button_grid}), {250, button_height - 10}, "LEVEL 1", .page_no = LevelPageNo, .function_pointer = LevelOne},
                       {.dimension = {150, button_height - 15}, .str = "Ok", .page_no = -1, .function_pointer = PromptPress},
                       {AddVector(home_origin, {0, button_grid - 20}), {150, button_height - 10}, "BACK", .page_no = LeaderboardPageNo, .function_pointer = BackPress1},
                       {{scoreboard_X + 30, scoreboard_Y - 1 * (button_height + 60)}, {100, button_height}, "PAUSE", .page_no = GamePageNo, .function_pointer = PausePress},
                       {{scoreboard_X + scoreboard_dx - 100 - 30, scoreboard_Y - 1 * (button_height + 60)}, {100, button_height}, "RESUME", .page_no = GamePageNo, .function_pointer = ResumePress},
                       {{scoreboard_X + 30, scoreboard_Y - 2 * (button_height + 30) - 30}, {100, button_height}, "BACK", .page_no = GamePageNo, .function_pointer = BackPress2},
                       {{scoreboard_X + 30, scoreboard_Y - 3 * (button_height + 30) - 30}, {button_height, button_height}, "X", .page_no = GamePageNo, .function_pointer = XPress},
                       {{750, 80}, {150, button_height - 10}, "BACK", .page_no = HelpPageNo, .function_pointer = BackPress1},
                       {AddVector(home_origin, {0, 2 * button_grid}), {150, button_height - 10}, "BACK", .page_no = SettingsPageNo, .function_pointer = BackPress1},
                       {AddVector(home_origin, {0, 2 * button_grid}), {150, button_height - 10}, "BACK", .page_no = ProfilePageNo, .function_pointer = BackPress1},
                       {AddVector(home_origin, {0, button_grid}), {130, button_height - 10}, "CANCEL", .page_no = SignUpPageNo, .function_pointer = CancelPress}};

projectile floating_object[200]; //holds all the current projectiles to be shown
int floating_objects_size = 0;

//perks
int basket_speed_perks_arr[30], basket_speed_next_perks = 0, basket_speed_no_of_perks = 10, basket_speed_perks_active = 0;
int basket_size_perks_arr[30], basket_size_next_perks = 0, basket_size_no_of_perks = 10, basket_size_perks_active = 0;
int extra_time_perks_arr[30], extra_time_next_perks = 0, extra_time_no_of_perks = 5;

//top scores
char toppers[15][35];
int top_scores[15], top_nxt = 0;

//profile_data
//*each profile holds consecutive 4 cells in profile_data for username, first name, last name and password
char profile_data[1000][35];
int next_profile_data = -1, loggedin_profile = -1;

//prompt text to show
char prompt_text[1000];

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
rgb yellow1 = {254, 228, 64};
rgb light_yellow = {144, 224, 239};
rgb light_red = {255, 153, 172};

//clouds initialization
cloud cld_one = {450, 500, 450, game_origin.y + 610, 1, "images/cloud.bmp"};
cloud cld_two = {650, 700, 650, game_origin.y + 560, 1, "images/cloud.bmp"};
cloud cld_three = {1050, 1100, 1050, game_origin.y + 610, 1, "images/cloud.bmp"};

//chicken initialization
chicken white_chick = {{game_origin.x + 100, -1}, {115, 111}, {chicken_speed[0], 0}, game_origin.x + 800, 0, 0, "images/red.bmp"};
chicken blue_chick = {{game_origin.x + 550, -1}, {121, 114}, {-1 * chicken_speed[1], 0}, game_origin.x + 300, 0, 1, "images/blue.bmp"};
chicken golden_chick = {{game_origin.x + 1000, -1}, {118, 111}, {-1 * chicken_speed[2], 0}, game_origin.x + 300, 0, 2, "images/chuck.bmp"};

//flock initialization
flock flock_arr[] = {{AddVector(game_origin, {0, 500}), {game_dimension.x, 3}, white_chick, blue_chick, golden_chick},
                     {AddVector(game_origin, {0, 400}), {game_dimension.x, 3}, white_chick, blue_chick, golden_chick}};
int flock_arr_size = 2;

//basket initialization
basket basket_arr[] = {{{110, 60}, "images/basket_1.bmp"},
                       {{160, 90}, "images/basket_2.bmp"}};

//bg_images
char game_bg[50] = "images\\a.bmp";

//wind array
int wind_arr[50], next_wind = 0, wind_act_time = 0;
Vector retardation;

//function in GamePage
void CloudAnimation(cloud *c);
void BasketMove(int flag);
void BasketDraw(basket jhuri);
void RightShift(int mx, int my);
void LeftShift(int mx, int my);
void ChickenDraw(chicken *chick);
void FlockDraw(flock *fk);
void GenerateRandom(int arr[], int start, int end, int no_of_rand, int chick_detect);
void GenerateRandomWithGap(int arr[], int start, int end, int no_of_rand, int gap);
void ChangeColor(rgb color);
void ScoreBoardDraw();
void ButtonBoardDraw();
void StopwatchUpdate();
void PopFrontEgg(projectile arr[], int *size);
void FloatingObjDraw();
int ProjectileDraw(projectile *dim);
int FallingObjectUpdate(projectile *obj);
void TopscoreUpdate(char *name, int scr);
void WriteTopperInfo();
void GetTopperInfo();

int Init = 1; //flag for generating/initializing all the necessary variables, arrays for game start

/* 
*Renders the game page
*components: main game, scoreboard, buttonboard, clouds, basket
 */

void GamePage()
{
    ChangeColor(light_red); //bg color
    iFilledRectangle(0, 0, screen_width, screen_height);

    //generates or initialize necessary variables/arrays for game to start
    if (Init)
    {
        Init = 0;
        int end = stopwatch_end_min * 60 + stopwatch_end_sec - 1 + 30;

        //generates eggs and poops for each chicken to be shown
        for (int j = 0; j < flock_arr_size; j++)
        {
            //start time for both eggs and poop should be same
            GenerateRandom(flock_arr[j].white.egg_lay, 2, end, flock_arr[j].white.no_of_egg, -1);
            GenerateRandom(flock_arr[j].white.poop_lay, 2, end, flock_arr[j].white.no_of_egg / 2, j * 10);

            GenerateRandom(flock_arr[j].blue.egg_lay, 2, end, flock_arr[j].blue.no_of_egg, -1);
            GenerateRandom(flock_arr[j].blue.poop_lay, 2, end, flock_arr[j].blue.no_of_egg / 2, j * 10 + 1);

            GenerateRandom(flock_arr[j].golden.egg_lay, 2, end, flock_arr[j].golden.no_of_egg, -1);
            GenerateRandom(flock_arr[j].golden.poop_lay, 2, end, flock_arr[j].golden.no_of_egg / 2, j * 10 + 2);
        }

        //generates perks
        GenerateRandom(basket_speed_perks_arr, 2, end, basket_speed_no_of_perks, -1);
        GenerateRandom(basket_size_perks_arr, 2, end, basket_size_no_of_perks, -1);
        GenerateRandom(extra_time_perks_arr, 2, end, extra_time_no_of_perks, -1);

        //generates wind
        int no_of_winds;
        if (game_time_category == 0)
            no_of_winds = 6;
        else if (game_time_category == 1)
            no_of_winds = 8;
        else if (game_time_category == 2)
            no_of_winds = 10;
        GenerateRandomWithGap(wind_arr, 2, end, no_of_winds, 10);
    }

    iShowBMP(game_origin.x, game_origin.y, game_bg);
    BasketDraw(basket_arr[basket_no]);
    ScoreBoardDraw();
    ButtonBoardDraw();
    FloatingObjDraw();

    //animated clouds(3 clouds)
    iShowBMP2(cld_one.x, cld_one.y, cld_one.filename, 0);
    CloudAnimation(&cld_one);

    iShowBMP2(cld_two.x, cld_two.y, cld_two.filename, 0);
    CloudAnimation(&cld_two);

    iShowBMP2(cld_three.x, cld_three.y, cld_three.filename, 0);
    CloudAnimation(&cld_three);
    //end of animated clouds

    //drawing the flocks with the chickens
    for (int i = 0; i < flock_arr_size; i++)
    {
        flock_arr[i].white.position.y = flock_arr[i].blue.position.y = flock_arr[i].golden.position.y = flock_arr[i].origin.y;
        FlockDraw(&flock_arr[i]);
    }
}

/* 
*draw pause, resume, back, cross button in the game page


 */
void ButtonBoardDraw()
{
    ChangeColor(black); //bg color
    iFilledRectangle(scoreboard_X, game_origin.y, scoreboard_dx, scoreboard_dy - 50);

    for (int i = 18; i < 22; i++)
    {
        ButtonDraw(button_arr[i], red1);
    }

    if (stopwatch_end_sec)
        iShowBMP2(240, 240, "images\\perk_2.bmp", 0xFFFFFF);
    if (basket_speed_perks_active)
        iShowBMP2(240, 190, "images\\perk_1.bmp", 0xFFFFFF);
    if (basket_size_perks_active)
        iShowBMP2(240, 140, "images\\perk_3.bmp", 0xFFFFFF);
}

//updates clouds co-ordinates for motion

void CloudAnimation(cloud *c)
{
    if (pause)
        return;
    c->x += c->dx;
    if (c->x == c->end_X || c->x == c->start_X)
        c->dx *= -1;
}

/* 
    *flag = 1, move the basket to right
    *flag = -1, move the basket to left
 */

void BasketMove(int flag)
{
    if (pause)
        return;
    if (flag == 1)
    {
        basket_origin = AddVector(basket_origin, basket_speed);
        int end_offset = basket_arr[basket_no].dimension.x;
        if (basket_origin.x > game_origin.x + game_dimension.x - end_offset)
            basket_origin.x = game_origin.x + game_dimension.x - end_offset;
    }

    else
    {
        basket_origin = SubVector(basket_origin, basket_speed);
        if (basket_origin.x < game_origin.x)
            basket_origin.x = game_origin.x;
    }
}

void BasketDraw(basket jhuri)
{
    iShowBMP2(basket_origin.x, basket_origin.y, jhuri.filename, 0xFCFEFC);
}

//chickendraw and update
void ChickenDraw(chicken *chick)
{
    if (!chick->show)
        return;
    int ignore = 0xFFFFFF;
    iShowBMP2(chick->position.x, chick->position.y, chick->filename, ignore);

    //motion update
    if (!pause)
    {
        chick->position.x += chick->speed.x;
        if (chick->speed.x > 0)
        {
            if (chick->position.x > chick->boundary_X)
                chick->position.x = chick->boundary_X;
        }
        else
        {
            if (chick->position.x < chick->boundary_X)
                chick->position.x = chick->boundary_X;
        }

        if (chick->position.x == chick->boundary_X)
        {
            chick->boundary_X = game_origin.x + (int)rand() % (int)(game_dimension.x - chick->dimension.x);
            if (chick->position.x < chick->boundary_X)
                chick->speed.x = fabs(chick->speed.x);
            else
                chick->speed.x = -fabs(chick->speed.x);
        }
    }
}

void FlockDraw(flock *fk)
{
    iSetColor(0, 0, 0);
    iFilledRectangle(fk->origin.x, fk->origin.y, fk->dimension.x, fk->dimension.y);

    ChickenDraw(&fk->white);
    ChickenDraw(&fk->blue);
    ChickenDraw(&fk->golden);
}

/* 

*desc: generates no_of_rand unique random numbers in the range [start, end] and store them in arr[]

*chick_detect specially for generating unique egg_lay and poop_lay random time

 */

void GenerateRandom(int arr[], int start, int end, int no_of_rand, int chick_detect)
{
    arr[no_of_rand] = -1; //indicate the end of the eggs

    int check_duplicate[end - start + 10] = {0};

    //for eggs and poop fall time unique
    if (chick_detect != -1)
    {
        if (chick_detect % 10 == 0)
        {
            for (int i = 0; i < flock_arr[chick_detect / 10].white.no_of_egg; i++)
            {
                int j = flock_arr[chick_detect / 10].white.egg_lay[i] - start;
                check_duplicate[j] = 1;
            }
        }
        else if (chick_detect % 10 == 1)
        {
            for (int i = 0; i < flock_arr[chick_detect / 10].blue.no_of_egg; i++)
            {
                int j = flock_arr[chick_detect / 10].blue.egg_lay[i] - start;
                check_duplicate[j] = 1;
            }
        }
        else
        {
            for (int i = 0; i < flock_arr[chick_detect / 10].golden.no_of_egg; i++)
            {
                int j = flock_arr[chick_detect / 10].golden.egg_lay[i] - start;
                check_duplicate[j] = 1;
            }
        }
    }
    for (int i = 0; i < no_of_rand; i++)
    {
        int random = (int)rand() % (end - start + 1);
        while (check_duplicate[random])
            random = (int)rand() % (end - start + 1);

        check_duplicate[random] = 1;
        arr[i] = start + random;
    }

    if (no_of_rand - 1 >= 0)
    {
        for (int pos = no_of_rand - 1; pos; pos--)
        {
            int maxi_ind = 0;
            for (int j = 0; j <= pos; j++)
                if (arr[j] > arr[maxi_ind])
                    maxi_ind = j;

            int temp = arr[maxi_ind];
            arr[maxi_ind] = arr[pos];
            arr[pos] = temp;
        }
    }
}

/* 
* desc: generate random number among which the difference is at least the gap parameter given in the function
 */
void GenerateRandomWithGap(int arr[], int start, int end, int no_of_rand, int gap)
{
    arr[no_of_rand] = -1;
    int check_duplicate[end - start + gap + 10] = {0};

    for (int i = 0; i < no_of_rand; i++)
    {
        int random = (int)rand() % (end - start + 1);
        while (check_duplicate[random])
            random = (int)rand() % (end - start + 1);

        for (int i = 0; i <= gap; i++)
        {
            check_duplicate[random + i] = 1;
            if (random - i >= 0)
                check_duplicate[random - i] = 1;
        }
        arr[i] = start + random;
    }

    if (no_of_rand - 1 >= 0)
    {
        for (int pos = no_of_rand - 1; pos; pos--)
        {
            int maxi_ind = 0;
            for (int j = 0; j <= pos; j++)
                if (arr[j] > arr[maxi_ind])
                    maxi_ind = j;

            int temp = arr[maxi_ind];
            arr[maxi_ind] = arr[pos];
            arr[pos] = temp;
        }
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

    int low_cell = 110, mid_cell = 210, high_cell = 300, horizontal_padding = 20, vertical_padding = 30;

    ChangeColor(red1);
    iLine(scoreboard_X + horizontal_padding, scoreboard_Y + low_cell, scoreboard_X + scoreboard_dx - horizontal_padding, scoreboard_Y + low_cell);
    iLine(scoreboard_X + horizontal_padding, scoreboard_Y + mid_cell, scoreboard_X + scoreboard_dx - horizontal_padding, scoreboard_Y + mid_cell);
    iLine(scoreboard_X + horizontal_padding, scoreboard_Y + high_cell, scoreboard_X + scoreboard_dx - horizontal_padding, scoreboard_Y + high_cell);

    ChangeColor(turquoise);
    iText(scoreboard_X + horizontal_padding, scoreboard_Y + high_cell + vertical_padding, "SCORE-BOARD", GLUT_BITMAP_TIMES_ROMAN_24);

    ChangeColor(red1);
    char score_str[20], win_score_str[20];
    sprintf(score_str, "SCORE: %d", score);
    sprintf(win_score_str, "TARGET: %d", win_score);
    iText(scoreboard_X + horizontal_padding, scoreboard_Y + high_cell - vertical_padding, score_str, GLUT_BITMAP_HELVETICA_18);
    iText(scoreboard_X + horizontal_padding, scoreboard_Y + high_cell - 2 * vertical_padding, win_score_str, GLUT_BITMAP_HELVETICA_18);

    char stopwatch_str[20];
    sprintf(stopwatch_str, "TIME: %02d : %02d", stopwatch_current_min, stopwatch_current_sec);
    iText(scoreboard_X + horizontal_padding, scoreboard_Y + low_cell - vertical_padding, stopwatch_str, GLUT_BITMAP_HELVETICA_18);
    sprintf(stopwatch_str, "FINISH TIME: %02d : %02d", stopwatch_end_min, stopwatch_end_sec);
    iText(scoreboard_X + horizontal_padding, scoreboard_Y + low_cell - 2 * vertical_padding, stopwatch_str, GLUT_BITMAP_HELVETICA_18);

    iText(scoreboard_X + horizontal_padding, scoreboard_Y + mid_cell - vertical_padding, "WHITE        BLUE      GOLDEN", GLUT_BITMAP_HELVETICA_18);
    char egg_cnt_str[50];
    sprintf(egg_cnt_str, "     %d            %d            %d", white_egg_cnt, blue_egg_cnt, golden_egg_cnt);
    iText(scoreboard_X + horizontal_padding, scoreboard_Y + mid_cell - vertical_padding - 35, egg_cnt_str, GLUT_BITMAP_TIMES_ROMAN_24);
}

void StopwatchUpdate()
{

    if (stopwatch_current_min == stopwatch_end_min && stopwatch_current_sec == stopwatch_end_sec)
    {
        iPauseTimer(0);
        pause = 1;
        if (sound_is_on)
            PlaySound(NULL, NULL, 0);
        TopscoreUpdate(profile_data[loggedin_profile], score);

        char temp[200] = "Game Over.";
        if (score >= win_score)
            strcat(temp, "You win. Hurrah!!!");
        else
            strcat(temp, "You lost. Better luck next time.");

        strcpy(prompt_text, temp);
        popup_show = PopupNo;

        //clearingalldata
        //pauseanimation

        return;
    }

    stopwatch_current_sec++;
    if (stopwatch_current_sec == 60)
    {
        stopwatch_current_sec = 0;
        stopwatch_current_min++;
    }

    //adding eggs and poops laid by the chickens
    int time_in_sec = stopwatch_current_min * 60 + stopwatch_current_sec;
    for (int i = 0; i < flock_arr_size; i++)
    {
        if (flock_arr[i].white.show == 1 && flock_arr[i].white.egg_lay[flock_arr[i].white.next_egg] == time_in_sec)
        {

            flock_arr[i].white.next_egg++;
            floating_object[floating_objects_size++] = {.origin = AddVector(flock_arr[i].white.position, {flock_arr[i].white.dimension.x / 2, 0}), .co_ordinate = AddVector(flock_arr[i].white.position, {flock_arr[i].white.dimension.x / 2, 0}), .dimension = {8.0, 14.0}, .velocity = flock_arr[i].white.speed, .color = flock_arr[i].white.color};
        }
        if (flock_arr[i].white.show == 1 && flock_arr[i].white.poop_lay[flock_arr[i].white.next_poop] == time_in_sec)
        {
            flock_arr[i].white.next_poop++;
            floating_object[floating_objects_size++] = {.origin = AddVector(flock_arr[i].white.position, {flock_arr[i].white.dimension.x / 2, 0}), .co_ordinate = AddVector(flock_arr[i].white.position, {flock_arr[i].white.dimension.x / 2, 0}), .dimension = {25, 22}, .velocity = flock_arr[i].white.speed, .color = poop_color};
        }

        if (flock_arr[i].blue.show == 1 && flock_arr[i].blue.egg_lay[flock_arr[i].blue.next_egg] == time_in_sec)
        {
            flock_arr[i].blue.next_egg++;
            floating_object[floating_objects_size++] = {.origin = AddVector(flock_arr[i].blue.position, {flock_arr[i].blue.dimension.x / 2, 0}), .co_ordinate = AddVector(flock_arr[i].blue.position, {flock_arr[i].blue.dimension.x / 2, 0}), .dimension = {8.0, 14.0}, .velocity = flock_arr[i].blue.speed, .color = flock_arr[i].blue.color};
        }
        if (flock_arr[i].blue.show == 1 && flock_arr[i].blue.poop_lay[flock_arr[i].blue.next_poop] == time_in_sec)
        {
            flock_arr[i].blue.next_poop++;
            floating_object[floating_objects_size++] = {.origin = AddVector(flock_arr[i].blue.position, {flock_arr[i].blue.dimension.x / 2, 0}), .co_ordinate = AddVector(flock_arr[i].blue.position, {flock_arr[i].blue.dimension.x / 2, 0}), .dimension = {25, 22}, .velocity = flock_arr[i].blue.speed, .color = poop_color};
        }

        if (flock_arr[i].golden.show == 1 && flock_arr[i].golden.egg_lay[flock_arr[i].golden.next_egg] == time_in_sec)
        {
            flock_arr[i].golden.next_egg++;
            floating_object[floating_objects_size++] = {.origin = AddVector(flock_arr[i].golden.position, {flock_arr[i].golden.dimension.x / 2, 0}), .co_ordinate = AddVector(flock_arr[i].golden.position, {flock_arr[i].golden.dimension.x / 2, 0}), .dimension = {8.0, 14.0}, .velocity = flock_arr[i].golden.speed, .color = flock_arr[i].golden.color};
        }
        if (flock_arr[i].golden.show == 1 && flock_arr[i].golden.poop_lay[flock_arr[i].golden.next_poop] == time_in_sec)
        {
            flock_arr[i].golden.next_poop++;
            floating_object[floating_objects_size++] = {.origin = AddVector(flock_arr[i].golden.position, {flock_arr[i].golden.dimension.x / 2, 0}), .co_ordinate = AddVector(flock_arr[i].golden.position, {flock_arr[i].golden.dimension.x / 2, 0}), .dimension = {25, 22}, .velocity = flock_arr[i].golden.speed, .color = poop_color};
        }
    }

    //adding perks
    if (basket_size_perks_arr[basket_size_next_perks] == time_in_sec)
    {
        basket_size_next_perks++;
        if (basket_size_perks_active == 0)
        {
            int falling_X = (int)rand() % (int)game_dimension.x;
            floating_object[floating_objects_size++] = {.origin = AddVector(game_origin, {falling_X, game_dimension.y - 29}), .co_ordinate = AddVector(game_origin, {falling_X, game_dimension.y}), .dimension = {32, 29}, .velocity = {0, 0}, .color = basket_size_perks_color};
        }
    }

    if (extra_time_perks_arr[extra_time_next_perks] == time_in_sec)
    {
        extra_time_next_perks++;
        int falling_X = (int)rand() % (int)game_dimension.x;
        floating_object[floating_objects_size++] = {.origin = AddVector(game_origin, {falling_X, game_dimension.y - 31}), .co_ordinate = AddVector(game_origin, {falling_X, game_dimension.y}), .dimension = {32, 31}, .velocity = {0, 0}, .color = extra_time_perks_color};
    }

    if (basket_speed_perks_arr[basket_speed_next_perks] == time_in_sec)
    {
        basket_speed_next_perks++;
        if (basket_speed_perks_active == 0)
        {
            int falling_X = (int)rand() % (int)game_dimension.x;
            floating_object[floating_objects_size++] = {.origin = AddVector(game_origin, {falling_X, game_dimension.y - 29}), .co_ordinate = AddVector(game_origin, {falling_X, game_dimension.y}), .dimension = {32, 29}, .velocity = {0, 0}, .color = basket_speed_perks_color};
        }
    }

    //checking end of perks
    if (time_in_sec == basket_speed_perks_active)
    {
        basket_speed_perks_active = 0;
        basket_speed = SubVector(basket_speed, {5, 0});
    }

    if (time_in_sec == basket_size_perks_active)
    {
        basket_size_perks_active = 0;
        basket_no--;
    }

    //adding winds
    if (time_in_sec == wind_arr[next_wind])
    {
        next_wind++;
        if (sound_is_on)
            PlaySound(TEXT("sounds\\wind.wav"), NULL, SND_LOOP | SND_ASYNC);
        Vector force = {0.182, 0};
        if (next_wind & 1)
            force = {-0.182, 0};
        net_accleration = AddVector(net_accleration, force);
        wind_act_time = 8;
        retardation = {-force.x / wind_act_time, 0};
    }

    if (wind_act_time)
    {
        wind_act_time--;
        if (sound_is_on && !wind_act_time)
            PlaySound(NULL, NULL, 0);
        net_accleration = AddVector(net_accleration, retardation);
    }
}

void PopFrontEgg(projectile arr[], int *size, int ind)
{
    if (size == 0)
        return;

    for (int i = ind + 1; i < *size; i++)
        arr[i - 1] = arr[i];

    (*size)--;
}

void FloatingObjDraw()
{
    int rmv[50], next = 0;

    for (int i = 0; i < floating_objects_size; i++)
    {
        if (ProjectileDraw(&floating_object[i]))
        {
            rmv[next++] = i;
        }
    }

    //sorting rmv
    for (int i = 0; i < next - 1; i++)
    {
        int mini_ind = i;
        for (int j = i + 1; j < next; j++)
            if (rmv[j] < rmv[mini_ind])
                mini_ind = j;

        int temp = rmv[i];
        rmv[i] = rmv[mini_ind];
        rmv[mini_ind] = temp;
    }

    for (int i = 0; i < next; i++)
        PopFrontEgg(floating_object, &floating_objects_size, rmv[i] - i);
}

int ProjectileDraw(projectile *obj)
{
    int res = 0;

    if (obj->color < 3) //egg object
    {
        ChangeColor(black);
        iFilledEllipse(obj->co_ordinate.x, obj->co_ordinate.y, obj->dimension.x + 2, obj->dimension.y + 2);

        if (obj->color == 0)
            ChangeColor(red1);
        else if (obj->color == 1)
            ChangeColor(blue1);
        else
            ChangeColor(yellow1);

        iFilledEllipse(obj->co_ordinate.x, obj->co_ordinate.y, obj->dimension.x, obj->dimension.y);
    }
    else if (obj->color == poop_color)
    {
        iShowBMP2(obj->co_ordinate.x, obj->co_ordinate.y, "images\\poop_image.bmp", 0xFFFFFF);
    }
    else if (obj->color == basket_speed_perks_color)
    {
        iShowBMP2(obj->co_ordinate.x, obj->co_ordinate.y, "images\\perk_1.bmp", 0xFFFFFF);
    }
    else if (obj->color == basket_size_perks_color)
    {
        iShowBMP2(obj->co_ordinate.x, obj->co_ordinate.y, "images\\perk_3.bmp", 0xFFFFFF);
    }
    else if (obj->color == extra_time_perks_color)
    {
        iShowBMP2(obj->co_ordinate.x, obj->co_ordinate.y, "images\\perk_2.bmp", 0xFFFFFF);
    }
    else
    {
        //other projectile
    }

    res = FallingObjectUpdate(obj);
    return res;
}

int FallingObjectUpdate(projectile *obj)
{
    if (pause)
        return 0;
    double prev_Y = obj->co_ordinate.y;
    obj->velocity = AddVector(obj->velocity, net_accleration);
    obj->co_ordinate = AddVector(obj->co_ordinate, obj->velocity);

    int ret = 0;

    //entering basket
    if (obj->co_ordinate.x >= basket_origin.x && obj->co_ordinate.x <= basket_origin.x + basket_arr[basket_no].dimension.x && prev_Y >= basket_origin.y + basket_arr[basket_no].dimension.y && obj->co_ordinate.y <= basket_origin.y + basket_arr[basket_no].dimension.y)
    {

        ret = 1;
        if (obj->color == 0)
            white_egg_cnt++;
        else if (obj->color == 1)
            blue_egg_cnt++;
        else if (obj->color == 2)
            golden_egg_cnt++;
        else if (obj->color == poop_color)
            poop_cnt++;
        else if (obj->color == basket_speed_perks_color)
        {
            basket_speed = AddVector(basket_speed, {5, 0});
            basket_speed_perks_active = stopwatch_current_min * 60 + stopwatch_current_sec + 15;
        }
        else if (obj->color == basket_size_perks_color)
        {
            basket_no = 1;
            basket_size_perks_active = stopwatch_current_min * 60 + stopwatch_current_sec + 15;
        }
        else if (obj->color == extra_time_perks_color)
        {
            stopwatch_end_sec += 5;
        }
        score = -poop_cnt * poop_point + white_egg_cnt * white_egg_point + blue_egg_cnt * blue_egg_point + golden_egg_cnt * golden_egg_point;
    }
    //hitting the ground
    else if (obj->co_ordinate.y <= game_origin.y)
    {
        ret = 1;
    }
    //collision with sidewall
    else if (obj->co_ordinate.x <= game_origin.x || obj->co_ordinate.x >= game_origin.x + game_dimension.x - obj->dimension.x)
        obj->velocity.x *= -1;

    return ret;
}

void GetTopperInfo()
{

    FILE *fp = NULL;

    if ((fp = fopen(leaderboard_file, "r")) == NULL)
    {
        printf("Error Opening file.\n");
        return;
    }

    char temp[50];
    top_nxt = 0;
    while (fscanf(fp, "%s", temp) != EOF)
    {
        char s_temp[10];
        int i = 0;
        for (; i < strlen(temp); i++)
        {
            if (temp[i] == ',')
                break;
            toppers[top_nxt][i] = temp[i];
        }

        toppers[top_nxt][i] = '\0';
        i++;
        int j;
        for (j = 0; i < strlen(temp); i++, j++)
            s_temp[j] = temp[i];

        s_temp[j] = '\0';

        top_scores[top_nxt] = atoi(s_temp);
        top_nxt++;
    }

    fclose(fp);
}

void TopscoreUpdate(char *name, int scr)
{
    if (top_nxt == 0)
        GetTopperInfo();
    int pos = top_nxt;

    while (pos && top_scores[pos - 1] < scr)
    {
        pos--;
    }
    if (top_nxt < 10)
        top_nxt++;
    for (int i = top_nxt - 1; i > pos; i--)
    {
        top_scores[i] = top_scores[i - 1];
        strcpy(toppers[i], toppers[i - 1]);
    }

    if (pos < top_nxt)
    {
        top_scores[pos] = scr;
        strcpy(toppers[pos], name);
    }
    WriteTopperInfo();
}

void WriteTopperInfo()
{
    if (top_nxt == 0)
        return;

    FILE *fp = NULL;
    if ((fp = fopen(leaderboard_file, "w")) == NULL)
    {
        printf("Error opening file in WriteTopperInfo.\n");
        return;
    }

    for (int i = 0; i < top_nxt; i++)
    {
        if (fprintf(fp, "%s,%d\n", toppers[i], top_scores[i]) == EOF)
        {
            printf("Error writing to leaderboard.\n");
            return;
        }
    }
    fclose(fp);
}

#endif // FF_H_INCLUDED