#include<stdio.h>
#include<winbgim.h>
#include<stdlib.h>
#include <cstdlib>
#include <ctime>
#define MAX 100
#define INPUT "points.inp"
void readfile();
void printpoints(struct toado m[MAX], int size);
void GUI_init();
void GUI_increase();
void GUI_decrease();
void GUI_loadfile();
void GUI_input();
void GUI_keyboard();
void GUI_random();
void mouse();
void input();
void keyboard();
void drawpoint(struct toado point, int color);
void drawpoints(struct toado points[MAX], int size);
void Random();
void increase();
void decrease();
void reset();
void exit();
//bien toan cuc
int sodinh;//so phan tu can sap xep
FILE *fp;
char buffer[10];
int enable_click = 1;

struct toado{
	int x;
	int y;
	int value;
};
struct toado td[MAX];//moi td la 1 kieu toado(x,y,value)
void readfile(){
	cleardevice();
	GUI_loadfile();
	fp=fopen(INPUT,"r");
	if(fp==NULL){
		printf("Find not found");
		return;
	}
	//else
	//doc dong dau tien cua tap tin
	fscanf(fp,"%d",&sodinh);
	printf("So phan tu can sap xep: %d\n",sodinh);
	//doc lan luot tung phan tu: moi phan tu cos 3 tham so: toado_x. toado_y, giatri	
	for(int i=0;i<sodinh;i++){
		fscanf(fp,"%d %d %d",&td[i].x, &td[i].y, &td[i].value);
	}
	
	//in ra cac diem 
	printpoints(td,sodinh);
	fclose(fp);
}
void printpoints(struct toado m[MAX], int size){
	for(int i=0;i<size;i++){
		printf("%d %d %d\n",m[i].x, m[i].y, m[i].value);
	}
}
void GUI_init(){
	setcolor(15);
	//main border
	setlinestyle(0,1,3);//setlinestyle(int linestyle, unsigned pattern, int thickness)
	rectangle(250,50,1250,740);
	//
	settextstyle(6,0,4);
	outtextxy(200,750,"|GVHD: Doan Vu Thinh |");
	outtextxy(740,750,"|Ten sv: Tran Hang Tong Dat|");
	
	//input number button
	rectangle(35,50,210,200);	
	settextstyle(6,0,4);
	outtextxy(110,105,"N");
	//keyboard button 
	rectangle(35,230,210,380);
	settextstyle(6,0,3);
	outtextxy(52,287,"Keyboard");
	//Random button
	rectangle(35,410,210,560);
	settextstyle(6,0,3);
	outtextxy(64,465,"Random");
	//Load file button 
	rectangle(35,590,210,740);
	settextstyle(6,0,3);
	outtextxy(54,650,"Load File");
	//increase button
	rectangle(1290,50,1465,200);
	settextstyle(6,0,3);
	outtextxy(1303,105,"Increasing");
	//Decrease button 
	rectangle(1290,230,1465,380);
	settextstyle(6,0,3);
	outtextxy(1300,287,"Decreasing");
	//Reset button
	rectangle(1290,410,1465,560);
	settextstyle(6,0,3);
	outtextxy(1338,467,"Reset");
	//Exit button 
	rectangle(1290,590,1465,740);
	settextstyle(6,0,3);
	outtextxy(1350,650,"Exit");

}
void GUI_input(){
	setcolor(15);
	//main border
	setlinestyle(0,1,3);//setlinestyle(int linestyle, unsigned pattern, int thickness)
	rectangle(250,50,1250,740);
	//
	settextstyle(6,0,4);
	outtextxy(200,750,"|GVHD: Doan Vu Thinh |");
	outtextxy(740,750,"|Ten sv: Tran Hang Tong Dat|");
	
	//input number button
	setcolor(4);
	rectangle(35,50,210,200);	
	settextstyle(6,0,4);
	outtextxy(110,105,"N");
	//keyboard button 
	setcolor(15);
	rectangle(35,230,210,380);
	settextstyle(6,0,3);
	outtextxy(52,287,"Keyboard");
	//Random button
	rectangle(35,410,210,560);
	settextstyle(6,0,3);
	outtextxy(64,465,"Random");
	//Load file button 
	rectangle(35,590,210,740);
	settextstyle(6,0,3);
	outtextxy(54,650,"Load File");
	//increase button
	rectangle(1290,50,1465,200);
	settextstyle(6,0,3);
	outtextxy(1303,105,"Increasing");
	//Decrease button 
	rectangle(1290,230,1465,380);
	settextstyle(6,0,3);
	outtextxy(1300,287,"Decreasing");
	//Reset button
	rectangle(1290,410,1465,560);
	settextstyle(6,0,3);
	outtextxy(1338,467,"Reset");
	//Exit button 
	rectangle(1290,590,1465,740);
	settextstyle(6,0,3);
	outtextxy(1350,650,"Exit");

}
void GUI_keyboard(){
	setcolor(15);
	//main border
	setlinestyle(0,1,3);//setlinestyle(int linestyle, unsigned pattern, int thickness)
	rectangle(250,50,1250,740);
	//
	settextstyle(6,0,4);
	outtextxy(200,750,"|GVHD: Doan Vu Thinh |");
	outtextxy(740,750,"|Ten sv: Tran Hang Tong Dat|");
	
	//input number button
	rectangle(35,50,210,200);	
	settextstyle(6,0,4);
	outtextxy(110,105,"N");
	//keyboard button 
	setcolor(4);
	rectangle(35,230,210,380);
	settextstyle(6,0,3);
	outtextxy(52,287,"Keyboard");
	//Random button
	setcolor(15);
	rectangle(35,410,210,560);
	settextstyle(6,0,3);
	outtextxy(64,465,"Random");
	//Load file button 
	rectangle(35,590,210,740);
	settextstyle(6,0,3);
	outtextxy(54,650,"Load File");
	//increase button
	rectangle(1290,50,1465,200);
	settextstyle(6,0,3);
	outtextxy(1303,105,"Increasing");
	//Decrease button 
	rectangle(1290,230,1465,380);
	settextstyle(6,0,3);
	outtextxy(1300,287,"Decreasing");
	//Reset button
	rectangle(1290,410,1465,560);
	settextstyle(6,0,3);
	outtextxy(1338,467,"Reset");
	//Exit button 
	rectangle(1290,590,1465,740);
	settextstyle(6,0,3);
	outtextxy(1350,650,"Exit");

}
void GUI_loadfile(){
	setcolor(15);
	//main border
	setlinestyle(0,1,3);//setlinestyle(int linestyle, unsigned pattern, int thickness)
	rectangle(250,50,1250,740);
	//
	settextstyle(6,0,4);
	outtextxy(200,750,"|GVHD: Doan Vu Thinh |");
	outtextxy(740,750,"|Ten sv: Tran Hang Tong Dat|");
	
	//input number button
	rectangle(35,50,210,200);	
	settextstyle(6,0,4);
	outtextxy(110,105,"N");
	//keyboard button 
	rectangle(35,230,210,380);
	settextstyle(6,0,3);
	outtextxy(52,287,"Keyboard");
	//Random button
	rectangle(35,410,210,560);
	settextstyle(6,0,3);
	outtextxy(64,465,"Random");
	//Load file button 
	setcolor(4);
	rectangle(35,590,210,740);
	settextstyle(6,0,3);
	outtextxy(54,650,"Load File");
	//increase button
	setcolor(15);
	rectangle(1290,50,1465,200);
	settextstyle(6,0,3);
	outtextxy(1303,105,"Increasing");
	//Decrease button 
	rectangle(1290,230,1465,380);
	settextstyle(6,0,3);
	outtextxy(1300,287,"Decreasing");
	//Reset button
	rectangle(1290,410,1465,560);
	settextstyle(6,0,3);
	outtextxy(1338,467,"Reset");
	//Exit button 
	rectangle(1290,590,1465,740);
	settextstyle(6,0,3);
	outtextxy(1350,650,"Exit");

}
void GUI_random(){
	setcolor(15);
	//main border
	setlinestyle(0,1,3);//setlinestyle(int linestyle, unsigned pattern, int thickness)
	rectangle(250,50,1250,740);
	//
	settextstyle(6,0,4);
	outtextxy(200,750,"|GVHD: Doan Vu Thinh |");
	outtextxy(740,750,"|Ten sv: Tran Hang Tong Dat|");
	
	//input number button
	rectangle(35,50,210,200);	
	settextstyle(6,0,4);
	outtextxy(110,105,"N");
	//keyboard button 
	rectangle(35,230,210,380);
	settextstyle(6,0,3);
	outtextxy(52,287,"Keyboard");
	//Random button
	setcolor(4);
	rectangle(35,410,210,560);
	settextstyle(6,0,3);
	outtextxy(64,465,"Random");
	//Load file button 
	setcolor(15);
	rectangle(35,590,210,740);
	settextstyle(6,0,3);
	outtextxy(54,650,"Load File");
	//increase button
	rectangle(1290,50,1465,200);
	settextstyle(6,0,3);
	outtextxy(1303,105,"Increasing");
	//Decrease button 
	rectangle(1290,230,1465,380);
	settextstyle(6,0,3);
	outtextxy(1300,287,"Decreasing");
	//Reset button
	rectangle(1290,410,1465,560);
	settextstyle(6,0,3);
	outtextxy(1338,467,"Reset");
	//Exit button 
	rectangle(1290,590,1465,740);
	settextstyle(6,0,3);
	outtextxy(1350,650,"Exit");

}

