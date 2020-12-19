/* BISMILLAH
NO DREAM IS TOO BIG AND NO DREAMER IS TOO SMALL
THE WHITE WOLF 

Author: Asif Azad 
Start-Date: 07.12.2020
 */

#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

typedef struct
{
    double x, y;
}Vector;

Vector AddVector(Vector a, Vector b);
Vector SubVector(Vector a, Vector b);
int EqualVector(Vector a, Vector b);



//global variables
int page_no = 6, prompt_show = 0, pause = 0, sound_is_on = 1;
int screen_width = 1550, screen_height = 800;
int chicken_speed[] = {3, 5, 7};
int current_time_slot = 0;
char leaderboard_file[50] = "leaderboard_short.txt";




//HomePage Variables
#define GamePageNo 0
#define HomePageNo 1
#define LoginPageNo 2
#define SignUpPageNo 3
#define LoginInfoNo 4
#define LevelPageNo 5
#define IntroNo 6
#define LeaderboardNo 7
#define HelpPageNo 8
#define SettingsPageNo 9
#define ProfilePageNo 10
#define PromptNo -1




#include "iGraphics.h"
#include "GamePage.h"
#include "HomePage.h"

#define dbg(a) cout<<#a<<" ->->->-> "<<a<<"\n"


void ButtonActive(int x, int y)
{
	y = screen_height - y;
	for(int i = 0; i< sizeof(button_arr)/sizeof(button); i++)
	{
		button_arr[i].active = 0;
		if((button_arr[i].page_no == page_no || prompt_show == PromptNo )&& x >= button_arr[i].origin.x && x <= button_arr[i].origin.x + button_arr[i].dimension.x && y >= button_arr[i].origin.y && y <= button_arr[i].origin.y + button_arr[i].dimension.y)
			button_arr[i].active = 1;
	}
	/* printf("x: %d y: %d\n", x, y); */
}


void iDraw()
{
    //place your drawing codes here
    iClear();

	
	if(page_no == GamePageNo)
		GamePage();
	else if(page_no == HomePageNo)
		HomePage();
	else if(page_no == LoginPageNo)
		LoginPage();
	else if(page_no == SignUpPageNo)
		SignUp();
	else if(page_no == LoginInfoNo)
		LoginInfo();
	else if(page_no == LevelPageNo)
		LevelPage();
	else if(page_no == IntroNo)
		Intro();
	else if(page_no == LeaderboardNo)
		LeaderboardDraw();
	else if(page_no == HelpPageNo)
		HelpPage();
	else if(page_no == SettingsPageNo)
		SettingsPage();
	else if(page_no == ProfilePageNo)
		ProfilePage();

	if(prompt_show == PromptNo)
		Prompt();
	glutPassiveMotionFunc(ButtonActive);
	
}



/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
int prev_mx = 0, prev_my = 0;

void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here

	if(page_no == GamePageNo && mx >= game_origin.x && mx <= game_origin.x + game_dimension.x && my >= game_origin.y && my <= game_origin.y + game_dimension.y)
	{
		if(mx < prev_mx)
			BasketMove(-1);
		else if(mx > prev_mx)
			BasketMove(1);
	}

	prev_mx = mx;
	prev_my = my;
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(page_no == GamePageNo)
		{
			RightShift(mx, my);
			LeftShift(mx, my);
		}

		for(int i = 0; i< sizeof(placeholder_arr)/sizeof(placeholder_arr[0]); i++)
		{
			placeholder_arr[i].active = 0;
			if(page_no == placeholder_arr[i].page_no && mx >= placeholder_arr[i].origin.x && mx <= placeholder_arr[i].origin.x + placeholder_arr[i].dimension.x && my >= placeholder_arr[i].origin.y && my <= placeholder_arr[i].origin.y + placeholder_arr[i].dimension.y)
			{
				placeholder_arr[i].active = 1;
			}
		}

		for(int i = 0; i< sizeof(button_arr)/sizeof(button_arr[0]); i++)
		{
			if(i == 6 && !pause) //extra constraints for resume button in homepage
				continue;
			if(mx >= button_arr[i].origin.x && mx <= button_arr[i].origin.x + button_arr[i].dimension.x && my >= button_arr[i].origin.y && my <= button_arr[i].origin.y + button_arr[i].dimension.y)
			{
				if((button_arr[i].page_no == page_no && prompt_show != PromptNo) || (i == 16 && prompt_show == PromptNo))
				{
					/* PlaySound(TEXT("sounds\\button_press.wav"), NULL, SND_FILENAME|SND_SYNC); */	
					button_arr[i].function_pointer();
					break;
				}
			}			
		}

		if(page_no == SettingsPageNo)
		{
			if(mx >= 605 && mx <= 605 + 20 && my >= 505 && my <= 505 + 20)
				sound_is_on = 1;
			else if(mx >= 925 && mx <= 925 + 20 && my >= 505 && my <= 505 + 20)
				sound_is_on = 0;
			
			else if(mx >= 575 && mx <= 575 + 20 && my >= 355 && my <= 355+20)
			{
				current_time_slot = 0;
				strcpy(leaderboard_file,"images\\leaderboard_short.bmp");
			}
			else if(mx >= 765 && mx <= 765 + 20 && my >= 355 && my <= 355+20)
			{
				current_time_slot = 1;
				strcpy(leaderboard_file,"images\\leaderboard_mid.bmp");
			}
			else if(mx >= 955 && mx <= 955 + 20 && my >= 355 && my <= 355+20)
			{
				current_time_slot = 2;
				strcpy(leaderboard_file,"images\\leaderboard_long.bmp");				
			}
		}
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	for(int i = 0; i< sizeof(placeholder_arr)/sizeof(placeholder_arr[0]); i++)
	{
		if(page_no == placeholder_arr[i].page_no && placeholder_arr[i].active == 1)
		{
			placeholder_arr[i].input[placeholder_arr[i].next_input++] = key;
		}
	}

    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		if(page_no == GamePageNo)
			BasketMove(1);
		break;

	case GLUT_KEY_LEFT:
		if(page_no == GamePageNo)
			BasketMove(-1);
		break;

	case GLUT_KEY_F12:
		for(int i = 0; i< sizeof(placeholder_arr)/sizeof(placeholder_arr[0]); i++)
		{
			if(page_no == placeholder_arr[i].page_no && placeholder_arr[i].active == 1 && placeholder_arr[i].next_input)
			{
				placeholder_arr[i].input[--placeholder_arr[i].next_input] = '\0';
			}
		}

	default:
		break;
	}
}

int EqualVector(Vector a, Vector b)
{
    return (a.x == b.x && a.y == b.y);
}

Vector SubVector(Vector a, Vector b)
{
    return {a.x - b.x , a.y - b.y};
}

Vector AddVector(Vector a, Vector b)
{
    return {a.x + b.x, a.y + b.y};
}

void Introcng()
{
	page_no = LoginPageNo;
	iPauseTimer(1);
}

int main()
{
    //place your own initialization codes here.
	
	iSetTimer(1000, StopwatchUpdate); //No. 1 for stopwatch
	iPauseTimer(0);

	iSetTimer(5000, Introcng); //No 2 for intro

	PlaySound(TEXT("sounds\\intro.wav"), NULL, SND_ASYNC);
    iInitialize(screen_width, screen_height, "Murga!");
    return 0;
}
