#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<windows.h>
#include <graphics.h>
#define MAX_SIZE 100

using namespace std;
//Khai bao ham
void drawframe();
void drawButton(int left, int top, int right, int bottom, const char* label);
bool isMouseHover(int left, int top, int right, int bottom);
void handleMouseHover(int left, int top, int right, int bottom, const char* label, bool &hovered);
void drawgraph();
void clearGraph();
void cleanGraph();
void dfs(int current, int end, int n, int& done);
void DFS_display();
void openAndReadFile(const char* filePath);
void handleClick(int x, int y);
void mouse();
void waitForKeypress();

//Cac bien danh dau
bool isResetMode = false; // Bien danh dau reset
bool isGraphLoaded = false;//Bien xac dinh xem do thi da duoc nap hay chua 
bool isDFSExecuted = false;// Bien check dfs da chay bao gio chua

//DFS
int dothi[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE];

int path[MAX_SIZE];
int len = 0;

//Graphics
int sodinh;
struct toado {
    int x;
    int y;
    int label;
};
struct toado td[MAX_SIZE];
FILE *fp;
char buffer[10];
int mtk[MAX_SIZE][MAX_SIZE];

//Doc file toa do va ma tran ke
void openAndReadFile(const char* filePath) {
    fp = fopen(filePath, "r");
    if (fp == NULL) {
        printf("File not found");
    } else {
        fscanf(fp, "%d", &sodinh);
        for (int i = 0; i < sodinh; i++) {
            fscanf(fp, "%d %d %d", &td[i].x, &td[i].y, &td[i].label);
        }
    }
    for (int i = 0; i < sodinh; i++) {
            for (int j = 0; j < sodinh; j++) {
                fscanf(fp, "%d", &mtk[i][j]);
            }
        }

    isGraphLoaded = true;
    fclose(fp);
}
//Ve do thi
void drawgraph(){
	//Hien thi toa do cua dinh va mtk
    settextstyle(1, 0, 3);
    for (int i = 0; i < sodinh; i++) {
        circle(td[i].x, td[i].y, 20);
        outtextxy(td[i].x - 10, td[i].y - 10, itoa(td[i].label, buffer, 10));
    }
    for (int i = 0; i < sodinh; i++) {
        for (int j = 0; j < sodinh; j++) {
            if (mtk[i][j] == 1) {
                line(td[i].x, td[i].y, td[j].x, td[j].y);
            }
        }
	}
}
//Ham xu ly thao tac
void handleClick(int x, int y) {
	//Open file
	if(x >= 580 && x <= 680 && y >= 10 && y <= 50){
	OPENFILENAME ofn;
	TCHAR szFile[MAX_PATH];
	TCHAR szFolder[MAX_PATH];
// Lay duong dan den thu muc hien tai cua chuong trinh
	GetCurrentDirectory(MAX_PATH, szFolder);
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = TEXT("All Files (*.*)\0*.*\0");
	ofn.nFilterIndex = 1;

	ofn.lpstrInitialDir = szFolder; //Su dung thu muc hien tai lam thu muc mac dinh
    if (GetOpenFileName(&ofn)) {
    	const char* filePath = ofn.lpstrFile;
    	openAndReadFile(filePath);
    	ZeroMemory(szFile, sizeof(szFile));
	}
		clearGraph();
        drawframe();
        drawgraph();
	}
	
	//Author
	if(x >= 580 && x <= 700 && y >= 70 && y <= 100){
		cleanGraph();
		drawframe();
		settextstyle(10, 0, 1);
    	outtextxy(150, 110, "GVHD: Th.S. DOAN VU THINH");
    	outtextxy(150, 160, "SVTH: DANG HOANG LAM");
    	outtextxy(150, 210, "MSSV: 63134410");
	}
	
	//Start
    if (x >= 580 && x <= 700 && y >= 130 && y <= 170) {	
    if(isGraphLoaded || isResetMode ){
    	if (!isDFSExecuted) {
        DFS_display(); // Chay dfs neu chua duoc chay truoc do
        isDFSExecuted = true; // Da chay dfs
    } else {
        	cleanGraph();
        	drawframe();
        	drawgraph();
            DFS_display(); 
        }
        isGraphLoaded=true;
    	}else{
    		setcolor(WHITE);
    		cleanGraph();
			drawframe();
    		outtextxy(195, 120, "NO GRAPH TO START");
    		outtextxy(60, 170, "CLICK THE 'Load file' BUTTON TO ADD GRAPH");
		}
	}
	
    //Reset
    if (x >= 580 && x <= 700 && y >= 190 && y <= 230) {
    if (isGraphLoaded) {
        isResetMode = true;
        isDFSExecuted = false;
        cleanGraph();
        drawframe();
        drawgraph();
    }
    isGraphLoaded = false;
}
    
    //Delete
    if (x >= 580 && x <= 700 && y >= 250 && y <= 290) {
    	isResetMode= false;
        cleanGraph();
        drawframe();
        outtextxy(180, 120, "DATA HAS BEEN DELETED");
    	outtextxy(60, 170, "CLICK THE 'Load file' BUTTON TO ADD GRAPH");
    }
    //Exit
    if (x >= 580 && x <= 700 && y >= 310 && y <= 350) {
        closegraph();
    }
}

//Kiem tra hover
bool isMouseHover(int left, int top, int right, int bottom) {
    int x = mousex();
    int y = mousey();
    if (x >= left && x <= right && y >= top && y <= bottom) {
        return true; // Chuot di chuyen vao trong vung cua button
    }
    return false; // Chuot di chuyen ra khoi vung cua button
}

