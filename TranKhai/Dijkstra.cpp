#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>//getch()
#include <time.h>//random
#include <cmath>//pow,sqrt,abs
#include <climits>//INT_MAX
#include<stdbool.h>

#define MAX 100
#define MAX_VALUES 9 //random numer in node
#define INPUT "graph.inp"
//global values
int sodinh;
FILE *fp; //file pointer
char buffer[10];
int enable_click = 1;
int graph[MAX][MAX];
int matrix[MAX][MAX];
int dist[MAX];
bool visited[MAX];
int n=1;
//tuan 3
FILE *fp_rand;
int start_node = 0;
int end_node = 8;
int length;
/////////////////////////////////////
////////////////////////////////////
//khai bao protype
void readFile();
void printPoints(struct toado m[MAX], int size);
void GUI_init();
void GUI_demo();
void mouse();
void keyboard();
void drawpoint(struct toado point, int color);
void drawpoint2(struct toado points[MAX], int size);
int rand_number_in_node();
void drawpoint_rand(struct toado points[MAX], int size);
void demo();
void draw_line(int start, int end, int color,int length);
//tuan 3
void Dijkstra();
void refreshGraph();
void draw_line_rand();
void readRandomGraph();
//tuan4
void initGraph();
void drawShortestPath(int parent[]);
int selectMinVertex(int value[], int processed[]);
////////////////////////////////////
struct toado{
	int x;
	int y;
	int value;
};

