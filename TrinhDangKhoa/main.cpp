#include<graphics.h>
#include<stdio.h>
#include<math.h>
#define maxdinh 20
#define INPUT "scanline.inp"

//Khai bao nut nhan co 2 diem (diem tren trai va diem duoi phai)
struct button{
	int x1, y1, x2, y2;//(x1, y1): vi tri diem tren trai; (x2, y2): vi tri diem duoi phai
};

//Khai bao chu hien thi
struct text{
	int x, y;
	char txt[255];
};

//Khai bao diem
struct point{
	int x, y;
};

//Khai bao bien
point pt[maxdinh];//Toa do cac dinh cua da giac
int n;//So dinh cua da giac
FILE *fp;//Con tro tap tin fp
float m[maxdinh];//He so goc cac canh cua da giac
int ymin, ymax;
int color = 15;//Mau mac dinh khi to mau
int oldcolor;
int fillspeed = 500;//Toc do to mau cho thuat toan floodfill va boundaryfill

//Nhap da giac bang ban phim
void keyboard(){
	printf("Nhap so dinh cua da giac: ");
	scanf("%d", &n);
	printf("CAC DINH CUA DA GIAC PHAI CO TOA DO: 30 < X < 1200, 100 < Y < 1040");
	printf("\nNhap cac dinh cua da giac: \n");
	for(int i=0; i<n; i++){
		printf("Nhap dinh [%d]: ", i);
		do{
			printf("\nNhap x: ");
			scanf("%d", &pt[i].x);
			printf("Nhap y: ");
			scanf("%d", &pt[i].y);
			if(pt[i].x <= 30 || pt[i].x >= 1200 || pt[i].y <=100 || pt[i].y >= 1040){
				printf("Toa do ban nhap khong nam trong man hinh. Vui long nhap lai!");
			}
		}while(pt[i].x <= 30 || pt[i].x >= 1200 || pt[i].y <=100 || pt[i].y >= 930);
	}
	
	//Them 1 dinh thu 4 == dinh thu 0
	pt[n].x = pt[0].x;
	pt[n].y = pt[0].y;
	
	//In ra cac dinh cua da giac
	printf("So dinh cua da giac: %d", n);
	printf("\nToa do cac dinh cua da giac: \n");
	for(int i=0; i<n; i++){
		printf("%d", pt[i].x);
		printf("%5d", pt[i].y);
		printf("\n");
	}
}

//Nhap da giac file
void readfile(){
	fp = fopen(INPUT, "r");//Mo tap tin de doc
	if(fp == NULL){
		printf("\nFile not found");
	}
	fscanf(fp, "%d", &n);
	printf("So dinh cua da giac: %d", n);
	
	//Doc cac dinh cua da giac
	for(int i=0; i<n; i++){
		fscanf(fp, "%d %d", &pt[i].x, &pt[i].y);	
	}
	
	//Them 1 dinh thu 4 == dinh thu 0
	pt[n].x = pt[0].x;//x[n] = x[0]
	pt[n].y = pt[0].y;//y[n] = y[0]
	
	//In ra cac dinh cua da giac
	printf("\nToa do cac dinh cua da giac: \n");
	for(int i=0; i<n; i++){
		printf("%d", pt[i].x);
		printf("%5d", pt[i].y);
		printf("\n");
	}
	fclose(fp);
}

//Ve da giac
void drawpoly(){
	for(int i=0; i<n; i++){
		setcolor(0);//Thiep lap mau ve
		setlinestyle(1, 0, 3);
		line(pt[i].x, pt[i].y, pt[i+1].x, pt[i+1].y);
	}
}


