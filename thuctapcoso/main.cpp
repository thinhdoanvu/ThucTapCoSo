#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#define MAX 100
#include <stdbool.h>
#include<Math.h>
#define MAX_POINTS 10

// Khai bao protype
void CUI_init();
void click();
void mousepolygon();
void mouseCircle();
void mouseElip();
void keyboard();
int is_run=0;
void drawPolygon();
void drawCircle();
void drawEllipse();
void reset();
void exit();
void fillPolygon();
void fillCircle();
void fillElip();
void yellow();
void green();
void red();
void magenta();
void choosecolor();

// khai bao bien cuc bo
int sodinh;//sodinh(so phan tu can sap xep)
FILE *fp; //file
int enable_mouse=1;
int maxPoints = 4;
bool isPolygonClicked = false; 
bool isCricleClicked = false;
bool isElipClicked = false;
struct toado{
	int x;
	int y;
};
struct toado td[MAX]; //moi td la 1 kieu toado(x,y,value)
//ve 
void CUI_init(){
	setcolor(WHITE);
	setlinestyle(0,1,3);//setlinestyle(int linestyle, unsigned pattern, int thickness)
	rectangle(10,5,640,310);
	//load file button
	setfillstyle(SOLID_FILL, LIGHTGRAY); // Thi?t l?p fill style và màu s?c d? làm m?
    setcolor(LIGHTGRAY);
	rectangle(660,10,760,50);
	settextstyle(2,0,7);
	outtextxy(670,20,"Mouse\n");
	//Keyboard button y=y+60 for top and bottom
	setfillstyle(SOLID_FILL, LIGHTGRAY); // Thi?t l?p fill style và màu s?c d? làm m?
    setcolor(LIGHTGRAY);
	rectangle(660,70,760,110);
	settextstyle(2,0,7);
	outtextxy(670,80,"Keyboard\n");
	//Reset button y=y+60 for top and bottom
	setcolor(WHITE);
	rectangle(660,130,760,170);
	settextstyle(2,0,7);
	outtextxy(670,140,"Flood Fill\n");
	//polygon button y=y+60 for top and bottom
	rectangle(660,190,760,230);
	settextstyle(2,0,7);
	outtextxy(670,200,"Reset\n");
	//polygon button y=y+60 for top and bottom
	rectangle(660,250,760,290);
	settextstyle(2,0,7);
	outtextxy(670,260,"Exit\n");
	//polygon 
	rectangle(20,320,110,360);
	settextstyle(2,0,7);
	outtextxy(30,330,"Polygon\n");
	//polygon button x=x+210 
	rectangle(220,320,310,360);
	settextstyle(2,0,7);
	outtextxy(230,330,"Cricle\n");
	//Exit button x=x+210 
	rectangle(420,320,510,360);
	settextstyle(2,0,7);
	outtextxy(430,330,"Ellipse\n");
	
   	// Set fill style and color
   setfillstyle(SOLID_FILL, YELLOW);
   setcolor(YELLOW);
   // Draw and fill the rectangle
   rectangle(20, 390, 110, 430);
   bar(21, 391, 109, 429);
	// Set fill style and color
   setfillstyle(SOLID_FILL, GREEN);
   setcolor(GREEN);
   // Draw and fill the rectangle
   rectangle(170, 390, 260, 430);
   bar(171, 391, 259, 429);	
	// Set fill style and color
   setfillstyle(SOLID_FILL, RED);
   setcolor(RED);
   // Draw and fill the rectangle
   rectangle(320, 390, 410, 430);
   bar(321, 391, 409, 429);	
   // Set fill style and color
   setfillstyle(SOLID_FILL, MAGENTA);
   setcolor(MAGENTA);
   // Draw and fill the rectangle
   rectangle(470, 390, 560, 430);
   bar(471, 391, 559, 429);	
   
   	// Set fill style and color
   setfillstyle(SOLID_FILL, CYAN);
   setcolor(CYAN);
   // Draw and fill the rectangle
   rectangle(20, 440, 110, 480);
   bar(21, 441, 109, 479);
	// Set fill style and color
   setfillstyle(SOLID_FILL, DARKGRAY);
   setcolor(DARKGRAY);
   // Draw and fill the rectangle
   rectangle(170, 440, 260, 480);
   bar(171, 441, 259, 479);	
	// Set fill style and color
   setfillstyle(SOLID_FILL, LIGHTGREEN);
   setcolor(LIGHTGREEN);
   // Draw and fill the rectangle
   rectangle(320, 440, 410, 480);
   bar(321, 441, 409, 479);	
   // Set fill style and color
   setfillstyle(SOLID_FILL, WHITE);
   setcolor(WHITE);
   // Draw and fill the rectangle
   rectangle(470, 440, 560, 480);
   bar(471, 441, 559, 479);	
}

