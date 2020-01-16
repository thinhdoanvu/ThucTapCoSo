#include <stdio.h>
#include<iostream>
#include<graphics.h>
#define round(a) ((int)(a+0.5))
using namespace std;
char c;
int color = 15;
char s[100];

struct point {
	int x,y;
};

struct Button
{
    int x1, y1, x2, y2;
};

int n=2;
int n1 = 0 ;
point pt[100];
point poly[100];
point poly1[100];
point clip[100];
int code1[10], code2[10];
int tong1, tong2;
int temp=0,temp1=0,temp2=0, temp3 = 0;


//---------------------------------------------------Reset toan bo giu lieu------------------------------------------------------------------
void resetALL()
{
    
	for (int i=0; i<=n+2; i++) 
	{
		pt[i] = {0,0};
		if (1<=i && i<=4)
		{
			code1[i] = 0;
			code2[i] = 0;
		} 
		
	}
	n = 2;
   for (int i=0; i<=n1; i++) 
	{
		poly[i] = {0,0};
		poly1[i] = {0,0};
	} n1=0;
	
}

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


//------------------------------------------------------------Xen tia da giac Sutherland Hogman-------------------------------------------------------------- 
void KhoiTao()
{
	printf("\nNHAP PHAI THOA MAN DIEU KIEN \n|| 140<X<720 && 20<Y<480 ||\n");
	do 
	{
		printf("Nhap hinh chu nhat Clipping\n");
		printf("xmin = "); scanf("%d",&pt[0].x);
		printf("ymin = "); scanf("%d",&pt[0].y);
		printf("xmax = "); scanf("%d",&pt[1].x);
		printf("ymax = "); scanf("%d",&pt[1].y);
	}
	while(140 >= pt[0].x || 720<=pt[0].x  ||  20>=pt[0].y || 480 <= pt[0].y || 140 >= pt[1].x || 720<=pt[1].x  ||  20>=pt[1].y || 480 <= pt[1].y);

	rectangle(pt[0].x,pt[0].y,pt[1].x,pt[1].y);
	printf("nhap so canh cua da giac :");
	scanf("%d",&n1);
	int i = 0;
	while(i<n1)
	{   printf("Nhap toa do dinh thu %d\n",i+1);
		printf("x = "); scanf("%d",&poly[i].x);
		printf("y = "); scanf("%d",&poly[i].y);
		if(140<poly[i].x && 720>poly[i].x  &&  20<poly[i].y && 480 > poly[i].y)
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

void Poly_Hogman() 
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

//-----------------------------------------------------Kiem tra diem nam trong button----------------------------------
bool check_button(Button bt,point p)
{
	   if(bt.x1<=p.x && bt.y1<=p.y&& bt.x2>=p.x&& bt.y2>=p.y) 
	      return true;
	   return false;                   
}
//------------------------------------------------------khai bao cac kieu button duoc su dung-------------------------------------------------------------------------------------
void bt_color(Button bt, int color_fill)
{
	setlinestyle(0,0,2);
	setfillstyle(1,color_fill);
    bar(bt.x1, bt.y1, bt.x2, bt.y2);
}


void button(Button bt, int color_fill)
{
	setlinestyle(0,0,2);
    setfillstyle(1,color_fill);
    setcolor(15);
    bar3d(bt.x1, bt.y1, bt.x2, bt.y2,20,1);
}
 
void button2(Button bt, int color_fill)
{
    setcolor(color_fill);
    setlinestyle(2,3,4);
    rectangle(bt.x1, bt.y1, bt.x2, bt.y2);
    
}

//------------------------------------------------Button giao dien menu chinh--------------------------------------------------------------------------------------------------
void button_menu1(Button bt, int color_fill, int color_line)
{
    button2(bt, color_fill);
  	setcolor(color_line);
  	settextstyle(10,0,1);
    outtextxy((bt.x1)+10, (bt.y1)+10,"1. Nhap Du Lieu Tu Ban Phim");
}
void button_menu2(Button bt, int color_fill, int color_line)
{
    button2(bt, color_fill);
    setcolor(color_line);
    outtextxy((bt.x1)+10, (bt.y1)+10,"2. Nhap Du Lieu Tu Giao Dien Do Hoa");
}
void button_menu3(Button bt, int color_fill, int color_line)
{
    button2(bt, color_fill);
    setcolor(color_line);
    outtextxy((bt.x1)+10, (bt.y1)+10,"3. Gioi Thieu");
}

//-------------------------------------------------Button giao dien nhap ban phim----------------------------------------------------------------------------------------------------
void button_dell(Button bt, int color_fill, int color_line)
{
    button2(bt, color_fill);
  	setcolor(color_line);
  	settextstyle(3,0,1);
    outtextxy((bt.x1)+10, (bt.y1)+10,"del");
}

void button_ins(Button bt, int color_fill, int color_line)
{
    button2(bt, color_fill);
  	setcolor(color_line);
  	settextstyle(3,0,1);
    outtextxy((bt.x1)+10, (bt.y1)+10,"insert");
}
//--------------------------------------------------Button giao dien do hoa --------------------------------------------------------------------------------------------------------

void button_line(Button bt, int color_fill, int color_line)
{
    button(bt, color_fill);
    setcolor(color_line);
    line((bt.x2-bt.x1)/5*2, (bt.y2-bt.y1)/5+bt.y1, (bt.x2-bt.x1), (bt.y2-bt.y1)/5*4+bt.y1);
}
 
void button_crop(Button bt, int color_fill, int color_line)
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
 
void button_del(Button bt, int color_fill, int color_line)
{
    button(bt, color_fill);
    settextjustify(1, 1);
    setfillstyle(1,color_line);
    bar(bt.x1 + (bt.x2-bt.x1)/4, bt.y1 + (bt.y2-bt.y1)/4, bt.x1 + (bt.x2-bt.x1)/4*3, bt.y1 + (bt.y2-bt.y1)/4*3);
}
 
void button_poly(Button bt, int color_fill, int color_line)
{
    button(bt, color_fill);
    settextjustify(1, 1);
    setfillstyle(1,color_line);
    line(bt.x1 + (bt.x2-bt.x1)/4, bt.y1 + (bt.y2-bt.y1)/4,bt.x1 + (bt.x2-bt.x1)/4, bt.y1 + (bt.y2-bt.y1)-10);
    line(bt.x1 + (bt.x2-bt.x1)/4, bt.y1 + (bt.y2-bt.y1)-10, bt.x1 + (bt.x2-bt.x1)/4*3, bt.y1 + (bt.y2-bt.y1)-10);
    line(bt.x1 + (bt.x2-bt.x1)/4, bt.y1 + (bt.y2-bt.y1)/4,bt.x1 + (bt.x2-bt.x1)/4*3, bt.y1 + (bt.y2-bt.y1)-10);
}

void boder(Button bt, int color_line)
{
	setcolor(color_line);
	rectangle(bt.x1, bt.y1, bt.x2, bt.y2);
	
}

void button_back(Button bt, int color_fill, int color_line)
{
    button2(bt, color_fill);
    settextjustify(1, 1);
    setfillstyle(1,color_line);
    settextstyle(0,0,2);
    outtextxy((bt.x1)+40, (bt.y1)+30,"Back");
}

//-----------------------------------------------------------Giao dien menu chinh------------------------------------------------------------
//Start Graphics0 // 
int graphic0()
{
	int i = 0;
    int size_x = 410, size_y = 40, space = 70;
    int x1_mn1 = 210, y1_mn1= 230, x2_mn1 = x1_mn1 + size_x, y2_mn1 = y1_mn1 + size_y;
    int x1_mn2 =x1_mn1 , y1_mn2= y1_mn1 + space, x2_mn2 = x1_mn2 + size_x, y2_mn2 = y1_mn2 + size_y;
    int x1_mn3 =x1_mn2 , y1_mn3= y1_mn2 + space, x2_mn3 = x1_mn3 + size_x, y2_mn3 = y1_mn3 + size_y;
    
    Button mn1 = {x1_mn1, y1_mn1, x2_mn1, y2_mn1};
    setcolor(5);
  	button_menu1(mn1,0,10);
    Button mn2 =  {x1_mn2, y1_mn2, x2_mn2, y2_mn2};
    button_menu2(mn2,0,10);
    Button mn3 =  {x1_mn3, y1_mn3, x2_mn3, y2_mn3};
    button_menu3(mn3,0,10);
  
	while (1)
	{   delay(100);
		settextstyle(4,0,8);
		setcolor(i%14+1); i++;
		outtextxy(150,50,"Clipping ");
		setcolor(3);
		setlinestyle(2,1,3);
	    rectangle(150,200,650,450);
	   
	    setfillstyle(1,0);
	    bar(300,180,500,220);
	    settextstyle(4,0,3);
	    outtextxy(350,190,"MENU");

		if (ismouseclick(WM_MOUSEMOVE))
		{
    		int x,y;
			getmouseclick(WM_MOUSEMOVE, x, y);
			point p = {x,y};
			//Hover button menu1
			if (check_button(mn1,p))
			{
				button_menu1(mn1,3,3);		
			}
			else if (!check_button(mn1, p))
			{
				button_menu1(mn1,0,10);
			}
			//Hover button menu2
			if (check_button(mn2,p))
			{
				button_menu2(mn2,3,3);
			}
			else if (!check_button(mn2, p))
			{
				button_menu2(mn2,0,10);
			}
			//Hover button menu3
			if (check_button(mn3,p))
			{
				button_menu3(mn3,3,3);
			}
			else if (!check_button(mn3, p))
			{
				button_menu3(mn3,0,10);
			}
		}
	if (ismouseclick(WM_LBUTTONUP))
	{
		int x,y;
			getmouseclick(WM_LBUTTONUP, x, y);
			point p = {x,y};
			//click button menu1
			if (check_button(mn1,p))
			{
				return 1;	
			}
			
			//click button menu2
			if (check_button(mn2,p))
			{
				return 2;
			}
			
			//click button menu3
			if (check_button(mn3,p))
			{
				return 3;
			}
		}
	}
}

//----------------------------------------------------Giao dien menu nhap ban phim------------------------------------------------------------------
//Start Graphics1 // 
void Graphic1()
{	
	Button del;
   	Button ins;
   	Button boder;
   	
   	int size_x = 80,  size_y = 50, space = 30;
     
    int x1_ins = 30, y1_ins = 240, x2_ins = x1_ins + size_x, y2_ins = y1_ins + size_y;
    
    int x1_del = x1_ins, y1_del = y2_ins + space, x2_del = x1_del + size_x, y2_del = y1_del + size_y;
    
    int x1_bd = 140, y1_bd = 20 , x2_bd = x1_bd + 580, y2_bd = y1_bd + 460;
    
    int x1_bk = 30, y1_bk = 10, x2_bk = 110, y2_bk = 60;
 	

    Button btback = {x1_bk, y1_bk, x2_bk, y2_bk};
    ins = {x1_ins, y1_ins, x2_ins, y2_ins};
    del = {x1_del, y1_del, x2_del, y2_del};
    boder = {x1_bd, y1_bd, x2_bd, y2_bd};
    drawwd2:
    button_dell(del,15,15);
    button_ins(ins,15,15);
    button2(boder,15);
    button_back(btback,2,15);
    while(1)
    { delay(0.01);
    	if (ismouseclick(WM_LBUTTONUP))
		{
	   		int x,y;
			getmouseclick(WM_LBUTTONUP, x, y);
			point p = {x,y};
			clearmouseclick(WM_LBUTTONUP);
			clearmouseclick(WM_LBUTTONDOWN);
			
			
			if (check_button(del,p))
			{   
				cleardevice();
				goto drawwd2;
			}
			
   	    	if (check_button(ins,p))
			{
				KhoiTao();
				addpointwd();
				Poly_Hogman() ;
					
   				}
			if(check_button(btback,p))
			{
				goto out;
			}
			
    	}
	}
	out:
	cleardevice();
}


//----------------------------------Giao dien gioi thieu------------------------------------------------------------------
//Start Graphics2 // 
void Graphic2()
{
	int x1_bk = 700, y1_bk = 10, x2_bk = 780, y2_bk = 60;int i=1;int j=0;
 	Button btback = {x1_bk, y1_bk, x2_bk, y2_bk};
  	button_back(btback,2,15);
  	while(1)
  	{
  		delay(200);
		if (ismouseclick(WM_LBUTTONUP))
		{
			int x,y;
			getmouseclick(WM_LBUTTONUP, x, y);
			point p = {x,y};
			if(check_button(btback,p))
			{
				goto out;
			}
   		}
   		settextstyle(4,0,5);
		setcolor(i%14+1); i++;j++;
		outtextxy(400,60,"Wellcome");
		
		
		
		setcolor(0);
		outtextxy(390,200+(j%10)*10,"Chao mung thay den voi bai TTCS cua chung em!!!");
		outtextxy(390,250+(j%10)*10,"Phien Ban v1.0 designer for TTCS");
		setcolor(12);
		settextstyle(4,0,2);
		setlinestyle(2,1,3);
		outtextxy(390,200+(i%10)*10,"Chao mung thay den voi bai TTCS cua chung em!!!");
		outtextxy(390,250+(i%10)*10,"Phien Ban v1.0 designer for TTCS");
		 
 	}
 	out: 
 	cleardevice();
}
//End Graphics2 // Giao dien gioi thieu


//-----------------------------------------------------------------Giao dien su dung chuot--------------------------------------
void Graphic()
{	
	drawwd: 
	resetALL();
    //Khai bao button 50x50 va khoang cach giua cac button la 30
    int size_x = 50, size_y = 50, space = 30;
     
    int x1_poly = 10, y1_poly = 150, x2_poly = x1_poly + size_x, y2_poly = y1_poly + size_y;
    
    int x1_line = x1_poly, y1_line = y2_poly + space , x2_line = x1_line + size_x, y2_line = y1_line + size_y;
    
    int x1_crop = x1_line, y1_crop = y2_line + space, x2_crop = x1_crop + size_x, y2_crop = y1_crop + size_y;
    
    int x1_del = x1_crop, y1_del = y2_crop + space, x2_del = x1_del + size_x, y2_del = y1_del + size_y;
    
    int x1_bk = 700, y1_bk = 10, x2_bk = 780, y2_bk = 60;
    int x1_boder = 90, y1_boder = 100, x2_boder = 770, y2_boder = 450;
	
	Button btPoly = {x1_poly, y1_poly, x2_poly, y2_poly};
    Button btLine = {x1_line, y1_line, x2_line, y2_line};
    Button btCrop = {x1_crop, y1_crop, x2_crop, y2_crop};
    Button btDel = {x1_del, y1_del, x2_del, y2_del};
    Button btboder = {x1_boder, y1_boder, x2_boder, y2_boder};
    
    Button btback = {x1_bk, y1_bk, x2_bk, y2_bk};
    
    Button btcolor[16];
    
   	button_poly(btPoly, 2 , 15);
    button_line(btLine, 2 , 15);
    button_crop(btCrop, 2 , 15);
    button_del(btDel, 2 , 15);
    boder(btboder, 2);
    button_back(btback,2,15);
    
    //----------------------Ve cac button color
    int x1 = 90, y1 = 65, x2 = x1 + 30, y2=y1+30;
    int spcolor = 12;
    for (int i = 1 ;i<16; i++)
    {
    	btcolor[i] = {x1, y1, x2, y2};
    	bt_color(btcolor[i],i);
    	x1+=30+spcolor; x2+=30+spcolor;
    	
    	
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
			//Hover button poly
			if (check_button(btPoly,p))
			{
				setcolor(15);
				button_poly(btPoly, 5 , 3);
				temp3=1;
			}
			else if (!check_button(btPoly, p) && temp3==1)
			{
				setcolor(15);
				button_poly(btPoly, 2 , 15);
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
			//Hover button Crop
			if (check_button(btCrop,p))
			{
				setcolor(15);
				button_crop(btCrop, 5 , 3);
				temp1=1;
			}
			else if (!check_button(btCrop, p) && temp1==1 )
			{
				setcolor(15);
				button_crop(btCrop, 2 , 15);
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
			sprintf(s,"\t Toa Do (%d,%d) \t",x,y);
			outtextxy(380,20,s);	
   		}
   
   		if (ismouseclick(WM_LBUTTONUP))
		{
	   		int x,y;
			getmouseclick(WM_LBUTTONUP, x, y);
			clearmouseclick(WM_LBUTTONUP);
			clearmouseclick(WM_LBUTTONDOWN);
			point p = {x,y};
			if (check_button(btPoly,p))
			{
				while(1)
				{  
					delay(0.01);
					point p1;
					if (ismouseclick(WM_MOUSEMOVE))
					{
						getmouseclick(WM_MOUSEMOVE, x, y);
						clearmouseclick(WM_MOUSEMOVE);
						setcolor(15);
						sprintf(s,"\t Toa Do (%d,%d) \t",x,y);
						outtextxy(380,20,s);
					}
					  
			 	 	if (ismouseclick(WM_LBUTTONDOWN))
				 	{  
					   	getmouseclick(WM_LBUTTONDOWN, x, y);
	            		clearmouseclick(WM_LBUTTONDOWN);
	           		 	p1 = {x,y};
	           		 	if (!check_button(btboder,p1)) break;
	           		 	poly[n1] = p1;
	           		 	n1++;
			 		}
			 		
			 	 	if(ismouseclick(WM_RBUTTONDOWN))
            		{
	            		getmouseclick(WM_RBUTTONDOWN, x, y);
						clearmouseclick(WM_RBUTTONDOWN);
						if (!check_button(btboder,p1)) break;
           		 		p1 = {x,y};
            			poly[n1] = p1;
	           		 	n1++;
            			setcolor(color);
            			for (int i= 0; i<n1; i++)
            			{   int k =(i+1) %n1;
            				line(poly[i].x,poly[i].y,poly[k].x,poly[k].y);
            			}
            			 		 	
            		}
				}
			}
			if (check_button(btDel,p))
			{  
				cleardevice();
				goto drawwd;
			}
			
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
						sprintf(s,"\t Toa Do (%d,%d) \t",x,y);
						outtextxy(380,20,s);
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
			
			if (check_button(btCrop,p))
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
						outtextxy(380,20,s);
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
						Poly_Hogman() ;
            		}
        		}
			}

			for (int i=1; i<16; i++)
			{
				if(check_button(btcolor[i],p))
				{
					color = i;
					break;
				}	
			}
			if(check_button(btback,p))
			{
				goto out;
			}
   		}  
 	}
 	out: 
 	cleardevice();
}
//-----------------------------------------------------------------------------------------------------------------------------------

int main()
{
	gnew:
    int x, y;
    initwindow(800,500);
    
    int t = graphic0();
    if(t == 1) {
    	cleardevice();
    	goto wd1;
    }
    else if(t == 2)
    {
    	cleardevice();
    	setlinestyle(0,0,0);
    	goto wd2;
    }
    else
    {
    	cleardevice();
    	goto wd3;
    }
    
    wd1:
    Graphic1(); 
    closegraph();
	goto gnew;
	
	wd2:
	Graphic();
	closegraph();
	goto gnew;
	wd3:
	Graphic2();
	closegraph();
	goto gnew;
    getch();
    closegraph();
}
	
