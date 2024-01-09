///Khai bao thu vien
//Printf scanf
#include <stdio.h>
//line rectangle circle...
#include <graphics.h>
#include <time.h>
#include <cmath>
#define MAX 100
#define INPUT "points.inp"
#define RADIUS 30				// Ban kinh hinh tron
#define CIRCLE_GAP 10      		// Khoang cach giua cac hinh vong tron
#define FONT_SIZE 3 			// Kich thuoc font
#define ARRAY_GAP 30 			// Khoang cach giua mang con ben trai va ben phai


/////////////////////////////////////////////////////////
///Khai bao bien toan cuc
int n;
int source[MAX];
int a[MAX];
//file pointer
FILE *fp;
int enable_mouse = 1;
int toado_x, toado_y;
char buffer[5];
int count_click = 0;

// Khai bao bien de theo doi trang thai cua cac nut
int loadfilestatus = 0;
int keyboardstatus = 0;
int inputstatus = 0;
int randstatus = 0;
int randarraystatus = 0;
int resetstatus = 0;
int exitstatus = 0;

int increasestatus = 0;
int decreasestatus = 0;

/////////////////////////////////////////////////////////
//Giao dien chuong trinh
void giaodien()
{
	//ve khung
	setlinestyle(3,1,3);
	rectangle(10,10,1360,900);
	//Thiet ke Info Tac gia
	setlinestyle(1,0,2);
	settextstyle(0,0,3);
	outtextxy(1390,660,"AUTHOR INFO");
	line(1420, 690, 1620, 690);
	settextstyle(8,0,1);
	setcolor(LIGHTGREEN);
	outtextxy(1365,700,"Name: Nguyen Khac Duy Hung");
	outtextxy(1365,720,"MSSV: 63132095");
	outtextxy(1365,740,"M: hung.nkd.63cntt@ntu.edu.vn");	
	outtextxy(1365,760,"GVHD: ThS. Doan Vu Thinh");	
	//Thiet ke nut Load file
	setcolor(loadfilestatus ? YELLOW : WHITE);
	setlinestyle(1, 0, 2);
	rectangle(1370, 10, 1680, 80);
	settextstyle(0, 0, 3);
	outtextxy(1410, 30, "LOAD FILE");
	//Thiet ke nut Keyboard
	setcolor(keyboardstatus ? YELLOW : WHITE);
	setlinestyle(1,0,2);
	rectangle(1370,100,1680,170);
	settextstyle(0,0,3);
	outtextxy(1425,110,"KEYBOARD");
	settextstyle(9,0,2);
	outtextxy(1440,135,"(10 elements)");
	//Thiet ke nut Input NUM
	setcolor(inputstatus ? YELLOW : WHITE);
	setlinestyle(1,0,2);
	rectangle(1370,200,1680,270);
	settextstyle(0,0,3);
	outtextxy(1390,210,"INPUT ARRAY");
	settextstyle(9,0,2);
	outtextxy(1430,235,"(2-10 elements)");
	//Thiet ke nut Random
	setcolor(randstatus ? YELLOW : WHITE);
	setlinestyle(1,0,2);
	rectangle(1370,300,1680,370);
	settextstyle(0,0,3);
	outtextxy(1450,310,"RANDOM");
	settextstyle(9,0,2);
	outtextxy(1440,335,"(10 elements)");
	//Thiet ke nut Random Array
	setcolor(randarraystatus ? YELLOW : WHITE);
	setlinestyle(1,0,2);
	rectangle(1370,400,1680,470);
	settextstyle(0,0,3);
	outtextxy(1380,410,"RANDOM ARRAY");
	settextstyle(9,0,2);
	outtextxy(1430,435,"(2-10 elements)");
	//Thiet ke nut RESET
	setcolor(resetstatus ? YELLOW : WHITE);
	setlinestyle(1,0,2);
	rectangle(1370,500,1680,570);
	settextstyle(0,0,3);
	outtextxy(1465,520,"RESET");
	//Thiet ke nut Exit
	setcolor(exitstatus ? YELLOW : WHITE);
	setlinestyle(1,0,2);
	rectangle(1370,900,1680,970);
	settextstyle(0,0,3);
	outtextxy(1480,920,"EXIT");	
	//Thiet ke nut sap xep tang dan
	setcolor(increasestatus ? LIGHTRED : WHITE);
	setlinestyle(1,0,2);
	rectangle(150,910,650,970);
	settextstyle(0,0,3);
	outtextxy(200,925,"SAP XEP TANG DAN");
	//Thiet ke nut sap xep giam dan
	setcolor(decreasestatus ? LIGHTRED : WHITE);
	setlinestyle(1,0,2);
	rectangle(750,910,1250,970);
	settextstyle(0,0,3);
	outtextxy(800,925,"SAP XEP GIAM DAN");			
}


/////////////////////////////////////////////////////////

//In gia tri mang
void inmang(int a[MAX], int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("Gia tri diem %d = %d\n", i + 1, a[i]);
	}
}

/////////////////////////////////////////////////////////
void readfile(int a[MAX], int &n, int &flag) 
{
    fp = fopen(INPUT, "r");
    if(fp == NULL) 
	{
        printf("Khong tim thay FILE!");
        flag = 1;
        return;
    }
    fscanf(fp, "%d", &n);
    printf("\nSo luong cac diem: %d\n", n);
    for(int i = 0; i < n; i++) 
	{
        fscanf(fp, "%d", &a[i]);

        // Kiem tra xem giá tri vua doc có nam trong khoang tu 0 den 9 không
        if (a[i] < 0 || a[i] > 9) 
		{
            printf("Gia tri du lieu trong FILE khong hop le! Cac gia tri phai nam trong khoang tu 0 den 9.\n");
            printf("Du lieu loi tai vi tri thu %d. Vui long kiem tra va sua FILE.\n", i + 1);
			flag = 2;
            break;
        }
    }
    printf("\nDU LIEU FILE DA DOC LA: \n");
    inmang(a, n);
    fclose(fp);
}

