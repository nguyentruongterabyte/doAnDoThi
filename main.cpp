#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
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
	void createVtex();
	void drawVtex();
	void createVtexName();
	void highLight();
	void defaultVtex();
	bool isDefaultVtex();
};

struct Button {
	Point coordinates;
	char* name;
	short height;
	short width;
	short tColor;
	short bColor;
	short pattern;//cac kieu gach cheo, cham bi,.. trong nut
	
	void initButton(short x, short y, short height, short width, short tColor, short bColor, short pattern, char* content);//x, y, height, width, content
	void drawButton();//Ve nut
	void highLight();//To sang nut (doi mau theo kieu mac dinh)
	void normal();//Dua nut tro ve hinh dang ban dau
	void highLight(int tColor, int bColor);//To sang nut voi mau chu va mau nen 
	bool isHoverButton();//Kiem tra xem ta co di chuyen chuot toi nut do hay khong
	bool isClickLMButton();//Kiem tra xem chuot trai co click vao o hay khong
};

int n = MAX;
Vertex vertices[MAX];

Button menuBar/*thanh menu*/, 
		helpBar/*thanh help*/,
		fileBar/*thanh file*/,
		adjacencyMatrixFrame/*khung hien thi ma tran ke*/, 
		pointBarFrame/*khung hien thi dinh va canh*/,
		taskBarFrame/*khung hien thi thanh tac vu gom menu, file va help*/,
		vertexTaskBarFrame/*khung hien thi thanh tac vu */;

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


int main() {
	
	int page = 0;
	initwindow(1280, 720);
	Vertex vtex;
	setTaskBarButtons();
	setFrame();
		
	initDefaultVertices();
	loadFileStartUp();
	
//	cout << n << endl;
//	for (int i = 0; i < n; i++) {
//		cout << vertices[i].coordinates.x << " " 
//		<< vertices[i].coordinates.y << " "
//		<< vertices[i].name << endl;
//	}
	while (true) {
		
		setactivepage(page);
		setvisualpage(1 - page);
		delay(1);
		vtex.defaultVtex();
		setfillstyle(10, GREEN);
		bar(1, 1, 1279, 719);
		drawFrame();
		vtex.createVtex();
		addVertexToList(vtex);
		//vtex.createVertex();
		//vtex.drawVertex();
		drawVertices();
		taskBar();
		//drawYesNoBar();
	
		
		page = 1 - page;
	}
//	//menuTools();
//	getch();
//	closegraph();
}


bool Button::isClickLMButton() {
	int x, y;
	getmouseclick(WM_LBUTTONDOWN, x, y);
	if (x >= this->coordinates.x && x <= this->coordinates.x + this->width
	&& y >= this->coordinates.y && y <= this->coordinates.y + this->height)
		return 1;
	return 0;
}

