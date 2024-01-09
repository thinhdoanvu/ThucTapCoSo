#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#define MAX 100
#define round(a) ((int)(a+0.5))
#define INPUT "xentia.inp"
#include<iostream>
using namespace std;

//Khai bao protype
//Reset data:
void resetAll();
//Giao dien chinh:
void GUI();
void clickmouse();
//Code 
void LiangBarsky( int xmin, int ymin, int xmax, int ymax);
void hoandoi();
void addpointwd();
void Cohen_Sutherland();
//Giao dien load file
void readfile();
//Giao dien keyboard
void MenuXenTia();
void KhoiTao();
void keyboard(); 
//Giao dien Graphic
void Graphic();

//Khai bao bien toan cuc
FILE *fp;// file
struct Button
{
    int x1, y1, x2, y2;
};

struct point {
	int x,y;
};

int color = 0;
int n=2;
int n1 = 0 ;
int xmin, xmax,ymin,ymax;

point p1, p2;
point pt[2];
point poly[20];
point poly1[20];
point clip[4];
int code1[10], code2[10];
int tong1, tong2;
int temp=0,temp1=0,temp2=0, temp3 = 0;

//----------------------------------------------------------Reset toan bo du lieu--------------
void resetAll(){
	cleardevice();
	GUI();
}
//-----------------------------------------------------------Khai báo các kieu button-----------
void bt_color(Button bt, int color_fill)
{
	setlinestyle(1,2,2);
	setfillstyle(1,color_fill);
    bar(bt.x1, bt.y1, bt.x2, bt.y2);
}
//-----Kieem tra xem 
bool check_button(Button bt,point p)
{
	   if(bt.x1<=p.x && bt.y1<=p.y&& bt.x2>=p.x&& bt.y2>=p.y) 
	      return true;
	   return false;                   
}

// 
void button2(Button bt, int color_fill)
{
    setcolor(color_fill);
    setlinestyle(2,3,4);
    rectangle(bt.x1, bt.y1, bt.x2, bt.y2);
    
}

//
void button(Button bt, int color_fill)
{

	setlinestyle(0,0,2);
    setfillstyle(1,color_fill);
    setcolor(15);
    rectangle(bt.x1, bt.y1, bt.x2, bt.y2);
}
//------------Button ve doan thang-------------
void button_line(Button bt, int color_fill, int color_line)
{
	button(bt, color_fill);
    setcolor(color_line);
    line((bt.x2-bt.x1)/5*2, (bt.y2-bt.y1)/5+bt.y1, (bt.x2-bt.x1), (bt.y2-bt.y1)/5*4+bt.y1);
    
}
//----------Button nhan code Liang------------
void button_liang(Button bt, int color_fill, int color_line)
{
	button(bt, color_fill);
    setcolor(color_line);
    line(bt.x1, bt.y1, bt.x2, bt.y2);
    line(bt.x1, bt.y2, bt.x2, bt.y1);
}
 
 //----------Button nhan code Cohen---------------
void button_cohen(Button bt, int color_fill, int color_line)
{
    button(bt, color_fill);
    settextjustify(1, 1);
    setfillstyle(1,color_line);
    int space = 10;
    line(bt.x1 + space, bt.y1 + 2*space, bt.x2 - 2*space, bt.y1 + 2*space);
    line(bt.x1 + 2*space, bt.y2 - 2*space, bt.x2 - space, bt.y2 - 2*space);
    line(bt.x1 + 2*space, bt.y1 + space, bt.x1 + 2*space, bt.y2 - 2*space);
    line(bt.x2 - 2*space, bt.y1 + 2*space, bt.x2 - 2*space, bt.y2 - space);
    
}
 
//-----------------Button xoa-------------------
void button_del(Button bt, int color_fill, int color_line)
{
    button(bt, color_fill);
    settextjustify(1, 1);
    setfillstyle(1,color_line);
    bar(bt.x1 + (bt.x2-bt.x1)/4, bt.y1 + (bt.y2-bt.y1)/4, bt.x1 + (bt.x2-bt.x1)/4*3, bt.y1 + (bt.y2-bt.y1)/4*3);
}

//-------------Khung ve trong giao dien graphic-------------------
void boder(Button bt, int color_line)
{
	setcolor(color_line);
	rectangle(bt.x1, bt.y1, bt.x2, bt.y2);
	
}

