#include <iostream>
#include <graphics.h>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <math.h>
#include <time.h>
#include "include/stack.hpp"
#include "include/queue.hpp"
#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wconversion-null"
#pragma GCC diagnostic ignored "-Wpointer-arith"
#define RADIUS 20
#define MAX 11
using namespace std;

enum key {
	KEY_BACKSPACE = 8,
	KEY_ESC = 27,
	KEY_ENTER = 13
};

enum workingZone {
	W_LEFT = 425,
	W_TOP = 20,
	W_RIGHT = 1259,
	W_BOTTOM = 520
};

struct Point/*cau truc diem*/ {
	int x;
	int y;
};

char *helpStr[] = {
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
	void changeColor(int tColor, int bColor);//doi mau nut
};

int Time;
int n = MAX;
Vertex vertices[MAX];
int G[MAX][MAX];
bool visited[MAX];

Button menuBar/*thanh menu*/, 
		helpBar/*thanh help*/,
		fileBar/*thanh file*/,
		adjacencyMatrixFrame/*khung hien thi ma tran ke*/, 
		pointBarFrame/*khung hien thi dinh va canh*/,
		taskBarFrame/*khung hien thi thanh tac vu gom menu, file va help*/,
		vertexTaskBarFrame/*khung hien thi thanh tac vu */,
		editFrame/*khung hien thi cac cong cu sua ten va xoa dinh*/,
		deleteButton/*Nut xoa dinh*/,
		editNameButton/*Nut sua ten dinh*/,
		addEdgeButton/*Nut tao canh*/,
		ESCButton;

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
void loadFileStartUp();//khi tat chuong trinh, 
					  //file nay se co chuc nang luu lai thong tin dinh canh cho lan chay tiep theo
void saveFileStartUp();//khi tao hay xoa dinh, file nay se co tac dung cap nhat lai nhung gi chung ta thao tac
void addVertexToList(Vertex vtex);//ham nay giup chung ta them mot dinh vua tao vao danh sach dinh
void clearAllVertices();//ham nay cho phep xoa tat ca cac dinh va cung dang hien thi tren man hinh
bool drawYesNoBar(char *question);//ham nay dung de xac nhan truoc khi lam gi do
bool isClickOtherVertex(Vertex vtexs);//kiem tra xem chuot trai co click vao dinh hay khong.
									  // Ham nay su dung de tranh tao dinh de len dinh khac
bool isEmptyVertex();//Kiem tra dinh tren man hinh da co hay chua
void strnDel(char *s, int pos, int count);//ham xoa ki tu trong chuoi
void upper(char *s);//Doi day s thanh chu in hoa
bool isNamesake(char *s);//Ham de kiem tra xem ten cua dinh vua tao co cung ten voi cac dinh khac khong
void drawAddVertex(int x, int y);//ve mot vong tron khi tao dinh
void editVertex();//xoa dinh tren do thi hoac doi ten dinh
void initEditTools();//Khoi tao hop thoai chinh sua dinh
void drawEditTools(int x, int y);//Ve hop thoai edit dinh
void deleteVertex(int pos);//xoa dinh trong danh sach tai mot vi tri cho truoc
void moveVertex();//ham di chuyen dinh
void drawMatrix();//ve ma tran trong so
void drawArrow(Vertex u, Vertex v, int color, int w);//ve mui ten
void drawTriangle(int x1, int y1, int x2, int y2, int color);//ve hinh tam giac dung cho mui ten
void drawLine(Vertex u, Vertex v, int color, int w);//ve duong noi hai dinh, ap dung cho do thi vo huong
void printWeight(int x, int y, int w);//xuat trong so 
void drawAllEdges();//ham ve tat ca cac canh
void drawAllEdges(int color);//ham ve tat ca cac canh voi mau do nguoi dung chon
void drawCurvedArrow(Vertex u, Vertex v, int color, int w);//ve mui ten dang cong
void drawCurvedArrow2(Vertex u, Vertex v, int color, int w);
void addEdge(int startPos);//tao canh
int enterWeight();//ham nhap trong so
void bfsTraveler(int u);
void BFS();
void showResultBFS(int *trace, char *resultText, int count);//show ket qua thuat toan duyet BFS ra man hinh
void dfsTraveler(int u);
void DFS();
void showResultDFS(int *trace, char *resultText, int count);//show ket qua thuat toan duyet DFS ra man hinh
int chooseVertex(char * request);//chon dinh
template <typename Type>
void setArrayTo(Type *arr, int num, int value);//ham de cho tat ca cac gia tri cua mang ve mot gia tri nao do
void clearmouseclick();//xoa tat ca cac click chuot
void pathXY();//tim duong di ngan nhat tu x toi y
void dijkstra(int start, int end);//thuat toan tim duong di ngan nhat
int minDistance(int *dist, bool *sptSet);// mot ham tien ich de tim dinh voi gia tri khoang cach toi thieu, 
										 //tu tap hop cac dinh chua duoc bao gom trong cay duong dan ngan nhat
void showResultPathXY(int *trace, int *dist, int start, int end);//show ra man hinh duong di ngan nhat tu x toi y
void eulerCycle(int u);//ham tim chu trinh euler
void showResultEulerCycle(stack CE);//show ket qua chu trinh euler ra man hinh
bool isUndirectedGraph();//ham kiem tra do thi co vo huong khong
bool isConnectedGraph();//ham kiem tra do thi co lien thong hay khong
void DFS(int u);//duyet theo chieu sau
void connectedComponents();//thanh phan lien thong
int countConnectedComponents();//tinh thanh phan lien thong cua do thi
int countConnectedComponents(int **connectedComponents);//tinh thanh phan lien thong cua do thi 
														//va tra ve mang cac thanh phan lien thong cua do thi
void showResultConnectedComponents(int **connectedComponents, int count, bool isUndirectedGraph, char *resultText);//show ra man hinh thanh phan lien thong cua do thi
int** create2DArray(unsigned height, unsigned width);//tao ma tran
void delete2DArray(int **arr, unsigned height, unsigned width);//xoa ma tran
template <typename Type>
void set2DArrayTo(Type **arr, unsigned height, unsigned width, int value);//cho tat ca cac gia tri cua ma tran ve mot gia tri nao do
void drawEnterToExitText();//in ra dong "press ENTER to exit" o goc phai duoi man hinh lam viec
void drawKeyToExitText();//in ra dong "press KEY to exit" o goc phai duoi man hinh lam viec
						//ham nay thuong duoc dung cho cac ham khong co ket qua 
//int tarjanAlgo(bool showResult, int remove);
//void tarjanVisit(int u, int *disc, int *low, stack &s, int &count, int &components, bool callTarjanResult);
//void tarjanResult(stack &s, int end, int components);