//------------------------------------------------------------------------Scanline----------------------------------------------------------------------//
void hesogoc(){
	for(int i=0; i<n; i++){
		//Co 2 truong hop dac biet: dy = 0 va dx = 0
		//xsau = xtruoc + (y - ytruoc) / m
		if(pt[i+1].y == pt[i].y){//dy = 0
			m[i] = 1;//Dang le m=0 nhung do cong thuc tim xgd co chia m nen phep chia bao loi (m chi can #0)
		}
		else{
			if(pt[i+1].x == pt[i].x){//dx = 0
				m[i] = 9999;//Man hinh co do phan giai 1600x1200 nen m = 9999 la vuot qua size man hinh = vo cung
			}
			else{
				//m=dy/dx;
				m[i] = (float)(pt[i+1].y - pt[i].y) / (pt[i+1].x - pt[i].x);//(yi+1 - yi) / (xi+1 - xi)	
			}	
		}
	}
	printf("\nHe so goc cac canh cua da giac: ");
	for(int i=0; i<n; i++){
		printf("%.1f  ",m[i]);
	}
}

void minmax(){
	ymin = pt[0].y;//ymin = tung do dinh 0
	ymax = pt[0].y;//ymax = tung do dinh 0
	for(int i=0; i<n; i++){
		if(ymin > pt[i].y){
			ymin = pt[i].y;
		}
		if(ymax < pt[i].y){
			ymax = pt[i].y;
		}
	}
	printf("\nymin = %d", ymin);
	printf("\nymax = %d\n", ymax);
}

void scanline(){
	printf("-----------------------------------------------Scanline-----------------------------------------------");
	hesogoc();
	minmax();
	int xgd[maxdinh];
	for(int y=ymin; y<ymax; y++){
		//Xet xem co giao diem hay khong co giao diem tung canh cua da giac
		int count = 0;//Luu giu so giao diem cua moi y so voi cac canh cua da giac		
		//Moi lan tang dong quet thi dem se lai ve 0 hay so giao diem = 0
		for(int i=0; i<n; i++){//Xet tung canh cua da giac
			if((y < pt[i].y && y <= pt[i+1].y) || (y >= pt[i].y && y > pt[i+1].y)){//Dong quet nam duoi hoac tren ca 2 tung do dinh
				printf("Khong co giao diem y = %d voi canh (%d,%d) - (%d,%d)\n", y, pt[i].x, pt[i].y, pt[i+1].x, pt[i+1].y);
			}
			else{
				printf("Ton tai giao diem giua y = %d voi canh cua da giac\n", y);
				//Xac dinh hoanh do giao diem
				xgd[count++] = round(pt[i].x + (y - pt[i].y) / m[i]);
			}
		}		
		
		//In ra cac xgd cua y voi cac canh cua da giac
		printf("Cac hoanh do giao diem cua y = %d voi cac canh cua da giac: ",y);
		for(int i=0; i<count; i++){
			printf("(%d,%d)  ",xgd[i], y);
		}		
		printf("\n");
		
		//Sap xep cac dinh theo hoanh do cua xgd
		for(int i=0; i<count-1; i++){
			for(int j=i+1; j<count; j++){
				if(xgd[i] > xgd[j]){
					int temp = xgd[i];
					xgd[i] = xgd[j];
					xgd[j] = temp;
				}
			}
		}
		
		//Noi cac dinh cua hoanh do giao diem lai voi nhau
		for(int i=0; i<count-1; i=i+2){
			setcolor(color);
			line(xgd[i], y, xgd[i+1], y);//Vi cung y
		}
		delay(10);
	}	
	printf("-------------------------------------------------End--------------------------------------------------\n");
}
//------------------------------------------------------------------------End---------------------------------------------------------------------------//



//----------------------------------------------------------------------Floodfill-----------------------------------------------------------------------//
//To mau ben phai
void fillright(int xa, int ya)
{ 
	if(getpixel(xa, ya) == oldcolor){
		putpixel(xa, ya, color);
		
		//Toc do to mau
	  	fillspeed--;
		if(fillspeed == 0){
			delay(20);
			fillspeed = 500;
		}
		
		//To mau het ve phia ben phai
	  	fillright(++xa, ya);
	  	xa--;  	  
	  	
		//To mau tu diem ke bien den tan cung ben duoi
		fillright(xa, ya + 1);
		
	  	//To mau tu diem ke bien den tan cung ben tren
	  	fillright(xa, ya - 1);
	}
}

