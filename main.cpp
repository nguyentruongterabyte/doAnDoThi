#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <math.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wconversion-null"
#pragma GCC diagnostic ignored "-Wpointer-arith"
#define RADIUS 20
#define MAX 10
using namespace std;

struct Point/*cau truc diem*/ {
	int x;
	int y;
};

char *helpStr[] = {
	"Click chuot trai len bang hien thi dinh va canh",
	"Click chuot trai len 1 dinh bat ky -> click tiep vao dinh tiep theo. Mot canh se duoc tao giua dinh",
	"Click chuot phai len dinh can sua"
};

struct Vertex /*cau truc dinh*/{
	Point coordinates;
	char *name;
	void create();
	void draw();
	void createName();
	void highLight();
	void highLight(int tColor, int bColor);
	void defaultVtex();
	bool isDefaultVtex();
	bool isHover();
	bool isClickLMButton();
	void changeName();
};

struct Button /*cau truc nut*/{
	Point coordinates;
	char* name;
	short height;
	short width;
	short tColor;
	short bColor;
	short pattern;//cac kieu gach cheo, cham bi,.. trong nut
	
	void init(short x, short y, short height, short width, short tColor, short bColor, short pattern, char* content);//x, y, height, width, content
	void draw();//Ve nut
	void highLight();//To sang nut (doi mau theo kieu mac dinh)
	void normal();//Dua nut tro ve hinh dang ban dau
	void highLight(int tColor, int bColor);//To sang nut voi mau chu va mau nen 
	bool isHover();//Kiem tra xem ta co di chuyen chuot toi nut do hay khong
	bool isClickLMButton();//Kiem tra xem chuot trai co click vao o hay khong
};

int n = MAX;
Vertex vertices[MAX];
int G[MAX][MAX];

Button menuBar/*thanh menu*/, 
		helpBar/*thanh help*/,
		fileBar/*thanh file*/,
		adjacencyMatrixFrame/*khung hien thi ma tran ke*/, 
		pointBarFrame/*khung hien thi dinh va canh*/,
		taskBarFrame/*khung hien thi thanh tac vu gom menu, file va help*/,
		vertexTaskBarFrame/*khung hien thi thanh tac vu */,
		editFrame/*khung hien thi cac cong cu sua ten va xoa dinh*/,
		deleteButton/*Nut xoa dinh*/,
		editNameButton/*Nut sua ten dinh*/;

void process();
void helpBox(char *helpStr);
void setTaskBarButtons();
void drawTaskBarButtons();
void taskBar();//ham thao tac thanh tac vu 
int menuTools();//ham hien thi bang cong cu menu
int helpTools();//ham hien thi bang cong cu huong dan
int fileTools();//ham hien thi bang cong cu file
void setFrame();//cai dat khung hien thi
void drawFrame();//
void drawVertices();
void initDefaultVertices();//khi goi ham nay toa do cua cac dinh se tu dong la x = -1, y = -1
void loadFileStartUp();//khi tat chuong trinh, file nay se co chuc nang luu lai thong tin dinh canh cho lan chay tiep theo
void saveFileStartUp();//khi tao hay xoa dinh, file nay se co tac dung cap nhat lai nhung gi chung ta thao tac
void addVertexToList(Vertex vtex);//ham nay giup chung ta them mot dinh vua tao vao danh sach dinh
void clearAllVertices();//ham nay cho phep xoa tat ca cac dinh va cung dang hien thi tren man hinh
bool drawYesNoBar(char *question);//ham nay dung de xac nhan truoc khi lam gi do
bool isClickOtherVertex(Vertex vtexs);//kiem tra xem chuot trai co click vao dinh hay khong. Ham nay su dung de tranh tao dinh de len dinh khac
bool isEmptyVertex();//Kiem tra dinh tren man hinh da co hay chua
void strnDel(char *s, int pos, int count);//ham xoa ki tu trong chuoi
void upper(char *s);//Doi day s thanh chu in hoa
bool isNamesake(char *s);//Ham de kiem tra xem ten cua dinh vua tao co cung ten voi cac dinh khac khong
void drawAddVertex(int x, int y);//ve mot vong tron khi tao dinh
void editVertex();//xoa dinh tren do thi hoac doi ten dinh
void initEditTools();//Khoi tao hop thoai chinh sua dinh
void drawEditTools(int x, int y);//Vẽ hộp thoại edit dinh
void deleteVertex(int pos);//xoa dinh trong danh sach tai mot vi tri cho truoc
void moveVertex();//ham di chuyen dinh
void drawMatrix();//ve ma tran trong so
void drawArrow(Vertex u, Vertex v, int color, int w);//ve mui ten
void drawTriangle(int x1, int y1, int x2, int y2, int color);//ve hinh tam giac dung cho mui ten
void printWeight(int x, int y, int w);//xuat trong so 
void drawAllEdges();//ham ve tat ca cac canh
void drawCurvedArrow(Vertex u, Vertex v, int color, int w);//ve mui ten dang cong
void drawCurvedArrow2(Vertex u, Vertex v, int color, int w);


int main() {
	process();

}

void process() {
	Vertex vtex;
	int page = 0;
	initwindow(1280, 720);
	setTaskBarButtons();
	setFrame();
	initDefaultVertices();
	initEditTools();
	loadFileStartUp();
	while (true) {	
		setactivepage(page);
		setvisualpage(1 - page);
		delay(1);
		vtex.defaultVtex();
		setfillstyle(10, GREEN);
		bar(1, 1, 1279, 719);
		drawFrame();
		moveVertex();
		if (n < MAX) {
			vtex.create();
			addVertexToList(vtex);
		}
		drawVertices();
		drawMatrix();
		taskBar();
		editVertex();
		drawAllEdges();
		page = 1 - page;
	}
	getch();
	closegraph();
}

void drawCurvedArrow2(Vertex u, Vertex v, int color, int w) {
	int x1 = u.coordinates.x, 
		y1 = u.coordinates.y,
		x2 = v.coordinates.x,
		y2 = v.coordinates.y;
	char c = getcolor();
	float xO = (x1 + x2) / 2 + (y1 - y2) / M_SQRT2; // or +
	float yO = (y1 + y2) / 2 + (x2 - x1) / M_SQRT2; // or +
	float r = sqrt(pow(xO - x1, 2) + pow(yO - y1, 2));
	float d = sqrt(pow(x1 - xO, 2) + pow(y1 - yO, 2));
	float a = (pow(r, 2) - pow(RADIUS, 2) + pow(d ,2)) / (2 * d);
	float h = sqrt(r * r - a * a);								//					 
	float tmpx1 = xO + a * (x1 - xO) / d;						//					   xT		  
	float tmpx2 = xO + a * (x2 - xO) / d;						//        *  * x3             x4*  *
	float tmpy1 = yO + a * (y1 - yO) / d;						//     *        *            *        *
	float tmpy2 = yO + a * (y2 - yO) / d;						//    *    x1    *          *     x2   *
	int x3 = tmpx1 - h* (y1 - yO) / d;   // -h					//    *          *          *          *
	int x4 = tmpx2 + h* (y2 - yO) / d;   // +h					//     *        *            *        *
	int y3 = tmpy1 + h * (x1 - xO) / d;  // 					//        *  *                  *  *
	int y4 = tmpy2 - h * (x2 - xO) / d;  // 					//				 	   xO          
	float stangle, endangle;									//					 
	float angle1 = float(x1 - xO) / r;
	float angle2 = 1 - float(pow(RADIUS, 2)) / (2 * pow(r, 2));
	if (angle1 < -1 || angle1 > 1) angle1 = int(angle1);
	if (angle2 < -1 || angle2 > 1) angle2 = int(angle2);
	angle1 = acos(angle1) * 180 / M_PI;
	angle2 = acos(angle2) * 180 / M_PI;
	if (y1 >= yO) angle1 = 360 - angle1;
	stangle = angle1 + angle2;
	angle1 = acos(1 - pow(sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2)), 2) / (2 * pow(r, 2)));
	angle1 = angle1 * 180 / M_PI;
	stangle = stangle - angle1 - 2 * angle2;
	endangle = stangle + angle1;
	float theta = atan2((y1 + y2) / 2 - yO, (x1 + x2) / 2 - xO);
	float xT = xO + r * cos(theta);
	float yT = yO + r * sin(theta);
	setcolor(color);
	setlinestyle(SOLID_LINE, 1, 2);
	arc(xO, yO, stangle, endangle, r);
	drawTriangle(2 * x4 - (x2 + x4) / 2, 2 * y4 - (y2 + y4) / 2, x4, y4, color); // FINALY
	printWeight(xT, yT, w);
	setcolor(c);
}

