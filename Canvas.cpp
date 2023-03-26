#include "Canvas.h"
#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;

Shape::Shape() {
	l = 0;
	w = 0;
	r = 0;
	area = 0;
	form = 0;
	//coordinates = NULL;
	x = 0;
	y = 0;
}

Shape::Shape(int a, double b, double c, int d, int e) {
	form = a;

	l = b;
	w = c;
	r = 0;
	if (form == 3) {
		area = l * w;
		x = d;
		y = e;

	}
	else if (form == 4) {
		area = (l * w) / 2.0;
		x = d;
		y = e;
	}
}

Shape::Shape(int a, double b, int c, int d) {
	form = a;
	if (form == 1) {
		r = b;
		area = 3.142 * b * b;
		l = 0;
		w = 0;
		x = c;
		y = d;
	}
	else if (form == 2) {
		l = b;
		w = b;
		r = 0;
		area = l * w;
		x = c;
		y = d;

	}
}

void Shape::getArea(Shape& S) {
	cout << "Area: " << S.area << endl;
}

Shape Shape::operator=(const Shape& S) {
	form = S.form;
	r = S.r;
	area = S.area;
	l = S.l;
	w = S.w;
	x = S.x;
	y = S.y;
	return S;
}

bool Shape::test_perpendicular(int x, int x1, int xc, int y, int y1, int yc, double r) {
	double m = double(x - x1) / (y - y1);
	double mt = -1 / m;
	//y-y1=m(x-x1);
	//y-yc=mt(x-xc);
	double xt = ((m * x1) - y1 + yc - (mt * xc)) / (m - mt);
	double yt = m * (xt - x1) + y1;
	return (r > pow((pow((xt - xc), 2) + pow((yt - yc), 2)), 1 / 2.0));
}

