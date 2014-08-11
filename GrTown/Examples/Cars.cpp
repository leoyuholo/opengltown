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

// cars.cpp - implementation of simple types of cars
// ============ TODO2: Complete this file to make it look natural ===============



#include "../GrTown_PCH.H"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../DrawingState.H"
#include "Cars.H"

#include <GL/glut.h>

/////////////////////////////////////////////////////
// car colors have names too
struct CarColors {
	char* name;
	int r,g,b;
};
CarColors cc[] = {
	{"red",220,30,30},
	{"white",225,225,225},
	{"black",50,50,70},
	{"green",30,225,30},
	{"blue",30,30,225},
	{"yellow",225,225,30}
};
const int nCarCols = 6;

///////////////////////////////////////////////////////
// the generic car...
int carCtr = 0;
Car::Car(char* name, int c) : GrObject(name,carCtr,cc[c%nCarCols].name)
{
  color((float) cc[c%nCarCols].r,(float) cc[c%nCarCols].g,(float) cc[c%nCarCols].b);
  rideAbove = 10;
  ridable = 1;

  // car params
	 w = 3.5;		// half of width
	 f = 3;		// length of front part
	 r = 6;		// length of back part
	 h = 1;		// height of ground
	 m = 1;		// height of motor
	 t = 1;		// height of back part
	 s = .3f;		// slope of windshield
	 a = .2f;		// rake of hood
	 sr = .1f;
	 br = .2f;

 	 dhw = 2.5;		// half of width
	 dhf = 3;		// length of front part
	 dhr = 6;		// length of back part
	 dhh = 1;		// height of ground
	 dhm = 1.5;		// height of motor
	 dht = 2;		// height of back part
	 dhs = .3f;		// slope of windshield
	 dha = .2f;		// rake of hood



	 // note: we can't actually load the textures now (since we don't have a GL context)
	 // so we just say that we don't have textures
	frontTexture = 0;
	sideTexture = 0;
}

// draw a wheel
//square root of 2 over 2
const float sqrt2_2 = .707106f;
float wc[9][2] = {
	{0,1}, {sqrt2_2,sqrt2_2}, {1,0}, {sqrt2_2,-sqrt2_2},
	{0,-1}, {-sqrt2_2,-sqrt2_2}, {-1,0}, {-sqrt2_2,sqrt2_2},
	{0,1}
};
static void drawWheel(float r, float w)
{
	int i=0;
	glNormal3f(-1,0,0);
	glBegin(GL_POLYGON);
	for(i=7; i>=0; i--)
		glVertex3f(w,wc[i][0]*r,wc[i][1]*r);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_QUAD_STRIP);
	for(i=0; i<9; i++) {
		glVertex3f(0,wc[i][0]*r,wc[i][1]*r);
		glVertex3f(w,wc[i][0]*r,wc[i][1]*r);
	}
	glEnd();

}

void Car::draw(DrawingState* d)
{

  // Draw four wheel 
  glColor3f(.1f,.1f,.1f);
  glPushMatrix();
	  glTranslatef(w-.5f,h,f-h);
	  drawWheel(h,1);
  glPopMatrix();
  glPushMatrix();
	  glTranslatef(w-.5f,h,f+r-h-1);
	  drawWheel(h,1);
  glPopMatrix();

  glPushMatrix();
	  glTranslatef(-w+.5f,h,f-h);
	  glRotatef(180,0,1,0);
	  drawWheel(h,1);
  glPopMatrix();
  glPushMatrix();
	  glTranslatef(-w+.5f,h,f+r-h-1);
	  glRotatef(180,0,1,0);
	  drawWheel(h,1);
  glPopMatrix();

  // Draw the body of the car
  glColor3fv(&color.r);
  drawBody(d);
}

  
static void drawBeam()
{
	const float cone_length = 20;
	int c;
	const float radius = 3;
	glBegin(GL_TRIANGLE_FAN);
	glColor4d(1,1,0,.8);
	glVertex3d(0,0,0);
    glColor4d(1,1,0,.2);
	for ( c=8; c>=0; c--) {
	  glNormal3f( wc[c][0], 0, wc[c][1]);
	  glVertex3f( wc[c][0]*radius, -cone_length, wc[c][1]*radius );
	}  		
	glEnd();
	glNormal3f(0,-1,0);
	glBegin(GL_POLYGON);
	for ( c=0; c<8; c++) {
	  glVertex3f( wc[c][0]*radius, -cone_length, wc[c][1]*radius );
	}  		
	glEnd();
}
// draw headlights at night
void Car::drawAfter(DrawingState* s)
{
  int tod = s->timeOfDay;
  bool daytime;
  if (tod >=6 && tod <= 19)
	daytime = true;
  else 
	daytime = false;
	
  if (!daytime) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);

	// Beam One
	glPushMatrix();			
	glTranslatef(-w*.7f,h+m/2,2);
	glRotated(90,1,0,0);
	drawBeam();
	glPopMatrix();
	// Beam 2
	glPushMatrix();			
	glTranslatef(w*.7f,h+m/2,2);
	glRotated(90,1,0,0);
	drawBeam();
	glPopMatrix();
	glFrontFace(GL_CW);
	glClearColor(1,1,1,1);
	glDisable(GL_BLEND);
  }
}