void drawCurvedArrow(Vertex u, Vertex v, int color, int w) {
	int x1 = u.coordinates.x,
		y1 = u.coordinates.y,
		x2 = v.coordinates.x,
		y2 = v.coordinates.y;
	//M_SQRT2		1.41421356237309504880
	char c = getcolor();
		float xO = (x1 + x2) / 2 + (y1 - y2) / -M_SQRT2; // or +
	float yO = (y1 + y2) / 2 + (x2 - x1) / -M_SQRT2; // or +
	float r = sqrt(pow(xO - x1, 2) + pow(yO - y1, 2));
	float d = sqrt(pow(x1 - xO, 2) + pow(y1 - yO, 2));
	float a = (pow(r, 2) - pow(RADIUS, 2) + pow(d ,2)) / (2 * d);
	float h = sqrt(r * r - a * a);								//					 
	float tmpx1 = xO + a * (x1 - xO) / d;						//					   xT		  
	float tmpx2 = xO + a * (x2 - xO) / d;						//        *  * x3             x4*  *
	float tmpy1 = yO + a * (y1 - yO) / d;						//     *        *            *        *
	float tmpy2 = yO + a * (y2 - yO) / d;						//    *    x1    *          *     x2   *
	int x3 = tmpx1 + h* (y1 - yO) / d;   // -h					//    *          *          *          *
	int x4 = tmpx2 - h* (y2 - yO) / d;   // +h					//     *        *            *        *
	int y3 = tmpy1 - h * (x1 - xO) / d;  // 					//        *  *                  *  *
	int y4 = tmpy2 + h * (x2 - xO) / d;  // 					//				 	   xO          
	float stangle, endangle;									//					 
	float angle1 = float(x1 - xO) / r;
	float angle2 = 1 - float(pow(RADIUS, 2)) / (2 * pow(r, 2));
	if (angle1 < -1 || angle1 > 1) angle1 = int(angle1);
	if (angle2 < -1 || angle2 > 1) angle2 = int(angle2);
	angle1 = acos(angle1) * 180 / M_PI;
	angle2 = acos(angle2) * 180 / M_PI;
	if (y1 >= yO) angle1 = 360 - angle1;
	stangle = angle1 + angle2;
	angle1 = acos(1 - pow(sqrt(pow(x3 - x4, 2) + pow(y3 - y4, 2)), 2) / (2 * pow(r, 2)));
	angle1 = angle1 * 180 / M_PI;
	endangle = stangle + angle1; 
	float theta = atan2((y1 + y2) / 2 - yO, (x1 + x2) / 2 - xO);
	float xT = xO + r * cos(theta);
	float yT = yO + r * sin(theta);
	if (xT < 425 || xT > 1259 || yT < 20 || yT > 520)
		return drawCurvedArrow2(u, v, color, w);
	setcolor(color);
	setlinestyle(SOLID_LINE, 1, 2);
	arc(xO, yO, stangle, endangle, r);
	drawTriangle(2 * x4 - (x2 + x4) / 2, 2 * y4 - (y2 + y4) / 2, x4, y4, color); // FINALY
	printWeight(xT, yT, w);
	setcolor(c);
	
}

void drawAllEdges() {
	for (int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if (G[i][j])
				drawCurvedArrow(vertices[i], vertices[j], CYAN, G[i][j]);
		}
	}
}

void printWeight(int x, int y, int w) {
	char c = getcolor();
	setcolor(YELLOW);
	char str[10];
	itoa(w, str, 10);
	outtextxy(x, y, str);
	setcolor(c);
}

void drawTriangle(int x1, int y1, int x2, int y2, int color) {
	char c = getcolor();
	setlinestyle(SOLID_LINE, 0, 3);
	setfillstyle(SOLID_LINE, color);
	int a[8];
	a[0] = x1 + y2 - y1;
	a[1] = y1 + x1 - x2;
	a[2] = x1 - y2 + y1;
	a[3] = y1 - x1 + x2;
	a[4] = x2;
	a[5] = y2;
	a[6] = a[0]; 
	a[7] = a[1];
	setcolor(color);
	fillpoly(4, a);
	setlinestyle(SOLID_LINE, 0, 1);
	setcolor(c);
	
	setfillstyle(1, c);
}

void drawArrow(Vertex u, Vertex v, int color, float w) {
	
	int x1, x2, y1, y2;
	char c = getcolor();
	x1 = u.coordinates.x;
	y1 = u.coordinates.y;
	x2 = v.coordinates.x;
	y2 = v.coordinates.y;
	float corner = atan(float(abs(y2 - y1)) / abs(x1 - x2));
	float Rsin = RADIUS * sin(corner);
	float Rcos = RADIUS * cos(corner);
	int x11 = x1 + Rcos;
	int y11 = y1 + Rsin;
	int x22 = x2 - Rcos;
	int y22 = y2 - Rsin;
	if (x1 > x2) {
		x11 = x1 - Rcos;
		x22 = x2 + Rcos;
	}
	if (y1 > y2) {
		y11 = y1 - Rsin;
		y22 = y2 + Rsin;
	}
	setlinestyle(SOLID_LINE, 1, 2);
	setcolor(color);
	line(x11, y11, x22, y22);
	drawTriangle(2 * x22 - (x2 + x22) / 2, 2 * y22 - (y22 + y2) / 2, x22, y22, color);
	printWeight((x1 + x2) / 2, (y1 + y2) / 2, w);
	setcolor(c);
}

