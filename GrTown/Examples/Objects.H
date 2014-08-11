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

/// GraphicsTown2006 
// written by Michael   - originally written Fall, 2000
// updated Fall, 2005
// updated Fall, 2006 - new texture manager, improvements for behaviors

//
// A set of relatively simple objects to get the ideas across
// these are mainly here as examples - real objects should be more
// interesting 

#include "../GrObject.H"
#include "../DrawingState.H"
#include "SimpleBehaviors.H"
//*******************************************added by ding
class Robot : public GrObject {
public:
	Robot(void);
  virtual void draw(DrawingState*);
  void Walk(float time);
  int left_rotate_angle;
  int left_movement;
  int right_rotate_angle;
  int right_movement;
  //  virtual void drawAfter(DrawingState*);
//  virtual void drawBody(DrawingState*);
};


//added*****************************************************************
class Snow : public GrObject {
public:
	Snow(float x, float y, float z);
	virtual void draw(DrawingState*);
};

class Airship : public GrObject {
public:
  Airship(float x, float y, float z, float s, int aa, float r=1, float g=.2, float b=.2);
  Color color;
  float size;
  int antiAlias;
  void update(float time);
  char * pic[10];
  int frame;
  int cumulate;
  int beam_rotate_angle;
  virtual void draw(DrawingState*);
  virtual void drawAfter(DrawingState*);
};
//**********************************************************************
// mainly for debugging
class Cube : public GrObject {
public:
  Cube(float x, float y, float z, float s, float r=1, float g=.2, float b=.2);
  Color color;
  float size;
  virtual void draw(DrawingState*);
};


class TestCubes : public GrObject {
public:
  TestCubes();
  virtual void draw(DrawingState*);
};

// this object uses a shader!
class ShadedCube : public GrObject {
public:
  ShadedCube(float x, float y, float z, float s, float r=1, float g=.2, float b=.2);
  Color color;
  float size;
  virtual void draw(DrawingState*);
};