void Car::drawBody(DrawingState*)
{
	glColor3f(1.0,0.5,0.0);
	glPushMatrix();
		glTranslatef(w*.7,h+t*.7,0);
		glutSolidSphere(0.5,5,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-w*.7,h+t*.7,0);
		glutSolidSphere(0.5,5,5);
	glPopMatrix();
	glColor3fv(&color.r);	
	polygon(-4,  w,h,0., -w,h,0., -w,h+t,0., w,h+t,0.);
	polygon(4,  w,h,r+f , -w,h,r+f, -w,h+t,r+f, w,h+t,r+f);
	polygon(-4, -w,t+h,f+r, w,t+h,f+r, w,t+h,0., -w,t+h,0.);
	polygon(4, w,h,0., -w,h,0., -w,h,f+r, w,h,f+r);
    polygon(-4,  w,h,f+r, w,h,0., w,t+h,0., w,t+h,f+r);
	polygon(4, -w,h,f+r, -w,h,0., -w,t+h,0., -w,t+h,f+r);

	glTranslatef(0,t,f-2);
/*
		fetchTexture("DingCar0_dh_side.bmp");
	polygon(-4,  dhw,dhh,0., -dhw,dhh,0., -dhw,dhh+dht,0., dhw,dhh+dht,0.);
		fetchTexture("DingCar0_dh_updownback.bmp");
	polygon(-4, -dhw,dht+dhh,dhf+dhr, dhw,dht+dhh,dhf+dhr, dhw,dht+dhh,0., -dhw,dht+dhh,0.);
		fetchTexture("DingCar0_dh_side.bmp");
	polygon(4,  dhw,dhh,dhr+dhf , -dhw,dhh,dhr+dhf, -dhw,dhh+dht,dhr+dhf, dhw,dhh+dht,dhr+dhf);
	polygon(4, dhw,dhh,0., -dhw,dhh,0., -dhw,dhh,dhf+dhr, dhw,dhh,dhf+dhr);
    polygon(-4,  dhw,dhh,dhf+dhr, dhw,dhh,0., dhw,dht+dhh,0., dhw,dht+dhh,dhf+dhr);
	polygon(4, -dhw,dhh,dhf+dhr, -dhw,dhh,0., -dhw,dht+dhh,0., -dhw,dht+dhh,dhf+dhr);
*/
	 //driving head	

	//fonrt
	glColor3fv(&color.r);
	polygon(-4,  dhw,dhh,0., -dhw,dhh,0., -dhw,dhh+dht,0.5 , dhw,dhh+dht,0.5);
	//front screen
	glColor3f(0.2,0.2,0.9);
	polygon(-4,  dhw-0.1,dhh+0.4,-0.1, -dhw+0.1,dhh+0.4, -0.1, -dhw+0.1,dhh+dht-0.2, 0.5-0.1 , dhw-0.1,dhh+dht-0.2, 0.5-0.1);
	//up
	glColor3f(0.1,0.1,0.1);
	polygon(-4, -dhw,dht+dhh,dhf+dhr-0.5, dhw,dht+dhh,dhf+dhr-0.5, dhw,dht+dhh,0.5, -dhw,dht+dhh,0.5);
	//back
	glColor3fv(&color.r);
	polygon(4,  dhw,dhh,dhr+dhf , -dhw,dhh,dhr+dhf, -dhw,dhh+dht,dhr+dhf-0.5, dhw,dhh+dht,dhr+dhf-0.5);
	//back screen
	glColor3f(0.2,0.2,0.9);
	polygon(4,  dhw-0.2,dhh+0.3,dhr+dhf+0.1 , -dhw+0.2,dhh+0.3,dhr+dhf+0.1, -dhw+0.2,dhh+dht-0.1,dhr+dhf-0.5+0.1, dhw-0.2,dhh+dht-0.1,dhr+dhf-0.5+0.1);


	glColor3fv(&color.r);
	//down
	polygon(4, dhw,dhh,0., -dhw,dhh,0., -dhw,dhh,dhf+dhr, dhw,dhh,dhf+dhr);
    
	//right
	glColor3fv(&color.r);
	polygon(-4,  dhw,dhh,dhf+dhr, dhw,dhh,0., dhw,dht+dhh,0.5, dhw,dht+dhh,dhf+dhr-0.5);
	//right Screen
	glColor3f(0.2,0.2,0.9);
	polygon(-4,  dhw+0.1,dhh+0.2,dhf+dhr-0.2, dhw+0.1,dhh+0.2,0.2, dhw+0.1,dht+dhh-0.2,0.5+0.2, dhw+0.1,dht+dhh-0.2,dhf+dhr-0.5-0.2);
	//left
	glColor3fv(&color.r);
	polygon(4, -dhw,dhh,dhf+dhr, -dhw,dhh,0., -dhw,dht+dhh,0.5, -dhw,dht+dhh,dhf+dhr-0.5);
	// left screeen
	glColor3f(0.2,0.2,0.9);
	polygon(4, -dhw-0.1,dhh+0.2,dhf+dhr-0.2, -dhw-0.1,dhh+0.2,0.2, -dhw-0.1,dht+dhh-0.2,0.5+0.2, -dhw-0.1,dht+dhh-0.2,dhf+dhr-0.5-0.2);

	//=============================================================
	// Now the cars are simply boxes with different hights. 
    // TODO2: To make the cars look more realistic and add texutres. 

}