void drawMatrix() {
	Point center;
	int squareEdge = 30;
	Button square, vertexButton[MAX];
	square.init(0, 0, squareEdge, squareEdge, BLACK, BLACK, 1, "");
	//bien center de ghi toa do can giua cua khung ma tran
	center.x = 15 + 400 / 2;
	center.y = 304 + 400 / 2;
	int x0 = center.x - n * squareEdge / 2 + squareEdge / 2;
	int y0 = center.y - n * squareEdge / 2 + squareEdge;
	for (int i = 0; i < n; i++) {//ve khung ma tran trong so va in ra gia tri cua ma tran trong so
		int x = x0;//su dung bien x de luu gia tri ban dau cua x0
		vertexButton[i].init(0, 0, squareEdge, squareEdge, YELLOW, BLUE, 1, vertices[i].name);
		//khoi tao gia tri cua cac nut dinh trong ma tran trong so
		for (int j = 0; j < n; j++) {
			char numText[3];
			itoa(G[i][j], numText, 10);//chuyen trong so canh sang dang text
			square.init(x0, y0, squareEdge, squareEdge, WHITE, BLACK, 1, numText);
			//square.highLight();
			square.draw();
			if (square.isHover()) 
				square.highLight();
 			x0 += squareEdge;
		}
		x0 = x;
		y0 += squareEdge;
	}
	x0 = center.x - squareEdge * n / 2 - squareEdge / 2;
	y0 = center.y - squareEdge * n / 2;
	int y = y0;
	if (!isEmptyVertex()) {
		square.coordinates.x = x0;
		square.coordinates.y = y0;
		square.name = "";
		square.draw();
	}
	for (int i = 0; i < n; i++) {
		y0 += squareEdge;
		vertexButton[i].coordinates.x = x0;
		vertexButton[i].coordinates.y = y0;
		vertexButton[i].draw();
	}
	y0 = y;
	for (int i = 0; i < n; i++) {
		x0 += squareEdge;
		vertexButton[i].coordinates.x = x0;
		vertexButton[i].coordinates.y = y0;
		vertexButton[i].draw();
	}
}

void moveVertex() {
	int x, y;
	if (ismouseclick(WM_LBUTTONDOWN)) {
		getmouseclick(WM_LBUTTONDOWN, x, y);
		for (int i = 0; i < n; i++) {
			int x0 = vertices[i].coordinates.x;
			int y0 = vertices[i].coordinates.y;
			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= RADIUS * RADIUS) {
				int page = 0;
				while (true) {
					setactivepage(page);
					setvisualpage(1 - page);
					if (ismouseclick(WM_MOUSEMOVE)) {
						getmouseclick(WM_MOUSEMOVE, x, y);
						bool check = 0;//check trung dinh
						for (int j = 0; j < n; j++)
							if (j != i) {
								int xB = vertices[j].coordinates.x;
								int yB = vertices[j].coordinates.y;
								if ((x - xB) * (x - xB) + (y - yB) * (y - yB) <= 4 * RADIUS * RADIUS)
									check = 1;
							}
						if (x >= 425 + RADIUS && x <= 1259 - RADIUS
						&& y >= 20 + RADIUS && y <= 520 - RADIUS && !check) {
							//neu nam trong pham vi bang dieu khien thi moi duoc di chuyen 
							vertices[i].coordinates.x = x;
							vertices[i].coordinates.y = y;
						}
						if (x < 435 + RADIUS && y >= 20 + RADIUS && y <= 520 - RADIUS) {
							vertices[i].coordinates.x = 425 + RADIUS;
							vertices[i].coordinates.y = y;
						}
						if (x > 1259 - RADIUS && y >= 20 + RADIUS && y <= 520 - RADIUS) {
							vertices[i].coordinates.x = 1259 - RADIUS;
							vertices[i].coordinates.y = y;
						}
						if (x >= 425 + RADIUS && x <= 1259 - RADIUS
						&& y < 20 + RADIUS) {
							vertices[i].coordinates.x = x;
							vertices[i].coordinates.y = 20 + RADIUS;
						}
						if (x >= 425 + RADIUS && x <= 1259 - RADIUS
						&& y > 520 - RADIUS) {
							vertices[i].coordinates.x = x;
							vertices[i].coordinates.y = 520 - RADIUS;
						}
					}					
					drawFrame();
					drawTaskBarButtons();
					drawVertices();
					drawMatrix();
					drawAllEdges();
					if (ismouseclick(WM_LBUTTONUP)) {
						break;
					}
					page = 1 - page;	
				}
			}
		}
	}
	saveFileStartUp();
	clearmouseclick(WM_LBUTTONDOWN);
	clearmouseclick(WM_LBUTTONUP);
}

void Vertex::changeName() {
	Button frame, finishButton, cancelButton, enterNameBar;
	int margin = 5;
	int height = 275 - 3 * margin - 40;
	int width = 400 - 2 * margin;
	int x, y;
	char name[3] = ""; 
	char request[] = "Nhap ten dinh";
	frame.init(15 + margin, 15 + 2 * margin + 40, height, width, YELLOW, DARKGRAY, 1, "");
	finishButton.init(15 + 2 * margin, 275 - margin - 30, 40, (width - 3 * margin) / 2, YELLOW, BLACK, 9, "HOAN THANH");
	cancelButton.init(15 + 3 * margin + (width - 3 * margin) / 2,275 - margin - 30, 40, (width - 3 * margin) / 2, YELLOW, BLACK, 9, "HUY");
	enterNameBar.init(15 + 2 * margin, 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50, 40, (width - 2 * margin), YELLOW, BLACK, 9, "");
	int page = 0;
	int i = 0; 
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		delay(50);
		if (ismouseclick(WM_LBUTTONDOWN))
			getmouseclick(WM_LBUTTONDOWN, x, y);
		setfillstyle(10, GREEN);
		bar (1, 1, 1279, 719);
		drawFrame();
		drawTaskBarButtons();
		drawVertices();
		drawMatrix();
		frame.draw();
		finishButton.draw();
		cancelButton.draw();
		enterNameBar.draw();
		drawAddVertex(this->coordinates.x, this->coordinates.y);
	
		if (strcmp(name, "") == 0) {
			outtextxy(15 + (400 - width) / 2 + (width - textwidth(request)) / 2, 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50 + (40 - textheight(request)) / 2, request);
			int x0 = this->coordinates.x, y0 = this->coordinates.y;
			line(x0, y0, x0 - RADIUS + 5, y0);
			line(x0, y0, x0 + RADIUS - 5, y0);
			line(x0, y0, x0, y0 + RADIUS - 5);
			line(x0, y0, x0, y0 - RADIUS + 5);
		}
		if (kbhit()) {
			char key = getch();
			if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) {
				//Neu phim ta nhap la chu cai thi moi them vao chuoi
				if (i < 2) {
					//Neu chieu dai cua chuoi da day thi khong cho them vao chuoi
					name[i] = key;
					i++;//vi tri se duoc nhay len mot don vi sau khi them mot ky tu vao chuoi
				}
			}
			if (i > 2)
				i = 2;
			if (key == 8) {
				strnDel(name, i - 1, 1);//xoa ki tu co vi tri sau cung cua chuoi
				i--;//vi tri se duoc giam xuong 1 don vi
			}
			if (i < 0)
				i = 0;
			if (strcmp(name, "") != 0 && key == 13 && !isNamesake(name)) {
				break;
			}
			if ((strcmp(name, "") == 0 && key == 13)) {
				frame.highLight(WHITE, RED);
				enterNameBar.draw();
				finishButton.draw();
				cancelButton.draw();
				delay(50);
			}
			if (isNamesake(name)) {
				for (int i = 0; i < n; i++)
					if (stricmp(name, vertices[i].name) == 0) {
						vertices[i].highLight();
						delay(50);
					}
			}
		}
		upper(name);
		outtextxy(15 + (400 - width) / 2 + (width - textwidth(name)) / 2, 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50 + (40 - textheight(name)) / 2, name);
		outtextxy(this->coordinates.x - textwidth(name) / 2, this->coordinates.y - textheight(name) / 2, name);
		if (finishButton.isHover())
			finishButton.highLight();
		if (cancelButton.isHover())
			cancelButton.highLight();
		if (ismouseclick(WM_LBUTTONDBLCLK))// neu co double click chuot trai khi dang tao ten thi phai xoa di
											//de tranh truong hop sau khi tao ten thi tao luon dinh moi
			clearmouseclick(WM_LBUTTONDBLCLK);
		if (ismouseclick(WM_RBUTTONDOWN))//neu co click chuot phai khi dang tao ten thi phai xoa di 
										//de tranh truong hop sau khi tao ten thi mo thanh edit dinh
			clearmouseclick(WM_RBUTTONDOWN);
		page = 1 - page;
		if (strcmp(name, "") != 0 && !isNamesake(name)
		&& x >= finishButton.coordinates.x && x <= finishButton.coordinates.x + finishButton.width
		&& y >= finishButton.coordinates.y && y <= finishButton.coordinates.y + finishButton.height)
			break;
		if (x >= cancelButton.coordinates.x && x <= cancelButton.coordinates.x + cancelButton.width
		&& y >= cancelButton.coordinates.y && y <= cancelButton.coordinates.y + cancelButton.height) {
			return;
		}
	}
	cout << name << endl;
	if (strcmp(name, "") == 0)
		return;