//-------------------Button quay lai-----------------------------
void button_back(Button bt, int color_fill, int color_line)
{
    button2(bt, color_fill);
    settextjustify(1, 1);
    setfillstyle(1,color_line);
    settextstyle(0,0,2);
    outtextxy((bt.x1)+45, (bt.y1)+25,"<--");
}

//-------------------------------------------------------------------Giao dien chính---------------------//

void GUI(){
	setcolor(BLUE);
	//boder
	setlinestyle(0,1,3);
	rectangle(80,10,550,370);
	//button THUC
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(18,32,"THUC");
	//button TAP y+40
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(22,72,"TAP");
	//button CO y+40
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(26,112,"CO");
	//button CO y+40
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(26,152,"SO");
	//button CO y+40
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(26,192,"2");
	//button CO y+40
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(52,192,"0");
	//button CO y+40
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(26,232,"2");
	//button CO y+40
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(52,232,"3");
	//button back
	setcolor(GREEN);
	settextstyle(2,0,7);
	rectangle(580,10,680,50);
	outtextxy(610,20,"New");
	//button load file : +60 for top and bottom
	setcolor(WHITE);
	settextstyle(2,0,7);
	rectangle(580,70,680,110);
	outtextxy(590,80,"Load File");
	//button : +60 for top and bottom
	setcolor(WHITE);
	settextstyle(2,0,7);
	rectangle(580,130,680,170);
	outtextxy(590,140,"Keyboard");
	//button fraphic
	setcolor(WHITE);
	settextstyle(2,0,7);
	rectangle(580,190,680,230);
	outtextxy(600,200,"Graphic");
	// button ho ten GVHD:
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(200,380,"GVHD: Doan Vu Thinh");
	// button ho ten:
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(160,400,"FullName: Cao Nguyen Quoc Lam");
	// button MSSV:
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(210,420,"MSSV: 63132195");
	// button Lop:-
	setcolor(WHITE);
	settextstyle(2,0,7);
	outtextxy(200,440,"Class: 63.CNTT - 4");
}

//------------------------------------------- Using mouse
void clickmouse(){
	int x_mouse;
	int y_mouse;
	while(1){
		//get even mouse click
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN,x_mouse,y_mouse);
			printf("\nToa do: (%d,%d)",x_mouse,y_mouse);
			//check button back
			if(x_mouse > 580 && x_mouse <680 && y_mouse > 10 && y_mouse < 50){ //Reset
				printf("Resetting....");
				resetAll();
			}
			//check button
			if(x_mouse > 580 && x_mouse <680 && y_mouse > 70 && y_mouse < 110){ //load file
				printf("Read from file...");
				readfile();
			}
			// check button keyboard
			if(x_mouse > 580 && x_mouse <680 && y_mouse > 130 && y_mouse < 170){ //keyboard
				setcolor(RED);
				keyboard();
				
			}
			// check button graphic
			if(x_mouse > 580 && x_mouse <680 && y_mouse > 190 && y_mouse < 230){ //Graphic
				printf("Running demo...");
				cleardevice();
				Graphic();	
			}
		}
		//Check right mouse click
		if(ismouseclick(WM_RBUTTONDOWN)){
			getmouseclick(WM_RBUTTONDOWN,x_mouse,y_mouse);
			printf("\nExiting...");
			break;
		}
		delay(100);// next click mouse
	}
}