int min(int a, int b);
void tarjanAlgo(int u, int disc[], int lowLink[], stack &stk, bool stkItem[], int **componentsList, int &counter);
int countStrongConComponent(int **compnentsList);


int main() {
	initwindow(1280, 720);
	setTaskBarButtons();
	setFrame();
	initDefaultVertices();
	initEditTools();
	loadFileStartUp();
	process();
}

void process() {
	Vertex vtex;
	int page = 0;
	while (true) {	
		setactivepage(page);
		setvisualpage(1 - page);
		delay(10);
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
		
		
		
//		if (ismouseclick(WM_MOUSEMOVE)) {
//			int x, y;
//			getmouseclick(WM_MOUSEMOVE, x, y);
//			cout << x << " " << y << endl;
//		}
	}
	getch();
	closegraph();
}

int min(int a, int b) {
	return (a < b) ? a: b;
}


void tarjanAlgo(int u, int disc[], int lowLink[], stack &stk, bool stkItem[], int **componentsList, int &counter) {
	disc[u] = lowLink[u] = ++Time;
	stk.push(u);
	stkItem[u] = true;
	for (int v = 0; v < n; v++) {
		if (G[u][v]) {	
			if (disc[v] == -1) {
				tarjanAlgo(v, disc, lowLink, stk, stkItem, componentsList, counter);
				lowLink[u] = min(lowLink[u], lowLink[v]);
			} 
			else if (stkItem[v])
				lowLink[u] = min(lowLink[u], disc[v]);
		}
	}
	int poppedItem = 0;
	if (lowLink[u] == disc[u]) {
		int k = 0;
		while (stk.get() != u) {
			poppedItem = stk.pop();
			componentsList[counter][k++] = poppedItem;
			stkItem[poppedItem] = false;
		}
		poppedItem = stk.pop();
		componentsList[counter][k] = poppedItem;
		stkItem[poppedItem] = false;
		counter++;
	}
}

int countStrongConComponent(int **componentsList) {
	Time = 0;
	int disc[n], lowLink[n], counter;
	bool stkItem[n];
	counter = 0;
	stack stk;
	for (int i = 0; i < n; i++) {
		disc[i] = lowLink[i] = -1;
		stkItem[i] = false;
	}
	for (int i = 0; i < n; i++)
		if (disc[i] == -1)
			tarjanAlgo(i, disc, lowLink, stk, stkItem, componentsList, counter);
	return counter;
}

void drawKeyToExitText() {
	char c = getcolor();
	setcolor(YELLOW);
	outtextxy(1259 - textwidth("press KEY to exit"), 520 - textheight("press KEY to exit"), "press KEY to exit");
	setcolor(c);
}

void drawEnterToExitText() {
	char c = getcolor();
	setcolor(YELLOW);
	outtextxy(1259 - textwidth("press ENTER to exit"), 520 - textheight("press ENTER to exit"), "press ENTER to exit");
	setcolor(c);
}

template <typename Type>
void set2DArrayTo(Type **arr, unsigned height, unsigned width, int value) {
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			arr[i][j] = value;
}

void delete2DArray(int **arr, unsigned height, unsigned width) {
	for (int h = 0; h < height; h++)
		delete []arr[h];
	delete []arr;
	arr = 0;
}

int** create2DArray(unsigned height, unsigned width) {
    int** array2D = 0;
    array2D = new int*[height];//tao bien ma tran
    
    for (int h = 0; h < height; h++) {
    	//tao cot cho ma tran
        array2D[h] = new int[width];
        for (int w = 0; w < width; w++) 
            //cho gia tri ban dau cua moi phan tu cua ma tran la 0
            array2D[h][w] = 0;
    }
    return array2D;
}

int countConnectedComponents() {
	setArrayTo(visited, n, false);
	int counter = 0;
	for (int i = 0; i < n; i++)
		if (!visited[i]) {
			counter++;
			DFS(i);
		}
	return counter;
}

void connectedComponents() {
	int **list = create2DArray(n, n), counter;
	set2DArrayTo(list, n, n, -1);
	bool isUGr = isUndirectedGraph();
	char resultText[100], counterStr[4];
	if (isUGr) {
		counter = countConnectedComponents(list);
		strcpy(resultText, "Do thi vo huong co ");
		itoa(counter, counterStr, 10);
		strcat(resultText, counterStr);
		strcat(resultText, " thanh phan lien thong");
//		cout << resultText << endl;
		showResultConnectedComponents(list, counter, 1, resultText);
	}
	else if (isConnectedGraph()){
		counter = countStrongConComponent(list);
		if (counter == 1)
			//neu counter == 1 thi suy ra day la do thi lien thong manh
			strcpy(resultText, "Do thi nay la do thi co huong lien thong manh");
		else {
			strcpy(resultText, "Do thi lien thong co huong co ");
			itoa(counter, counterStr, 10);
			strcat(resultText, counterStr);
			strcat(resultText, " thanh phan lien thong manh");
//			cout << resultText << endl;
		}
		showResultConnectedComponents(list, counter, 0, resultText);
	}
	else {
		counter = countConnectedComponents(list);
		strcpy(resultText, "Do thi lien thong yeu. Bien doi do thi thanh do thi vo huong ta duoc ");
		itoa(counter, counterStr, 10);
		strcat(resultText, counterStr);
		strcat(resultText, " thanh phan lien thong");
		showResultConnectedComponents(list, counter, 1, resultText);
	}
	delete2DArray(list, n, n);
}