/////////////////////////////////////////////////////////
//Ham nut Keyboard - Mac dinh nut nay se co 10 phan tu
void keyboard(int a[MAX], int &size) {
    size = 10;
    printf("\n---GIA TRI TUNG PHAN TU (Nhap tu 0 den 9)---\n");
    for (int i = 0; i < size; i++) {
        do {
            printf("Gia tri %d: ", i + 1);
            scanf("%d", &a[i]);

            // Kiem tra xem gia tri nhap co nam trong khoang tu 0 den 9 khong
            if (a[i] < 0 || a[i] > 9) 
			{
                printf("Gia tri nhap khong hop le (Tu 0 den 9). Vui long nhap lai.\n");
            }
        } while (a[i] < 0 || a[i] > 9);
    }

    printf("\n---HOAN TAT VIEC NHAP DU LIEU---\n");
}

/////////////////////////////////////////////////////////
//Ham nut Nhap so luong phan tu
void input_array(int a[MAX], int &size)
{
    printf("\n---SO LUONG PHAN TU---\n");	
    do 
	{
        printf("Nhap so luong phan tu (tu 2 den 10): ");
        scanf("%d", &n);
        if (n < 2 || n > 10)
		{
            printf("So luong phan tu khong hop le. Vui long nhap lai.\n");
        }
    } while (n < 2 || n > 10);
    printf("\n---GIA TRI TUNG PHAN TU (Nhap tu 0 den 9)---\n");
    for (int i = 0; i < size; i++) 
	{
        do {
            printf("Phan tu thu %d: ", i + 1);
            scanf("%d", &a[i]);
            // Kiem tra xem gia tri nhap co hop le hay khong (tuc la tu 0 den 9)
            if (a[i] < 0 || a[i] > 9) 
			{
                printf("Gia tri phan tu khong hop le (tu 0 den 9). Vui long nhap lai.\n");
            }
        } while (a[i] < 0 || a[i] > 9);
    }
    printf("\n---HOAN TAT VIEC NHAP DU LIEU---\n"); 
}

/////////////////////////////////////////////////////////
//Ham nut Tao ngau nhien so

bool check_dup(int a[MAX], int n, int x)
{
	for(int i = 0; i < n; i++)
	{
		if(a[i] == x)
		{
			return true;
		}
	}
	return false;
}

void random_num(int a[MAX], int &size)
{
    srand(time(NULL));
    int i = 0;
    while(i < size) 
	{
        int rand_num = rand() % 10;
        if(!check_dup(a, i, rand_num)) 
		{
            a[i++] = rand_num;
        }
    }
    size = i;
    inmang(a, size);
}

int getRand(int a, int b) 
{
    return rand() % (b - a + 1) + a;
}

void random_array(int a[MAX], int *size)
{
    srand(time(NULL));
    
	//Random so luong phan tu tu 2 den 10
	*size = getRand(2, 10);			
    
	for(int i = 0; i < *size; i++)
	{
		int rand_num;
		do
		{
			rand_num = getRand(0, 9);
		}while(check_dup(a, i, rand_num));
		
		a[i] = rand_num;
	}
	
    //In phan tu
    printf("\n-----So luong phan tu duoc tao ngau nhien la: %d-----\n", n);
    printf("\n---Cac gia tri cua cac phan tu duoc tao ngau nhien---\n");    
	inmang(a, n);
}

/////////////////////////////////////////////////////////////
//Ham ve mui ten
void arrow(int x1, int y1, int x2, int y2) 
{
	//Thiet lap kieu cho duong thang mui ten
	setcolor(LIGHTCYAN);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
		
    //ve duong thang
    line(x1, y1, x2, y2);

    // Kich thuoc mui ten
    int arrowSize = 10;

    // Tinh goc cua duong thang
    double angle = atan2(y2 - y1, x2 - x1);

    // Tinh toa do cua cac diem de ve mui ten
    int x3 = x2 - arrowSize * cos(angle - M_PI / 6);
    int y3 = y2 - arrowSize * sin(angle - M_PI / 6);
    int x4 = x2 - arrowSize * cos(angle + M_PI / 6);
    int y4 = y2 - arrowSize * sin(angle + M_PI / 6);

    // Ve mui ten
    line(x2, y2, x3, y3);
    line(x2, y2, x4, y4);
}

//Ve ra danh sach mang
void veds(int a[MAX], int n){

	//Neu day so gom 2 so
	if(n == 2)
	{
		toado_x = 670;
		toado_y = 300;	
	}
	//Neu day so gom 3 so
	else if(n == 3)
	{
		toado_x = 630;
		toado_y = 200;
	}
	//Neu day so gom 4 so
	else if(n == 4)
	{
		toado_x = 600;
		toado_y = 200;	
	}
	//Neu day so gom 5 so
	else if(n == 5)
	{
		toado_x = 560;
		toado_y = 100;	
	}
	//Neu day so gom 6 so
	else if(n == 6)
	{
		toado_x = 525;
		toado_y = 100;	
	}
	//Neu day so gom 7 so
	else if(n == 7)
	{
		toado_x = 480;
		toado_y = 100;	
	}
	//Neu day so gom 8 so
	else if(n == 8)
	{
		toado_x = 455;
		toado_y = 100;	
	}
	//Neu day so gom 9 so
	else if(n == 9)
	{
		toado_x = 420;
		toado_y = 100;	
	}
	//Neu day so gom 10 so
	else if(n == 10)
	{
		toado_x = 385;
		toado_y = 100;	
	}

	settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
	
	for(int i = 0; i < n; i++)
	{
	    setcolor(WHITE);	
        int x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
        int y = toado_y;
        circle(x, y, RADIUS);
        sprintf(buffer, "%d", a[i]);
        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
	}
}

