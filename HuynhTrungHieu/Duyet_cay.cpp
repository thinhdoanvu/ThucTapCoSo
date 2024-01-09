//-- Thu vien chuan C++
#include <iostream>
//-- Thu vien do hoa
#include<graphics.h>
//-- Thu vien de su dung thuat toan hang doi
#include<queue>
//-- Thu vien de su dung ham exit(0)
#include<stdlib.h>
//-- Thu vien de doc du lieu tu file
#include <fstream>
//-- Khong gian ten dung de luu tru
using namespace std;

#define MAX 50
#define INPUT "points.inp"

//-- Khai bao prototype
void GUI_init();
void mouse();
void readfile();
void printpoints(struct toado m[MAX], int size);
void keyboard(); 
void MoPhongVeCay();
void SinhCay();


int tmp, tmp1;
int dl = 400;
int continuee1 = 1;
int sodinh;//so dinh (so phan tu can sap xep)
ifstream fp;//file pointer
int enable_click = 1;
//-----------------------------------------------

//-- Giao dien menu chuong trinh
void GUI_init() {
    setcolor(WHITE);
    //main border
    setlinestyle(0, 1, 3);
    rectangle(10, 10, 900, 700);
    // Load file button
    rectangle(910, 10, 1010, 50);  // Tang gia tri toa do x de di chuyen ben phai
    settextstyle(2, 0, 7);
    outtextxy(920, 20, "Load file");

    // Keyboard button
    rectangle(910, 70, 1010, 110);  // Tang gia tri toa do x de di chuyen ben phai
    settextstyle(2, 0, 7);
    outtextxy(920, 80, "Keyboard");

    // Demo button
    rectangle(910, 130, 1010, 170);  // Tang gia tri toa do x de di chuyen ben phai
    settextstyle(2, 0, 7);
    outtextxy(920, 140, "Starting");
    
    rectangle(910, 190, 1140, 420);
    settextstyle(2, 0, 7);
    outtextxy(917, 200, "Tensv: Huynh Trung Hieu");
    
    settextstyle(2, 0, 7);
    outtextxy(920, 260, "Lop: 63.CNTT-3");
    
    
    settextstyle(2, 0, 7);
    outtextxy(920, 320, "MSSV: 63132050");
    
    
    settextstyle(2, 0, 7);
    outtextxy(920, 380, "GVHD: Doan Vu Thinh");
}



struct toado {
    int x;
    int y;
    int value;
};

struct toado td[MAX];//moi toa do la mot kieu toado(x,y,value)

//-- Ham doc du lieu tu file
void readfile() {
    fp.open(INPUT);
    if (!fp) {
        cout << "File not found" << endl;
        return;
    }
    //else
    //doc dong dau tien cua tap tin
    fp >> sodinh;
    cout << "So phan tu can duyet: " << sodinh << endl;
    //doc lan luot tung phan tu: moi ptu co 3 tham so: toado_x, toado_y, giatri
    for (int i = 0; i < sodinh; i++) {
        fp >> td[i].x >> td[i].y >> td[i].value;
    }
    //in ra cac diem
    printpoints(td, sodinh);
    fp.close();
}

//-- Ham in cac phan tu can duyet
void printpoints(struct toado m[MAX], int size) {
    for (int i = 0; i < size; i++) {
        cout << m[i].x << "  " << m[i].y << "  " << m[i].value << endl;
    }
}

//-- Ham nhap du lieu tu ban phim
void keyboard(){
	fp.open(INPUT);
    if (!fp) {
        cout << "File not found" << endl;
        return;
    }
    //else
    //doc dong dau tien cua tap tin
    fp >> sodinh;
    //doc lan luot tung phan tu: moi ptu co 2 tham so: toado_x, toado_y
    for (int i = 0; i < sodinh; i++) {
        fp >> td[i].x >> td[i].y;
    }
    //nhap gia tri cho cac dinh
    for (int i = 0; i < sodinh; i++) {
        std::cout << "td[" << i << "].value = ";
        std::cin >> td[i].value;
    }
    //in ra cac diem
    printpoints(td, sodinh);
    fp.close();
}



