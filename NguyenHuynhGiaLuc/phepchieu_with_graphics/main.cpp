#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include<math.h>
#define maxdinh 10
#define MAX 100
#define INPUT "points.inp"
#define MTK "mtk.inp"


struct toado {
    int x;
    int y;
    int z;
    char value;
};

int sodinh;
FILE *fp;
struct toado td[MAX];
int enable_click = 1;
int mtk[maxdinh][maxdinh];//ma tran ke cac dinh cua da giac



void readFile();
void drawpoint(struct toado point, int color);
void draw_point(struct toado points[MAX], int size);
void GUI_init();
void GUI_demo();
void mouse();
void keyboard();
void printGraphInfo();
void ve_da_giac(struct toado points[MAX], int size);
void ve_chieu_top(struct toado points[MAX], int size);
void ve_chieu_canh_ben(struct toado points[MAX], int size) ;




void readFile() {
    fp = fopen(INPUT, "r");
    if (fp == NULL) {
        printf("File not found");
        return;
    }
    fscanf(fp, "%d", &sodinh);
    for (int i = 0; i < sodinh; i++) {
        fscanf(fp, "%d %d %d %c", &td[i].x, &td[i].y, &td[i].z, &td[i].value);
    }
    
    
    
    //DOC NOI DUNG TAP TIN MA TRAN KE
	fp=fopen(MTK,"r");//doc file toa do dinh
	if(fp==NULL){
		printf("File not found");
	}
	else{
		fscanf(fp,"%d",&sodinh);//so dinh
		for(int i=0; i<sodinh; i++){//cac dinh
			for(int j=0; j<sodinh;j++){//cac dinh
				fscanf(fp,"%d",&mtk[i][j]);
			}
		}
	}
	//in ra toa do cac dinh da giac
	
    fclose(fp);
    printGraphInfo();
    
}



void drawpoint(struct toado point, int color) {
    setcolor(color);
    char charValue[2] = {point.value, '\0'};
    outtextxy(point.x, point.y, charValue);
}

void draw_point(struct toado points[MAX], int size) {
    cleardevice();
    for (int i = 0; i < size; i++) {
        drawpoint(points[i], 15);
    }
}

void ve_chieu_top(struct toado points[MAX], int size) { // chieu dung
	
    for (int i = 0; i < size - 1 ; i++) {
        for (int j = i + 1; j < size; j++) {
            if (mtk[i][j] == 1) {
                line(points[i].x, points[i].y, points[j].x, points[j].y);
            }
        }
    }
    delay(100);
}

void ve_chieu_mat_day(struct toado points[MAX], int size) { // chieu bang
    cleardevice();
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (mtk[i][j] == 1) {
                line(points[i].x, points[i].z, points[j].x, points[j].z);
            }
        }
    }
    delay(100);
}


void ve_chieu_canh_ben(struct toado points[MAX], int size) { // chieu canh ben
    cleardevice();
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (mtk[i][j] == 1) {
                line(points[i].y, points[i].z, points[j].y, points[j].z);
            }
        }
    }
    delay(300);
}



void printGraphInfo() {
    printf("So dinh: %d\n", sodinh);

    printf("Toa do cac dinh:\n");
    for (int i = 0; i < sodinh; i++) {
        printf("%c: (%d, %d, %d)\n", td[i].value, td[i].x, td[i].y, td[i].z);
    }

    printf("Ma tran ke:\n");
    for (int i = 0; i < sodinh; i++) {
        for (int j = 0; j < sodinh; j++) {
            printf("%d ", mtk[i][j]);
        }
        printf("\n");
    }
}

void GUI_init() {
    setcolor(WHITE);
    setlinestyle(0, 1, 3);
    rectangle(10, 10, 670, 570);
    
    // Load file button
    rectangle(680, 10, 780, 50);
    settextstyle(2, 0, 7);
    outtextxy(690, 20, "Load file");

    // Keyboard button
    rectangle(680, 70, 780, 110);
    settextstyle(2, 0, 7);
    outtextxy(690, 80, "Keyboard");

    // Run button
    rectangle(680, 130, 780, 170);
    settextstyle(2, 0, 7);
    outtextxy(690, 140, "Run");

    // Top button
    rectangle(680, 190, 780, 230);
    settextstyle(2, 0, 7);
    outtextxy(690, 200, "Top");

    // Left button
    rectangle(680, 250, 780, 290);
    settextstyle(2, 0, 7);
    outtextxy(690, 260, "Left");

    // Front button
    rectangle(680, 310, 780, 350);
    settextstyle(2, 0, 7);
    outtextxy(690, 320, "Front");
    
    // Reset button
    rectangle(680, 370, 780, 410);
    settextstyle(2, 0, 7);
    outtextxy(690, 380, "Reset");
    
    //exit
	rectangle(680, 430, 780, 470);
	settextstyle(2, 0, 7);
	outtextxy(690, 440, "Exit");
    
   	settextstyle(2, 0, 7);
   	outtextxy(690, 480, "GVHD: ThS.DOAN VU THINH");
   	outtextxy(690, 510, "TenSV: NGUYEN HUYNH GIA LUC");
   	outtextxy(690, 540, "MSSV: 63132245");
   	outtextxy(690, 570, "LOP: 63.CNTT-4");
}