//Chia nho mang con cap 1
void veds_chia(int a[MAX], int left, int mid, int right)
{
	//Neu day so co 2 so
	if(n == 2)
	{
		toado_x = 530;	
		toado_y = 400;	
	}
	//Neu day so co 3 so
	else if(n == 3)
	{
		toado_x = 440;	
		toado_y = 300;	
	}
	//Neu day so gom 4 so
	else if(n == 4)
	{
		toado_x = 440;
		toado_y = 350;	
	}
	//Neu day so gom 5 so
	else if(n == 5)
	{
		toado_x = 420;
		toado_y = 250;	
	}
	//Neu day so gom 6 so
	else if(n == 6)
	{
		toado_x = 385;
		toado_y = 250;	
	}
	//Neu day so gom 7 so
	else if(n == 7)
	{
		toado_x = 340;
		toado_y = 250;	
	}
	//Neu day so gom 8 so
	else if(n == 8)
	{
		toado_x = 320;
		toado_y = 250;	
	}
	//Neu day so gom 9 so
	else if(n == 9)
	{
		toado_x = 280;
		toado_y = 250;	
	}
	//Neu day so gom 10 so
	else if(n == 10)
	{
		toado_x = 245;
		toado_y = 250;	
	}
    //Mang con ben trai
    for (int i = left; i <= mid; i++) 
	{
        setcolor(WHITE);
        int x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
        int y = toado_y;
        circle(x, y, RADIUS);
        sprintf(buffer, "%d", a[i]);
        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
    }
    //Khoang cach (BIG) cua 2 mang con da duoc chia nho
    if(n == 3)		toado_x += (mid + 2) * (2 * RADIUS + CIRCLE_GAP) + ARRAY_GAP + 210;			
    else if(n == 4)	toado_x += (mid + 2) * (2 * RADIUS + CIRCLE_GAP) + ARRAY_GAP + 220;			
    else if(n == 5)	toado_x += (mid + 2) * (2 * RADIUS + CIRCLE_GAP) + ARRAY_GAP + 110;			
    else			toado_x += (mid + 2) * (2 * RADIUS + CIRCLE_GAP) + ARRAY_GAP + 180;			
    //Mang con ben phai
    for (int i = mid + 1; i <= right; i++) 
	{
        setcolor(WHITE);
        int x = toado_x + (i - mid - 1) * (2 * RADIUS + CIRCLE_GAP);
        int y = toado_y;
        circle(x, y, RADIUS);
        sprintf(buffer, "%d", a[i]);
        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
    }
    //Goi ham ve mui ten
    if(n == 2)
    {
		arrow(640, 340, 570, 380);
		arrow(770, 340, 840, 380);
		delay(1000);
		arrow(570, 420, 640, 460);
		arrow(840, 420, 770, 460);
	}
    else if(n == 3)
    {
		arrow(660, 240, 570, 280);
		arrow(740, 240, 840, 280);
		delay(1000);
	}
    else if(n == 4)
    {
		arrow(630, 250, 550, 300);
		arrow(780, 250, 860, 300);
		delay(1000);
	}
    else if(n == 5)
    {
		arrow(630, 150, 550, 200);
		arrow(780, 150, 860, 200);
		delay(1000);
	}
    else if(n == 6)
    {
		arrow(630, 150, 550, 200);
		arrow(780, 150, 860, 200);
		delay(1000);
	}
    else if(n == 7)
    {
		arrow(610, 150, 530, 200);
		arrow(780, 150, 860, 200);
		delay(1000);
	}
    else if(n == 8)
    {
		arrow(620, 150, 540, 200);
		arrow(780, 150, 860, 200);
		delay(1000);
	}
    else if(n == 9)
    {
		arrow(620, 150, 540, 200);
		arrow(780, 150, 860, 200);
		delay(1000);
	}
    else if(n == 10)
    {
		arrow(620, 150, 540, 200);
		arrow(780, 150, 860, 200);
		delay(1000);
	}
}

