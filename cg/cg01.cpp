#include <iostream>
#include <graphics.h>
#include <math.h>

using namespace std;

float mod(float n)
{
	return (n < 0 ? -1 * n : n);
}

float sign(float n)
{
	return (n < 0 ? -1 : 1);
}

class Lines
{
	public:
		void draw_line(int, int, int, int);
		void draw_line(float, float, float, float);
};

void Lines::draw_line(int x0, int y0, int x1, int y1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	
	int length = mod(dx) >= mod(dy) ? mod(dx) : mod(dy);
		
	dx /= length;
	dy /= length;
	
	float x = x0 + (0.5 * sign(dx));
	float y = y0 + (0.5 * sign(dy));
	
	int gd = DETECT, gm; 
	
    initgraph (&gd, &gm, NULL); 
	
	for(int i = 0; i <= length; i++)
	{
		putpixel(floor(x), floor(y), WHITE);
		x += dx;
		y += dy;
		delay(100);
	}
	
	delay(2000);
	closegraph();
}

void Lines::draw_line(float x1, float y1, float x2, float y2)
{
	float m_new = 2 * (y2 - y1); 
	float slope_error_new = m_new - (x2 - x1); 
	
	int gd = DETECT, gm; 
	
    initgraph (&gd, &gm, NULL); 
    
	for (float x = x1, y = y1; x <= x2; x++) 
	{ 
		putpixel(floor(x), floor(y), WHITE);

		// Add slope to increment angle formed 
		slope_error_new += m_new; 

		// Slope error reached limit, time to 
		// increment y and update slope error. 
		if (slope_error_new >= 0) 
		{ 
		 y++; 
		 slope_error_new  -= 2 * (x2 - x1); 
		} 
		delay(100);
	}
	
	delay(2000);
	closegraph();
}

int main()
{	
	Lines L;

	int ch, x0, y0, x1, y1;
	
	do{
		cout << "Choose the algorithm to draw line: \n";
		cout << "1. Digital Differential Analyzer\n";
		cout << "2. Bresenham's Line Generation\n";	
		cout << "3. Exit\n";
		cout << "Enter your choice: ";
		cin >> ch;
		cout << endl;
		
		if(ch == 1 || ch == 2)
		{		
			cout << "Enter the starting point:\n";
			cout << "x0: ";
			cin >> x0;
			cout << "y0: ";
			cin >> y0;
	
			cout << "Enter the end point:\n";
			cout << "x1: ";
			cin >> x1;
			cout << "y1: ";
			cin >> y1;
		}
		
		switch(ch)
		{
			case 1:
				L.draw_line(x0, y0, x1, y1);
				break;
			case 2:
				L.draw_line(float(x0), float(y0), float(x1), float(y1));
				break;
			case 3:
				cout << "Exited\n";
				break;
			default:
				cout << "Enter your choice betweent 1 - 3, only\n\n";
		}
	}while(ch != 3);
	
	return 0;
}

