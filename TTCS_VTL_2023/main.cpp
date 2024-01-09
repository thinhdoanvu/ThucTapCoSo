#include<iostream>
#include<graphics.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAX 100
#define input "data.inp"
#define input "datatamgiac.inp"
#define input "datatron.inp"
#include<Math.h>
#define ROUND(a) ((float)(a+0.5))

using namespace std;

//khai bao protype
void readfile();
void readfile2();
void Indiem(struct toado m[MAX], int size);
void ART_init();
void keyboard();
void ART_cool();
void translation();
void rotation();
void scaling();
void reset();
void close();
void inputCir();
void circle();

//Khai bao bien
int sodinh; // so dinh 
FILE *fp; //file
int x,y;
int r, p;
struct toado{
	int x, y;
};

struct toado td[MAX]; //moi td là mot kieu toado(x,y,value)

void Indiem(struct toado m[MAX], int size){
	for(int i = 0; i < size; i++){
		cout << m[i].x <<" " << m[i].y <<" \n";
	}
}

void readfile(){
	fp=fopen("data.inp","r");
	if(fp==NULL){
		cout << "Find not found";
		return ;
	}
	fscanf(fp, "%d", &sodinh);
	cout << "So ptu can xep: " << sodinh << "\n";
	for(int i=0;i<sodinh;i++){
		fscanf(fp, "%d %d", &td[i].x, &td[i].y);
	}
	//in cac diem
	Indiem(td, sodinh);
	fclose(fp);
	ART_cool();
}

void readfile2(){
	fp=fopen("datatamgiac.inp","r");
	if(fp==NULL){
		cout << "Find not found";
		return ;
	}
	fscanf(fp, "%d", &sodinh);
	cout << "So ptu can xep: " << sodinh << "\n";
	for(int i=0;i<sodinh;i++){
		fscanf(fp, "%d %d", &td[i].x, &td[i].y);
	}
	//in cac diem
	Indiem(td, sodinh);
	fclose(fp);
	ART_cool();
}

void readfile3(){
	fp=fopen("datatron.inp","r");
	if(fp==NULL){
		cout << "Find not found";
		return ;
	}
	fscanf(fp, "%d", &sodinh);
	cout << "So ptu can xep: " << sodinh << "\n";
	for(int i=0;i<sodinh;i++){
		fscanf(fp, "%d %d", &td[i].x, &td[i].y);
	}
	//in cac diem
	Indiem(td, sodinh);
	fclose(fp);
	circle();
}

void ART_init(){
	setcolor(YELLOW);
	//khung lon
	setlinestyle(0,1,3);
	rectangle(10,10,750,650);
	//o truy van
	setcolor(GREEN);
	rectangle(790,10,980,50);
	settextstyle(2,0,8);
	setcolor(WHITE);
	outtextxy(800,20,"Load file");
	
	setcolor(GREEN);
	rectangle(790,110,980,150);
	settextstyle(2,0,8);
	setcolor(WHITE);
	outtextxy(800,120,"Keyboard");
	
	setcolor(GREEN);
	rectangle(790,210,980,250);
	settextstyle(2,0,8);   
	setcolor(WHITE);
	outtextxy(800,220,"Translation");
	
	setcolor(GREEN);
	rectangle(790,310,980,350);
	settextstyle(2,0,8);
	setcolor(WHITE);
	outtextxy(800,320,"Rotation");
	
	setcolor(GREEN);
	rectangle(790,410,980,450);
	settextstyle(2,0,8);
	setcolor(WHITE);
	outtextxy(800,420,"Scaling");
	
	setcolor(GREEN);
	rectangle(790,510,980,550);
	settextstyle(2,0,8);
	setcolor(WHITE);
	outtextxy(800,520,"Reset");
	
	setcolor(GREEN);
	rectangle(790,610,980,650);
	settextstyle(2,0,8);
	setcolor(WHITE);
	outtextxy(800,620,"Close");
	
//	thong tin SV
	settextstyle(2,0,7);
	outtextxy(10,670,"GVHD : DOAN VU THINH");
	outtextxy(10,700,"SVTH : VO THUY LINH");
	outtextxy(10,730,"LOP : 63.CNTT-4");
}


void Click(){
    int x_mouse, y_mouse, chose;
    while (1) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x_mouse, y_mouse);

            if (x_mouse > 790 && x_mouse < 980 && y_mouse > 10 && y_mouse < 50) { 
            	cout << "Chon file doc: \n";
            	cout << "1. File hinh vuong \n";
            	cout << "2. File hinh tam giac \n";
            	cout << "3. File hinh tron \n";
            	//nhap lua chon
            	cout << "Vui long nhap file can doc: ";
            	cin >> chose;
            	// Nút "Read file"
            	if(chose == 1){
            		cout << "Doc file 1 ..." << "\n";
            		readfile();
				}
				else if(chose == 2){
					cout << "Doc file 2 ..." << "\n";
					readfile2();
				}
				else if(chose == 3){
					cout << "Doc file 3 ..." << "\n";
					readfile3();	
				}
			    else{
			    	cout << "Doc file khong hop le!";
				}           
            } 
            // Nút "Keyboard"
			if (x_mouse > 790 && x_mouse < 980 && y_mouse > 110 && y_mouse < 150) { 
                keyboard();
            }
            // Nút "Translation"
            if (x_mouse >  790 && x_mouse < 980 && y_mouse > 210 && y_mouse < 250) {
            	translation();
            }
			// Nút "Rotation"
            if (x_mouse >  790 && x_mouse < 980 && y_mouse > 310 && y_mouse < 350) {
            	rotation();
            }  
			// Nút "Scaling"
            if (x_mouse >  790 && x_mouse < 980 && y_mouse > 410 && y_mouse < 450) {
            	scaling();
            } 
            // Nút "Reset"
            if (x_mouse >  790 && x_mouse < 980 && y_mouse > 510  && y_mouse < 550) {
            	reset();            
            }            
			// Nút "Close"
            if (x_mouse >  790 && x_mouse < 980 && y_mouse > 610  && y_mouse < 650) {
            	close();
            }              
        }
        delay(100);
    }
}

