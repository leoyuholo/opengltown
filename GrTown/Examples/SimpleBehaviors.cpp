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
#include "../GrTown_PCH.H"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../MMatrix.H"
#include "../GrObject.H"

#include "SimpleBehaviors.H"

//added*****************************************************************
MoveForward::MoveForward(GrObject * o, float sp) : Behavior(o), speed(sp)
{
}

void MoveForward::simulateUntil(unsigned long time)
{
	unsigned long dt = time - lastV;	// how long since last update
	float secs = ((float) dt) / 1000;	// convert ms to sec
	lastV = time;
	owner->transform[3][0] += owner->transform[2][0] * secs * speed;
	owner->transform[3][1] += owner->transform[2][1] * secs * speed;
	owner->transform[3][2] += owner->transform[2][2] * secs * speed;

	//owner->transform[3][0] += owner->transform[0][0] * secs * speed;
	//owner->transform[3][1] += owner->transform[0][1] * secs * speed;
	//owner->transform[3][2] += owner->transform[0][2] * secs * speed;

	lastV = time;
}

Video::Video(GrObject * o, float sp) : Behavior(o), speed(sp)
{
}
void Video::simulateUntil(unsigned long time)
{
	Airship * a = (Airship *)owner;
	a->update((float)(time-lastV) * speed);
	lastV = time;
}
Blink::Blink(GrObject * o, float sp) : Behavior(o), speed(sp)
{
}
void Blink::simulateUntil(unsigned long time)
{
	Car1 * a = (Car1 *)owner;
	a->blink((float)(time-lastV) * speed);
	lastV = time;
}

Walk::Walk(GrObject * o, float sp) : Behavior(o), speed(sp)
{
}
void Walk::simulateUntil(unsigned long time)
{
	Robot * a = (Robot *)owner;
	a->Walk((float)(time-lastV) * speed);
	lastV = time;
}
Clock::Clock(GrObject * o, float sp) : Behavior(o), speed(sp)
{
}
void Clock::simulateUntil(unsigned long time)
{
	ClockTower * a = (ClockTower *)owner;
	a->clock((float)(time-lastV) * speed);
	lastV = time;
}
Falling::Falling(GrObject * o, float sp) : Behavior(o), speed(sp)
{
}
void Falling::simulateUntil(unsigned long time)
{
	unsigned long dt = time - lastV;	// how long since last update
	float secs = ((float) dt) / 1000;	// convert ms to sec
	lastV = time;
	owner->transform[3][0] -= owner->transform[1][0] * secs * speed;
	owner->transform[3][1] -= owner->transform[1][1] * secs * speed;
	owner->transform[3][2] -= owner->transform[1][2] * secs * speed;

	lastV = time;
}
//**********************************************************************

//////////////////////////////////////////////////////////////////////
// a trick - since we don't care much about what the rotation is (only
// the rate), we can tie the rotation to the absolute time
Spin::Spin(GrObject* o, float v) : Behavior(o), vel(v)
{
}
void Spin::simulateUntil(unsigned long t)
{
	// remember position
	float x = owner->transform[3][0];
	float y = owner->transform[3][1];
	float z = owner->transform[3][2];
	// set rotation based on time
	rotMatrix(owner->transform, 'y', vel * static_cast<float>(t));
	// put the position back
	owner->transform[3][0] = x;
	owner->transform[3][1] = y;
	owner->transform[3][2] = z;

	lastV = t;
}

////////////////////////////////////////////////////////////////////////
ForwardAlways::ForwardAlways(GrObject* o, float v)
	: Behavior(o), vel(v)
{
}
void ForwardAlways::simulateUntil(unsigned long t)
{
	unsigned long dt = t - lastV;	// how long since last update
	float secs = ((float) dt) / 1000;	// convert ms to sec
	lastV = t;
	owner->transform[3][0] += owner->transform[2][0] * secs * vel;
	owner->transform[3][1] += owner->transform[2][1] * secs * vel;
	owner->transform[3][2] += owner->transform[2][2] * secs * vel;

	lastV = t;
}

////////////////////////////////////////////////////////////////////////
TurnAlways::TurnAlways(GrObject* o, float v)
	: Behavior(o), vel(v)
{
}
void TurnAlways::simulateUntil(unsigned long t)
{
	unsigned long dt = t - lastV;	// how long since last update
	float secs = ((float) dt) / 1000;	// convert ms to sec
	lastV = t;
	Matrix delta, newT;
	rotMatrix(delta,'Y',secs * vel);
	multMatrix(delta,owner->transform,newT);
	copyMatrix(newT,owner->transform);

	lastV = t;
}

