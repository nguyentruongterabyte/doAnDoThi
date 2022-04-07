#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wconversion-null"
#pragma GCC diagnostic ignored "-Wpointer-arith"
#define RADIUS 25
using namespace std;

struct Point {
	int x;
	int y;
};

struct Button {
	Point coordinates;
	char* name;
	short height;
	short width;
	short tColor;
	short bColor;
	short pattern;//các kiểu gạch chéo, chấm bi,.. trong nút
	
	void initButton(short, short, short, short, short, short, short, char*);//x, y, height, width, content
	void drawButton();//Vẽ nút
	void highLight();//Tô sáng nút (đổi màu theo kiểu mặc định)
	void normal();//Đưa nút trở về hình dạng ban đầu
	void highLight(int, int);//Tô sáng nút với màu chữ và màu nền 
	bool isHoverButton();//Kiểm tra xem ta có di chuyển chuột tới nút đó hay không
	bool isClickLMButton();//Kiểm tra xem chuột trái có click vào ô hay không
};

Button menuBar, 
		helpBar,
		fileBar,
		helpToolsHoverBar,
		fileToolsHoverBar,
		menuToolsHoverBar;

void menu();
int menuTools();
int helpTools();
int fileTools();
void setFrame();//cài đặt khung hiển thị
void createVertex(); //tạo đỉnh


int main() {
	int count = 0;
	initwindow(1280, 720);
	setfillstyle(10, GREEN);
	bar(1, 1, 1279, 719);
	setFrame();
	while (true) {
		delay(200);
		menu();
		createVertex();
	}
	//menuTools();
	getch();
	closegraph();
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
	//get màu của khung hình chung
	int c = getcolor();
	//tạo nút
	//tạo màu cho nút
	setfillstyle(this->pattern, this->bColor);
	bar(this->coordinates.x, this->coordinates.y, this->coordinates.x + this->width, this->coordinates.y + this->height);
	rectangle(this->coordinates.x, this->coordinates.y, this->coordinates.x + this->width, this->coordinates.y + this->height);
	//tạo màu chữ
	setcolor(this->tColor);
	//in nội dung của nút ra nút
	outtextxy(this->coordinates.x + (this->width - textwidth(this->name)) / 2, this->coordinates.y + (this->height - textheight(this->name)) / 2, this->name);
	//khôi phục lại màu ban đầu khi thoát tạo nút
	setcolor(c);
	setfillstyle(0, c);
}

void Button::initButton(short x, short y, short height, short width, short tColor, short bColor, short pattern, char* content) {
	// hàm này để khởi tạo những thông số của một nút
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
	//Với hàm này chúng ta sẽ lấy màu vàng là màu chữ và màu xanh đậm là màu nền làm màu mặc định
	Button highLight;
	highLight = *this;
	highLight.tColor = YELLOW;
	highLight.bColor = BLUE;
	highLight.drawButton();
	
}

void Button::highLight(int tColor, int bColor) {
	//Với hàm này màu do người lập trình chọn
	Button highLight;
	highLight.initButton(this->coordinates.x, this->coordinates.y, this->height, this->width, tColor, bColor, this->pattern, this->name);
	highLight.drawButton();
}

void Button::normal() {
	this->drawButton();
}

bool Button::isHoverButton() {
	//hàm mousex(), mousey() để lấy tọa độ chuột trong cửa sổ ta đang thao tác
	int x = mousex(), y = mousey();
	//nếu con trỏ chuột nằm trong phạm vi hình chữ nhật của nút thì được tính là 1 hover
	if (x >= this->coordinates.x && x <= this->coordinates.x + this->width &&
		y >= this->coordinates.y && y <= this->coordinates.y + this->height)
		return 1;
	return 0;
}

void menu() {
	int option,
	x = mousex(), 
	y = mousey();
	Button bannerBarFrame;
	//Khởi tạo khung
	bannerBarFrame.initButton(15, 15, 275, 320, 0, 3, 1, "");
	//Cài đặt thông số cho nút menu, nút help và nút file
	menuBar.initButton(20, 20, 40, 100, YELLOW, LIGHTBLUE, 9, "MENU");
	helpBar.initButton(125, 20, 40, 100, YELLOW, LIGHTBLUE, 9, "HELP");
	fileBar.initButton(230, 20, 40, 100, YELLOW, LIGHTBLUE, 9, "FILE");	
	bannerBarFrame.drawButton();
	menuBar.drawButton();
	helpBar.drawButton();
	fileBar.drawButton();
	if (menuBar.isHoverButton()) {//thanh menu bar thì sẽ hiển thị ra danh sách các công cụ ở dưới
		menuBar.highLight();
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
				outtextxy(340, 15, "Xoa do thi tren man hinh");
				break;
			}
		}
	}
}

int helpTools() {
	const short itemsAmount = 8;
	Button helpTools[8];
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
	while (true) {
		delay(700);
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
	}
	return -1;
}

