#pragma once

/* #include "iGraphics.h" */
#include<stdio.h>
#include<string.h>
#include "GamePage.h"

typedef struct 
{
    Vector origin, dimension;
    char* str;
    int active, page_no;
    void (*function_pointer)();
}button;


typedef struct 
{
    Vector origin, dimension;
    char *title, *label;
    char input[50];
    int next_input, active, page_no;
}placeholder;

typedef struct 
{
    int one, two, three;
} int_tuple;


typedef struct
{
    int stopwatch_end_min, stopwatch_end_sec;
    int win_score[15];
    int_tuple no_of_eggs[15];
} time_slot;

//time slot initialization
time_slot time_slot_arr[] = {{1, 0, {100, 300, 500, 700, 1000}, {{20, 0, 0}, {20, 15, 0}, {20, 15, 10}, {20, 15, 0},{20, 15, 0},{20, 15, 10},{20, 15, 10}}},
{2, 0, {300, 500, 700, 1000, 1300}, {{20, 0, 0}, {20, 15, 0}, {20, 15, 10}, {20, 15, 0},{20, 15, 0},{20, 15, 10},{20, 15, 10}}},
{3, 0, {500, 700, 1000, 1300, 1500}, {{20, 0, 0}, {20, 15, 0}, {20, 15, 10}, {20, 15, 0},{20, 15, 0},{20, 15, 10},{20, 15, 10}}}};

//variables from homepage
Vector home_origin = {500, 0}, home_dimension = {550, screen_height};
int HEL_font_size = 13;
int button_height = 50, button_grid = 70;
int placeholder_height = 30, placeholder_grid = 100;
int current_time_slot = 0;



void ButtonDraw(button btn, rgb col);
void LoginPage();
void SignUp();
void PlaceholderDraw(placeholder* pl, rgb col);
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

//buttons initialization
button button_arr[] = {{AddVector(home_origin,{0, button_grid}), {100, button_height}, "EXIT", .page_no = HomePageNo}, 
{AddVector(home_origin,{0, 2*button_grid}), {100, button_height}, "HELP", .page_no = HomePageNo}, 
{AddVector(home_origin,{0, 3*button_grid}), {200, button_height}, "SETTINGS", .page_no = HomePageNo}, 
{AddVector(home_origin,{0, 4*button_grid}), {250, button_height}, "LEADERBOARD", .page_no = HomePageNo}, 
{AddVector(home_origin,{0, 5*button_grid}), {200, button_height}, "PROFILE", .page_no = HomePageNo}, 
{AddVector(home_origin,{0, 6*button_grid}), {200, button_height}, "START", .page_no = HomePageNo}, 
{AddVector(home_origin,{0, 7*button_grid}), {200, button_height}, "RESUME", .page_no = HomePageNo}, 
{AddVector(home_origin,{0, 4*button_grid}), {200, button_height}, "SIGN UP", .page_no = LoginPageNo, .function_pointer = SignupPress},
{AddVector(home_origin,{0, 5*button_grid}), {200, button_height}, "LOG IN", .page_no = LoginPageNo, .function_pointer = LoginPress}, 
{AddVector(home_origin,{0, button_grid}), {150, button_height-10}, "CREATE", .page_no = SignUpPageNo, .function_pointer = AddProfileInfo}, 
{AddVector(home_origin,{0, button_grid}), {150, button_height-10}, "SIGN IN", .page_no = LoginInfoNo, .function_pointer = ProfileAccess},
{AddVector(home_origin,{0, 2*button_grid}), {250, button_height-10}, "LEVEL 5", .page_no = LevelPageNo, .function_pointer = LevelFive},
{AddVector(home_origin,{0, 3*button_grid}), {250, button_height-10}, "LEVEL 4", .page_no = LevelPageNo, .function_pointer = LevelFour},
{AddVector(home_origin,{0, 4*button_grid}), {250, button_height-10}, "LEVEL 3", .page_no = LevelPageNo, .function_pointer = LevelThree},
{AddVector(home_origin,{0, 5*button_grid}), {250, button_height-10}, "LEVEL 2", .page_no = LevelPageNo, .function_pointer = LevelTwo},
{AddVector(home_origin,{0, 6*button_grid}), {250, button_height-10}, "LEVEL 1", .page_no = LevelPageNo, .function_pointer = LevelOne},
{.dimension = {150, button_height-15}, .str = "Ok", .page_no = -1, .function_pointer = PromptPress}};