//Chia nho mang con cap 2 - dong thu 3
void veds_sub(int a[MAX], int left, int mid, int right) 
{
	//Neu day so co 3 so
	if(n == 3)
	{
		toado_x = 320;	
		toado_y = 450;	
	}
	//Neu day so co 4 so
	else if(n == 4)
	{
		toado_x = 350;	
		toado_y = 500;	
	}	
	//Neu day so co 5 so
	else if(n == 5)
	{
		toado_x = 350;	
		toado_y = 400;	
	}
	//Neu day so gom 6 so
	else if(n == 6)
	{
		toado_x = 310;
		toado_y = 400;	
	}
	//Neu day so gom 7 so
	else if(n == 7)
	{
		toado_x = 270;
		toado_y = 400;	
	}
	//Neu day so gom 8 so
	else if(n == 8)
	{
		toado_x = 250;
		toado_y = 400;	
	}
	//Neu day so gom 9 so
	else if(n == 9)
	{
		toado_x = 210;
		toado_y = 400;	
	}
	//Neu day so gom 10 so
	else if(n == 10)
	{
		toado_x = 210;
		toado_y = 400;	
	}
	////////////////////////////////////////////
	int mid_sub = mid / 2;
	//Left_Side     
	//Mang con nho hon ben trai
	for (int i = left; i <= mid_sub; i++) 
	{
	    setcolor(WHITE);	
	    int x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
	    int y = toado_y;
	    circle(x, y, RADIUS);
	    sprintf(buffer, "%d", a[i]);
	    outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
	}
    //Khoang cach (SMALL) cua 2 mang con da duoc chia nho
    if(n == 3)		toado_x += 310;	
    else if(n == 4)	toado_x += 250;	
    else if(n == 5)	toado_x += 210;	
    else if(n == 6)	toado_x += 285;	
	else			toado_x += 280;	
	//Mang con nho hon ben phai
	for (int i = mid_sub + 1; i <= mid; i++) 
	{
	    setcolor(WHITE);
	    int x = toado_x + (i - mid_sub - 1) * (2 * RADIUS + CIRCLE_GAP);
	    int y = toado_y;
	    circle(x, y, RADIUS);
	    sprintf(buffer, "%d", a[i]);
	    outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
	}
    //Khoang cach (BIG) cua 2 mang con da duoc chia nho
	if(n == 3)					toado_x += 360;	
	else if(n >= 4 && n <= 6)	toado_x += 210;	
	else if(n == 5 || n == 6)	toado_x += 210;	
	else if(n == 7 || n == 8)	toado_x += 280;
	else if(n == 9 || n == 10)	toado_x += 350;	
	////////////////////////////////////////////
	//Right_Side
	int mid_sub_right_1 = mid + 1 + (right - mid - 1) / 2;
    int mid_sub_right_2 = mid_sub_right_1 + 1;
    //Mang con nho hon ben trai
    for (int i = mid + 1; i <= mid_sub_right_1; i++) 
	{
    	int x = toado_x + (i - mid - 1) * (2 * RADIUS + CIRCLE_GAP);
        int y = toado_y;
        
        circle(x, y, RADIUS);
        char buffer[5];
        sprintf(buffer, "%d", a[i]);
        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
        setcolor(WHITE);		
	}
    //Khoang cach (SMALL) cua 2 mang con da duoc chia nho
	if(n == 4)					toado_x += 180;	
	else if(n == 5 || n == 6)	toado_x += 150;
	else if(n == 7)				toado_x += 130;
	else if(n == 8 || n == 9)	toado_x += 140;
	else if(n == 10)			toado_x += 70;
	//Mang con nho hon ben phai
    for (int i = mid_sub_right_2; i <= right; i++) 
	{
        setcolor(WHITE);
        int x = toado_x + (i - mid - 1) * (2 * RADIUS + CIRCLE_GAP);
        int y = toado_y;
        circle(x, y, RADIUS);
        sprintf(buffer, "%d", a[i]);
        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
    }
    //////////////////////////////////////////////////////////////////////////////
    //Goi ham ve mui ten
    if(n == 3)
    {
		arrow(420, 350, 360, 410);
		arrow(530, 350, 590, 410);
		arrow(910, 350, 960, 410);
		delay(1000);
		arrow(480, 480, 580, 580);
		arrow(940, 480, 820, 580);
	}
    else if(n == 4)
    {
		arrow(400, 400, 360, 450);
		arrow(540, 400, 580, 450);
		arrow(870, 400, 830, 450);
		arrow(990, 400, 1030, 450);
		delay(1000);
		arrow(470, 540, 560, 620);
		arrow(940, 540, 850, 620);
	}
    else if(n == 5)
    {
		arrow(450, 300, 400, 350);
		arrow(500, 300, 550, 350);
		arrow(850, 300, 800, 350);
		arrow(900, 300, 950, 350);
		delay(1000);
	}
    else if(n == 6)
    {
		arrow(410, 300, 360, 350);
		arrow(500, 300, 550, 350);
		arrow(900, 300, 850, 350);
		arrow(990, 300, 1040, 350);
		delay(1000);
	}
    else if(n == 7)
    {
		arrow(410, 300, 360, 350);
		arrow(470, 300, 520, 350);
		arrow(930, 300, 880, 350);
		arrow(1010, 300, 1060, 350);
		delay(1000);
	}
    else if(n == 8)
    {
		arrow(410, 300, 360, 350);
		arrow(440, 300, 490, 350);
		arrow(970, 300, 920, 350);
		arrow(1000, 300, 1050, 350);
		delay(1000);
	}
    else if(n == 9)
    {
		arrow(380, 300, 330, 350);
		arrow(460, 300, 510, 350);
		arrow(1000, 300, 950, 350);
		arrow(1030, 300, 1080, 350);
		delay(500);
	}
    else if(n == 10)
    {
		arrow(350, 300, 300, 350);
		arrow(420, 300, 470, 350);
		arrow(980, 300, 930, 350);
		arrow(1050, 300, 1100, 350);
		delay(500);
	}
}