double Shape::point_area(int x1, int x2, int x3, int y1, int y2, int y3) {
	double area = ((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
	if (area > 0) {
		//cout << "Area: " << area << endl;

		return area;
	}
	else {
		area *= -1;
		//cout << "Area: " << area << endl;

		return area;
	}
}
//int x, int x1, int x2, int x3, int y, int y1, int y2, int y3
//int x1, int y1, int x2, int y2, int x3, int y3, int x, int y
//(test_within(x, y, x + w, y, x + (w / 2), y + l, S1.x, S1.y) || test_within(x, y, x + w, y, x + (w / 2), y + l, S1.x + S1.w, S1.y))
//(test_within(S1.x, S1.y, S1.x + S1.w, S1.y, S1.x + (S1.w / 2), S1.y + S1.l, x, y) || test_within(S1.x, S1.y, S1.x + S1.w, S1.y, S1.x + (S1.w / 2), S1.y + S1.l, x + w, y))

bool Shape::test_within(int x1, int y1, int x2, int y2, int x3, int y3, int x, int y) {
	bool check = false;
	/* Calculate area of complete triangle*/
	double area, area1, area2, area3, total_area;
	area = point_area(x1, x2, x3, y1, y2, y3);
	area1 = point_area(x, x2, x3, y, y2, y3);
	area2 = point_area(x1, x, x3, y1, y, y3);
	area3 = point_area(x1, x2, x, y1, y2, y);
	total_area = area1 + area2 + area3;
	if (total_area == area) {
		check = true;
		return check;
	}
	return check;
}

bool Shape::overlapping(Shape S1) {
	bool check = false;
	//1.Circle - Circle;
	if (form == 1 && S1.form == 1) {
		cout << "Circle-Circle\n";
		int c1, c2;
		c1 = ((x - S1.x) * (x - S1.x)) + ((y - S1.y) * (y - S1.y));
		c2 = (pow((r + S1.r), 2));
		if (c1 < c2) {
			check = true;
			return check;
		}
		else {
			return check;
		}
	}
	//2.Triangle - Triangle;
	else if (form == 4 && S1.form == 4) {
		cout << "Triangle -Triangle\n";
		if (x > (S1.x + S1.w) || (x + w) < S1.x) {
			//cout << "2\n";
			return check;
		}
		else  if ((y + l) < S1.y || (S1.y + S1.l) < y) {
			//cout << "3\n";
			return check;
		}
		else {
			if ((y > S1.y) && ((x > ((S1.x + S1.w) / 2)) || (x + w) < ((S1.x + S1.w) / 2))) {
				if (test_within(x, y, x + w, y, x + (w / 2), y + l, S1.x, S1.y) || test_within(x, y, x + w, y, x + (w / 2), y + l, S1.x + S1.w, S1.y)) {
					check = true;
					return check;
				}
			}
			else if ((y < S1.y) && ((((x + w) / 2) < S1.x) || ((x + w) / 2) > (S1.x + S1.w))) {
				if (test_within(S1.x, S1.y, S1.x + S1.w, S1.y, S1.x + (S1.w / 2), S1.y + S1.l, x, y) || test_within(S1.x, S1.y, S1.x + S1.w, S1.y, S1.x + (S1.w / 2), S1.y + S1.l, x + w, y)) {
					check = true;
					return check;
				}
			}
			else {
				check = true;

			}
		}
	}
	//3.Square / Rectangle - Square / Rectangle;
	else if ((form == 2 || form == 3) && (S1.form == 2 || S1.form == 3)) {
		cout << "Square / Rectangle - Square / Rectangle\n";
		if (x > (S1.x + S1.w) || (x + w) < S1.x) {
			//cout << "2\n";
			return check;
		}
		else  if ((y + l) < S1.y || (S1.y + S1.l) < y) {
			//cout << "3\n";
			return check;
		}
		else {
			check = true;
			return check;
		}
	}
	//4.Square / Rectangle - Circle;
	else if (((form == 2 || form == 3) && S1.form == 1) || ((S1.form == 2 || S1.form == 3) && form == 1)) {
		if (form == 1) {
			//cout << "Yoooo!\n";
			Shape temp = *this;
			*this = S1;
			S1 = temp;
		}
		double px = 0, py = 0;

		if (S1.x > x + w) {
			px = x + w;
		}
		else if (S1.x < x + w) {
			px = S1.x;
		}
		if (px < x) {
			px = x;
		}

		if (S1.y > y + l) {
			px = y + l;
		}
		else if (S1.y < y + l) {
			px = S1.y;
		}
		if (px < y) {
			px = y;
		}

		px -= S1.x;
		py -= S1.y;
		if (pow(S1.r, 2) > pow(px, 2) + pow(py, 2)) { //pow(c,2)=pow(a,2)+pow(b,2)
			check = true;
			return check;
		}
	}
	//5.Square / Rectangle - Triangle;
	else if (((form == 2 || form == 3) && S1.form == 4) || ((S1.form == 2 || S1.form == 3) && form == 4)) {
		cout << "Square / Rectangle - Triangle\n";
		if (form == 4) {
			//cout << "Yoooo!\n";
			Shape temp = *this;
			*this = S1;
			S1 = temp;
		}
		if (x > (S1.x + S1.w) || (x + w) < S1.x) {
			//cout << "2\n";
			return check;
		}
		else  if ((y + l) < S1.y || (S1.y + S1.l) < y) {
			//cout << "3\n";
			return check;
		}
		else if (test_within(S1.x + S1.w, S1.y, S1.x + (S1.w / 2), S1.y + S1.l, S1.x, S1.y, x, y) || test_within(S1.x + S1.w, S1.y, S1.x + (S1.w / 2), S1.y + S1.l, S1.x, S1.y, x + w, y)) {
			check = true;
			return check;
		}
		else {
			check = true;
			return check;
		}

	}
	//6.Circle - Triangle;
	else if ((form == 1 && S1.form == 4) || (S1.form == 1 && form == 4)) {
		if (form == 4) {
			//cout << "Yoooo!\n";
			Shape temp = *this;
			*this = S1;
			S1 = temp;
		}
		double px = 0, py = 0;

		if (S1.x > x + w) {
			px = x + w;
		}
		else if (S1.x < x + w) {
			px = S1.x;
		}
		if (px < x) {
			px = x;
		}

		if (S1.y > y + l) {
			px = y + l;
		}
		else if (S1.y < y + l) {
			px = S1.y;
		}
		if (px < y) {
			px = y;
		}
		px -= S1.x;
		py -= S1.y;
		if (pow(S1.r, 2) > pow(px, 2) + pow(py, 2)) { //pow(c,2)=pow(a,2)+pow(b,2)
			if ((S1.y > y && S1.x > x + (w / 2)) && (test_perpendicular(x + (w / 2), x + w, S1.x, y + l, y, S1.y, S1.r))) {
				check = true;
				return check;
			}
			else if ((S1.y > y && S1.x < x + (w / 2)) && (test_perpendicular(x, x + (w / 2), S1.x, y, y + l, S1.y, S1.r))) {
				check = true;
				return check;
			}
		}
	}
	else {
		cout << "OK!\n";
	}

	return check;

}

Shape Shape::returnLargestShape(Shape*& S1, int index) {
	Shape Ans = S1[0];
	double max = S1[0].getArea();

	for (int i = 0; i < index; i++) {
		if (max <= S1[i].getArea()) {
			Ans = S1[i];
			max = S1[i].getArea();
		}
	}
	return Ans;
}

Shape& Shape::overlappingShapes(Shape*& S,int j) {
	Shape max = returnLargestShape(S,j);
	int x = 0;
	for (int i = 0; i < j; i++) {
		if (max.overlapping(S[i]) && (max.form == S[i].form)) {
			x++;
		}
	}
	Shape* OLS = new Shape[x];
	x = 0;
	for (int i = 0; i < j; i++) {
		if (max.overlapping(S[i]) && (max.form == S[i].form)) {
			OLS[x] = S[i];
			x++;
		}
	}
	return (*OLS);
}

double Shape:: operator[](int i) {
	if (i == 1) { return (x * 1.0); }
	else if (i == 2) { return (y * 1.0); }
	else if (i == 3) { return l; }
	else if (i == 4) { return w; }
	else if (i == 5) { return r; }
	else if (i == 6) { return area; }
	else if (i == 7) { return form; }
	else {
		cout << "Invalid Case!\n";
		return 0.0;
	}
}

string toUpper(string n) {
	for (int i = 0; i < n.length(); i++) {
		if (int(n[i]) >= 97 && int(n[i]) <= 122) {
			n[i] = char(int(n[i]) - 32);
		}
	}
	return n;
}

Canvas::Canvas() {
	C = NULL;
	S = NULL;
	R = NULL;
	T = NULL;
	for (int i = 0; i < 4; i++) {
		size[i] = 0;
	}
}

Canvas::Canvas(int i[]) {

	for (int j = 0; j < 4; j++) {
		/*while (i[j] > 10 || i[i] < 0) {
			cout << "Invalid size!\nRenter size: ";
			cin >> i[j];
		}*/
		size[j] = i[j];
	}
	C = new Shape[size[0]];
	for (int k = 0; k < size[0]; k++) {
		C[k].x = rand() % 30;
		C[k].y = rand() % 30;
		C[k].l = 0;
		C[k].w = 0;
		C[k].r = rand() % 10;
		C[k].area = 3.142 * C[k].r * C[k].r;
	}
	S = new Shape[size[1]];
	for (int k = 0; k < size[1]; k++) {
		S[k].x = rand() % 30;
		S[k].y = rand() % 30;
		S[k].l = rand() % 10;
		S[k].w = S[k].l;
		S[k].r = 0;
		S[k].area = S[k].l * S[k].w;
	}
	R = new Shape[size[2]];
	for (int k = 0; k < size[2]; k++) {
		R[k].x = rand() % 30;
		R[k].y = rand() % 30;
		R[k].l = rand() % 10;
		R[k].w = rand() % 10;
		R[k].r = 0;
		R[k].area = R[k].l * R[k].w;
	}
	T = new Shape[size[3]];
	for (int k = 0; k < size[3]; k++) {
		T[k].x = rand() % 30;
		T[k].y = rand() % 30;
		T[k].l = rand() % 10;
		T[k].w = rand() % 10;
		T[k].r = 0;
		T[k].area = (T[k].l * T[k].w) / 2.0;
	}

	//int x=0;
	//for (int j = 0; j < i; j++) {
	//	/*cout << "Enter Form of" << j + 1 << " : ";
	//	cin >> S[i].form;
	//	cout << "Generate Random? Press '0' for yes!\n";
	//	cin >> x;*/
	//	if (x == 0) {
	//		S[i].x = rand() % 30;
	//		S[i].y = rand() % 30;
	//		if (S[i].form == 4 || S[i].form == 3) {
	//			S[i].l = rand() % 10;
	//			S[i].w = rand() % 10;
	//			S[i].r = 0;
	//			if (S[i].form == 4) {
	//				S[i].area = (S[i].l * S[i].w) / 2.0;
	//			}
	//			else {
	//				S[i].area = S[i].l * S[i].w;
	//			}
	//		}
	//		else if (S[i].form == 1) {
	//			S[i].l = 0;
	//			S[i].w = 0;
	//			S[i].r = rand() % 10;
	//			S[i].area = 3.142 * S[i].r * S[i].r;
	//		}
	//		else if (S[i].form == 2) {
	//			S[i].l = rand() % 10;
	//			S[i].w = S[i].l;
	//			S[i].r = 0;
	//			S[i].area = S[i].l * S[i].w;
	//		}
	//	}
	//}
}

Canvas::Canvas(Canvas& C1) {
	//size = C.getSize();
	for (int i = 0; i < 4; i++) {
		size[i] = C1.getSize(i);
	}
	C = new Shape[size[0]];
	for (int k = 0; k < size[0]; k++) {
		C[k].x = C1.C[k].x;
		C[k].y = C1.C[k].y;
		C[k].l = 0;
		C[k].w = 0;
		C[k].r = C1.C[k].getR();
		C[k].area = 3.142 * C[k].r * C[k].r;
	}
	S = new Shape[size[1]];
	for (int k = 0; k < size[1]; k++) {
		S[k].x = C1.S[k].x;
		S[k].y = C1.S[k].y;
		S[k].l = C1.S[k].getL();
		S[k].w = S[k].l;
		S[k].r = 0;
		S[k].area = S[k].l * S[k].w;
	}
	R = new Shape[size[2]];
	for (int k = 0; k < size[2]; k++) {
		R[k].x = C1.R[k].x;
		R[k].y = C1.R[k].y;
		R[k].l = C1.R[k].getL();
		R[k].w = C1.R[k].getW();
		R[k].r = 0;
		R[k].area = R[k].l * R[k].w;
	}
	T = new Shape[size[3]];
	for (int k = 0; k < size[3]; k++) {
		T[k].x = C1.T[k].x;
		T[k].y = C1.T[k].y;
		T[k].l = C1.T[k].getL();
		T[k].w = C1.T[k].getW();
		T[k].r = 0;
		T[k].area = (T[k].l * T[k].w) / 2.0;
	}
}

void Canvas:: operator()(int a, int b) {
	if (a == 1) {
		cout << "CIRCLE\n";
		cout << "Radius: " << C[b].getR() << endl;
		cout << "Area: " << C[b].getArea() << endl;
		cout << "Coordinates: (" << C[b].x << "," << C[b].y << ")" << endl;
	}
	else if (a == 2) {
		cout << "SQUARE\n";
		cout << "Length: " << S[b].getL() << endl;
		cout << "Width: " << S[b].getW() << endl;
		cout << "Area: " << S[b].getArea() << endl;
		cout << "Coordinates: (" << S[b].x << "," << S[b].y << ")" << endl;
	}
	else if (a == 3) {
		cout << "RECTANGLE\n";
		cout << "Length: " << R[b].getL() << endl;
		cout << "Width: " << R[b].getW() << endl;
		cout << "Area: " << R[b].getArea() << endl;
		cout << "Coordinates: (" << R[b].x << "," << R[b].y << ")" << endl;
	}
	else if (a == 4) {
		cout << "TRIANGLE\n";
		cout << "Length: " << T[b].getL() << endl;
		cout << "Width: " << T[b].getW() << endl;
		cout << "Area: " << T[b].getArea() << endl;
		cout << "Coordinates: (" << T[b].x << "," << T[b].y << ")" << endl;
	}
	else {
		cout << "Form does not exist!\n";
	}
}

Shape Canvas:: operator[](string s) {
	//int x;
	Shape* obj;
	string temp = toUpper(s);
	if (temp == "CIRCLE") {
		size[0]++;
		obj = new Shape[size[0]];
		for (int k = 0; k < size[0]; k++) {
			if (k == size[0] - 1) {
				C = obj;
				return (C[k]);
			}
			obj[k].x = C[k].x;
			obj[k].y = C[k].y;
			obj[k].l = 0;
			obj[k].w = 0;
			obj[k].r = C[k].getR();
			obj[k].area = 3.142 * C[k].r * C[k].r;
		}
	}
	else if(temp == "SQUARE") {
		size[1]++;
		obj = new Shape[size[1]];
		for (int k = 0; k < size[1]; k++) {
			if (k == size[1] - 1) {
				S = obj;
				return (S[k]);
			}
			obj[k].x = S[k].x;
			obj[k].y = S[k].y;
			obj[k].l = S[k].getL();
			obj[k].w = S[k].getL();
			obj[k].r = 0;
			obj[k].area = S[k].l * S[k].w;
		}
	}
	else if (temp == "RECTANGLE") {
		size[2]++;
		obj = new Shape[size[2]];
		for (int k = 0; k < size[2]; k++) {
			if (k == size[2] - 1) {
				R = obj;
				return (R[k]);
			}
			obj[k].x = R[k].x;
			obj[k].y = R[k].y;
			obj[k].l = R[k].getL();
			obj[k].w = R[k].getL();
			obj[k].r = 0;
			obj[k].area = R[k].l * R[k].w;
		}
	}
	else if (temp == "TRIANGLE") {
		size[3]++;
		obj = new Shape[size[3]];
		for (int k = 0; k < size[3]; k++) {
			if (k == size[3] - 1) {
				T = obj;
				return (T[k]);
			}
			obj[k].x = T[k].x;
			obj[k].y = T[k].y;
			obj[k].l = T[k].getL();
			obj[k].w = T[k].getL();
			obj[k].r = 0;
			obj[k].area = (T[k].l * T[k].w)/2.0;
		}
	}
	cout << "Invalid Shape!\n";
	obj = new Shape;
	return (*obj);
	//return S[x];
}

void Canvas:: operator=(Canvas& C1) {
	for (int i = 0; i < 4; i++) {
		size[i] = C1.getSize(i);
	}
	C = new Shape[size[0]];
	for (int k = 0; k < size[0]; k++) {
		C[k].x = C1.C[k].x;
		C[k].y = C1.C[k].y;
		C[k].l = 0;
		C[k].w = 0;
		C[k].r = C1.C[k].getR();
		C[k].area = 3.142 * C[k].r * C[k].r;
	}
	S = new Shape[size[1]];
	for (int k = 0; k < size[1]; k++) {
		S[k].x = C1.S[k].x;
		S[k].y = C1.S[k].y;
		S[k].l = C1.S[k].getL();
		S[k].w = S[k].l;
		S[k].r = 0;
		S[k].area = S[k].l * S[k].w;
	}
	R = new Shape[size[2]];
	for (int k = 0; k < size[2]; k++) {
		R[k].x = C1.R[k].x;
		R[k].y = C1.R[k].y;
		R[k].l = C1.R[k].getL();
		R[k].w = C1.R[k].getW();
		R[k].r = 0;
		R[k].area = R[k].l * R[k].w;
	}
	T = new Shape[size[3]];
	for (int k = 0; k < size[3]; k++) {
		T[k].x = C1.T[k].x;
		T[k].y = C1.T[k].y;
		T[k].l = C1.T[k].getL();
		T[k].w = C1.T[k].getW();
		T[k].r = 0;
		T[k].area = (T[k].l * T[k].w) / 2.0;
	}
	//return C1;
}

void Shape:: operator+=(Shape& S1) {
	form = S1.form;
	l = S1.l;
	w = S1.w;
	x = S1.x;
	y = S1.y;
	r = S1.r;
	area = S1.area; 
}

void Canvas:: operator=(Shape& S1) {
	Shape* obj;
	if (S1.form == 1) {
		size[1]++;
		obj = new Shape[size[1]];
		for (int k = 0; k < size[1]; k++) {
			if (k == size[1] - 1) {
				S = obj;
				obj[k].x = S1.x;
				obj[k].y = S1.y;
				obj[k].l = S1.getL();
				obj[k].w = S1.getL();
				obj[k].r = 0;
				obj[k].area = S1.area;
				//return (S[k]);
			}
			obj[k].x = S[k].x;
			obj[k].y = S[k].y;
			obj[k].l = S[k].getL();
			obj[k].w = S[k].getL();
			obj[k].r = 0;
			obj[k].area = S[k].l * S[k].w;
		}
	}
	else if (S1.form == 2) {
		size[1]++;
		obj = new Shape[size[1]];
		for (int k = 0; k < size[1]; k++) {
			if (k == size[1] - 1) {
				obj[k].x = S1.x;
				obj[k].y = S1.y;
				obj[k].l = S1.getL();
				obj[k].w = S1.getL();
				obj[k].r = 0;
				obj[k].area = S1.area;
				S = obj;
				//return (S[k]);
			}
			obj[k].x = S[k].x;
			obj[k].y = S[k].y;
			obj[k].l = S[k].getL();
			obj[k].w = S[k].getL();
			obj[k].r = 0;
			obj[k].area = S[k].l * S[k].w;
		}
	}
	else if (S1.form == 3) {
		size[2]++;
		obj = new Shape[size[2]];
		for (int k = 0; k < size[2]; k++) {
			if (k == size[2] - 1) {
				obj[k].x = S1.x;
				obj[k].y = S1.y;
				obj[k].l = S1.getL();
				obj[k].w = S1.getL();
				obj[k].r = 0;
				obj[k].area = S1.area;
				R = obj;
				//return (R[k]);
			}
			obj[k].x = R[k].x;
			obj[k].y = R[k].y;
			obj[k].l = R[k].getL();
			obj[k].w = R[k].getL();
			obj[k].r = 0;
			obj[k].area = R[k].l * R[k].w;
		}
	}
	else if (S1.form == 4) {
		size[3]++;
		obj = new Shape[size[3]];
		for (int k = 0; k < size[3]; k++) {
			if (k == size[3] - 1) {
				obj[k].x = S1.x;
				obj[k].y = S1.y;
				obj[k].l = S1.getL();
				obj[k].w = S1.getL();
				obj[k].r = 0;
				obj[k].area = S1.area;
				T = obj;
				//return (T[k]);
			}
			obj[k].x = T[k].x;
			obj[k].y = T[k].y;
			obj[k].l = T[k].getL();
			obj[k].w = T[k].getL();
			obj[k].r = 0;
			obj[k].area = (T[k].l * T[k].w)/2.0;
		}
	}
}

Canvas& Canvas:: operator+(Canvas& C1) {
	for (int i = 0; i < 4; i++) {
		size[i] = C1.getSize(i);
	}
	Canvas* obj = new Canvas;
	obj->C = new Shape[size[0]+C1.size[0]];
	int i = 0;
	for (int k = 0; k < size[0]; k++) {
		obj->C[i].x = C[k].x;
		obj->C[i].y = C[k].y;
		obj->C[i].l = 0;
		obj->C[i].w = 0;
		obj->C[i].r = C[k].getR();
		obj->C[i].area = C[k].getArea();
		i++;
	}
	for (int k = 0; k < C1.size[0]; k++) {
		obj->C[i].x = C1.C[k].x;
		obj->C[i].y = C1.C[k].y;
		obj->C[i].l = 0;
		obj->C[i].w = 0;
		obj->C[i].r = C1.C[k].getR();
		obj->C[i].area = C1.C[k].getArea();
		i++;
	}
	obj->S = new Shape[size[1]+C1.size[1]];
	i = 0;
	for (int k = 0; k < size[1]; k++) {
		obj->S[i].x = S[k].x;
		obj->S[i].y = S[k].y;
		obj->S[i].l = S[k].getL();
		obj->S[i].w = S[k].l;
		obj->S[i].r = 0;
		obj->S[i].area = S[k].l * S[k].w;
		i++;
	}
	for (int k = 0; k < C1.size[1]; k++) {
		obj->S[i].x = C1.S[k].x;
		obj->S[i].y = C1.S[k].y;
		obj->S[i].l = C1.S[k].getL();
		obj->S[i].w = C1.S[k].l;
		obj->S[i].r = 0;
		obj->S[i].area = C1.S[k].l * C1.S[k].w;
		i++;
	}
	obj->R = new Shape[size[2]+C1.size[2]];
	i = 0;
	for (int k = 0; k < size[2]; k++) {
		obj->R[i].x = R[k].x;
		obj->R[i].y = R[k].y;
		obj->R[i].l = R[k].getL();
		obj->R[i].w = R[k].getW();
		obj->R[i].r = 0;
		obj->R[i].area = R[k].l * R[k].w;
		i++;
	}
	for (int k = 0; k < size[2]; k++) {
		obj->R[i].x = C1.R[k].x;
		obj->R[i].y = C1.R[k].y;
		obj->R[i].l = C1.R[k].getL();
		obj->R[i].w = C1.R[k].getW();
		obj->R[i].r = 0;
		obj->R[i].area = C1.R[k].l * C1.R[k].w;
		i++;
	}
	obj->T = new Shape[size[3]+C1.size[3]];
	i = 0;
	for (int k = 0; k < size[3]; k++) {
		obj->T[i].x = T[k].x;
		obj->T[i].y = T[k].y;
		obj->T[i].l = T[k].getL();
		obj->T[i].w = T[k].getW();
		obj->T[i].r = 0;
		obj->T[i].area = T[k].getArea();
		i++;
	}
	for (int k = 0; k < size[3]; k++) {
		obj->T[i].x = C1.T[k].x;
		obj->T[i].y = C1.T[k].y;
		obj->T[i].l = C1.T[k].getL();
		obj->T[i].w = C1.T[k].getW();
		obj->T[i].r = 0;
		obj->T[i].area = C1.T[k].getArea();
		i++;
	}
	return(*obj);
}

void Canvas::Display() {
	for (int b = 0; b < size[0]; b++) {
		cout << "CIRCLE\n";
		cout << "Radius: " << C[b].r << endl;
		cout << "Area: " << C[b].area << endl;
		cout << "Coordinates: (" << C[b].x << "," << C[b].y << ")" << endl;
	}
	for (int b = 0; b < size[1];b++) {
		cout << "SQUARE\n";
		cout << "Length: " << S[b].l << endl;
		cout << "Width: " << S[b].w << endl;
		cout << "Area: " << S[b].area << endl;
		cout << "Coordinates: (" << S[b].x << "," << S[b].y << ")" << endl;
	}
	for (int b = 0; b < size[2];b++) {
		cout << "RECTANGLE\n";
		cout << "Length: " << R[b].l << endl;
		cout << "Width: " << R[b].w << endl;
		cout << "Area: " << R[b].area << endl;
		cout << "Coordinates: (" << R[b].x << "," << R[b].y << ")" << endl;
	}
	for (int b = 0; b < size[3];b++){
		cout << "TRIANGLE\n";
		cout << "Length: " << T[b].l << endl;
		cout << "Width: " << T[b].w << endl;
		cout << "Area: " << T[b].area << endl;
		cout << "Coordinates: (" << T[b].x << "," << T[b].y << ")" << endl;
	}
}