//	this->name = name;
	strcpy(this->name, name);
}

void deleteVertex(int pos) {
	for (int i = pos; i < n - 1; i++)
		vertices[i] = vertices[i + 1];//Cap nhat lai danh sach dinh
	for (int i = pos; i < n - 1; i++) 
		for (int j = 0; j < n; j++) 
			G[i][j] = G[i + 1][j];//Xoa hang trong ma tran ke
	for (int i = 0; i < n; i++)
		for (int j = pos; j < n - 1; j++)
			G[i][j] = G[i][j + 1];//Xoa cot trong ma tran ke
	vertices[n - 1].defaultVtex();
	n--;
	saveFileStartUp();
}

void drawEditTools(int x, int y) {
	editFrame.coordinates.x = x, editFrame.coordinates.y = y;
	deleteButton.coordinates.x = x, deleteButton.coordinates.y = y;
	editNameButton.coordinates.x = x, editNameButton.coordinates.y = y + deleteButton.height;
	
	editFrame.draw();
	deleteButton.draw();
	editNameButton.draw();
}

void initEditTools() {
	//do hop thoai nay co the dung o bat ky vi tri nao trong chuong trinh nen x y mac dinh cua no la 0
	editFrame.init(0, 0, 80, 100, WHITE, DARKGRAY, 1, "");
	deleteButton.init(0, 0, 40, 100, YELLOW, BLACK, 1, "Xoa dinh");
	editNameButton.init(0, 0, 40, 100, YELLOW, BLACK, 1, "Sua ten");
}

void editVertex() {
	int x, y;
	if (ismouseclick(WM_RBUTTONDOWN)) {
		getmouseclick(WM_RBUTTONDOWN, x, y);
		for (int i = 0; i < n; i++) {
			int x0 = vertices[i].coordinates.x,
				y0 = vertices[i].coordinates.y;
			if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= RADIUS * RADIUS) {
				int page = 0;
				while (true) {
					setactivepage(page);
					setvisualpage(1 - page);
					delay(10);
					setfillstyle(10, GREEN);
					bar(1, 1, 1279, 719);
					drawFrame();
					drawTaskBarButtons();
					drawVertices();
					drawMatrix();
					if (x0 + RADIUS > 1259 - editFrame.width && y0 < 520 - editFrame.height)
						drawEditTools(x0 - RADIUS - editFrame.width, y0);//goc tren cung ben phai
					else if (x0 + RADIUS > 1259 - editFrame.width && y0 > 520 - editFrame.height)
						drawEditTools(x0 - RADIUS - editFrame.width, y0 - editFrame.height);//goc duoi cung ben phai
					else if (y0 > 520 - editFrame.height)
						drawEditTools(x0 + RADIUS, y0 - editFrame.height);//goc duoi cung ben trai
					else 
						drawEditTools(x0 + RADIUS, y0);//cac cho con lai
					if (ismouseclick(WM_RBUTTONDOWN)) {
						int xR, yR;
						getmouseclick(WM_RBUTTONDOWN, xR, yR);
						if ((xR - x0) * (xR - x0) + (yR - y0) * (yR - y0) > RADIUS * RADIUS)
							break;
					} 
					if (deleteButton.isHover())
						deleteButton.highLight();
					if (editNameButton.isHover())
						editNameButton.highLight();
					if (ismouseclick(WM_LBUTTONDOWN)) {
						int xL, yL;
						getmouseclick(WM_LBUTTONDOWN, xL, yL);
						if (xL >= deleteButton.coordinates.x && xL <= deleteButton.coordinates.x + deleteButton.width
						&& yL >= deleteButton.coordinates.y && yL <= deleteButton.coordinates.y + deleteButton.height) {
							bool confirm = drawYesNoBar("Ban co chac muon xoa dinh?");
							if (confirm) {
								deleteVertex(i);
							}
							break;
						}
						else if (xL >= editNameButton.coordinates.x && xL <= editNameButton.coordinates.x + editNameButton.width
						&& yL >= editNameButton.coordinates.y && yL <= editNameButton.coordinates.y + editNameButton.height) {
							vertices[i].changeName();	
							break;	
						}
						else 
							break;
					}
					page = 1 - page;
				}
			}
		}
	}
}

void drawAddVertex(int x, int y) {
	char c = getcolor();
	setcolor(YELLOW);
	circle(x, y, RADIUS);
	setcolor(c);
}

bool isNamesake(char *s) {
	for (int i = 0; i < n; i++) {
		if(stricmp(s, vertices[i].name) == 0)
			return 1;
	}
	return 0;
}

void upper(char *s) {
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
	}
}

void strnDel(char s[], int pos, int count) {
	unsigned len = strlen(s);
	if (pos >= len) 
		return;
	if (pos + count > len) 
		count = len - pos;
	for (unsigned i = 0; i <= len - pos - count; i++)
		s[pos + i] = s[pos + count + i];
}

bool Button::isClickLMButton() {
	int x, y;
	getmouseclick(WM_LBUTTONDOWN, x, y);
	if (x >= this->coordinates.x && x <= this->coordinates.x + this->width
	&& y >= this->coordinates.y && y <= this->coordinates.y + this->height)
		return 1;
	return 0;
}