//using mouse to select functions loadfile, keyboard, ...
void click(){
    int x_mouse, y_mouse;
    bool isShapeSelected = false;
    bool isMouseClicked = false;
    bool isKeyboardClicked = false;
    int clickCount = 0;
    while (1) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x_mouse, y_mouse);
            if (x_mouse > 660 && x_mouse < 760 && y_mouse > 10 && y_mouse < 50) { 
			    if (!isMouseClicked) { 
			        setfillstyle(SOLID_FILL, WHITE);
			        setcolor(WHITE);
			        rectangle(660, 10, 760, 50);
        			outtextxy(670, 20, "Mouse\n");
			        isMouseClicked = true;
			    }
			    else {
			    	setcolor(WHITE);
			        rectangle(660, 10, 760, 50);
        			outtextxy(670, 20, "Mouse\n");
			        if (isPolygonClicked) {
			        	printf("Dung chuot...\n");
			            mousepolygon();
			            drawPolygon();
			        } 
			        else if (isCricleClicked) {
			        	printf("Dung chuot...\n");
			            mouseCircle();
			            drawCircle();
			        }
			        else if (isElipClicked) {
			        	printf("Dung chuot...\n");
			            mouseElip();
			            drawEllipse();
			        }
			        clickCount = 0;
			    }
			}
			else {
				setcolor(RED);
			    rectangle(660, 10, 760, 50);
        		outtextxy(670, 20, "Mouse\n");
			    setfillstyle(SOLID_FILL, LIGHTGRAY); 
	    		setcolor(LIGHTGRAY);
			    rectangle(20,320,110,360);
				settextstyle(2,0,7);
				outtextxy(30,330,"Polygon\n");
				//polygon button x=x+210 
				rectangle(220,320,310,360);
				settextstyle(2,0,7);
				outtextxy(230,330,"Cricle\n");
				//Exit button x=x+210 
				rectangle(420,320,510,360);
				settextstyle(2,0,7);
				outtextxy(430,330,"Ellipse\n");
			}
            // Nut "Keyboard"
			if (x_mouse > 660 && x_mouse < 760 && y_mouse > 70 && y_mouse < 110) {
		        if (!isKeyboardClicked) {
		            setfillstyle(SOLID_FILL, WHITE);
		            setcolor(WHITE);
		            rectangle(660, 70, 760, 110);
		            outtextxy(670, 80, "Keyboard\n");
		            isKeyboardClicked = true;
		            clickCount = 0;
		        } else {
		            setcolor(WHITE);
		            rectangle(660, 70, 760, 110);
		            outtextxy(670, 80, "Keyboard\n");
		            if (isPolygonClicked) {
		            	printf("Ban phim..\n");
		                keyboard();
		                drawPolygon();
		            } else if (isCricleClicked) {
		            	printf("Ban phim..\n");
		                keyboard();
		                drawCircle();
		            } else if (isElipClicked) {
		            	printf("Ban phim..\n");
		                keyboard();
		                drawEllipse();
		            }
		            clickCount = 0;
		        }
		    } else {
		        setcolor(RED);
		        rectangle(660, 70, 760, 110);
		        outtextxy(670, 80, "Keyboard\n");
		        setfillstyle(SOLID_FILL, LIGHTGRAY); 
		        setcolor(LIGHTGRAY);
		        rectangle(20, 320, 110, 360);
		        settextstyle(2, 0, 7);
		        outtextxy(30, 330, "Polygon\n");
		        //polygon button x = x + 210 
		        rectangle(220, 320, 310, 360);
		        settextstyle(2, 0, 7);
		        outtextxy(230, 330, "Circle\n");
		        //Exit button x = x + 210 
		        rectangle(420, 320, 510, 360);
		        settextstyle(2, 0, 7);
		        outtextxy(430, 330, "Ellipse\n");
		    }
            
			if (x_mouse > 660 && x_mouse < 760 && y_mouse > 130 && y_mouse < 170) { 
                if (isPolygonClicked) {
                	printf("Chon mau...\n");
	                fillPolygon(); 
                } 
                else if (isCricleClicked){
                	printf("Chon mau...\n");
                	fillCircle();
				}
				else if(isElipClicked){
					printf("Chon mau...\n");
                	fillElip(); 
				}
            } 
            
            if (x_mouse > 660 && x_mouse < 760 && y_mouse > 190 && y_mouse < 230) {
                isPolygonClicked = false;
			    isCricleClicked = false;
			    isElipClicked = false;
			    sodinh = 0;
			    cleardevice();
			    CUI_init();
            }
			
			if (x_mouse > 660 && x_mouse < 760 && y_mouse > 250 && y_mouse < 290) {
                exit(0);
            }            
            
            // N?t "Polygon"
			if (x_mouse > 20 && x_mouse < 110 && y_mouse > 320 && y_mouse < 360) { 
                printf("Ve da giac\n");
                printf("Chon du lieu chuot hay ban phim\n");
                isPolygonClicked = true;
            } 
            // N?t "Cricle"
			if (x_mouse > 220 && x_mouse < 310 && y_mouse > 320 && y_mouse < 360) { 
                printf("Ve hinh tron\n");
                printf("Chon du lieu chuot hay ban phim\n");
                isCricleClicked = true;
            }
            // N?t "Elip"
			if (x_mouse > 420 && x_mouse < 510 && y_mouse > 320 && y_mouse < 360) { 
                printf("Ve hinh elip.\n");
                printf("Chon du lieu chuot hay ban phim\n");
                isElipClicked = true;
            }
        }
        delay(100);
    }
}