/***********************************************************************/
// simple car: a sport-utility
SUV::SUV(int c) : Car("SUV",c)
{
	 w = 3.5;		// half of width
	 f = 3;		// length of front part
	 r = 6;		// length of back part
	 h = 1;		// height of ground
	 m = 1;		// height of motor
	 t = 1;		// height of back part
	 s = .3f;		// slope of windshield
	 a = .2f;		// rake of hood
	 sr = .1f;
	 br = .2f;

 	 dhw = 2.5;		// half of width
	 dhf = 2;		// length of front part
	 dhr = 5;		// length of back part
	 dhh = 1;		// height of ground
	 dhm = 1.5;		// height of motor
	 dht = 2;		// height of back part
	 dhs = .3f;		// slope of windshield
	 dha = .1f;		// rake of hood

}


// another set makes a van...
Van::Van(int c) : Car("Van",c)
{
	 w = 3;		// half of width
	 f = 2;		// length of front part
	 r = 5;		// length of back part
	 h = 1;		// height of ground
	 m = 2.5;	// height of motor
	 t = 2;		// height of back part
	 s = .3f;		// slope of windshield
	 a = 1.f;		// rake of hood
	 sr = .5f;
	 br = .5f;

	 dhw = 2.5;		// half of width
	 dhf = 2;		// length of front part
	 dhr = 3;		// length of back part
	 dhh = 1;		// height of ground
	 dhm = 1.5;		// height of motor
	 dht = 2;		// height of back part
	 dhs = .3f;		// slope of windshield
	 dha = .1f;		// rake of hood
}

//added*****************************************************************

MyCar3::MyCar3(int c) : Car("MyCar3",c)
{
	 w = 3.5;		// half of width
	 f = 2;		// length of front part
	 r = 10;		// length of back part
	 h = 1;		// height of ground
	 m = 2.5;		// height of motor
	 t = 5;		// height of back part
	 s = .6f;		// slope of windshield
	 a = .2f;		// rake of hood
	 sr = .5f;
	 br = .5f;

}
//**********************************************************************


//added*****************************************************************
MyCar::MyCar(int c) : Car("MyCar",c)
{
	 w = 3;		// half of width
	 f = 2;		// length of front part
	 r = 8;		// length of back part
	 h = 1;		// height of ground
	 m = 2.5;	// height of motor
	 t = 5;		// height of back part
	 s = .3f;		// slope of windshield
	 a = 1.f;		// rake of hood
	 sr = .5f;
	 br = .5f;
}
//**********************************************************************

//added*****************************************************************
Car1::Car1(char* name, int c) : GrObject(name,carCtr,cc[1].name)
{
  color((float) cc[1].r,(float) cc[1].g,(float) cc[1].b);
  rideAbove = 10;
  ridable = 1;

  // car params
	 w = 3.5;		// half of width
	 f = 3;		// length of front part
	 r = 6;		// length of back part
	 h = 1;		// height of ground
	 m = 1.5;		// height of motor
	 t = 4;		// height of back part
	 s = .3f;		// slope of windshield
	 a = .2f;		// rake of hood
	 sr = .1f;
	 br = .2f;

	 // note: we can't actually load the textures now (since we don't have a GL context)
	 // so we just say that we don't have textures
	frontTexture = 0;
	sideTexture = 0;
}

//// draw a wheel
////square root of 2 over 2
//const float sqrt2_2 = .707106f;
//float wc[9][2] = {
//	{0,1}, {sqrt2_2,sqrt2_2}, {1,0}, {sqrt2_2,-sqrt2_2},
//	{0,-1}, {-sqrt2_2,-sqrt2_2}, {-1,0}, {-sqrt2_2,sqrt2_2},
//	{0,1}
//};
//static void drawWheel(float r, float w)
//{
//	int i=0;
//	glNormal3f(1,0,0);
//	glBegin(GL_POLYGON);
//	for(i=7; i>=0; i--)
//		glVertex3f(w,wc[i][0]*r,wc[i][1]*r);
//	glEnd();
//	glBegin(GL_QUAD_STRIP);
//	for(i=0; i<9; i++) {
//		glVertex3f(0,wc[i][0]*r,wc[i][1]*r);
//		glVertex3f(w,wc[i][0]*r,wc[i][1]*r);
//	}
//	glEnd();
//
//}

