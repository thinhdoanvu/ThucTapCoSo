#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#define MAX 100
#define INPUT "points.inp"

void mouse();
void readfile();
void keyboard();
void intoado(struct mt[MAX], int size);
void vediem(struct toado diem);
void veds(struct toado mt[MAX], int size);
void pointcolor(struct toado diem, int flag);
void vegiaodien();
void ShellSort();
struct toado
{
    int x;
    int y;
    int value;
};

struct toado td[MAX];
int npoints;
FILE *fp;
char buffer[10];
int flag;
int enable_mouse = 1;
int is_run = 0;

void mouse()
{
    int maxx, maxy;
    int x_mouse, y_mouse;
    while (enable_mouse)
    {
        // su kien mouse click
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            // Vi tri cua x_mouse, y_mouse khi click
            getmouseclick(WM_LBUTTONDOWN, x_mouse, y_mouse);
            // in ra toa do cua mouse
//            printf("\n(%d,%d)", x_mouse, y_mouse);

            // kiem tra nhan nut = Load file
            if (x_mouse > 590 && x_mouse < 740 && y_mouse > 10 && y_mouse < 50)
            {
                printf("\nDOC NOI DUNG CAC DIEM TU TAP TIN INPUT");
                readfile();
                // ve cac diem ra man hinh
                veds(td, npoints);
                // cho phep demo
                is_run = 1;
            }

            // kiem tra nhan nut = Keyboard
            if (x_mouse > 590 && x_mouse < 740 && y_mouse > 70 && y_mouse < 110)
            {
                printf("\nNHAP CAC DIEM BANG BAN PHIM");
                keyboard();
                // ve cac diem ra man hinh
                veds(td, npoints);
                // cho phep demo
                is_run = 1;
            }
            if (x_mouse > 590 && x_mouse < 740 && y_mouse > 190 && y_mouse < 230)
			{
				closegraph(); 
    			exit(0);
			}

            // kiem tra nhan nut = Demo
            if (is_run == 1 && x_mouse > 590 && x_mouse < 740 && y_mouse > 130 && y_mouse < 170)
            {
                printf("\nRUNNING...");
                ShellSort();
            }
        }

        // Check for right mouse button click to exit the loop
        if (ismouseclick(WM_RBUTTONDOWN))
        {
            getmouseclick(WM_RBUTTONDOWN, x_mouse, y_mouse);
            printf("\nRight mouse button clicked. Exiting...");
            break;
        }
        delay(100); // Delay to control the loop speed
    }
}

void keyboard()
{
    // Ðoc du lieu tu file và luu vào m?ng td
    fp = fopen(INPUT, "r");
    if (fp == NULL)
    {
        printf("Khong the mo file");
        return;
    }
    fscanf(fp, "%d", &npoints);
    for (int i = 0; i < npoints; i++)
    {
        fscanf(fp, "%d %d %d", &td[i].x, &td[i].y, &td[i].value);
    }
    fclose(fp);

    // Thay doi giá tri value tu bàn phím
    printf("\nNhap 10 so:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("Nhap so thu %d: ", i + 1);
        scanf("%d", &td[i].value);
    }

    // Ghi lai vào file
    fp = fopen(INPUT, "w");
    if (fp == NULL)
    {
        printf("Khong the mo file");
        return;
    }

    fprintf(fp, "%d\n", 10);
    for (int i = 0; i < 10; i++)
    {
        fprintf(fp, "%d %d %d\n", td[i].x, td[i].y, td[i].value);
    }

    fclose(fp);
}

void readfile()
{
    fp = fopen(INPUT, "r");
    if (fp == NULL)
    {
        printf("File not found");
        return;
    }
    fscanf(fp, "%d", &npoints);
    printf("\nSO LUONG CAC DIEM: %d", npoints);
    for (int i = 0; i < npoints; i++)
    {
        fscanf(fp, "%d %d %d", &td[i].x, &td[i].y, &td[i].value);
    }
    fclose(fp);
}

void intoado(struct toado mt[MAX], int size)
{
    printf("\ntoa do cac dinh: \n");
    for (int i = 0; i < size; i++)
    {
        printf("%d  %d %d\n", mt[i].x, mt[i].y, mt[i].value);
    }
}