void Button::drawButton() {
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

void Button::initButton(short x, short y, short height, short width, short tColor, short bColor, short pattern, char* content) {
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
	highLight.drawButton();
	
}

void Button::highLight(int tColor, int bColor) {
	//Voi ham nay mau do nguoi lap trinh chon
	Button highLight;
	highLight.initButton(this->coordinates.x, this->coordinates.y, this->height, this->width, tColor, bColor, this->pattern, this->name);
	highLight.drawButton();
}

void Button::normal() {
	this->drawButton();
}

bool Button::isHoverButton() {
	//ham mousex(), mousey() de lay toa do chuot trong cua so ta dang thao tac
	int x = mousex(), y = mousey();
	//neu con tro chuot nam trong pham vi hinh chu nhat cua nut thi duoc tinh la 1 hover
	if (x >= this->coordinates.x && x <= this->coordinates.x + this->width &&
		y >= this->coordinates.y && y <= this->coordinates.y + this->height)
		return 1;
	return 0;
}

void setTaskBarButtons() {
	menuBar.initButton(20, 20, 40, 100, YELLOW, LIGHTBLUE, 9, "MENU");
	helpBar.initButton(125, 20, 40, 100, YELLOW, LIGHTBLUE, 9, "HELP");
	fileBar.initButton(230, 20, 40, 100, YELLOW, LIGHTBLUE, 9, "FILE");
}

void drawTaskBarButtons() {
	menuBar.drawButton();
	helpBar.drawButton();
	fileBar.drawButton();
}

void helpBox(char *helpStr) {
	Button helpBoxFrame;
	helpBoxFrame.initButton(20, 60, 225, 315, YELLOW, BLACK, 1, "");
		
}

void taskBar() {
	int option;
	drawTaskBarButtons();
	if (menuBar.isHoverButton()) {//thanh menu bar thi se hien thi ra danh sach cac cong cu o duoi
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
	else if (helpBar.isHoverButton()) {
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
	else if (fileBar.isHoverButton()) {
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
				bool confirm = drawYesNoBar("Ban co muon \n xoa tat ca?");
				if (confirm)
					clearAllVertices();
				break;
			}
		}
	}
}

int helpTools() {
	const short itemsAmount = 8;
	Button helpTools[8], helpToolsHoverBar /*khung de xu ly hover*/;
	helpToolsHoverBar.initButton(20, 60, 40 * 4 + 20, 320, BLACK, BLACK, 1, "");
	helpTools[0].name = "Cach them dinh";
	helpTools[1].name = "Cach them cung";
	helpTools[2].name = "Cach sua dinh";
	helpTools[3].name = "Cach sua cung";
	helpTools[4].name = "Cach xoa dinh";
	helpTools[5].name = "Cach xoa cung";
	helpTools[6].name = "Cach di chuyen dinh";
	helpTools[7].name = "Cach di chuyen cung";
	int y0 = 65;
	for (int i = 0; i < itemsAmount; i++) {
		helpTools[i].pattern = 1;
		helpTools[i].width = 151;
		helpTools[i].height = 40;
		helpTools[i].bColor = BLACK;
		helpTools[i].tColor = YELLOW;
		if (i % 2 == 0) {
			helpTools[i].coordinates.x = 20;
			helpTools[i].coordinates.y = y0;
			helpTools[i + 1].coordinates.y = y0;
			y0 += 45; 
		} else {
			helpTools[i].coordinates.x = 178; 
		}
	}
	for (int i = 0; i < itemsAmount; i++) {
		helpTools[i].drawButton();
	}
	int page = 0;
	while (true) {
		delay(10);
		setactivepage(page);
		setvisualpage(1- page);
		taskBarFrame.drawButton();
		drawTaskBarButtons();
		helpBar.highLight();
		if (helpBar.isHoverButton() || helpToolsHoverBar.isHoverButton()) {
			int x, y;
			getmouseclick(WM_LBUTTONDOWN, x, y);
			for (int i = 0; i < itemsAmount; i++) {
				if (x >= helpTools[i].coordinates.x && x <= helpTools[i].coordinates.x + helpTools[i].width 
				&& y >= helpTools[i].coordinates.y && y <= helpTools[i].coordinates.y + helpTools[i].height)
					return i + 1;
				if (helpTools[i].isHoverButton())
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
	Button menuTools[10], menuToolsHoverBar/*khung de xu ly hover*/;
	menuToolsHoverBar.initButton(20, 60, 225, 315, BLACK, BLACK, 1, "");//Nut gia de xu ly hover
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
	//Vong for duoi day se tao cac nut sap xep xen ke
	//Chi ap dung voi danh sach tools co so luong chan (cu the ta cho la 10 items)
	for (i = 0; i < itemsAmount; i++) {
		//Cai mau nen cho cac nut menu tool trong hop thoai menu tools
		menuTools[i].bColor = BLACK;
		//Cai mau chu
		menuTools[i].tColor = YELLOW;
		menuTools[i].height = 40;
		menuTools[i].pattern = 1;
		//Cac cap nut (0 1), (2 3), (4 5), (6 7), (8 9) se co chung toa do y
		//Cac nut 0 2 4 6 8 se co chung toa do x
		//Cac nut 0 1 4 5 8 9 se co chung chieu rong 
		//Cac nut 2 6 se co chung chieu rong
		//Cac nut 3 7 se co chung chieu rong
		if (i % 2 == 0) {
			//Cac nut 0 2 4 6 8 se co chung toa do x
			menuTools[i].coordinates.x = 20;
			//Cap nut dau tien se co toa do nam duoi nut menuBar (y0 = 65)
			//Cap nut tiep theo co toa do bang cap nut truoc cong them 45 
			menuTools[i].coordinates.y = y0;
			menuTools[i + 1].coordinates.y = y0;
			y0 += 45; 
		}
		if (i % 4 == 0 || i % 4 == 1) {
			//Do rong cua cac nut 0 1 4 5 8 9 se la 151
			menuTools[i].width = 151;
		} 
		if (i % 4 == 0) {
			//Toa do x cua cac nut 0 4 8 la 179
			menuTools[i + 1].coordinates.x = 179;
		}
		if (i % 4 == 2) { 
			//Toa do x cua cac nut 3 7 la 227
			menuTools[i + 1].coordinates.x = 227;
			//Chieu rong cua no la 103
			menuTools[i + 1].width = 103;
			//Chieu rong cua nut 2 6 la 200
			menuTools[i].width = 200;
			
		}
	}
	for (i = 0; i < itemsAmount; i++)
		//ve cac nut ra man hinh
		menuTools[i].drawButton();
	int page = 0;
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		delay(10);
		taskBarFrame.drawButton();
		drawTaskBarButtons();
		menuBar.highLight();
		//Neu con tro chuot dang nam trong pham vi cua thanh menu 
		//hoac no dang nam trong pham vi o chua cac cong cu cua thanh menu thi moi thao tac
		//nguoc lai thi thoat vong lap
		if (menuToolsHoverBar.isHoverButton() || menuBar.isHoverButton()) {
			int x, y;
			//xu ly su kien chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			for (i = 0; i < itemsAmount; i++) {
				if (menuTools[i].isHoverButton())
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
	Button fileTools[4], fileToolsHoverBar/*khung xử lý hover*/;
	fileToolsHoverBar.initButton(20, 60, 40 * 4 + 5 * 4, 315, BLACK, BLACK, 1, "");
	int y0 = 65;
	fileTools[0].name = "Mo file";
	fileTools[1].name = "Luu file";
	fileTools[2].name = "Xoa do thi trong file";
	fileTools[3].name = "Xoa do thi tren man hinh";
	for (int i = 0; i < itemsAmount; i++) {
		fileTools[i].tColor = YELLOW;
		fileTools[i].bColor = BLACK;
		fileTools[i].pattern = 1;
		fileTools[i].coordinates.x = 20;
		fileTools[i].coordinates.y = y0;
		y0 += 45;
		fileTools[i].width = 310;
		fileTools[i].height = 40;
	}
	for (int i = 0; i < itemsAmount; i++)
		fileTools[i].drawButton();
	int page = 0;
	while (true) {
		delay(10);
		setactivepage(page);
		setvisualpage(1 - page);
		taskBarFrame.drawButton();
		drawTaskBarButtons();
		fileBar.highLight();
		if (fileToolsHoverBar.isHoverButton() || fileBar.isHoverButton()) {
			int x, y;
			getmouseclick(WM_LBUTTONDOWN, x, y);
			for (int i = 0; i < itemsAmount; i++) {
				if (fileTools[i].isHoverButton())
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
	taskBarFrame.initButton(15, 15, 275, 400, 0, 3, 1, "");// width cu = 320
	//Khoi tao cua so thao tac cac tac vu nhu tao dinh, them dinh, xoa dinh, xoa canh,...
	vertexTaskBarFrame.initButton(420, 15, 689, 844, 0, 3, 1, "");
	//Khoi tai khung cua ma tran ke
	adjacencyMatrixFrame.initButton(15, 295, 409, 400, 0, 3, 1, "");
	//Khoi tao khung hien thi dinh va canh
	pointBarFrame.initButton(425, 20, 500, 834, 0, BLACK , 1, ""); 
}

void drawFrame() {
	//Ve khung hien thi
	taskBarFrame.drawButton();
	vertexTaskBarFrame.drawButton();
	taskBarFrame.drawButton();
	adjacencyMatrixFrame.drawButton();
	pointBarFrame.drawButton();
}

void Vertex::createVtex() {
	
	if (ismouseclick(WM_LBUTTONDOWN)) {
		//Neu co click chuot trai
		getmouseclick(WM_LBUTTONDOWN, this->coordinates.x, this->coordinates.y);
		//Neu no nam trong pham vi cua bang hien thi dinh thi moi cho tao dinh
		if (this->coordinates.x >= 425 + RADIUS && this->coordinates.x <= 1259 - RADIUS
		&& this->coordinates.y >= 20 + RADIUS && this->coordinates.y <= 520 - RADIUS) {
			this->createVtexName();
		}
	}
}

void Vertex::createVtexName() {
	Button nameCreateBar;
	int page = 0; 
	nameCreateBar.initButton(425 + (834 - 200) / 2, 20 + (500 - 200) / 2, 200, 200, YELLOW, BLACK, 1, "Bang tao ten");
	this->name = new char[3];
	this->name = "A";
//	char c = getcolor();
//	
//		
//		pointBarFrame.drawButton();
//		drawVertices();
//		nameCreateBar.drawButton();
//		gets(name);
//	



		
}

void Vertex::drawVtex() {
	int x = mousex(), y = mousey();
	if (this->coordinates.x == -1 && this->coordinates.y == -1)
		return;
	char c = getcolor();
	setfillstyle(1, BLACK);
	circle(this->coordinates.x, this->coordinates.y, RADIUS);
	//pieslice(this->coordinates.x, this->coordinates.y, 0, 0, RADIUS);
	setcolor(YELLOW);
	outtextxy(this->coordinates.x - textwidth(this->name) / 2, this->coordinates.y - textheight(this->name) / 2, this->name);
	if ((x - this->coordinates.x) * (x - this->coordinates.x) + (y - this->coordinates.y) * (y - this->coordinates.y) <= RADIUS * RADIUS)
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

bool Vertex::isDefaultVtex() {
	if (this->coordinates.x == -1 && this->coordinates.y == -1)
		return 1;
	return 0;
}

void Vertex::defaultVtex() {
	this->coordinates.x = -1;
	this->coordinates.y = -1;
}

void drawVertices() {
	for (int i = 0; i < n; i++) 
		vertices[i].drawVtex();
}

void initDefaultVertices() {
	for (int i = 0; i < n; i++) {
		vertices[i].defaultVtex();
	}
}

void loadFileStartUp() {
	ifstream input ("filesInProgram//startUpFile.txt");
 	input >> n;
	for (int i = 0; i < n; i++) {
		input >> vertices[i].coordinates.x >> vertices[i].coordinates.y;
		vertices[i].name = new char[3];
		input >> vertices[i].name;
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
}

void addVertexToList(Vertex vtex) {
	if (n < MAX && vertices[n].isDefaultVtex() && !vtex.isDefaultVtex()) {
		vertices[n] = vtex;
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
	Button nameCreateBar, yesBar, NoBar;
	int height = 100;
	int width = 200;
	int margin = 5;
	nameCreateBar.initButton(425 + (834 - width) / 2 , 20 + (500 - height) / 2, height, width, YELLOW, BLACK, 1, "");
	yesBar.initButton(425 + (834 - width) / 2 + margin, 20 + (500 - height) / 2 + (height - 40 - margin), 40, (width - 3 * margin) / 2, YELLOW, BLACK, 9, "YES");
	
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
		nameCreateBar.drawButton();
		yesBar.drawButton();
		outtextxy(425 + (834 - 200) / 2 + 10, 20 + (500 - 100) / 2 + 10, question);
		if (kbhit()) {
			char key = getch();
			if (key == 13) {
				return 1;	
			}
			
		}
		
		page = 1 - page;
	}

}