void showResultConnectedComponents(int **connectedComponents, int count, bool isUndirectedGraph, char *resultText) {
	int page = 0;
	char componentsStr[n][30] = {""};
	Button resultBox, xButton, components[n];
	resultBox.init(425, 525, 40, 834, YELLOW, BLACK, 1, resultText);
	for (int i = 0; i < count; i++) {
		//duyet tung thanh phan lien thong
		//tuong ung voi so hang cua ma tran connectedComponents
		for (int j = 0; j < n; j++) {
			//moi thanh phan lien thong se co cac dinh
			//tuong uong voi tung cot cua ma tran connectedComponets
			int v = connectedComponents[i][j];
			if (v != -1) {
				//neu v khac -1 thi noi ten dinh v vao sau componentsStr[i]
				strcat(componentsStr[i], vertices[v].name);
				//noi dau phay
				strcat(componentsStr[i], ", ");
			}
		
		}
		//xoa dau phay o sau cua moi chuoi thanh phan lien thong
		strnDel(componentsStr[i], strlen(componentsStr[i]) - 2, 2);
		//sao chep thanh phan lien thong sang moi button cua no
		//de hien thi ra man hinh
		components[i].name = componentsStr[i];
		components[i].height = 40;
		if (count < 5)
			components[i].width = 200;
		else 
			components[i].width = 100;
			
		components[i].bColor = BLACK;
		components[i].tColor = YELLOW;
		components[i].pattern = 1;
	}
	int frag = count / 2,
		x0 = 425 + (834 - frag * components[0].width) / 2,
		y0 = 525 + 40; 
	for (int i = 0; i < frag; i++) {
		components[i].coordinates.x = x0;
		components[i].coordinates.y = y0;
		x0 += (components[i].width + 5);
	}
	x0 = 425 + (834 - (count - frag)* components[0].width) / 2,
	y0 += 45;
	
	for (int i = frag; i < count; i++) {
		components[i].coordinates.x = x0;
		components[i].coordinates.y = y0;
		x0 += (components[i].width + 5);
	}
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		drawFrame();
		drawTaskBarButtons();
		drawMatrix();
		drawVertices();
		drawEnterToExitText();
		drawAllEdges();
		resultBox.draw();
		for (int i = 0; i < count; i++) {
			for (int j = 0; j < n; j++) {
				int v = connectedComponents[i][j];
				if (v != -1) {
					//tu ham connectedComponents() 
					//ta gan gia tri cho ma tran connectedComponents la -1
					//nen o ham nay ta chi thao tac voi nhung 
					//dinh co gia tri khac -1
					vertices[v].highLight(YELLOW, i + 1);//mau i + 1 tuong tu nhu mau tu 1 toi 11 (voi dieu kien la MAX = 10)
					if (isUndirectedGraph) {
						//neu la do thi vo huong thi ve
						//cac duong thang khong co trong so w = 0;
						for (int k = 0; k < n; k++)
							if (G[v][k])
								drawLine(vertices[v], vertices[k], i + 1, 0);
						}
					else {
						for (int k = 0; k < n; k++) {
							int h = connectedComponents[i][k];
							if (h != -1 && G[v][h]) {
								if (!G[h][v])
									drawArrow(vertices[v], vertices[h], i + 1, G[v][h]);
								else
									drawCurvedArrow(vertices[v], vertices[h], i + 1, G[v][h]);	
							}
						}
					}
				}
			}
			components[i].draw();
			if (components[i].isHover()) {
				components[i].highLight();
				//neu di chuot vao vi tri o cua thanh phan lien thong 
				//nao thi cac dinh cua thanh phan lien thong do se duoc to sang
				for (int k = 0; k < n; k++) {
					int u = connectedComponents[i][k];
					if (u != -1)
						vertices[u].highLight(WHITE, 13);
				}
			}
		}
		if (kbhit()) {
			char key = getch();
			if (key == KEY_ESC || key == KEY_ENTER)
				break;	
		}	
		page = 1 - page;
	}
}

int countConnectedComponents(int **connectedComponents) {
	//setArrayTo(visited, n, false);
	int counter = 0;
	bool isAdded[n];//mang nay co tac dung danh dau cac dinh 
					//da duoc them vao thanh phan lien thong truoc
	for (int i = 0; i < n; i++)
		//cho mang ve gia tri false
		isAdded[i] = false, visited[i] = false;
	for (int i = 0; i < n; i++)
		if (!visited[i]) {
			//neu chua tham dinh i thi duyet dfs bat dau tu dinh i
			//dinh tham roi se duoc danh dau la true
			//tu dinh i neu co dinh nao nam trong danh sach dinh ke
			//voi i thi nhung dinh do duoc goi la mot thanh phan lien thong
			//ta se luu no vao mot ma tran de tra ve ket qua
			//nhung thanh phan lien thong cua do thi
			DFS(i);
			int k = 0;
			for (int j = 0; j < n; j++)
				if (visited[j] && !isAdded[j]) {
					//neu dinh da duoc dfs duyet roi 
					//va dinh do chua duoc them vao thanh phan lien thong nao
					//thi them no vao thanh phan lien thong thu counter
					isAdded[j] = true;
					connectedComponents[counter][k] = j;	
					k++;
				}
			counter++;
		}
	return counter;
}

void DFS(int u) {
	stack s;
	s.push(u);
	while (!s.isEmpty()) {
		u = s.pop();
		if (!visited[u]) {
			visited[u] = true;
			for (int i = 0; i < n; i++)
				if ((G[u][i] || G[i][u]) && !visited[i]) 
					s.push(i);
		}
	} 
}

bool isUndirectedGraph() {
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++)
			if (G[i][j])
				if (G[i][j] != G[j][i] || G[i][j] != 1) 
					return false;
	return true;	
}

bool isConnectedGraph() {
	//Kiem tra do thi co lien thong hay khong
	if (countConnectedComponents() == 1) return true;
	return false; 
}

void showResultEulerCycle(stack CE) {
	Button resultBox, xButton;
	resultBox.init(425, 525, 100, 834, YELLOW, BLACK, 1, "");
	xButton.init(1219, 525, 100, 40, WHITE, RED, 1, "x");
	char resultStr[20] = "Chu trinh euler", eulerResultStr[200] = "";
	int trace[n * n];
	int counter = 0;
	while (!CE.isEmpty()) {
		char vertex[3];
		int v = CE.pop();
		strcpy(vertex, vertices[v].name);
		strcat(eulerResultStr, vertex);
		strcat(eulerResultStr, " -> ");
		trace[counter] = v;
		counter++;
	}
	strnDel(eulerResultStr, strlen(eulerResultStr) - 3, 3);
	resultBox.name = eulerResultStr;
	int page = 0;
	bool isUGr = isUndirectedGraph();
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		drawFrame();
		drawTaskBarButtons();
		drawVertices();
		drawAllEdges();
		drawEnterToExitText();
		resultBox.draw();
		vertices[trace[0]].highLight();
		xButton.draw();
		setactivepage(1);
		setvisualpage(1);
		if (isUGr) {
			for (int i = 1; i < counter; i++) {
				int u = trace[i - 1];
				int v = trace[i];
				drawArrow(vertices[u], vertices[v], LIGHTGREEN, 0);
				delay(500);
				vertices[v].highLight();
				if (kbhit()) {
					char key = getch();
					if (key == KEY_ENTER)
						return;
				}
				if (xButton.isClickLMButton())
					return;
			}
		}
		else {
			for (int i = 1; i < counter; i++) {
				int u = trace[i - 1];
				int v = trace[i];
				if (G[u][v]) {
					if (!G[v][u]) {
						drawArrow(vertices[u], vertices[v], LIGHTGREEN, G[u][v]);
						delay(500);
						vertices[v].highLight();
					}
					else {
						drawCurvedArrow(vertices[u], vertices[v], LIGHTGREEN, G[u][v]);
						delay(500);
						vertices[v].highLight();						
					}
				}
				if (kbhit()) {
					char key = getch();
					if (key == KEY_ENTER)
						return;
				}
				if (xButton.isClickLMButton())
					return;
			}
		}

		if (kbhit()) {
			char key = getch();
			if (key == KEY_ENTER)
				break;
		}
		if (xButton.isClickLMButton())
			break;
		clearmouseclick();
		page = 1 - page;			
	}
}