void GUI_increase(){
	setcolor(15);
	//main border
	setlinestyle(0,1,3);//setlinestyle(int linestyle, unsigned pattern, int thickness)
	rectangle(250,50,1250,740);
	//input number button
	rectangle(35,50,210,200);	
	settextstyle(6,0,4);
	outtextxy(110,105,"N");
	//key board button 
	rectangle(35,230,210,380);
	settextstyle(6,0,3);
	outtextxy(52,287,"Keyboard");
	//Random button
	rectangle(35,410,210,560);
	settextstyle(6,0,3);
	outtextxy(64,465,"Random");
	//Load file button 
	rectangle(35,590,210,740);
	settextstyle(6,0,3);
	outtextxy(54,650,"Load File");
	//increase button
	setcolor(4);
	rectangle(1290,50,1465,200);
	settextstyle(6,0,3);
	outtextxy(1303,105,"Increasing");
	//Decrease button 
	setcolor(15);
	rectangle(1290,230,1465,380);
	settextstyle(6,0,3);
	outtextxy(1300,287,"Decreasing");
	//Reset button
	rectangle(1290,410,1465,560);
	settextstyle(6,0,3);
	outtextxy(1338,467,"Reset");
	//Exit button 
	rectangle(1290,590,1465,740);
	settextstyle(6,0,3);
	outtextxy(1350,650,"Exit");

}

