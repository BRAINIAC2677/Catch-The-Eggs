/* BISMILLAH
NO DREAM IS TOO BIG AND NO DREAMER IS TOO SMALL
THE WHITE WOLF 

Author: Asif Azad 
CSE 1-1 TERM PROJECT
Start-Date: 07.12.2020
 */

#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

typedef struct
{
	double x, y;
} Vector;

Vector AddVector(Vector a, Vector b);
Vector SubVector(Vector a, Vector b);
int EqualVector(Vector a, Vector b);

//global variables
int page_no = 6;
int popup_show = 0;
int pause = 0;
int sound_is_on = 1;
int screen_width = 1550, screen_height = 800;
int chicken_speed[] = {3, 4, 6};
int game_time_category = 0;							 //*0 for 1 min, 1 for 2 min, 2 for 3 min
char leaderboard_file[50] = "leaderboard_short.txt"; //*3 different leaderboard files for 3 different game_time_category

#define GamePageNo 0
#define HomePageNo 1
#define LoginPageNo 2
#define SignUpPageNo 3
#define LoginInfoPageNo 4
#define LevelPageNo 5
#define IntroPageNo 6
#define LeaderboardPageNo 7
#define HelpPageNo 8
#define SettingsPageNo 9
#define ProfilePageNo 10
#define PopupNo -1

#include "iGraphics.h"
#include "GamePage.h"
#include "HomePage.h"

#define dbg(a) cout << #a << " ->->->-> " << a << "\n"

void ButtonActive(int x, int y)
{
	y = screen_height - y;
	for (int i = 0; i < sizeof(button_arr) / sizeof(button); i++)
	{
		button_arr[i].active = 0;
		if ((button_arr[i].page_no == page_no || popup_show == PopupNo) && x >= button_arr[i].origin.x && x <= button_arr[i].origin.x + button_arr[i].dimension.x && y >= button_arr[i].origin.y && y <= button_arr[i].origin.y + button_arr[i].dimension.y)
			button_arr[i].active = 1;
	}
}

void iDraw()
{
	iClear();

	if (page_no == GamePageNo)
		GamePage();
	else if (page_no == HomePageNo)
		HomePage();
	else if (page_no == LoginPageNo)
		LoginPage();
	else if (page_no == SignUpPageNo)
		SignUp();
	else if (page_no == LoginInfoPageNo)
		LoginInfo();
	else if (page_no == LevelPageNo)
		LevelPage();
	else if (page_no == IntroPageNo)
		Intro();
	else if (page_no == LeaderboardPageNo)
		LeaderboardDraw();
	else if (page_no == HelpPageNo)
		HelpPage();
	else if (page_no == SettingsPageNo)
		SettingsPage();
	else if (page_no == ProfilePageNo)
		ProfilePage();

	if (popup_show == PopupNo)
		Prompt();
	glutPassiveMotionFunc(ButtonActive);
}

int prev_mx = 0, prev_my = 0;

void iMouseMove(int mx, int my)
{

	if (page_no == GamePageNo && mx >= game_origin.x && mx <= game_origin.x + game_dimension.x && my >= game_origin.y && my <= game_origin.y + game_dimension.y)
	{
		if (mx < prev_mx)
			BasketMove(-1);
		else if (mx > prev_mx)
			BasketMove(1);
	}

	prev_mx = mx;
	prev_my = my;
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

		for (int i = 0; i < sizeof(placeholder_arr) / sizeof(placeholder_arr[0]); i++)
		{
			placeholder_arr[i].active = 0;
			if (page_no == placeholder_arr[i].page_no && mx >= placeholder_arr[i].origin.x && mx <= placeholder_arr[i].origin.x + placeholder_arr[i].dimension.x && my >= placeholder_arr[i].origin.y && my <= placeholder_arr[i].origin.y + placeholder_arr[i].dimension.y)
			{
				placeholder_arr[i].active = 1;
			}
		}

		for (int i = 0; i < sizeof(button_arr) / sizeof(button_arr[0]); i++)
		{
			if (i == 6 && !pause) //extra constraints for resume button in homepage
				continue;
			if (mx >= button_arr[i].origin.x && mx <= button_arr[i].origin.x + button_arr[i].dimension.x && my >= button_arr[i].origin.y && my <= button_arr[i].origin.y + button_arr[i].dimension.y)
			{
				if ((button_arr[i].page_no == page_no && popup_show != PopupNo) || (i == 16 && popup_show == PopupNo))
				{
					button_arr[i].function_pointer();
					break;
				}
			}
		}

		if (page_no == SettingsPageNo)
		{
			if (mx >= 605 && mx <= 605 + 20 && my >= 505 && my <= 505 + 20)
			{
				sound_is_on = 1;
				PlaySound(TEXT("sounds\\twinkle.wav"), NULL, SND_LOOP | SND_ASYNC);
			}
			else if (mx >= 925 && mx <= 925 + 20 && my >= 505 && my <= 505 + 20)
			{
				sound_is_on = 0;
				PlaySound(NULL, NULL, 0);
			}

			else if (mx >= 575 && mx <= 575 + 20 && my >= 355 && my <= 355 + 20)
			{
				game_time_category = 0;
				strcpy(leaderboard_file, "leaderboard_short.txt");
			}
			else if (mx >= 765 && mx <= 765 + 20 && my >= 355 && my <= 355 + 20)
			{
				game_time_category = 1;
				strcpy(leaderboard_file, "leaderboard_mid.txt");
			}
			else if (mx >= 955 && mx <= 955 + 20 && my >= 355 && my <= 355 + 20)
			{
				game_time_category = 2;
				strcpy(leaderboard_file, "leaderboard_long.txt");
			}
		}
	}
}

void iKeyboard(unsigned char key)
{
	for (int i = 0; i < sizeof(placeholder_arr) / sizeof(placeholder_arr[0]); i++)
	{
		if (page_no == placeholder_arr[i].page_no && placeholder_arr[i].active == 1)
		{
			placeholder_arr[i].input[placeholder_arr[i].next_input++] = key;
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		if (page_no == GamePageNo)
			BasketMove(1);
		break;

	case GLUT_KEY_LEFT:
		if (page_no == GamePageNo)
			BasketMove(-1);
		break;

	case GLUT_KEY_F12:
		for (int i = 0; i < sizeof(placeholder_arr) / sizeof(placeholder_arr[0]); i++)
		{
			if (page_no == placeholder_arr[i].page_no && placeholder_arr[i].active == 1 && placeholder_arr[i].next_input)
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
	return {a.x - b.x, a.y - b.y};
}

Vector AddVector(Vector a, Vector b)
{
	return {a.x + b.x, a.y + b.y};
}

void Introcng()
{
	page_no = LoginPageNo;
	iPauseTimer(1);
	if (sound_is_on)
		PlaySound(TEXT("sounds\\twinkle.wav"), NULL, SND_LOOP | SND_ASYNC);
}

int main()
{

	iSetTimer(1000, StopwatchUpdate); //No. 1 for stopwatch
	iPauseTimer(0);

	iSetTimer(5000, Introcng); //No 2 for intro

	PlaySound(TEXT("sounds\\intro.wav"), NULL, SND_ASYNC);
	iInitialize(screen_width, screen_height, "Catch The Eggs!");
	return 0;
}