void eulerCycle() {
	Button resultBox, xButton;
	resultBox.init(425, 525, 100, 834, YELLOW, BLACK, 1, "");
	xButton.init(1219, 525, 100, 40, WHITE, RED, 1, "x");
	stack st, CE;
	
	if (!isConnectedGraph()) {
		char resultStr[100] = "Do thi nay khong co chu trinh Euler vi khong lien thong";
		resultBox.name = resultStr;
		int page = 0;
		while (true) {
			setactivepage(page);
			setvisualpage(1 - page);
			taskBarFrame.draw();
			drawTaskBarButtons();
			resultBox.draw();
			xButton.draw();
			clearmouseclick();
			drawKeyToExitText();
//			ESCButton.draw();
			if (xButton.isClickLMButton())
				return;
			if (kbhit()) {
				getch();
				return;
			}
			page = 1 - page;
		}
	}
	
	if (isEmptyVertex())
		return;
	bool isUGr = isUndirectedGraph();
	if (isUGr) {
		//neu la do thi vo huong
		//dieu kien de do thi co chu trinh euler
		//khi va chi khi moi dinh cua no deu co bac chan
		//hoac co duy nhat 2 dinh bac le (truong hop nay chi tim duoc duong di euler)
		//khong co chu trinh euler
		//mang deg[] dung de luu bac cua tung dinh trong do thi
		int deg[n];
		for (int i = 0; i < n; i++) {
			deg[i] = 0;
			for (int j = 0; j < n; j++)
				if (G[i][j])
					deg[i]++;
		}
		int oddVertexDeg = 0;
		for (int i = 0; i < n; i++)
			//neu bac cua no la le thi do thi khong co chu trinh euler 
			if (deg[i] % 2) {
				oddVertexDeg++;
			}
		if (oddVertexDeg != 0 && oddVertexDeg != 2) {
			//neu do thi khong co chu trinh euler 
			//thi thong bao ra man hinh
			int page = 0;
			char resultStr[100] = "Do thi nay khong co chu trinh Euler vi dinh ";
			for (int i = 0; i < n; i++) {
				if (deg[i] % 2) {
					strcat(resultStr, vertices[i].name);
					strcat(resultStr, " ");
				}
			}
			strcat(resultStr, "co bac le.");
			resultBox.name = resultStr;
			while (true) {
				setactivepage(page);
				setvisualpage(1 - page);
				resultBox.draw();
//				ESCButton.draw();
				xButton.draw();
				drawKeyToExitText();
				taskBarFrame.draw();
				drawTaskBarButtons();
				if (kbhit())
					return;
				if (xButton.isClickLMButton())
					return;
				clearmouseclick();
				page = 1 - page;
			}
		}
		else if (oddVertexDeg == 2) {
			//truong hop do thi co hai dinh bac le duy nhat thi
			//co duong di euler
			//dinh bat dau duong di euler la dinh dau tien co dinh bac le
			int tmpMatrx[n][n];
			int u;
			for (u = 0; u < n; u++)
				if (deg[u] % 2)
					break;
			st.push(u);
				//sao chep ma tran G sang ma tran tmp
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					tmpMatrx[i][j] = G[i][j];
			while (!st.isEmpty()) {
				int counter = 0;
				int s = st.get();
				for (int i = 0; i < n; i++) {
					if (tmpMatrx[s][i] == 0)
						counter++;
				}
				if (counter != n) {
					for (int t = 0; t < n; t++) {
						if (tmpMatrx[s][t]) {
							st.push(t);
							tmpMatrx[s][t] /*= tmpMatrx[t][s]*/ = 0;
							if (isUGr)
								tmpMatrx[t][s] = 0;
							break;
						}
					} 
				} 
				else {
					CE.push(s);
					st.pop();
				}
			}
			showResultEulerCycle(CE);
			return;
		}
	}
	else {
		//khi do thi la co huong
		//kiem tra ban bac ra va ban bac vao cua tat ca cac dinh
		//neu degIn != degOut thi khong co chu trinh euler
		int degOut[n], degIn[n], tmpMatrx[n][n];
		char resultStr[100] = "Do thi nay khong co chu trinh Euler vi dinh ";
		//tinh ban bac ra cua moi dinh
		for (int i = 0; i < n; i++) {
			degOut[i] = 0;
			for (int j = 0; j < n; j++)
				if (G[i][j])
					degOut[i]++;	
		} 
		//tinh ban bac vao cua moi dinh
		for (int i = 0; i < n; i++) {
			degIn[i] = 0;
			for (int j = 0; j < n; j++)
				if (G[j][i])
					degIn[i]++;
		}
		
		bool isEulerGraph = true;
		for (int i = 0; i < n; i++)
			//neu ban bac ra cua no khong bang ban bac vao
			if (degOut[i] != degIn[i]) {
				strcat(resultStr, vertices[i].name);
				strcat(resultStr, " ");
				isEulerGraph = false;
			}
		strcat(resultStr, " co ban bac ra khong bang ban bac vao");
		resultBox.name = resultStr;
		if (!isEulerGraph) {
			int page = 0;
			while (true) {
				setactivepage(page);
				setvisualpage(1 - page);
				taskBarFrame.draw();
//				ESCButton.draw();
				resultBox.draw();
				xButton.draw();
				drawKeyToExitText();
				if (kbhit())
					return;
				if (xButton.isClickLMButton())
					return;
				clearmouseclick();
				page = 1 - page;
			}	
		}
	}
	int u = chooseVertex("Chon dinh bat dau chu trinh Euler");
	st.push(u);//cho dinh u vao ngan xep
	int tmpMatrx[n][n];//luu ma tran ke vao mot ma tran tam thoi khac 
					//vi khi tim chu trinh Euler no se bi bien doi
	//sao chep ma tran G sang ma tran tmp
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			tmpMatrx[i][j] = G[i][j];
	
	while (!st.isEmpty()) {
		int counter = 0;
		int s = st.get();
		for (int i = 0; i < n; i++) {
			if (tmpMatrx[s][i] == 0)
				counter++;
		}
		if (counter != n) {
			for (int t = 0; t < n; t++) {
				if (tmpMatrx[s][t]) {
					st.push(t);
					tmpMatrx[s][t] /*= tmpMatrx[t][s]*/ = 0;
					if (isUGr)
						tmpMatrx[t][s] = 0;
					break;
				}
			} 
		} 
		else {
			CE.push(s);
			st.pop();
		}
	}
	showResultEulerCycle(CE);
}