//-----------------------------------------------Code Cohen-Sutherland------------------------------//
//---------------------------------------------------Cohen Sutherland Xen tia doan thang--------------------------------------------
point kiemtra(point p1, point p2, point p3)
{
	int t1 = (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
	int t2 = (p1.x - p3.x)*(p1.x - p3.x) + (p1.y - p3.y)*(p1.y - p3.y);
	if (t1 > t2 ) return p2;
	return p3;
	
}

void hoandoi()
{
	if (pt[0].x > pt[1].x) swap(pt[0].x, pt[1].x);
	if (pt[0].y > pt[1].y) swap(pt[0].y, pt[1].y);
	rectangle(pt[0].x, pt[0].y, pt[1].x, pt[1].y);
}

void MaCode(point p1, point p2)
{
	tong1 = 0;
	tong2 = 0;
	if (p1.y> pt[1].y) code1[1] = 1;
	if (pt[0].y > p1.y) code1[2] = 1;
	if (p1.x > pt[1].x) code1[3] = 1;
	if (pt[0].x > p1.x) code1[4] = 1;
	
	if (p2.y > pt[1].y) code2[1] = 1;
	if (pt[0].y > p2.y) code2[2] = 1;
	if (p2.x > pt[1].x) code2[3] = 1;
	if (pt[0].x > p2.x) code2[4] = 1;
	
	int mu2 = 1;
	for (int i = 4; i > 0; i--)
	{
		tong1 += mu2*code1[i]; 
		tong2 += mu2*code2[i];
		mu2 *= 2;
	}
}

 void CatXen(point p1, point p2)
{
	if ((tong1+tong2) == 0)
	{
		printf("duong thang nam trong HCN Clipping\n");
		setcolor(RED);
		setlinestyle(0,0,3);
		line(p1.x,p1.y,p2.x,p2.y);

	}
	else if ((tong1&tong2) != 0)
	{
		printf("duong thang nam ngoai HCN Clipping\n");
	}
	
	else
	{
		printf("duong thang can cat xen\n");
		float m = 1.0*(p2.y-p1.y)/(p2.x-p1.x);
		float x,y;
		if(tong1 != 0)
		{
			if(code1[1]==1 && code1[4]==1)
			{
			  	point b1, b2;				
				x = p1.x+1.0*(pt[1].y-p1.y)/m;
				b1.x = round(x);
	   			b1.y= pt[1].y;
				printf("%d-%d\n",b1.x,b1.y);				
				y = p1.y+(pt[0].x-p1.x)*m;
				b2.y= round(y);
   				b2.x=pt[0].x;
   				p1=kiemtra(p1,b1,b2);
   				

			}
			else if(code1[1]==1 && code1[3]==1)
			{
			  	point b1, b2;				
				x = p1.x+1.0*(pt[1].y-p1.y)/m;
				b1.x = round(x);
	   			b1.y= pt[1].y;
	   			
				printf("%d-%d\n",b1.x,b1.y);
								
				y = p1.y+(pt[1].x-p1.x)*m;
				b2.y= round(y);
    			b2.x=pt[1].x;
   				p1=kiemtra(p1,b1,b2);

			}
			else if(code1[2]==1 && code1[3]==1)
			{
			  	point b1, b2;				
				x = p1.x+1.0*(pt[0].y-p1.y)/m;
				b1.x = round(x);
    			b1.y= pt[0].y;
	   			
				printf("%d-%d\n",b1.x,b1.y);
								
				y = p1.y+(pt[1].x-p1.x)*m;
				b2.y= round(y);
    			b2.x=pt[1].x;
   				p1=kiemtra(p1,b1,b2);

			}
			else if(code1[2]==1 && code1[4]==1)
			{
			  	point b1, b2;				
				x = p1.x+1.0*(pt[0].y-p1.y)/m;
				b1.x = round(x);
    			b1.y= pt[0].y;
	   			
				printf("%d-%d\n",b1.x,b1.y);
								
				y = p1.y+(pt[0].x-p1.x)*m;
				b2.y= round(y);
   				b2.x=pt[0].x;
   				p1=kiemtra(p1,b1,b2);

			}
			
			else if(code1[1] == 1)
			{
				x = p1.x+1.0*(pt[1].y-p1.y)/m;
				p1.x = round(x);
    			p1.y= pt[1].y;
			}
			else if (code1[4] == 1)
			{
				y = p1.y+(pt[0].x-p1.x)*m;
				p1.y= round(y);
    			p1.x=pt[0].x;
			}
			else if (code1[2] == 1)
			{
				x = p1.x+1.0*(pt[0].y-p1.y)/m;
				p1.x = round(x);
    			p1.y= pt[0].y;
			}
			else if (code1[3] == 1)
			{
				y = p1.y+(pt[1].x-p1.x)*m;
				p1.y= round(y);
    			p1.x=pt[1].x;
			}
		}
		
		if(tong2 != 0)
		{
			if(code2[1]==1 && code2[4]==1)
			{
			  	point b1, b2;				
				x = p2.x+1.0*(pt[1].y-p2.y)/m;
				b1.x = round(x);
	   			b1.y= pt[1].y;
				printf("%d-%d\n",b1.x,b1.y);				
				y = p2.y+(pt[0].x-p2.x)*m;
				b2.y= round(y);
   				b2.x=pt[0].x;
   				p2=kiemtra(p2,b1,b2);

			}
			else if(code2[1]==1 && code2[3]==1)
			{
			  	point b1, b2;				
				x = p2.x+1.0*(pt[1].y-p2.y)/m;
				b1.x = round(x);
	   			b1.y= pt[1].y;
	   			
				printf("%d-%d\n",b1.x,b1.y);
								
				y = p2.y+(pt[1].x-p2.x)*m;
				b2.y= round(y);
    			b2.x=pt[1].x;
   				p2=kiemtra(p2,b1,b2);

			}
			else if(code2[2]==1 && code2[3]==1)
			{
			  	point b1, b2;				
				x = p2.x+1.0*(pt[0].y-p2.y)/m;
				b1.x = round(x);
    			b1.y= pt[0].y;
	   			
				printf("%d-%d\n",b1.x,b1.y);
								
				y = p2.y+(pt[1].x-p2.x)*m;
				b2.y= round(y);
    			b2.x=pt[1].x;
   				p2=kiemtra(p2,b1,b2);

			}
			else if(code2[2]==1 && code2[4]==1)
			{
			  	point b1, b2;				
				x = p2.x+1.0*(pt[0].y-p2.y)/m;
				b1.x = round(x);
    			b1.y= pt[0].y;
	   			
				printf("%d-%d\n",b1.x,b1.y);
								
				y = p2.y+(pt[0].x-p2.x)*m;
				b2.y= round(y);
   				b2.x=pt[0].x;
   				p2=kiemtra(p2,b1,b2);

			}
			else if(code2[1] == 1)
			{
				x=p2.x+1.0*(pt[1].y-p2.y)/m;
				p2.x = round(x);
    			p2.y = pt[1].y;
			}
			else if (code2[2] == 1)
			{
				x = p2.x+1.0*(pt[0].y-p2.y)/m;
				p2.x = round(x);
    			p2.y = pt[0].y;
			}
			else if (code2[3] == 1)
			{
				y = p2.y + (pt[1].x-p2.x)*m;
				p2.y = round(y);
    			p2.x = pt[1].x;
			}
			else if (code2[4] == 1)
			{
				y = p2.y + (pt[0].x-p2.x)*m;
				p2.y = round(y);
    			p2.x = pt[0].x;
			}
		}
		int mid_x = round((p1.x+p2.x)/2);
		int mid_y = round((p1.y+p2.y)/2);
		if (pt[0].x < mid_x && mid_x < pt[1].x && pt[0].y < mid_y && mid_y < pt[1].y)
		{ 
			setcolor(RED);
			setlinestyle(0,0,3);
			line(p1.x,p1.y,p2.x,p2.y);
		}
	}
}

void tohog(point p1, point p2)
{
	MaCode(p1,p2);
	CatXen(p1,p2);
}

void addpointwd()
 {
 	clip[0] = pt[0];
 	clip[1].x = pt[0].x;
 	clip[1].y = pt[1].y;
 	clip[2] = pt[1];
 	clip[3].x = pt[1].x;
 	clip[3].y = pt[0].y;
 }

int x_intersect(point p1,point p2, point p3, point p4) 
{ 
    int num = (p1.x*p2.y - p1.y*p2.x) * (p3.x-p4.x) - 
              (p1.x-p2.x) * (p3.x*p4.y - p3.y*p4.x); 
    int den = (p1.x-p2.x) * (p3.y-p4.y) - (p1.y-p2.y) * (p3.x-p4.x); 
    return round(num/den); 
} 
 
int y_intersect(point p1,point p2, point p3, point p4) 
{ 
    int num = (p1.x*p2.y - p1.y*p2.x) * (p3.y-p4.y) - 
              (p1.y-p2.y) * (p3.x*p4.y - p3.y*p4.x); 
    int den = (p1.x-p2.x) * (p3.y-p4.y) - (p1.y-p2.y) * (p3.x-p4.x); 
    return round(num/den); 
} 

void cllip(point p1,point p2) 
{    
	int n2 = 0;
    for (int i = 0; i < n1; i++) 
    { 
    	int k = (i+1) % n1; 
        int ix = poly[i].x, iy = poly[i].y; 
        int kx = poly[k].x, ky = poly[k].y; 
 
        int i_pos = (p2.x-p1.x) * (iy-p1.y) - (p2.y-p1.y) * (ix-p1.x); 
  
        int k_pos = (p2.x-p1.x) * (ky-p1.y) - (p2.y-p1.y) * (kx-p1.x); 
  
        // Case 1 : When both points are inside 
        if (i_pos < 0  && k_pos < 0) 
        { 
            poly1[n2].x = kx; 
            poly1[n2].y = ky; 
            n2++; 
        } 
  
        // Case 2: When only first point is outside 
        else if (i_pos >= 0  && k_pos < 0) 
        { 
            poly1[n2].x = x_intersect(p1,p2,poly[i],poly[k]); 
            poly1[n2].y = y_intersect(p1,p2,poly[i],poly[k]); 
            n2++;
  
            poly1[n2].x = kx; 
            poly1[n2].y = ky; 
            n2++;
        } 
  
        // Case 3: When only second point is outside 
        else if (i_pos < 0  &&  k_pos >= 0) 
        { 	poly1[n2].x = x_intersect(p1,p2,poly[i],poly[k]); 
            poly1[n2].y = y_intersect(p1,p2,poly[i],poly[k]); 
            n2++;
        } 
  
        else
        { 
        //nothing;
        } 
    } 
  	
    n1 = n2; 
    printf("%dN1\n = ",n1);
    for (int i = 0; i < n1; i++) 
    { 	
        poly[i] = poly1[i]; 
        printf("\n%d--%d\n",poly[i].x,poly[i].y);
    } 
    
} 

void Cohen_Sutherland() 
{ 

    for (int i=0; i<4; i++) 
    { 
        int k = (i+1) % 4; 
  
        cllip(clip[i],clip[k]); 
        
    } 
    setcolor(RED);
	setlinestyle(0,0,3);
	for (int i = 0; i < n1; i++) 
    { 	int k= (i+1)%n1;  
        line(poly[i].x,poly[i].y,poly[k].x,poly[k].y); 
    } 
} 

//--------------------------------------------Code Liang-Barsky-----------------------------------------------
void Liang_Barsky(point p1, point p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int p[4], q[4], t1 = 0, t2 = 1;

    p[0] = -dx;
    p[1] = dx;
    p[2] = -dy;
    p[3] = dy;

    q[0] = p1.x - xmin;
    q[1] = xmax - p1.x;
    q[2] = p1.y - ymin;
    q[3] = ymax - p1.y;

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0) {
            printf("Line is parallel to the clipping window and outside\n");
            return;
        }

        float r = (float)q[i] / p[i];

        if (p[i] < 0 && r > t1)
            t1 = r;
        else if (p[i] > 0 && r < t2)
            t2 = r;
    }

    // Check if the line is outside the clipping window
    if (t1 > t2) {
        printf("Line is outside the clipping window\n");
        return hoandoi();
    }
    

    // Clipping coordinates
    int x1 = p1.x + t1 * dx;
    int y1 = p1.y + t1 * dy;
    int x2 = p1.x + t2 * dx;
    int y2 = p1.y + t2 * dy;

    printf("Line is inside the clipping window\n");
    printf("Clipped coordinates: (%d, %d) to (%d, %d)\n", pt[0].x, pt[0].y, pt[1].x, pt[1].y);

    for (int i=0; i<4; i++) 
    { 
        int k = (i+1) % 4; 
  
        cllip(clip[i],clip[k]); 
        
    } 
    setcolor(RED);
	setlinestyle(0,0,3);
	for (int i = 0; i < n1; i++) 
    { 	int k= (i+1)%n1;  
        line(poly[i].x,poly[i].y,poly[k].x,poly[k].y); 
    }
}