void Button::draw() {
	//get mau cua khung hinh chung
	int c = getcolor();
	//tao nut
	//tao mau cho nut
	setfillstyle(this->pattern, this->bColor);
	bar(this->coordinates.x, this->coordinates.y, this->coordinates.x + this->width, this->coordinates.y + this->height);
	rectangle(this->coordinates.x, this->coordinates.y, this->coordinates.x + this->width, this->coordinates.y + this->height);
	//tao mau chu
	setcolor(this->tColor);
	//in noi dung cua nut ra nut
	//settextstyle(3, 0, 1);
	outtextxy(this->coordinates.x + (this->width - textwidth(this->name)) / 2, this->coordinates.y + (this->height - textheight(this->name)) / 2, this->name);
	//khoi phuc lai mau ban dau khi thoat tao nut
	setcolor(c);
	setfillstyle(0, c);
}

void Button::init(short x, short y, short height, short width, short tColor, short bColor, short pattern, char* content) {
	// ham nay de khoi tao nhung thong so cua mot nut
	this->coordinates.x = x;
	this->coordinates.y = y;
	this->height = height;
	this->width = width;
	this->tColor = tColor;
	this->bColor = bColor;
	this->name = content;
	this->pattern = pattern;
}

void Button::highLight() {
	//Voi ham nay chung ta se lay mau vang la mau chu va mau xanh dam la mau nen lam mau mac dinh
	Button highLight;
	highLight = *this;
	highLight.tColor = YELLOW;
	highLight.bColor = BLUE;
	highLight.draw();
	
}

void Button::highLight(int tColor, int bColor) {
	//Voi ham nay mau do nguoi lap trinh chon
	Button highLight;
	highLight.init(this->coordinates.x, this->coordinates.y, this->height, this->width, tColor, bColor, this->pattern, this->name);
	highLight.draw();
}

void Button::normal() {
	this->draw();
}

bool Button::isHover() {
	//ham mousex(), mousey() de lay toa do chuot trong cua so ta dang thao tac
	int x = mousex(), y = mousey();
	//neu con tro chuot nam trong pham vi hinh chu nhat cua nut thi duoc tinh la 1 hover
	if (x >= this->coordinates.x && x <= this->coordinates.x + this->width &&
		y >= this->coordinates.y && y <= this->coordinates.y + this->height)
		return 1;
	return 0;
}

void setTaskBarButtons() {
	int margin = 5, 
		width = (400 - margin * 4) / 3,
		height = 40;
	int xM, yM, xH, yH, xF, yF;
	xM = 15 + margin, yM = 15 + margin;
	xH = xM + margin + width, yH = yM;
	xF = xH + margin + width, yF = yH;
	menuBar.init(xM, yM, height, width, YELLOW, LIGHTBLUE, 9, "MENU");
	helpBar.init(xH, yH, height, width, YELLOW, LIGHTBLUE, 9, "HELP");
	fileBar.init(xF, yF, height, width, YELLOW, LIGHTBLUE, 9, "FILE");
}

void drawTaskBarButtons() {
	menuBar.draw();
	helpBar.draw();
	fileBar.draw();
}

void helpBox(char *helpStr) {
	Button helpBoxFrame;
	helpBoxFrame.init(20, 60, 225, 315, YELLOW, BLACK, 1, "");
		
}

void taskBar() {
	int option, ad;
	drawTaskBarButtons();
	if (menuBar.isHover()) {//thanh menu bar thi se hien thi ra danh sach cac cong cu o duoi
		//menuBar.highLight();
		option = menuTools();
		switch (option) {
			case 1: {
				outtextxy(340, 15, "Canh cau");
				break;
			}
			case 2: {
				outtextxy(340, 15, "Dinh tru");
				break;
			}
			case 3: {
				outtextxy(340, 15, "Thanh phan lien thong");
				break;
			}
			case 4: {
				outtextxy(340, 15, "DFS");
				break;
			}
			case 5: {
				outtextxy(340, 15, "Euler");
				break;
			}
			case 6: {
				outtextxy(340, 15, "Dinh that");
				break;
			}
			case 7: {
				outtextxy(340, 15, "Tim duong di ngan nhat");
				break;
			}
			case 8: {
				outtextxy(340, 15, "BFS");
				break;
			}
			case 9: {
				outtextxy(340, 15, "Topo sort");
				break;
			}
			case 10: {
				outtextxy(340, 15, "Hamliton");
				break;
			}
			default:
				break;
			}
		}
	else if (helpBar.isHover()) {
		helpBar.highLight();
		option = helpTools();
		switch (option) {
			case 1: {
				outtextxy(340, 15, "Cach them dinh");
				helpBox(helpStr[0]);				
				break;
			}
			case 2: {
				outtextxy(340, 15, "Cach them cung");
				break;
			}
			case 3: {
				outtextxy(340, 15, "Cach sua dinh");
				break;
			}
			case 4: {
				outtextxy(340, 15, "Cach sua cung");
				break;
			}
			case 5: {
				outtextxy(340, 15, "Cach xoa dinh");
				break;
			}
			case 6: {
				outtextxy(340, 15, "Cach xoa cung");
				break;
			}
			case 7: {
				outtextxy(340, 15, "Cach di chuyen dinh");
				break;
					}
			case 8: {
				outtextxy(340, 15, "Cach di chuyen cung");
				break;
					}
			default: 
				break;
		}
	}
	else if (fileBar.isHover()) {
		fileBar.highLight();
		option = fileTools();
		switch(option) {
			case 1: {
				outtextxy(340, 15, "Mo file");
				break;
			}
			case 2: {
				outtextxy(340, 15, "Luu file");
				break;
			}
			case 3: {
				outtextxy(340, 15, "Xoa do thi trong file");
				break;
			}
			case 4: {
				bool confirm = drawYesNoBar("Ban co chac muon xoa tat ca?");
				if (confirm) 
					clearAllVertices();			
				break;
			}
		}
	}
}

int helpTools() {
	const short itemsAmount = 8;
	int margin = 5,
		height = 40,
		width = (400 - 3 * margin) / 2;
	int x0 = 15,
		y0 = 15 + height + 2 * margin;
	Button helpTools[8], helpToolsHoverBar /*khung de xu ly hover*/;
	helpToolsHoverBar.init(x0 + margin, y0 - margin, (height + margin) * itemsAmount / 2, 2 * width, BLACK, BLACK, 1, "");
	helpTools[0].name = "Cach them dinh";
	helpTools[1].name = "Cach them cung";
	helpTools[2].name = "Cach sua dinh";
	helpTools[3].name = "Cach sua cung";
	helpTools[4].name = "Cach xoa dinh";
	helpTools[5].name = "Cach xoa cung";
	helpTools[6].name = "Cach di chuyen dinh";
	helpTools[7].name = "Cach di chuyen cung";
	for (int i = 0; i < itemsAmount; i++) {
		helpTools[i].pattern = 1;
		helpTools[i].width = width;
		helpTools[i].height = 40;
		helpTools[i].bColor = BLACK;
		helpTools[i].tColor = YELLOW;
		if (i % 2 == 0) {
			helpTools[i].coordinates.x = x0 + margin;
			helpTools[i].coordinates.y = y0;
			helpTools[i + 1].coordinates.y = y0;
			y0 += (height + margin); 
		} else {
			helpTools[i].coordinates.x = x0 + width + 2 * margin; 
		}
	}
	for (int i = 0; i < itemsAmount; i++) {
		helpTools[i].draw();
	}
	int page = 0;
	while (true) {
		delay(10);
		setactivepage(page);
		setvisualpage(1- page);
		taskBarFrame.draw();
		drawTaskBarButtons();
		drawAllEdges();
		helpBar.highLight();
		if (helpBar.isHover() || helpToolsHoverBar.isHover()) {
			int x, y;
			getmouseclick(WM_LBUTTONDOWN, x, y);
			for (int i = 0; i < itemsAmount; i++) {
				if (x >= helpTools[i].coordinates.x && x <= helpTools[i].coordinates.x + helpTools[i].width 
				&& y >= helpTools[i].coordinates.y && y <= helpTools[i].coordinates.y + helpTools[i].height)
					return i + 1;
				if (helpTools[i].isHover())
					helpTools[i].highLight();
				else
					helpTools[i].normal();
			}
		}
		else
			break;
		page = 1 - page;
	}
	return -1;
}