//-- Ham su dung chuot de thao tac: loadfile, keyboard, run demo
void mouse() {
    int x_mouse;
    int y_mouse;
    while (enable_click) {
        //get event mouse click
        if (ismouseclick(WM_LBUTTONDOWN)) {
            //get position of mouse
            getmouseclick(WM_LBUTTONDOWN, x_mouse, y_mouse);
            //checking for buttons
            if (x_mouse > 910 && x_mouse < 1010 && y_mouse > 10 && y_mouse < 50) {
                cout << "Read from file..." << endl;
                readfile();
                SinhCay();
            }
            //checking for buttons
            if (x_mouse > 910 && x_mouse < 1010 && y_mouse > 70 && y_mouse < 110) {
                cout << "Input from keyboard..." << endl;
                keyboard();
                break;
            }
            //checking for buttons
            if (x_mouse > 910 && x_mouse < 1010 && y_mouse > 130 && y_mouse < 170) {
                cout << "Running demo..." << endl;
                break;
            }
        }
        //check right mouse click to exit loop
        if (ismouseclick(WM_RBUTTONDOWN)) {
            //get position of mouse
            getmouseclick(WM_RBUTTONDOWN, x_mouse, y_mouse);
            //printf x,y mouse to console
            cout << "\nExiting..." << endl;
        }
        delay(100);//wait for next cycle mouse click
    }
}

