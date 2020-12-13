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
}button;


//variables
Vector home_origin = {500, 0}, home_dimension = {550, screen_height};
int font_size = 13;
int button_height = 50, home_block = 70;


//buttons initialization
button button_arr[] = {{AddVector(home_origin,{0, home_block}), {100, button_height}, "EXIT", .page_no = 1}, 
{AddVector(home_origin,{0, 2*home_block}), {100, button_height}, "HELP", .page_no = 1}, 
{AddVector(home_origin,{0, 3*home_block}), {200, button_height}, "SETTINGS", .page_no = 1}, 
{AddVector(home_origin,{0, 4*home_block}), {250, button_height}, "LEADERBOARD", .page_no = 1}, 
{AddVector(home_origin,{0, 5*home_block}), {200, button_height}, "PROFILE", .page_no = 1}, 
{AddVector(home_origin,{0, 6*home_block}), {200, button_height}, "START", .page_no = 1}, 
{AddVector(home_origin,{0, 7*home_block}), {200, button_height}, "RESUME", .page_no = 1}};


void ButtonDraw(button btn);

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
            ButtonDraw(button_arr[i]);
        }
    }
    
}


void ButtonDraw(button btn)
{
    ChangeColor(red1);
    iRectangle(btn.origin.x, btn.origin.y, btn.dimension.x, btn.dimension.y);

    if(btn.active)
        iFilledRectangle(btn.origin.x, btn.origin.y, btn.dimension.x, btn.dimension.y);

    double text_X = btn.origin.x + (btn.dimension.x - strlen(btn.str)*font_size)/2;
    double text_Y = btn.origin.y + (btn.dimension.y - font_size)/2;
    
    if(text_X < 0 || text_Y < 0)
    {
        printf("Too small Button.\n");
        return ;
    }
    if(btn.active)
        ChangeColor(black);
    iText(text_X, text_Y, btn.str, GLUT_BITMAP_HELVETICA_18);
}