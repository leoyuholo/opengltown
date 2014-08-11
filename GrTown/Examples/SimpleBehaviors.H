#pragma once
/// GraphicsTown2006 
// written by Michael   - originally written Fall, 2000
// updated Fall, 2005
// updated Fall, 2006 - new texture manager, improvements for behaviors

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

// simple example behaviors - something to learn from

#include "../Behavior.H"

#include "Objects.H"
#include "Cars.H"
#include "Suburbs.H"

//added*****************************************************************
class MoveForward : public Behavior
{
public:
	MoveForward(GrObject* owner, float sp = 2.0f);
	virtual void simulateUntil(unsigned long);
private:
	float speed;
};

class Video : public Behavior
{
public:
	Video(GrObject* owner, float sp = 1.0f);
	virtual void simulateUntil(unsigned long);
private:
	float speed;
};
class Walk : public Behavior
{
public:
	Walk(GrObject* owner, float sp = 1.0f);
	virtual void simulateUntil(unsigned long);
private:
	float speed;
};

class Blink : public Behavior
{
public:
	Blink(GrObject* owner, float sp = 1.0f);
	virtual void simulateUntil(unsigned long);
private:
	float speed;
};
class Clock : public Behavior
{
public:
	Clock(GrObject* owner, float sp = 1.0f);
	virtual void simulateUntil(unsigned long);
private:
	float speed;
};
class Falling : public Behavior
{
public:
	Falling(GrObject* owner, float sp = 1.0f);
	virtual void simulateUntil(unsigned long);
	float speed;
};
//**********************************************************************

////////////////////////////////////////////////////////////////////////
// a simple behavior: spin around the center point
// velocity (roughly) is radians per timestep (millisecond)
//
// the blasts away the rotation part of the object's transform matrix,
// but doesn't effect the translation part
class Spin : public Behavior {
public:
	Spin(GrObject* owner, float vel = .005);

	float vel;					// we need to remember this

	virtual void simulateUntil(unsigned long);
};

////////////////////////////////////////////////////////////////////////
// these examples directly update the object's matrix
// - its a bit harder to do anything complicated this way
//
// always makes things go forward - you probably want to change its
// direction using another behavior
class ForwardAlways : public Behavior {
public:
	ForwardAlways(GrObject* owner, float vel = 10);
	float vel;
	virtual void simulateUntil(unsigned long);
};
class TurnAlways : public Behavior {
public:
	TurnAlways(GrObject* owner, float vel = .1);
	float vel;
	virtual void simulateUntil(unsigned long);
};


