 // I declare that the assignment here submitted is original
 // except for source material explicitly acknowledged,
 // and that the same or closely related material has not been
 // previously submitted for another course.
 // I also acknowledge that I am aware of University policy and
 // regulations on honesty in academic work, and of the disciplinary
 // guidelines and procedures applicable to breaches of such
 // policy and regulations, as contained in the website.
 //
 // University Guideline on Academic Honesty:
 //   http://www.cuhk.edu.hk/policy/academichonesty/
 // Faculty of Engineering Guidelines to Academic Honesty:
 //   http://www.erg.cuhk.edu.hk/erg-intra/upload/documents/ENGG_Discipline.pdf
 //
 // Student Name  : Lo Yu Ho
 // Student ID    : 1155004076
 // Student Name  : Ting Kwok On
 // Student ID    : 1155002742

#pragma once
// these are example objects - very simple - hopefully yours will be nicer!

// Cars - cars are actually just static, rigid objects
// A driving behavior is added to move them around
//



#include "../GrObject.H"



// keep a pointer to the texture, that way we only look it up the first time
class Texture;

class Car : public GrObject {
 public:
	Texture* sideTexture;
	Texture* frontTexture;

  Car(char* type, int color);
  Color color;

  // this draw the whole car - subclasses just redefine "body"
  virtual void draw(DrawingState*);
  virtual void drawAfter(DrawingState*);

  virtual void drawBody(DrawingState*);
  
	float w;		// half width
	float f; 		// length of front part
	float r; 		// length of back part
	float h; 		// height of ground
	float m; 		// height of motor
	float t; 		// height of back part
	float s; 		// slope of windshield
	float a; 		// rake of hood
	float sr;		// side rake of upper part
	float br;		// back rake of upper part

	float dhw;		// half width
	float dhf; 		// length of front part
	float dhr; 		// length of back part
	float dhh; 		// height of ground
	float dhm; 		// height of motor
	float dht; 		// height of back part
	float dhs; 		// slope of windshield
	float dha; 		// rake of hood
};

class SUV : public Car {
public:
  SUV(int color);
};
class HatchBack : public Car {
public:
  HatchBack(int color);
};

class Van : public Car {
public:
  Van(int color);
};

//added*****************************************************************
class MyCar : public Car {
public:
  MyCar(int color);
};
//**********************************************************************

//added*****************************************************************
class MyCar3 : public Car {
public:
  MyCar3(int color);
};
//**********************************************************************

//added*****************************************************************
class Car1 : public GrObject {
 public:
	Texture* sideTexture;
	Texture* frontTexture;

  Car1(char* type, int color);
  Color color;

  // this draw the whole car - subclasses just redefine "body"
  virtual void draw(DrawingState*);
  virtual void drawAfter(DrawingState*);
  void blink(float time);

  virtual void drawBody(DrawingState*);
  
  int blink_rotate_angle;
  int blinking;
	float w;		// half width
	float f; 		// length of front part
	float r; 		// length of back part
	float h; 		// height of ground
	float m; 		// height of motor
	float t; 		// height of back part
	float s; 		// slope of windshield
	float a; 		// rake of hood
	float sr;		// side rake of upper part
	float br;		// back rake of upper part
};
//**********************************************************************

//added*****************************************************************
class MyCar2 : public Car1 {
public:
  MyCar2(int color);
};
//**********************************************************************




class DingCar0 : public GrObject {
 public:
	Texture* sideTexture;
	Texture* frontTexture;

  DingCar0(char* type, int color);
  Color color;
  // this draw the whole car - subclasses just redefine "body"
  virtual void draw(DrawingState*);
  virtual void drawAfter(DrawingState*);
  virtual void drawBody(DrawingState*);
  
	float w;		// half width
	float f; 		// length of front part
	float r; 		// length of back part
	float h; 		// height of ground
	float m; 		// height of motor
	float t; 		// height of back part
	float s; 		// slope of windshield
	float a; 		// rake of hood
	float sr;		// side rake of upper part
	float br;		// back rake of upper part

	//box
	float boxw;		// half width
	float boxf; 		// length of front part
	float boxr; 		// length of back part
	float boxh; 		// height of ground
	float boxm; 		// height of motor
	float boxt; 		// height of back part
	float boxs; 		// slope of windshield
	float boxa; 		// rake of hood

	//driving head
	float dhw;		// half width
	float dhf; 		// length of front part
	float dhr; 		// length of back part
	float dhh; 		// height of ground
	float dhm; 		// height of motor
	float dht; 		// height of back part
	float dhs; 		// slope of windshield
	float dha; 		// rake of hood
};
class MyDingCar0 : public DingCar0 {
public:
  MyDingCar0(int color);
};




class DingCar1 : public GrObject {
 public:
	Texture* sideTexture;
	Texture* frontTexture;

  DingCar1(char* type, int color);
  Color color;
  // this draw the whole car - subclasses just redefine "body"
  virtual void draw(DrawingState*);
  virtual void drawAfter(DrawingState*);
  virtual void drawBody(DrawingState*);
  
	float w;		// half width
	float f; 		// length of front part
	float r; 		// length of back part
	float h; 		// height of ground
	float m; 		// height of motor
	float t; 		// height of back part
	float s; 		// slope of windshield
	float a; 		// rake of hood
	float sr;		// side rake of upper part
	float br;		// back rake of upper part

	//driving head
	float dhw;		// half width
	float dhf; 		// length of front part
	float dhr; 		// length of back part
	float dhh; 		// height of ground
	float dhm; 		// height of motor
	float dht; 		// height of back part
	float dhs; 		// slope of windshield
	float dha; 		// rake of hood
};

class MyDingCar1 : public DingCar1 {
public:
  MyDingCar1(int color);
};