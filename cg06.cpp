#include<graphics.h>

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    
    setcolor(2);
    circle(100,200,50);

    delay(1000);
    
    return 0;
}
