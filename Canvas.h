#pragma once
#include<iostream>

using namespace std;

class Shape {
public:
	// think about the private data members...
	int x;
	int y;
	double l;
	double w;
	double r;
	double area;
	int form; // 1=cirle; 2=square; 3=rectangle; 4=triangle;
	bool test_perpendicular(int, int, int, int, int, int, double);
	double point_area(int, int, int, int, int, int);
	bool test_within(int, int, int, int, int, int, int, int);
public:


	int getForm() {
		return this->form;
	}
	void setForm(int form) {
		this->form = form;
	}

	int getX() {
		return this->x;
	}
	void setX(int x) {
		this->x = x;
	}

	int getY() {
		return this->y;
	}
	void setY(int y) {
		this->y = y;
	}

	double getL() {
		return this->l;
	}
	void setL(double l) {
		this->l = l;
	}


	double getW() {
		return this->w;
	}
	void setW(double w) {
		this->w = w;
	}


	double getR() {
		return this->r;
	}
	void setR(double r) {
		this->r = r;
	}

	double getArea() {
		return this->area;
	}
	void setArea(double area) {
		this->area = area;
	}

	// provide definitions of following functions...
	Shape();// default constructor
	Shape(int, double, double, int, int);//parameterized constructor that will allow to initialize different types of instances
	Shape(int, double, int, int);
	Shape operator=(const Shape&);
	void getArea(Shape&);//prints area
	bool overlapping(Shape);//determines if two Shapes are overlapping or not
	static Shape returnLargestShape(Shape*&, int);//a static function that returns the largest Shape from the array of Shapes, this functions should only work for the same shapes
	Shape& overlappingShapes(Shape*&,int);//a static function that returns an array of Shapes overlapping the largest Shape, this functions should only work for the same shapes

	double operator[](int);//whenever you have to access any information of shape
	void operator+=(Shape&);
	//~Shape();
};

const int TYPE_OF_SHAPES_PER_CANVAS = 10;

class Canvas {
private:
	// think of private data member carefully
	Shape* C;
	Shape* S;
	Shape* R;
	Shape* T;
	int size[4];
public:
	//implement necessary constructors
	int getSize(int i) {
		return size[i];
	}
	Canvas();
	Canvas(int i[]);
	Canvas(Canvas&);
	//operator[](Shape&); //returns the appropriate reference to add or remove the shape from the canvas
	Shape operator[](string); //Returns the shapes of a certain type “Circle” – all circles
	void operator=(Canvas&);
	void operator=(Shape&);
	void operator()(int, int); //prints the information of specific shape in the canvas
	Canvas& operator+(Canvas&); //adds two canvas and creates a third one with shapes of first two canvases – be careful of the limit of shapes per canvas
	operator string(); //converts the canvas information into a well-formatted string.It should include information of all types and shapes in it.
	void Display();
	~Canvas() {
		delete[] S;
	}
};