void Car1::draw(DrawingState* d)
{

  // Draw four wheel 
  glColor3f(.1f,.1f,.1f);
  glPushMatrix();
	  glTranslatef(w-.5f,h,f-h);
	  drawWheel(h,1);
  glPopMatrix();
  glPushMatrix();
	  glTranslatef(w-.5f,h,f+r-h-1);
	  drawWheel(h,1);
  glPopMatrix();

  glPushMatrix();
	  glTranslatef(-w+.5f,h,f-h);
	  glRotatef(180,0,1,0);
	  drawWheel(h,1);
  glPopMatrix();
  glPushMatrix();
	  glTranslatef(-w+.5f,h,f+r-h-1);
	  glRotatef(180,0,1,0);
	  drawWheel(h,1);
  glPopMatrix();

  // Draw the body of the car
  glColor3fv(&color.r);
  drawBody(d);
}

  
//static void drawBeam()
//{
//	const float cone_length = 20;
//	int c;
//	const float radius = 3;
//	glBegin(GL_TRIANGLE_FAN);
//	glColor4d(1,1,0,.8);
//	glVertex3d(0,0,0);
//    glColor4d(1,1,0,.2);
//	for ( c=8; c>=0; c--) {
//	  glNormal3f( wc[c][0], 0, wc[c][1]);
//	  glVertex3f( wc[c][0]*radius, -cone_length, wc[c][1]*radius );
//	}  		
//	glEnd();
//	glNormal3f(0,-1,0);
//	glBegin(GL_POLYGON);
//	for ( c=0; c<8; c++) {
//	  glVertex3f( wc[c][0]*radius, -cone_length, wc[c][1]*radius );
//	}  		
//	glEnd();
//}
// draw headlights at night
void Car1::drawAfter(DrawingState* s)
{
  int tod = s->timeOfDay;
  bool daytime;
  if (tod >=6 && tod <= 19)
	daytime = true;
  else 
	daytime = false;
	
  if (!daytime) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);

	// Beam One
	glPushMatrix();			
	glTranslatef(-w*.7f,h+m/2,2);
	glRotated(90,1,0,0);
	drawBeam();
	glPopMatrix();
	// Beam 2
	glPushMatrix();			
	glTranslatef(w*.7f,h+m/2,2);
	glRotated(90,1,0,0);
	drawBeam();
	glPopMatrix();
	glFrontFace(GL_CW);
	glClearColor(1,1,1,1);
	glDisable(GL_BLEND);
  }
}

void Car1::blink(float time)
{
	blink_rotate_angle += 10;
	blink_rotate_angle %= 360;
}
static void drawBeam1(int beam_color)
{
	const float cone_length = 3;
	int c;
	const float radius = 1;
	glBegin(GL_TRIANGLE_FAN);
	if(beam_color == 1)
		glColor4d(1,1,1,.8);
	else
		glColor4d(1,1,1,.8);

	glVertex3d(0,0,0);
	if(beam_color == 1)
		glColor4d(1,0.5,0,.2);
	else
		glColor4d(0.5,0.5,1,.2);
	for ( c=8; c>=0; c--) {
	  glNormal3f( wc[c][0], 0, wc[c][1]);
	  glVertex3f( wc[c][0]*radius, -cone_length, wc[c][1]*radius );
	}  		
	glEnd();
	glNormal3f(0,-1,0);
	glBegin(GL_POLYGON);
	for ( c=0; c<8; c++) {
	  glVertex3f( wc[c][0]*radius, -cone_length, wc[c][1]*radius );
	}  		
	glEnd();
}
void Car1::drawBody(DrawingState*)
{
	glColor3f(1.0,0.5,0.0);
	glPushMatrix();
		glTranslatef(w*.7,t*.45,0);
		glutSolidSphere(0.5,5,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-w*.7,t*.45,0);
		glutSolidSphere(0.5,5,5);
	glPopMatrix();
	// front part
	// front
	glColor3f(1,1,1);
	polygon(-4, -w,h,0., -w,h+m-a,0., w,h+m-a,0., w,h,0.);
	// hood
	polygon(-4, -w,h+m-a,0., -w,h+m,f, w,h+m,f, w,h+m-a,0.);
	// fenders
	polygon(-4, -w,h,0., -w,h,f, -w,h+m,f, -w,h+m-a,0.);
	polygon( 4,  w,h,0.,  w,h,f,  w,h+m,f,  w,h+m-a,0.);

	// main part
	// top
	polygon(-4, -w+sr,t+h,f, -w+sr,t+h,f+r-br, w-sr,t+h,f+r-br, w-sr,t+h,f);
	// left side (x-), right side (x+), bottoms first, then tops
	polygon(-4, -w,h,f,    -w,  h,f+r,  -w,m+h,f+r,   -w,m+h,f);
	polygon( 4,  w, h,f,   w,  h,f+r,   w,m+h,f+r,    w,m+h,f);
	fetchTexture("suv-side.png");
	polygon(-4, -w, h+m,f-s,  -w,h+m,f+r,  -w+sr,t+h,f+r-br,   -w+sr,t+h,f);
	polygon( 4,  w, h+m,f-s,   w,h+m,f+r,   w-sr,t+h,f+r-br,    w-sr,t+h,f);
	// front, back
	fetchTexture("suv-front.png");
	polygon(-4, -w,h+m,f-s,  -w+sr,t+h,f,   w-sr,t+h,  f,  w,h+m,f-s);

	polygon( 4, -w,h+m,f+r,  -w+sr,t+h,f+r-br,  w-sr,t+h,f+r-br, w,h+m,f+r);
	glBindTexture(GL_TEXTURE_2D,0);
	polygon( 4, -w,h,f+r,  -w,h+m,f+r,  w,h+m,f+r, w,h,f+r);
	//=============================================================
	// Now the cars are simply boxes with different hights. 
    // TODO2: To make the cars look more realistic and add texutres. 

	if(blinking == 1){
		glPushMatrix();
			glTranslatef(0, h+t+0.5, f+1);
			glPushMatrix();
				glColor3f(1,1,1);
				glutSolidCube(1);
			glPopMatrix();
			glPushMatrix();
				glColor3f(1,0,0);
				glTranslatef(-1.5, 0, 0);
				glScalef(2, 1, 1);
				glutSolidCube(1);
			glPopMatrix();
			glPushMatrix();
				glColor3f(0,0,1);
				glTranslatef(1.5, 0, 0);
				glScalef(2, 1, 1);
				glutSolidCube(1);
			glPopMatrix();
			// Beam One
			glPushMatrix();
				glTranslatef(-1, 0, 0);
				glRotated(blink_rotate_angle,0,1,0);
				glRotated(90,1,0,0);
				drawBeam1(1);
			glPopMatrix();
			// Beam Two
			glPushMatrix();
				glTranslatef(1, 0, 0);
				glRotated(blink_rotate_angle,0,1,0);
				glRotated(90,1,0,0);
				drawBeam1(0);
			glPopMatrix();
			// Beam Three
			glPushMatrix();
				glTranslatef(-1, 0, 0);
				glRotated(blink_rotate_angle+180,0,1,0);
				glRotated(90,1,0,0);
				drawBeam1(1);
			glPopMatrix();
			// Beam Four
			glPushMatrix();
				glTranslatef(1, 0, 0);
				glRotated(blink_rotate_angle+180,0,1,0);
				glRotated(90,1,0,0);
				drawBeam1(0);
			glPopMatrix();
		glPopMatrix();

		glColor3f(1, 1, 1);
	}

}
//**********************************************************************