// xu li
//chuot
void mousepolygon() {
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x >= 10 && x <= 640 && y >= 5 && y <= 310) {
                td[sodinh].x = x;
                td[sodinh].y = y;
                sodinh++;
                putpixel(x, y, WHITE);

                if (sodinh >= 3 ) {
                    drawPolygon();
                }
            }
            else{
            	click();
			}
        }
        else if (kbhit()) {
            break;
        }
    }
}

void mouseCircle() {
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x >= 10 && x <= 640 && y >= 5 && y <= 310) {
                td[sodinh].x = x;
	            td[sodinh].y = y;
	            sodinh++;
	            putpixel(x, y, WHITE);
	            if (sodinh == 2) {
	                drawCircle();
	                break;
	            }
            }
            else{
            	click();
			}
        }
        else if (kbhit()) {
            break;
        }
    }
}

void mouseElip(){
	 while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x >= 10 && x <= 640 && y >= 5 && y <= 310) {
                td[sodinh].x = x;
	            td[sodinh].y = y;
	            sodinh++;
	
	            putpixel(x, y, WHITE);
	
	            if (sodinh == 2) {
	                drawEllipse();
	                break;
	            }
            }
            else{
            	click();
			}
        }
        else if (kbhit()) {
            break;
        }
    }
}

//keyboard();
void keyboard(){
	printf("Nhap so dinh: ");
    scanf("%d", &sodinh);
    printf("Nhap toa do\n");
    for (int i = 0; i < sodinh; i++) {
        printf("Toa do %d: ", i + 1);
        scanf("%d %d", &td[i].x, &td[i].y);
    }
}