int menuTools() {
	const short itemsAmount = 10;
	Button menuTools[10];
	menuToolsHoverBar.initButton(20, 60, 225, 315, BLACK, BLACK, 1, "");//Nút giả để xử lý hover
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
	//Vòng for dưới đây sẽ tạo các nút sắp xếp xen kẽ
	//Chỉ áp dụng với danh sách tools có số lượng chẵn (cụ thể ta cho là 10 items)
	for (i = 0; i < itemsAmount; i++) {
		//Cài màu nền cho các nút menu tool trong hộp thoại menu tools
		menuTools[i].bColor = BLACK;
		//Cài màu chữ
		menuTools[i].tColor = YELLOW;
		menuTools[i].height = 40;
		//Cài loại tô vào nút
		menuTools[i].pattern = 1;
		//Các cặp nút (0 1), (2 3), (4 5), (6 7), (8 9) sẽ có chung tọa độ y
		//Các nút 0 2 4 6 8 sẽ có chung tọa độ x
		//Các nút 0 1 4 5 8 9 sẽ có chung chiều rộng
		//Các nút 2 6 sẽ có chung chiều rộng
		//Các nút 3 7 sẽ có chung chiều rộng
		if (i % 2 == 0) {
			//Các nút 0 2 4 6 8 sẽ có chung tọa độ x
			menuTools[i].coordinates.x = 20;
			//Cặp nút đầu tiên sẽ có tọa độ nằm dưới nút menuBar (y0 = 65)
			//Cặp nút tiếp theo có tọa độ bằng cặp nút trước cộng thêm 45 
			menuTools[i].coordinates.y = y0;
			menuTools[i + 1].coordinates.y = y0;
			y0 += 45; 
		}
		if (i % 4 == 0 || i % 4 == 1) {
			//Độ rộng của các nút 0 1 4 5 8 9 sẽ là 151
			menuTools[i].width = 151;
		} 
		if (i % 4 == 0) {
			//Tọa độ x của các nút 0 4 8 là 179
			menuTools[i + 1].coordinates.x = 179;
		}
		if (i % 4 == 2) {
			//Tọa độ x của các nút 3 7 là 227 
			//Chiều rộng của nó là 103
			menuTools[i + 1].coordinates.x = 227;
			menuTools[i + 1].width = 103;
			//Chiều rộng của nút 2 6 là 200
			menuTools[i].width = 200;
			
		}
	}
	for (i = 0; i < itemsAmount; i++)
		//vẽ các nút ra màn hình
		menuTools[i].drawButton();
		
	while (true) {
		delay(200);
		//Nếu con trỏ chuột đang nằm trong phạm vi của thanh menu 
		//hoặc nó đang nằm trong phạm vi ô chứa các công cụ của thanh menu thì mới thao tác
		//ngược lại thì thoát vòng lặp
		if (menuToolsHoverBar.isHoverButton() || menuBar.isHoverButton()) {
			int x, y;
			//xử lý sự kiện chuột trái
			getmouseclick(WM_LBUTTONDOWN, x, y);
			for (i = 0; i < itemsAmount; i++) {
				if (menuTools[i].isHoverButton())
					//nếu di chuột vào một trong các menu tools thì sẽ high light dòng đó
					menuTools[i].highLight();
				else
					menuTools[i].normal();
				//nếu click chuột trái vào một trong số các công cụ của ô chứa menu tools 
				//thì sẽ trả về giá trị để xử lý các hàm sau này (DFS, BFS,...)
				if (x >= menuTools[i].coordinates.x && x <= menuTools[i].coordinates.x + menuTools[i].width
				&& y >= menuTools[i].coordinates.y && y <= menuTools[i].coordinates.y + menuTools[i].height)
					return i + 1;
			}
		}
		else 
			break;	
	}
	return -1;
}

int fileTools() {
	const short itemsAmount = 4;
	Button fileTools[4];
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
	while (true) {
		delay(200);
		if (fileToolsHoverBar.isHoverButton() || fileBar.isHoverButton()) {
			int x, y;
			getmouseclick(WM_LBUTTONDOWN, x, y);
			for (int i = 0; i < itemsAmount; i++) {
				if (fileTools[i].isHoverButton())
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
	}
	return -1;
}

void setFrame() {
	Button bannerBarFrame, taskBarFrame, adjacencyMatrixFrame, pointBarFrame;
	//Khởi tạo thanh tác vụ gồm có nút menu, nút help, nút file và một số thao tác khác
	bannerBarFrame.initButton(15, 15, 275, 400, 0, 3, 1, "");// width cũ = 320
	//Khởi tạo cửa sổ thao tác các tác vụ như tạo đỉnh, thêm đỉnh, xóa đỉnh, xóa cạnh,...
	taskBarFrame.initButton(420, 15, 689, 844, 0, 3, 1, "");
	//Khởi tại khung của ma trận kề
	//Khởi tạo khung hiển thị đỉnh và cạnh
	pointBarFrame.initButton(425, 20, 500, 834, 0, GREEN, 1, ""); 
	
	adjacencyMatrixFrame.initButton(15, 295, 409, 400, 0, 3, 1, "");
	bannerBarFrame.drawButton();
	taskBarFrame.drawButton();
	adjacencyMatrixFrame.drawButton();
	pointBarFrame.drawButton();
}

void createVertex() {

	int x, y;
	char *name = new char[3];
	char c = getcolor();
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (x >= 425 + RADIUS && x <= 1259 - RADIUS
			&& y >= 20 + RADIUS && y <= 520 - RADIUS) {
				setfillstyle(1, 5);
				setcolor(5);
				pieslice(x, y, 0, 0, RADIUS);
			}
		}
		setfillstyle(1, c);
		setcolor(c);
}




