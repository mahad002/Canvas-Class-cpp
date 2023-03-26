#include <iostream>
#include "Canvas.h"

using namespace std;

int main() {
	Canvas C;
	Shape s_Obj(1, 2, 2, 10); //circle made at center 2,2 and radius=10
	C["Circle"] += s_Obj; //should add the object to the canvas
	C(1, 0); //prints a certain shape in the canvas
	cout << "--------------------------------\n";
	C.Display();
	cout << "--------------------------------\n";
	Canvas C1;
	C1["Rectangle"] = Shape(3, 3, 4, 5, 10); //rectangle is added to Canvas C1
	C1.Display();
	cout << "--------------------------------\n";
	Canvas C3;
	//C3 = C1 ; //Canvas C3 will now have a circle and a rectangle
	C3.Display();
	cout << "--------------------------------\n";
	
	return 0;
}