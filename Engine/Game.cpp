 /****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (inhibitRight)
		{
		}
		else
		{
			vx = vx + 1;
			inhibitRight = true;
		}
	}
	else
	{
		inhibitRight = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (inhibitLeft)
		{
		}
		else
		{
			vx = vx - 1;
			inhibitLeft = true;
		}
	}
	else
	{
		inhibitLeft = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if (inhibitUp)
		{
		}
		else
		{
			vy = vy - 1;
			inhibitUp = true;
		}
	}
	else
	{
		inhibitUp = false;
	}

	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (inhibitDown)
		{
		}
		else
		{
			vy = vy + 1;
			inhibitDown = true;
		}
	}
	else
	{
		inhibitDown = false;
	}

	x_mobile = x_mobile + vx;
	y_mobile = y_mobile + vy;

	if (x_mobile + 5 >= gfx.ScreenWidth)
	{
		x_mobile = gfx.ScreenWidth - 6;
		vx = 0;
	}

	if (x_mobile - 5 < 0)
	{
		x_mobile = 5;
		vx = 0;
	}

	if (y_mobile + 5 >= gfx.ScreenHeight)
	{
		y_mobile = gfx.ScreenHeight - 6;
		vy = 0;
	}

	if (y_mobile - 5 < 0)
	{
		y_mobile = 5;
		vy = 0;
	}

	x_mobile = clampScreenX(x_mobile);
	y_mobile = clampScreenY(y_mobile);
	
	colliding = 
		OverlapTest(x_fixed0, y_fixed0, x_mobile, y_mobile) ||
		OverlapTest(x_fixed1, y_fixed1, x_mobile, y_mobile) ||
		OverlapTest(x_fixed2, y_fixed2, x_mobile, y_mobile) ||
		OverlapTest(x_fixed3, y_fixed3, x_mobile, y_mobile);

}

void Game::ComposeFrame()
{
	DrawBox(x_fixed0, y_fixed0, 0, 255, 0);
	DrawBox(x_fixed1, y_fixed1, 0, 255, 0);
	DrawBox(x_fixed2, y_fixed2, 0, 255, 0);
	DrawBox(x_fixed3, y_fixed3, 0, 255, 0);


	if (colliding)
	{
		DrawBox(x_mobile, y_mobile, 255, 0, 0);
	}
	else
	{
		DrawBox(x_mobile, y_mobile, 255, 255, 255);
	}
}
	
void Game::DrawBox(int x, int y, int r, int g, int b)
{
		gfx.PutPixel(x + 5, y - 5, r, g, b);
		gfx.PutPixel(x + 5, y - 4, r, g, b);
		gfx.PutPixel(x + 5, y - 3, r, g, b);
		gfx.PutPixel(x + 5, y + 3, r, g, b);
		gfx.PutPixel(x + 5, y + 4, r, g, b);
		gfx.PutPixel(x + 5, y + 5, r, g, b);
		gfx.PutPixel(x + 4, y - 5, r, g, b);
		gfx.PutPixel(x + 3, y - 5, r, g, b);
		gfx.PutPixel(x - 3, y - 5, r, g, b);
		gfx.PutPixel(x - 4, y - 5, r, g, b);
		gfx.PutPixel(x - 5, y - 5, r, g, b);
		gfx.PutPixel(x - 5, y - 4, r, g, b);
		gfx.PutPixel(x - 5, y - 3, r, g, b);
		gfx.PutPixel(x - 5, y + 3, r, g, b);
		gfx.PutPixel(x - 5, y + 4, r, g, b);
		gfx.PutPixel(x - 5, y + 5, r, g, b);
		gfx.PutPixel(x - 4, y + 5, r, g, b);
		gfx.PutPixel(x - 3, y + 5, r, g, b);
		gfx.PutPixel(x + 3, y + 5, r, g, b);
		gfx.PutPixel(x + 4, y + 5, r, g, b);
}

 bool Game::OverlapTest(int box0x, int box0y, int box1x, int box1y)
{
	 const int   left_box0 = box0x - 5;
	 const int  right_box0 = box0x + 5;
	 const int    top_box0 = box0y - 5;
	 const int bottom_box0 = box0y + 5;

	 const int   left_box1 = box1x - 5;
	 const int  right_box1 = box1x + 5;
	 const int    top_box1 = box1y - 5;
	 const int bottom_box1 = box1y + 5;

	 return
			left_box0 <= right_box1 &&
			right_box0 >= left_box1 &&
			top_box0 <= bottom_box1 &&
			bottom_box0 >= top_box1;

}

 int Game::clampScreenX(int x)
 {
	 const int left = x - 5;
	 const int right = x + 5;
		if (left < 0)
		{
			return 5;
		}
		else if (right >= gfx.ScreenWidth) 
		{ 
			return gfx.ScreenWidth - 6;
		}
		else
		{
			return x;
		}
 }

 int Game::clampScreenY(int y)
 {
	 const int top = y - 5;
	 const int bottom = y + 5;
	 if(top < 0)
	 {
		 return 5; 
	 }
	 else if(bottom >= gfx.ScreenHeight)
	 {
		 return gfx.ScreenHeight - 6;
	 }
	 else
	 {
		 return y;
	 }
 }