void vediem(struct toado diem)
{
    setcolor(WHITE);
    setlinestyle(0, 1, 2);
    circle(diem.x, diem.y, 20);
    settextstyle(1, 0, 3);
    outtextxy(diem.x - 9, diem.y - 14, itoa(diem.value, buffer, 10));
}

void veds(struct toado mt[MAX], int size)
{
    for (int i = 0; i < size; i++)
    {
        vediem(mt[i]);
        delay(200);
    }
}

void pointcolor(struct toado diem, int flag)
{
    setcolor(WHITE);
    vegiaodien();
    if (flag == 1)
    {
        setcolor(RED);
    }
    else
    {
        if (flag == 2)
        {
            setcolor(GREEN);
        }
        else
        {
            setcolor(WHITE);
        }
    }
    circle(diem.x, diem.y, 20);
    settextstyle(1, 0, 3);
    outtextxy(diem.x - 9, diem.y - 14, itoa(diem.value, buffer, 10));
}


void ShellSort()
{
	int time = 300;
    for (int gap = npoints / 2; gap > 0; gap /= 2)
    {
        // Ve toan bo day diem mau trang
        for (int j = 0; j < npoints; j++)
        {
            pointcolor(td[j], 0);
        }
        delay(time);

        // Thuc hien Shell Sort voi khoang cach gap hien tai
        for (int i = gap; i < npoints; i++)
        {
            for (int j = i - gap; j >= 0 && td[j].value > td[j + gap].value; j -= gap)
            {
                // Ve hai diem dang so sanh voi mau do
                pointcolor(td[j], 1);
                pointcolor(td[j + gap], 1);
                delay(time);
                // So sanh va di chuyen cho neu can thiet
                int temp = td[j].value;
                td[j].value = td[j + gap].value;
                td[j + gap].value = temp;
                //  Ve hai diem da so sanh voi mau xanh la
                delay(time);
                pointcolor(td[j], 2);
                pointcolor(td[j + gap], 2);
                delay(500);
                // Tra lai mau trang cho hai diem so sanh
                pointcolor(td[j], 0);
                pointcolor(td[j + gap], 0);
                delay(time);
            }
        }

        
        cleardevice();
    }

    //ve day diem da duoc sap xep
    for (int j = 0; j < npoints; j++)
    {
        pointcolor(td[j], 3);
    }
    delay(time);

    // Ve giao dien sau khi sap xep
    vegiaodien();
    veds(td, npoints);
    printf("\nSAU KHI XAP XEP : ");
    for (int i = 0; i < npoints; i++)
    {
        printf("%d ", td[i].value);
    }
}



void vegiaodien()
{
    setcolor(CYAN);
    // ve khung lon
    setlinestyle(3, 1, 3);
    rectangle(10, 10, 550, 370);
    // ve nut load file
    setcolor(LIGHTMAGENTA);
    setlinestyle(1, 0, 2);
    rectangle(590, 10, 740, 50);
    settextstyle(2, 0, 7);
    outtextxy(630, 20, "Load file");
    // ve nut keyboard: y=y+60 (top,bot)
    setcolor(LIGHTCYAN);
    setlinestyle(1, 0, 2);
    rectangle(590, 70, 740, 110);
    settextstyle(2, 0, 7);
    outtextxy(630, 80, "Key board");
    // ve nut run: y=y+60 (top,bot)
    setcolor(LIGHTGREEN);
    setlinestyle(1, 0, 2);
    rectangle(590, 130, 740, 170);
    settextstyle(2, 0, 7);
    outtextxy(620, 140, "Run Demo");
    // Ve nút Reset: y=y+60 (top, bot)
	setcolor(LIGHTRED);
	setlinestyle(1, 0, 2);
	rectangle(590, 190, 740, 230);
	settextstyle(2, 0, 7);
	outtextxy(630, 200, "E x i t");

    //thong tin
    setcolor(LIGHTBLUE);
	settextstyle(2,0,5);
	outtextxy(590,270,"GVHD: Doan Vu Thinh");
	outtextxy(590,290,"Name: Ngo Hoang Vu");
	outtextxy(590,310,"MSSV: 63131717");
	outtextxy(590,330,"Email: vu.nh.63cntt@ntu.edu.vn");
	outtextxy(590,350,"Class: 63.CNTT-3");
}

int main()
{
    // khoi tao man hinh do hoa
    initwindow(800, 400);

    // ve giao dien
    vegiaodien();

    // goi ham chuot
    mouse();

    // ket thuc
    getch();
}