//-- Mo phong tao cay
void MoPhongVeCay() //-- 4 6 2 3 1 5 9
{
	setlinestyle(3,1,3);
	setcolor(4);
	
	//---- node goc (4)
	settextstyle(0,0,4);
	outtextxy(435,53,"4"); //-- giam x 15, giam y 17
	circle(450,70,25); //-- x, y, ban kinh 
	
	
	//-- Tu (4) ve 2 ham line()	----------------------------------------------




	//--- Node cha (6)
	
	delay(dl);
	line(467,87,583,153); //-- tang x1,y1 17, giam x2,y2 di 17
	delay(dl);
	settextstyle(0,0,4);
	outtextxy(585,153,"6");
	circle(600,170,25);
	
	//--- Tu (6) ve 2 ham line() -----------------------------------
	
	
	
	
	//-- node cha (2)
	delay(dl);
	line(433,87,317,153); //-- giam x1,y2 17, tang y1,x2 17
	delay(dl);
	settextstyle(0,0,4);
	outtextxy(285,153,"2"); //-- Giam x 15, giam y 17 
	circle(300,170,25);
	
	//-- Tu (2) ve 2 ham line() ------------------------------
	
	
	
	//-- Node la (3)
	delay(dl);
	line(317,187,383,253); //-- tang x1,y1 di 17, giam x2,y2 17
	delay(dl);
	settextstyle(0,0,4);
	outtextxy(385,253,"3"); //-- Giam x 15, giam y 17 
	circle(400,270,25);
	
	
	
	
	//-- Node la (1)
	delay(dl);
	line(283,187,217,253); //-- Giam x1,y2,x2 di 17, tang y1 17
	delay(dl);
	settextstyle(0,0,4);
	outtextxy(185,253,"1"); //-- Giam x 15, giam y 17 
	circle(200,270,25);
	

		
	
	
	//-- Node la (5)
	delay(dl);
	line(583,187,517,253); //-- tang y1, giam x1,x2,y2
	delay(dl);
	settextstyle(0,0,4);
	outtextxy(483,253,"5"); //-- Giam x 15, giam y 17
	circle(500,270,25);
	
	
	
	
	
	//-- Node la (9)
	delay(dl);
	line(617,187,683,253);
	delay(dl);
	settextstyle(0,0,4);
	outtextxy(685,253,"9"); //-- Giam x 15, giam y 17
	circle(700,270,25);
	
}
//--------------------------------------------------------------
void TatDen()
{
	delay(dl);
	
	//-- tat den 1 ----------
	setcolor(4);
	settextstyle(0,0,4);
	outtextxy(185,253,"1"); //-- Giam x 15, giam y 17 
	circle(200,270,25);
	
	//-- tat den 2 -------------------------------------------
	setcolor(4);
	settextstyle(0,0,4);
	outtextxy(285,153,"2"); //-- Giam x 15, giam y 17 
	circle(300,170,25);	
	
	//--- tat den 3 -------------
	setcolor(4);
	settextstyle(0,0,4);
	outtextxy(385,253,"3"); //-- Giam x 15, giam y 17 
	circle(400,270,25);
	
	//-- Tat den 4 ---------------------------
	setcolor(4);
	settextstyle(0,0,4);
	outtextxy(435,53,"4"); // giam x 15, giam y 17
	circle(450,70,25);
		
	//---- tat den 5 -----------------------
	setcolor(4);
	settextstyle(0,0,4);
	outtextxy(483,253,"5"); //-- Giam x 15, giam y 17
	circle(500,270,25);
	
	//--- Tat den 6 ---------
	setcolor(4);
	settextstyle(0,0,4);
	outtextxy(585,153,"6"); //-- Gian x 15, giam y 17
	circle(600,170,25);	
		
	//--- tat den 9 --------------------
	setcolor(4);
	settextstyle(0,0,4);
	outtextxy(685,253,"9"); //-- Giam x 15, giam y 17
	circle(700,270,25);			
}
//------ Ham an den CHIEU CAO -------------
void AnDenCao()
{
	setcolor(0);
	
	//--- an den 4 ----------------------
	settextstyle(1,0,3);
	outtextxy(225,378,"4"); //-- Giam x 10, giam y 12
	circle(235,390,20);
	
	
	//--- an den 2 ---------------------------
	settextstyle(1,0,3);
	outtextxy(325,378,"2"); //-- Giam x 10, giam y 12
	circle(335,390,20);
	
	
	//--- an den 6 ----------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(425,378,"6"); //-- Giam x 10, giam y 12
	circle(435,390,20);
	
	
	//-- an den 1 ----------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(525,378,"1"); //-- Giam x 10, giam y 12
	circle(535,390,20);

	
	//-- an den 3 ------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(625,378,"3"); //-- Giam x 10, giam y 12
	circle(635,390,20);
	
	
	//--- an den 5 -----------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(725,378,"5"); //-- Giam x 10, giam y 12
	circle(735,390,20);
	
	
	//--- an den 9 ----------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(825,378,"9"); //-- Giam x 10, giam y 12
	circle(835,390,20);
}
//--- Ham an den NLR -----------------
void AnDenNLR()
{
	setcolor(0);
	//-- an den 4 ---------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(225,448,"4"); //-- Giam x 10, giam y 12
	circle(235,460,20);
	
	
	//-- an den 2 -----------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(325,448,"2"); //-- Giam x 10, giam y 12
	circle(335,460,20);
	
	
	//--- an den 1 -----------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(425,448,"1"); //-- Giam x 10, giam y 12
	circle(435,460,20);
	

	//-- an den 3 -------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(525,448,"3"); //-- Giam x 10, giam y 12
	circle(535,460,20);
	

	//---- an den 6 --------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(625,448,"6"); //-- Giam x 10, giam y 12
	circle(635,460,20);
	
	
	//--- an den 5 ----------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(725,448,"5"); //-- Giam x 10, giam y 12
	circle(735,460,20);
	

	//-- an den 9 -----------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(825,448,"9"); //-- Giam x 10, giam y 12
	circle(835,460,20);
}