//added*****************************************************************
MyCar2::MyCar2(int c) : Car1("MyCar2",c)
{
	 w = 3.5;		// half of width
	 f = 2;		// length of front part
	 r = 10;		// length of back part
	 h = 1;		// height of ground
	 m = 2.5;		// height of motor
	 t = 5;		// height of back part
	 s = .6f;		// slope of windshield
	 a = .2f;		// rake of hood
	 sr = .5f;
	 br = .5f;
	 blinking = 1;
}
//**********************************************************************


/*
void MyCar3::drawBody(DrawingState*){

	polygon(-4, -w,h,0., -w,h+t,0., w,h+t,0., w,h,0.);
	polygon(4, -w,h,r+f, -w,h+t,r+f, w,h+t,r+f, w,h,r+f);
	polygon(-4, w,t+h,0., -w,t+h,0., -w,t+h,f+r, w,t+h,f+r);
	polygon(4, w,h,0., -w,h,0., -w,h,f+r, w,h,f+r);
    polygon(-4, w,t+h,0., w,t+h,f+r, w,h,f+r, w,h,0.);
	polygon(4, -w,t+h,0., -w,t+h,f+r, -w,h,f+r, -w,h,0.);

}
*/

DingCar0::DingCar0(char* name, int c) : GrObject(name,carCtr,cc[c%nCarCols].name)
{
  color((float) cc[c%nCarCols].r,(float) cc[c%nCarCols].g,(float) cc[c%nCarCols].b);
  rideAbove = 10;
  ridable = 1;

  // car params
	 w = 3.5;		// half of width
	 f = 3;		// length of front part
	 r = 6;		// length of back part
	 h = 1;		// height of ground
	 m = 1.5;		// height of motor
	 t = 4;		// height of back part
	 s = .3f;		// slope of windshield
	 a = .2f;		// rake of hood
	 sr = .1f;
	 br = .2f;

	 // note: we can't actually load the textures now (since we don't have a GL context)
	 // so we just say that we don't have textures
	frontTexture = 0;
	sideTexture = 0;
}

void DingCar0::draw(DrawingState* d)
{

  // Draw four wheel 
  glColor3f(.1f,.1f,.1f);
  glPushMatrix();
	  glTranslatef(w-.5f,h,f-h);
	  drawWheel(h,1);
  glPopMatrix();
  glPushMatrix();
	  glTranslatef(w-.5f,h,f+r-h-1);
	  drawWheel(h,1);
  glPopMatrix();
  glPushMatrix();
	  glTranslatef(w-.5f,h,f-r-h-1);
	  drawWheel(h,1);
  glPopMatrix();

  glPushMatrix();
	  glTranslatef(-w+.5f,h,f-h);
	  glRotatef(180,0,1,0);
	  drawWheel(h,1);
  glPopMatrix();
  glPushMatrix();
	  glTranslatef(-w+.5f,h,f+r-h-1);
	  glRotatef(180,0,1,0);
	  drawWheel(h,1);
  glPopMatrix();
  glPushMatrix();
	  glTranslatef(-w+.5f,h,f-r-h-1);
	  glRotatef(180,0,1,0);
	  drawWheel(h,1);
  glPopMatrix();


  // Draw the body of the car
  glColor3fv(&color.r);
  drawBody(d);
}

 