int menuTools() {
	const short itemsAmount = 10;
	int margin = 5,
		height = 40;
	Button menuTools[10], menuToolsHoverBar/*khung de xu ly hover*/;
	menuToolsHoverBar.init(20, 60, 225, 315, BLACK, BLACK, 1, "");//Nut gia de xu ly hover
	menuTools[0].name = "Canh cau";
	menuTools[1].name = "Dinh tru";
	menuTools[2].name = "Thanh phan lien thong";
	menuTools[3].name = "DFS";
	menuTools[4].name = "Euler";
	menuTools[5].name = "Dinh that";
	menuTools[6].name = "Tim duong di ngan nhat";
	menuTools[7].name = "BFS";
	menuTools[8].name = "Topo sort";
	menuTools[9].name = "Hamliton";
	int y0 = 65, i;
			//Cap nut dau tien se co toa do nam duoi nut menuBar (y0 = 65)
	//Vong for duoi day se tao cac nut sap xep xen ke
	//Chi ap dung voi danh sach tools co so luong chan (cu the ta cho la 10 items)
	for (i = 0; i < itemsAmount; i++) {
		//Cai mau nen cho cac nut menu tool trong hop thoai menu tools
		menuTools[i].bColor = BLACK;
		//Cai mau chu
		menuTools[i].tColor = YELLOW;
		menuTools[i].height = height;
		menuTools[i].pattern = 1;
		//Cac cap nut (0 1), (2 3), (4 5), (6 7), (8 9) se co chung toa do y
		//Cac nut 0 2 4 6 8 se co chung toa do x
		//Cac nut 0 1 4 5 8 9 se co chung chieu rong 
		//Cac nut 2 6 se co chung chieu rong
		//Cac nut 3 7 se co chung chieu rong
		menuTools[i].coordinates.y = y0;
		if (i % 2 == 0) {
			//Cac nut 0 2 4 6 8 se co chung toa do x
			menuTools[i].coordinates.x = 15 + margin;
			//menuTools[i + 1].coordinates.y = y0;
		} 
		else 
			y0 += (height + margin);
			//Cap nut tiep theo co toa do bang cap nut truoc cong them 45 
			
		if (i % 4 == 0 || i % 4 == 1) {
			menuTools[i].width = (400 - 3 * margin) / 2;
		} 
		if (i % 4 == 1) {
			//Toa do x cua cac nut 1 5 9 la 179
			menuTools[i].coordinates.x = 15 + 2 * margin + (400 - 3 * margin) / 2;
		}
		if (i % 4 == 2) { 
			//Toa do x cua cac nut 3 7 la 227
			menuTools[i + 1].coordinates.x = 15 + 2 * margin + 2 * (400 - 3 * margin) / 3;
			//Chieu rong cua no la 103
			menuTools[i + 1].width = (400 - 3 * margin) / 3;
			//Chieu rong cua nut 2 6 la 200
			menuTools[i].width = 2 * (400 - 3 * margin) / 3;
			
		}
	}
	for (i = 0; i < itemsAmount; i++)
		//ve cac nut ra man hinh
		menuTools[i].draw();
	int page = 0;
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		delay(10);
		taskBarFrame.draw();
		drawAllEdges();
		drawTaskBarButtons();
//		drawAllEdges();
		menuBar.highLight();
		//Neu con tro chuot dang nam trong pham vi cua thanh menu 
		//hoac no dang nam trong pham vi o chua cac cong cu cua thanh menu thi moi thao tac
		//nguoc lai thi thoat vong lap
		if (menuToolsHoverBar.isHover() || menuBar.isHover()) {
			int x, y;
			//xu ly su kien chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			for (i = 0; i < itemsAmount; i++) {
				if (menuTools[i].isHover())
					//neu di chuot vao mot trong cac menu tools thi se high light dong do
					menuTools[i].highLight();
				else
					menuTools[i].normal();
				//neu click chuot trai vao mot trong so cac cong cu cua o chua menu tools 
				//thi se tra ve gia tri de xu ly cac ham sau nay (DFS, BFS,...)
				if (x >= menuTools[i].coordinates.x && x <= menuTools[i].coordinates.x + menuTools[i].width
				&& y >= menuTools[i].coordinates.y && y <= menuTools[i].coordinates.y + menuTools[i].height)
					return i + 1;
			}
		}
		else 
			break;	
		page = 1 - page;
	}
	return -1;
}

int fileTools() {
	const short itemsAmount = 4;
	int margin = 5,
		height = 40, 
		width = 400 - 2 * margin;
	int y0 = 15 + height + 2 * margin,
		x0 = 15;
	Button fileTools[4], fileToolsHoverBar/*khung xử lý hover*/;
	fileToolsHoverBar.init(x0 + margin, y0 - margin, itemsAmount * (height + margin), width, BLACK, BLACK, 1, "");
	fileTools[0].name = "Mo file";
	fileTools[1].name = "Luu file";
	fileTools[2].name = "Xoa do thi trong file";
	fileTools[3].name = "Xoa do thi tren man hinh";
	for (int i = 0; i < itemsAmount; i++) {
		fileTools[i].tColor = YELLOW;
		fileTools[i].bColor = BLACK;
		fileTools[i].pattern = 1;
		fileTools[i].coordinates.x = x0 + margin;
		fileTools[i].coordinates.y = y0;
		y0 += (height + margin);
		fileTools[i].width = width;
		fileTools[i].height = height;
	}
	for (int i = 0; i < itemsAmount; i++)
		fileTools[i].draw();
	int page = 0;
	while (true) {
		delay(10);
		setactivepage(page);
		setvisualpage(1 - page);
		taskBarFrame.draw();
		drawTaskBarButtons();
		drawAllEdges();
		fileBar.highLight();
		if (fileToolsHoverBar.isHover() || fileBar.isHover()) {
			int x, y;
			getmouseclick(WM_LBUTTONDOWN, x, y);
			for (int i = 0; i < itemsAmount; i++) {
				if (fileTools[i].isHover())
				//neu thanh file tools nao duoc chuot do nguoi dung di chuyen toi thi se duoc to sang
					fileTools[i].highLight();
				else 
					fileTools[i].normal();
				if (x >= fileTools[i].coordinates.x && x <= fileTools[i].coordinates.x + fileTools[i].width 
				&& y >= fileTools[i].coordinates.x && y <= fileTools[i].coordinates.y + fileTools[i].height)
					return i + 1;
			}
		}
		else 
			break;
		page = 1 - page;
	}
	return -1;
}