//Chia nho mang con cap 3
void veds_sub_sub(int a[], int left, int mid, int right) 
{
	int mid_sub = mid / 2; 
	//Neu day so co 5 so
	if(n == 5)
	{
		toado_x = 300;	
		toado_y = 550;	
		
		int i;
		for(i = 0; i <= mid; i++)
		{
		    setcolor(WHITE);
	    	int x = toado_x + i * (5 * RADIUS + CIRCLE_GAP);
	        int y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}
		
		for(int i = mid + 1; i <= right; i++)
		{
			setcolor(WHITE);
	    	int x = 110 + i * (7 * RADIUS + CIRCLE_GAP);
	        int y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		arrow(370, 450, 320, 500);
		arrow(400, 450, 450, 500);
		arrow(580, 450, 600, 500);
		arrow(770, 450, 770, 500);
		arrow(990, 450, 990, 500);
		delay(1000);
		arrow(500, 600, 570, 650);
		arrow(900, 600, 830, 650);  
	}
	//Neu day so co 6 so
	if(n == 6)
	{
		toado_x = 250;	
		toado_y = 550;	
		int i;
		for(i = 0; i <= mid; i++)
		{
			setcolor(WHITE);
	    	int x = toado_x + i * (6 * RADIUS + CIRCLE_GAP);
	        int y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}
		//Khoang cach (BIG) cua 2 mang con da duoc chia nho
		toado_x = 180;
		for(int i = mid + 1; i <= right; i++)
		{
	        setcolor(WHITE);
	    	int x = toado_x + i * (6 * RADIUS + CIRCLE_GAP);
	        int y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
		}
		arrow(320, 450, 270, 500);
		arrow(370, 450, 420, 500);
		arrow(600, 450, 620, 500);
		arrow(820, 450, 770, 500);
		arrow(860, 450, 910, 500);
		arrow(1100, 450, 1120, 500);
		delay(1000);
		arrow(500, 600, 570, 650);
		arrow(900, 600, 830, 650);  
	}
	//Neu day so co 7 so
	if(n == 7)
	{
		toado_x = 240;	
		toado_y = 550;	
		int i;
		for(i = 0; i < mid - 1; i++)
		{
			setcolor(WHITE);
	    	int x = toado_x + i * (4 * RADIUS + CIRCLE_GAP);
	        int y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}
		toado_x = 260;
		for(i = mid - 1; i <= mid; i++)
		{
			setcolor(WHITE);
	    	int x = toado_x + i * (4 * RADIUS + CIRCLE_GAP);
	        int y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}		
		//Khoang cach (BIG) cua 2 mang con da duoc chia nho
		toado_x = 140;
		for(int i = mid + 1; i <= right; i++)
		{
			setcolor(WHITE);
	    	int x = toado_x + i * (5 * RADIUS + CIRCLE_GAP);
	        int y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		arrow(290, 450, 260, 500);
		arrow(320, 450, 350, 500);
		arrow(570, 450, 540, 500);
		arrow(600, 450, 630, 500);
		arrow(840, 450, 810, 500);
		arrow(880, 450, 910, 500);
		arrow(1100, 450, 1100, 500);
		delay(1000);
		arrow(460, 600, 530, 650);
		arrow(920, 600, 850, 650);  
	}	
	//Neu day so co 8 so
	if(n == 8)
	{
		toado_x = 220;	
		toado_y = 550;	
		int i;
		for(i = 0; i < mid - 1; i++)
		{
			setcolor(WHITE);
	    	int x = toado_x + i * (4 * RADIUS + CIRCLE_GAP);
	        int y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}
		toado_x = 240;
		for(i = mid - 1; i <= mid; i++)
		{
			setcolor(WHITE);
	    	int x = toado_x + i * (4 * RADIUS + CIRCLE_GAP);
	        int y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}		
		//Khoang cach (BIG) cua 2 mang con da duoc chia nho
		toado_x = 260;
		for(int i = mid + 1; i < right - 1; i++)
		{
			setcolor(WHITE);
	    	int x = toado_x + i * (4 * RADIUS + CIRCLE_GAP);
	        int y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		toado_x = 280;
		for(int i = right - 1; i <= right; i++)
		{
			setcolor(WHITE);
	    	int x = toado_x + i * (4 * RADIUS + CIRCLE_GAP);
	        int y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		arrow(270, 450, 240, 500);
		arrow(300, 450, 330, 500);
		arrow(550, 450, 520, 500);
		arrow(580, 450, 610, 500);
		arrow(830, 450, 800, 500);
		arrow(860, 450, 890, 500);
		arrow(1110, 450, 1080, 500);
		arrow(1140, 450, 1170, 500);
		delay(1000);
		arrow(430, 600, 480, 650);
		arrow(980, 600, 930, 650);  
	}

	//Neu day so co 9 so
	if(n == 9)
	{
		toado_x = 170;	
		toado_y = 550;	
		int i, x, y;		
		for(i = 0; i < 2; i++)
		{
		    setcolor(WHITE);
	    	x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}
		toado_x = 240;		
		i = 2;
	    setcolor(WHITE);
	    x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
	    y = toado_y;
	    circle(x, y, RADIUS);
	    sprintf(buffer, "%d", a[i]);
	    outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);	
		toado_x = 175;
		for(i = mid - 1; i <= mid; i++)
		{
	    	setcolor(WHITE);
	    	x = toado_x + i * (3 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}				
		//Khoang cach (BIG) cua 2 mang con da duoc chia nho
		toado_x = 160;
		for(int i = mid + 1; i < right - 1; i++)
		{
			setcolor(WHITE);
	    	x = toado_x + i * (4 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		toado_x = 180;
		for(int i = right - 1; i <= right; i++)
		{
		    setcolor(WHITE);
	    	x = toado_x + i * (4 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		arrow(250, 450, 220, 500);
		arrow(310, 450, 340, 500);		
		arrow(520, 450, 490, 500);
		arrow(530, 450, 560, 500);
		arrow(870, 450, 840, 500);
		arrow(880, 450, 910, 500);		
		arrow(1150, 450, 1120, 500);
		arrow(1160, 450, 1190, 500);	
		delay(1000);
		toado_x = 120;	
		toado_y = 700;
		for(i = 0; i < 2; i++)
		{
			setcolor(WHITE);
	    	x = toado_x + i * (5 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}
		toado_x = 240;		
		i = 2;
		setcolor(WHITE);
		x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
	    y = toado_y;
	    circle(x, y, RADIUS);
	    sprintf(buffer, "%d", a[i]);
	    outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
		toado_x = 175;
		for(i = mid - 1; i <= mid; i++)
		{
			setcolor(WHITE);
	    	x = toado_x + i * (3 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}
		//Khoang cach (BIG) cua 2 mang con da duoc chia nho
		toado_x = 160;
		for(int i = mid + 1; i < right - 1; i++)
		{
		    setcolor(WHITE);
	    	x = toado_x + i * (4 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		toado_x = 180;
		for(int i = right - 1; i <= right; i++)
		{
		    setcolor(WHITE);
	    	x = toado_x + i * (4 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		arrow(180, 600, 150, 650);
		arrow(220, 600, 250, 650);		
		arrow(380, 600, 380, 650);
		arrow(475, 600, 475, 650);
		arrow(575, 600, 575, 650);
		arrow(810, 600, 810, 650);
		arrow(940, 600, 940, 650);		
		arrow(1090, 600, 1090, 650);
		arrow(1220, 600, 1220, 650);
		delay(1000);
		arrow(330, 740, 390, 790);
		arrow(1090, 740, 1030, 790);
	}

	//Neu day so co 10 so
	if(n == 10)
	{
		toado_x = 170;	
		toado_y = 550;	
		int i, x, y;		
		for(i = 0; i < 2; i++)
		{
		    setcolor(WHITE);
	    	x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}
		toado_x = 240;		
		i = 2;
		setcolor(WHITE);
	    x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
	    y = toado_y;
	    circle(x, y, RADIUS);
	    sprintf(buffer, "%d", a[i]);
	    outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
		toado_x = 175;
		for(i = mid - 1; i <= mid; i++)
		{
		    setcolor(WHITE);
	    	x = toado_x + i * (3 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}				
		//Khoang cach (BIG) cua 2 mang con da duoc chia nho
		toado_x = 450;
		for(int i = mid + 1; i < 7; i++)
		{
		    setcolor(WHITE);
	    	x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		toado_x = 520;		
		i = 7;
	    setcolor(WHITE);
	    x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
	    y = toado_y;
	    circle(x, y, RADIUS);
	    sprintf(buffer, "%d", a[i]);
	    outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
		toado_x = 305;
		for(int i = 8; i <= right; i++)
		{
		    setcolor(WHITE);
	    	x = toado_x + i * (3 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		arrow(270, 450, 200, 500);
		arrow(290, 450, 360, 500);		
		arrow(520, 450, 490, 500);
		arrow(530, 450, 560, 500);
		arrow(900, 450, 830, 500);
		arrow(920, 450, 990, 500);		
		arrow(1150, 450, 1120, 500);
		arrow(1160, 450, 1190, 500);	
		delay(1000);
		toado_x = 120;	
		toado_y = 700;
		for(i = 0; i < 2; i++)
		{
		    setcolor(WHITE);
	    	x = toado_x + i * (5 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}
		toado_x = 240;		
		i = 2;
		setcolor(WHITE);
	    x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
	    y = toado_y;  
	    circle(x, y, RADIUS);
	    sprintf(buffer, "%d", a[i]);
	    outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
		toado_x = 175;
		for(i = mid - 1; i <= mid; i++)
		{
		    setcolor(WHITE);
	    	x = toado_x + i * (3 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);		
		}		
		for(int i = mid + 1; i < 7; i++)
		{
		    setcolor(WHITE);
	    	x =  i * (5 * RADIUS + CIRCLE_GAP) - 50;
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		toado_x = 520;		
		i = 7;
	    setcolor(WHITE);
	    x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
	    y = toado_y;
	    circle(x, y, RADIUS);
	    sprintf(buffer, "%d", a[i]);
	    outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
		toado_x = 305;
		for(int i = 8; i <= right; i++)
		{
		    setcolor(WHITE);
	    	x = toado_x + i * (3 * RADIUS + CIRCLE_GAP);
	        y = toado_y;
	        circle(x, y, RADIUS);
	        sprintf(buffer, "%d", a[i]);
	        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);			
		}
		arrow(190, 600, 150, 650);
		arrow(220, 600, 260, 650);		
		arrow(380, 600, 380, 650);
		arrow(475, 600, 475, 650);
		arrow(575, 600, 575, 650);
		arrow(820, 600, 780, 650);
		arrow(850, 600, 890, 650);		
		arrow(1010, 600, 1010, 650);
		arrow(1105, 600, 1105, 650);
		arrow(1205, 600, 1205, 650);
		delay(1000);
		arrow(280, 750, 350, 790);
		arrow(1150, 750, 1080, 790);
	}
}

//////////////////////////////////////////////////////////////////////////////////
void veds_sort(int a[MAX], int idx) 
{
	if(n == 2)
	{
		toado_x = 670;
		toado_y = 500;		
	}
	else if(n == 3)
	{
		toado_x = 630;
		toado_y = 600;
	}
	//Neu day so gom 4 so
	else if(n == 4)
	{
		toado_x = 600;
		toado_y = 650;	
	}
	//Neu day so gom 5 so
	else if(n == 5)
	{
		toado_x = 560;
		toado_y = 700;	
	}
	//Neu day so gom 6 so
	else if(n == 6)
	{
		toado_x = 525;
		toado_y = 700;	
	}
	//Neu day so gom 7 so
	else if(n == 7)
	{
		toado_x = 480;
		toado_y = 700;	
	}
	//Neu day so gom 8 so
	else if(n == 8)
	{
		toado_x = 455;
		toado_y = 700;	
	}
	//Neu day so gom 9 so
	else if(n == 9)
	{
		toado_x = 430;
		toado_y = 800;	
	}
	//Neu day so gom 10 so
	else if(n == 10)
	{
		toado_x = 400;
		toado_y = 800;	
	}
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    for (int i = 0; i < n; i++) {
        int x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
        int y = toado_y;

        if (i == idx) 
		{
            setcolor(RED);
        } 
		else 
		{
            setcolor(WHITE);
        }

        circle(x, y, RADIUS);
        sprintf(buffer, "%d", a[i]);
        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
    }
}

///////////////////////////////////////////////////////////
////Ham sap xep
void merge_tangdan(int a[MAX], int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    int temp[n1 + n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = 0;
    int index = left;
    while (i < n1 && j < n2) 
	{
        if (L[i] <= R[j]) 
		{
            temp[k] = L[i];
            i++;
        }
		else 
		{
            temp[k] = R[j];
            j++;
        }
        k++;

        // Hien thi mang sau moi buoc sap xep
        veds_sort(a, index);
        delay(500);
        index++;
    }
    while (i < n1) 
	{
        temp[k] = L[i];
        i++;
        k++;

        // Hien thi mang sau moi buoc sap xep
        veds_sort(a, index);
        delay(500);
        index++;
    }
    while (j < n2) 
	{
        temp[k] = R[j];
        j++;
        k++;

        // Hien thi mang sau moi buoc sap xep
        veds_sort(a, index);
        delay(500);
        index++;
    }
    // Sao chep mang temp vao mang goc
    for (int i = 0; i < k; i++) 
	{
        a[left + i] = temp[i];

        // Hien thi mang sau moi buoc sap xep
        veds_sort(a, left + i);
        delay(500);
    }
    // Hien thi mang sau khi tron
    for (int i = left; i <= right; i++)
	 {
        setcolor(GREEN);
        int x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
        int y = toado_y;

        circle(x, y, RADIUS);
        char buffer[5];
        sprintf(buffer, "%d", a[i]);
        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
        setcolor(WHITE);
    }
    delay(500);
}

void merge_giamdan(int a[MAX], int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];
    int temp[n1 + n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = 0;
    int index = left;
    while (i < n1 && j < n2) 
	{
        if (L[i] >= R[j]) 
		{
            temp[k] = L[i];
            i++;
        }
		else 
		{
            temp[k] = R[j];
            j++;
        }
        k++;

        // Hien thi mang sau moi buoc sap xep
        veds_sort(a, index);
        delay(500);
        index++;
    }

    while (i < n1) 
	{
        temp[k] = L[i];
        i++;
        k++;

        // Hien thi mang sau moi buoc sap xep
        veds_sort(a, index);
        delay(500);
        index++;
    }

    while (j < n2) 
	{
        temp[k] = R[j];
        j++;
        k++;

        // Hien thi mang sau moi buoc sap xep
        veds_sort(a, index);
        delay(500);
        index++;
    }

    // Sao ch?p mang temp v?o mang goc
    for (int i = 0; i < k; i++) 
	{
        a[left + i] = temp[i];

        // Hien thi mang sau moi buoc sap xep
        veds_sort(a, left + i);
        delay(500);
    }
    // Hien thi mang sau khi tron
    for (int i = left; i <= right; i++)
	{
        setcolor(GREEN);
        int x = toado_x + i * (2 * RADIUS + CIRCLE_GAP);
        int y = toado_y;

        circle(x, y, RADIUS);
        char buffer[5];
        sprintf(buffer, "%d", a[i]);
        outtextxy(x - textwidth(buffer) / 2, y - textheight(buffer) / 2, buffer);
        setcolor(WHITE);
    }
    delay(500);
}

void mergesort_tangdan(int a[MAX], int left, int right) 
{
    if (left < right) 
	{
        int mid = (left + right) / 2;
        mergesort_tangdan(a, left, mid);
        mergesort_tangdan(a, mid + 1, right);
        merge_tangdan(a, left, mid, right);
    }
}

void mergesort_giamdan(int a[MAX], int left, int right) 
{
    if (left < right) 
	{
        int mid = (left + right) / 2;
        mergesort_giamdan(a, left, mid);
        mergesort_giamdan(a, mid + 1, right);
        merge_giamdan(a, left, mid, right);
    }
}

/////////////////////////////////////////////////////////
//Ham tro chuot (mouse)
void mouse(){
	int x_mouse, y_mouse;
	while(enable_mouse)
	{
	///Cac su kien mouse click
		if(ismouseclick(WM_LBUTTONDOWN))
		{
			//Vi tri cua x_mouse, y_mouse khi click
			getmouseclick(WM_LBUTTONDOWN, x_mouse, y_mouse);
			//In ra toa do cua mouse
			printf("\n(%d, %d)", x_mouse, y_mouse);
			//Kiem tra khi nhan nut Load file
			if(x_mouse > 1380 && x_mouse < 1680 && y_mouse > 10 && y_mouse < 80)
			{
				clearviewport();
				loadfilestatus = 1;
				keyboardstatus = inputstatus = randstatus = randarraystatus = resetstatus = exitstatus = increasestatus = decreasestatus = 0;				
				giaodien();
			    printf("\n---------DOC NOI DUNG CAC DIEM TU TAP TIN INPUT---------\n");
			    int flag = 0;
			   	readfile(source, n, flag);
				if(flag == 0)
				{
				    //Ve cac diem ra man hinh	
					veds(source, n);									
				}
				else if(flag == 1)
				{
				    settextstyle(0, 0, 3);
				    outtextxy(425, 400, "Loi khong doc duoc FILE");
					outtextxy(350, 440, "Vui long kiem tra va sua FILE");					
				} 				
				else if(flag == 2)
				{
				    settextstyle(0, 0, 3);
				    outtextxy(150, 400, "Loi file do phat hien co gia tri khong hop le");
					outtextxy(350, 440, "Vui long kiem tra va sua FILE");					
				}  	
			}
			//Kiem tra khi nhan nut Keyboard
	        if(x_mouse > 1370 && x_mouse < 1680 && y_mouse > 100 && y_mouse < 170)
			{
				clearviewport();
				keyboardstatus = 1;
				loadfilestatus = inputstatus = randarraystatus = randstatus = resetstatus = exitstatus = increasestatus = decreasestatus = 0;
				giaodien();
			    settextstyle(0, 0, 3);
			    outtextxy(200, 400, "Waiting for input data from the keyboard");
			    outtextxy(400, 450, "at the console windows...");
	            printf("\n---------NHAP GIA TRI CUA 10 DIEM BANG BAN PHIM---------\n");
	            keyboard(source, n);
				clearviewport();
				giaodien();
	            //ve cac diem ra man hinh	
				veds(source,n);	            
			}
			//Kiem tra khi nhan nut Nhap so luong phan tu + Nhap gia tri cac phan tu do.
	        if(x_mouse > 1370 && x_mouse < 1680 && y_mouse > 200 && y_mouse < 270)
			{
				clearviewport();
				inputstatus = 1;
				loadfilestatus = keyboardstatus = randstatus = randarraystatus = resetstatus = exitstatus = increasestatus = decreasestatus = 0;
				giaodien();
			    settextstyle(0, 0, 3);
			    outtextxy(190, 400, "Waiting for input data from the keyboard");
			    outtextxy(380, 450, "at the console windows...");
	            printf("\n---------NHAP SO LUONG PHAN TU VA GIA TRI CAC PHAN TU---------\n");
				input_array(source, n);
				clearviewport();
				giaodien();
	            //ve cac diem ra man hinh
				veds(source,n);								
			}
			//Kiem tra khi nhan nut Tao ngau nhien 10 so
			if(x_mouse > 1370 && x_mouse < 1680 && y_mouse > 300 && y_mouse < 370)
			{
			
				clearviewport();
				randstatus = 1;
				loadfilestatus = keyboardstatus = inputstatus = randarraystatus = resetstatus = exitstatus = increasestatus = decreasestatus = 0;
				giaodien();
				printf("\n-----TAO NGAU NHIEN 10 SO-----\n");
				n = 10;
				random_num(source, n);
	            //ve cac diem ra man hinh	
				veds(source,n);
			}
			//Kiem tra khi nhan nut Tao ngau nhien tu 2 den 10 so
			if(x_mouse > 1370 && x_mouse < 1680 && y_mouse > 400 && y_mouse < 470)
			{
				clearviewport();
				randarraystatus = 1;
				loadfilestatus = keyboardstatus = inputstatus = randstatus = resetstatus = exitstatus = increasestatus = decreasestatus = 0;
				giaodien();
				if(count_click == 0)
				{
					printf("\n-----TAO NGAU NHIEN TU 2 DEN 10 SO-----");				
					random_array(source, &n);
		            //ve cac diem ra man hinh	
					veds(source,n);				
				}
				else
				{
					printf("\n-----RESET MANG DE TAO NGAU NHIEN MANG KHAC-----");
					clearviewport();
					giaodien();
					count_click = 0;
					delay(500);
					printf("\n-----TAO NGAU NHIEN TU 2 DEN 10 SO-----");				
					random_array(source, &n);
		            //ve cac diem ra man hinh	
					veds(source,n);
				}
				count_click++;
			}
			//Kiem tra khi nhan nut RESET
			if(x_mouse > 1370 && x_mouse < 1680 && y_mouse > 500 && y_mouse < 570)
			{
				if(loadfilestatus || keyboardstatus || inputstatus || randstatus || randarraystatus)
				{
					printf("\n-----THUC HIEN RESET THAO TAC-----\n");	
					clearviewport();
					resetstatus = 1;
					loadfilestatus = keyboardstatus = inputstatus = randstatus = randarraystatus = exitstatus = increasestatus = decreasestatus = 0;
					giaodien();					
				}
				else
				{
					resetstatus = 0;
					giaodien();
					printf("\nVUI LONG CHON CAC CHUC NANG NHAP HOAC TAO DAY SO TRUOC KHI NHAN NUT RESET...\n");					
				}
			}				
			//Kiem tra khi nhan nut EXIT
			if(x_mouse > 1370 && x_mouse < 1680 && y_mouse > 910 && y_mouse < 970)
			{
			    printf("\nTHOAT KHOI CHUONG TRINH DO HOA. VUI LONG NHAN NUT BAT KY DE THOAT CONSOLE...\n");
    			closegraph();
    			FreeConsole();
    			ExitProcess(0);
			}

			// Khi nhan nut sap xep tang dan
			if (x_mouse > 150 && x_mouse < 650 && y_mouse > 910 && y_mouse < 970) 
			{
			    if (loadfilestatus || keyboardstatus || inputstatus || randstatus || randarraystatus) 
				{
			        enable_mouse = 0;
			        printf("\nKHOI CHAY SAP XEP TANG DAN BANG THUAT TOAN MERGE SORT...");
			        increasestatus = 1;
			        decreasestatus = 0;
			        //Doi mau nut
			        if (decreasestatus == 1) 
			        {
			            clearviewport();
			            decreasestatus = 0;
			            giaodien();
			        }                    
					clearviewport();
					giaodien();
					veds(source, n);
					for(int i = 0; i < n; i++)
					{
						a[i] = source[i];
					}
					delay(500);
					//Goi ham ve 2 mang con duoc chia tu mang lon
					veds_chia(a, 0, (n - 1) / 2, n - 1);
					delay(500);
					if(n > 2)
					{
						veds_sub(a, 0, (n - 1) / 2, n - 1);
						delay(500);
					}
					if(n > 4)
					{
						veds_sub_sub(a, 0, (n - 1) / 2, n - 1);
						delay(500);
					}
				    veds_sort(a, 0);
				    mergesort_tangdan(a, 0, n - 1);
			        delay(500);
			        clearmouseclick(WM_LBUTTONDOWN);
			        clearmouseclick(WM_RBUTTONDOWN);    
			        enable_mouse = 1;   
			    } 
				else 
				{
			        printf("\nVUI LONG CHON CAC CHUC NANG NHAP HOAC TAO DAY SO TRUOC KHI NHAN NUT SAP XEP TANG DAN HOAC GIAM DAN...\n");
			    }	
			}

			// Khi nhan nut sap xep giam dan
			if (x_mouse > 750 && x_mouse < 1250 && y_mouse > 910 && y_mouse < 970) 
			{
			    if (loadfilestatus || keyboardstatus || inputstatus || randstatus || randarraystatus) 
			    {
					enable_mouse = 0;
					printf("\nKHOI CHAY SAP XEP GIAM DAN BANG THUAT TOAN MERGE SORT...");
					decreasestatus = 1;
					increasestatus = 0;
					//Doi mau nut
					if (increasestatus == 1) 
					{
					    clearviewport();
					    increasestatus = 0;
					    giaodien();
					}	
					clearviewport();
					giaodien();
			        veds(source, n);
					for(int i = 0; i < n; i++)
					{
						a[i] = source[i];
					}
					delay(500);
					//Goi ham ve 2 mang con duoc chia tu mang lon
					veds_chia(a, 0, (n - 1) / 2, n - 1);
					delay(500);
					if(n > 2)
					{
						veds_sub(a, 0, (n - 1) / 2, n - 1);
						delay(500);
					}
					if(n > 4)
					{
						veds_sub_sub(a, 0, (n - 1) / 2, n - 1);
						delay(500);
					}
					veds_sort(a, 0);
					mergesort_giamdan(a, 0, n - 1);
					delay(500);
					clearmouseclick(WM_LBUTTONDOWN);
					clearmouseclick(WM_RBUTTONDOWN);	
					enable_mouse = 1;					
				}
				else 
				{
			        printf("\nVUI LONG CHON CAC CHUC NANG NHAP HOAC TAO DAY SO TRUOC KHI NHAN NUT SAP XEP TANG DAN HOAC GIAM DAN...\n");
			    }
			}
		}	
		//Kiem tra khi nhan chuot phai thi thoat khoi vong lap
	    if (ismouseclick(WM_RBUTTONDOWN)) 
		{
	        getmouseclick(WM_RBUTTONDOWN, x_mouse, y_mouse);
	        printf("\nDANG THOAT KHOI CHUONG TRINH...");
	        break;
	    }
	    delay(100);
	}
}

/////////////////////////////////////////////////////////
//Chuong trinh chinh
int main()
{
	//Khoi tao man hinh do hoa
	initwindow(1700,1000);
	//Goi ham hien thi giao dien
	giaodien();
	//Goi ham chuot
	mouse();
	//Dung man hinh
	getch();
}