//vehinhdagia
void drawPolygon(){
	if (sodinh < 3) {
        printf("So dinh khong hop le\n");
        return;
    }
    setcolor(WHITE);
    delay(800); 
    for (int i = 0; i < sodinh - 1; i++) {
    	delay(800); 
        line(td[i].x, td[i].y, td[i + 1].x, td[i + 1].y);
    }
    delay(800); 
    line(td[sodinh - 1].x, td[sodinh - 1].y, td[0].x, td[0].y);
}
//tomaudagiac
bool isInsidePolygon(int x, int y) {
    int i, j;
    bool inside = false;
    for (i = 0, j = sodinh - 1; i < sodinh; j = i++) {
        if (((td[i].y > y) != (td[j].y > y)) &&
            (x < (td[j].x - td[i].x) * (y - td[i].y) / (td[j].y - td[i].y) + td[i].x))
            inside = !inside;
    }
    return inside;
}
void fillPolygon() {
    bool isColorChosen = false;
    bool isFilled = false;
    while (!kbhit() && !isFilled) {
        if (!isColorChosen) {
            choosecolor();
            isColorChosen = true;
        }
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (isInsidePolygon(x, y)) {
                floodfill(x, y, WHITE);
                isFilled = true;
            }
        }
    }
}
//ve hinh tron
void drawCircle() {
    if (sodinh != 2) {
        printf("So dinh khong hop le\n");
        return;
    }
    setcolor(WHITE);
    int r = sqrt(pow(td[1].x - td[0].x, 2) + pow(td[1].y - td[0].y, 2));
    int x = 0;
    int y = r;
    int p = 3 - 2 * r; 
    while (x <= y) {
        putpixel(td[0].x + x, td[0].y + y, WHITE);
        putpixel(td[0].x - x, td[0].y + y, WHITE);
        putpixel(td[0].x - x, td[0].y - y, WHITE);
        putpixel(td[0].x + x, td[0].y - y, WHITE);
        putpixel(td[0].x + y, td[0].y + x, WHITE);
        putpixel(td[0].x - y, td[0].y + x, WHITE);
        putpixel(td[0].x + y, td[0].y - x, WHITE);
        putpixel(td[0].x - y, td[0].y - x, WHITE);
        if (p < 0) { 
            p += 4 * x + 6; 
        } else {
            p += 4 * (x - y) + 10; 
            y--;
        }
        x++;
        delay(50); 
    }
}
void fillCircle() {
	bool isColorChosen = false;
    bool isFilled = false;
    while (!kbhit()) {
    	if (!isColorChosen) {
            choosecolor();
            isColorChosen = true;
        }
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int clickX, clickY;
            int r = sqrt(pow(td[1].x - td[0].x, 2) + pow(td[1].y - td[0].y, 2));
            int x = td[0].x;
            int y = td[0].y;
            getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
            if (pow(clickX - x, 2) + pow(clickY - y, 2) <= pow(r, 2)) {
                fillellipse(x, y, r, r);  
                isFilled = true;
                break;
            }
        }
    }
}