//----------------------------------------------------------Giao dien Load file---------------------------------------------------------------//
void readfile() {
    FILE *fp;
    fp = fopen("xentia.inp", "r");

    if (fp == NULL) {
        printf("File not found or cannot be opened.\n");
        return;
    }

    // Read clipping window coordinates
    if (fscanf(fp, "%d %d %d %d", &pt[0].x, &pt[0].y, &pt[1].x, &pt[1].y) != 4) {
        printf("Error reading coordinates of clipping window.\n");
        fclose(fp);
        return;
    }

    // Draw the clipping window
    setcolor(RED);
    rectangle(pt[0].x, pt[0].y, pt[1].x, pt[1].y);
    poly[0]={poly[0].x,poly[0].y};
 	poly[1]={poly[1].x,poly[1].y};
 	hoandoi();
 	for (int i=2; i<=n-2 ; i+=2)
 	{
 		tohog(pt[i],pt[i+1]);
 		for (int j=1; j<=4; j++)
 		{
 			code1[j] = 0;
			code2[j] = 0;
 		}
 	}

    // Read the number of vertices
    if (fscanf(fp, "%d", &n1) != 1) {
        printf("Error reading the number of vertices.\n");
        fclose(fp);
        return;
    }

    // Read and draw 
    for (int i = 0; i < n1; i++) {
        if (fscanf(fp, "%d %d", &poly[i].x, &poly[i].y) != 2) {
            printf("Error reading coordinates of vertex %d.\n", i + 1);
            fclose(fp);
            return;
        }
        printf("\nToa do thu %d: (%d, %d)\n", i + 1, poly[i].x, poly[i].y);
    }

    // Draw the line
    setcolor(GREEN);
    for (int i = 0; i < n1; i++) {
        int k = (i + 1) % n1;
        line(poly[i].x, poly[i].y, poly[k].x, poly[k].y);
    }
    // Perform polygon clipping using Cohen-Sutherland
    addpointwd();
    Cohen_Sutherland();
    fclose(fp);
}