void setFrame() {
	//Khoi tao thanh tac vu gom co nut menu, nut help, nut file va mot so thao tac khac
	taskBarFrame.init(15, 15, 275, 400, 0, 3, 1, "");// width cu = 320
	//Khoi tao cua so thao tac cac tac vu nhu tao dinh, them dinh, xoa dinh, xoa canh,...
	vertexTaskBarFrame.init(420, 15, 689, 844, 0, 3, 1, "");
	//Khoi tai khung cua ma tran ke
	adjacencyMatrixFrame.init(15, 295, 409, 400, 0, 3, 1, "");
	//Khoi tao khung hien thi dinh va canh
	pointBarFrame.init(425, 20, 500, 834, 0, BLACK , 1, ""); 
}

void drawFrame() {
	//Ve khung hien thi
	taskBarFrame.draw();
	vertexTaskBarFrame.draw();
	taskBarFrame.draw();
	adjacencyMatrixFrame.draw();
	pointBarFrame.draw();
}

void Vertex::create() {
	int x, y;
	if (ismouseclick(WM_LBUTTONDBLCLK)) {
		//Neu co click double chuot trai
		getmouseclick(WM_LBUTTONDBLCLK, x, y);
		//Neu no nam trong pham vi cua bang hien thi dinh thi moi cho tao dinh
		if (x >= 425 + RADIUS && x <= 1259 - RADIUS
		&& y >= 20 + RADIUS && y <= 520 - RADIUS) {
			for (int i = 0; i < n; i++) {
				int x0 = vertices[i].coordinates.x;
				int y0 = vertices[i].coordinates.y;
				if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= 4 * RADIUS * RADIUS)
					return;
			}
			this->coordinates.x = x;
			this->coordinates.y = y;
			circle(x, y, RADIUS);
			this->createName();
		}
	}
}

void Vertex::createName() {
	Button frame, finishButton, cancelButton, enterNameBar;
	int margin = 5;
	int height = 275 - 3 * margin - 40;
	int width = 400 - 2 * margin;
	int x, y;
	this->name = new char[3];
	char name[3] = ""; 
	char request[] = "Nhap ten dinh";
	frame.init(15 + margin, 15 + 2 * margin + 40, height, width, YELLOW, DARKGRAY, 1, "");
	finishButton.init(15 + 2 * margin, 275 - margin - 30, 40, (width - 3 * margin) / 2, YELLOW, BLACK, 9, "HOAN THANH");
	cancelButton.init(15 + 3 * margin + (width - 3 * margin) / 2,275 - margin - 30, 40, (width - 3 * margin) / 2, YELLOW, BLACK, 9, "HUY");
	enterNameBar.init(15 + 2 * margin, 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50, 40, (width - 2 * margin), YELLOW, BLACK, 9, "");
	int page = 0;
	int i = 0; 
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		delay(50);
		setfillstyle(10, GREEN);
		bar (1, 1, 1279, 719);
		drawFrame();
		drawTaskBarButtons();
		drawVertices();
		drawMatrix();
		frame.draw();
		finishButton.draw();
		cancelButton.draw();
		enterNameBar.draw();
		drawAddVertex(this->coordinates.x, this->coordinates.y);//ve dau vong tron co dau cong
		if (ismouseclick(WM_LBUTTONDOWN))
			getmouseclick(WM_LBUTTONDOWN, x, y);
		if (ismouseclick(WM_LBUTTONDBLCLK))// neu co double click chuot trai khi dang tao ten thi phai xoa di
											//de tranh truong hop sau khi tao ten thi tao luon dinh moi
			clearmouseclick(WM_LBUTTONDBLCLK);
		if (ismouseclick(WM_RBUTTONDOWN))//neu co click chuot phai khi dang tao ten thi phai xoa di 
										//de tranh truong hop sau khi tao ten thi mo thanh edit dinh
			clearmouseclick(WM_RBUTTONDOWN);
		if (strcmp(name, "") != 0 && !isNamesake(name)//neu ten khong bi trong va ten khong bi trung voi cac dinh khac thi se duoc nhan enter
		&& x >= finishButton.coordinates.x && x <= finishButton.coordinates.x + finishButton.width
		&& y >= finishButton.coordinates.y && y <= finishButton.coordinates.y + finishButton.height)
		//xu ly click chuot trai vao o hoan thanh
			break;
		if (x >= cancelButton.coordinates.x && x <= cancelButton.coordinates.x + cancelButton.width
		&& y >= cancelButton.coordinates.y && y <= cancelButton.coordinates.y + cancelButton.height) {
			//neu chuot trai co click vao o huy thi ket thuc ham
			this->defaultVtex();
			return;
		}
		if (strcmp(name, "") == 0) {
			outtextxy(15 + (400 - width) / 2 + (width - textwidth(request)) / 2, 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50 + (40 - textheight(request)) / 2, request);
			int x0 = this->coordinates.x, y0 = this->coordinates.y;
			line(x0, y0, x0 - RADIUS + 5, y0);
			line(x0, y0, x0 + RADIUS - 5, y0);
			line(x0, y0, x0, y0 + RADIUS - 5);
			line(x0, y0, x0, y0 - RADIUS + 5);
		}
		if (kbhit()) {
			char key = getch();
			if ((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z')) {
				//Neu phim ta nhap la chu cai thi moi them vao chuoi
				if (i < 2) {
					//Neu chieu dai cua chuoi da day thi khong cho them vao chuoi
					name[i] = key;
					i++;//vi tri se duoc nhay len mot don vi sau khi them mot ky tu vao chuoi
				}
			}
			if (i > 2)
				i = 2;
			if (key == 8) {
				strnDel(name, i - 1, 1);//xoa ki tu co vi tri sau cung cua chuoi
				i--;//vi tri se duoc giam xuong 1 don vi
			}
			if (i < 0)
				i = 0;
			if (strcmp(name, "") != 0 && key == 13 && !isNamesake(name)) {
				break;
			}
			if ((strcmp(name, "") == 0 && key == 13)) {
				frame.highLight(WHITE, RED);
				enterNameBar.draw();
				finishButton.draw();
				cancelButton.draw();
				delay(50);
			}
			if (isNamesake(name)) {
				for (int i = 0; i < n; i++)
					if (stricmp(name, vertices[i].name) == 0) {
						vertices[i].highLight(WHITE, RED);
						delay(50);
					}
			}
			//cout << i << endl;
		}
		upper(name);
		outtextxy(15 + (400 - width) / 2 + (width - textwidth(name)) / 2, 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50 + (40 - textheight(name)) / 2, name);
		outtextxy(this->coordinates.x - textwidth(name) / 2, this->coordinates.y - textheight(name) / 2, name);
		if (finishButton.isHover())
			finishButton.highLight();
		if (cancelButton.isHover())
			cancelButton.highLight();
		page = 1 - page;
	}
	
//	this->name = name;
	strcpy(this->name, name);
}