// draw headlights at night
void DingCar0::drawAfter(DrawingState* s)
{
  int tod = s->timeOfDay;
  bool daytime;
  if (tod >=6 && tod <= 19)
	daytime = true;
  else 
	daytime = false;
	
  if (!daytime) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);

	// Beam One
	glPushMatrix();			
	glTranslatef(-w*.7f,h+m/2,2);
	glRotated(90,1,0,0);
	drawBeam();
	glPopMatrix();
	// Beam 2
	glPushMatrix();			
	glTranslatef(w*.7f,h+m/2,2);
	glRotated(90,1,0,0);
	drawBeam();
	glPopMatrix();
	glFrontFace(GL_CW);
	glClearColor(1,1,1,1);
	glDisable(GL_BLEND);
  }
}

void DingCar0::drawBody(DrawingState*)
{
	glColor3f(1.0,0.5,0.0);
	glPushMatrix();
		glTranslatef(w*.7,h+t*.7,0);
		glutSolidSphere(0.5,5,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-w*.7,h+t*.7,0);
		glutSolidSphere(0.5,5,5);
	glPopMatrix();


	//base
	glColor3f(0.5,0.5,0.5);
	polygon(-4,  w,h,0., -w,h,0., -w,h+t,0., w,h+t,0.);
	polygon(4,  w,h,r+f , -w,h,r+f, -w,h+t,r+f, w,h+t,r+f);
	polygon(-4, -w,t+h,f+r, w,t+h,f+r, w,t+h,0., -w,t+h,0.);
	polygon(4, w,h,0., -w,h,0., -w,h,f+r, w,h,f+r);
    polygon(-4,  w,h,f+r, w,h,0., w,t+h,0., w,t+h,f+r);
	polygon(4, -w,h,f+r, -w,h,0., -w,t+h,0., -w,t+h,f+r);

	glTranslatef(0,1.0,0);
	glColor3f(1.0,0.0,0.0);
	 //driving head	
	fetchTexture("DingCar0_dh_front.bmp");
	polygon(-4,  dhw,dhh,0., -dhw,dhh,0., -dhw,dhh+dht,0., dhw,dhh+dht,0.);
		fetchTexture("DingCar0_dh_updownback.bmp");
	polygon(4,  dhw,dhh,dhr+dhf , -dhw,dhh,dhr+dhf, -dhw,dhh+dht,dhr+dhf, dhw,dhh+dht,dhr+dhf);
		fetchTexture("DingCar0_dh_updownback.bmp");
	polygon(-4, -dhw,dht+dhh,dhf+dhr, dhw,dht+dhh,dhf+dhr, dhw,dht+dhh,0., -dhw,dht+dhh,0.);
		fetchTexture("DingCar0_dh_updownback.bmp");
	polygon(4, dhw,dhh,0., -dhw,dhh,0., -dhw,dhh,dhf+dhr, dhw,dhh,dhf+dhr);
		fetchTexture("DingCar0_dh_side.bmp");
    polygon(-4,  dhw,dhh,dhf+dhr, dhw,dhh,0., dhw,dht+dhh,0., dhw,dht+dhh,dhf+dhr);
		fetchTexture("DingCar0_dh_side.bmp");
	polygon(4, -dhw,dhh,dhf+dhr, -dhw,dhh,0., -dhw,dht+dhh,0., -dhw,dht+dhh,dhf+dhr);

	glTranslatef(0,0,f-1);


	//box
	glColor3f(0.5,0.5,0.5);
		fetchTexture("DingCar0_box_updown.bmp");
	polygon(-4,  boxw,boxh,0., -boxw,boxh,0., -boxw,boxh+boxt,0., boxw,boxh+boxt,0.);
		fetchTexture("DingCar0_box_back.bmp");
	polygon(4,  boxw,boxh,boxr+boxf , -boxw,boxh,boxr+boxf, -boxw,boxh+boxt,boxr+boxf, boxw,boxh+boxt,boxr+boxf);
		fetchTexture("DingCar0_box_updown.bmp");
	polygon(-4, -boxw,boxt+boxh,boxf+boxr, boxw,boxt+boxh,boxf+boxr, boxw,boxt+boxh,0., -boxw,boxt+boxh,0.);
		fetchTexture("DingCar0_box_updown.bmp");
	polygon(4, boxw,boxh,0., -boxw,boxh,0., -boxw,boxh,boxf+boxr, boxw,boxh,boxf+boxr);
		fetchTexture("DingCar0_box_side.bmp");
    polygon(-4,  boxw,boxh,boxf+boxr, boxw,boxh,0., boxw,boxt+boxh,0., boxw,boxt+boxh,boxf+boxr);
		fetchTexture("DingCar0_box_side.bmp");
	polygon(4, -boxw,boxh,boxf+boxr, -boxw,boxh,0., -boxw,boxt+boxh,0., -boxw,boxt+boxh,boxf+boxr);
	//=============================================================
	// Now the cars are simply boxes with different hights. 
    // TODO2: To make the cars look more realistic and add texutres. 

}