void GUI_decrease(){
	setcolor(15);
	//main border
	setlinestyle(0,1,3);//setlinestyle(int linestyle, unsigned pattern, int thickness)
	rectangle(250,50,1250,740);
	//input number button
	rectangle(35,50,210,200);	
	settextstyle(6,0,4);
	outtextxy(110,105,"N");
	//key board button 
	rectangle(35,230,210,380);
	settextstyle(6,0,3);
	outtextxy(52,287,"Keyboard");
	//Random button
	rectangle(35,410,210,560);
	settextstyle(6,0,3);
	outtextxy(64,465,"Random");
	//Load file button 
	rectangle(35,590,210,740);
	settextstyle(6,0,3);
	outtextxy(54,650,"Load File");
	//increase button
	rectangle(1290,50,1465,200);
	settextstyle(6,0,3);
	outtextxy(1303,105,"Increasing");
	//Decrease button 
	setcolor(4);
	rectangle(1290,230,1465,380);
	settextstyle(6,0,3);
	outtextxy(1300,287,"Decreasing");
	//Reset button
	setcolor(15);
	rectangle(1290,410,1465,560);
	settextstyle(6,0,3);
	outtextxy(1338,467,"Reset");
	//Exit button 
	rectangle(1290,590,1465,740);
	settextstyle(6,0,3);
	outtextxy(1350,650,"Exit");

}