struct toado td[MAX];
////////////////////////////////////
void readFile(){
fp = fopen(INPUT,"r");
    if(fp==NULL){
        printf("File not found");
        return;
    }
    fscanf(fp, "%d",&sodinh);
    for(int i=0;i<sodinh;i++) {
        fscanf(fp, "%d %d %d", &td[i].x, &td[i].y, &td[i].value);
    }
    // Ð?c ma tr?n k? sau khi dã d?c t?t c? các di?m
    for(int i=0;i<sodinh;i++){
        for (int j=0;j<sodinh;j++){
            fscanf(fp, "%d",&matrix[i][j]);
        }
    }
    printPoints(td, sodinh);
    printf("Ma tran ke:\n");
    for(int i=0;i<sodinh;i++){
        for(int j=0;j<sodinh;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    
    fclose(fp);
}
///////////////////////////////////////

void readRandomGraph() {
    FILE *fp_rand = fopen("graph_temp.inp", "r");
    if (fp_rand == NULL) {
        printf("File not found");
        return;
    }
	//doc so dinh
    fscanf(fp_rand, "%d", &sodinh);
	//doc toa do
    for (int i = 0; i < sodinh; i++) {
        fscanf(fp_rand, "%d %d %d", &td[i].x, &td[i].y, &td[i].value);
    }
	//doc ma tran ke
    for (int i = 0; i < sodinh; i++) {
        for (int j = 0; j < sodinh; j++) {
            fscanf(fp_rand, "%d", &graph[i][j]);
        }
    }
    fclose(fp_rand);

    printf("Toa do: \n");
    printPoints(td, sodinh);

    printf("Ma tran ke: \n");
    for (int i = 0; i < sodinh; i++) {
        for (int j = 0; j < sodinh; j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}
////////////////////////////////////
void printPoints(struct toado m[MAX], int size){
	for(int i=0; i<size; i++){
		printf("%d %d %d\n", m[i].x, m[i].y, m[i].value);
	}
}
////////////////////////////////////
void GUI_init(){
	setcolor(WHITE);
	setlinestyle(0,1,3);//main border
	rectangle(10,10,680,320);
	// button load file
	rectangle(10,380,100,330);
	settextstyle(2,0,7);
	outtextxy(20,340,"Load file");
	// keyboard
	rectangle(115,380,220,330);
	settextstyle(2,0,7);
	outtextxy(125,340,"Keyboard");
	// demo
	rectangle(235,380,340,330);
	settextstyle(2,0,7);
	outtextxy(245,340,"Dijkstra");
	// reset
	rectangle(355,380,450,330);
	settextstyle(2,0,7);
	outtextxy(370,340,"Reset");
	// random
	rectangle(465,380,570,330);
	settextstyle(2,0,7);
	outtextxy(475,340,"Random");

	// exit
	rectangle(585,380,680,330);
	settextstyle(2,0,7);
	outtextxy(610,340,"Exit");
	
	rectangle(690,10,890,380);
	settextstyle(2,0,7);
	outtextxy(720, 20,"P.INFORMATION");
	outtextxy(695,40,"Full Name: Tran Khai");
	outtextxy(695,60,"Class: 63.CNTT-2");
	outtextxy(695,80,"Topic: Dijkstra with graphics");
	outtextxy(695,100,"Teacher: Doan Vu Thinh");
	outtextxy(695,150,"Describe: Tim duong di");	
	outtextxy(695,170,"ngan nhat tu dinh thu");	
	outtextxy(695,190,"0 den dinh thu 8 trong");
	outtextxy(695,210,"do thi");
}
////////////////////////////////////
////////////////////////////////////
void GUI_demo(){
	setcolor(WHITE);
	setlinestyle(0,1,3);//main border
	rectangle(10,10,680,320);
	setcolor(7);
	// button load file
	rectangle(10,380,100,330);
	settextstyle(2,0,7);
	outtextxy(20,340,"Load file");
	// keyboard
	rectangle(115,380,220,330);
	settextstyle(2,0,7);
	outtextxy(125,340,"Keyboard");
	// demo
	setcolor(4);
	rectangle(235,380,340,330);
	settextstyle(2,0,7);
	outtextxy(245,340,"Dijkstra");
	setcolor(7);
	// reset
	rectangle(355,380,450,330);
	settextstyle(2,0,7);
	outtextxy(370,340,"Reset");
	// random
	rectangle(465,380,570,330);
	settextstyle(2,0,7);
	outtextxy(475,340,"Random");

	// exit
	rectangle(585,380,680,330);
	settextstyle(2,0,7);
	outtextxy(610,340,"Exit");
}
////////////////////////////////////
//using mouse select button
void mouse() {
    int x_mouse, y_mouse;
    while(enable_click) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x_mouse, y_mouse);
            if(x_mouse>10&&x_mouse<100&&y_mouse>330&& y_mouse<380){ // load file button
                printf("Read from file ...");
                outtextxy(150,20,"TIM DUONG DI NGAN NHAT TU DINH 0 DEN 8");
                readFile();
                initGraph();
            }
            if(x_mouse>115&&x_mouse<220&&y_mouse>330&& y_mouse<380){ // keyboard button
                printf("INPUT ...");
                keyboard();
                demo();
            }
            //Dijkstra
            if(x_mouse>235&&x_mouse<340&&y_mouse>330&& y_mouse<380){ // demo button
                printf("Running ...");
                readFile();
                demo();        
				enable_click = 1;    
            }
            if(x_mouse>355&&x_mouse<450&&y_mouse>330&& y_mouse<380){ // demo button
                printf("Resting ...");
                cleardevice();
                GUI_init();
            }
            if(x_mouse>465&&x_mouse<570&&y_mouse>330&& y_mouse<380){ // demo button
                printf("Random ...");
                drawpoint_rand(td, sodinh);
                draw_line_rand();
            }
            if(x_mouse>585&&x_mouse<680&&y_mouse>330&& y_mouse<380){ // demo button
                printf("Exiting ...");
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
////////////////////////////////////
void keyboard(){//read data from keyboard
	fp = fopen(INPUT,"r");
    if(fp==NULL){
        printf("File not found");
        return;
    }
    fscanf(fp, "%d",&sodinh);
    for(int i=0;i<sodinh;i++) {
        fscanf(fp, "%d %d %d", &td[i].x, &td[i].y, &td[i].value);
        // nhap lai gia tri
		printf("\ntd[%d].value= ",i);
		scanf("%d",&td[i].value);
    }
    printPoints(td, sodinh);
    for(int i=0;i<sodinh;i++){
        for (int j=0;j<sodinh;j++){
            fscanf(fp, "%d",&matrix[i][j]);
        }
    }
    printf("Ma tran ke:\n");
    for(int i=0;i<sodinh;i++){
        for(int j=0;j<sodinh;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nFinished");
    fclose(fp);
}
////////////////////////////////////////////////////////////////
//-------------DRAW---------------//
void initGraph() {
	drawpoint2(td,sodinh);
    for (int i = 0; i < sodinh; i++) {
        for (int j = 0; j < sodinh; j++) {
            if (matrix[i][j] != 0) {
                draw_line(i, j, 4, matrix[i][j]);
                delay(100);
            }
        }
    }
}

void drawpoint(struct toado point, int color){
	setcolor(color);
	circle(point.x,point.y,20);
	settextstyle(1,0,3);
	outtextxy(point.x-9,point.y-14,itoa(point.value,buffer,10));
}

void drawpoint2(struct toado points[MAX], int size){
	for(int i=0;i<size;i++){
		drawpoint(points[i],15);
		delay(100);
	}
}

int rand_number_in_node() {
    static int usedValues[MAX_VALUES] = {0};  // M?ng d? theo dõi giá tr? dã s? d?ng
    int randomValue;
    int allUsed = 1;
    for (int i = 0; i < MAX_VALUES; i++) {
        if (usedValues[i] == 0) {
            allUsed = 0;
            break;
        }
    }
    if (allUsed) {
        for (int i = 0; i < MAX_VALUES; i++) {
            usedValues[i] = 0;
        }
    }
    do {
        randomValue = rand() % MAX_VALUES + 1;
    } while (usedValues[randomValue - 1] == 1); 
    usedValues[randomValue - 1] = 1;
    return randomValue;
}

void refreshGraph(){
    for (int i = 0; i < sodinh; i++) {
        for (int j = 0; j < sodinh; j++) {
            graph[i][j] = matrix[i][j];
        }
    }
}

void drawpoint_rand(struct toado points[MAX], int size) {
	readRandomGraph();
    srand(time(NULL));
    refreshGraph();
    FILE *fp_rand = fopen("graph_temp.inp", "w");
    if (fp_rand == NULL) {
        printf("File not found");
        return;
    }
    // ghi so dinh
    fprintf(fp_rand, "%d\n", sodinh);
    for(int i = 0; i < size; i++){
        struct toado randomPoint;
        randomPoint.x = points[i].x;
        randomPoint.y = 30 + rand() % (300 - 30 + 1);
        int randomColor = rand() % 9 + 1;
        randomPoint.value = rand_number_in_node();
        drawpoint(randomPoint, randomColor);
        // ghi toa do vao file
        fprintf(fp_rand, "%d %d %d\n", randomPoint.x, randomPoint.y, randomPoint.value);
        // Cap nhat ma tran ke
        graph[i][i] = randomPoint.value;
        delay(100);
    }
	//ghi ma tran ke vao file
    for (int i = 0; i < sodinh; i++) {
        for (int j = 0; j < sodinh; j++) {
			// ghi ma tran ke vao file
            fprintf(fp_rand, "%d ", graph[i][j]);
        }
        fprintf(fp_rand, "\n");
    }
    fclose(fp_rand);
    // Cap nhat ma tran ke random
    for (int i = 0; i < size; i++) {
        graph[i][i] = td[i].value;
    }
}

void draw_line(int start, int end, int color, int length) {
    setcolor(color);
    line(td[start].x, td[start].y, td[end].x, td[end].y);    
	// in khong cach cac node
    int mid_x = (td[start].x + td[end].x) / 2;
    int mid_y = (td[start].y + td[end].y) / 2;
    // display
    setcolor(WHITE);
    settextstyle(1, 0, 1);
    char length_str[5];
    itoa(length, length_str, 10);
    outtextxy(mid_x - 5, mid_y - 5, length_str);
    delay(100);
}

void draw_line_rand() {
	readRandomGraph();
	Dijkstra();
}

void drawShortestPath(int parent[]){
    for (int i = 1; i < sodinh; ++i){
        int u = parent[i];
        if (u != -1){
            draw_line(u, i, GREEN, graph[u][i]);
            GUI_demo();
            delay(200);
        }
    }
    drawpoint2(td, sodinh);
    delay(200);
}

//------------------------------END-DRAW--------------------------//
/////////////////////////////////////////////////////////////////

int selectMinVertex(int value[], int processed[]) {
    int minimum = INT_MAX;
    int vertex = -1;
    for (int i = 0; i < sodinh; ++i) {
        if (processed[i] == 0 && value[i] < minimum) {
            vertex = i;
            minimum = value[i];
        }
    }
    return vertex;
}

void Dijkstra(){
    int parent[sodinh];
    int value[sodinh];
    int processed[sodinh];
    parent[0] = -1;
    value[0] = 0;
    processed[0] = 0;
    for (int i = 1; i < sodinh; i++){
        parent[i] = -1;

        value[i] = INT_MAX;
        processed[i] = 0;
    }
    for (int i = 0; i < sodinh - 1; ++i){
        int u = selectMinVertex(value, processed);
        processed[u] = 1;
        for (int v = 0; v < sodinh; ++v){
            if (graph[u][v] != 0 && processed[v] == 0 && value[u] != INT_MAX &&(value[u] + graph[u][v] < value[v])){
                value[v] = value[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }
    drawShortestPath(parent);
}

void demo(){
    enable_click = 0;
    GUI_demo();
    // Khoi tao do thi
    for(int i=0; i<sodinh; i++){
        for(int j=0; j<sodinh; j++){
            graph[i][j] = matrix[i][j]; // lay ma tran ke tu file
        }
    }
    Dijkstra();
    GUI_demo();
}
////////////////////////////////////
//main
int main(){
	readFile();
	initwindow(900,400);
	GUI_init();
	mouse();
	getch();
}