MyDingCar0::MyDingCar0(int c) : DingCar0("DingCar0-0",c)
{
	 w = 3.5;		// half of width
	 f = 7;		// length of front part
	 r = 4;		// length of back part
	 h = 1;		// height of ground
	 m = 1.5;		// height of motor
	 t = 1;		// height of back part
	 s = .3f;		// slope of windshield
	 a = .2f;		// rake of hood
	 sr = .5f;
	 br = .5f;

	 	//box
	 boxw = 3.5;		// half of width
	 boxf = 3;		// length of front part
	 boxr = 2;		// length of back part
	 boxh = 1;		// height of ground
	 boxm = 1.5;		// height of motor
	 boxt = 4;		// height of back part
	 boxs = .3f;		// slope of windshield
	 boxa = .2f;		// rake of hood

		//driving head
	 dhw = 3.5;		// half of width
	 dhf = 2;		// length of front part
	 dhr = 3;		// length of back part
	 dhh = 1;		// height of ground
	 dhm = 1.5;		// height of motor
	 dht = 3;		// height of back part
	 dhs = .3f;		// slope of windshield
	 dha = .2f;		// rake of hood

}

DingCar1::DingCar1(char* name, int c) : GrObject(name,carCtr,cc[c%nCarCols].name)
{
  color((float) cc[c%nCarCols].r,(float) cc[c%nCarCols].g,(float) cc[c%nCarCols].b);
  rideAbove = 10;
  ridable = 1;

  // car params
	 w = 3.5;		// half of width
	 f = 3;		// length of front part
	 r = 6;		// length of back part
	 h = 1;		// height of ground
	 m = 1.5;		// height of motor
	 t = 4;		// height of back part
	 s = .3f;		// slope of windshield
	 a = .2f;		// rake of hood
	 sr = .1f;
	 br = .2f;

	 // note: we can't actually load the textures now (since we don't have a GL context)
	 // so we just say that we don't have textures
	frontTexture = 0;
	sideTexture = 0;
}

void DingCar1::draw(DrawingState* d)
{

  // Draw four wheel 
  glColor3f(.1f,.1f,.1f);
  glPushMatrix();
	  glTranslatef(w-.5f,h,f-h);
	  drawWheel(h,1);
  glPopMatrix();
  glPushMatrix();
	  glTranslatef(w-.5f,h,f+r-h-1);
	  drawWheel(h,1);
  glPopMatrix();


  glPushMatrix();
	  glTranslatef(-w+.5f,h,f-h);
	  glRotatef(180,0,1,0);
	  drawWheel(h,1);
  glPopMatrix();
  glPushMatrix();
	  glTranslatef(-w+.5f,h,f+r-h-1);
	  glRotatef(180,0,1,0);
	  drawWheel(h,1);
  glPopMatrix();



  // Draw the body of the car
  glColor3fv(&color.r);
  drawBody(d);
}

 

// draw headlights at night
void DingCar1::drawAfter(DrawingState* s)
{
  int tod = s->timeOfDay;
  bool daytime;
  if (tod >=6 && tod <= 19)
	daytime = true;
  else 
	daytime = false;
	
  if (!daytime) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);

	// Beam One
	glPushMatrix();			
	glTranslatef(-w*.7f,h+m/2,2);
	glRotated(90,1,0,0);
	drawBeam();
	glPopMatrix();
	// Beam 2
	glPushMatrix();			
	glTranslatef(w*.7f,h+m/2,2);
	glRotated(90,1,0,0);
	drawBeam();
	glPopMatrix();
	glFrontFace(GL_CW);
	glClearColor(1,1,1,1);
	glDisable(GL_BLEND);
  }
}