//--- Ham an den LNR -----------------
void AnDenLNR()
{
	setcolor(0);
	//--- an den 1 -----------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(225,518,"1"); //-- Giam x 10, giam y 12
	circle(235,530,20);
	

	//-- an den 2 -------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(325,518,"2"); //-- Giam x 10, giam y 12
	circle(335,530,20);
	
	
	//---- an den 3 -------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(425,518,"3"); //-- Giam x 10, giam y 12
	circle(435,530,20);
	
	
	//--- an den 4 -------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(525,518,"4"); //-- Giam x 10, giam y 12
	circle(535,530,20);
	
	
	//-- an den 5 -------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(625,518,"5"); //-- Giam x 10, giam y 12
	circle(635,530,20);
	
	
	//-- an den 6 ---------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(725,518,"6"); //-- Giam x 10, giam y 12
	circle(735,530,20);
	
	
	//-- an den 9 ----------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(825,518,"9"); //-- Giam x 10, giam y 12
	circle(835,530,20);	
}

//--- Ham an den LRN -----------------
void AnDenLRN()
{
	setcolor(0);
	//-- an den 1 ------------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(225,588,"1"); //-- Giam x 10, giam y 12
	circle(235,600,20);
	

	//-- an den 3 -------------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(325,588,"3"); //-- Giam x 10, giam y 12
	circle(335,600,20);
	
	
	//-- an den 2 --------------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(425,588,"2"); //-- Giam x 10, giam y 12
	circle(435,600,20);
	
	
	//--- an den 5 --------------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(525,588,"5"); //-- Giam x 10, giam y 12
	circle(535,600,20);
	
	
	//-- an den 9 ----------------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(725,588,"9"); //-- Giam x 10, giam y 12
	circle(735,600,20);
	
	
	//-- an den 6 ------------------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(625,588,"6"); //-- Giam x 10, giam y 12
	circle(635,600,20);
	
	
	//-- an den 4 -----------------------------------------------------------------------------------
	settextstyle(1,0,3);
	outtextxy(825,588,"4"); //-- Giam x 10, giam y 12
	circle(835,600,20);
}

void KhungKetQua(){
	setcolor(5);
	// Ve hinh chu nhat voi toa do (20, 350) làm góc trên bên trái và (885, 635) làm góc duoi bên phai
	rectangle(20,350,885,635);
	// Ve duong ngang tu (20, 425) den (885, 425)
	line(20, 425, 885, 425);
	// Ve duong doc tu (200, 350) den (200, 635)
	line(200, 350, 200, 635);
	// Ve duong ngang tu (20, 495) den (885, 495)
	line(20, 495, 885, 495);
	// Ve duong ngang tu (20, 565) den (885, 565)
	line(20, 565, 885, 565);
}