//To mau ben trai
void fillleft(int xa, int ya)
{ 
	if(getpixel(xa, ya) == oldcolor){ 
	  	putpixel(xa, ya, color);
	  	
	  	//Toc do to mau
	  	fillspeed--;
		if(fillspeed == 0){
			delay(20);
			fillspeed = 500;
		}	
		
		//To mau het ve phia ben trai
	  	fillleft(--xa, ya);
	  	xa++;
	  	
	  	//To mau tu diem ke bien den tan cung ben duoi
		fillleft(xa, ya + 1);
		
	  	//To mau tu diem ke bien den tan cung ben tren
	  	fillleft(xa, ya - 1);
	}
}

//to mau da giac
void floodfill(int x, int y)
{ 
  	fillright(x, y);
	fillleft(x-1, y);
}
//---------------------------------------------------------------------------End------------------------------------------------------------------------//



//-----------------------------------------------------------------------Boundaryfill-------------------------------------------------------------------//
//To mau
void boundaryright(int xa, int ya)
{ 
			
  	if((getpixel(xa, ya) != 0) && (getpixel(xa, ya) != color)) 
  	{
  	  	putpixel(xa, ya, color);
  	  	
  	  	//Toc do to mau
	  	fillspeed--;
		if(fillspeed == 0){
			delay(20);
			fillspeed = 500;
		}
  	  
		//To mau het ve phia ben phai
  	  	boundaryright(++xa, ya);
  	  
  	  	//Giam x - 1
  	  	xa--;
  	  
		//to mau tu diem ke bien den tan cung ben duoi
  	  	boundaryright(xa, ya+1);
  	  
  	  	//to mau tu diem ke bien den tan cung ben tren
  	  	boundaryright(xa, ya-1);
	}	
}

//to nua ben trai
void boundaryleft(int xa, int ya)
{ 
  	if((getpixel(xa, ya) != 0) && (getpixel(xa, ya) != color)) 
  	{
  	  	putpixel(xa, ya, color);
  	  	
  	  	//Toc do to mau
	  	fillspeed--;
		if(fillspeed == 0){
			delay(20);
			fillspeed = 500;
		}
  	  
		//To mau het ve phia ben phai
  	  	boundaryleft(--xa,ya);
  	  
  	  	//Tang x - 1
  	  	xa++;
  	  
		//To mau tu diem ke bien den tan cung ben duoi
  	  	boundaryleft(xa,ya+1);
  	  
  	  	//To mau tu diem ke bien den tan cung ben tren
  	  	boundaryleft(xa,ya-1);
	}	
}

void boundaryfill(int x, int y)
{
	boundaryright(x, y);
	boundaryleft(x-1, y);
}
//---------------------------------------------------------------------------End------------------------------------------------------------------------//



//------------------------------------------------------------------------Tao giao dien-----------------------------------------------------------------//
//Nut mau
void button_color(button btn, int color){
	setcolor(color);
	setfillstyle(1, color);
	rectangle(btn.x1, btn.y1, btn.x2, btn.y2);
	floodfill(btn.x1 + 2, btn.y1 + 2, color);
}

//Nut chuc nang
void button_exe(button btn, int color_btn, text txt, int color_txt){
	setcolor(color_btn);
	setlinestyle(0, 0, 3);
	rectangle(btn.x1, btn.y1, btn.x2, btn.y2);
	settextstyle(10, 0, 5);
	setcolor(color_txt);
	outtextxy(txt.x, txt.y, txt.txt);
}

//Kiem tra 1 diem co nam trong 1 nut khong
bool check_button(button btn, int x, int y){
	if(x >= btn.x1 && x <= btn.x2 && y >= btn.y1 && y <= btn.y2)
		return true;
	return false;
}