// Vehinhellip
void drawEllipse() {
    if (sodinh != 2) {
        printf("so dinh khong hop le\n");
        return;
    }
    setcolor(WHITE);
    int a = abs(td[1].x - td[0].x);
    int b = abs(td[1].y - td[0].y);
    int x = 0;
    int y = b;
    int p = pow(b, 2) - pow(a, 2) * b + pow(a, 2) / 4;
    while (2 * pow(b, 2) * x < 2 * pow(a, 2) * y) {
        putpixel(td[0].x + x, td[0].y + y, WHITE);
        putpixel(td[0].x - x, td[0].y + y, WHITE);
        putpixel(td[0].x - x, td[0].y - y, WHITE);
        putpixel(td[0].x + x, td[0].y - y, WHITE);
        if (p < 0) {
            x++;
            p += 2 * pow(b, 2) * x + pow(b, 2);
        } else {
            x++;
            y--;
            p += 2 * pow(b, 2) * x - 2 * pow(a, 2) * y + pow(b, 2);
        }
    }
    p = pow(b, 2) * pow((x + 0.5), 2) + pow(a, 2) * pow((y - 1), 2) - pow(a, 2) * pow(b, 2);
    while (y >= 0) {
        putpixel(td[0].x + x, td[0].y + y, WHITE);
        putpixel(td[0].x - x, td[0].y + y, WHITE);
        putpixel(td[0].x - x, td[0].y - y, WHITE);
        putpixel(td[0].x + x, td[0].y - y, WHITE);
        if (p > 0) {
            y--;
            p -= 2 * pow(a, 2) * y + pow(a, 2);
        } else {
            x++;
            y--;
            p += 2 * pow(b, 2) * x - 2 * pow(a, 2) * y + pow(a, 2);
        }
        delay(50); 
    }
    
}
void fillElip() {
	bool isColorChosen = false;
    bool isFilled = false;
    int centerX = td[0].x;
    int centerY = td[0].y;
    int radiusX = abs(td[1].x - td[0].x);
    int radiusY = abs(td[1].y - td[0].y);
    while (!kbhit()) {
    	if (!isColorChosen) {
            choosecolor();
            isColorChosen = true;
        }
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int clickX, clickY;
            getmouseclick(WM_LBUTTONDOWN, clickX, clickY);
            int dx = clickX - centerX;
            int dy = clickY - centerY;
            float value = (dx * dx) / (radiusX * radiusX) + (dy * dy) / (radiusY * radiusY);
            if (value <= 1) {
                fillellipse(centerX, centerY, radiusX, radiusY);
                isFilled = true;
            }
            break;
        }
    }
}
//mau
void yellow(){
	setfillstyle(SOLID_FILL, YELLOW); 
}
void green(){
	setfillstyle(SOLID_FILL, GREEN);
}
void red(){
	setfillstyle(SOLID_FILL, RED);
}
void magenta(){
	setfillstyle(SOLID_FILL, MAGENTA);
}
void cyan(){
	setfillstyle(SOLID_FILL, CYAN);
}
void darkgray(){
	setfillstyle(SOLID_FILL, DARKGRAY);
}
void lightgreen(){
	setfillstyle(SOLID_FILL, LIGHTGREEN);
}
void white(){
	setfillstyle(SOLID_FILL, WHITE);
}

void choosecolor() {
    int x_mouse, y_mouse;
    bool colorChosen = false; 
    while (!kbhit() && !colorChosen) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x_mouse, y_mouse);
            if (x_mouse > 20 && x_mouse < 110 && y_mouse > 390 && y_mouse < 430) {
                yellow();
                colorChosen = true;
            } else if (x_mouse > 170 && x_mouse < 260 && y_mouse > 390 && y_mouse < 430) {
                green();
                colorChosen = true;
            } else if (x_mouse > 320 && x_mouse < 410 && y_mouse > 390 && y_mouse < 430) {
                red();
                colorChosen = true;
            } else if (x_mouse > 470 && x_mouse < 560 && y_mouse > 390 && y_mouse < 430) {
                magenta();
                colorChosen = true;
            } else if (x_mouse > 20 && x_mouse < 110 && y_mouse > 440 && y_mouse < 480) {
                cyan();
                colorChosen = true;
            }  else if (x_mouse > 170 && x_mouse < 260 && y_mouse > 440 && y_mouse < 480) {
                darkgray();
                colorChosen = true;
            }  else if (x_mouse > 320 && x_mouse < 410 && y_mouse > 440 && y_mouse < 480) {
                lightgreen();
                colorChosen = true;
            }  else if (x_mouse > 470 && x_mouse < 560 && y_mouse > 440 && y_mouse < 480) {
                white();
                colorChosen = true;
            }
        }
    }
}

int main(){
	initwindow(800,500);
	CUI_init();
	//dung chuot
	click();
	getch();
}