void Vertex::draw() {
	int x = mousex(), y = mousey();
	if (this->coordinates.x == -1 && this->coordinates.y == -1)
		return;
	char c = getcolor();
	setfillstyle(1, BLACK);
	circle(this->coordinates.x, this->coordinates.y, RADIUS);
	//pieslice(this->coordinates.x, this->coordinates.y, 0, 0, RADIUS);
	setcolor(YELLOW);
	outtextxy(this->coordinates.x - textwidth(this->name) / 2, this->coordinates.y - textheight(this->name) / 2, this->name);
	if (this->isHover())
		this->highLight();
	setcolor(c);
	setfillstyle(1, c);
	
}

void Vertex::highLight() {
	char c = getcolor();
	setfillstyle(1, BLUE);
	pieslice(this->coordinates.x, this->coordinates.y, 0, 0, RADIUS);
	setcolor(YELLOW);
	outtextxy(this->coordinates.x - textwidth(this->name) / 2, this->coordinates.y - textheight(this->name) / 2, this->name);
	setcolor(c);
	setfillstyle(1, c);
}

void Vertex::highLight(int tColor, int bColor) {
	char c = getcolor();
	setfillstyle(1, bColor);
	pieslice(this->coordinates.x, this->coordinates.y, 0, 0, RADIUS);
	setcolor(tColor);
	outtextxy(this->coordinates.x - textwidth(this->name) / 2, this->coordinates.y - textheight(this->name) / 2, this->name);
	setcolor(c);
	setfillstyle(1, c);	
}

bool Vertex::isDefaultVtex() {
	if (this->coordinates.x == -1 && this->coordinates.y == -1)
		return 1;
	return 0;
}

bool Vertex::isHover() {
	int x = mousex(), y = mousey();
	if ((x - this->coordinates.x) * (x - this->coordinates.x) + (y - this->coordinates.y) * (y - this->coordinates.y) <= RADIUS * RADIUS)
		// tam I(a,b) phuong trinh (x - a)2 + (y - b)2 <= r2
		return 1;
	return 0;
}

bool Vertex::isClickLMButton() {
	int x, y;
	getmouseclick(WM_LBUTTONDOWN, x, y);
	if ((this->coordinates.x - x) * (this->coordinates.x - x) 
	+ (this->coordinates.y - y) * (this->coordinates.y - y) <= RADIUS * RADIUS)
		return 1;
	return 0;
}


void Vertex::defaultVtex() {
	this->coordinates.x = -1;
	this->coordinates.y = -1;
}

void drawVertices() {
	int x, y;
	for (int i = 0; i < n; i++) 
		vertices[i].draw();
}

void initDefaultVertices() {
	for (int i = 0; i < n; i++) {
		vertices[i].defaultVtex();
	}
}

void loadFileStartUp() {
	ifstream input ("filesInProgram//startUpFile.txt");
	if (input.is_open()) {
		input >> n;
		for (int i = 0; i < n; i++) {
			input >> vertices[i].coordinates.x >> vertices[i].coordinates.y;
			vertices[i].name = new char[3];
			input >> vertices[i].name;
		}
		for (int i = 0; i < n; i++) 
			for (int j = 0; j < n; j++)
				input >> G[i][j];
	} else {
		FILE * newFile = fopen("filesInProgram//startUpFile.txt", "a");
		fprintf(newFile, "%d", 0);
		fclose(newFile);
	}
 
	input.close();
}

void saveFileStartUp() {
	fstream output;
	output.open("filesInProgram//startUpFile.txt", ios::out);
	output << n << endl;
	for (int i = 0; i < n; i++) {
		output << vertices[i].coordinates.x << " "
		 << vertices[i].coordinates.y << " "
		 << vertices[i].name << endl;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			output << G[i][j] << " ";
		}
		output << endl;
	}
	output.close();
}

void addVertexToList(Vertex vtex) {
	if (n < MAX && vertices[n].isDefaultVtex() && !vtex.isDefaultVtex()) {
		vertices[n] = vtex;
		for (int i = 0; i <= n; i++) {
			G[n][i] = 0;
			G[i][n] = 0;
		}
		n++;
		saveFileStartUp();
	}
}

void clearAllVertices() {
	n = 0;
	for (int i = 0; i < MAX; i++) {
		vertices[i].defaultVtex();
	}
	saveFileStartUp();
}

bool drawYesNoBar(char *question) {
	Button frame, yesButton, noButton;
	int height = 100;
	int width = 200;
	int margin = 5;
	int x, y;
	frame.init(425 + (834 - width) / 2 , 20 + (500 - height) / 2, height, width, YELLOW, BLACK, 1, "");
	yesButton.init(425 + (834 - width) / 2 + margin, 20 + (500 - height) / 2 + (height - 40 - margin), 40, (width - 3 * margin) / 2, YELLOW, BLACK, 9, "CO");
	noButton.init(425 + (834 - width) / 2 + margin * 2 + (width - 3 * margin) / 2, 20 + (500 - height) / 2 + (height - 40 - margin), 40, (width - 3 * margin) / 2, YELLOW, BLACK, 9, "KHONG");
	int page = 0;
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		setfillstyle(10, GREEN);
		bar(1, 1, 1279, 719);
		delay(10);
		drawFrame();
		drawTaskBarButtons();
		drawVertices();
		drawMatrix();
		frame.draw();
		noButton.draw();
		yesButton.draw();
		if (ismouseclick(WM_RBUTTONDOWN))//neu co click chuot phai vao man hinh thi phai xoa 
										// de no khong mo hop thoai edit dinh khi ta vo tinh click chuot phai vao dinh bat ky
			clearmouseclick(WM_RBUTTONDOWN);
		if (ismouseclick(WM_LBUTTONDBLCLK))//neu co double click chuot trai vao man hinh thi phai xoa no vi neu khi thoat 
											//ham nay co the tao dinh moi ngay tuc thi
			clearmouseclick(WM_LBUTTONDBLCLK);
		outtextxy(425 + (834 - width) / 2 + (width - textwidth(question)) / 2, 20 + (500 - height) / 2 + 10, question);
		if (kbhit()) {
			char key = getch();
			if (key == 13) {
				return 1;	
			}
		}
		if (yesButton.isHover())//neu chuot di chuyen toi thanh yes thanh yes se sang
			yesButton.highLight();
		else if (noButton.isHover())//neu chuot di chuyen toi thanh no thanh no se sang
			noButton.highLight();
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (x >= yesButton.coordinates.x && x <= yesButton.coordinates.x + yesButton.width
			&& y >= yesButton.coordinates.y && y <= yesButton.coordinates.y + yesButton.height)
				return 1;
			if (x >= noButton.coordinates.x && x <= noButton.coordinates.x + noButton.width
			&& y >= noButton.coordinates.y && y <= noButton.coordinates.y + noButton.height)
				return 0;
		}
 		page = 1 - page;
	}
	
}

bool isClickOtherVertex(Vertex vtex) {
	int x = vtex.coordinates.x, y = vtex.coordinates.y;
	for (int i = 0; i < n; i++) 
		if ((x - vertices[i].coordinates.x) * (x - vertices[i].coordinates.x) + (y - vertices[i].coordinates.y) * (y - vertices[i].coordinates.y) <= 4 * RADIUS * RADIUS)
		// tam I(a,b) phuong trinh (x - a)2 + (y - b)2 <= r2)
			return 1;
	return 0;
}

bool isEmptyVertex() {
	if (n == 0)
		return 1;
	return 0;
}