//placeholder initialization
placeholder placeholder_arr[] = {{AddVector(home_origin,{0, 2*placeholder_grid}), {300, placeholder_height},"PASSWORD", "Password should not cross 30 characters.", .page_no = SignUpPageNo},
{AddVector(home_origin,{0, 3*placeholder_grid}), {300, placeholder_height},"LAST NAME", "Last name should not cross 30 characters.", .page_no = SignUpPageNo},
{AddVector(home_origin,{0, 4*placeholder_grid}), {300, placeholder_height},"FIRST NAME", "First name should not cross 30 characters.", .page_no = SignUpPageNo},
{AddVector(home_origin,{0, 5*placeholder_grid}), {300, placeholder_height},"USERNAME", "Username should not cross 30 characters.", .page_no = SignUpPageNo},
{AddVector(home_origin,{0, 3*placeholder_grid}), {300, placeholder_height},"PASSWORD", "Write your password.", .page_no = LoginInfoNo},
{AddVector(home_origin,{0, 4*placeholder_grid}), {300, placeholder_height},"USERNAME", "Write your username.",.page_no = LoginInfoNo}};




void HomePage()
{
    iShowBMP(0, 0, "images/sky_bg.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    for(int i = 0; i< 7; i++)
    {
        if(button_arr[i].page_no == page_no)
        {
            button_arr[i].origin.x = home_origin.x + (home_dimension.x - button_arr[i].dimension.x)/2;
            ButtonDraw(button_arr[i], red1);
        }
    }
    
}


void ButtonDraw(button btn, rgb col)
{
    ChangeColor(col);
    iRectangle(btn.origin.x, btn.origin.y, btn.dimension.x, btn.dimension.y);

    if(btn.active)
        iFilledRectangle(btn.origin.x, btn.origin.y, btn.dimension.x, btn.dimension.y);

    double text_X = btn.origin.x + (btn.dimension.x - strlen(btn.str)*HEL_font_size)/2;
    double text_Y = btn.origin.y + (btn.dimension.y - HEL_font_size)/2;
    
    if(text_X < 0 || text_Y < 0)
    {
        printf("Too small Button.\n");
        return ;
    }
    if(btn.active)
        ChangeColor(black);
    iText(text_X, text_Y, btn.str, GLUT_BITMAP_HELVETICA_18);
}


void LoginPage()
{

    iShowBMP(0, 0, "images/sky_bg.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    for(int i = 7; i<9; i++)
    {
        button_arr[i].origin.x = home_origin.x + (home_dimension.x - button_arr[i].dimension.x)/2;
        ButtonDraw(button_arr[i], turquoise);
    }

}

void SignUp()
{
    iShowBMP(0, 0, "images/sky_bg.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    for(int i = 0; i< 4; i++)
    {
        placeholder_arr[i].origin.x = home_origin.x + (home_dimension.x - placeholder_arr[i].dimension.x)/2;
        PlaceholderDraw(&placeholder_arr[i], turquoise);
    }

    button_arr[9].origin.x = home_origin.x + (home_dimension.x - button_arr[9].dimension.x)/2;
    ButtonDraw(button_arr[9], turquoise);
}

void PlaceholderDraw(placeholder* pl, rgb col)
{
    ChangeColor(col);

    iText(pl->origin.x, pl->origin.y + pl->dimension.y + 10, pl->title, GLUT_BITMAP_HELVETICA_18);
    iText(pl->origin.x, pl->origin.y - 15, pl->label, GLUT_BITMAP_HELVETICA_12);
    

    ChangeColor(white2);
    iFilledRectangle(pl->origin.x, pl->origin.y, pl->dimension.x, pl->dimension.y);

    ChangeColor(black);
    iText(pl->origin.x + 10, pl->origin.y + (pl->dimension.y - HEL_font_size)/2, pl->input, GLUT_BITMAP_HELVETICA_18);

}


void AddProfileInfo()
{

    char username[50],first_name[50],last_name[50],password[50];

    for(int i = 0; i< 4; i++)
    {
        if(placeholder_arr[i].next_input > 30)
        {
            //invalid prompt
            return;
        }
    }

    if(UsernameMatch(placeholder_arr[3].input) != -1)
    {
        //invalid prompt 
        return;
    }
    

    strcpy(username, placeholder_arr[3].input);
    strcpy(first_name, placeholder_arr[2].input);
    strcpy(last_name, placeholder_arr[1].input);
    strcpy(password, placeholder_arr[0].input);

    FILE* fp = NULL;
    if((fp = fopen("profile.txt", "ab")) == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    int str_sizes[] = {(int)strlen(username),(int)strlen(first_name),(int)strlen(last_name),(int)strlen(password)};
    
    if(fseek(fp, 0, SEEK_END))
    {
        printf("Error in random access.\n");
        return;
    }

    if(fwrite(str_sizes, sizeof(str_sizes), 1, fp) != 1)
    {
        printf("Error writing sizes.\n");
        return;
    }

    if(fwrite(username, str_sizes[0], 1, fp) != 1)
    {
        printf("Error writing username.\n");
        return;
    }

    if(fwrite(first_name, str_sizes[1], 1, fp) != 1)
    {
        printf("Error writing first name.\n");
        return;
    }

    if(fwrite(last_name, str_sizes[2], 1, fp) != 1)
    {
        printf("Error writing last name.\n");
        return;
    }

    if(fwrite(password, str_sizes[3], 1, fp) != 1)
    {
        printf("Error writing password.\n");
        return;
    }

    fclose(fp);

    page_no = HomePageNo;
}

void LoginInfo()
{
    iShowBMP(0, 0, "images/sky_bg.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);


    for(int i = 4; i<6; i++)
    {
        placeholder_arr[i].origin.x = home_origin.x + (home_dimension.x - placeholder_arr[i].dimension.x)/2;
        PlaceholderDraw(&placeholder_arr[i], blue1);
    }

    button_arr[10].origin.x = home_origin.x + (home_dimension.x - button_arr[10].dimension.x)/2;
    ButtonDraw(button_arr[10], blue1); 

}

void GetProfileInfo()
{
    FILE *fp = NULL;

    if((fp = fopen("profile.txt", "rb")) == NULL)
    {
        printf("Error opening the file in GetProfileInfo.\n");
        return;
    }

    int str_sizes[4];
    next_profile_data = 0;

    while (fread(str_sizes, sizeof(str_sizes), 1, fp) == 1)
    {
        char ret_username[str_sizes[0]+1], ret_first_name[str_sizes[1]+1], ret_last_name[str_sizes[2] + 1], ret_password[str_sizes[3]+1];

        if(fread(ret_username, sizeof(ret_username)-1, 1, fp) != 1)
        {
            printf("Error reading ret_username.\n");
            return ;
        }


        ret_username[str_sizes[0]] = '\0';


        if(fread(ret_first_name, sizeof(ret_first_name)-1, 1, fp) != 1)
        {
            printf("Error reading ret_first_name.\n");
            return ;
        }

        ret_first_name[str_sizes[1]] = '\0';


        if(fread(ret_last_name, sizeof(ret_last_name)-1, 1, fp) != 1)
        {
            printf("Error reading last_name.\n");
            return ;
        }

        ret_last_name[str_sizes[2]] = '\0';

        if(fread(ret_password, sizeof(ret_password)-1, 1, fp) != 1)
        {
            printf("Error reading password.\n");
            return ;
        }

        ret_password[str_sizes[3]] = '\0';

        strcpy(profile_data[next_profile_data++],ret_username);
        strcpy(profile_data[next_profile_data++],ret_first_name);
        strcpy(profile_data[next_profile_data++],ret_last_name);
        strcpy(profile_data[next_profile_data++],ret_password);

    }

    fclose(fp);
}

int UsernameMatch(char *user_name)
{
    if(next_profile_data == -1)
        GetProfileInfo();
    int res = -1;

    for(int i = 0; i< next_profile_data; i+=4)
    {
        if(strcmp(profile_data[i], user_name))
            continue;
        res = i;
        break;
    }

    return res;
}

int PassMatch(char *pass)
{
    if(next_profile_data == -1)
        GetProfileInfo();
    int res = -1;

    for(int i = 0; i< next_profile_data; i+=4)
    {
        if(strcmp(profile_data[i+3], pass))
            continue;
        res = i;
        break;
    }

    return res;
}

void ProfileAccess()
{
    int res1 = UsernameMatch(placeholder_arr[5].input);
    int res2 = PassMatch(placeholder_arr[4].input);
    if(res1 != -1 && res1 == res2)
    {
        loggedin_profile = res1;
        page_no = HomePageNo;

        char temp[100] = "Now you are logged in. Have fun!!! Press ok to continue.";
        strcpy(prompt_text, temp);
        prompt_show = PromptNo;
    }
    else
    {
        //show invalid prompt
        char temp[200] = "Sorry, invalid username or password. Try to avoid spelling mistakes. Press ok to continue.";
        strcpy(prompt_text, temp);
        prompt_show = PromptNo;
    }
    
}

void LevelPage()
{
    iShowBMP(0, 0, "images/sky_bg.bmp");

    ChangeColor(black);
    iFilledRectangle(home_origin.x, home_origin.y, home_dimension.x, home_dimension.y);

    for(int i = 11; i < 16; i++)
    {
        button_arr[i].origin.x = home_origin.x + (home_dimension.x - button_arr[i].dimension.x)/2;
        ButtonDraw(button_arr[i], yellow1);
    }

}


void LevelOne()
{
    flock_arr_size = 1;
    flock_arr[0].white.show = 1;

    stopwatch_end_min = time_slot_arr[current_time_slot].stopwatch_end_min;
    stopwatch_end_sec = time_slot_arr[current_time_slot].stopwatch_end_sec;

    target_score = time_slot_arr[current_time_slot].win_score[0];
    flock_arr[0].white.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[0].one;
    flock_arr[0].blue.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[0].two;
    flock_arr[0].golden.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[0].three;

    page_no = GamePageNo;  
    iResumeTimer(0);  
}
void LevelTwo()
{
    flock_arr_size = 1;
    flock_arr[0].white.show = 1;
    flock_arr[0].blue.show = 1;

    stopwatch_end_min = time_slot_arr[current_time_slot].stopwatch_end_min;
    stopwatch_end_sec = time_slot_arr[current_time_slot].stopwatch_end_sec;

    target_score = time_slot_arr[current_time_slot].win_score[1];
    flock_arr[0].white.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[1].one;
    flock_arr[0].blue.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[1].two;
    flock_arr[0].golden.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[1].three;

    page_no = GamePageNo;
    iResumeTimer(0);
}
void LevelThree()
{
    flock_arr_size = 1;
    flock_arr[0].white.show = 1;
    flock_arr[0].blue.show = 1;
    flock_arr[0].golden.show = 1;

    stopwatch_end_min = time_slot_arr[current_time_slot].stopwatch_end_min;
    stopwatch_end_sec = time_slot_arr[current_time_slot].stopwatch_end_sec;

    target_score = time_slot_arr[current_time_slot].win_score[2];
    flock_arr[0].white.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[2].one;
    flock_arr[0].blue.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[2].two;
    flock_arr[0].golden.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[2].three;

    page_no = GamePageNo;
    iResumeTimer(0);
}
void LevelFour()
{
    flock_arr_size = 2;
    flock_arr[0].white.show = 1;
    flock_arr[1].white.show = 1;
    flock_arr[0].blue.show = 1;
    flock_arr[1].blue.show = 1;

    stopwatch_end_min = time_slot_arr[current_time_slot].stopwatch_end_min;
    stopwatch_end_sec = time_slot_arr[current_time_slot].stopwatch_end_sec;

    target_score = time_slot_arr[current_time_slot].win_score[3];
    flock_arr[0].white.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[3].one;
    flock_arr[0].blue.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[3].two;
    flock_arr[0].golden.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[3].three;

    flock_arr[1].white.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[4].one;
    flock_arr[1].blue.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[4].two;
    flock_arr[1].golden.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[4].three;

    page_no = GamePageNo;
    iResumeTimer(0);
}
void LevelFive()
{
    flock_arr_size = 2;
    flock_arr[0].white.show = 1;
    flock_arr[0].blue.show = 1;
    flock_arr[0].golden.show = 1;
    flock_arr[1].white.show = 1;
    flock_arr[1].blue.show = 1;
    flock_arr[1].golden.show = 1;

    stopwatch_end_min = time_slot_arr[current_time_slot].stopwatch_end_min;
    stopwatch_end_sec = time_slot_arr[current_time_slot].stopwatch_end_sec;

    target_score = time_slot_arr[current_time_slot].win_score[4];
    flock_arr[0].white.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[5].one;
    flock_arr[0].blue.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[5].two;
    flock_arr[0].golden.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[5].three;

    flock_arr[1].white.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[6].one;
    flock_arr[1].blue.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[6].two;
    flock_arr[1].golden.no_of_egg = time_slot_arr[current_time_slot].no_of_eggs[6].three;

    page_no = GamePageNo;
    iResumeTimer(0);
}

void Intro()
{
    iShowBMP(0, 0, "images/sky_bg.bmp");

}

void LoginPress()
{
    page_no = LoginInfoNo;
}

void SignupPress()
{
    page_no = SignUpPageNo;
}

void Prompt()
{
    Vector origin = {550, 300}, dimension = {0, 0};
    int char_per_line = 40, vetical_padding = 10, side_padding = 20;
    int lines = strlen(prompt_text)/char_per_line + (strlen(prompt_text)%char_per_line != 0);
    int small_font = 9;
    dimension.y = small_font*lines + vetical_padding*(lines-1) + side_padding*3 + button_height;
    dimension.x = side_padding*2 + small_font*char_per_line;

    
    ChangeColor(white);
    iFilledRectangle(origin.x, origin.y, dimension.x, dimension.y);

    Vector text_origin = {origin.x + side_padding, origin.y + dimension.y - side_padding - small_font};

    ChangeColor(black);
    for(int i = 0; i< lines; i++)
    {

        char temp[char_per_line+1];
        temp[char_per_line] = '\0';

        int lim = (i+1)*char_per_line;
        if(strlen(prompt_text) < lim)
        {
            lim = strlen(prompt_text);
            temp[lim - i*char_per_line ] = '\0';
        }

        for(int j = i*char_per_line, k = 0; j < lim; j++, k++)
            temp[k] = prompt_text[j];
        
        iText(text_origin.x, text_origin.y, temp, GLUT_BITMAP_HELVETICA_18);
        text_origin = SubVector(text_origin, {0, vetical_padding + small_font});
    }

    button_arr[16].origin.x = origin.x + (dimension.x - button_arr[16].dimension.x)/2;
    button_arr[16].origin.y = origin.y + side_padding;
    ButtonDraw(button_arr[16], turquoise);

}

void PromptPress()
{
    if(prompt_text[0] = 'N')  //logged in
    {

    }

    else if(prompt_text[0] = 'S')  //invalid username or password
    {

    }

    prompt_show = 0;
}