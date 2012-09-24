/*
*Scott Mogul
*HW02
*
*/
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Resources.h"
#include "cinder/text.h"
#include "cinder/gl/Texture.h"
#include "Node.h"
#include "Shape.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HW02App : public AppBasic {
	public:
		void setup();	
		void keyDown( KeyEvent event);
		void update();
		void draw();
		
	private:
		Surface* mySurface_; //The Surface object whose pixel array we will modify
		static const int Width=800; //width of visible window
		static const int Height=600; //height of visible window
		static const int Size=1024; //surface size

		void makeTextBox();

		Node *sentinel;
		Node *nodeOne;
		Node *nodeTwo;
		Node *nodeThree;
		Node *nodeFour;

		gl::Texture *text_texture;
		bool displayMenu;
		TextBox *text_box;
};

void HW02App::setup(){
	mySurface_ = new Surface(Size,Size,false);
	displayMenu = true;
	makeTextBox();

	Shape *shapeOne = new Shape(Vec2f(500, 150), 100);
	Shape *shapeTwo = new Shape(Vec2f(500, 200), 75);
	Shape *shapeThree = new Shape(Vec2f(500, 250), 50);
	Shape *shapeFour = new Shape(Vec2f(500, 290), 35);

	nodeOne = new Node(shapeOne);
	nodeTwo = new Node(shapeTwo);
	nodeThree = new Node(shapeThree);
	nodeFour = new Node(shapeFour);
	sentinel = new Node(nodeOne, nodeFour);

	nodeOne -> pointers(nodeTwo, sentinel);
	nodeTwo -> pointers(nodeThree, nodeOne);
	nodeThree -> pointers(nodeFour, nodeTwo);
	nodeFour -> pointers(sentinel, nodeThree);
}
/*
*makeTextBox inspired by github user rileycr (Riley Cooper)
*/
void HW02App::makeTextBox(){
	text_box = new TextBox();
	text_box -> alignment( TextBox::CENTER );
	text_box -> setText("Press ? to close menu \n To reverse the list press r \n Send current item to back of list press b \n");
	text_box -> setFont(Font("Times", 40));
	text_box->setBackgroundColor(ColorA(0,0,0,0.5));
	text_texture = new gl::Texture(text_box -> render());
}

/*void HW02App::mouseDown( MouseEvent event ){
}*/

void HW02App::keyDown( KeyEvent event){
	
	if(event.getChar() == '?'){
		displayMenu = !displayMenu;
	}
	if(event.getChar() == 'r'){
		sentinel ->reverse(sentinel);
	}
	if(event.getCode() == 'b'){
		sentinel -> sendToBack(sentinel);
	}
	//Broken, don't try app will freeze 
	if(event.getCode() == 'f'){
		sentinel -> sendToFront(sentinel);
	}
}

void HW02App::update(){
	
}

void HW02App::draw(){
	
	gl::draw(*mySurface_);
	gl::clear( Color8u(50,200,100));
	Node* current_ = sentinel -> next_;
	do{
		current_ -> draw();
		current_  = current_ -> next_;
	} while(current_ != sentinel);

	if(displayMenu)
		gl::draw(*text_texture);
}


CINDER_APP_BASIC( HW02App, RendererGl )