void showResultPathXY(int *trace, int *dist, int start, int end) {
	Button resultBox, xButton;
	resultBox.init(425, 525, 100, 834, YELLOW, BLACK, 1, "");
	xButton.init(1219, 525, 100, 40, WHITE, RED, 1, "x");
	if (dist[end] == INT_MAX) {
		char str[80] = "Khong ton tai duong di tu ";
		strcat(str, vertices[start].name);
		strcat(str, " den ");
		strcat(str, vertices[end].name);
		strcat(str, "! Tu dong thoat sau [     s]");
//		strcpy(resultBox.name, str);
		resultBox.name = str;
		int page = 0, startTime, endTime, timeCount;
		time_t now = time(0);
		tm *ltm = localtime(&now);
		startTime =ltm->tm_hour * 3600 + ltm->tm_min * 60 + ltm->tm_sec;
		while(true) {
			now = time(0);
			ltm = localtime(&now);
			endTime = ltm->tm_hour * 3600 + ltm->tm_min * 60 + ltm->tm_sec;
			timeCount = endTime - startTime;
			
			if (timeCount == 15)
				break;
			setactivepage(page);
			setvisualpage(1 - page);
			drawFrame();
			drawTaskBarButtons();
			drawMatrix();
			drawVertices();
			drawAllEdges();
			resultBox.draw();
			xButton.draw();
			drawKeyToExitText();
			if (kbhit()) 
				break;
			clearmouseclick();
			char timeCountdownStr[4];
			itoa(15 - timeCount, timeCountdownStr, 10);
			outtextxy(425 + (834 - textwidth(str)) / 2 + textwidth(str) - textwidth(timeCountdownStr) - textwidth("s]"), 525 + (100 - textheight(timeCountdownStr)) / 2, timeCountdownStr);
			page = 1 - page;
		}
		
	} 
	else {
		int traveler[n];
		char resultText[100] = "";
		char weightSumText[25] = "Chieu dai duong di: ", weightSumStr[5]; 
		resultBox.name = "";
		itoa(dist[end], weightSumStr, 10);
		strcat(weightSumText, weightSumStr);
		stack s;
		//sau khi tim duoc duong di ta se truy vet duong di tu 
		//dinh end toi dinh start bang mang trace
		//va push no vao trong stack
		while (end != start) {
			s.push(end);
			end = trace[end];
		}
		s.push(start);
		int count = 0, v;
		do {
			v = s.pop();
			strcat(resultText, vertices[v].name);
			strcat(resultText, " -> ");
			traveler[count] = v;
			count++;
		} while (!s.isEmpty());
		strnDel(resultText, strlen(resultText) - 3, 3);
		resultBox.name = resultText;
		int page = 0;
		bool isUGr = isUndirectedGraph();
		//show ra man hinh
		while (true) {
			setactivepage(page);
			setvisualpage(1 - page);
			drawFrame();
			drawTaskBarButtons();
			drawMatrix();
			drawVertices();
			drawAllEdges();
			resultBox.draw();
			xButton.draw();
//			ESCButton.draw();
			clearmouseclick();
			outtextxy(425 + (834 - textwidth(weightSumText)) / 2, 525 + (150 - textheight(weightSumText)) / 2, weightSumText);
			drawEnterToExitText();
			setactivepage(1);
			setvisualpage(1);
			int u = trace[0], v;
			vertices[u].highLight();
			if (isUGr)
				for (int i = 1; i < count; i++) {
					u = traveler[i - 1];
					v = traveler[i];
					drawArrow(vertices[u], vertices[v], LIGHTGREEN, G[u][v]);
					delay(200);
					vertices[v].highLight();
					drawEnterToExitText();
					if (kbhit()) {
						char key = getch();
						if (key == KEY_ENTER)
							return;
					}
					if (xButton.isClickLMButton())
						return;
				}
			else 
				for (int i = 1; i < count; i++) {
					u = traveler[i - 1];
					v = traveler[i];
					if (!G[v][u])
						drawArrow(vertices[u], vertices[v], LIGHTGREEN, G[u][v]);
					else 
						drawCurvedArrow(vertices[u], vertices[v], LIGHTGREEN, G[u][v]);
					delay(200);
					vertices[v].highLight();
					if (kbhit()) {
						char key = getch();
						if (key == KEY_ENTER)
							return;
					}
					if (xButton.isClickLMButton())
						return;
				}
			if (kbhit()) {
				char key = getch();
				if (key == KEY_ENTER)
					return;
			}
			if (xButton.isClickLMButton())
				return;
 			page = 1 - page;
		}
	}
}
 
int minDistance(int *dist, bool *sptSet) {
    // Khoi tao gia tri toi thieu
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int start, int end) {
	int dist[n];//Mang dau ra. dist [i] se giu khoang cach ngan nhat 
				// tu start den end
	bool sptSet[n];//sptset [i] se dung neu dinh duoc dua vao ngan nhat
					// cay duong dan hoac khoang cach ngan nhat tu start den end duoc hoan thanh
	int trace[n];
	// Khoi tao tat ca cac khoang cach la vo han va stpset [] la false
	for (int i = 0; i < n; i++)
		dist[i] = INT_MAX, sptSet[i] = false;
	dist[start] = 0;//khoang cach cua dinh nguon tu chinh no luon la 0
	// Tim duong di ngan nhat cho tat ca cac dinh
	for (int count = 0; count < n - 1; count++) {
		//Chon dinh khoang cach toi thieu tu tap hop cac dinh chua
		//duoc xu ly. u luon bang start trong lan lap dau tien.
		int u = minDistance(dist, sptSet);
		sptSet[u] = true;//danh dau dinh duoc lua chon la da duoc xu ly
		for (int v = 0; v < n; v++)
			// Cap nhat dist [v] Chi khi khong co trong sptset, co mot canh tu 
			// u den v va tong trong luong cua duong dan tu src den v qua u la 
			// nho hon gia tri hien tai cua dist [v]
			if (!sptSet[v] && G[u][v] && dist[u] != INT_MAX
                && dist[u] + G[u][v] < dist[v]) {
                	dist[v] = dist[u] + G[u][v];
                	trace[v] = u;
				}
	}
	showResultPathXY(trace, dist, start, end);
	return;
}