//Giao dien man hinh chinh
void GUI_init(){
	gui:
	//Man hinh hien thi
	setcolor(3);
	setlinestyle(0, 0 ,3);
	rectangle(30, 100, 1200, 1040);
	button btn_ui = {30, 100, 1200, 1040};	
	
	//Thong tin tac gia
	settextstyle(10, 0, 3);
	setcolor(RED);
	char cr1[] = "MSSV: 63134337";
	char cr2[] = "Name: Trinh Dang Khoa";
	char cr3[] = "Class: 63.CNTT-4";
	outtextxy(1240, 1070, cr1);
	outtextxy(1240, 1110, cr2);
	outtextxy(1240, 1150, cr3);
	
	//Cac nut mau
	button btn_color[17];
	int x1 = 1230, y1 = 100, x2 = 1310, y2 = 180;
	int k = 0;
	for(int i = 0; i < 16; i++){		
		if(i == 11){
			continue;
		}
		k++;
		btn_color[i] = {x1, y1, x2, y2};
		button_color(btn_color[i], i);
		x1 += 110; x2 += 110;
		if(k == 3){
			y1 += 110;
			y2 += 110;
			x1 = 1230;
			x2 = 1310;
			k = 0;
		}
	}
	
	//Nut loadfile
	button btn_lf = {1230, 680, 1530, 780};
	text txt_lf = {1275, 700, "Load file"};
	button_exe(btn_lf, 0, txt_lf, 0);
	
	//Nut keyboard
	button btn_kb = {1230, 810, 1530, 910};
	text txt_kb = {1275, 835, "Keyboard"};
	button_exe(btn_kb, 0, txt_kb, 0);
	
	//Nut dung chuot
	button btn_m = {1230, 940, 1530, 1040};
	text txt_m = {1320, 965, "Mouse"};
	button_exe(btn_m, 0, txt_m, 0);
	
	//Nut scanline
	button btn_sl = {30, 1070, 240, 1180};
	text txt_sl = {35, 1100, "Scanline"};
	button_exe(btn_sl, 0, txt_sl, 0);
	
	//Nut floodfill
	button btn_ff = {270, 1070, 510, 1180};
	text txt_ff = {280, 1100, "Floodfill"};
	button_exe(btn_ff, 0, txt_ff, 0);
	
	//Nut boundaryfill
	button btn_bf = {540, 1070, 860, 1180};
	text txt_bf = {550, 1100, "Boundaryfill"};
	button_exe(btn_bf, 0, txt_bf, 0);
	
	//Nut xoa
	setcolor(0);
	line(1010, 1090, 1080, 1160);
	line(1010, 1160, 1080, 1090);
	button btn_del = {890, 1070, 1200, 1180};
	text txt_del = {820, 990, ""};
	button_exe(btn_del, 0, txt_del, 0);
	
	//Xu ly dung chuot
	while(1){
		delay(0.1);
		
		char s[100];
		int x, y;
		//Tao hieu ung hover nut		
		if(ismouseclick(WM_MOUSEMOVE)){	
			getmouseclick(WM_MOUSEMOVE, x, y);	
	
			//Hien toa do khi di chuyen chuot
			setcolor(0);
			sprintf(s, "\t Toa Do (%d,%d) \t", x, y);
			outtextxy(650, 10, s);
			
			//Nut loadfile
			if(check_button(btn_lf, x, y)){
				button_exe(btn_lf, 1, txt_lf, 1);
			}else if(!check_button(btn_lf, x, y) ){
				button_exe(btn_lf, 0, txt_lf, 0);
			}
			
			//Nut keyboard
			if(check_button(btn_kb, x, y)){
				button_exe(btn_kb, 1, txt_kb, 1);
			}else if(!check_button(btn_kb, x, y) ){
				button_exe(btn_kb, 0, txt_kb, 0);
			}
			
			//Nut dung chuot
			if(check_button(btn_m, x, y)){
				button_exe(btn_m, 1, txt_m, 1);
			}else if(!check_button(btn_m, x, y)){
				button_exe(btn_m, 0, txt_m, 0);
			}
			
			//Nut scanline
			if(check_button(btn_sl, x, y)){
				button_exe(btn_sl, 2, txt_sl, 2);
			}else if(!check_button(btn_kb, x, y)){
				button_exe(btn_sl, 0, txt_sl, 0);
			}
			
			//Nut floodfill
			if(check_button(btn_ff, x, y)){
				button_exe(btn_ff, 2, txt_ff, 2);
			}else if(!check_button(btn_ff, x, y)){
				button_exe(btn_ff, 0, txt_ff, 0);
			}
			
			//Nut boundaryfill
			if(check_button(btn_bf, x, y)){
				button_exe(btn_bf, 2, txt_bf, 2);
			}else if(!check_button(btn_kb, x, y)){
				button_exe(btn_bf, 0, txt_bf, 0);
			}
			
			//Nut xoa
			if(check_button(btn_del, x, y)){
				button_exe(btn_del, 12, txt_del, 12);
				setcolor(12);
				line(1010, 1090, 1080, 1160);
				line(1010, 1160, 1080, 1090);
			}else if(!check_button(btn_del, x, y)){
				button_exe(btn_del, 0, txt_del, 0);
				setcolor(0);
				line(1010, 1090, 1080, 1160);
				line(1010, 1160, 1080, 1090);
			}
		}
		
		//Tao su kien khi nhan nut
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			
			//Nut loadfile
			if(check_button(btn_lf, x, y)){
				readfile();
				drawpoly();
			}
					
			//Nut keyboard
			if(check_button(btn_kb, x, y)){
				keyboard();
				drawpoly();
			}
			
			//Nut dung chuot
			if(check_button(btn_m, x, y)){
				n = 0;
				while(1){
					delay(0.1);
					
					if(ismouseclick(WM_MOUSEMOVE)){	
						getmouseclick(WM_MOUSEMOVE, x, y);	
						//Hien toa do khi di chuyen chuot
						setcolor(0);
						sprintf(s, "\t Toa Do (%d,%d) \t", x, y);
						outtextxy(650, 10, s);
					}
					
					//Nhap da giac bang chuot
					if(ismouseclick(WM_LBUTTONDOWN)){
						getmouseclick(WM_LBUTTONDOWN, x, y);
						clearmouseclick(WM_LBUTTONDOWN);
						if(check_button(btn_ui, x, y)){
							setcolor(0);
							circle(x, y, 2);
							pt[n].x = x;
							pt[n].y = y;
							n++;
						}
					}
					if(ismouseclick(WM_RBUTTONDOWN)){
						clearmouseclick(WM_RBUTTONDOWN);
						
						//Them 1 dinh thu 4 == dinh thu 0
						pt[n].x = pt[0].x;
						pt[n].y = pt[0].y;
						drawpoly();
						
						//In ra cac dinh cua da giac
						printf("So dinh cua da giac: %d", n);
						printf("\nToa do cac dinh cua da giac: \n");
						for(int i=0; i<n; i++){
							printf("%d", pt[i].x);
							printf("%5d", pt[i].y);
							printf("\n");
						}
						break;
					}	
				}
			}
			
			//Cac nut mau
			for(int i=0; i<16; i++){
				if(i == 11) continue;
				if(check_button(btn_color[i], x, y)){
					color = i;
				}
			}
			
			//Nut scanline
			if(check_button(btn_sl, x, y)){
				scanline();
			}
			
			//Nut floodfill
			if(check_button(btn_ff, x, y)){
				while(1){
					delay(0.1);
					if(ismouseclick(WM_LBUTTONDOWN)){
						getmouseclick(WM_LBUTTONDOWN, x, y);
						if(check_button(btn_ui, x, y)){
							oldcolor = getpixel(x, y);
							floodfill(x, y);			
							break;
						}	
					}
				}
			}	
			
			//Nut boundaryfill
			if(check_button(btn_bf, x, y)){
				while(1){
					delay(0.1);
					if(ismouseclick(WM_LBUTTONDOWN)){
						getmouseclick(WM_LBUTTONDOWN, x, y);
						if(check_button(btn_ui, x, y)){
							boundaryfill(x, y);			
							break;
						}	
					}
				}
			}	
			
			//Nut xoa
			if(check_button(btn_del, x, y)){
				cleardevice();
				color = 15;
				goto gui;
			}	
		}
	}
}
//---------------------------------------------------------------------------End------------------------------------------------------------------------//

int main(){
	initwindow(1600, 1300);
	setbkcolor(11);
	cleardevice();
	GUI_init();
}
