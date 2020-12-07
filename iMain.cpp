/* BISMILLAH
NO DREAM IS TOO BIG AND NO DREAMER IS TOO SMALL
THE WHITE WOLF 

Author: Asif Azad 
Start-Date: 07.12.2020
 */

#include<bits/stdc++.h>
using namespace std;

#include "iGraphics.h"
#include "GamePage.h"

#define dbg(a) cout<<#a<<" ->->->-> "<<a<<"\n"
#define GamePageNo 0

int page_no = 0;
int screen_width = 1550, screen_height = 800;

void iDraw()
{
    //place your drawing codes here
    iClear();
	
	if(page_no == GamePageNo)
		GamePage();
}



/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
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
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

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

	default:
		break;
	}
}



int main()
{
    //place your own initialization codes here.
    iInitialize(screen_width, screen_height, "Murga!");
    return 0;
}