void pathXY() {
	Button instruction;
	instruction.init(425, 525, 40, 834, YELLOW, BLACK, 1, "Chon dinh ket thuc");
	if (isEmptyVertex()) return;
	if (n < 2) return;
	int start, end;
	start = chooseVertex("Chon dinh bat dau");
	end = start;
	int page = 0;
	while (end == start) {
		setactivepage(page);
		setvisualpage(1 - page);
		pointBarFrame.draw();
		drawVertices();
		instruction.draw();
		int x = mousex();
		int y = mousey();
		if (x >= W_LEFT && x <= W_RIGHT && y >= W_TOP && y <= W_BOTTOM) {
			setlinestyle(DOTTED_LINE, 1, 2);
			line(vertices[start].coordinates.x, vertices[start].coordinates.y, x, y);
			setlinestyle(SOLID_LINE, 1, 1);
		}
		vertices[start].highLight();
		if (ismouseclick(WM_LBUTTONDOWN)) {
			int xL, yL;
			getmouseclick(WM_LBUTTONDOWN, xL, yL); 
			for (int i = 0; i < n; i++) {
				int xV = vertices[i].coordinates.x;
				int yV = vertices[i].coordinates.y;
				if ((xV - xL) * (xV - xL) + (yV - yL) * (yV - yL) <= RADIUS * RADIUS) {
					end = i;
				}
			}
		}
		clearmouseclick();
		page = 1 - page;
	}
	dijkstra(start, end);
	
}

void clearmouseclick() {
	if (ismouseclick(WM_RBUTTONDOWN)) 
		clearmouseclick(WM_RBUTTONDOWN);
	if (ismouseclick(WM_LBUTTONDOWN))
		clearmouseclick(WM_LBUTTONDOWN);
	if (ismouseclick(WM_LBUTTONDBLCLK))
		clearmouseclick(WM_LBUTTONDBLCLK);
}

template <typename Type>

void setArrayTo(Type *arr, int num, int value) {
	for (int i = 0; i < num; i++)
		arr[i] = value;
}

void DFS() {
	if (isEmptyVertex()) return;
	int start = chooseVertex("Chon dinh bat dau duyet theo chieu sau (DFS)");
	if (start != -1) {
		setArrayTo(visited, n, 0);
		dfsTraveler(start);
	}
}

void showResultDFS(int *trace, char *resultText, int count) {
	Button resultBox, xButton;
	resultBox.init(425, 525, 100, 834, YELLOW, BLACK, 1, resultText);
	xButton.init(1219, 525, 100, 40, WHITE, RED, 1, "x");
	int page = 0; 
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		delay(100);
		drawFrame();
		drawVertices();
		drawAllEdges();
		drawTaskBarButtons();
		drawMatrix();
		ESCButton.draw();
		resultBox.draw();
		xButton.draw();
		outtextxy(430, 525 + (100 - textheight("Ket qua thuat toan DFS:")) / 2, "Ket qua thuat toan DFS:");
		drawEnterToExitText();
		setactivepage(1);
		setvisualpage(1);
		for (int i = 0; i < count; i += 2) {
			int u = trace[i];
			int v = trace[i + 1];
			vertices[u].highLight();
			drawArrow(vertices[u], vertices[v], LIGHTGREEN, 0);
			delay(200);
			vertices[v].highLight();
		}
		if (xButton.isClickLMButton())
			break;
		if (kbhit()) {
			char key = getch();
			if (key == KEY_ENTER)
				break;
		}
		clearmouseclick();
		page = 1 - page;
	}
}

void dfsTraveler(int u) {
	int start = u;
	stack s;
	int trace[n * n];
	stack edgeStart;
	int count = 0;
	char resultText[100] = "";
	s.push(u);
	setactivepage(1);
	setvisualpage(1);
	while (!s.isEmpty()) {
		clearmouseclick();
		drawEnterToExitText();
		u = s.pop();//lay dinh o tren ngan xep va xoa no ra khoi danh sach
		if (!visited[u]) {//neu dinh do chua duoc tham
			vertices[u].highLight();
			strcat(resultText, vertices[u].name);
			strcat(resultText, " -> ");
			visited[u] = 1;//danh dau no da tham
			for (int i = n - 1; i >= 0; i--)
				if ((G[u][i] || G[i][u]) && !visited[i]) {
					s.push(i);//them no vao hang doi
					edgeStart.push(u);
				}//neu dinh chua duyet va ke voi dinh u	
		}
		int k = edgeStart.pop();
		int j = s.get();
		while (!G[k][j] && !edgeStart.isEmpty()) {
			k = edgeStart.pop();
		}	
		if (j != k && !visited[j]) {
			drawArrow(vertices[k], vertices[j], LIGHTGREEN, 0);
			trace[count] = k;
			trace[count + 1] = j;
			delay(500);
			count += 2;
		}
		if (kbhit()) {
			char key = getch();
			if (key == KEY_ENTER)
				return;
		}
	}
	strnDel(resultText, strlen(resultText) - 3, 3);
	showResultDFS(trace, resultText, count);
}

void BFS() {
	if (isEmptyVertex()) return;
	int start = chooseVertex("Chon dinh bat dau duyet theo chieu rong (BFS)");
	if (start != -1) {
		setArrayTo(visited, n, 0);
		bfsTraveler(start);
	}
}

void showResultBFS(int *trace, char *resultText, int count) {
	Button resultBox, xButton;
	resultBox.init(425, 525, 100, 834, YELLOW, BLACK, 1, resultText);
	xButton.init(1219, 525, 100, 40, WHITE, RED, 1, "x");
	int page = 0; 
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		delay(100);
		drawFrame();
		drawVertices();
		drawAllEdges();
		drawTaskBarButtons();
		drawMatrix();
		ESCButton.draw();
		resultBox.draw();
		xButton.draw();
		outtextxy(430, 525 + (100 - textheight("Ket qua thuat toan BFS:")) / 2, "Ket qua thuat toan BFS:");
		drawEnterToExitText();
		setactivepage(1);
		setvisualpage(1);
		for (int i = 0; i < count; i += 2) {
			int u = trace[i];
			int v = trace[i + 1];
			vertices[u].highLight();
			drawArrow(vertices[u], vertices[v], LIGHTGREEN, 0);
			delay(200);
			vertices[v].highLight();
		}
		if (xButton.isClickLMButton())
			break;
		if (kbhit()) {
			char key = getch();
			if (key == KEY_ENTER)
				break;
		}
		clearmouseclick();
		page = 1 - page;
	}
}

void bfsTraveler(int u) {
//	int start = u;
	queue q;
	int trace[n * n];
	queue edgeStart;
	int count = 0;
	char resultText[100] = "";
	q.push(u);
	setactivepage(1);
	setvisualpage(1);
	while (!q.isEmpty()) {
		clearmouseclick();
		drawEnterToExitText();
		u = q.pop();//lay dinh o tren hang doi va xoa no ra khoi danh sach
		if (!visited[u]) {//neu dinh do chua duoc tham
			vertices[u].highLight();
			strcat(resultText, vertices[u].name);
			strcat(resultText, " -> ");
			visited[u] = 1;//danh dau no da tham
			for (int i = 0; i < n; i++)
				if ((G[u][i] || G[i][u]) && !visited[i]) {
					q.push(i);//them no vao ngan xep
					edgeStart.push(u);
				}//neu dinh chua duyet va ke voi dinh u	
		}
		int k = edgeStart.pop();
		int j = q.get();
		while (!G[k][j] && !edgeStart.isEmpty()) {
			k = edgeStart.pop();
		}	
		if (j != k && !visited[j]) {
			drawArrow(vertices[k], vertices[j], LIGHTGREEN, 0);
			trace[count] = k;
			trace[count + 1] = j;
			delay(500);
			count += 2;
		}
		if (kbhit()) {
			char key = getch();
			if (key == KEY_ENTER)
				return;
		}
	}
	strnDel(resultText, strlen(resultText) - 3, 3);
	showResultBFS(trace, resultText, count);
}

