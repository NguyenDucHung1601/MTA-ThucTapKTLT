#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>
#include<stdio.h>
#include"console.h";
using namespace std;

#pragma warning (disable : 4996)

#define MAUCHU 15
#define MAUNEN 10
#define WIDTH_SCREEN 1600
#define HEIGHT_SCREEN 1000

typedef char str[40];
str MenuChinh[6] = { " 1. Them moi ho so", " 2. In danh sach", " 3. Sap xep", " 4. Tim kiem", " 5. Thong ke", " 6. Thoat" };
str Menu2a[2] = { "1. Chinh sua ho so", "2. Xoa ho so" };
str Menu3a[4] = { "1. Sap xep chon (SelectionSort)", "2. Sap xep chen (InsertionSort)", "3. Sap xep noi bot (BubbleSort)", "4. Sap xep nhanh (QuickSort)" };
str Menu3b[6] = { "1. Ma sinh vien", "2. Ma Lop", "3. Ho va ten", "4. Ngay sinh", "5. Diem trung binh tich luy","6. Uu tien: Ma Lop > Ho ten > Ngay sinh" };
str Menu4a[2] = { "1. Tim kien tuan tu (linearSearch)","2. Tim kiem nhi phan (binarySearch)" };
str Menu4b[3] = { "1. Tim kiem chinh xac", "2. Tim kiem gan chinh xac", "3. Tim kiem ngau nhien" };
str Menu4c[5] = { "1. Ma sinh vien", "2. Ma Lop", "3. Ho va ten", "4. Ngay sinh", "5. Diem trung binh tich luy" };
str Menu5[2] = { "1. So luong sinh vien theo Lop", "2. Phan loai ket qua hoc tap" };

char fileTextName[] = { "StudentData.txt" }; // file text luu du lieu sinh vien
char fileBinaryName[] = { "StudentData.dat" }; // file nhi phan luu du lieu sinh vien
char info0[] = { "" }; // thong tin dinh kem Display
char info1[] = { "   >> Sap xep theo Ma sinh vien" };
char info2[] = { "   >> Sap xep theo Ma lop" };
char info3[] = { "   >> Sap xep theo Ho va ten" };
char info4[] = { "   >> Sap xep theo Ngay sinh" };
char info5[] = { "   >> Sap xep theo Diem TBTL" };
char info6[] = { "   >> Sap xep theo Thu tu uu tien: Ma lop > Ho ten > Ngay sinh" };

enum BUTTON { UP, DOWN, LEFT, RIGHT, ESC, ENTER };
BUTTON key(int k) {
	if (k == 224) {
		char c;
		c = getch();
		if (c == 72)	return UP;
		if (c == 80)	return DOWN;
		if (c == 75)	return LEFT;
		if (c == 77)	return RIGHT;
	}
	else if (k == 13)	return ENTER;
	else if (k == 27)	return ESC;
}

typedef struct SinhVien {
	char HoTen[41];
	int ngaySinh, thangSinh, namSinh;
	char MaSV[9];
	char MaLop[9];
	float DiemTBTL;
	struct SinhVien *next;
	struct SinhVien *prev;
}Node;
Node *first, *last;
Node *ffirst, *flast;

typedef struct LopHoc {
	char malop[9];
	int soSV, xuatsac, gioi, kha, trungbinh, yeu;
	struct LopHoc *next;
}Lop;
Lop *cfirst, *clast;


void programName();
int menu(str mangMenu[], int n, int x, int y);
void splitWindow();
bool checkDate(int day, int month, int year);
bool checkID(char ID[]);
char* setID(int k);
void chuanHoaTen(char s[]);
void chuanHoaID(char s[]);
void newStudent();
void deleteHead();
void deleteTail();
int length();
void deletePosition(int position);
void redoEdit(int position);
void paintInfo(Node *p, int stt, int yi, int color);
void rowInfo();
int totalNumPage();
int doList(int sttDau, int sttCuoi, Node *start, Node *end);
void display(Node *start, char info[]);
void swap(Node *p1, Node *p2);
int compareStrName(char s1[], char s2[]);
int compareName(Node *p1, Node *p2);
int compareDate(Node *p1, Node *p2);
int comparePointerPosition(Node *p1, Node *p2);
int compareMix(Node *p1, Node *p2);
void selectionSort(int choice);
void insertionSort(int choice);
void bubbleSort(int choice);
Node* element(int pos);
int partition(int choice, int left, int right);
void quickSort(int choice, int left, int right);
char* enterSearchChar(int choice);
float enterSearchNum(int choice);
void paintInfoFound(Node *p, int stt, int yi, int color);
int doListFound(int sttDau, int sttCuoi, Node *start, Node *end);
int lengthFound();
int totalNumPageFound();
void displayFound(int choice, int key, Node *start, char noidung[], int ngay, int thang, int nam, float diemtb);
void addTail_FoundList(Node *q);
void linearSearch(int way, int key);
void binarySearch(int choice);
void addTail_ClassList(char maLop[]);
void thongKe(int choice);
void writeTextFile(char *fileName);
void readTextFile(char *fileName);
void writeBinaryFile(char *fileName);
void readBinaryFile(char *fileName);
void chuanHoaDataFromFile();


int main() {
	first = NULL;
	last = NULL;
	resizeConsole(WIDTH_SCREEN, HEIGHT_SCREEN); // chinh lai size man hinh
	//readTextFile(fileTextName);// doc du lieu tu da luu tu file StudentData.txt
	readBinaryFile(fileBinaryName); // doc du lieu da luu tu file StudentData.dat
	chuanHoaDataFromFile();
	programName();
mnc:	switch (menu(MenuChinh, 6, 0, 7)) {
case 1: //================== THAO TAC CHINH 1: THEM MOI HO SO ==========================
	newStudent();
	break;
case 2: //================== THAO TAC CHINH 2: IN DANH SACH ============================
	display(first, info0);
	break;
case 3: //================== THAO TAC CHINH 3: SAP XEP =================================
	TextColor(11);		gotoXY(21, 9);		cout << "-->  Chon thuat toan sap xep:";
	switch (menu(Menu3a, 4, 25, 10))
	{
	case 1:		TextColor(11);		gotoXY(59, 10);		cout << "-->  Chon khoa de sap xep:";
		switch (menu(Menu3b, 6, 64, 11)) {
		case 1:	selectionSort(1);	clrscr();	display(first, info1);	break;
		case 2:	selectionSort(2);	clrscr();	display(first, info2);	break;
		case 3:	selectionSort(3);	clrscr();	display(first, info3);	break;
		case 4:	selectionSort(4);	clrscr();	display(first, info4);	break;
		case 5:	selectionSort(5);	clrscr();	display(first, info5);	break;
		case 6: selectionSort(6);	clrscr();	display(first, info6);	break;
		}
		break;
	case 2:		TextColor(11);		gotoXY(59, 11);		cout << "-->  Chon khoa de sap xep:";
		switch (menu(Menu3b, 6, 64, 12)) {
		case 1:	insertionSort(1);	clrscr();	display(first, info1);	break;
		case 2:	insertionSort(2);	clrscr();	display(first, info2);	break;
		case 3:	insertionSort(3);	clrscr();	display(first, info3);	break;
		case 4:	insertionSort(4);	clrscr();	display(first, info4);	break;
		case 5:	insertionSort(5);	clrscr();	display(first, info5);	break;
		case 6:	insertionSort(6);	clrscr();	display(first, info6);	break;
		}
		break;
	case 3:		TextColor(11);		gotoXY(59, 12);		cout << "-->  Chon khoa de sap xep:";
		switch (menu(Menu3b, 6, 64, 13)) {
		case 1:	bubbleSort(1);	clrscr();	display(first, info1);	break;
		case 2: bubbleSort(2);	clrscr();	display(first, info2);	break;
		case 3: bubbleSort(3);	clrscr();	display(first, info3);	break;
		case 4:	bubbleSort(4);	clrscr();	display(first, info4);	break;
		case 5:	bubbleSort(5);	clrscr();	display(first, info5);	break;
		case 6:	bubbleSort(6);	clrscr();	display(first, info6);	break;
		}
		break;
	case 4:		TextColor(11);		gotoXY(59, 13);		cout << "-->  Chon khoa de sap xep:";
		switch (menu(Menu3b, 6, 64, 14)) {
		case 1:	quickSort(1, 1, length());		clrscr();	display(first, info1);	break;
		case 2:	quickSort(2, 1, length());		clrscr();	display(first, info2);	break;
		case 3: quickSort(3, 1, length());		clrscr();	display(first, info3);	break;
		case 4:	quickSort(4, 1, length());		clrscr();	display(first, info4);	break;
		case 5:	quickSort(5, 1, length());		clrscr();	display(first, info5);	break;
		case 6:	quickSort(6, 1, length());		clrscr();	display(first, info6);	break;
		}
	}
	break;
case 4: //================== THAO TAC CHINH 4: TIM KIEM ================================
	TextColor(11);		gotoXY(20, 10);		cout << "-->  Chon thuat toan tim kiem:";
	switch (menu(Menu4a, 2, 25, 11)) {
	case 1: // ----------- Tim kiem TUAN TU --------------------	
		TextColor(11);		gotoXY(64, 11);		cout << "-->  Chon kieu tim kiem:";
		switch (menu(Menu4b, 3, 69, 12)) {
		case 1: // tim kiem chinh xac
			TextColor(11);	gotoXY(96, 12); cout << "--> Chon khoa can tim kiem";
			switch (menu(Menu4c, 5, 100, 13)) {
			case 1:	linearSearch(1, 1);	break;
			case 2:	linearSearch(1, 2);	break;
			case 3:	linearSearch(1, 3); break;
			case 4: linearSearch(1, 4);	break;
			case 5:	linearSearch(1, 5);	break;
			}
			break;
		case 2: // tim kiem gan chinh xac
			TextColor(11);	gotoXY(96, 13); cout << "--> Chon khoa can tim kiem";
			switch (menu(Menu4c, 5, 100, 14)) {
			case 1:	linearSearch(2, 1);	break;
			case 2:	linearSearch(2, 2);	break;
			case 3:	linearSearch(2, 3);	break;
			case 4:	linearSearch(2, 4);	break;
			case 5: linearSearch(2, 5);	break;
			}
			break;
		case 3: // tim kiem ngau nhien khong quan tam den truong
			linearSearch(3, 0); break;
		}
		break;
	case 2: // --------------- Tim kiem NHI PHAN --------------------	
		TextColor(11);		gotoXY(64, 12);		cout << "-->  Chon khoa can tim kiem:";
		switch (menu(Menu4c, 5, 69, 13)) {
		case 1: binarySearch(1); break;
		case 2: binarySearch(2); break;
		case 3:	binarySearch(3); break;
		case 4: binarySearch(4); break;
		case 5: binarySearch(5); break;
		}
		break;
	}
	break;
case 5: //================== THAO TAC CHINH 5: THONG KE =================================
	TextColor(11);		gotoXY(20, 11);		cout << "-->  Chon bao cao thong ke:";
	switch (menu(Menu5, 2, 25, 12)) {
	case 1: thongKe(1); break;
	case 2: thongKe(2); break;
	}
	break;
case 6: // ================== THAO TAC CHINH 6: THOAT ====================================
	writeTextFile(fileTextName); // luu lai toan bo du lieu vao file StudentData.txt truoc khi ket thuc chuong trinh
	writeBinaryFile(fileBinaryName); // luu lai toan bo du lieu vao file StudentData.dat truoc khi ket thuc chuong trinh
	splitWindow();
	TextColor(12);	gotoXY(70, 10);	cout << "     -- CHUONG TRINH KET THUC --";
	TextColor(14);	gotoXY(70, 11);	cout << "  Cam on ban da su dung chuong trinh";  gotoXY(70, 12); cout << "     Chao tam biet - Hen gap lai";
	TextColor(15);	gotoXY(120, 39); system("pause");
	return 0;
}
		clrscr();
		goto mnc;
}