//-----------------------------------------------------------------------Giao dien nhap tay----------------------------------------------------------------------//
void MenuXenTia() {
    printf("Chon thu thuat xen tia:\n");
    printf("1. Cohen-Sutherland\n");
    printf("2. Liang-Barsky\n");
}

void KhoiTao()
{
	printf("\nNHAP PHAI THOA MAN DIEU KIEN \n|| 80<X<550 && 10<Y<370 ||\n");
	do 
	{
		printf("Nhap hinh chu nhat Clipping\n");
		printf("xmin = "); scanf("%d",&pt[0].x);
		printf("ymin = "); scanf("%d",&pt[0].y);
		printf("xmax = "); scanf("%d",&pt[1].x);
		printf("ymax = "); scanf("%d",&pt[1].y);
	}
	while(80 >= pt[0].x || 550<=pt[0].x  ||  10>=pt[0].y || 370 <= pt[0].y || 80 >= pt[1].x || 550<=pt[1].x  ||  10>=pt[1].y || 370 <= pt[1].y);
	//Ve cua so cut
	setcolor(GREEN);
	rectangle(pt[0].x,pt[0].y,pt[1].x,pt[1].y);
	printf("nhap so canh cua da giac :");
	scanf("%d",&n1);
	int i = 0;
	while(i<n1)
	{   printf("Nhap toa do dinh thu %d\n",i+1);
		printf("x = "); scanf("%d",&poly[i].x);
		printf("y = "); scanf("%d",&poly[i].y);
		if(80<poly[i].x && 550>poly[i].x  &&  10<poly[i].y && 370 > poly[i].y)
		{   
			i++;
		}
		else {
			printf(" diem ban vua nhap khong nam trong cua so , vui long nhap lai \n");
		}
		
	}
	for (int i=0; i<n1; i++)
	{   int k=(i+1)%n1;
		line(poly[i].x,poly[i].y,poly[k].x,poly[k].y);
    }
    
}