int chooseVertex(char *request) {
	int x, y;
	int page = 0;
	Button instruction;
	instruction.init(425, 525, 40, 834, YELLOW, BLACK, 1, request);
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		delay(50);
		drawFrame();
		drawTaskBarButtons();
		drawMatrix();
		drawAllEdges();
		drawVertices();
		instruction.draw();
		if (ismouseclick(WM_LBUTTONDOWN)) {
			getmouseclick(WM_LBUTTONDOWN, x, y);
			for (int i = 0; i < n; i++) {
				int x0 = vertices[i].coordinates.x;
				int y0 = vertices[i].coordinates.y;
				if ((x - x0) * (x - x0) + (y - y0) * (y - y0) <= RADIUS * RADIUS)
					return i;
			}
		}
		if (kbhit()) {
			char key = getch();
			if (key == KEY_ESC) {
				return -1;
			}
		}
		page = 1 - page;
	}
}

int enterWeight() {
	int margin = 5;
	int height = 275 - 3 * margin - 40;
	int width = 400 - 2 * margin;
	char weightStr[4] = "";
	char request[] = "Nhap trong so";
	int i = 0, x, y;
	int page = 0;
	Button frame, finishButton, cancelButton, enterWeightBar;
	frame.init(15 + margin, 15 + 2 * margin + 40, height, width, YELLOW, DARKGRAY, 1, "");
	finishButton.init(15 + 2 * margin, 275 - margin - 30, 40, (width - 3 * margin) / 2, YELLOW, BLACK, 9, "HOAN THANH");
	cancelButton.init(15 + 3 * margin + (width - 3 * margin) / 2,275 - margin - 30, 40, (width - 3 * margin) / 2, YELLOW, BLACK, 9, "HUY");
	enterWeightBar.init(15 + 2 * margin, 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50, 40, (width - 2 * margin), YELLOW, BLACK, 9, "");
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		delay(50);
		drawFrame();
		drawVertices();
		drawMatrix();
		drawAllEdges();
		drawTaskBarButtons();
		frame.draw();
		finishButton.draw();
		cancelButton.draw();
		enterWeightBar.draw();
		if (ismouseclick(WM_LBUTTONDOWN))
			getmouseclick(WM_LBUTTONDOWN, x, y);
		if (strcmp(weightStr, "") == 0) 
			outtextxy(15 + (400 - width) / 2 + (width - textwidth(request)) / 2, 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50 + (40 - textheight(request)) / 2, request);
		if (finishButton.isHover())
			finishButton.highLight();
		if (cancelButton.isHover())	
			cancelButton.highLight();
		if (strcmp(weightStr, "") != 0
		&& x >= finishButton.coordinates.x && x <= finishButton.coordinates.x + finishButton.width
		&& y >= finishButton.coordinates.y && y <= finishButton.coordinates.y + finishButton.height)
			break;
		if (x >= cancelButton.coordinates.x && x <= cancelButton.coordinates.x + cancelButton.width
		&& y >= cancelButton.coordinates.y && y <= cancelButton.coordinates.y + cancelButton.height) 
			return 0;
		if (ismouseclick(WM_LBUTTONDOWN)) {
			int x, y;
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if (x >= finishButton.coordinates.x && x <= finishButton.coordinates.x + finishButton.width
			&& y >= finishButton.coordinates.y && y <= finishButton.coordinates.y + finishButton.height
			&& strcmp(weightStr, "") != 0)
				break; 
		}
		if (kbhit()) {
			char key = getch();
			if (key >= '0' && key <= '9')
				if (i < 3) {
					weightStr[i] = key;
					i++;
				}
			if (i > 3)
				i = 3;
			if (key == KEY_BACKSPACE) {
				strnDel(weightStr, i - 1, 1);
				i--;
			}
			if (i < 0)
				i = 0;
			if (strcmp(weightStr, "") != 0 && key == 13)
				break;
			if (strcmp(weightStr, "") == 0 && key == 13) {
				frame.highLight(WHITE, RED);
				enterWeightBar.draw();
				finishButton.draw();
				cancelButton.draw();
				delay(50);
			}
		}
		outtextxy(15 + (400 - width) / 2 + (width - textwidth(weightStr)) / 2, 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50 + (40 - textheight(weightStr)) / 2, weightStr);
		if (i < 3 && strcmp(weightStr, "") != 0)
				outtextxy(15 + (400 - width) / 2 + (width - textwidth(weightStr)) / 2 + textwidth(weightStr), 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50 + (40 - textheight(weightStr)) / 2, "_");
		
		page = 1 - page;
	}
	return atoi(weightStr);
}