//----------------------------------------------------------------
void BatDenVaInCao()
{
	//-- Duyet cay theo chieu cao
	delay(dl); 
	setcolor(14);
	settextstyle(0,0,2);
	outtextxy(25,380,"CHIEU CAO");
	KhungKetQua();

	//-------------------------------------------------------------------
	
	//-- bat den 4 ------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(435,53,"4"); // giam x 15, giam y 17
	circle(450,70,25);
	
	//--- in 4 ----------------------
	setcolor(2);
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(225,378,"4"); //-- Giam x 10, giam y 12
	circle(235,390,20);
	
	
	//-- bat den 2 ------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(285,153,"2"); //-- Giam x 15, giam y 17 
	circle(300,170,25);
	
	//--- in 2 ---------------------------
	setcolor(2);
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(325,378,"2"); //-- Giam x 10, giam y 12
	circle(335,390,20);
	
	
	//-- bat den 6 ---------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(585,153,"6"); //-- giam x 15, giam y 17
	circle(600,170,25);
	
	//--- in 6 ----------------------------------------------------
	setcolor(2);
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(425,378,"6"); //-- Giam x 10, giam y 12
	circle(435,390,20);
	
	
	//--- bat den 1 -----------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(185,253,"1"); //-- Giam x 15, giam y 17 
	circle(200,270,25);
	
	//-- in 1 ----------------------------------------------------
	setcolor(2);
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(525,378,"1"); //-- Giam x 10, giam y 12
	circle(535,390,20);

	
	//--- bat den 3 ----------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(385,253,"3"); //-- Giam x 15, giam y 17 
	circle(400,270,25);
	
	//-- in 3 ------------------------------------------------------------
	setcolor(2);
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(625,378,"3"); //-- Giam x 10, giam y 12
	circle(635,390,20);
	
	
	//--- bat den 5 ---------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(483,253,"5"); //-- Giam x 15, giam y 17
	circle(500,270,25);
	
	//--- in 5 -----------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(725,378,"5"); //-- Giam x 10, giam y 12
	circle(735,390,20);
	
	
	//--- bat den 9 -------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(685,253,"9"); //-- Giam x 15, giam y 17
	circle(700,270,25);
	
	//--- in 9 ----------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(825,378,"9"); //-- Giam x 10, giam y 12
	circle(835,390,20);
}
//------------ Duyet Chieu Sau ------------------------------------------
void BatDenVaInSauNLR()
{
	//-- Duyet NLR ----------------------------------------------------
	delay(dl);
	setcolor(14);
	settextstyle(0,0,2);
	outtextxy(75,450,"NLR");
	KhungKetQua();

	
	//--- bat den 4 ---------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(435,53,"4"); //-- Giam x 15, giam y 17
	circle(450,70,25);
	
	//-- in 4 ---------------------------------------------------------
	setcolor(2);
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(225,448,"4"); //-- Giam x 10, giam y 12
	circle(235,460,20);
	

	
	//-- bat den 2 ------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(285,153,"2"); //-- Giam x 15, giam y 17 
	circle(300,170,25);
	
	//-- in 2 -----------------------------------------------------------
	setcolor(2);
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(325,448,"2"); //-- Giam x 10, giam y 12
	circle(335,460,20);
	

	
	//--- bat den 1 ------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(185,253,"1"); //-- Giam x 15, giam y 17 
	circle(200,270,25);
	
	//--- in 1 -----------------------------------------------------------
	setcolor(2);
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(425,448,"1"); //-- Giam x 10, giam y 12
	circle(435,460,20);
	

	
	//-- bat den 3 --------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(385,253,"3"); // giam x 15, giam y 17
	circle(400,270,25);
	
	//-- in 3 -------------------------------------------------------------
	setcolor(2);
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(525,448,"3"); //-- Giam x 10, giam y 12
	circle(535,460,20);
	

	
	//--- bat den 6 ----------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(585,153,"6"); //-- Giam x 15, giam y 17
	circle(600,170,25);
	
	//---- in 6 --------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(625,448,"6"); //-- Giam x 10, giam y 12
	circle(635,460,20);

	
	//-- bat den 5 -----------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(483,253,"5"); //-- giam x 17, giam y 17
	circle(500,270,25);	
	
	//--- in 5 ----------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(725,448,"5"); //-- Giam x 10, giam y 12
	circle(735,460,20);
	

	
	//--- bat den 9 -----------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(685,253,"9"); //-- Giam x 15, giam y 17
	circle(700,270,25);	
	
	//-- in 9 -----------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(825,448,"9"); //-- Giam x 10, giam y 12
	circle(835,460,20);
}
//-----------------------------------------------------------------------------
void BatDenVaInSauLNR()
{
	//-- Duyet LNR -----------------------------------------------------------
	delay(dl);
	setcolor(14);
	settextstyle(0,0,2);
	outtextxy(75,520,"LNR");
	KhungKetQua();
	
	//-------------------------------------------------------------------------
	
	//-- bat den 1 ------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(185,253,"1"); //-- Giam x 15, giam y 17 
	circle(200,270,25);	
	
	//--- in 1 -----------------------------------------------------------------
	setcolor(2);
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(225,518,"1"); //-- Giam x 10, giam y 12
	circle(235,530,20);
	
	
			
	//-- bat den 2 -------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(285,153,"2"); //-- Giam x 15, giam y 17 
	circle(300,170,25);	
	
	//-- in 2 -------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(325,518,"2"); //-- Giam x 10, giam y 12
	circle(335,530,20);
	
	
	//--- bat den 3 -------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(385,253,"3"); //-- Giam x 15, giam y 17 
	circle(400,270,25);	
	
	//---- in 3 -------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(425,518,"3"); //-- Giam x 10, giam y 12
	circle(435,530,20);
	

	
	//---- bat den 4 -------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(435,53,"4"); //-- Giam x 15, giam y 17
	circle(450,70,25);	
	
	//--- in 4 -------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(525,518,"4"); //-- Giam x 10, giam y 12
	circle(535,530,20);
	
	
	//--- bat den 5 --------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(483,253,"5"); //-- Gian x 15, giam y 17
	circle(500,270,25);	
	
	//-- in 5 -------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(625,518,"5"); //-- Giam x 10, giam y 12
	circle(635,530,20);
	
	
	//--- bat den 6 -------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(585,153,"6"); //-- Giam x 15, giam y 17
	circle(600,170,25);	
	
	//-- in 6 ---------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(725,518,"6"); //-- Giam x 10, giam y 12
	circle(735,530,20);
	
	
	//-- bat den 9 ----------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(685,253,"9"); // giam x 15, giam y 17
	circle(700,270,25);	
	
	//-- in 9 ----------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(825,518,"9"); //-- Giam x 10, giam y 12
	circle(835,530,20);	
}
//-----------------------------------------------------------------------------
void BatDenVaInSauLRN()
{
	//--- Duyet LRN
	delay(dl);
	setcolor(14);
	settextstyle(0,0,2);
	outtextxy(75,590,"LRN");
	KhungKetQua();
	
	//--------------------------------------------------------------------------------
	
	//-- bat den 1 -------------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(185,253,"1"); // giam x 15, giam y 17
	circle(200,270,25);	
	
	//-- in 1 ------------------------------------------------------------------------
	setcolor(2);
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(225,588,"1"); //-- Giam x 10, giam y 12
	circle(235,600,20);
	
		
	//--- bat den 3 -------------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(385,253,"3"); //-- Giam x 15, giam y 17 
	circle(400,270,25);
	
	//-- in 3 -------------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(325,588,"3"); //-- Giam x 10, giam y 12
	circle(335,600,20);
	
	
		
	//-- bat den 2 --------------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(285,153,"2"); //-- Giam x 15, giam y 17 
	circle(300,170,25);	
	
	//-- in 2 --------------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(425,588,"2"); //-- Giam x 10, giam y 12
	circle(435,600,20);
	
	
	//--- bat den 5 ---------------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(483,253,"5"); //-- Giam x 15, giam y 17 
	circle(500,270,25);	
	
	//--- in 5 --------------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(525,588,"5"); //-- Giam x 10, giam y 12
	circle(535,600,20);
	
	
	//--- bat den 9 ---------------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(685,253,"9"); //-- Giam x 15, giam y 17
	circle(700,270,25);	
	
	//-- in 9 ----------------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(625,588,"9"); //-- Giam x 10, giam y 12
	circle(635,600,20);
	
	
	//-- bat den 6 ------------------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(585,153,"6"); //-- giam x 15, giam y 17
	circle(600,170,25);	
	
	//-- in 6 ------------------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(725,588,"6"); //-- Giam x 10, giam y 12
	circle(735,600,20);
	
	
	
	
	//--- bat den 4 ---------------------------------------------------------------------------
	delay(dl);
	setcolor(2);
	settextstyle(0,0,4);
	outtextxy(435,53,"4"); //-- Giam x 15, giam y 17
	circle(450,70,25);	
	
	//-- in 4 -----------------------------------------------------------------------------------
	delay(dl);
	settextstyle(1,0,3);
	outtextxy(825,588,"4"); //-- Giam x 10, giam y 12
	circle(835,600,20);
}
//------- Goi ham GRAPHICS ----------------------------------------------------------------------
//-- Duyet chieu cao --------------------------------------------
void MoPhongDuyetCayChieuCao()
{
	cout << "1. Duyet cay theo chieu cao: 4 2 6 1 3 5 9";
	TatDen();
	BatDenVaInCao();		
}
//--------------------------------------------------------------------------------
//-- Duyet chieu sau (3 cach) ---------------------------------------------
void MoPhongDuyetLNR()
{
	TatDen();
	BatDenVaInSauLNR();
}
//-----------------------------------------------------------------------------
void MoPhongDuyetLRN()
{
	TatDen();
	BatDenVaInSauLRN();		
}
//------------------------------------------------------------------------------------
void MoPhongDuyetNLR()
{
	TatDen();
	BatDenVaInSauNLR();
}
//------------------------------------------------------------------------------------------------
//----- Menu lua chon 1 trong 2 cach duyet -------------------------------------
void menu1()
{
	
	cout << "\n* CHON 1 TRONG 2 CACH DUYET (CHIEU RONG HOAC CHIEU SAU)";
	cout << "\n";
	cout << "\n 1. Duyet cay theo chieu cao";
	cout << "\n";
	cout << "\n 2. Duyet cay theo chieu sau";
}
//----- Menu duyet cay chieu cao ------------------
void menu2()
{
	
	cout << "\n* CHON 1 TRONG 3 CACH DUYET THEO CHIEU SAU";
	cout << "\n";
	cout << "\n 1. NLR";
	cout << "\n";
	cout << "\n 2. LNR";
	cout << "\n";
	cout << "\n 3. LRN";
	cout << "\n";
}
//-------------------------------------------------
void MoPhongDuyetCayChieuSau()
{
	//---------------------------------------
	cout << "\nLua chon cua ban la? ([1] or [2] or [3]): ";
	cin >> tmp1;
	//-- Duyet Cay theo chieu sau
	//---------------------------------------------------------------------------------------------
	if(tmp1 == 1)
	{
		AnDenNLR();
		cout << "\n  2.1. NLR: 4 2 1 3 6 5 9";
		MoPhongDuyetNLR();
	}
	if(tmp1 == 2)
	{
		AnDenLNR();
		cout << "\n  2.2. LNR: 1 2 3 4 5 6 9";
		MoPhongDuyetLNR();
	}
	if(tmp1 == 3)
	{
		AnDenLRN();
		cout << "\n  2.3. LRN: 1 3 2 5 9 6 4";
		MoPhongDuyetLRN();
	}
	//-----------------------------------------------------------------------------------------
}
//---------------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------------
//--- PHAN SINH DUYET CAY (LY THUYET VA MO PHONG)