void programName() {
	gotoXY(0, 0);
	TextColor(14);
	cout << " -- HOC VIEN KY THUAT QUAN SU ( MTA ) --" << endl;
	cout << "    _______________________________" << endl;
	cout << "   |   PHAN MEM QUAN LI SINH VIEN  |" << endl;
	cout << "    *******************************" << endl;
	TextColor(12);	cout << "\n\n ______ MENU ______" << endl; TextColor(15); // in ra menu chinh
	int y = 7;
	for (int i = 0; i < 6; i++) {
		gotoXY(0, y);		cout << MenuChinh[i] << endl;
		y++;
	}
	TextColor(12); gotoXY(0, 19);  cout << " ____ Huong dan ____" << endl; TextColor(15);
	cout << " - Di chuyen: "; TextColor(11); cout << "UP-DOWN" << endl; TextColor(15);
	cout << " - Lua chon : "; TextColor(11); cout << "ENTER" << endl; TextColor(15);
	cout << " - Lat trang: "; TextColor(11); cout << "RIGHT-LEFT" << endl; TextColor(15);
	cout << " - Tro ve   : "; TextColor(11); cout << "ESC";
	TextColor(12); gotoXY(0, 32);	cout << " ____ Thong tin ____" << endl;
	TextColor(15);	cout << " - Nguyen Duc Hung\n - CNTT16B\n - 17150124";

}
int menu(str mangMenu[], int n, int x, int y) { // ---------------------------  Hien thi ra menu va chon menu -----------------------------------------------------
	int tt = 0; // bien chi ta dang o thao tac nao. hien tai tt=0 la thao tac 1
	int *mau = new int[n];
	for (int i = 0; i < n; i++)		mau[i] = MAUCHU;
	mau[0] = MAUNEN; // hien dang o thao tac 1
	TextColor(14);
	programName();
	while (1) {
		TextColor(15);
		int yi = y;
		for (int i = 0; i < n; i++) {
			TextColor(mau[i]);
			gotoXY(x, yi);
			cout << mangMenu[i] << endl;
			yi++;
		}
		gotoXY(x, y);
		int z = _getch();
		BUTTON BUTTON = key(z); // bien trang thai de xac dinh can dua len hay dua xuong
		switch (BUTTON) {
		case UP:
		{
			if (tt == 0)	tt = n - 1;
			else	tt--;
			break;
		}
		case DOWN:
		{
			if (tt == n - 1)		tt = 0;
			else	tt++;
			break;
		}
		case ENTER:
			return tt + 1; // chon thao tac do khi nhan ENTER
		case ESC:
			return NULL;
		}
		// reset lai mau sau khi chon thao tac
		for (int i = 0; i < n; i++)		mau[i] = MAUCHU;
		mau[tt] = MAUNEN;
	}
}
void splitWindow() { // ---------- chia cua so chuong trinh thanh phan Menu va phan Thuc hien chuc nang
	TextColor(15);
	int y = 6;
	for (int i = 0; i < 36; i++) {
		gotoXY(25, y);
		cout << char(186);
		y++;
	}
}
bool checkDate(int day, int month, int year) { //---------------------kiem tra tinh hop le cua ngay thang (so voi lich co that)-----------------------
	if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day >= 1 && day <= 31) && (year >= 1900 && year <= 2016))	return true;
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && (day >= 1 && day <= 30) && (year >= 1900 && year <= 2016))	return true;
	else if (month == 2 && (year >= 1900 && year <= 2016)) { // ktra thang 2 (so sanh voi lich co that)
		/* Dieu kien kiem tra nam nhuan: - TH1: (voi nam co 2 cs tan cung khac 0, VD: 1960 ) --> nam chia het cho 4 nhung khong chia het cho 100
										 - TH2: nam chia het cho 400  (VD: 1600)                                                                    */
		if (((year % 100 != 0 && year % 4 == 0) || (year % 400 == 0)) && (day >= 1 && day <= 29)) return true; // nam nhuan
		else if (!((year % 100 != 0 && year % 4 == 0) || (year % 400 == 0)) && (day >= 1 && day <= 28)) return true; // nam khong nhuan
		else return false;
	}
	else  return false;
}
bool checkID(char ID[]) { // ------------- ktra xem maSV nhap vao da ton tai truoc do hay chua ----------------
	for (Node *p = first; p != NULL; p = p->next) {
		if (strcmp(p->MaSV, ID) == 0) return false;
	}
	return true;
}
char* setID(int k) { //-------------------- nhap du lieu vao (voi toi da k ki tu)---------------------
	char *kq = new char[k + 1]; // tao mang
	int n, i = 0;
tt:	do {
	n = _getch(); // lay ma ASCII
	if (((n >= '0' && n <= '9') || (n >= 'a' && n <= 'z') || (n >= 'A' && n <= 'Z') || n == ' ') && i < k) {
		cout << char(n); // xuat ki tu ra man hinh
		kq[i++] = n; // luu ki tu vao chuoi kq
	}
	else if (n == '\b' && i > 0) { // neu nhan Backspace ma chuoi khong rong
		cout << "\b \b"; // xoa 1 ki tu tren man hinh
		kq[--i] = 0; // xoa 1 ki tu trong chuoi kq
	}
	if (n == 13 && i == 0)  goto tt; // neu nhan Enter ma chuoi chua day
} while (n != 13);
kq[i] = 0;
return kq;
}
void chuanHoaTen(char s[]) { //----------------chuan hoa Ho ten khi nhap vao--------------------------
	// dau xau
	while (s[0] == ' ') strcpy(&s[0], &s[1]);
	// cuoi xau
	while (s[strlen(s) - 1] == ' ')  s[strlen(s) - 1] = '\0';
	// giua
	for (int i = 0; i < strlen(s); i++)
		if (s[i] == ' ' && s[i + 1] == ' ')
		{
			strcpy(&s[i], &s[i + 1]);
			i--;
		}
	strlwr(s); // viet thuong tat ca xau
	s[0] = toupper(s[0]);
	for (int i = 0; i < strlen(s); i++)
		if (s[i] == ' ') s[i + 1] = toupper(s[i + 1]);
}
void chuanHoaID(char s[]) {
	// dau xau
	while (s[0] == ' ') strcpy(&s[0], &s[1]);
	// cuoi xau
	while (s[strlen(s) - 1] == ' ')  s[strlen(s) - 1] = '\0';
	// giua
	for (int i = 0; i < strlen(s); i++) // xoa cac dau cach lien nhau
		if ((s[i] == ' ' && s[i + 1] == ' ') || (s[i] == ' ' && s[i + 1] != ' '))
		{
			strcpy(&s[i], &s[i + 1]);
			i--;
		}
	strupr(s);
}
void newStudent() { //--------------------cap nhat du lieu cho sinh vien moi------------------
	splitWindow();	gotoXY(27, 6);		TextColor(11);		cout << char(205) << char(205) << char(205) << " THEM MOI HO SO " << char(205) << char(205) << char(205);
	TextColor(15);
	gotoXY(28, 8);		TextColor(13);  cout << "Cap nhat du lieu Sinh vien moi: ";   TextColor(15);
	gotoXY(30, 10);		cout << char(218);
	gotoXY(120, 10);	cout << char(191);
	gotoXY(30, 20);		cout << char(192);
	gotoXY(120, 20);	cout << char(217);
	for (int i = 31; i <= 119; i++) { gotoXY(i, 10);	cout << char(196); }
	for (int i = 31; i <= 119; i++) { gotoXY(i, 12);	cout << char(196); }
	for (int i = 31; i <= 119; i++) { gotoXY(i, 14);	cout << char(196); }
	for (int i = 31; i <= 119; i++) { gotoXY(i, 16);	cout << char(196); }
	for (int i = 31; i <= 119; i++) { gotoXY(i, 18);	cout << char(196); }
	for (int i = 31; i <= 119; i++) { gotoXY(i, 20);	cout << char(196); }
	for (int i = 11; i <= 19; i += 2) { gotoXY(30, i);	cout << char(179); }
	for (int i = 11; i <= 19; i += 2) { gotoXY(120, i);	cout << char(179); }
	for (int i = 12; i <= 18; i += 2) { gotoXY(30, i);	cout << char(195); }
	for (int i = 12; i <= 18; i += 2) { gotoXY(120, i);	cout << char(180); }
	for (int i = 11; i <= 19; i += 2) { gotoXY(58, i);  cout << char(179); }
	gotoXY(32, 11);		cout << "Ho va ten";
	gotoXY(32, 13);		cout << "Ngay sinh <dd/mm/yyyy>";
	gotoXY(32, 15);		cout << "Ma sinh vien";
	gotoXY(32, 17);		cout << "Ma Lop";
	gotoXY(32, 19);		cout << "Diem TBTL";
	gotoXY(31, 21);	TextColor(12); cout << "Chu y: ";
	gotoXY(38, 21); TextColor(14); cout << "- Ngay sinh phai ton tai tren lich thuc te cac nam tu 1900 den 2016";
	gotoXY(38, 22); TextColor(14); cout << "- Ma SV phai co 8 ki tu va khong duoc trung voi ma SV cua sinh vien khac"; TextColor(15);
	Node *p = (Node *)malloc(sizeof(Node));
	// nhap Ho ten
	gotoXY(60, 11);	    strcpy(p->HoTen, setID(40));
	gotoXY(60, 11);		cout << "                                              ";
	gotoXY(60, 11);		chuanHoaTen(p->HoTen);		cout << p->HoTen;
	// nhap ngay sinh
	do {
		gotoXY(60, 13);		cout << "                        ";
		gotoXY(60, 13);	    cin >> p->ngaySinh;
		gotoXY(60, 13);		cout << right << setw(2) << setfill('0') << p->ngaySinh << " / ";
		gotoXY(65, 13);		cin >> p->thangSinh;
		gotoXY(65, 13);		cout << right << setw(2) << setfill('0') << p->thangSinh << " / ";
		gotoXY(70, 13);		cin >> p->namSinh;
		gotoXY(70, 13);		cout << p->namSinh;
	} while (checkDate(p->ngaySinh, p->thangSinh, p->namSinh) == false);
	// nhap ma SV
	do {
		gotoXY(60, 15); cout << "        ";
		gotoXY(60, 15);	strcpy(p->MaSV, setID(8));	chuanHoaID(p->MaSV);
	} while ((strlen(p->MaSV) != 8) || (checkID(p->MaSV)) == false);
	// nhap ma Lop
	gotoXY(60, 17);	strcpy(p->MaLop, setID(8));
	gotoXY(60, 17);	cout << "        ";
	chuanHoaID(p->MaLop);
	gotoXY(60, 17);  cout << p->MaLop;
	// nhap diem TBTL
	do {
		gotoXY(60, 19);		cout << "                 ";
		gotoXY(60, 19);		cin >> p->DiemTBTL;
	} while (p->DiemTBTL < 0 || p->DiemTBTL>10);
	gotoXY(60, 19);		cout << right << setw(5) << fixed << setprecision(2) << setfill(' ') << p->DiemTBTL;
	gotoXY(30, 24);		TextColor(11);	cout << "--> Cap nhat du lieu thanh cong";	TextColor(15);
	// them vao cuoi DS
	if (first == NULL) {
		p->next = NULL;
		p->prev = NULL;
		first = last = p;
	}
	else {
		last->next = p;
		p->next = NULL;
		p->prev = last;
		last = p;
	}
	gotoXY(120, 39);		system("pause");
}
void deleteHead() { //-----------------------xoa dau Ds sinh vien--------------------
	Node *temp = first;
	if (first == last) 	first = last = NULL;  // khi DS chi co 1 ptu
	else { // khi DS co nhieu hon 1 ptu
		first = first->next;
		first->prev = NULL;
	}
	free(temp);
}
void deleteTail() {//----------------------xoa duoi Ds sinh vien---------------------------
	Node *temp = last;
	if (first == last) 	first = last = NULL;
	else {
		last = last->prev;
		last->next = NULL;
	}
	free(temp);
}
int length() { //-----------------------tinh do dai Ds sinh vien----------------------------
	int count = 0;
	for (Node *p = first; p != NULL; p = p->next) {
		count++;
	}
	return count;
}
void deletePosition(int position) { //--------------- xoa node tai vtri bat ki trong Ds sinh vien--------------------
	if (position == 1)				 	deleteHead();
	else if (position == length())		deleteTail();
	else {
		Node *p = first;
		for (int i = 1; i < position - 1; i++)	p = p->next;
		Node *temp;
		temp = p->next;
		((p->next)->next)->prev = p;
		p->next = (p->next)->next;
		free(temp);
	}
}
void redoEdit(int position) {//----------------------chinh sua 1 ho so-----------------------------
	clrscr(); programName(); splitWindow(); gotoXY(27, 6); TextColor(11);	cout << char(205) << char(205) << char(205) << " CHINH SUA HO SO " << char(205) << char(205) << char(205);	TextColor(15);
	Node *p;
	if (position == 1)	p = first;
	else if (position == length())	p = last;
	else {
		p = first;
		for (int i = 0; i < position - 1; i++)	p = p->next;
	}
	gotoXY(28, 8);		TextColor(13);   cout << "Chinh sua thong tin Sinh vien: ";   TextColor(15);
	gotoXY(30, 10);		cout << char(218);
	gotoXY(120, 10);	cout << char(191);
	gotoXY(30, 20);		cout << char(192);
	gotoXY(120, 20);	cout << char(217);
	for (int i = 31; i <= 119; i++) { gotoXY(i, 10);	cout << char(196); }
	for (int i = 31; i <= 119; i++) { gotoXY(i, 12);	cout << char(196); }
	for (int i = 31; i <= 119; i++) { gotoXY(i, 14);	cout << char(196); }
	for (int i = 31; i <= 119; i++) { gotoXY(i, 16);	cout << char(196); }
	for (int i = 31; i <= 119; i++) { gotoXY(i, 18);	cout << char(196); }
	for (int i = 31; i <= 119; i++) { gotoXY(i, 20);	cout << char(196); }
	for (int i = 11; i <= 19; i += 2) { gotoXY(30, i);	cout << char(179); }
	for (int i = 11; i <= 19; i += 2) { gotoXY(120, i);	cout << char(179); }
	for (int i = 12; i <= 18; i += 2) { gotoXY(30, i);	cout << char(195); }
	for (int i = 12; i <= 18; i += 2) { gotoXY(120, i);	cout << char(180); }
	for (int i = 11; i <= 19; i += 2) { gotoXY(58, i);  cout << char(179); }
	gotoXY(31, 21);	TextColor(12); cout << "Chu y: ";
	gotoXY(38, 21); TextColor(14); cout << "- Ngay sinh phai ton tai tren lich thuc te cac nam tu 1900 den 2016";
	gotoXY(38, 22); TextColor(14); cout << "- Ma SV phai co 8 ki tu va khong duoc trung voi ma SV cua sinh vien khac"; TextColor(15);
	// === in lai du lieu cu
	gotoXY(32, 11);	cout << "Ho va ten";	gotoXY(60, 11);	cout << p->HoTen;	gotoXY(84, 11); cout << "|>>>";
	gotoXY(32, 13);	cout << "Ngay sinh <dd/mm/yyyy>";
	gotoXY(60, 13);		cout << right << setw(2) << setfill('0') << p->ngaySinh << " / ";
	gotoXY(65, 13);		cout << right << setw(2) << setfill('0') << p->thangSinh << " / ";
	gotoXY(70, 13);		cout << p->namSinh;		gotoXY(84, 13); cout << "|>>>";
	gotoXY(32, 15);	cout << "Ma sinh vien";		gotoXY(60, 15);	cout << p->MaSV;	gotoXY(84, 15); cout << "|>>>";
	gotoXY(32, 17);	cout << "Ma Lop";			gotoXY(60, 17);	cout << p->MaLop;	gotoXY(84, 17); cout << "|>>>";
	gotoXY(32, 19);	cout << "Diem TBTL";		gotoXY(60, 19);	cout << right << setw(5) << fixed << setprecision(2) << setfill(' ') << p->DiemTBTL;	gotoXY(84, 19); cout << "|>>>";
	// === Nhap du lieu moi ===
	// nhap Ho ten
	gotoXY(90, 11);		strcpy(p->HoTen, setID(40));
	gotoXY(90, 11);		cout << "                            ";
	gotoXY(90, 11);		chuanHoaTen(p->HoTen);		cout << p->HoTen;
	// nhap ngay sinh
	do {
		gotoXY(90, 13);		cout << "                ";
		gotoXY(90, 13);	    cin >> p->ngaySinh;
		gotoXY(90, 13);		cout << right << setw(2) << setfill('0') << p->ngaySinh << " / ";
		gotoXY(95, 13);		cin >> p->thangSinh;
		gotoXY(95, 13);		cout << right << setw(2) << setfill('0') << p->thangSinh << " / ";
		gotoXY(100, 13);	cin >> p->namSinh;
		gotoXY(100, 13); cout << p->namSinh;
	} while (checkDate(p->ngaySinh, p->thangSinh, p->namSinh) == false);
	// nhap ma SV
	char msv[9];
	do {
		gotoXY(90, 15);	cout << "        ";
		gotoXY(90, 15); strcpy(msv, setID(8));	chuanHoaID(msv);
		if (strcmp(msv, p->MaSV) == 0) break;
	} while ((strlen(msv) != 8) || (checkID(msv) == false));
	strcpy(p->MaSV, msv);  gotoXY(90, 15); cout << p->MaSV;
	// nhap ma Lop
	gotoXY(90, 17); strcpy(p->MaLop, setID(8));
	gotoXY(90, 17); cout << "        "; chuanHoaID(p->MaLop);
	gotoXY(90, 17); cout << p->MaLop;
	// nhap diem TBTL
	do {
		gotoXY(90, 19);		cout << "                 ";
		gotoXY(90, 19);		cin >> p->DiemTBTL;
	} while (p->DiemTBTL < 0 || p->DiemTBTL>10);
	gotoXY(90, 19);		cout << right << setw(5) << fixed << setprecision(2) << setfill(' ') << p->DiemTBTL;
	gotoXY(30, 24);		TextColor(11);	cout << " --> Chinh sua ho so thanh cong!";	TextColor(15); gotoXY(120, 39);  system("pause");
}
void paintInfo(Node *p, int stt, int yi, int color) { // ---------- to mau noi bat 1 dong hien thi thong tin sinh vien---------------------------------
	TextColor(color);
	gotoXY(34, yi);  cout << stt;
	gotoXY(42, yi);	 cout << p->HoTen;
	gotoXY(68, yi);	 cout << right << setw(2) << setfill('0') << p->ngaySinh << "/ ";
	gotoXY(72, yi);  cout << right << setw(2) << setfill('0') << p->thangSinh << "/ ";
	gotoXY(76, yi);  cout << p->namSinh;
	gotoXY(87, yi);  cout << p->MaSV;
	gotoXY(103, yi); cout << p->MaLop;
	gotoXY(119, yi); cout << right << setw(5) << fixed << setprecision(2) << setfill(' ') << p->DiemTBTL;
	TextColor(7);
}
void rowInfo() { //------------------------ hang thong tin sinh vien  "| STT  |  Ho va ten   |  Ngay sinh  |  Ma SV    |  Ma Lop    |  Diem TBTL |" -------------------
	gotoXY(32, 8);	cout << char(218);	gotoXY(131, 8); cout << char(191);
	for (int i = 33; i <= 130; i++) { gotoXY(i, 8);	cout << char(196); }
	for (int i = 33; i <= 130; i++) { gotoXY(i, 10);	cout << char(196); }
	gotoXY(32, 10);	cout << char(192);	gotoXY(131, 10); cout << char(217);
	gotoXY(32, 9);	cout << char(179);  gotoXY(131, 9);	cout << char(179);
	gotoXY(33, 9);	cout << " STT  |  Ho va ten              |  Ngay sinh       |  Ma SV        |  Ma Lop       |  Diem TBTL";

}
int totalNumPage() { // ---------- Tinh tong so trang in trong Danh sach sinh vien ------------------
	if (length() % 10 == 0)		return (length() / 10);
	else	return (length() / 10 + 1);
}
int doList(int sttDau, int sttCuoi, Node *start, Node *end) { // ------ Lam viec voi Ds, di chuyen con tro, lat trang, chon dong ---------------------
	Node *p = start;
	int stt = sttDau;
	int y = 11;
	paintInfo(p, sttDau, 11, 14);
	while (1) {
		int z = _getch();
		BUTTON move = key(z);
		switch (move) {
		case UP:
			if (p != start) {
				paintInfo(p, stt, y, 7); // reset lai mau cho dong duoc show truoc do
				p = p->prev;
				stt--;
				y -= 2;
				paintInfo(p, stt, y, 14); // to mau cho dong dang duoc show				
			}
			else {
				paintInfo(p, stt, y, 7); // reset lai mau cho dong duoc show truoc do
				p = end;
				stt = sttCuoi;
				y = 11 + (sttCuoi - sttDau) * 2;
				paintInfo(p, stt, y, 14); // to mau cho dong dang duoc show
			}
			break;
		case DOWN:
			if (p != end) {
				paintInfo(p, stt, y, 7); // reset lai mau cho dong duoc show truoc do
				p = p->next;
				stt++;
				y += 2;
				paintInfo(p, stt, y, 14); // to mau cho dong dang duoc show
			}
			else {
				paintInfo(p, stt, y, 7); // reset lai mau cho dong duoc show truoc do
				p = start;
				stt = sttDau;
				y = 11;
				paintInfo(p, stt, y, 14); // to mau cho dong dang duoc show
			}
			break;
		case LEFT:
			return 999999975;
		case RIGHT:
			return 999999977;
		case ENTER:
			return stt;
		case ESC:
			return 999999999;
		}
	}
}
void display(Node *start, char info[]) { //-------------------------hien thi ds sinh vien--------------------- tu vtri start
	clrscr(); programName(); splitWindow(); gotoXY(27, 6);	TextColor(11); cout << char(205) << char(205) << " DANH SACH SINH VIEN " << char(205) << char(205);
	TextColor(15); cout << "  So luong sinh vien: " << length(); TextColor(13); cout << info; TextColor(15);
	ToMau(0, 8, MenuChinh[1], 10);
	rowInfo();
	if (first == NULL) { // Ktra neu Ds rong -----> Ket thuc ham
		gotoXY(32, 14);  system("pause");
		return;
	}
	// -------- tinh stt cua sinh vien dau trang in ----------------
	int sttDau = 0;
	if (start == first)	 sttDau = 1;
	else if (start == last)  sttDau = length();
	else {
		for (Node *temp = start; temp != NULL; temp = temp->prev)	sttDau++;
	}
	// -------- tinh trang Dang Xem la trang thu may ---------------
	int currentPage = (sttDau - 1) / 10 + 1;
	// -------- tinh stt cua sinh vien cuoi trang in ------------------
	int sttCuoi = sttDau;
	Node *end = start; // end se tro den vtri cuoi trang in
	for (int i = 1; i <= 9; i++) {
		if (end == last)  break;
		end = end->next; // end tro den vtri cuoi cung cua trang in
		sttCuoi++;
	}
	// ---------- in trang Ds (toi da 10 sv trong 1 trang) ----------------
	Node *p = start;
	int y = 11, stt = sttDau;
	for (int i = 1; i <= 10; i++) { // in toi da 10 sv trong 1 trang
		if (p == NULL) break;
		gotoXY(32, y + 1);	cout << char(192);	gotoXY(131, y + 1); cout << char(217);
		gotoXY(32, y);	cout << char(179);  gotoXY(131, y);	cout << char(179);
		gotoXY(33, y);  cout << "      |                         |    /   /         |               |               |";
		for (int i = 33; i <= 130; i++) { gotoXY(i, y + 1);	cout << char(196); }
		gotoXY(34, y);	cout << stt;
		gotoXY(42, y); cout << p->HoTen;
		gotoXY(68, y); cout << right << setw(2) << setfill('0') << p->ngaySinh;
		gotoXY(72, y); cout << right << setw(2) << setfill('0') << p->thangSinh;
		gotoXY(76, y); cout << p->namSinh;
		gotoXY(87, y); cout << p->MaSV;
		gotoXY(103, y); cout << p->MaLop;
		gotoXY(119, y); cout << right << setw(5) << fixed << setprecision(2) << setfill(' ') << p->DiemTBTL;
		y += 2;
		stt++;
		p = p->next;
	}
	gotoXY(72, 32);	cout << "-- Trang " << currentPage << " / " << totalNumPage() << " --";
	gotoXY(32, 36);	TextColor(12); cout << "Chu y: ";
	gotoXY(39, 36); TextColor(14); cout << "Chon Sua (Xoa) thong tin sinh vien: nhan "; TextColor(11); cout << "ENTER";
	// ============= Di chuyen con tro (Len-Xuong) de xem ro tung dong, Lat trang (Trai-Phai), Chon de sua-xoa(Enter) ================================
	int pos = doList(sttDau, sttCuoi, start, end);
	switch (pos) {
	case 999999975: // ---------- Lat trang in truoc (LEFT) ------------
		if (currentPage == 1) {
			Node *begin = first;
			for (int i = 1; i <= (totalNumPage() - 1) * 10; i++)  begin = begin->next;
			display(begin, info);
		}
		else  display(start->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev, info);
		break;
	case 999999977: // ---------- Lat trang in sau (RIGHT) --------------
		if (currentPage == totalNumPage()) {
			display(first, info);
		}
		else  display(end->next, info);
		break;
	case 999999999: // ---------- Quay ve menu chinh (ESC) --------------
		return;
	default: // ----------------- Chon dong (ENTER) de Xoa(Sua) ---------------------
		gotoXY(133, 11 + 2 * (pos - sttDau)); TextColor(11); cout << "--> Chon thao tac:";
		switch (menu(Menu2a, 2, 137, 12 + 2 * (pos - sttDau))) {
		case 1:
			redoEdit(pos);
			break;
		case 2:
			if (pos == sttDau) {
				if ((start == last) && (start != first)) {
					start = start->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev;
				}
				else start = start->next; // Ds in bat dau tu Start ---> phai co Start moi thay the truoc khi xoa Start
			}
			deletePosition(pos);
			break;
		}
		display(start, info); // In lai Ds sau khi Xoa (Sua)
	}
}
void swap(Node *p1, Node *p2) { // -------- Doi vtri 2 sinh vien cho nhau ------------------
	char tempht[41]; // swap ho ten
	strcpy(tempht, p1->HoTen);
	strcpy(p1->HoTen, p2->HoTen);
	strcpy(p2->HoTen, tempht);
	int temp; // swap ngay sinh
	temp = p1->ngaySinh;
	p1->ngaySinh = p2->ngaySinh;
	p2->ngaySinh = temp;
	temp = p1->thangSinh;
	p1->thangSinh = p2->thangSinh;
	p2->thangSinh = temp;
	temp = p1->namSinh;
	p1->namSinh = p2->namSinh;
	p2->namSinh = temp;
	char tempID[9]; // swap masv, maLop
	strcpy(tempID, p1->MaSV);
	strcpy(p1->MaSV, p2->MaSV);
	strcpy(p2->MaSV, tempID);
	strcpy(tempID, p1->MaLop);
	strcpy(p1->MaLop, p2->MaLop);
	strcpy(p2->MaLop, tempID);
	float tempd; // swap diem tbtl
	tempd = p1->DiemTBTL;
	p1->DiemTBTL = p2->DiemTBTL;
	p2->DiemTBTL = tempd;
}
int compareStrName(char s1[], char s2[]) { // so sanh 2 xau ki tu hoTen:  giong nhau --> (0), khac nhau --> (1)
	// tach tu trong s1
	char name1[41];
	strcpy(name1, s1);
	int count1 = 0;
	char tu1[5][10];
	char *t1 = strtok(name1, " ");
	while (t1 != NULL) {
		strcpy(tu1[count1], t1);
		t1 = strtok(NULL, " ");
		count1++;
	}
	// tach tu trong s2
	char name2[41];
	strcpy(name2, s2);
	int count2 = 0;
	char tu2[5][10];
	char *t2 = strtok(name2, " ");
	while (t2 != NULL) {
		strcpy(tu2[count2], t2);
		t2 = strtok(NULL, " ");
		count2++;
	}
	// so sanh 2 hoTen, so sanh so tu truoc
	if (count1 != count2)	return 1; // so tu khac nhau --> 2 ten khac nhau
	else { // so tu bang nhau, so sanh tung tu xem co giong nhau hay khong
		for (int i = 0; i < count1; i++) {
			if (strcmp(tu1[i], tu2[i]) != 0)	return 1; // co tu khac nhau --> 2 ten khac nhau
		}
		return 0; // so tu bang nhau, cac tu giong nhau --> 2 ten giong nhau
	}
}
int compareName(Node *p1, Node *p2) { // ----------- so sanh 2 ho ten cua p1,p2. Neu: <  --> (-1); neu > --> (1); neu = -->(0)
	// tach p1->Hoten thanh ho, dem, ten
	char name1[41];
	strcpy(name1, p1->HoTen);
	int count1 = 0;
	char tu1[5][10];
	char *t1 = strtok(name1, " ");
	while (t1 != NULL) {
		strcpy(tu1[count1], t1);
		t1 = strtok(NULL, " ");
		count1++;
	}
	// tach p2->HoTen thanh ho, dem, ten
	char name2[41];
	strcpy(name2, p2->HoTen);
	int count2 = 0;
	char tu2[5][10];
	char *t2 = strtok(name2, " ");
	while (t2 != NULL) {
		strcpy(tu2[count2], t2);
		t2 = strtok(NULL, " ");
		count2++;
	}
	// so sanh 2 hoTen, so sanh ten truoc
	if (strcmp(tu1[count1 - 1], tu2[count2 - 1]) > 0)	return 1;
	else if (strcmp(tu1[count1 - 1], tu2[count2 - 1]) < 0)   return -1;
	else { // ten giong nhau --> so sanh dem
		if (strcmp(tu1[count1 - 2], tu2[count2 - 2]) > 0)	return 1;
		else if (strcmp(tu1[count1 - 2], tu2[count2 - 2]) < 0)  return -1;
		else { // ten, dem giong nhau --> so sanh ho
			if (strcmp(tu1[0], tu2[0]) > 0)  return 1;
			else if (strcmp(tu1[0], tu2[0]) < 0)  return -1;
			else return 0; // ten, dem, ho giong nhau --> 2 ho ten giong nhau
		}
	}
}
int compareDate(Node *p1, Node *p2) { //----- So sanh 2 ngay sinh cua p1,p2. Neu: p1 truoc p2 --> (1); p1 sau p2 --> (-1); p1 bang p2 --> (0)
	// so sanh namSinh truoc
	if (p1->namSinh > p2->namSinh)	return 1;
	else if (p1->namSinh < p2->namSinh)	return -1;
	else { // namSinh bang nhau --> so sanh thangSinh
		if (p1->thangSinh > p2->thangSinh)	return 1;
		else if (p1->thangSinh < p2->thangSinh)	return -1;
		else { // namSinh, thangSinh bang nhau --> so sanh ngaySinh
			if (p1->ngaySinh > p2->ngaySinh) return 1;
			else if (p1->ngaySinh < p2->ngaySinh) return -1;
			else return 0; // namSinh, thangSinh, ngaySinh bang nhau ---> 2 ngay sinh bang nhau
		}
	}
}
int comparePointerPosition(Node *p1, Node *p2) { //---- So sanh vtri 2 con tro p1,p2. Neu: p1 truoc p2 --> (-1); p1 sau p2 --> (1); p1 trung p2 --> (0)
	if (p1 == p2)	return 0;
	else {
		for (Node *p = p1; p != NULL; p = p->next) {
			if (p == p2)	return -1;
		}
		return 1;
	}
}
int compareMix(Node *p1, Node *p2) { // ---------- so sanh 2 sv theo hon hop cac truong,theo thu tu uu tien: Ma Lop > Ho ten > Ngay sinh
	// so sanh ma Lop truoc
	if (strcmp(p1->MaLop, p2->MaLop) > 0)	return 1;
	else if (strcmp(p1->MaLop, p2->MaLop) < 0)	return -1;
	else { // ma Lop giong nhau --> so sanh ho ten
		if (compareName(p1, p2) > 0)	return 1;
		else if (compareName(p1, p2) < 0)	return -1;
		else { // ma Lop, ho ten giong nhau --> so sanh ngay sinh
			if (compareDate(p1, p2) > 0)	return 1;
			else if (compareDate(p1, p2) < 0)	return -1;
			else	return 0; // ma Lop, ho ten, ngay sinh giong nhau --> 2 sv giong nhau
		}
	}
}
void selectionSort(int choice) { //-------------- sap xep lua chon -----------------
	for (Node *p1 = first; p1 != NULL; p1 = p1->next) {
		for (Node *p2 = p1->next; p2 != NULL; p2 = p2->next) {
			switch (choice) {
			case 1:
				if (strcmp(p1->MaSV, p2->MaSV) > 0)  swap(p1, p2);
				break;
			case 2:
				if (strcmp(p1->MaLop, p2->MaLop) > 0)  swap(p1, p2);
				break;
			case 3:
				if (compareName(p1, p2) > 0) swap(p1, p2);
				break;
			case 4:
				if (compareDate(p1, p2) > 0)  swap(p1, p2);
				break;
			case 5:
				if (p1->DiemTBTL < p2->DiemTBTL)  swap(p1, p2);
				break;
			case 6:
				if (compareMix(p1, p2) > 0)  swap(p1, p2);
			}
		}
	}
}
void insertionSort(int choice) { // ------------------ sap xep chen ----------------------------
	/*
	int j,temp;
	for(int i=1; i<n; i++){
		j=i-1;
		temp=a[i];
		while(temp<a[j] && j>=0){
			a[j+1] = a[j];
			j--;
		}
		a[j+1]=temp;
	}
	*/
	Node *p2;
	Node *temp;
	for (Node *p1 = first->next; p1 != NULL; p1 = p1->next) {
		p2 = p1->prev;
		temp = p1;
		switch (choice) {
		case 1:
			while ((strcmp(temp->MaSV, p2->MaSV) < 0) && (p2 != first)) {
				swap(temp, p2);
				p2 = p2->prev;
				temp = temp->prev;
			}
			if (strcmp(temp->MaSV, p2->MaSV) < 0)	swap(temp, p2);
			break;
		case 2:
			while ((strcmp(temp->MaLop, p2->MaLop) < 0) && (p2 != first)) {
				swap(temp, p2);
				p2 = p2->prev;
				temp = temp->prev;
			}
			if (strcmp(temp->MaLop, p2->MaLop) < 0)	swap(temp, p2);
			break;
		case 3:
			while ((compareName(temp, p2) < 0) && (p2 != first)) {
				swap(temp, p2);
				p2 = p2->prev;
				temp = temp->prev;
			}
			if (compareName(temp, p2) < 0)	swap(temp, p2);
			break;
		case 4:
			while ((compareDate(temp, p2) < 0) && (p2 != first)) {
				swap(temp, p2);
				p2 = p2->prev;
				temp = temp->prev;
			}
			if (compareDate(temp, p2) < 0)	swap(temp, p2);
			break;
		case 5:
			while ((temp->DiemTBTL > p2->DiemTBTL) && (p2 != first)) {
				swap(temp, p2);
				p2 = p2->prev;
				temp = temp->prev;
			}
			if (temp->DiemTBTL > p2->DiemTBTL)	swap(temp, p2);
			break;
		case 6:
			while ((compareMix(temp, p2) < 0) && (p2 != first)) {
				swap(temp, p2);
				p2 = p2->prev;
				temp = temp->prev;
			}
			if (compareMix(temp, p2) < 0)	swap(temp, p2);
			break;
		}
	}
}
void bubbleSort(int choice) { // --------------------- sap xep noi bot -----------------------------
	for (Node *p1 = first; p1 != last; p1 = p1->next) {
		for (Node *p2 = last; p2 != p1; p2 = p2->prev) {
			switch (choice) {
			case 1:
				if (strcmp(p2->MaSV, (p2->prev)->MaSV) < 0)  swap(p2, p2->prev);
				break;
			case 2:
				if (strcmp(p2->MaLop, (p2->prev)->MaLop) < 0)  swap(p2, p2->prev);
				break;
			case 3:
				if (compareName(p2, p2->prev) < 0)  swap(p2, p2->prev);
				break;
			case 4:
				if (compareDate(p2, p2->prev) < 0)  swap(p2, p2->prev);
				break;
			case 5:
				if (p2->DiemTBTL > (p2->prev)->DiemTBTL)  swap(p2, p2->prev);
				break;
			case 6:
				if (compareMix(p2, p2->prev) < 0)  swap(p2, p2->prev);
				break;
			}
		}
	}
}
Node * element(int pos){
	if (pos == 1)	return first;
	else if (pos == length())	return last;
	else {
		Node *p = first;
		for (int i = 1; i < pos; i++)	p = p->next;
		return p;
	}
}
int partition(int choice, int left, int right)
{
	Node *X = element(left);
	int i = left + 1;
	int j = right;
	do {
		switch (choice) {
		case 1:
			while ((i <= j) && (strcmp(element(i)->MaSV, X->MaSV) <= 0))	i++;
			while ((i <= j) && (strcmp(element(j)->MaSV, X->MaSV) > 0))		j--;
			break;
		case 2:
			while ((i <= j) && (strcmp(element(i)->MaLop, X->MaLop) <= 0))	i++;
			while ((i <= j) && (strcmp(element(j)->MaLop, X->MaLop) > 0))	j--;
			break;
		case 3:
			while ((i <= j) && (compareName(element(i), X) <= 0))	i++;
			while ((i <= j) && (compareName(element(j), X) > 0))	j--;
			break;
		case 4:
			while ((i <= j) && (compareDate(element(i), X) <= 0))	i++;
			while ((i <= j) && (compareDate(element(j), X) > 0))	j--;
			break;
		case 5:
			while ((i <= j) && (element(i)->DiemTBTL >= X->DiemTBTL))	i++;
			while ((i <= j) && (element(j)->DiemTBTL < X->DiemTBTL))	j--;
			break;
		case 6:
			while ((i <= j) && (compareMix(element(i), X) <= 0))	i++;
			while ((i <= j) && (compareMix(element(j), X) > 0))	j--;
			break;
		}
		if (i < j) {
			swap(element(i), element(j));
			i++;
			j--;
		}
	} while (i <= j);
	swap(element(left), element(j));
	return j;
}
void quickSort(int choice, int left, int right)
{
	int k;
	if (left < right) {
		k = partition(choice, left, right);
		quickSort(choice, left, k - 1);
		quickSort(choice, k + 1, right);
	}
}
char* enterSearchChar(int choice) { // ------------- nhap thong tin can tim kiem kieu char: ma sv, ma Lop, hoten ------------------------
	char hoten[41], masv[9], maLop[9], random[41];
	switch (choice) {
	case 0: // nhap maSv de tim (khong can du 8 ki tu) _ Dung cho tim kiem gan chinh xac
		gotoXY(34, 9); cout << "Tim theo Ma sinh vien";
		gotoXY(63, 9); strcpy(masv, setID(8));
		return masv;
	case 1: // nhap maSv de tim (phai co du 8 ki tu) _ Dung cho tim kiem chinh xac
		gotoXY(34, 9); cout << "Tim theo Ma sinh vien";
		gotoXY(33, 11); TextColor(12); cout << "Chu y: "; TextColor(14); cout << "Ma sinh vien phai co 8 ki tu"; TextColor(15);
		do {
			gotoXY(63, 9);	cout << "        "; gotoXY(63, 9);
			strcpy(masv, setID(8));
		} while (strlen(masv) != 8);
		return masv;
	case 2: // nhap maLop de tim _ Dung cho ca tim kiem chinh xac va tim kiem gan chinh xac
		gotoXY(34, 9); cout << "Tim theo Ma Lop ";
		gotoXY(63, 9); strcpy(maLop, strupr(setID(8)));
		return maLop;
	case 3: // nhap hoTen de tim (tu dong chuan hoa ten) _ Dung cho tim kiem chinh xac
		gotoXY(34, 9); cout << "Tim theo Ho va ten ";
		gotoXY(63, 9);	strcpy(hoten, setID(40)); chuanHoaTen(hoten);
		return hoten;
	case 4: // nhap hoTen de tim (khong tu dong chuan hoa ten) _ Dung cho tiem kiem gan chinh xac
		gotoXY(34, 9); cout << "Tim theo Ho va ten ";
		gotoXY(63, 9);	strcpy(hoten, setID(40));
		return hoten;
	case 5: // nhap du lieu ngau nhien de tim kiem (khong can quan tam den truong) _ Dung cho tim kiem ngau nhien
		gotoXY(34, 9); cout << "Tim theo noi dung ";
		gotoXY(63, 9);	strcpy(random, setID(40));
		return random;
	}
}
float enterSearchNum(int choice) { // ------------- nhap thong tin can tim kiem kieu so: ngaysinh, thangsinh, namsinh, diemtbtl ----------------
	float num;
	cout << setprecision(0);
	switch (choice) {
	case 1: // nhap ngaySinh de tim kiem
		gotoXY(33, 11); TextColor(12); cout << "Chu y: "; TextColor(14); cout << "Ngay sinh phai ton tai tren lich thuc te cac nam tu 1900 den 2016"; TextColor(15);
		gotoXY(34, 9); cout << "Tim theo Ngay sinh";
		gotoXY(63, 9); cin >> num;
		gotoXY(63, 9); cout << right << setw(2) << setfill('0') << num << "/ ";
		return num;
	case 2: // nhap thangSinh de tim kiem
		gotoXY(33, 11); TextColor(12); cout << "Chu y: "; TextColor(14); cout << "Ngay sinh phai ton tai tren lich thuc te cac nam tu 1900 den 2016"; TextColor(15);
		gotoXY(34, 9); cout << "Tim theo Ngay sinh";
		gotoXY(67, 9); cin >> num;
		gotoXY(67, 9); cout << right << setw(2) << setfill('0') << num << "/ ";
		return num;
	case 3: // nhap namSinh de tim kiem
		gotoXY(33, 11); TextColor(12); cout << "Chu y: "; TextColor(14); cout << "Ngay sinh phai ton tai tren lich thuc te cac nam tu 1900 den 2016"; TextColor(15);
		gotoXY(34, 9); cout << "Tim theo Ngay sinh";
		gotoXY(71, 9); cin >> num;
		gotoXY(71, 9); cout << num;
		return num;
	case 4: // nhap diemTbtl de tim kiem
		gotoXY(34, 9); cout << "Tim theo Diem TBTL ";
		do {
			gotoXY(63, 9);		cout << "                          ";
			gotoXY(63, 9);		cin >> num;
		} while (num < 0 || num>10);
		gotoXY(63, 9);	cout << right << setprecision(2) << right << setw(5) << setfill(' ') << num;
		return num;
	}
}
void paintInfoFound(Node *p, int stt, int yi, int color) { // ---------- to mau noi bat 1 dong hien thi thong tin sinh vien tim duoc---------------------------------
	TextColor(color);
	gotoXY(34, yi);  cout << stt;
	gotoXY(42, yi);  cout << p->HoTen;
	gotoXY(68, yi);  cout << right << setw(2) << setfill('0') << p->ngaySinh;
	gotoXY(72, yi);  cout << right << setw(2) << setfill('0') << p->thangSinh;
	gotoXY(76, yi);  cout << p->namSinh;
	gotoXY(87, yi);  cout << p->MaSV;
	gotoXY(103, yi); cout << p->MaLop;
	gotoXY(119, yi); cout << right << setw(5) << setfill(' ') << fixed << setprecision(2) << p->DiemTBTL;
	TextColor(7);
}
int doListFound(int sttDau, int sttCuoi, Node *start, Node *end) { // ------ Lam viec voi Ds sinh vien tim duoc, di chuyen con tro, lat trang, chon dong ---------------------
	Node *p = start;
	int stt = sttDau;
	int y = 11;
	paintInfoFound(p, sttDau, 11, 14);
	while (1) {
		int z = _getch();
		BUTTON move = key(z);
		switch (move) {
		case UP:
			if (p != start) {
				paintInfoFound(p, stt, y, 7); // reset lai mau cho dong duoc show truoc do
				p = p->prev;
				stt--;
				y -= 2;
				paintInfoFound(p, stt, y, 14); // to mau cho dong dang duoc show				
			}
			else {
				paintInfoFound(p, stt, y, 7); // reset lai mau cho dong duoc show truoc do
				p = end;
				stt = sttCuoi;
				y = 11 + (sttCuoi - sttDau) * 2;
				paintInfoFound(p, stt, y, 14); // to mau cho dong dang duoc show
			}
			break;
		case DOWN:
			if (p != end) {
				paintInfoFound(p, stt, y, 7); // reset lai mau cho dong duoc show truoc do
				p = p->next;
				stt++;
				y += 2;
				paintInfoFound(p, stt, y, 14); // to mau cho dong dang duoc show
			}
			else {
				paintInfoFound(p, stt, y, 7); // reset lai mau cho dong duoc show truoc do
				p = start;
				stt = sttDau;
				y = 11;
				paintInfoFound(p, stt, y, 14); // to mau cho dong dang duoc show
			}
			break;
		case LEFT:
			return 999999975;
		case RIGHT:
			return 999999977;
			/*case ENTER:
				return stt;*/
		case ESC:
			return 999999999;
		}
	}
}
int lengthFound() {
	int count = 0;
	for (Node *p = ffirst; p != NULL; p = p->next) {
		count++;
	}
	return count;
}
int totalNumPageFound() { // ---------- Tinh tong so trang in trong Danh sach sinh vien ------------------
	if (lengthFound() % 10 == 0)		return (lengthFound() / 10);
	else	return (lengthFound() / 10 + 1);
}
void displayFound(int choice, int key, Node *start, char noidung[], int ngay, int thang, int nam, float diemtb) { // hien thi ra thong tin tim kiem duoc
	clrscr(); programName(); splitWindow(); gotoXY(27, 6);	TextColor(11); cout << char(205) << char(205) << " TIM KIEM THONG TIN " << char(205) << char(205); gotoXY(54, 6); TextColor(13);
	switch (choice) { // In ra Header
	case 1: //------------- Tim kiem Tuan tu >>  Tim kiem chinh xac --------------
		switch (key) {
		case 1: cout << ">> Tim kiem chinh xac"; TextColor(15); cout << "    >> Ma sinh vien: "; TextColor(10); cout << noidung; TextColor(15); break;
		case 2: cout << ">> Tim kiem chinh xac"; TextColor(15); cout << "    >> Ma lop: "; TextColor(10); cout << noidung; TextColor(15); break;
		case 3: cout << ">> Tim kiem chinh xac"; TextColor(15); cout << "    >> Ho ten: "; TextColor(10); cout << noidung; TextColor(15); break;
		case 4: cout << ">> Tim kiem chinh xac"; TextColor(15); cout << "    >> Ngay sinh: "; TextColor(10);
			cout << right << setw(2) << setfill('0') << ngay << "/ ";
			cout << right << setw(2) << setfill('0') << thang << "/ ";
			cout << nam; TextColor(15); break;
		case 5: cout << ">> Tim kiem chinh xac"; TextColor(15); cout << "    >> Diem TBTL: "; TextColor(10); printf("%.2f", diemtb); TextColor(15); break;
		}
		break;
	case 2: // -------------  Tim kiem tuan tu >> Tim kiem gan chinh xac --------------
		switch (key) {
		case 1: cout << ">> Tim kiem gan chinh xac"; TextColor(15); cout << "    >> Ma sinh vien: "; TextColor(10); cout << noidung; TextColor(15); break;
		case 2: cout << ">> Tim kiem gan chinh xac"; TextColor(15); cout << "    >> Ma lop: "; TextColor(10); cout << noidung; TextColor(15); break;
		case 3: cout << ">> Tim kiem gan chinh xac"; TextColor(15); cout << "    >> Ho ten: "; TextColor(10); cout << noidung; TextColor(15); break;
		case 4: cout << ">> Tim kiem gan chinh xac"; TextColor(15); cout << "    >> Ngay sinh: "; TextColor(10);
			cout << right << setw(2) << setfill('0') << ngay << "/ ";
			cout << right << setw(2) << setfill('0') << thang << "/ ";
			cout << nam; TextColor(15); break;
		case 5: cout << ">> Tim kiem gan chinh xac"; TextColor(15); cout << "    >> Diem TBTL: "; TextColor(10); printf("%.2f", diemtb); TextColor(15); break;
		}
		break;
	case 3: // ------------- Tim kiem tuan tu >> Tim kiem ngau nhien ------------------
		if (key == 0) cout << ">> Tim kiem ngau nhien"; TextColor(15); cout << "   >> Noi dung: "; TextColor(10); cout << noidung; TextColor(15); break;
	case 4: // ------------- Tim kiem Nhi phan ----------------------------------------
		switch (key) {
		case 1: cout << ">> Tim kiem Nhi phan"; TextColor(15); cout << "    >> Ma sinh vien: "; TextColor(10); cout << noidung; TextColor(15); break;
		case 2: cout << ">> Tim kiem Nhi phan"; TextColor(15); cout << "    >> Ma lop: "; TextColor(10); cout << noidung; TextColor(15); break;
		case 3: cout << ">> Tim kiem Nhi phan"; TextColor(15); cout << "    >> Ho ten: "; TextColor(10); cout << noidung; TextColor(15); break;
		case 4: cout << ">> Tim kiem Nhi phan"; TextColor(15); cout << "    >> Ngay sinh: "; TextColor(10);
			cout << right << setw(2) << setfill('0') << ngay << "/ ";
			cout << right << setw(2) << setfill('0') << thang << "/ ";
			cout << nam; TextColor(15); break;
		case 5: cout << ">> Tim kiem Nhi phan"; TextColor(15); cout << "    >> Diem TBTL: "; TextColor(10); printf("%.2f", diemtb); TextColor(15); break;
		}
	}
	cout << "   >> So luong tim duoc: "; TextColor(10); cout << lengthFound(); TextColor(15);
	ToMau(0, 10, MenuChinh[3], 10);
	rowInfo();
	if (ffirst == NULL) { // Ktra neu Ds rong -----> Ket thuc ham
		gotoXY(120, 39);  system("pause");
		return;
	}
	// -------- tinh stt cua sinh vien dau trang in ----------------
	int sttDau = 0;
	if (start == ffirst)	 sttDau = 1;
	else if (start == flast)  sttDau = lengthFound();
	else {
		for (Node *temp = start; temp != NULL; temp = temp->prev)	sttDau++;
	}
	// -------- tinh trang Dang Xem la trang thu may ---------------
	int currentPage = (sttDau - 1) / 10 + 1;
	// -------- tinh stt cua sinh vien cuoi trang in ------------------
	int sttCuoi = sttDau;
	Node *end = start; // end se tro den vtri cuoi trang in
	for (int i = 1; i <= 9; i++) {
		if (end == flast)  break;
		end = end->next; // end tro den vtri cuoi cung cua trang in
		sttCuoi++;
	}
	// ---------- in trang Ds (toi da 10 sv trong 1 trang) ----------------
	Node *p = start;
	int y = 11, stt = sttDau;
	for (int i = 1; i <= 10; i++) { // in toi da 10 sv trong 1 trang
		if (p == NULL) break;
		gotoXY(32, y + 1);	cout << char(192);	gotoXY(131, y + 1); cout << char(217);
		gotoXY(32, y);	cout << char(179);  gotoXY(131, y);	cout << char(179);
		gotoXY(33, y);  cout << "      |                         |    /   /         |               |               |";
		for (int i = 33; i <= 130; i++) { gotoXY(i, y + 1);	cout << char(196); }
		gotoXY(34, y);	cout << stt;
		gotoXY(42, y); cout << p->HoTen;
		gotoXY(68, y); cout << right << setw(2) << setfill('0') << p->ngaySinh;
		gotoXY(72, y); cout << right << setw(2) << setfill('0') << p->thangSinh;
		gotoXY(76, y); cout << p->namSinh;
		gotoXY(87, y); cout << p->MaSV;
		gotoXY(103, y); cout << p->MaLop;
		gotoXY(119, y); cout << right << setw(5) << setfill(' ') << fixed << setprecision(2) << p->DiemTBTL;
		y += 2;
		stt++;
		p = p->next;
	}
	cout << setprecision(0);
	gotoXY(72, 32);	cout << "-- Trang " << currentPage << " / " << totalNumPageFound() << " --";
	//gotoXY(32, 36);	TextColor(12); cout << "Chu y: ";
	//gotoXY(39, 36); TextColor(14); cout << "Chon Sua (Xoa) thong tin sinh vien: nhan "; TextColor(11); cout << "ENTER";
	// ============= Di chuyen con tro (Len-Xuong) de xem ro tung dong, Lat trang (Trai-Phai), Chon de sua-xoa(Enter) ================================
	int pos = doListFound(sttDau, sttCuoi, start, end);
	switch (pos) {
	case 999999975: // ---------- Lat trang in truoc (LEFT) ------------
		if (currentPage == 1) {
			Node *begin = ffirst;
			for (int i = 1; i <= (totalNumPageFound() - 1) * 10; i++)  begin = begin->next;
			displayFound(choice, key, begin, noidung, ngay, thang, nam, diemtb);
		}
		else  displayFound(choice, key, start->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev, noidung, ngay, thang, nam, diemtb);
		break;
	case 999999977: // ---------- Lat trang in sau (RIGHT) --------------
		if (currentPage == totalNumPageFound()) {
			displayFound(choice, key, ffirst, noidung, ngay, thang, nam, diemtb);
		}
		else 	displayFound(choice, key, end->next, noidung, ngay, thang, nam, diemtb);
		break;
	case 999999999: // ---------- Quay ve menu chinh (ESC) --------------
		return;
		//default: // ----------------- Chon dong (ENTER) de Xoa(Sua) ---------------------
		//	gotoXY(133, 11 + 2 * (pos - sttDau)); TextColor(11); cout << "--> Chon thao tac:";
		//	switch (menu(Menu2a, 2, 137, 12 + 2 * (pos - sttDau))) {
		//	case 1:
		//		redoEdit(pos);
		//		break;
		//	case 2:
		//		if (pos == sttDau) {
		//			if ((start == flast) && (start != ffirst)) {
		//				start = start->prev->prev->prev->prev->prev->prev->prev->prev->prev->prev;
		//			}
		//			else start = start->next; // Ds in bat dau tu Start ---> phai co Start moi thay the truoc khi xoa Start
		//		}
		//		deletePosition(pos);
		//		break;
		//	}
		//	displayFound(choice, key, start, noidung, ngay, thang, nam, diemtb); // In lai Ds sau khi Xoa (Sua)
	}
}
void addTail_FoundList(Node *q) {
	Node *p = (Node *)malloc(sizeof(Node));
	strcpy(p->HoTen, q->HoTen);
	p->ngaySinh = q->ngaySinh;
	p->thangSinh = q->thangSinh;
	p->namSinh = q->namSinh;
	strcpy(p->MaSV, q->MaSV);
	strcpy(p->MaLop, q->MaLop);
	p->DiemTBTL = q->DiemTBTL;
	// then vao cuoi Ds TimKiem
	if (ffirst == NULL) {
		p->next = NULL;
		p->prev = NULL;
		ffirst = flast = p;
	}
	else {
		flast->next = p;
		p->next = NULL;
		p->prev = flast;
		flast = p;
	}
}
void linearSearch(int way, int key) { // --------- Tim kiem tuan tu -------------------
	char hoTen[41] = "", maSv[9] = "", maLop[9] = "", random[40] = "";
	int ngSinh = 0, thSinh = 0, namSinh = 0;
	float diemTb = 0;
	ffirst = NULL;	flast = NULL;
	clrscr(); programName(); splitWindow(); gotoXY(27, 6); TextColor(11); cout << char(205) << char(205) << " TIM KIEM THONG TIN " << char(205) << char(205); TextColor(15); ToMau(0, 10, MenuChinh[3], 10);
	gotoXY(32, 8);	cout << char(218);	gotoXY(131, 8); cout << char(191);
	for (int i = 33; i <= 130; i++) { gotoXY(i, 8);	cout << char(196); }
	for (int i = 33; i <= 130; i++) { gotoXY(i, 10);	cout << char(196); }
	gotoXY(32, 10);	cout << char(192);	gotoXY(131, 10); cout << char(217);
	gotoXY(32, 9);	cout << char(179);  gotoXY(131, 9);	cout << char(179);
	gotoXY(60, 9);  cout << char(179);
	switch (way) { // chon kieu tim kiem (1.chinh xac, 2.gan chinh xac, 3.ngau nhien)
	case 1: //=============	TIM KIEM CHINH XAC ===============
		gotoXY(54, 6); TextColor(13); cout << ">> Tim kiem chinh xac"; TextColor(15);
		switch (key) {
		case 1: // tim theo ma sv
		{
			strcpy(maSv, enterSearchChar(1));
			for (Node *p = first; p != NULL; p = p->next) {
				if ((strcmp(p->MaSV, maSv)) == 0)	addTail_FoundList(p);
			}
			displayFound(1, 1, ffirst, maSv, ngSinh, thSinh, namSinh, diemTb);
			break;
		}
		case 2: // tiem theo ma Lop
		{
			strcpy(maLop, enterSearchChar(2));	chuanHoaID(maLop);
			for (Node *p = first; p != NULL; p = p->next) {
				if ((strcmp(p->MaLop, maLop)) == 0)	addTail_FoundList(p);
			}
			displayFound(1, 2, ffirst, maLop, ngSinh, thSinh, namSinh, diemTb);
			break;
		}
		case 3: // tim theo ho ten
		{
			strcpy(hoTen, enterSearchChar(3));
			for (Node *p = first; p != NULL; p = p->next) {
				if (compareStrName(p->HoTen, hoTen) == 0)	addTail_FoundList(p);
			}
			displayFound(1, 3, ffirst, hoTen, ngSinh, thSinh, namSinh, diemTb);
			break;
		}
		case 4: // tim theo ngay sinh
		{
			do {
				gotoXY(63, 9); cout << "                                 ";
				ngSinh = int(enterSearchNum(1));
				thSinh = int(enterSearchNum(2));
				namSinh = int(enterSearchNum(3));
			} while (checkDate(ngSinh, thSinh, namSinh) == false);
			for (Node *p = first; p != NULL; p = p->next) {
				if ((p->ngaySinh == ngSinh) && (p->thangSinh == thSinh) && (p->namSinh == namSinh))   addTail_FoundList(p);
			}
			displayFound(1, 4, ffirst, hoTen, ngSinh, thSinh, namSinh, diemTb);
			break;
		}
		case 5: // tim theo diem tbtl
		{
			diemTb = enterSearchNum(4);
			for (Node *p = first; p != NULL; p = p->next) {
				if (p->DiemTBTL == diemTb) addTail_FoundList(p);
			}
			displayFound(1, 5, ffirst, hoTen, ngSinh, thSinh, namSinh, diemTb);
			break;
		}
		}
		break;
	case 2: //============== TIM KIEM GAN CHINH XAC ==============
		gotoXY(54, 6); TextColor(13); cout << ">> Tim kiem gan chinh xac"; TextColor(15);
		switch (key) {
		case 1: // tim theo ma sv
		{
			strcpy(maSv, enterSearchChar(0));
			for (Node *p = first; p != NULL; p = p->next) {
				if (strstr(p->MaSV, maSv) != NULL) addTail_FoundList(p);
			}
			displayFound(2, 1, ffirst, maSv, ngSinh, thSinh, namSinh, diemTb);
			break;
		}
		case 2: // tim theo ma Lop
		{
			strcpy(maLop, enterSearchChar(2)); chuanHoaID(maLop);
			for (Node *p = first; p != NULL; p = p->next) {
				if ((strstr(p->MaLop, maLop)) != NULL)  addTail_FoundList(p);
			}
			displayFound(2, 2, ffirst, maLop, ngSinh, thSinh, namSinh, diemTb);
			break;
		}
		case 3: // tim theo ho ten
		{
			char tenlwr[41];
			strcpy(hoTen, enterSearchChar(4)); strlwr(hoTen);
			for (Node *p = first; p != NULL; p = p->next) {
				strcpy(tenlwr, p->HoTen);	strlwr(tenlwr);
				if (strstr(tenlwr, hoTen) != NULL) addTail_FoundList(p);
			}
			displayFound(2, 3, ffirst, hoTen, ngSinh, thSinh, namSinh, diemTb);
			break;
		}
		case 4: // tim theo ngay sinh
		{
			gotoXY(33, 12); TextColor(14); cout << "       Tim ra sinh vien co ngay sinh trong do "; TextColor(11); cout << "ngay "; TextColor(14); cout << "(hoac ";
			TextColor(11); cout << "thang"; TextColor(14); cout << ", hoac "; TextColor(11); cout << "nam"; TextColor(14); cout << ") trung voi du lieu nhap"; TextColor(15);
			do {
				gotoXY(63, 9); cout << "                                 ";
				ngSinh = int(enterSearchNum(1));
				thSinh = int(enterSearchNum(2));
				namSinh = int(enterSearchNum(3));
			} while (checkDate(ngSinh, thSinh, namSinh) == false);
			for (Node *p = first; p != NULL; p = p->next) {
				if ((p->ngaySinh == ngSinh) || (p->thangSinh == thSinh) || (p->namSinh == namSinh)) addTail_FoundList(p);
			}
			displayFound(2, 4, ffirst, hoTen, ngSinh, thSinh, namSinh, diemTb);
			break;
		}
		case 5: // tim theo diem tbtl
		{
			gotoXY(33, 11); TextColor(12); cout << "Chu y: "; TextColor(14); cout << "Tim ra diem TBTL trong do "; TextColor(11); cout << "phan nguyen ";
			TextColor(14); cout << "(hoac "; TextColor(11); cout << "phan thap phan"; TextColor(14); cout << ") trung voi du lieu nhap"; TextColor(15);
			int nguyenTBTL, thphanTBTL, nguyenNhap, thphanNhap;
			diemTb = enterSearchNum(4);
			nguyenNhap = int(diemTb);
			thphanNhap = int(diemTb * 100 - nguyenNhap * 100);
			if (thphanNhap % 10 == 0)	thphanNhap /= 10;
			for (Node *p = first; p != NULL; p = p->next) {
				nguyenTBTL = int(p->DiemTBTL);
				thphanTBTL = int(p->DiemTBTL * 100 - nguyenTBTL * 100);
				if (thphanTBTL % 10 == 0)	thphanTBTL /= 10;
				if (nguyenTBTL == nguyenNhap || thphanTBTL == thphanNhap)	addTail_FoundList(p);
			}
			displayFound(2, 5, ffirst, hoTen, ngSinh, thSinh, namSinh, diemTb);
			break;
		}
		}
		break;
	case 3: //=================== TIM KIEM NGAU NHIEN =================
	{
		char hotenlwr[41], masvlwr[9], maloplwr[9];
		strcpy(random, enterSearchChar(5));		strlwr(random);
		for (Node *p = first; p != NULL; p = p->next) {
			strcpy(hotenlwr, p->HoTen);	strlwr(hotenlwr);
			strcpy(masvlwr, p->MaSV);	strlwr(masvlwr);
			strcpy(maloplwr, p->MaLop);	strlwr(maloplwr);
			if ((strstr(masvlwr, random) != NULL) || (strstr(maloplwr, random) != NULL) || (strstr(hotenlwr, random) != NULL)) addTail_FoundList(p);
		}
		displayFound(3, 0, ffirst, random, ngSinh, thSinh, namSinh, diemTb);
		break;
	}
	}
	return;
}
void binarySearch(int choice) { // --------- Tim kiem nhi phan -------------------
	char hoTen[41] = "", maSv[9] = "", maLop[9] = "";
	int ngSinh = 0, thSinh = 0, namSinh = 0;
	float diemTb = 0;
	ffirst = NULL; flast = NULL;
	clrscr(); programName(); splitWindow(); gotoXY(27, 6); TextColor(11); cout << char(205) << char(205) << " TIM KIEM THONG TIN " << char(205) << char(205); TextColor(15); ToMau(0, 10, MenuChinh[3], 10);
	gotoXY(32, 8);	cout << char(218);	gotoXY(131, 8); cout << char(191);
	for (int i = 33; i <= 130; i++) { gotoXY(i, 8);	cout << char(196); }
	for (int i = 33; i <= 130; i++) { gotoXY(i, 10);	cout << char(196); }
	gotoXY(32, 10);	cout << char(192);	gotoXY(131, 10); cout << char(217);
	gotoXY(32, 9);	cout << char(179);  gotoXY(131, 9);	cout << char(179);
	gotoXY(60, 9);  cout << char(179); 	gotoXY(54, 6); TextColor(13); cout << "Tim kiem Nhi phan"; TextColor(15);
	Node *t = (Node *)malloc(sizeof(Node)); // con tro phu de so sanh ngaysinh, ten
	int left, right, mid, i; // vtri trai - phai - giua cua binarySearch; // i: chi so chay de ktra cac sv lan can cua sv dau tien tim dc
    // ===== BinarySearch: Tim duoc sinh vien dau tien thoa man --> Ktra tiep cac sinh vien lan can trai - lan can phai cua sinh vien do ===== //
	/*  int left = 0;
		int rigth = n - 1;
		while (left <= rigth) {
		int mid = (left + rigth) / 2;
		if (a[mid] == x) 		return true;
		else if (a[mid] > x) 	rigth = mid - 1;
		else 				left = mid + 1;
		}
		return false;   */
	switch (choice) {
	case 1: // tim kiem theo ma sinh vien
	{
		strcpy(maSv, enterSearchChar(1));
		bubbleSort(1); // Sap xep Ds sinh vien theo thu tu Ma lop tang dan
		left = 1;
		right = length();
		while (left <= right) {
			mid = (left + right) / 2;
			if (strcmp(element(mid)->MaSV, maSv) == 0) { // tim duoc sv dau tien co Ma sinh vien thoa man
				addTail_FoundList(element(mid));
				break;
			}
			else if (strcmp(element(mid)->MaSV, maSv) > 0)	right = mid - 1;
			else	left = mid + 1;
		}
		i = mid;
		while (i != length()) { // ktra cac lan can phai cua sv dau tien tim duoc
			i++;
			if (strcmp(element(i)->MaSV, maSv) == 0)	addTail_FoundList(element(i));
			else  break;
		}
		i = mid;
		while (i != 1) { // ktra cac lan can trai cua sv dau tien tim duoc
			i--;
			if (strcmp(element(i)->MaSV, maSv) == 0)	addTail_FoundList(element(i));
			else  break;
		}
		displayFound(4, 1, ffirst, maSv, ngSinh, thSinh, namSinh, diemTb);
		break;
	}
	case 2: // tim kiem theo ma lop
	{
		strcpy(maLop, enterSearchChar(2));
		bubbleSort(2); // Sap xep Ds sinh vien theo thu tu Ma lop tang dan
		left = 1;
		right = length();
		while (left <= right) {
			mid = (left + right) / 2;
			if (strcmp(element(mid)->MaLop, maLop) == 0) { // tim duoc sv dau tien co Ma lop thoa man
				addTail_FoundList(element(mid));
				break;
			}
			else if (strcmp(element(mid)->MaLop, maLop) > 0)	right = mid - 1;
			else	left = mid + 1;
		}
		i = mid;
		while (i != length()) { // ktra cac lan can phai cua sv dau tien tim duoc
			i++;
			if (strcmp(element(i)->MaLop, maLop) == 0)	addTail_FoundList(element(i));
			else  break;
		}
		i = mid;
		while (i != 1) { // ktra cac lan can trai cua sv dau tien tim duoc
			i--;
			if (strcmp(element(i)->MaLop, maLop) == 0)	addTail_FoundList(element(i));
			else  break;
		}
		displayFound(4, 2, ffirst, maLop, ngSinh, thSinh, namSinh, diemTb);
		break;
	}
	case 3: // tim kiem theo ho ten
	{
		strcpy(hoTen, enterSearchChar(3));
		strcpy(t->HoTen, hoTen);
		bubbleSort(3); // Sap xep Ds sinh vien theo thu tu Ho ten tang dan
		left = 1;
		right = length();
		while (left <= right) {
			mid = (left + right) / 2;
			if (compareName(element(mid), t) == 0) { // tim duoc sv dau tien co Ho ten thoa man
				addTail_FoundList(element(mid));
				break;
			}
			else if (compareName(element(mid), t) > 0)	right = mid - 1;
			else	left = mid + 1;
		}
		i = mid;
		while (i != length()) { // ktra cac lan can phai cua sv dau tien tim duoc
			i++;
			if (compareName(element(i), t) == 0)	addTail_FoundList(element(i));
			else  break;
		}
		i = mid;
		while (i != 1) { // ktra cac lan can trai cua sv dau tien tim duoc
			i--;
			if (compareName(element(i), t) == 0)	addTail_FoundList(element(i));
			else  break;
		}
		displayFound(4, 3, ffirst, hoTen, ngSinh, thSinh, namSinh, diemTb);
		break;
	}
	case 4: // tim kiem theo ngay sinh
	{
		do {
			gotoXY(63, 9); cout << "                                 ";
			ngSinh = int(enterSearchNum(1));
			thSinh = int(enterSearchNum(2));
			namSinh = int(enterSearchNum(3));
		} while (checkDate(ngSinh, thSinh, namSinh) == false);
		t->ngaySinh = ngSinh;
		t->thangSinh = thSinh;
		t->namSinh = namSinh;
		bubbleSort(4); // Sap xep Ds sinh vien theo thu tu Ngay sinh tang dan
		left = 1;
		right = length();
		while (left <= right) {
			mid = (left + right) / 2;
			if (compareDate(element(mid), t) == 0) { // tim duoc sv dau tien co Ngay sinh thoa man
				addTail_FoundList(element(mid));
				break;
			}
			else if (compareDate(element(mid), t) > 0)	right = mid - 1;
			else	left = mid + 1;
		}
		i = mid;
		while (i != length()) { // ktra cac lan can phai cua sv dau tien tim duoc
			i++;
			if (compareDate(element(i), t) == 0)	addTail_FoundList(element(i));
			else  break;
		}
		i = mid;
		while (i != 1) { // ktra cac lan can trai cua sv dau tien tim duoc
			i--;
			if (compareDate(element(i), t) == 0)	addTail_FoundList(element(i));
			else  break;
		}
		displayFound(4, 4, ffirst, hoTen, ngSinh, thSinh, namSinh, diemTb);
		break;
	}
	case 5: // tim kiem theo diem TBTL
	{
		diemTb = enterSearchNum(4);
		bubbleSort(5); // Sap xep Ds sinh vien theo thu tu Diem TBTL giam dan
		left = 1;
		right = length();
		while (left <= right) {
			mid = (left + right) / 2;
			if (element(mid)->DiemTBTL == diemTb) { // tim duoc sv dau tien co diem TBTL thoa man
				addTail_FoundList(element(mid));
				break;
			}
			else if (element(mid)->DiemTBTL > diemTb)	left = mid + 1;
			else	right = mid - 1;
		}
		i = mid;
		while (i != length()) { // ktra cac lan can phai cua sv dau tien tim duoc
			i++;
			if (element(i)->DiemTBTL == diemTb)	addTail_FoundList(element(i));
			else  break;
		}
		i = mid;
		while (i != 1) { // ktra cac lan can trai cua sv dau tien tim duoc
			i--;
			if (element(i)->DiemTBTL == diemTb)	addTail_FoundList(element(i));
			else  break;
		}
		displayFound(4, 5, ffirst, hoTen, ngSinh, thSinh, namSinh, diemTb);
		break;
	}
	}
}
void addTail_ClassList(char maLop[]) {
	Lop *p = (Lop *)malloc(sizeof(Lop));
	strcpy(p->malop, maLop);
	p->next = NULL;
	if (cfirst == NULL)		cfirst = p;
	else 	clast->next = p;
	clast = p;
}
void thongKe(int choice) {
	cfirst = NULL;
	clast = NULL;
	clrscr(); programName(); splitWindow(); ToMau(0, 11, MenuChinh[4], 10);
	gotoXY(27, 6); TextColor(11); cout << char(205) << char(205) << " THONG KE " << char(205) << char(205);
	// ========== XU LI SO LIEU ========= //
	// --------- Tim cac maLop co trong Ds sinh vien -----> them vao Ds LopHoc -------------------
	bubbleSort(2); // Sap xep Ds sinh vien theo ma Lop de tim kiem
	if (first->MaLop[strlen(first->MaLop) - 1] == '\n')   first->MaLop[strlen(first->MaLop) - 1] = '\0'; // khu \n neu doc du lieu tu file
	addTail_ClassList(first->MaLop);
	for (Node *q = first->next; q != NULL; q = q->next) {
		if (q->MaLop[strlen(q->MaLop) - 1] == '\n')		q->MaLop[strlen(q->MaLop) - 1] = '\0'; // khu \n neu doc du lieu tu file
		if (strcmp(q->MaLop, clast->malop) != 0)	addTail_ClassList(q->MaLop);
	}
	// ------------------------------ Tinh so Sv, XS, G, K, TB, Y cua moi lop, va tong cua tat ca cac lop ------------------
	int soSVLop; // so luong sinh vien moi lop
	int XS, G, K, TB, Y; // so luong sv xuat sac, gioi, kha, trung binh, yeu cua lop
	int tongXS = 0, tongG = 0, tongK = 0, tongTB = 0, tongY = 0; // tong so luong sv xuat sac, gioi, kha, trung binh, yeu cua moi cac lop
	for (Lop *p = cfirst; p != NULL; p = p->next) { // Lay so sinh vien cua moi lop, ktra Phan loai ket qua hoc tap
		soSVLop = 0;
		XS = G = K = TB = Y = 0;
		for (Node *q = first; q != NULL; q = q->next) {
			if (q->MaLop[strlen(q->MaLop)] == '\n')	  q->MaLop[strlen(q->MaLop)] == '\0'; // khu "\n" trong ma lop neu doc du lieu sinh vien tu file
			if (strcmp(q->MaLop, p->malop) == 0) {
				soSVLop++;
				if (q->DiemTBTL >= 9)	XS++;
				else if (q->DiemTBTL >= 8 && q->DiemTBTL < 9)	G++;
				else if (q->DiemTBTL >= 6.5 && q->DiemTBTL < 8)	K++;
				else if (q->DiemTBTL >= 5 && q->DiemTBTL < 6.5) TB++;
				else Y++;
			}
		}
		p->soSV = soSVLop; // luu du lieu sinh vien moi lop vao lop tuong ung trong Ds LopHoc
		p->xuatsac = XS;
		p->gioi = G;
		p->kha = K;
		p->trungbinh = TB;
		p->yeu = Y;
		tongXS += XS;
		tongG += G;
		tongK += K;
		tongTB += TB;
		tongY += Y;
	}
	switch (choice) {
	case 1: // ============ Thong ke So luong sinh vien moi lop ================
	{
		// --------- Ke khung -------------
		gotoXY(34, 8); TextColor(13); cout << "_____________ BAO CAO SO LUONG SINH VIEN THEO LOP ____________"; TextColor(15);
		gotoXY(32, 9); cout << char(218);		gotoXY(97, 9); cout << char(191);
		gotoXY(32, 10); cout << char(179);		gotoXY(97, 10); cout << char(179);
		gotoXY(32, 11); cout << char(192);		gotoXY(97, 11); cout << char(217);
		for (int i = 33; i < 97; i++) { gotoXY(i, 9); cout << char(196); }
		for (int i = 33; i < 97; i++) { gotoXY(i, 11); cout << char(196); }
		gotoXY(35, 10); cout << "STT   |  Ma Lop              |  So sinh vien   |  Ty le";
		// -------- In so lieu vao bang thong ke ---------
		int y = 12, stt = 0;
		for (Lop *p = cfirst; p != NULL; p = p->next) {
			stt++;
			gotoXY(32, y); cout << char(179);	gotoXY(97, y); cout << char(179);
			gotoXY(32, y + 1); cout << char(192);	gotoXY(97, y + 1); cout << char(217);
			gotoXY(34, y);  cout << "       |                      |                 |";
			for (int i = 33; i < 97; i++) { gotoXY(i, y + 1); cout << char(196); }
			gotoXY(35, y); cout << stt;
			gotoXY(44, y); cout << p->malop;
			gotoXY(69, y); cout << setw(5) << setfill(' ') << p->soSV;
			gotoXY(85, y); cout << setw(6) << setfill(' ') << fixed << setprecision(2) << float(p->soSV) / float(length()) * 100 << " %";
			y += 2;
		}
		gotoXY(32, y); cout << char(179);  gotoXY(97, y); cout << char(179);
		gotoXY(35, y);  cout << "         Tong cong           |                 |       ";
		for (int i = 33; i < 97; i++) { gotoXY(i, y + 1); cout << char(196); }
		gotoXY(32, y + 1); cout << char(192);	gotoXY(97, y + 1); cout << char(217);
		gotoXY(69, y); cout << setw(5) << setfill(' ') << length();
		gotoXY(85, y); cout << "100.00 %";
		break;

	}
	case 2: // ============ Thong ke Phan loai ket qua hoc tap =================
	{
		// ke khung
		gotoXY(34, 8); TextColor(13); cout << "_______________________________________ BAO CAO PHAN LOAI KET QUA HOC TAP _________________________________________"; TextColor(15);
		for (int i = 33; i < 150; i++) { gotoXY(i, 9); cout << char(196); }	gotoXY(32, 9); cout << char(218);	gotoXY(150, 9); cout << char(191);
		gotoXY(32, 10); cout << char(179); gotoXY(32, 12); cout << char(179); gotoXY(150, 10); cout << char(179); gotoXY(150, 12); cout << char(179);
		gotoXY(32, 11); cout << char(179); gotoXY(150, 11); cout << char(180); gotoXY(32, 13); cout << char(192); gotoXY(150, 13); cout << char(217);
		for (int i = 33; i < 150; i++) { gotoXY(i, 13); cout << char(196); } for (int i = 51; i < 150; i++) { gotoXY(i, 11); cout << char(196); } gotoXY(150, 11); cout << char(180);
		gotoXY(130, 9); cout << char(194); gotoXY(110, 9); cout << char(194); gotoXY(90, 9); cout << char(194); gotoXY(70, 9); cout << char(194); gotoXY(50, 9); cout << char(194);
		gotoXY(130, 10); cout << char(179); gotoXY(110, 10); cout << char(179); gotoXY(90, 10); cout << char(179); gotoXY(70, 10); cout << char(179); gotoXY(50, 10); cout << char(179);
		gotoXY(130, 11); cout << char(197); gotoXY(110, 11); cout << char(197); gotoXY(90, 11); cout << char(197); gotoXY(70, 11); cout << char(197); gotoXY(50, 11); cout << char(195);
		gotoXY(130, 12); cout << char(179); gotoXY(110, 12); cout << char(179); gotoXY(90, 12); cout << char(179); gotoXY(70, 12); cout << char(179); gotoXY(50, 12); cout << char(179);
		gotoXY(130, 13); cout << char(193); gotoXY(110, 13); cout << char(193); gotoXY(90, 13); cout << char(193); gotoXY(70, 13); cout << char(193); gotoXY(50, 13); cout << char(193);
		gotoXY(138, 11); cout << char(194); gotoXY(118, 11); cout << char(194); gotoXY(98, 11); cout << char(194); gotoXY(78, 11); cout << char(194); gotoXY(58, 11); cout << char(194);
		gotoXY(138, 12); cout << char(179); gotoXY(118, 12); cout << char(179); gotoXY(98, 12); cout << char(179); gotoXY(78, 12); cout << char(179); gotoXY(58, 12); cout << char(179);
		gotoXY(138, 13); cout << char(193); gotoXY(118, 13); cout << char(193); gotoXY(98, 13); cout << char(193); gotoXY(78, 13); cout << char(193); gotoXY(58, 13); cout << char(193);
		gotoXY(34, 11); cout << " Ma lop - So SV"; gotoXY(56, 10); cout << "XUAT SAC"; gotoXY(78, 10); cout << "GIOI";	gotoXY(98, 10); cout << "KHA";
		gotoXY(115, 10); cout << "TRUNG BINH"; gotoXY(138, 10); cout << "YEU";
		gotoXY(53, 12); cout << "SL"; gotoXY(73, 12); cout << "SL"; gotoXY(93, 12); cout << "SL"; gotoXY(113, 12); cout << "SL"; gotoXY(133, 12); cout << "SL";
		gotoXY(60, 12); cout << "Ty le (%)"; gotoXY(80, 12); cout << "Ty le (%)"; gotoXY(100, 12); cout << "Ty le (%)"; gotoXY(120, 12); cout << "Ty le (%)"; gotoXY(140, 12); cout << "Ty le (%)";
		// In so lieu vao bang thong ke
		int y = 14;
		for (Lop *p = cfirst; p != NULL; p = p->next) {
			for (int i = 33; i < 150; i++) { gotoXY(i, y + 1); cout << char(196); } gotoXY(32, y - 1); cout << char(195); gotoXY(150, y - 1); cout << char(180); gotoXY(50, y + 1); cout << char(193);
			gotoXY(138, y + 1); cout << char(193); gotoXY(118, y + 1); cout << char(193); gotoXY(98, y + 1); cout << char(193); gotoXY(78, y + 1); cout << char(193); gotoXY(58, y + 1); cout << char(193);
			gotoXY(130, y + 1); cout << char(193); gotoXY(110, y + 1); cout << char(193); gotoXY(90, y + 1); cout << char(193); gotoXY(70, y + 1); cout << char(193); gotoXY(50, y + 1); cout << char(193);
			gotoXY(32, y); cout << char(179);  gotoXY(150, y); cout << char(179); gotoXY(32, y + 1); cout << char(192);  gotoXY(150, y + 1); cout << char(217); gotoXY(43, y + 1); cout << char(193);
			gotoXY(33, y); cout << "                 |       |           |       |           |       |           |       |           |       |           ";
			gotoXY(35, y); cout << p->malop; gotoXY(43, y); cout << "| " << p->soSV;
			gotoXY(53, y); cout << p->xuatsac;
			gotoXY(73, y); cout << p->gioi;
			gotoXY(93, y); cout << p->kha;
			gotoXY(113, y); cout << p->trungbinh;
			gotoXY(133, y); cout << p->yeu;
			gotoXY(60, y); cout << setw(6) << setfill(' ') << fixed << setprecision(2) << float(p->xuatsac) / float(p->soSV) * 100;
			gotoXY(80, y); cout << setw(6) << setfill(' ') << fixed << setprecision(2) << float(p->gioi) / float(p->soSV) * 100;
			gotoXY(100, y); cout << setw(6) << setfill(' ') << fixed << setprecision(2) << float(p->kha) / float(p->soSV) * 100;
			gotoXY(120, y); cout << setw(6) << setfill(' ') << fixed << setprecision(2) << float(p->trungbinh) / float(p->soSV) * 100;
			gotoXY(140, y); cout << setw(6) << setfill(' ') << fixed << setprecision(2) << float(p->yeu) / float(p->soSV) * 100;
			y += 2;
		}
		for (int i = 33; i < 150; i++) { gotoXY(i, y + 1); cout << char(196); } gotoXY(32, y - 1); cout << char(195); gotoXY(150, y - 1); cout << char(180); gotoXY(50, y + 1); cout << char(193);
		gotoXY(138, y + 1); cout << char(193); gotoXY(118, y + 1); cout << char(193); gotoXY(98, y + 1); cout << char(193); gotoXY(78, y + 1); cout << char(193); gotoXY(58, y + 1); cout << char(193);
		gotoXY(130, y + 1); cout << char(193); gotoXY(110, y + 1); cout << char(193); gotoXY(90, y + 1); cout << char(193); gotoXY(70, y + 1); cout << char(193); gotoXY(50, y + 1); cout << char(193);
		gotoXY(32, y); cout << char(179);  gotoXY(150, y); cout << char(179); gotoXY(32, y + 1); cout << char(192);  gotoXY(150, y + 1); cout << char(217); gotoXY(43, y + 1); cout << char(193);
		gotoXY(33, y); cout << "                 |       |           |       |           |       |           |       |           |       |           ";
		gotoXY(35, y); cout << "Tong    | " << length();
		gotoXY(53, y); cout << tongXS;
		gotoXY(73, y); cout << tongG;
		gotoXY(93, y); cout << tongK;
		gotoXY(113, y); cout << tongTB;
		gotoXY(133, y); cout << tongY;
		gotoXY(60, y); cout << setw(6) << setfill(' ') << fixed << setprecision(2) << float(tongXS) / float(length()) * 100;
		gotoXY(80, y); cout << setw(6) << setfill(' ') << fixed << setprecision(2) << float(tongG) / float(length()) * 100;
		gotoXY(100, y); cout << setw(6) << setfill(' ') << fixed << setprecision(2) << float(tongK) / float(length()) * 100;
		gotoXY(120, y); cout << setw(6) << setfill(' ') << fixed << setprecision(2) << float(tongTB) / float(length()) * 100;
		gotoXY(140, y); cout << setw(6) << setfill(' ') << fixed << setprecision(2) << float(tongY) / float(length()) * 100;
	}
	}
	cout << setprecision(0);
	gotoXY(120, 39);	system("pause");
}
void writeTextFile(char *fileName) {
	FILE *fw;
	fw = fopen(fileName, "w");
	if (fw == NULL)	return;
	fprintf(fw, "%d", length());
	for (Node *p = first; p != NULL; p = p->next) {
		fprintf(fw, "\n%s", p->HoTen);
		fprintf(fw, "\n%d", p->ngaySinh);
		fprintf(fw, "\n%d", p->thangSinh);
		fprintf(fw, "\n%d", p->namSinh);
		fprintf(fw, "\n%s", p->MaSV);
		fprintf(fw, "\n%s", p->MaLop);
		fprintf(fw, "\n%f", p->DiemTBTL);
	}
	fclose(fw);
}
void readTextFile(char *fileName) {
	FILE *fr;
	fr = fopen(fileName, "r");
	if (fr == NULL)		return;
	int n;
	char buff[10]; // bo dem, xoa nhung ki tu thua
	fscanf(fr, "%d", &n); // doc so luong sinh vien
	while (!feof(fr)) {
		Node *p = (Node *)malloc(sizeof(Node));
		fgets(buff, 10, fr);	fgets(p->HoTen, 41, fr);
		fscanf(fr, "%d", &p->ngaySinh);
		fscanf(fr, "%d", &p->thangSinh);
		fscanf(fr, "%d", &p->namSinh);
		fgets(buff, 10, fr);	fgets(p->MaSV, 9, fr);
		fgets(buff, 10, fr);	fgets(p->MaLop, 9, fr);
		fscanf(fr, "%f", &p->DiemTBTL);
		// them vao cuoi DS
		if (first == NULL) {
			p->next = NULL;
			p->prev = NULL;
			first = last = p;
		}
		else {
			last->next = p;
			p->next = NULL;
			p->prev = last;
			last = p;
		}
	}
	fclose(fr);
}
void writeBinaryFile(char *fileName) {
	FILE *fw;
	fw = fopen(fileName, "wb");
	if (fw == NULL)	return;
	for (Node *p = first; p != NULL; p = p->next) {
		fwrite(p, sizeof(Node), 1, fw);
	}
	fclose(fw);
}
void readBinaryFile(char *fileName) {
	FILE *fr;
	fr = fopen(fileName, "rb");
	if (fr == NULL)	return;

	Node*p = (Node *)malloc(sizeof(Node));
	fread(p, sizeof(Node), 1, fr);
	while (!feof(fr)) {
		// them vao cuoi DS
		if (first == NULL) {
			p->next = NULL;
			p->prev = NULL;
			first = last = p;
		}
		else {
			last->next = p;
			p->next = NULL;
			p->prev = last;
			last = p;
		}
		p = (Node *)malloc(sizeof(Node));
		fread(p, sizeof(Node), 1, fr);
	}
	fclose(fr);
}
void chuanHoaDataFromFile(){
	for (Node *p = first; p != NULL; p = p->next) { // khu \n trong chuoi char (neu co)
		while (p->MaSV[strlen(p->MaSV) - 1] == '\n')  p->MaLop[strlen(p->MaSV) - 1] = '\0';
		while (p->MaLop[strlen(p->MaLop) - 1] == '\n')  p->MaLop[strlen(p->MaLop) - 1] = '\0';
		while (p->HoTen[strlen(p->HoTen) - 1] == '\n')  p->HoTen[strlen(p->HoTen) - 1] = '\0';
	}
}