void DingCar1::drawBody(DrawingState*)
{
	glColor3f(1.0,0.5,0.0);
	glPushMatrix();
		glTranslatef(w*.7,h+t*.7,0);
		glutSolidSphere(0.5,5,5);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-w*.7,h+t*.7,0);
		glutSolidSphere(0.5,5,5);
	glPopMatrix();
	//base
	glColor3f(1,0,0);

	polygon(-4,  w,h,0., -w,h,0., -w,h+t,0., w,h+t,0.);
	polygon(4,  w,h,r+f , -w,h,r+f, -w,h+t,r+f, w,h+t,r+f);
	polygon(-4, -w,t+h,f+r, w,t+h,f+r, w,t+h,0., -w,t+h,0.);
	polygon(4, w,h,0., -w,h,0., -w,h,f+r, w,h,f+r);
    polygon(-4,  w,h,f+r, w,h,0., w,t+h,0., w,t+h,f+r);
	polygon(4, -w,h,f+r, -w,h,0., -w,t+h,0., -w,t+h,f+r);

	glTranslatef(0,1.0,0);
	glColor3f(1.0,0.0,0.0);

	 //driving head	

	//fonrt
	glColor3fv(&color.r);
	polygon(-4,  dhw,dhh,0., -dhw,dhh,0., -dhw,dhh+dht,0.5 , dhw,dhh+dht,0.5);
	//front screen
	glColor3f(0.2,0.2,0.9);
	polygon(-4,  dhw-0.1,dhh+0.4,-0.1, -dhw+0.1,dhh+0.4, -0.1, -dhw+0.1,dhh+dht-0.2, 0.5-0.1 , dhw-0.1,dhh+dht-0.2, 0.5-0.1);
	//up
	glColor3f(0.1,0.1,0.1);
	polygon(-4, -dhw,dht+dhh,dhf+dhr-0.5, dhw,dht+dhh,dhf+dhr-0.5, dhw,dht+dhh,0.5, -dhw,dht+dhh,0.5);
	//back
	glColor3fv(&color.r);
	polygon(4,  dhw,dhh,dhr+dhf , -dhw,dhh,dhr+dhf, -dhw,dhh+dht,dhr+dhf-0.5, dhw,dhh+dht,dhr+dhf-0.5);
	//back screen
	glColor3f(0.2,0.2,0.9);
	polygon(4,  dhw-0.2,dhh+0.3,dhr+dhf+0.1 , -dhw+0.2,dhh+0.3,dhr+dhf+0.1, -dhw+0.2,dhh+dht-0.1,dhr+dhf-0.5+0.1, dhw-0.2,dhh+dht-0.1,dhr+dhf-0.5+0.1);


	glColor3fv(&color.r);
	//down
	polygon(4, dhw,dhh,0., -dhw,dhh,0., -dhw,dhh,dhf+dhr, dhw,dhh,dhf+dhr);
    
	//right
	glColor3fv(&color.r);
	polygon(-4,  dhw,dhh,dhf+dhr, dhw,dhh,0., dhw,dht+dhh,0.5, dhw,dht+dhh,dhf+dhr-0.5);
	//right Screen
	glColor3f(0.2,0.2,0.9);
	polygon(-4,  dhw+0.1,dhh+0.2,dhf+dhr-0.2, dhw+0.1,dhh+0.2,0.2, dhw+0.1,dht+dhh-0.2,0.5+0.2, dhw+0.1,dht+dhh-0.2,dhf+dhr-0.5-0.2);
	//left
	glColor3fv(&color.r);
	polygon(4, -dhw,dhh,dhf+dhr, -dhw,dhh,0., -dhw,dht+dhh,0.5, -dhw,dht+dhh,dhf+dhr-0.5);
	// left screeen
	glColor3f(0.2,0.2,0.9);
	polygon(4, -dhw-0.1,dhh+0.2,dhf+dhr-0.2, -dhw-0.1,dhh+0.2,0.2, -dhw-0.1,dht+dhh-0.2,0.5+0.2, -dhw-0.1,dht+dhh-0.2,dhf+dhr-0.5-0.2);



	//=============================================================
	// Now the cars are simply boxes with different hights. 
    // TODO2: To make the cars look more realistic and add texutres. 

}

MyDingCar1::MyDingCar1(int c) : DingCar1("DingCar1-0",c)
{
	 w = 3.5;		// half of width
	 f = 3;		// length of front part
	 r = 4;		// length of back part
	 h = 1;		// height of ground
	 m = 1.5;		// height of motor
	 t = 1;		// height of back part
	 s = .3f;		// slope of windshield
	 a = .2f;		// rake of hood
	 sr = .5f;
	 br = .5f;



		//driving head
	 dhw = 3.5;		// half of width
	 dhf = 3;		// length of front part
	 dhr = 4;		// length of back part
	 dhh = 1;		// height of ground
	 dhm = 1.5;		// height of motor
	 dht = 3;		// height of back part
	 dhs = .3f;		// slope of windshield
	 dha = .2f;		// rake of hood

}

/*

reference

	fetchTexture("DingCar0_front.bmp");
	polygon(-4,  dhw,dhh,0., -dhw,dhh,0., -dhw,dhh+dht,0., dhw,dhh+dht,0.);
		fetchTexture("DingCar0_back.bmp");
	polygon(4,  dhw,dhh,dhr+dhf , -dhw,dhh,dhr+dhf, -dhw,dhh+dht,dhr+dhf, dhw,dhh+dht,dhr+dhf);
		fetchTexture("DingCar0_up.bmp");
	polygon(-4, -dhw,dht+dhh,dhf+dhr, dhw,dht+dhh,dhf+dhr, dhw,dht+dhh,0., -dhw,dht+dhh,0.);
		fetchTexture("DingCar0_down.bmp");
	polygon(4, dhw,dhh,0., -dhw,dhh,0., -dhw,dhh,dhf+dhr, dhw,dhh,dhf+dhr);
		fetchTexture("DingCar0_right.bmp");
    polygon(-4,  dhw,dhh,dhf+dhr, dhw,dhh,0., dhw,dht+dhh,0., dhw,dht+dhh,dhf+dhr);
		fetchTexture("DingCar0_left.bmp");
	polygon(4, -dhw,dhh,dhf+dhr, -dhw,dhh,0., -dhw,dht+dhh,0., -dhw,dht+dhh,dhf+dhr);

*/