struct node
{
	int data; //-- node mang gia tri la data.
	node *pleft,*pright; //--- 2 phan lien ket (trai - phai)
};
typedef node* tree;

//---------------------------------------------------------------------------------------------------

//-- Khoi tao cây
void init(tree &t)
{
	t=NULL; //-- gan t = NULL de tranh loi
}
//---------------------------------------------------------------------------------------------------

//-- Tao node moi
node* get_node(int data)
{
	node *p=new node(); //-- tao 1 node moi kieu con tro la p 
	p->data=data; //-- gian gia tri cho node moi = data
	p->pleft=NULL;//-- lien ket trai rong
	p->pright=NULL;//-- lien ket phai rong
	return p;
}


//------------------------------------------------------------------------------------------------

void SinhCay()
{
	tree t;
	MoPhongVeCay();
}

//------------------------------------------------------------------------------------------------
//-------- Phan Duyet Cay

//-- 1. Ham duyet cay nhi phan theo chieu cao
void DuyetCayTheoChieuCao(tree &t) //-- Duyet tu tren xuong, sau do tu trai qua.
{
	// Neu nhu cay co so phan tu (>=1)
	if(t!=NULL)
	{
		//-- Tao queue de luu vet (a)
		queue<tree> a;
		//-- Sau do them vao queue goc
		a.push(t);
		//-- Trong khi queue khac rong
		while(!a.empty())
		{
			//-- Node p co tac dung quay lui lai cac Node truoc do
			node *p=a.front();
			//-- Xuat du lieu 
			cout<<p->data<<" ";
			//-- Xu li xong xoa trong queue
			a.pop();
			//---------------------------------------
			//-- Duyet tu tren xuong va tu trai qua phai
			if(p->pleft!=NULL)
			{
				//-- Day node qua left
				a.push(p->pleft);
			}
			if(p->pright!=NULL)
			{
				//-- Day node qua right
				a.push(p->pright);
			}
		}
	}
}
//---------------------------------------------------------------------------------------------
//-- Ham Duyet theo chieu cao da dong goi
void DuyetCay1()
{
//	tree t;
//	input(t);
//	DuyetCayTheoChieuCao(t);
	MoPhongDuyetCayChieuCao();
}
//---------------------------------------------------------------------------------------------
//-- 2. Ham Duyet cay nhi phan theo chieu sau
//----- Duyet LNR ------------------------------------------------------------------------------