//Su dung chuot de chon cac ham: N = , keyboard, loadfile, random, decreasing, increasing, reset, exit
void mouse(){
	int x_mouse;
	int y_mouse;
	while(enable_click){
		//get even mouse click
	
		if(ismouseclick(WM_LBUTTONDOWN)){
			//get position of mouse
			getmouseclick(WM_LBUTTONDOWN,x_mouse, y_mouse);
			//printf x,y mouse to console
			//printf("(%d,%d)",x_mouse,y_mouse);
			//checking for buttons
			
			//N button
			if(x_mouse > 35 && x_mouse < 210 && y_mouse >50 && y_mouse < 200){
				input();	
				drawpoints(td,sodinh);		
			}
			
			//keyboard button
			if(x_mouse > 35 && x_mouse < 210 && y_mouse >230 && y_mouse < 380){
				printf("Input form keyboard ...");
				keyboard();
				drawpoints(td,sodinh);					
			}
			//Random button
			if(x_mouse > 35 && x_mouse < 210 && y_mouse >410 && y_mouse < 560){
				printf("Random number...\n");
				Random();
				drawpoints(td,sodinh);				
			}	
			
			//load file button
			if(x_mouse > 35 && x_mouse < 210 && y_mouse >590 && y_mouse <740){			
				readfile();	
				drawpoints(td,sodinh);	
			}
								
		
			//Increase button
			if(x_mouse > 1290 && x_mouse < 1465 && y_mouse > 50 && y_mouse < 200){
				printf("Increasing...");
				increase();			
			}	
			
			//Decrease button
			if(x_mouse > 1290 && x_mouse < 1465 && y_mouse > 230 && y_mouse < 380){
				printf("Decreasing...");
				decrease();			
			}	
			
			//Reset button
			if(x_mouse > 1290 && x_mouse < 1465 && y_mouse > 410 && y_mouse < 560){
				reset();			
			}	
			
			//Exit button
			if(x_mouse > 1290 && x_mouse < 1465 && y_mouse > 590 && y_mouse < 740){
				exit();			
			}			
		}
		//check right mouse click to exit loop
		if(ismouseclick(WM_RBUTTONDOWN)){
			getmouseclick(WM_RBUTTONDOWN,x_mouse, y_mouse);
			printf("\nExiting...");
			
		break;
	}
	delay(100);//wait for next cycle mouse click
	}		
}
void input(){
	cleardevice();
	GUI_input();
	
	while (1) {
        printf("Nhap so luong phan tu:\t");
        scanf("%d", &sodinh);
        if (sodinh >= 2 && sodinh < 10) {
            break; // Thoát kh?i vòng l?p n?u sodinh n?m trong kho?ng cho phép
        }
        printf("Vui long nhap lai so luong phan tu trong khoang tu 2 den 9!\n");
    }
    if(sodinh<10){
    	for(int i=0;i<sodinh;i++){
		td[i].x = 350 +(i*100);
		td[i].y = 380;
		//nhap gia tri cho cac diem
		printf("\ntd[%d].value = ",i);
		scanf("%d",&td[i].value);
		}
	}
		//print points
	printpoints(td,sodinh);
	printf("\Finished!");
}
void keyboard(){
	cleardevice();
	GUI_keyboard();
	//read data from keyboard
	fp=fopen(INPUT,"r");
	if(fp==NULL){
		printf("Find not found");
		return;
	}
	//else
	//doc dong dau tien cua tap tin
	fscanf(fp,"%d",&sodinh);
	//doc lan luot tung phan tu: moi phan tu cos 3 tham so: toado_x. toado_y, giatri
	
	for(int i=0;i<sodinh;i++){
		fscanf(fp,"%d %d %d",&td[i].x, &td[i].y, &td[i].value);
		//Nhap gia trio cho cac diem
		printf("\ntd[%d].value = ",i);
		scanf("%d",&td[i].value);
	}
	
	//print points
	printpoints(td,sodinh);
	printf("\Finished!");
	fclose(fp);
}
void drawpoint(struct toado point, int color){
    int newRadius = 40; // // thay doi ban kinh a

    setcolor(color);
    circle(point.x, point.y, newRadius);
    settextstyle(1, 0, 4);
    outtextxy(point.x - 11, point.y - 15, itoa(point.value, buffer, 10));
}

void drawpoints(struct toado points[MAX], int size){
	for(int i=0; i<size; i++){
		drawpoint(points[i],15);//WHITE
		delay(100);
	}
}