void keyboard(){
	cout << "Nhap so dinh: ";
	cin >> sodinh;
	cout << "Nhap toa do: \n";
	for(int i = 0; i < sodinh; i++){
		cin >> td[i].x >> td[i].y;
	}
	if(sodinh > 2){
		ART_cool();
	}
	else{
		circle();
	}
}

void ART_cool(){
	for (int i = 0; i < sodinh - 1; i++) {
        line(td[i].x, td[i].y, td[i + 1].x, td[i + 1].y);
    }
    line(td[sodinh - 1].x, td[sodinh - 1].y, td[0].x, td[0].y);  
	delay(100); 
}

void circle(){
	//midpoint
	if(sodinh != 2){
		return;
	}
	r = sqrt(pow(td[1].x - td[0].x, 2) + pow(td[1].y - td[0].y, 2));
	x=0;
  	y=r;
  	p= 3 - 2 * r; 
  	while(x<=y)
  	{
    	putpixel(td[0].x+x,td[0].y+y,255);
	  	putpixel(td[0].x-x,td[0].y+y,255);
	  	putpixel(td[0].x-x,td[0].y-y,255);
	  	putpixel(td[0].x+x,td[0].y-y,255);
	  	putpixel(td[0].x+y,td[0].y+x,255);
	  	putpixel(td[0].x-y,td[0].y+x,255);
	  	putpixel(td[0].x+y,td[0].y-x,255);
	  	putpixel(td[0].x-y,td[0].y-x,255);
    	if(p<0){
    		p+=4*x+6;
		}
    	else{
    		p+=4*(x-y)+10;
      		y--;
    	}
    	x++;		
	}
	delay(100);
}


void translation(){
	
	int targetx, targety;
	cout << "Khoang cach di chuyen theo truc x = ";
	cin >> targetx;
	cout << "Khoang cach di chuyen theo truc y = ";
	cin >> targety;
	int steps = 10;
	int stepx = (targetx - x) / steps;
	int stepy = (targety - y) / steps;
	for (int step = 1; step <= steps; step++) {
        x += stepx;
        y += stepy;
        for (int i = 0; i < sodinh; i++) {
            td[i].x = td[i].x + stepx;
            td[i].y = td[i].y + stepy;
        }
	    cleardevice();
		ART_init();
		if(sodinh > 2){
			ART_cool();
		}
		else{
			circle();
		}	 
	}
}

void rotation(){
	int targetx, targety, degree;
	cout << "Toa do cua tam quay (x): ";
	cin >> targetx;
	cout << "Toa do cua tam quay (y): ";
	cin >> targety;
	cout << "He so goc quay (degree): ";
	cin >> degree;
	float radian = (float) degree / (180 * 3.14); //hsg / 180 * pi
  	float dx;
  	float dy;
  	int steps = 10;
	float angleDelta = radian / steps;
	for (int step = 1; step <= steps; step++) {
        float currentAngle = step * angleDelta; 
	  	for(int i = 0; i < sodinh; i++){
	  		dx = (float)(td[i].x - targetx); //toado cu - toado moi
		    dy = (float)(td[i].y - targety);
		    td[i].x = floor(targetx + dx * cos(currentAngle) - dy * sin(currentAngle)); //floor: lam tron so thap phan
		    td[i].y = floor(targety + dx * sin(currentAngle) + dy * cos(currentAngle));
		}
	    cleardevice();
		ART_init();
	    if(sodinh > 2){
			ART_cool();
		}
		else{
			circle();
		}
	}
}

void scaling(){
	float scale_x, scale_y;
	float dx;
  	float dy;
	cout << "Toa do moi cua doi tuong tren truc x: ";
	cin >> x;
	cout << "Toa do moi cua doi tuong tren truc y: ";
	cin >> y;
	cout << "Ti le bien dang theo truc x: ";
	cin >> scale_x;
	cout << "Ti le bien dang theo truc y: ";
	cin >> scale_y;
	int steps = 10; 
    float scale_xDelta = (scale_x - 1) / steps;
    float scale_yDelta = (scale_y - 1) / steps;
	for(int step = 1; step <= steps; step++)
    { 
        float currentScale_x = 1 + step * scale_xDelta / 10 ; 
        float currentScale_y = 1 + step * scale_yDelta / 10;        	
        for(int i = 0; i < sodinh; i++)
        {
            // chon tam cua doi tuong la diem (x, y)
            td[i].x = x + (int)((float)(td[i].x - x) * currentScale_x);
            td[i].y = y + (int)((float)(td[i].y - y) * currentScale_y);      	
        }
        if(sodinh > 2){
        	cleardevice();
			ART_init();
			ART_cool();
		}
        else{
        	cleardevice();
			ART_init();
			circle();
		}
	}
}

//reset
void reset(){
	sodinh = 0;
    cleardevice();
    ART_init();
}

//exit
void close(){ 
    exit(0);
}


int main(){
	//khoi tao man hinh do hoa hien thi
	initwindow(1000,800);	
	//hien thi giao dien chinh
	ART_init();
	//an chuot
	Click();
	//dung man hinh
	getch();
}