void DuyetLNR(tree &t)
{
	if(t == NULL)
		return;
	DuyetLNR(t->pleft);
	cout << t->data << " ";
	DuyetLNR(t->pright);
}

//---------------------------------------------------------------------------------------------

//----- Duyet LRN
void DuyetLRN(tree &t)
{
	if(t == NULL)
		return;
	DuyetLNR(t->pleft);
	DuyetLNR(t->pright);
	cout << t->data << " ";
}

//-----------------------------------------------------------------------------------------------

//----- Duyet NLR
void DuyetNLR(tree &t)
{
	if(t == NULL)
		return;
	cout << t->data << " ";
	DuyetLNR(t->pleft);
	DuyetLNR(t->pright);
}

//-------------------------------------------------------------------------------------------------
//-- Ham Duyet theo chieu sau da dong goi
void DuyetCay2()
{
//	tree t;
//	input(t);
//	DuyetLNR(t);
//	DuyetLRN(t);
//	DuyetNLR(t);
	menu2();
	MoPhongDuyetCayChieuSau();
	while(continuee1 == 1)
	{
		cout << "\n\nTiep tuc hay dung lai? (tiep tuc [1], dung lai [0]): ";
		cin >> continuee1;
		if(continuee1 == 1)
		{
			MoPhongDuyetCayChieuSau();
			
		}
		else
		{
			cout << "\nChuong trinh ket thuc!!! (da xoa du lieu)";
			exit(0);
		}
	}
	
}
//-------------------------------------------------------------------------------------------------

