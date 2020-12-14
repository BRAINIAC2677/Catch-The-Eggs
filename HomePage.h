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
    void (*fun)();
}button;


typedef struct 
{
    Vector origin, dimension;
    char *title, *label;
    char input[50];
    int next_input, active, page_no;
}placeholder;


//variables
Vector home_origin = {500, 0}, home_dimension = {550, screen_height};
int HEL_font_size = 13;
int button_height = 50, button_grid = 70;
int placeholder_height = 30, placeholder_grid = 100;


void ButtonDraw(button btn, rgb col);
void LoginPage();
void SignUp();
void PlaceholderDraw(placeholder* pl, rgb col);
void AddProfileInfo();

//buttons initialization
button button_arr[] = {{AddVector(home_origin,{0, button_grid}), {100, button_height}, "EXIT", .page_no = 1}, 
{AddVector(home_origin,{0, 2*button_grid}), {100, button_height}, "HELP", .page_no = 1}, 
{AddVector(home_origin,{0, 3*button_grid}), {200, button_height}, "SETTINGS", .page_no = 1}, 
{AddVector(home_origin,{0, 4*button_grid}), {250, button_height}, "LEADERBOARD", .page_no = 1}, 
{AddVector(home_origin,{0, 5*button_grid}), {200, button_height}, "PROFILE", .page_no = 1}, 
{AddVector(home_origin,{0, 6*button_grid}), {200, button_height}, "START", .page_no = 1}, 
{AddVector(home_origin,{0, 7*button_grid}), {200, button_height}, "RESUME", .page_no = 1}, 
{AddVector(home_origin,{0, 4*button_grid}), {200, button_height}, "SIGN UP", .page_no = 2},
{AddVector(home_origin,{0, 5*button_grid}), {200, button_height}, "LOG IN", .page_no = 2}, 
{AddVector(home_origin,{0, button_grid}), {150, button_height-10}, "CREATE", .page_no = SignUpPageNo, .fun = AddProfileInfo}, 
{AddVector(home_origin,{0, button_grid}), {150, button_height-10}, "SIGN IN", .page_no = LoginInfoNo}};


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
            return;
        }
    }

    strcpy(username, placeholder_arr[3].input);
    strcpy(first_name, placeholder_arr[2].input);
    strcpy(last_name, placeholder_arr[1].input);
    strcpy(password, placeholder_arr[0].input);

    FILE* fp = NULL;
    if((fp = fopen("profile.txt", "wb")) == NULL)
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