void addEdge(int startPos) {
	int x, y;
	Button instruction;
	char c = getcolor();
	int page = 0;
	int i = startPos;
	int x0 = vertices[i].coordinates.x;
	int y0 = vertices[i].coordinates.y;
	instruction.init(425, 525, 40, 834, YELLOW, BLACK, 1, "Di chuyen chuot toi vi tri dinh con lai va click chuot trai. Click chuot phai vao vi tri bat ky de huy tao canh");
	while (true) {
		setactivepage(page);
		setvisualpage(1 - page);
		delay(10);
		drawFrame();
		drawTaskBarButtons();
		drawVertices();
		drawMatrix();
		drawAllEdges();
		instruction.draw();
		x = mousex(), y = mousey();
		float corner = atan(float(abs(y - y0)) / abs(x - x0));
		float Rsin = RADIUS * sin(corner);
		float Rcos = RADIUS * cos(corner);
		int x11 = x0 + Rcos;
		int y11 = y0 + Rsin;
		int x22 = x - Rcos;
		int y22 = y - Rsin;
		if (x0 > x) {
			x11 = x0 - Rcos;
			x22 = x + Rcos;
		}
		if (y0 > y) {
			y11 = y0 - Rsin;
			y22 = y + Rsin;
		}	
		if (x22 >= 425 && x22 <= 1259 && y22 >= 20 && y22 <= 520) {
			setcolor(WHITE);
			setlinestyle(SOLID_LINE, 1, 2);
			line(x11, y11, x22, y22);
			drawTriangle(2 * x22 - (x + x22) / 2, 2 * y22 - (y22 + y) / 2, x22, y22, WHITE);
			setcolor(c);
			setlinestyle(SOLID_LINE, 0, 1);
		}
		if (ismouseclick(WM_LBUTTONDBLCLK))
			clearmouseclick(WM_LBUTTONDBLCLK);
		if (ismouseclick(WM_RBUTTONDOWN))
			break;
		if (ismouseclick(WM_LBUTTONDOWN)) {//click chuot trai vao cac dinh con lai
			bool checked = false;								//-> nhap trong so -> tao canh
			int xL, yL;
			getmouseclick(WM_LBUTTONDOWN, xL, yL);
			for (int j = 0; j < n; j++) {
				int xV, yV;
				xV = vertices[j].coordinates.x;
				yV = vertices[j].coordinates.y;
				if ((x0 - xL) * (x0 - xL) + (y0 - yL) * (y0 - yL) > RADIUS * RADIUS &&
				(xV - xL) * (xV - xL) + (yV - yL) * (yV - yL) <= RADIUS * RADIUS) {
					G[i][j] = enterWeight();
					checked = true;
				}
			}
			if (checked)
				break;
		}
		page = 1 - page;
	}
	saveFileStartUp();
	clearmouseclick(WM_RBUTTONDOWN);
	clearmouseclick(WM_LBUTTONDOWN);
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

void drawAllEdges(int color) {
	if (isUndirectedGraph()) {
		for (int i = 0; i < n; i++) 
			for(int j = 0; j < n; j++)
				if (G[i][j]) 
					drawLine(vertices[i], vertices[j], color, 0);
	}
	else {
		for (int i = 0; i < n; i++) 
			for(int j = 0; j < n; j++)
				if (G[i][j]) {
					if (!G[j][i])
						drawArrow(vertices[i], vertices[j], color, G[i][j]);
					else 
						drawCurvedArrow(vertices[i], vertices[j], color, G[i][j]);
				} 
	}
}

void drawAllEdges() {
	if (isUndirectedGraph()) {
		for (int i = 0; i < n; i++) 
			for(int j = 0; j < n; j++)
				if (G[i][j]) 
					drawLine(vertices[i], vertices[j], MAGENTA, 0);
	}
	else {
		for (int i = 0; i < n; i++) 
			for(int j = 0; j < n; j++)
				if (G[i][j]) {
					if (!G[j][i])
						drawArrow(vertices[i], vertices[j], MAGENTA, G[i][j]);
					else 
						drawCurvedArrow(vertices[i], vertices[j], MAGENTA, G[i][j]);
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

void drawLine(Vertex u, Vertex v, int color, int w) {
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
	if (w != 0)
		printWeight((x1 + x2) / 2, (y1 + y2) / 2, w);
	setcolor(c);
	setlinestyle(SOLID_LINE, 1, 1);
}

void drawArrow(Vertex u, Vertex v, int color, int w) {
	
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
	if (w != 0)
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
			if (key == KEY_BACKSPACE) {
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
		if (strcmp(name, "") != 0 && !isNamesake(name)
		&& x >= finishButton.coordinates.x && x <= finishButton.coordinates.x + finishButton.width
		&& y >= finishButton.coordinates.y && y <= finishButton.coordinates.y + finishButton.height)
			break;
		if (x >= cancelButton.coordinates.x && x <= cancelButton.coordinates.x + cancelButton.width
		&& y >= cancelButton.coordinates.y && y <= cancelButton.coordinates.y + cancelButton.height) 
			return;
		if (strcmp(name, "") != 0 && i < 2)
			outtextxy(15 + (400 - width) / 2 + (width - textwidth(name)) / 2 + textwidth(name), 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50 + (40 - textheight(name)) / 2, "_");
		page = 1 - page;
	}
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
	addEdgeButton.coordinates.x = x, addEdgeButton.coordinates.y = editNameButton.coordinates.y + editNameButton.height;
	
	editFrame.draw();
	deleteButton.draw();
	editNameButton.draw();
	addEdgeButton.draw();
}

void initEditTools() {
	//do hop thoai nay co the dung o bat ky vi tri nao trong chuong trinh nen x y mac dinh cua no la 0
	editFrame.init(0, 0, 120, 100, WHITE, DARKGRAY, 1, "");
	deleteButton.init(0, 0, 40, 100, YELLOW, BLACK, 1, "Xoa dinh");
	editNameButton.init(0, 0, 40, 100, YELLOW, BLACK, 1, "Sua ten");
	addEdgeButton.init(0, 0, 40, 100, YELLOW, BLACK, 1, "Tao canh");
	
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
					drawAllEdges();
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
					if (addEdgeButton.isHover())
						addEdgeButton.highLight();
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
						else if (xL >= addEdgeButton.coordinates.x && xL <= addEdgeButton.coordinates.x + addEdgeButton.width
						&& yL >= addEdgeButton.coordinates.y && yL <= addEdgeButton.coordinates.y + addEdgeButton.height) {
							addEdge(i);
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
	clearmouseclick(WM_LBUTTONDOWN);
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
	ESCButton.init(425, 660, 40, 100, YELLOW, BLACK, 1, "ESC | Thoat");
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
//				outtextxy(340, 15, "Thanh phan lien thong");
//				connectedComponents();
				connectedComponents();
//				tarjanAlgo(1, 2);
				break;
			}
			case 4: {
//				outtextxy(340, 15, "DFS");
				DFS();
				break;
			}
			case 5: {
//				outtextxy(340, 15, "Euler");
				eulerCycle();
				break;
			}
			case 6: {
				outtextxy(340, 15, "Dinh that");
				break;
			}
			case 7: {
//				outtextxy(340, 15, "Tim duong di ngan nhat");
				pathXY();
				break;
			}
			case 8: {
//				outtextxy(340, 15, "BFS");
				BFS();
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
	menuToolsHoverBar.init(20, 60, 225, 395, BLACK, BLACK, 1, "");//Nut gia de xu ly hover
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
	Button fileTools[4], fileToolsHoverBar/*khung x? l? hover*/;
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
		drawAllEdges();
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
			if (key == KEY_BACKSPACE) {
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
		if (strcmp(name, "") != 0 && i < 2)
			outtextxy(15 + (400 - width) / 2 + (width - textwidth(name)) / 2 + textwidth(name), 20 + (275 - height) / 2 + (height - 40 - margin) + margin - 40 - 2 * margin - 50 + (40 - textheight(name)) / 2, "_");
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

void Button::changeColor(int tColor, int bColor) {
	this->tColor = tColor;
	this->bColor = bColor;
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
		drawAllEdges();
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