void Random(){
	cleardevice();
	GUI_random();
    // Set seed ngau nhien dua tren thoi gian hien tai
    srand(time(0));
    // tao ngau nhien so luong phan tu tu 2 den 10
    sodinh = rand() % 9 + 2;
    printf("So luong phan tu la: %d\n",sodinh);
    // kiem tra gia tri da su dung hay chua
    int usedValues[10] = {0};	
    for(int i=0;i<sodinh;i++){
    if(sodinh<11){
		td[i].x = 300 +(i*100);
		td[i].y = 380;
		}
		do {
            td[i].value = rand() % 10;
        } while (usedValues[td[i].value]);

        //danh dau gia tri da su dung
        usedValues[td[i].value] = 1;
	}
		//print points
	printpoints(td,sodinh);
	printf("\Finished!");

}
void increase() {
    // when click star button - mouse click = false
    enable_click = 0;
    // Load GUI_increase
    GUI_increase();
    // Sorting using Selection Sort
    for (int i = 0; i < sodinh - 1; i++) {
        int min_index = i;

        // draw points with WHITE color
        for (int j = 0; j < sodinh; j++) {
            drawpoint(td[j], 15); // WHITE
        }
        // draw point i with RED color
        drawpoint(td[i], 4); // RED
        // find the index of the minimum element
        for (int k = i + 1; k < sodinh; k++) {
            // draw point k with RED color
            drawpoint(td[k], 4); // RED

            // mark color for comparison
            delay(2000);
            // find the minimum element
            if (td[k].value < td[min_index].value) {
                drawpoint(td[min_index], 15); // WHITE
                min_index = k;
                drawpoint(td[min_index], 2); // GREEN
                delay(2000);
            } else {
                drawpoint(td[k], 15); // WHITE
            }
        }

        // swap the found minimum element with the first element
        if (min_index != i) {
            // mark color for swapping
            drawpoint(td[i], 2); // GREEN
            drawpoint(td[min_index], 2); // GREEN
            delay(2000);

            // swap
            int temp = td[i].value;
            td[i].value = td[min_index].value;
            td[min_index].value = temp;
        }
    }

    // draw all points with ORANGE color after sorting
    for (int i = 0; i < sodinh; i++) {
        drawpoint(td[i], 14); // ORANGE
    }
    enable_click = 1;// sau khi chay het thi tra lai de bam duoc nut exit
}
void decrease() {
    // Disable mouse clicks
    enable_click = 0;
    // Load GUI_decrease (assuming you have a GUI function for "decrease")
    GUI_decrease();
    // Sorting using Selection Sort in descending order
    for (int i = 0; i < sodinh - 1; i++) {
        int max_index = i;

        // Draw points with WHITE color
        for (int j = 0; j < sodinh; j++) {
            drawpoint(td[j], 15); // WHITE
        }

        // Draw point i with RED color
        drawpoint(td[i], 4); // RED

        // Find the index of the maximum element (change the comparison condition)
        for (int k = i + 1; k < sodinh; k++) {
            // Draw point k with RED color
            drawpoint(td[k], 4); // RED

            // Mark color for comparison
            delay(2000);

            // Find the maximum element (change the comparison condition)
            if (td[k].value > td[max_index].value) {
                drawpoint(td[max_index], 15); // WHITE
                max_index = k;
                drawpoint(td[max_index], 2); // GREEN
            } else {
                drawpoint(td[k], 15); // WHITE
            }
        }

        // Swap the found maximum element with the first element
        if (max_index != i) {
            // Mark color for swapping
            drawpoint(td[i], 2); // GREEN
            drawpoint(td[max_index], 2); // GREEN
            delay(200);

            // Swap
            int temp = td[i].value;
            td[i].value = td[max_index].value;
            td[max_index].value = temp;
        }
    }

    // Draw all points with ORANGE color after sorting
    for (int i = 0; i < sodinh; i++) {
        drawpoint(td[i], 14); // ORANGE
    }

    // Enable mouse clicks after sorting
    enable_click = 1;
}

void reset() {

    // Clear the screen
    cleardevice();

    // Draw the initial GUI
    GUI_init();

    // Set the enable_click back to true
    enable_click = 1;
}

void exit() {
	closegraph();
    exit(0);
}
int main(){
	
	//ve giao dien
	initwindow(1800,800);
	GUI_init();
	//dung chuot
	mouse();
	//dung man hinh
	getch();
	return 0;
	
	
	
}
