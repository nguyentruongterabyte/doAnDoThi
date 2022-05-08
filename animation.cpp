//file nay nam trong thu muc include

void showWelcome();
void setUserTextStyle();

void setUserTextStyle() {
	settextstyle(11, 0, 2);
}

void showWelcome() {
	settextstyle(0, 0, 10);
	char c = getcolor();
	setcolor(YELLOW);
	for (int i = 0; i < 200; i++) {
		outtextxy((1280 - textwidth("WELCOME")) / 2, (720 - textheight("WELCOME")) / 2, "WELCOME");
		delay(10);
	}
	cleardevice();
	for (int i = 0; i < 20; i++) {
		outtextxy((1280 - textwidth("ELCOME")) / 2, (720 - textheight("ELCOME")) / 2, "ELCOME");
		delay(10);
	}
	cleardevice();
	
	for (int i = 0; i < 20; i++) {
		outtextxy((1280 - textwidth("LCOME")) / 2, (720 - textheight("LCOME")) / 2, "LCOME");
		delay(10);
	}
	cleardevice();
	for (int i = 0; i < 20; i++) {
		outtextxy((1280 - textwidth("COME")) / 2, (720 - textheight("COME")) / 2, "COME");
		delay(10);
	}
	cleardevice();
	for (int i = 0; i < 20; i++) {
		outtextxy((1280 - textwidth("OME")) / 2, (720 - textheight("OME")) / 2, "OME");
		delay(10);
	}
	cleardevice();
	for (int i = 0; i < 20; i++) {
		outtextxy((1280 - textwidth("ME")) / 2, (720 - textheight("ME")) / 2, "ME");
		delay(10);
	}
	cleardevice();
	for (int i = 0; i < 20; i++) {
		outtextxy((1280 - textwidth("E")) / 2, (720 - textheight("E")) / 2, "E");
		delay(10);
	}
	
	cleardevice();
	setUserTextStyle();
	setcolor(c);
}