void keyboard(){
	MenuXenTia();
    int choice;
    printf("Nhap lua chon: ");
    scanf("%d", &choice);
	
    switch (choice) {
        case 1:
        	printf("Ban da lua chon thuat toan Cohen - Sutherland");
        	KhoiTao();
        	addpointwd();
        	Cohen_Sutherland();
            break;
        case 2:
        	printf("Ban da lua chon thuat toan Liang - Barsky");
			KhoiTao();
        	addpointwd();
            Liang_Barsky(p1,p2);
            break;
        default:
            printf("Lua chon khong hop le.\n");
        }
}

//--------------------------------------------------------------------------Giao dien graphic---------------------------------------------//
//--------------------------------------------------Button giao dien do hoa --------------------------------------------------------------//
 
void Graphic(){

    int size_x = 50, size_y = 50, space = 30;
    
    //int x1_poly = 10, y1_poly = 150, x2_poly = x1_poly + size_x, y2_poly = y1_poly + size_y;
    
    int x1_line = 15, y1_line = 150 , x2_line = 65, y2_line = 200;
    
    int x1_liang = 570, y1_liang = 130 , x2_liang = 620, y2_liang = 180;
    
    int x1_cohen = 570, y1_cohen = 230, x2_cohen = 620, y2_cohen = 280;
    
    int x1_del = 15, y1_del = 250, x2_del = 65, y2_del = 300;

    int x1_bk = 580, y1_bk = 10, x2_bk = 680, y2_bk = 50;
    
    int x1_boder = 95, y1_boder = 90, x2_boder = 550, y2_boder = 370;
	
	Button btLiang = {x1_liang, y1_liang, x2_liang, y2_liang};
    Button btLine = {x1_line, y1_line, x2_line, y2_line};
    Button btCohen = {x1_cohen, y1_cohen, x2_cohen, y2_cohen};
    Button btboder = {x1_boder, y1_boder, x2_boder, y2_boder};
    Button btDel = {x1_del, y1_del, x2_del, y2_del};
    Button btback = {x1_bk, y1_bk, x2_bk, y2_bk};
    Button btcolor[16];
    
	button_liang(btLiang, 2 , 15);
    button_line(btLine, 2 , 15);
    button_cohen(btCohen, 2 , 15);
    boder(btboder, 2);
    button_back(btback,2,15);
    button_del(btDel, 2 , 15);
    
    //----------------------Ve cac button color
    int x1 = 120, y1 = 400, x2 = x1 + 30, y2=y1+30;
    int spcolor = 12;
    for (int i = 1 ;i<7; i++)
    {
    	btcolor[i] = {x1, y1, x2, y2};
    	bt_color(btcolor[i],i);
    	x1+= 60+spcolor; x2+=60+spcolor;	
    }
    
    //------------------theo tac tren giao dien chinh
	while(1)
   { 
   		delay(0.1);
   	 	if (ismouseclick(WM_MOUSEMOVE))
		{
    		int x,y;
    		char s[100];
			getmouseclick(WM_MOUSEMOVE, x, y);
			point p = {x,y};
			//Hover button Liang
			if (check_button(btLiang,p))
			{
				setcolor(15);
				button_liang(btLiang, 5 , 3);
				temp3=1;
			}
			else if (!check_button(btLiang, p) && temp3==1)
			{
				setcolor(15);
				button_liang(btLiang, 2 , 15);
				temp3=0;
			}
			
			//Hover button Line
			if (check_button(btLine,p))
			{
				setcolor(15);
				button_line(btLine, 5 , 3);
				temp=1;
			}
			else if (!check_button(btLine, p)&& temp==1 )
			{
				setcolor(15);
				button_line(btLine, 2 , 15);
				temp=0;
			}
			//Hover button Cohen
			if (check_button(btCohen,p))
			{
				setcolor(15);
				button_cohen(btCohen, 5 , 3);
				temp1=1;
			}
			else if (!check_button(btCohen, p) && temp1==1 )
			{
				setcolor(15);
				button_cohen(btCohen, 2 , 15);
				temp1=0;
			}
			//Hover button Del
			if (check_button(btDel,p))
			{
				setcolor(15);
				button_del(btDel, 5 , 3);
				temp2=1;
			}
			else if (!check_button(btDel, p) && temp2==1)
			{
				setcolor(15);
				button_del(btDel, 2 , 15);
				temp2=0;
			}
			//Trang thai con tro?
			setcolor(15);
			sprintf(s,"\n Toa Do (%d,%d)",x,y);
			outtextxy(300,40,s);	
   		}
   
   		if (ismouseclick(WM_LBUTTONUP))
		{
	   		int x,y;
	   		char s[100];
			getmouseclick(WM_LBUTTONUP, x, y);
			clearmouseclick(WM_LBUTTONUP);
			clearmouseclick(WM_LBUTTONDOWN);
			point p = {x,y};
   	    	if (check_button(btLine,p))
			{
				while(1)
				{  
				 	delay(0.1);
					point p1,p2;
					if (ismouseclick(WM_MOUSEMOVE))
					{
						getmouseclick(WM_MOUSEMOVE, x, y);
						clearmouseclick(WM_MOUSEMOVE);
						setcolor(15);
						printf(s,"\n Toa Do (%d,%d) \n",x,y);
						outtextxy(300,40,s);
					}
					
			 	 	if (ismouseclick(WM_LBUTTONDOWN))
				 	{  
					   	getmouseclick(WM_LBUTTONDOWN, x, y);
	            		clearmouseclick(WM_LBUTTONDOWN);
	           		 	p1 = {x,y};
            			if (!check_button(btboder,p1)) break;
			 		}
			 		
			 	 	if(ismouseclick(WM_LBUTTONUP))
            		{
	            		getmouseclick(WM_LBUTTONUP, x, y);
						clearmouseclick(WM_LBUTTONUP);
           		 		p2 = {x,y};
           		 		
            			if (!check_button(btboder,p2)) break;
            			setcolor(color);
            		 	line(p1.x,p1.y,p2.x,p2.y);
            		 	pt[n]={p1.x,p1.y};
            		 	pt[n+1]={p2.x,p2.y};
            		 	n+=2;
            		}	
        		}	
			}
			
			if (check_button(btDel,p))
			{  
				cleardevice();
				Graphic();
			}
			
			if (check_button(btCohen,p))
			{
				while(1)
				{  
				 	delay(0.01);
					point p1,p2;
					if (ismouseclick(WM_MOUSEMOVE))
					{
						getmouseclick(WM_MOUSEMOVE, x, y);
						clearmouseclick(WM_MOUSEMOVE);
						setcolor(15);
						sprintf(s,"\t Toa Do (%d,%d) \t",x,y);
						outtextxy(300,40,s);
					}
			 	 	if (ismouseclick(WM_LBUTTONDOWN))
				 	{  
					   	getmouseclick(WM_LBUTTONDOWN, x, y);
	            		clearmouseclick(WM_LBUTTONDOWN);
	           		 	p1 = {x,y};
            			if (!check_button(btboder,p1)) break;
			 		}
			 		
			 	 	if(ismouseclick(WM_LBUTTONUP))
            		{
	            		getmouseclick(WM_LBUTTONUP, x, y);
						clearmouseclick(WM_LBUTTONUP);
           		 		p2 = {x,y};
            			if (!check_button(btboder,p2)) 
						break;
            			setcolor(color);
            			setlinestyle(0,0,0);
            		 	rectangle(p1.x,p1.y,p2.x,p2.y);
            		 	pt[0]={p1.x,p1.y};
            		 	pt[1]={p2.x,p2.y};
            		 	hoandoi();
            		 	for (int i=2; i<=n-2 ; i+=2)
            		 	{
            		 		tohog(pt[i],pt[i+1]);
            		 		for (int j=1; j<=4; j++)
            		 		{
            		 			code1[j] = 0;
								code2[j] = 0;
            		 		}
            		 	}
            		 	printf("tn1 = %d\n",n1);
            		 	addpointwd();
						Cohen_Sutherland() ;
            		}
        		}
			}

			if (check_button(btLiang,p))
			{
				while(1)
				{  
				 	delay(0.01);
					point p1,p2;
					if (ismouseclick(WM_MOUSEMOVE))
					{
						getmouseclick(WM_MOUSEMOVE, x, y);
						clearmouseclick(WM_MOUSEMOVE);
						setcolor(15);
						sprintf(s,"\t Toa Do (%d,%d) \t",x,y);
						outtextxy(300,40,s);
					}
			 	 	if (ismouseclick(WM_LBUTTONDOWN))
				 	{  
					   	getmouseclick(WM_LBUTTONDOWN, x, y);
	            		clearmouseclick(WM_LBUTTONDOWN);
	           		 	p1 = {x,y};
            			if (!check_button(btboder,p1)) break;
			 		}
			 	 	if(ismouseclick(WM_LBUTTONUP))
            		{
	            		getmouseclick(WM_LBUTTONUP, x, y);
						clearmouseclick(WM_LBUTTONUP);
           		 		p2 = {x,y};
            			if (!check_button(btboder,p2)) 
						break;
            			setcolor(color);
            			setlinestyle(0,0,0);
            		 	rectangle(p1.x,p1.y,p2.x,p2.y);
            		 	pt[0]={p1.x,p1.y};
            		 	pt[1]={p2.x,p2.y};
            		 	hoandoi();
            		 	for (int i=2; i<=n-2 ; i+=2)
            		 	{
            		 		tohog(pt[i],pt[i+1]);
            		 		for (int j=1; j<=4; j++)
            		 		{
            		 			code1[j] = 0;
								code2[j] = 0;
            		 		}
            		 	}
            		 	printf("tn1 = %d\n",n1);
            		 	addpointwd();
						Liang_Barsky(p1,p2) ;
            		}
        		}
			}
			
			for (int i=1; i<7; i++)
			{
				if(check_button(btcolor[i],p))
				{
					color = i;
					break;
				}	
			}
			if(check_button(btback,p))
			{
				cleardevice();
				goto out;
			}
   		} 
 	}
	out:
	cleardevice();			
}

//----------------------------------------------------------------------------Main---------------------------------------------------------
int main(){
	//draw interface
	initwindow(700,500);
	GUI();
	// Using mouse
	clickmouse();
	getch();
}