//--- Goi ham DuyetCay1 và DuyetCay2
void DuyetCay()
{
	//----------------- Phan Sinh Duyet Cay --------------------------------------------------------
	//-- Dua ra OPTIONS -----------
	cout << "\n\nLua chon cua ban la? ([1] or [2]): ";
	cin >> tmp;
	//-- 1. Sinh va Duyet Cay Theo Chieu cao (bfs)
	if(tmp == 1)
	{
		AnDenCao();//-- An cac den duyet chieu cao
		DuyetCay1();//-- Duyet theo chieu cao
	}
	//-- 2. Sinh va Duyet cay theo Chieu sau (dfs)
	if(tmp == 2)
	{
		DuyetCay2(); //-- Duyet theo chieu sau
	}
}

int main()
{
	initwindow(1170, 730);//width=700px, height=400px
    GUI_init();
    mouse();
    SinhCay();
	//--- Phan menu ----------------------------------------------
	menu1();
	//----------------------------------------------------------
	DuyetCay();
	while(continuee1 == 1)
	{
		cout << "\n\nTiep tuc hay dung lai? (tiep tuc [1], dung lai [0]): ";
		cin >> continuee1;
		if(continuee1 == 1)
		{
			DuyetCay();
		}
		else
		{
			cout << "\nChuong trinh ket thuc!!!";
			exit(0);
		}
	}
	getch();
	closegraph();
	return 0;
}