//Xu ly khi hover vao button
void handleMouseHover(int left, int top, int right, int bottom, const char* label, bool &hovered) {
    char buffer[MAX_SIZE]; // Khai báo buffer luu du lieu chuoi
    if (isMouseHover(left, top, right, bottom)) {
        setcolor(RED);
        rectangle(left, top, right, bottom);
        settextstyle(10, 0, 1);

        sprintf(buffer, "%s", label); //Dinh dang chuoi duoc luu vao buffer
        outtextxy(left + 10, top + 10, buffer); // Hien thi noi dung cua buffer

        hovered = true;
    } else if (hovered) {
        setcolor(WHITE);
        rectangle(left, top, right, bottom);
        settextstyle(10, 0, 1);
        
        sprintf(buffer, "%s", label); 
        outtextxy(left + 10, top + 10, buffer);
        hovered = false;
    }
}

//Ham ve button
void drawButton(int left, int top, int right, int bottom, const char* label) {
	
    setcolor(WHITE);
	setlinestyle(0, 1, 3);
    rectangle(left, top, right, bottom);
    settextstyle(10, 0, 1);

    char buffer[MAX_SIZE];
    strcpy(buffer, label);
    outtextxy(left + 10, top + 10, buffer);
}


//Ve khung do hoa
void drawframe() {
    setcolor(WHITE);
    setlinestyle(0, 1, 3);
    rectangle(10, 10, 550, 370);
    
    rectangle(10, 380, 550, 480);
    settextstyle(10, 0, 1);
    
    drawButton(580, 10, 700, 50, "Load file");
	drawButton(580, 70, 700, 110, "Author");
    drawButton(580, 130, 700, 170, "Starting");
    drawButton(580, 190, 700, 230, "Reset");
    drawButton(580, 250, 700, 290, "Delete");	
	drawButton(580, 310, 700, 350, "Exit");
}


//Xoa do thi
void clearGraph(){
	isDFSExecuted=false;
	memset(visited, 0, sizeof(visited));
	memset(path, 0, sizeof(path));
	len = 0;
	cleardevice();
}

//Xoa do thi
void cleanGraph(){
	memset(visited, 0, sizeof(visited));
	memset(path, 0, sizeof(path));
	len = 0;
	cleardevice();
	isGraphLoaded = false;//Gan ve false sau khi xoa do thi the hien chua nap
}

//Thuat toan
void dfs(int current, int end, int n, int& done) {
    int x = 20, y = 390;
    buffer[0] = '\0';
    visited[current] = 1;
    path[len++] = current;
    if (current == end) {
        done = 1;
        setcolor(RED);
        circle(td[current].x, td[current].y, 20);
        delay(500);
        //Gan gia tri cua path cho buffer
        for (int i = 0; i < len; i++) {
            string temp = to_string(path[i]);
            const char* tempChar = temp.c_str();
            strcat(buffer, tempChar);
            strcat(buffer, " ");
        }
        //In ra duong di o khung chu nhat ben duoi graph
        settextstyle(1, 0, 3);
        setcolor(WHITE);
        outtextxy(x, y, "DFS: ");
        outtextxy(x + 100, y, buffer);
        for (int i = 0; i < len; i++) {
            printf("%d ", path[i]);
        }
        //Ve lai duong di chinh xac cua dfs
        drawframe();
        drawgraph();
        for (int i = 0; i < len; i++) {
            setcolor(RED);
            circle(td[path[i]].x, td[path[i]].y, 20);
            line(td[path[i - 1]].x, td[path[i - 1]].y, td[path[i]].x, td[path[i]].y);
        }
        return;
    }
    for (int i = 0; i < sodinh; i++) {
        if (done == 0 && visited[current] == 1) {
            delay(50);
            setcolor(RED);
            circle(td[current].x, td[current].y, 20);
        }
        if (done == 0 && mtk[current][i] == 1 && visited[i] == 0) {
            delay(50);
            setcolor(RED);
            line(td[current].x, td[current].y, td[i].x, td[i].y);
            dfs(i, end, n, done);
        }
    }
    len--;
}

void DFS_display(){
		int done = 0;
		int start, end;
		printf("Nhap dinh bat dau: ");
        scanf("%d", &start);
        printf("Nhap dinh ket thuc: ");
        scanf("%d", &end);
        dfs(start, end, sodinh, done);
        printf("\n");
} 

//Ham xu ly con tro chuot
void mouse() {
    int x;
    int y;
    //Bien danh dau hover
    bool hovered = false;
	bool hovered1 = false; 
	bool hovered2 = false; 
	bool hovered3 = false; 
	bool hovered4 = false; 
	bool hovered5 = false; 
    while (!kbhit()) {
        if (ismouseclick(WM_MOUSEMOVE)) {
            getmouseclick(WM_MOUSEMOVE, x, y);
            handleMouseHover(580, 10, 700, 50, "Load file", hovered);
            handleMouseHover(580, 70, 700, 110, "Author", hovered1);
            handleMouseHover(580, 130, 700, 170, "Starting", hovered2);
            handleMouseHover(580, 190, 700, 230, "Reset", hovered3);
            handleMouseHover(580, 250, 700, 290, "Delete", hovered4);
            handleMouseHover(580, 310, 700, 350, "Exit", hovered5);
            clearmouseclick(WM_MOUSEMOVE);
        }
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            handleClick(x, y);
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

//main
int main() {
    //readfile();
    initwindow(720, 500);
    drawframe();
    mouse(); // Chay su kien click chuot

    getch(); // Cho  nguoi dung bam phim bat ki de tiep tuc
    closegraph();
    return 0;
}