void GUI_demo() {
    setcolor(WHITE);
    setlinestyle(0, 1, 3);
    rectangle(10, 10, 670, 570);
    setcolor(7);

    // Load file button
    rectangle(680, 10, 780, 50);
    settextstyle(2, 0, 7);
    outtextxy(690, 20, "Load file");

    // Keyboard button
    rectangle(680, 70, 780, 110);
    settextstyle(2, 0, 7);
    outtextxy(690, 80, "Keyboard");

	setcolor(4);
	
    // Run button
    rectangle(680, 130, 780, 170);
    settextstyle(2, 0, 7);
    outtextxy(690, 140, "Run");
	
	setcolor(7);
	
    // Top button
    rectangle(680, 190, 780, 230);
    settextstyle(2, 0, 7);
    outtextxy(690, 200, "Top");

	// Left button
    rectangle(680, 250, 780, 290);
    settextstyle(2, 0, 7);
    outtextxy(690, 260, "Left");

    // Front button
    rectangle(680, 310, 780, 350);
    settextstyle(2, 0, 7);
    outtextxy(690, 320, "Front");
    
    //Reset button
    rectangle(680, 370, 780, 410);
    settextstyle(2, 0, 7);
    outtextxy(690, 380, "Reset");
    
    //exit
	rectangle(680, 430, 780, 470);
	settextstyle(2, 0, 7);
	outtextxy(690, 440, "Exit");
    
    settextstyle(2, 0, 7);
	outtextxy(690, 480, "GVHD: ThS.DOAN VU THINH");
	outtextxy(690, 510, "TenSV: NGUYEN HUYNH GIA LUC");
	outtextxy(690, 540, "MSSV: 63132245");
	outtextxy(690, 570, "LOP: 63.CNTT-4");
    
}

void mouse() {
    int x_mouse, y_mouse;
    while (enable_click) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x_mouse, y_mouse);
            if (x_mouse > 680 && x_mouse < 780 && y_mouse > 10 && y_mouse < 50) {
                printf("Read from file ...");
                readFile();
                draw_point(td, sodinh);
                GUI_demo();
            }
            if (x_mouse > 680 && x_mouse < 780 && y_mouse > 70 && y_mouse < 110) {
                printf("INPUT ...");
                keyboard();
                draw_point(td, sodinh);
                GUI_demo();
            }
            if (x_mouse > 680 && x_mouse < 780 && y_mouse > 130 && y_mouse < 170) {
                printf("Running ...");
                ////////////////////
            }
            if (x_mouse > 680 && x_mouse < 780 && y_mouse > 190 && y_mouse < 230) {
                printf("Top...");
                draw_point(td,sodinh); 
                ve_chieu_top(td,sodinh);
                //ve_truc_giao_3D(td, sodinh);
                GUI_demo();
            }
            if (x_mouse > 680 && x_mouse < 780 && y_mouse > 250 && y_mouse < 290) {
                printf("Left....");
                draw_point(td, sodinh);
				ve_chieu_canh_ben(td, sodinh);
				GUI_demo();
            }
            if (x_mouse > 680 && x_mouse < 780 && y_mouse > 310 && y_mouse < 350) {
                printf("Front...");
                draw_point(td, sodinh);
                ve_chieu_mat_day(td, sodinh);
                GUI_demo();
            }
            if (x_mouse > 680 && x_mouse < 780 && y_mouse > 370 && y_mouse < 410) {
               	printf("Reset...");
                cleardevice();
				GUI_init();
            }
			if (x_mouse > 680 && x_mouse < 780 && y_mouse > 430 && y_mouse < 470) {
			    printf("Exiting...");
			    exit(0);
			}
            
        }

        if (ismouseclick(WM_RBUTTONDOWN)) {
            getmouseclick(WM_RBUTTONDOWN, x_mouse, y_mouse);
            printf("\nExiting");
            break;
        }
        delay(100);
    }
}




void keyboard() {
    fp = fopen(INPUT, "r");
    if (fp == NULL) {
        printf("File not found");
        return;
    }
    fscanf(fp, "%d", &sodinh);
    printf("Da giac co : %d dinh\n", sodinh);
    for (int i = 0; i < sodinh; i++) {
        fscanf(fp, "%d %d %d %c", &td[i].x, &td[i].y, &td[i].z, &td[i].value);
        printf("\nNhap dinh thu %d = ", i);
        scanf(" %c", &td[i].value);
        td[i].value = toupper(td[i].value);
    }

  	printGraphInfo();
    printf("\nFinished");
    fclose(fp);
}

int main() {
    readFile();
    initwindow(1000, 610);
    GUI_init();
    mouse();
    getch();
    return 0;
}
