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

// the simple example objects - not that exciting - yours should be
// better! 

// note - because this is a precompiled header, getting the name the same
// is more important than getting the path right`
#include "../GrTown_PCH.H"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../MMatrix.H"
#include <GL/glut.h>


#include "Suburbs.H"

/***********************************************************************/
// a Really simple tree - just a cone with a stem...
// use normals to make it look rounder...
SimpleTree1::SimpleTree1(float h, float r)
	: height(h), radius(r)
{
}
void SimpleTree1::draw(DrawingState*)
{
	// cone for the body
	glFrontFace(GL_CW);
	glColor3f(0.f,.6f,.3f);
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0,1,0);
	glVertex3f(0,height,0);
	glNormal3f(1,0,0);
	glVertex3f(radius,height/4,0);
	glNormal3f(0,0,1);
	glVertex3f(0,height/4,radius);
	glNormal3f(-1,0,0);
	glVertex3f(-radius,height/4,0);
	glNormal3f(0,0,-1);
	glVertex3f(0,height/4,-radius);
	glNormal3f(1,0,0);
	glVertex3f(radius,height/4,0);
	glEnd();
	glFrontFace(GL_CCW);
	// stem
	glColor3f(.6f,.5f,.3f);
	glBegin(GL_QUAD_STRIP);
	glNormal3f(1,0,0);
	glVertex3f(radius/5,0,0);
	glVertex3f(radius/5,height/4,0);
	glNormal3f(0,0,1);
	glVertex3f(0,0,radius/5);
	glVertex3f(0,height/4,radius/5);
	glNormal3f(-1,0,0);
	glVertex3f(-radius/5,0,0);
	glVertex3f(-radius/5,height/4,0);
	glNormal3f(0,0,-1);
	glVertex3f(0,0,-radius/5);
	glVertex3f(0,height/4,-radius/5);
	glNormal3f(1,0,0);
	glVertex3f(radius/5,0,0);
	glVertex3f(radius/5,height/4,0);
	glEnd();
}

DingHouse6::DingHouse6()
{
	color(.6f,.7f,.8f);
	rotMatrix(transform,'Y',3.14159f/2.f);
}
void DingHouse6::draw(DrawingState*)
{
	float height = 240;
	float radius = 10;
	glPushMatrix();
	GLUquadricObj* dummy;
	dummy = gluNewQuadric();
	glColor3f(1.0,0.6,0.4);

	glTranslatef(20,0,0);
	// Chinmy
	glScalef(1,20,1);
	glutSolidCube(5);
	glPopMatrix();

	glColor3fv(&color.r);
//	fetchTexture("house4side001.png");
	polygoni(4, 20, 0, 30, -20, 0, 30,  -20,30, 30, 20,30,30);
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(0,0,0.1);
	polygoni(4, 20,20,30,    -20, 20, 30,  -20,25, 30,     20,25,30);
	glPopMatrix();

//	fetchTexture("house4side001.png");
	glColor3f(1,1,1);
	polygoni(4, -20, 0, -30, 20, 0, -30, 20,30,-30,  -20,30, -30);	
	glColor3f(0,0,0);
	glPushMatrix();
	glTranslatef(0,0,-0.1);
		polygoni(4, -20, 20,-30,   20, 20,-30,    20,25,-30,  -20,25, -30);
	glPopMatrix();

	glColor3fv(&color.r);
//	fetchTexture("house4side002.png");
	polygoni(3,  20,30,30,  -20,30,30,  0,45,30);
//	fetchTexture("house4side002.png");
	polygoni(3, -20,30,-30,  20,30,-30,   0,45,-30);

//	fetchTexture("house4front001.png");
	glBegin(GL_POLYGON);
	glNormal3f(1,0,0);
	glTexCoord2f(0,1); glVertex3i( 20,30,-30);
	glTexCoord2f(1,1); glVertex3i( 20,30, 30);
	glTexCoord2f(1,0); glVertex3i( 20, 0, 30);
	glTexCoord2f(0,0); glVertex3i( 20, 0,-30);
	glEnd();

	glPushMatrix();
	glTranslatef(0.2,0,0);	
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	glNormal3f(-1,0,0);
	glTexCoord2f(0,0); glVertex3i(20,20,-30);
	glTexCoord2f(0,1); glVertex3i(20,25,-30);
	glTexCoord2f(1,1); glVertex3i(20,25, 30);
	glTexCoord2f(1,0); glVertex3i(20,20, 30);
	glEnd();
	glPopMatrix();

//	fetchTexture("house4back001.png");
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	glNormal3f(-1,0,0);
	glTexCoord2f(0,0); glVertex3i(-20, 0,-30);
	glTexCoord2f(1,0); glVertex3i(-20, 0, 30);
	glTexCoord2f(1,1); glVertex3i(-20,30, 30);
	glTexCoord2f(0,1); glVertex3i(-20,30,-30);
	glEnd();

	glPushMatrix();
	glTranslatef(-0.1,0,0);	
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	glNormal3f(-1,0,0);
	glTexCoord2f(0,0); glVertex3i(-20,20,-30);
	glTexCoord2f(1,0); glVertex3i(-20,20, 30);
	glTexCoord2f(1,1); glVertex3i(-20,25, 30);
	glTexCoord2f(0,1); glVertex3i(-20,25,-30);
	glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D,0);
	glBindTexture(GL_TEXTURE_2D,0);
	glColor3f(1,1,1);
	fetchTexture("house4roof001.png");
	polygoni( 4, 20,30,-30,  20,30, 30,   0, 45, 30,   0, 45, -30);
	polygoni(-4,-20,30,-30, -20,30, 30,   0, 45, 30,   0, 45, -30);
	glBindTexture(GL_TEXTURE_2D,0);

	glTranslatef(20,0,0);
	glRotatef(90,0,1,0);

	glColor3fv(&color.r);
//	fetchTexture("house4side001.png");
	polygoni(4, 10, 0, 20, -10, 0, 20,  -10,20, 20, 10,20,20);
//	fetchTexture("house4side001.png");
	polygoni(4, -10, 0, -20, 10, 0, -20, 10,20,-20,  -10,20, -20);
//	fetchTexture("house4side002.png");
	polygoni(3,  10,20,20,  -10,20,20,  0,45,20);
//	fetchTexture("house4side002.png");
	polygoni(3, -10,20,-20,  10,20,-20,   0,45,-20);

	glPushMatrix();
	glTranslatef(0,0,25.2);
	glColor3f(.5,.5,.5);
	polygoni(4, 5,0,-5, -5,0,-5, -5,10,-5, 5,10,-5);
	glPopMatrix();
	glColor3f(1.0,1.0,1.0);
//	fetchTexture("house4front001.png");
	glBegin(GL_POLYGON);
	glNormal3f(1,0,0);
	glTexCoord2f(0,1); glVertex3i( 10,20,-20);
	glTexCoord2f(1,1); glVertex3i( 10,20, 20);
	glTexCoord2f(1,0); glVertex3i( 10, 0, 20);
	glTexCoord2f(0,0); glVertex3i( 10, 0,-20);
	glEnd();
	//fetchTexture("house4back001.png");
	glBegin(GL_POLYGON);
	glNormal3f(-1,0,0);
	glTexCoord2f(0,0); glVertex3i(-10, 0,-20);
	glTexCoord2f(1,0); glVertex3i(-10, 0, 20);
	glTexCoord2f(1,1); glVertex3i(-10,20, 20);
	glTexCoord2f(0,1); glVertex3i(-10,20,-20);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,0);
	fetchTexture("house4roof001.png");
	polygoni( 4, 10,20,-20,  10,20, 20,   0, 45, 20,   0, 45, -20);
	polygoni(-4,-10,20,-20, -10,20, 20,   0, 45, 20,   0, 45, -20);
}
//**********************************************************************



/***added by Ding ******************************************************/
SimpleHouse7::SimpleHouse7()
{
	color(.6f,.7f,.8f);
}
void SimpleHouse7::draw(DrawingState*)
{
	GLfloat radius = 10;
	GLfloat height = 80;

	glColor3fv(&color.r);
	//main body
	glColor3f(1, 1, 1);

	fetchTexture("DingHouse0_door.bmp");
	polygoni(4, -15, 0,-15,  15, 0,-15,  15,20,-15,  -15,20,-15);
	fetchTexture("DingHouse0_window.bmp");
	polygoni(4,  15, 0,-15,  15, 0, 15,  15,20, 15,   15,20,-15);
	//back
	polygoni(4,  15, 0, 15, -15, 0, 15, -15,20, 15,   15,20, 15);	
	polygoni(4, -15, 0, 15, -15, 0,-15, -15,20,-15,  -15,20, 15);
	//fetchTexture("roof3.png");

	//head

	polygoni(4, -25, 20,-25,  25, 20,-25,  25,30,-25,  -25,30,-25);
	polygoni(4,  25, 20,-25,  25, 20, 25,  25,30, 25,   25,30,-25);
	polygoni(4,  25, 20, 25, -25, 20, 25, -25,30, 25,   25,30, 25);
	polygoni(4, -25, 20, 25, -25, 20,-25, -25,30,-25,  -25,30, 25);
	//head button
	fetchTexture("DingHouse0_wall.bmp");
	polygoni(4, -25, 20, -25, -25, 20, 25,  25,20, 25,  25,20, -25);

	fetchTexture("roof3.png");
	polygoni(3, -25,30,-25,  25,30,-25,   0,45,0);
	polygoni(3,  25,30,-25,  25,30, 25,   0,45,0);
	polygoni(3,  25,30, 25, -25,30, 25,   0,45,0);
	polygoni(3, -25,30, 25, -25,30,-25,   0,45,0);

	// Pillar
	glPushMatrix();
	glTranslatef(20,0,20);
	glColor3f(1.0,1.0,1.0);	
	glBegin(GL_QUAD_STRIP);
	glNormal3f(1,0,0);
	glVertex3f(20/5,0,0);
	glVertex3f(radius/5,height/4,0);
	glNormal3f(0,0,1);
	glVertex3f(0,0,radius/5);
	glVertex3f(0,height/4,radius/5);
	glNormal3f(-1,0,0);
	glVertex3f(-radius/5,0,0);
	glVertex3f(-radius/5,height/4,0);
	glNormal3f(0,0,-1);
	glVertex3f(0,0,-radius/5);
	glVertex3f(0,height/4,-radius/5);
	glNormal3f(1,0,0);
	glVertex3f(radius/5,0,0);
	glVertex3f(radius/5,height/4,0);
	glEnd();

	glPopMatrix();

	// Pillar
	glPushMatrix();

	glTranslatef(-20,0,20);
	glBegin(GL_QUAD_STRIP);
	glNormal3f(1,0,0);
	glVertex3f(20/5,0,0);
	glVertex3f(radius/5,height/4,0);
	glNormal3f(0,0,1);
	glVertex3f(0,0,radius/5);
	glVertex3f(0,height/4,radius/5);
	glNormal3f(-1,0,0);
	glVertex3f(-radius/5,0,0);
	glVertex3f(-radius/5,height/4,0);
	glNormal3f(0,0,-1);
	glVertex3f(0,0,-radius/5);
	glVertex3f(0,height/4,-radius/5);
	glNormal3f(1,0,0);
	glVertex3f(radius/5,0,0);
	glVertex3f(radius/5,height/4,0);
	glEnd();

	glPopMatrix();

	// Pillar
	glPushMatrix();

	glTranslatef(20,0,-20);
	glBegin(GL_QUAD_STRIP);
	glNormal3f(1,0,0);
	glVertex3f(20/5,0,0);
	glVertex3f(radius/5,height/4,0);
	glNormal3f(0,0,1);
	glVertex3f(0,0,radius/5);
	glVertex3f(0,height/4,radius/5);
	glNormal3f(-1,0,0);
	glVertex3f(-radius/5,0,0);
	glVertex3f(-radius/5,height/4,0);
	glNormal3f(0,0,-1);
	glVertex3f(0,0,-radius/5);
	glVertex3f(0,height/4,-radius/5);
	glNormal3f(1,0,0);
	glVertex3f(radius/5,0,0);
	glVertex3f(radius/5,height/4,0);
	glEnd();

	glPopMatrix();

	//Pillar
	glPushMatrix();
	glTranslatef(-20,0,-20);
	glBegin(GL_QUAD_STRIP);
	glNormal3f(1,0,0);
	glVertex3f(20/5,0,0);
	glVertex3f(radius/5,height/4,0);
	glNormal3f(0,0,1);
	glVertex3f(0,0,radius/5);
	glVertex3f(0,height/4,radius/5);
	glNormal3f(-1,0,0);
	glVertex3f(-radius/5,0,0);
	glVertex3f(-radius/5,height/4,0);
	glNormal3f(0,0,-1);
	glVertex3f(0,0,-radius/5);
	glVertex3f(0,height/4,-radius/5);
	glNormal3f(1,0,0);
	glVertex3f(radius/5,0,0);
	glVertex3f(radius/5,height/4,0);
	glEnd();

	glPopMatrix();

}
/***********************************************************************/

//added*****************************************************************
FogBox::FogBox()
{
	fogOn = 0;
	fogStart = 0.0; // Fog start z value.
	fogEnd = 300;
}
void FogBox::draw(DrawingState* d)
{
	if(fogOn){
		float fogColor[4] = {0.5, 0.5, 0.5, 1.0};
		int fogMode = GL_LINEAR;
		glEnable(GL_FOG);
		glHint(GL_FOG_HINT, GL_NICEST);
		glFogfv(GL_FOG_COLOR, fogColor);
		glFogi(GL_FOG_MODE, fogMode);
		glFogf(GL_FOG_START, fogStart);
		glFogf(GL_FOG_END, fogEnd);
	} else
		glDisable(GL_FOG);
}
void FogBox::drawAfter(DrawingState* d)
{
	if (d->timeOfDay == 6) {
		fogOn = 1;
		fogEnd = 300;
	}else if(d->timeOfDay== 7){
		fogOn = 1;
		fogEnd = 100;
	}else if(d->timeOfDay== 8){
		fogOn = 1;
		fogEnd = 300;
	}else
		fogOn = 0;
}
SnowBox::SnowBox(float x, float y, float z, int ms):width(x), height(y), length(z), maxSnow(ms)
{
	noOfSnow = 0;
}
void SnowBox::draw(DrawingState* d)
{
	int tod = d->timeOfDay;
	if (tod > 20 && tod <= 24) {
		for(int i = 0;i < noOfSnow;i++){
			glColor3f(1, 1, 1);
			glPushMatrix();
			glTranslatef(snowx[i], snowy[i], snowz[i]);
			GLUquadricObj *snow;
			snow = gluNewQuadric();
			gluSphere(snow, 1, 5, 5);
			glPopMatrix();
			if(snowy[i] < 300 && snowy[i] > -3){
				glPushMatrix();
				glColor3f((snowy[i])/1000, (snowy[i])/1000, (snowy[i])/1000);
				glTranslatef(snowx[i], 1, snowz[i]);
				glRotatef(270, 1, 0, 0);
				if(snowy[i] > 1){
					gluDisk(snow, 0, 1, 5, 5);
				}else if(snowy[i] > 0){
					gluDisk(snow, 0, snowy[i], 5, 5);
				}
				glPopMatrix();
			}
		}
	}else
		noOfSnow = 0;
}
void SnowBox::drawAfter(DrawingState* d)
{
	if (d->timeOfDay > 20 && d->timeOfDay<= 24) {
		if(noOfSnow < maxSnow){
			noOfSnow++;
		}
		snowx[noOfSnow] = (rand()%width);
		snowy[noOfSnow] = 300+(rand()%height);
		snowz[noOfSnow] = (rand()%length);
		snowxsp[noOfSnow] = 1 * (0.1+(float)(rand()%1000)/(float)50000);
		snowysp[noOfSnow] = 1 * (0.5+(float)(rand()%1000)/(float)50000);
		snowzsp[noOfSnow] = 1 * (0.1+(float)(rand()%1000)/(float)50000);
		for(int i = 0;i < noOfSnow;i++){
			if(snowy[i] > -1)
				snowy[i] -= (snowysp[i]);
			else
				snowy[i] = 300 + (rand()%height);
			if(snowy[i] > 0){
				if(snowx[i] > 0 && snowx[i] < width)
					snowx[i] += (snowxsp[i]);
				else
					snowy[i] = (rand()%width);
				if(snowz[i] > 0 && snowz[i] < length)
					snowz[i] -= (snowzsp[i]);
				else
					snowz[i] = (rand()%length);
				if(rand()%100 == 1){
					snowxsp[i] *= -1;
				}
				if(rand()%100 == 1){
					snowzsp[i] *= -1;
				}
			}
		}
	}
}
void SkyBox::draw(DrawingState * d)
{
	int tod = d->timeOfDay;
	glPushMatrix();
	glScalef(10000, 10000, 10000);

	glDisable(GL_LIGHTING);
	fetchTexture("skybox_texture004.png", true, true);
	if (tod < 6) {
		glColor3f(1, 1, 1);
		fetchTexture("skybox_texture004.png", true, true);
	} else if (tod < 10) {
		float amt = (((float)tod) - 6) / 3.0f;
		glColor3f(amt, amt, amt);
		fetchTexture("skybox_texture002.png", true, true);
	} else if (tod < 12) {
		glColor3f(1, 1, 1);
		fetchTexture("skybox_texture002.png", true, true);
	} else if (tod < 20) {
		float amt = (20 - (float)tod) / 8.0f;
		glColor3f(amt, amt, amt);
		fetchTexture("skybox_texture002.png", true, true);
	} else {
		glColor3f(1, 1, 1);
		fetchTexture("skybox_texture004.png", true, true);
	}

	glBegin(GL_QUADS);
	//front
	glNormal3f(0, 0, 1);
	glTexCoord2f(.25,.75);
	glVertex3f(-1, -1, -1);
	glTexCoord2f(.25,  .5);
	glVertex3f( 1, -1, -1);
	glTexCoord2f(.5,  .5);
	glVertex3f( 1,  1, -1);
	glTexCoord2f(.5, .75);
	glVertex3f(-1,1,-1);
	//right
	glNormal3f(-1, 0, 0);
	//glColor3f(0, 0, 1);
	glTexCoord2f(.25,  .5);
	glVertex3f(1, -1, -1);
	glTexCoord2f(.25, .25);
	glVertex3f(1, -1, 1);
	glTexCoord2f( .5, .25);
	glVertex3f(1, 1, 1);
	glTexCoord2f( .5,  .5);
	glVertex3f(1, 1, -1);
	//back
	glNormal3f(0, 0, -1);
	//glColor3f(0, 1, 0);
	glTexCoord2f(.25,   0);
	glVertex3f(-1, -1, 1);
	glTexCoord2f( .5,   0);
	glVertex3f(-1,  1, 1);
	glTexCoord2f( .5, .25);
	glVertex3f( 1,  1, 1);
	glTexCoord2f(.25, .25);
	glVertex3f( 1, -1, 1);
	//left
	glNormal3f(1, 0, 0);
	//glColor3f(0, 1, 1);
	glTexCoord2f(.25, .75);
	glVertex3f(-1, -1,  -1);
	glTexCoord2f( .5, .75);
	glVertex3f(-1, 1,  -1);
	glTexCoord2f( .5, 1);
	glVertex3f(-1,  1,  1);
	glTexCoord2f(.25, 1);
	glVertex3f(-1, -1,  1);
	//top
	glNormal3f(0, -1, 0);
	//glColor3f(1, 0, 0);
	glTexCoord2f( .5, .75);
	glVertex3f(-1.01, 0.99, -1.01);
	glTexCoord2f( .5,  .5);
	glVertex3f(1.01, 0.99, -1.01);
	glTexCoord2f(.75,  .5);
	glVertex3f(1.01, 0.99, 1.01);
	glTexCoord2f(.75, .75);
	glVertex3f(-1.01, 0.99, 1.01);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}
//**********************************************************************

/***********************************************************************/
// draw a patch of lawn - use a repeating texture
Lawn::Lawn(float xi1, float zi1, float xi2, float zi2)
	: x1(xi1), z1(zi1), x2(xi2), z2(zi2)
{
}

void Lawn::draw(DrawingState* d)
{
	// the catch here is that we need to use a polygon offset to draw
	// the lawn just above the ground...
	if (d->drGrTex)
		fetchTexture("soil001.png",true,true);
	else
		glBindTexture(GL_TEXTURE_2D,0);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(-2.,-2.);
	glNormal3f(0,1,0);
	glColor3f(1,1,1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0,(z2-z1)/4.f);            glVertex3f(x1,0,z2);
	glTexCoord2f((x2-x1)/4.f, (z2-z1)/4.f); glVertex3f(x2,0,z2);
	glTexCoord2f((x2-x1)/4.f,0);            glVertex3f(x2,0,z1);
	glTexCoord2f(0,0);                      glVertex3f(x1,0,z1);
	glEnd();
	glDisable(GL_POLYGON_OFFSET_FILL);
	glBindTexture(GL_TEXTURE_2D,0);
}


/***********************************************************************/
/* simplest possible house */
SimpleHouse1::SimpleHouse1()
{
	color(.6f,.7f,.8f);
}
void SimpleHouse1::draw(DrawingState*)
{
	glColor3fv(&color.r);
	fetchTexture("simpleHouse1-front.png");
	glBegin(GL_POLYGON);
	glNormal3f(0,0,-1);
	glTexCoord2f(0,0); glVertex3i(-20, 0, -25);
	glTexCoord2f(0,1); glVertex3i(-20,30, -25);
	glTexCoord2f(.5,1.5); glVertex3i(  0,45,-25);
	glTexCoord2f(1,1); glVertex3i( 20,30,-25);
	glTexCoord2f(1,0); glVertex3i( 20, 0,-25);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3i(-20, 0,   25);
	glTexCoord2f(1,0); glVertex3i( 20, 0,   25);
	glTexCoord2f(1,1); glVertex3i( 20,30,   25);
	glTexCoord2f(.5,1.5); glVertex3i(  0,45,25);
	glTexCoord2f(0,1); glVertex3i(-20,30,   25);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
	//  polygoni( 5, -20,0,-25,  20,0,-25,   20, 30,-25,   0,45,-25, -20,30,-25);
	//polygoni( 5, -20,0, 25,  20,0, 25,   20, 30, 25,   0,45, 25, -20,30, 25);
	polygoni( 4, 20, 0,-25,  20, 0, 25,  20, 30, 25,  20, 30, -25);
	polygoni(-4,-20, 0,-25, -20, 0, 25, -20, 30, 25, -20, 30, -25);
	polygoni( 4, 20,30,-25,  20,30, 25,   0, 45, 25,   0, 45, -25);
	polygoni(-4, -20,30,-25, -20,30, 25,   0, 45, 25,   0, 45, -25);
}
/***********************************************************************/
/* simplest possible house */
SimpleHouse2::SimpleHouse2()
{
	color(.6f,.7f,.8f);
	rotMatrix(transform,'Y',3.14159f/2.f);
}
void SimpleHouse2::draw(DrawingState*)
{
	glColor3fv(&color.r);
	polygoni( 5, -20,0,-30, 20,0,-30, 20,30,-30, 0,45,-30, -20,30,-30);
	polygoni(-5, -20,0, 30, 20,0, 30, 20,30, 30, 0,45, 30, -20,30, 30);
	fetchTexture("house4front001.png");
	glBegin(GL_POLYGON);
	glNormal3f(1,0,0);
	glTexCoord2f(0,1); glVertex3i( 20,30,-30);
	glTexCoord2f(1,1); glVertex3i( 20,30, 30);
	glTexCoord2f(1,0); glVertex3i( 20, 0, 30);
	glTexCoord2f(0,0); glVertex3i( 20, 0,-30);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(-1,0,0);
	glTexCoord2f(0,0); glVertex3i(-20, 0,-30);
	glTexCoord2f(1,0); glVertex3i(-20, 0, 30);
	glTexCoord2f(1,1); glVertex3i(-20,30, 30);
	glTexCoord2f(0,1); glVertex3i(-20,30,-30);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
	glBindTexture(GL_TEXTURE_2D,0);
	fetchTexture("house4roof001.png");
	polygoni( 4, 20,30,-30,  20,30, 30,   0, 45, 30,   0, 45, -30);
	polygoni(-4,-20,30,-30, -20,30, 30,   0, 45, 30,   0, 45, -30);
}

//added*****************************************************************
//from internet, DONE modification
void door(float width, float height, float thick)
{
	float frame = 2;
	float fw_ratio = frame / width;
	float fh_ratio = frame / height;
	glColor3f(1, 1, 1);

	glPushMatrix();
	fetchTexture("wood2.jpg", true, true);
	glPushMatrix();
	glTranslatef(0, 0, -0.5);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1);	glVertex3f(frame, frame, 0);
	glTexCoord2i(0, 0);	glVertex3f(width - frame, frame, 0);
	glTexCoord2i(1, 0);	glVertex3f(width - frame, height - frame, 0);
	glTexCoord2i(1, 1);	glVertex3f(frame, height - frame, 0);
	glEnd();
	glPopMatrix();

	fetchTexture("woodslats2.png", true, true);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);	glVertex3f(0, 0, 0);
	glTexCoord2i(1, 0);	glVertex3f(width, 0, 0);
	glTexCoord2i(1, 1);	glVertex3f(width - frame, frame, 0);
	glTexCoord2i(0, 1);	glVertex3f(frame, frame, 0);

	glTexCoord2i(1, 0);	glVertex3f(0, 0, 0);
	glTexCoord2i(1, 1);	glVertex3f(frame, frame, 0);
	glTexCoord2i(0, 1);	glVertex3f(frame, height - frame, 0);
	glTexCoord2i(0, 0);	glVertex3f(0, height, 0);

	glTexCoord2i(0, 1);	glVertex3f(width - frame, frame, 0);
	glTexCoord2i(0, 0);	glVertex3f(width, 0, 0);
	glTexCoord2i(1, 0);	glVertex3f(width, height, 0);
	glTexCoord2i(1, 1);	glVertex3f(width - frame, height - frame, 0);

	glTexCoord2i(1, 1);	glVertex3f(frame, height - frame, 0);
	glTexCoord2i(0, 1);	glVertex3f(width - frame, height - frame, 0);
	glTexCoord2i(0, 0);	glVertex3f(width, height, 0);
	glTexCoord2i(1, 0);	glVertex3f(0, height, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	fetchTexture("woodslats2.png", true, true);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);	glVertex3f(0, 0, 0);
	glTexCoord2i(1, 0);	glVertex3f(width, 0, 0);
	glTexCoord2i(1, 1);	glVertex3f(width, 0, -2);
	glTexCoord2i(0, 1);	glVertex3f(0, 0, -2);

	glTexCoord2i(0, 0);	glVertex3f(width, 0, -2);
	glTexCoord2i(1, 0);	glVertex3f(width, height, -2);
	glTexCoord2i(1, 1);	glVertex3f(width, height, 0);
	glTexCoord2i(0, 1);	glVertex3f(width, 0, 0);

	glTexCoord2i(0, 0);	glVertex3f(0, height, 0);
	glTexCoord2i(1, 0);	glVertex3f(width, height, 0);
	glTexCoord2i(1, 1);	glVertex3f(width, height, -2);
	glTexCoord2i(0, 1);	glVertex3f(0, height, -2);

	glTexCoord2i(0, 0);	glVertex3f(0, 0, 0);
	glTexCoord2i(1, 0);	glVertex3f(0, height, 0);
	glTexCoord2i(1, 1);	glVertex3f(0, height, -2);
	glTexCoord2i(0, 1);	glVertex3f(0, 0, -2);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	fetchTexture("woodslats2.png", true, true);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);	glVertex3f(0, frame, 0);
	glTexCoord2i(1, 0);	glVertex3f(width, frame, 0);
	glTexCoord2i(1, 1);	glVertex3f(width, frame, -2);
	glTexCoord2i(0, 1);	glVertex3f(0, frame, -2);

	glTexCoord2i(0, 0);	glVertex3f(width - frame, 0, -2);
	glTexCoord2i(1, 0);	glVertex3f(width - frame, height, -2);
	glTexCoord2i(1, 1);	glVertex3f(width - frame, height, 0);
	glTexCoord2i(0, 1);	glVertex3f(width - frame, 0, 0);

	glTexCoord2i(0, 0);	glVertex3f(0, height - frame, 0);
	glTexCoord2i(1, 0);	glVertex3f(width, height - frame, 0);
	glTexCoord2i(1, 1);	glVertex3f(width, height - frame, -2);
	glTexCoord2i(0, 1);	glVertex3f(0, height - frame, -2);

	glTexCoord2i(0, 0);	glVertex3f(frame, 0, 0);
	glTexCoord2i(1, 0);	glVertex3f(frame, height, 0);
	glTexCoord2i(1, 1);	glVertex3f(frame, height, -2);
	glTexCoord2i(0, 1);	glVertex3f(frame, 0, -2);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -2);
	fetchTexture("wood2.jpg", true, true);
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 1);	glVertex3f(frame, frame, 0);
	glTexCoord2i(0, 0);	glVertex3f(width - frame, frame, 0);
	glTexCoord2i(1, 0);	glVertex3f(width - frame, height - frame, 0);
	glTexCoord2i(1, 1);	glVertex3f(frame, height - frame, 0);
	glEnd();
	glPopMatrix();

	fetchTexture("woodslats2.png", true, true);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);	glVertex3f(0, 0, 0);
	glTexCoord2i(1, 0);	glVertex3f(width, 0, 0);
	glTexCoord2i(1, 1);	glVertex3f(width - frame, frame, 0);
	glTexCoord2i(0, 1);	glVertex3f(frame, frame, 0);

	glTexCoord2i(1, 0);	glVertex3f(0, 0, 0);
	glTexCoord2i(1, 1);	glVertex3f(frame, frame, 0);
	glTexCoord2i(0, 1);	glVertex3f(frame, height - frame, 0);
	glTexCoord2i(0, 0);	glVertex3f(0, height, 0);

	glTexCoord2i(0, 1);	glVertex3f(width - frame, frame, 0);
	glTexCoord2i(0, 0);	glVertex3f(width, 0, 0);
	glTexCoord2i(1, 0);	glVertex3f(width, height, 0);
	glTexCoord2i(1, 1);	glVertex3f(width - frame, height - frame, 0);

	glTexCoord2i(1, 1);	glVertex3f(frame, height - frame, 0);
	glTexCoord2i(0, 1);	glVertex3f(width - frame, height - frame, 0);
	glTexCoord2i(0, 0);	glVertex3f(width, height, 0);
	glTexCoord2i(1, 0);	glVertex3f(0, height, 0);
	glEnd();
	glPopMatrix();

}
void primitives_brickWall(float width, float height)
{
	float brickHeight = 2.5f;
	float brickWidth = 5.0f;
	float wholeWidth = 5.0f;
	float halfWidth = 2.5f;
	//float cementSize = .3f;
	float cementSize = .2f;
	float i, j;
	bool offset = false;

	for (j = 0; j < height; j += brickHeight) {
		for (i = 0; i < width; i += brickWidth) {

			if ((i == 0) && (offset)) { //first half brick
				brickWidth = halfWidth;
			} else if ((brickWidth == halfWidth)) { //whole brick
				brickWidth = wholeWidth;
			} else if ((offset) && (i + brickWidth > width)) { //last half brick
				brickWidth = halfWidth;
			}

			//Draw a brick
			fetchTexture("brick2.png", true, true);
			glBegin(GL_QUADS);
			glColor3f(1, 1, 1);
			glNormal3f(0, 0, 1);

			glTexCoord2i(0, 0);
			glVertex3f(i, j, 0);
			glTexCoord2i(1, 0);
			glVertex3f(i + brickWidth - cementSize, j, 0);
			glTexCoord2i(1, 1);
			glVertex3f(i + brickWidth - cementSize, j + brickHeight - cementSize, 0);
			glTexCoord2i(0, 1);
			glVertex3f(i, j + brickHeight - cementSize, 0);
			glEnd();

			//Draw cement
			glBindTexture(GL_TEXTURE_2D, 0);
			glBegin(GL_QUADS);
			//glColor3f(.5f, .5f, .5f);
			glColor3f(.2f, .2f, .2f);
			glNormal3f(1, 0, .1f);

			glVertex3f(i + brickWidth - cementSize, j, 0);
			glVertex3f(i + brickWidth, j, 0);
			glVertex3f(i + brickWidth, j + brickHeight - cementSize, 0);
			glVertex3f(i + brickWidth - cementSize, j + brickHeight - cementSize, 0);				
			glEnd();
		}

		//Draw cement
		glBegin(GL_QUADS);
		//glColor3f(.5f, .5f, .5f);
		glColor3f(.2f, .2f, .2f);
		glNormal3f(0, 1, .1f);

		glVertex3f(0, j + brickHeight - cementSize, 0);
		glVertex3f(width, j + brickHeight - cementSize, 0);
		glVertex3f(width, j + brickHeight, 0);
		glVertex3f(0, j + brickHeight, 0);
		glEnd();

		offset = !offset;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}
void MTcube(double x, double y, double z, double e)
{

	double s = e/2;
	glBegin(GL_QUADS);
	////right
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 0); 
	glVertex3f(x+s,y-s,z-s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 0); 
	glVertex3f(x-s,y-s,z-s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 1); 
	glVertex3f(x-s,y+s,z-s);
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 1); 
	glVertex3f(x+s,y+s,z-s);
	////left
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 0); 
	glVertex3f(x-s,y-s,z+s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 0); 
	glVertex3f(x+s,y-s,z+s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 1); 
	glVertex3f(x+s,y+s,z+s);
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 1); 
	glVertex3f(x-s,y+s,z+s);
	//back
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 0); 
	glVertex3f(x-s,y-s,z-s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 0); 
	glVertex3f(x-s,y-s,z+s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 1); 
	glVertex3f(x-s,y+s,z+s);
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 1); 
	glVertex3f(x-s,y+s,z-s);
	//front
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 0); 
	glVertex3f(x+s,y-s,z+s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 0); 
	glVertex3f(x+s,y-s,z-s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 1); 
	glVertex3f(x+s,y+s,z-s);
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 1); 
	glVertex3f(x+s,y+s,z+s);
	//bottom
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 0); 
	glVertex3f(x-s,y-s,z+s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 0); 
	glVertex3f(x-s,y-s,z-s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 1); 
	glVertex3f(x+s,y-s,z-s);
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 1); 
	glVertex3f(x+s,y-s,z+s);
	//top
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 0); 
	glVertex3f(x-s,y+s,z-s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 0); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 0); 
	glVertex3f(x-s,y+s,z+s);
	glMultiTexCoord2fARB(GL_TEXTURE0,1, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,1, 1); 
	glVertex3f(x+s,y+s,z+s);
	glMultiTexCoord2fARB(GL_TEXTURE0,0, 1); 
	glMultiTexCoord2fARB(GL_TEXTURE1,0, 1); 
	glVertex3f(x+s,y+s,z-s);
	glEnd();

}
BumpHouse::BumpHouse()
{
	color(.6f,.7f,.8f);
}
void BumpHouse::draw(DrawingState*)
{
	glColor3fv(&color.r);

	glDisable(GL_CULL_FACE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPushMatrix();
	glTranslatef(-20, 0, 25);
	primitives_brickWall(30, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(20, 0, 25);
	primitives_brickWall(30, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-20, 20, 25);
	primitives_brickWall(70, 10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10, 0, 25);
	glRotatef(-30, 0, 1, 0);
	door(10, 20, 5);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-20, 0, 25);
	glRotatef(90, 0, 1, 0);
	primitives_brickWall(50, 30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(50, 0, -25);
	glRotatef(180, 0, 1, 0);
	primitives_brickWall(70, 30);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(50, 0, -25);
	glRotatef(270, 0, 1, 0);
	primitives_brickWall(50, 30);
	glPopMatrix();

	fetchTexture("woodslats.jpg", true, true);
	//floor
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-20, 0, 25);
	glTexCoord2f(1, 0); glVertex3f(50, 0, 25);
	glTexCoord2f(1, 1); glVertex3f(50, 0, -25);
	glTexCoord2f(0, 1); glVertex3f(-20, 0, -25);
	glEnd();
	glPopMatrix();

	//boxes	
	Texture* t1 = fetchTexture("crate.jpg", true, true);
	Texture* t2 = fetchTexture("test.png", true, true);
	glEnable(GL_CULL_FACE);
	glPushMatrix();
	for(int k = 5;k > 0;k--){
		for(int j = k;j > 0;j--){
			for(int i = 0;i < j;i++){
				switch(i){
				case 0:
					t1 = fetchTexture("crate.jpg", true, true);
					break;
				case 1:
					t1 = fetchTexture("crate1.jpg", true, true);
					break;
				case 2:
					t1 = fetchTexture("crate2.jpg", true, true);
					break;
				case 3:
					t1 = fetchTexture("crate3.jpg", true, true);
					break;
				case 4:
					t1 = fetchTexture("crate4.jpg", true, true);
					break;
				}
				switch(k){
				case 1:
					t2 = fetchTexture("MT.jpg", true, true);
					break;
				case 2:
					t2 = fetchTexture("MT1.jpg", true, true);
					break;
				case 3:
					t2 = fetchTexture("MT2.jpg", true, true);
					break;
				case 4:
					t2 = fetchTexture("MT3.jpg", true, true);
					break;
				case 5:
					t2 = fetchTexture("MT4.jpg", true, true);
					break;
				}
				glActiveTextureARB(GL_TEXTURE0_ARB);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, t1->texName);
				glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
				glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_REPLACE);
				glActiveTextureARB(GL_TEXTURE1_ARB);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, t2->texName);
				glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
				glTexEnvf (GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_ADD);
				MTcube(10 - k*5, 2.5+i*5, 20+(j-k)*5, 5);
			}
		}
	}
	glActiveTexture(GL_TEXTURE0);
	glPopMatrix();
	glDisable(GL_CULL_FACE);

	glEnable(GL_TEXTURE_2D);
	//roof
	fetchTexture("woodslats.jpg", true, true);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, -1);
	glTexCoord2f(.51f, .51f); glVertex3f(-20, 30, 25);
	glTexCoord2f(.99f, .51f); glVertex3f(50, 30, 25);
	glTexCoord2f(.99f, .99f); glVertex3f(50, 40, 0);
	glTexCoord2f(.51f, .99f); glVertex3f(-20, 40, 0);

	glNormal3f(0, 1, 1);
	glTexCoord2f(.51f, .51f); glVertex3f(-20, 30, -25);
	glTexCoord2f(.51f, .99f); glVertex3f(-20, 40, 0);
	glTexCoord2f(.99f, .99f); glVertex3f(50, 40, 0);
	glTexCoord2f(.99f, .51f); glVertex3f(50, 30, -25);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);
	glTexCoord2f(.51f, .51f); glVertex3f(-20, 30, -25);
	glTexCoord2f(.99f, .51f); glVertex3f(-20, 30, 25);
	glTexCoord2f(.75f, .99f); glVertex3f(-20, 40, 0);

	glNormal3f(0, 0, -1);
	glTexCoord2f(.51f, .51f); glVertex3f(50, 30, -25);
	glTexCoord2f(.75f, .99f); glVertex3f(50, 40, 0);
	glTexCoord2f(.99f, .51f); glVertex3f(50, 30, 25);
	glEnd();
	glPopMatrix();

	glEnable(GL_CULL_FACE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 0);
}

SimpleHouse4::SimpleHouse4()
{
	color(.6f,.7f,.8f);
	rotMatrix(transform,'Y',3.14159f/2.f);
}
void SimpleHouse4::draw(DrawingState*)
{
	glColor3fv(&color.r);
	fetchTexture("house4side001.png");
	polygoni(4, 20, 0, 30, -20, 0, 30,  -20,30, 30, 20,30,30);
	fetchTexture("house4side001.png");
	polygoni(4, -20, 0, -30, 20, 0, -30, 20,30,-30,  -20,30, -30);
	fetchTexture("house4side002.png");
	polygoni(3,  20,30,30,  -20,30,30,  0,45,30);
	fetchTexture("house4side002.png");
	polygoni(3, -20,30,-30,  20,30,-30,   0,45,-30);
	fetchTexture("house4front001.png");
	glBegin(GL_POLYGON);
	glNormal3f(1,0,0);
	glTexCoord2f(0,1); glVertex3i( 20,30,-30);
	glTexCoord2f(1,1); glVertex3i( 20,30, 30);
	glTexCoord2f(1,0); glVertex3i( 20, 0, 30);
	glTexCoord2f(0,0); glVertex3i( 20, 0,-30);
	glEnd();
	fetchTexture("house4back001.png");
	glBegin(GL_POLYGON);
	glNormal3f(-1,0,0);
	glTexCoord2f(0,0); glVertex3i(-20, 0,-30);
	glTexCoord2f(1,0); glVertex3i(-20, 0, 30);
	glTexCoord2f(1,1); glVertex3i(-20,30, 30);
	glTexCoord2f(0,1); glVertex3i(-20,30,-30);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
	glBindTexture(GL_TEXTURE_2D,0);
	fetchTexture("house4roof001.png");
	polygoni( 4, 20,30,-30,  20,30, 30,   0, 45, 30,   0, 45, -30);
	polygoni(-4,-20,30,-30, -20,30, 30,   0, 45, 30,   0, 45, -30);
}
//**********************************************************************

//modified*****************************************************************
//**********************************************************************

//added*****************************************************************
//from internet, TODO modification
SimpleHouse5::SimpleHouse5()
{
	color(.6f,.7f,.8f);
	rotMatrix(transform,'Y',3.14159f/2.f);
}
void SimpleHouse5::draw(DrawingState*)
{
	glColor3fv(&color.r);

	fetchTexture("house_custom.bmp", true, true);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(.01f, .01f); glVertex3f(0, 0, 25);
	glTexCoord2f(.49f, .01f); glVertex3f(30, 0, 25);
	glTexCoord2f(.49f, .49f); glVertex3f(30, 25, 25);
	glTexCoord2f(.01f, .49f); glVertex3f(0, 25, 25);

	glNormal3f(-1, 0, 0);
	glTexCoord2f(.01f, .51f); glVertex3f(30, 0, 25);
	glTexCoord2f(.49f, .51f); glVertex3f(30, 0, -25);
	glTexCoord2f(.49f, .99f); glVertex3f(30, 25, -25);
	glTexCoord2f(.01f, .99f); glVertex3f(30, 25, 25);

	glNormal3f(1, 0, 0);
	glTexCoord2f(.01f, .51f); glVertex3f(0, 0, 25);
	glTexCoord2f(.01f, .99f); glVertex3f(0, 25, 25);
	glTexCoord2f(.49f, .99f); glVertex3f(0, 25, -25);
	glTexCoord2f(.49f, .51f); glVertex3f(0, 0, -25);

	glNormal3f(0, 0, -1);
	glTexCoord2f(.01f, .01f); glVertex3f(0, 0, -25);
	glTexCoord2f(.01f, .49f); glVertex3f(0, 25, -25);		
	glTexCoord2f(.49f, .49f); glVertex3f(30, 25, -25);
	glTexCoord2f(.49f, .01f); glVertex3f(30, 0, -25);

	glNormal3f(0, 1, 0);
	glTexCoord2f(.51f, .01f); glVertex3f(0, 25, 25);
	glTexCoord2f(.99f, .01f); glVertex3f(30, 25, 25);
	glTexCoord2f(.99f, .49f); glVertex3f(30, 25, -25);
	glTexCoord2f(.51f, .49f); glVertex3f(0, 25, -25);

	glNormal3f(0, 1, 1);
	glTexCoord2f(.51f, .51f); glVertex3f(15, 35, 25);
	glTexCoord2f(.51f, .99f); glVertex3f(30, 25, 25);
	glTexCoord2f(.99f, .99f); glVertex3f(30, 25, -8);
	glTexCoord2f(.99f, .51f); glVertex3f(15, 35, -8);		

	glNormal3f(0, 1, -1);
	glTexCoord2f(.51f, .51f); glVertex3f(15, 35, 25);
	glTexCoord2f(.99f, .51f); glVertex3f(15, 35, -8);		
	glTexCoord2f(.99f, .99f); glVertex3f(0, 25, -8);
	glTexCoord2f(.51f, .99f); glVertex3f(0, 25, 25);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, 1);
	glTexCoord2f(.51f, .51f); glVertex3f(0, 25, 25);
	glTexCoord2f(.99f, .51f); glVertex3f(30, 25, 25);
	glTexCoord2f(.99f, .99f); glVertex3f(15, 35, 25);

	glNormal3f(0, 0, -1);
	glTexCoord2f(.01f, .01f); glVertex3f(0, 25, -8);
	glTexCoord2f(.25f, .49f); glVertex3f(15, 35, -8);		
	glTexCoord2f(.49f, .01f); glVertex3f(30, 25, -8);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}
//**********************************************************************

//added*****************************************************************

StairHouse::StairHouse(){

}


void stair_house(float r, float g, float b){
	//wall
	glColor3f(r, g, b);
	//right side
	glPushMatrix();
	glTranslatef(-30, 20, 0);
	glScalef(1, 40, 40);
	cube(0, 0, 0, 1);
	glPopMatrix();
	//left side
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-30, 20, 0);
	glScalef(1, 40, 40);
	cube(0, 0, 0, 1);
	glPopMatrix();
	//glPushMatrix();
	//glTranslatef(30, 20, 0);
	//glScalef(1, 40, 40);
	//cube(0, 0, 0, 1);
	//glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(0, 20, 20);
	glScalef(60, 40, 1);
	cube(0, 0, 0, 1);
	glPopMatrix();
	//front
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(0, 20, 20);
	glScalef(60, 40, 1);
	cube(0, 0, 0, 1);
	glPopMatrix();
	//glPushMatrix();
	//glTranslatef(0, 20, -20);
	//glScalef(60, 40, 1);
	//cube(0, 0, 0, 1);
	//glPopMatrix();

	//roof
	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glTranslatef(5, -40, 0);
	glScalef(50, 1, 40);
	cube(0, 0, 0, 1);
	glPopMatrix();


	//stair
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPushMatrix();
	glTranslatef(-6, 4, 15);
	glScalef(4, 1, 10);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-10, 8, 15);
	glScalef(4, 1, 10);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-14, 12, 15);
	glScalef(4, 1, 10);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-18, 16, 15);
	glScalef(4, 1, 10);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 20, 15);
	glScalef(10, 1, 10);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 24, 8);
	glScalef(10, 1, 4);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 28, 4);
	glScalef(10, 1, 4);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 32, 0);
	glScalef(10, 1, 4);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 36, -4);
	glScalef(10, 1, 4);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 40, -13);
	glScalef(10, 1, 14);
	cube(0, 0, 0, 1);
	glPopMatrix();

}

void StairHouse::draw(DrawingState*)
{

	//wall
	//right side
	glColor3f(.5, .5, .5);
	glPushMatrix();
	glTranslatef(-30, 20, 0);
	glScalef(1, 40, 40);
	cube(0, 0, 0, 1);
	glPopMatrix();
	//left side
	glPushMatrix();
	glTranslatef(30, 20, 0);
	glScalef(1, 40, 40);
	cube(0, 0, 0, 1);
	glPopMatrix();
	//back
	glPushMatrix();
	glTranslatef(0, 20, 20);
	glScalef(60, 40, 1);
	cube(0, 0, 0, 1);
	glPopMatrix();
	////front lower
	//glPushMatrix();
	//	glTranslatef(20, 12.5, -20);
	//	glScalef(20, 25, 1);
	//	cube(0, 0, 0, 1);
	//glPopMatrix();
	//glPushMatrix();
	//	glTranslatef(-20, 12.5, -20);
	//	glScalef(20, 25, 1);
	//	cube(0, 0, 0, 1);
	//glPopMatrix();
	////front upper
	//glPushMatrix();
	//	glTranslatef(0, 32.5, -20);
	//	glScalef(60, 15, 1);
	//	cube(0, 0, 0, 1);
	//glPopMatrix();

	//front
	glPushMatrix();
	glTranslatef(20, 20, -20);
	glScalef(20, 40, 1);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-20, 20, -20);
	glScalef(20, 40, 1);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 32.5, -20);
	glScalef(20, 15, 1);
	cube(0, 0, 0, 1);
	glPopMatrix();

	//roof
	glPushMatrix();
	glTranslatef(5, 40, 0);
	glScalef(50, 1, 40);
	cube(0, 0, 0, 1);
	glPopMatrix();



	//stair
	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPushMatrix();
	glTranslatef(-2, 0, 15);
	glScalef(4, 1, 10);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-6, 4, 15);
	glScalef(4, 1, 10);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-10, 8, 15);
	glScalef(4, 1, 10);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-14, 12, 15);
	glScalef(4, 1, 10);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-18, 16, 15);
	glScalef(4, 1, 10);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 20, 15);
	glScalef(10, 1, 10);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 24, 8);
	glScalef(10, 1, 4);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 28, 4);
	glScalef(10, 1, 4);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 32, 0);
	glScalef(10, 1, 4);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 36, -4);
	glScalef(10, 1, 4);
	cube(0, 0, 0, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, 40, -13);
	glScalef(10, 1, 14);
	cube(0, 0, 0, 1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 40, 0);
	glRotatef(180, 0, 1, 0);
	fetchTexture("floor1.jpg");
	stair_house(1, 1, 1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 80, 0);
	fetchTexture("floor2.jpg");
	stair_house(1, 1, 1);
	glPopMatrix();

}
//**********************************************************************
//**********************************************************************
//added*****************************************************************
//modified*****************************************************************
//added*****************************************************************
ClockTower::ClockTower(int r) : roof(r)
{
	color(.6f,.7f,.8f);
}
void ClockTower::draw(DrawingState* d){
	glColor3fv(&color.r);
	//base
	glPushMatrix();
	glScalef(30, 15, 30);
	glutSolidCube(1);
	glPopMatrix();
	//body
	glPushMatrix();
	glTranslatef(0, 80, 0);
	glScalef(20, 150, 20);
	glutSolidCube(1);
	glPopMatrix();
	//poles
	glPushMatrix();
	glTranslatef(-10, 80, -10);
	glScalef(5, 150, 5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10, 80, -10);
	glScalef(5, 150, 5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(10, 80, 10);
	glScalef(5, 150, 5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-10, 80, 10);
	glScalef(5, 150, 5);
	glutSolidCube(1);
	glPopMatrix();
	//clock
	glPushMatrix();
	glTranslatef(0, 160, 0);
	glScalef(30, 30, 30);
	glutSolidCube(1);
	glPopMatrix();
	//boaders
	glPushMatrix();
	glTranslatef(-13, 160, -13);
	glScalef(5, 30, 5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(13, 160, -13);
	glScalef(5, 30, 5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(13, 160, 13);
	glScalef(5, 30, 5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-13, 160, 13);
	glScalef(5, 30, 5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 147.5, 13);
	glScalef(30, 5, 5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 147.5, -13);
	glScalef(30, 5, 5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(13, 147.5, 0);
	glScalef(5, 5, 30);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-13, 147.5, 0);
	glScalef(5, 5, 30);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 172.5, 13);
	glScalef(30, 5, 5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 172.5, -13);
	glScalef(30, 5, 5);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(13, 172.5, 0);
	glScalef(5, 5, 30);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-13, 172.5, 0);
	glScalef(5, 5, 30);
	glutSolidCube(1);
	glPopMatrix();
	//roof
	//fetchTexture("roof3.png");
	//polygoni(3, -15, 175, -15, 15, 175, -15, 0, 195, 0);
	//polygoni(3, 15, 175, -15, 15, 175, 15, 0, 195, 0);
	//polygoni(3, 15, 175, 15, -15, 175, 15, 0, 195, 0);
	//polygoni(3, -15, 175, 15, -15, 175, -15, 0, 195, 0);
	glPushMatrix();
	glTranslatef(0, 174, 0);
	glScalef(35, 3, 35);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 177, 0);
	glScalef(25, 3, 25);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 180, 0);
	glScalef(20, 3, 20);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 183, 0);
	glScalef(15, 3, 15);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 186, 0);
	glScalef(10, 3, 10);
	glutSolidCube(1);
	glPopMatrix();

	if (d->timeOfDay >=6 && d->timeOfDay <= 19)
		fetchTexture("env_skybox_texture001.png");
	else
		fetchTexture("env_skybox_texture003.png");

	glDisable(GL_CULL_FACE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP); 
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_FILL); 
	gluQuadricNormals(qobj, GLU_SMOOTH); 
	glEnable(GL_TEXTURE_GEN_S);	
	glEnable(GL_TEXTURE_GEN_T);
	glPushMatrix();
	glRotatef(mins_rotate * 30, 0, 1, 0);
	switch(roof){
	case 0:
		//sphere
		glTranslatef(0, 195, 0);
		gluSphere(qobj, 5, 25, 25);
		break;
		//sphere
	case 1:
		//cylinder
		glTranslatef(0, 200, 0);
		gluCylinder(qobj, 10, 10, 10, 25, 25);
		break;
		//cylinder
	case 2:
		//cube
		glTranslatef(0, 200, 0);
		glRotatef(45, 0, 0, 1);
		glRotatef(45, 1, 0, 0);
		glutSolidCube(10);
		break;
		//cube
	case 3:
		//cone
		glTranslatef(0, 200, 0);
		glRotatef(-45, 1, 0, 0);
		gluCylinder(qobj, 0, 10, 20, 25, 25);
		break;
		//cone
	}
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glPopMatrix();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 0);   
	glEnable(GL_CULL_FACE);

}
void ClockTower::drawAfter(DrawingState* d)
{
	int tod = d->timeOfDay;
	bool daytime;
	if (tod >=6 && tod <= 19)
		daytime = true;
	else 
		daytime = false;

	if (!daytime) {

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
		float cone_length = 200;
		float radius = 5;
		float theta,dtheta = pi/8;
		int c;

		float norm[3];
		float sum;
		// Beam One
		glPushMatrix();
		glDisable(GL_CULL_FACE);
		glTranslatef(65, -40, -60);
		glRotatef(15, 1, 0, 0);
		glRotatef(15, 0, 0, 1);
		glFrontFace(GL_CW);

		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1,1,0,.8f);
		glVertex3f(0,cone_length,0);
		for ( c=0,theta = 0.0 ; c <= 16  ; theta += dtheta, c++ ) {
			float z = sin(theta) * radius;
			float x = cos(theta) * radius;
			glColor4f(1,1,0,.2f);

			norm[0] = 0; norm[1] = x; norm[2] = z; sum = norm[0] + norm[1] + norm[2];
			norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;				
			glNormal3f( norm[0],norm[1],norm[2]);

			glVertex3f( x, cone_length/6, z );
		}
		glEnd();
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		// Beam Two
		glPushMatrix();
		glDisable(GL_CULL_FACE);
		glTranslatef(-65, -40, -60);
		glRotatef(15, 1, 0, 0);
		glRotatef(-15, 0, 0, 1);
		glFrontFace(GL_CW);

		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1,1,0,.8f);
		glVertex3f(0,cone_length,0);
		for ( c=0,theta = 0.0 ; c <= 16  ; theta += dtheta, c++ ) {
			float z = sin(theta) * radius;
			float x = cos(theta) * radius;
			glColor4f(1,1,0,.2f);

			norm[0] = 0; norm[1] = x; norm[2] = z; sum = norm[0] + norm[1] + norm[2];
			norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;				
			glNormal3f( norm[0],norm[1],norm[2]);

			glVertex3f( x, cone_length/6, z );
		}
		glEnd();
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		// Beam Three
		glPushMatrix();
		glDisable(GL_CULL_FACE);
		glTranslatef(-65, -40, 60);
		glRotatef(-15, 1, 0, 0);
		glRotatef(-15, 0, 0, 1);
		glFrontFace(GL_CW);

		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1,1,0,.8f);
		glVertex3f(0,cone_length,0);
		for ( c=0,theta = 0.0 ; c <= 16  ; theta += dtheta, c++ ) {
			float z = sin(theta) * radius;
			float x = cos(theta) * radius;
			glColor4f(1,1,0,.2f);

			norm[0] = 0; norm[1] = x; norm[2] = z; sum = norm[0] + norm[1] + norm[2];
			norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;				
			glNormal3f( norm[0],norm[1],norm[2]);

			glVertex3f( x, cone_length/6, z );
		}
		glEnd();
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		// Beam Four
		glPushMatrix();
		glDisable(GL_CULL_FACE);
		glTranslatef(65, -40, 60);
		glRotatef(-15, 1, 0, 0);
		glRotatef(15, 0, 0, 1);
		glFrontFace(GL_CW);

		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1,1,0,.8f);
		glVertex3f(0,cone_length,0);
		for ( c=0,theta = 0.0 ; c <= 16  ; theta += dtheta, c++ ) {
			float z = sin(theta) * radius;
			float x = cos(theta) * radius;
			glColor4f(1,1,0,.2f);

			norm[0] = 0; norm[1] = x; norm[2] = z; sum = norm[0] + norm[1] + norm[2];
			norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;				
			glNormal3f( norm[0],norm[1],norm[2]);

			glVertex3f( x, cone_length/6, z );
		}
		glEnd();
		glEnable(GL_CULL_FACE);
		glPopMatrix();

		glDisable(GL_BLEND);
		glClearColor(1,1,1,1);

	}
	//side1
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0, 160, -15);
	//hour hand
	glPushMatrix();
	/*tod/24*360 = tod*15*/
	glRotatef(tod*30, 0, 0, 1);
	glTranslatef(0, 3, 0);
	glScalef(1, 6, 1);
	glutSolidCube(1);
	glPopMatrix();
	//minute hand
	glPushMatrix();
	glRotatef(mins_rotate, 0, 0, 1);
	glTranslatef(0, 5, 0);
	glScalef(1, 10, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	//side2
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(0, 160, -15);
	//hour hand
	glPushMatrix();
	/*tod/24*360 = tod*15*/
	glRotatef(tod*30, 0, 0, 1);
	glTranslatef(0, 3, 0);
	glScalef(1, 6, 1);
	glutSolidCube(1);
	glPopMatrix();
	//minute hand
	glPushMatrix();
	glRotatef(mins_rotate, 0, 0, 1);
	glTranslatef(0, 5, 0);
	glScalef(1, 10, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	//side3
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(180, 0, 1, 0);
	glTranslatef(0, 160, -15);
	//hour hand
	glPushMatrix();
	/*tod/24*360 = tod*15*/
	glRotatef(tod*30, 0, 0, 1);
	glTranslatef(0, 3, 0);
	glScalef(1, 6, 1);
	glutSolidCube(1);
	glPopMatrix();
	//minute hand
	glPushMatrix();
	glRotatef(mins_rotate, 0, 0, 1);
	glTranslatef(0, 5, 0);
	glScalef(1, 10, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	//side4
	glPushMatrix();
	glColor3f(0, 0, 0);
	glRotatef(270, 0, 1, 0);
	glTranslatef(0, 160, -15);
	//hour hand
	glPushMatrix();
	/*tod/24*360 = tod*15*/
	glRotatef(tod*30, 0, 0, 1);
	glTranslatef(0, 3, 0);
	glScalef(1, 6, 1);
	glutSolidCube(1);
	glPopMatrix();
	//minute hand
	glPushMatrix();
	glRotatef(mins_rotate, 0, 0, 1);
	glTranslatef(0, 5, 0);
	glScalef(1, 10, 1);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();

	glColor3f(1, 1, 1);

}
void ClockTower::clock(float time)
{
	cumulate++;
	cumulate %= 1800/*30*60*/;
	mins_rotate = (int)cumulate / 5;
}
//**********************************************************************
//added*****************************************************************
BankOfChina::BankOfChina()
{
	color(.6f,.7f,.8f);
}
void BankOfChina::draw(DrawingState*)
{
	//glPushMatrix();
	//	glColor3f(0, 0, 0);
	//	glTranslatef(0.5, 322, 0.5);
	//	glScalef(0.2, 50, 0.2);
	//	glutSolidCube(1);
	//glPopMatrix();
	glColor3fv(&color.r);
	//BOC X5
	glPushMatrix();
	glPushMatrix();
	fetchTexture("boc_side5.png");
	polygoni(-4, 0,0,0, -30,0,30, -30,260,30, 0,260,0);
	polygoni(-4, 30,0,30, 0,0,0, 0,260,00, 30,260,30);
	polygoni(-4, -30,0,30, 30,0,30, 30,260,30, -30,260,30);
	glPopMatrix();
	//roof
	glPushMatrix();
	fetchTexture("boc_top.png");
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);	glVertex3f(-30, 260, 30);
	glTexCoord2f(1.0, 0.0);	glVertex3f(30, 260, 30);
	glTexCoord2f(0.5, 1.0);	glVertex3f(0, 307, 0);
	glEnd();
	fetchTexture("boc_side2.png");
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, -1);
	glTexCoord2f(1.0, 0.6);	glVertex3f(30, 260, 30);
	glTexCoord2f(0.0, 0.6);	glVertex3f(0, 260, 0);
	glTexCoord2f(0.0, 1.0);	glVertex3f(0, 307, 0);
	glEnd();
	fetchTexture("boc_side2.png");
	glBegin(GL_TRIANGLES);
	glNormal3f(-1, 0, 1);
	glTexCoord2f(0.0, 1.0);	glVertex3f(0, 307, 0);
	glTexCoord2f(0.0, 0.6);	glVertex3f(0, 260, 0);
	glTexCoord2f(1.0, 0.6);	glVertex3f(-30, 260, 30);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	//BOC X3
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	fetchTexture("boc_side3.png");
	polygoni(-4, 0,0,0, -30,0,30, -30,167,30, 0,167,0);
	polygoni(-4, 30,0,30, 0,0,0, 0,167,00, 30,167,30);
	polygoni(-4, -30,0,30, 30,0,30, 30,167,30, -30,167,30);
	glPopMatrix();
	//roof
	glPushMatrix();
	fetchTexture("boc_top.png");
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);	glVertex3f(-30, 167, 30);
	glTexCoord2f(1.0, 0.0);	glVertex3f(30, 167, 30);
	glTexCoord2f(0.5, 1.0);	glVertex3f(0, 214, 0);
	glEnd();
	fetchTexture("boc_side2.png");
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, -1);
	glTexCoord2f(1.0, 0.6);	glVertex3f(30, 167, 30);
	glTexCoord2f(0.0, 0.6);	glVertex3f(0, 167, 0);
	glTexCoord2f(0.0, 1.0);	glVertex3f(0, 214, 0);
	glEnd();
	fetchTexture("boc_side2.png");
	glBegin(GL_TRIANGLES);
	glNormal3f(-1, 0, 1);
	glTexCoord2f(0.0, 1.0);	glVertex3f(0, 214, 0);
	glTexCoord2f(0.0, 0.6);	glVertex3f(0, 167, 0);
	glTexCoord2f(1.0, 0.6);	glVertex3f(-30, 167, 30);
	glEnd();
	glPopMatrix();
	////roof
	//glPushMatrix();
	//fetchTexture("boc_roof001.png");
	//polygoni(-3, 0,230,0, 0,167,0, -30,167,30);
	//polygoni(-3, 0,230,0, 30,167,30, 0,167,0);
	//polygoni(-3, 0,230,0, -30,167,30, 30,167,30);
	//glPopMatrix();
	glPopMatrix();
	//BOC X2
	glPushMatrix();
	glRotatef(270, 0, 1, 0);
	glPushMatrix();
	fetchTexture("boc_side2.png");
	polygoni(-4, 0,0,0, -30,0,30, -30,120,30, 0,120,0);
	polygoni(-4, 30,0,30, 0,0,0, 0,120,00, 30,120,30);
	polygoni(-4, -30,0,30, 30,0,30, 30,120,30, -30,120,30);
	glPopMatrix();
	//roof
	glPushMatrix();
	fetchTexture("boc_top.png");
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);	glVertex3f(-30, 120, 30);
	glTexCoord2f(1.0, 0.0);	glVertex3f(30, 120, 30);
	glTexCoord2f(0.5, 1.0);	glVertex3f(0, 167, 0);
	glEnd();
	fetchTexture("boc_side2.png");
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0.0, 1.0);	glVertex3f(0, 167, 0);
	glTexCoord2f(0.0, 0.6);	glVertex3f(0, 120, 0);
	glTexCoord2f(1.0, 0.6);	glVertex3f(30, 120, 30);
	glEnd();
	fetchTexture("boc_side2.png");
	glBegin(GL_TRIANGLES);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0.0, 1.0);	glVertex3f(0, 167, 0);
	glTexCoord2f(0.0, 0.6);	glVertex3f(0, 120, 0);
	glTexCoord2f(1.0, 0.6);	glVertex3f(-30, 120, 30);
	glEnd();
	glPopMatrix();
	glPopMatrix();
	//BOC X1
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glPushMatrix();
	fetchTexture("boc_side1.png");
	polygoni(-4, 0,0,0, -30,0,30, -30,72,30, 0,72,0);
	polygoni(-4, 30,0,30, 0,0,0, 0,72,0, 30,72,30);
	polygoni(-4, -30,0,30, 30,0,30, 30,72,30, -30,72,30);
	glPopMatrix();
	//roof
	glPushMatrix();
	fetchTexture("boc_top.png");
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0, 0.0);	glVertex3f(-30, 72, 30);
	glTexCoord2f(1.0, 0.0);	glVertex3f(30, 72, 30);
	glTexCoord2f(0.5, 1.0);	glVertex3f(0, 120, 0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}
//**********************************************************************
//added*****************************************************************
void StadiumLight(double poleZ, double poleY){
	glColor3f(1,1,1);
	glBegin(GL_QUAD_STRIP);
	glNormal3d( 1, 0,0);
	glVertex3d( 1, 0,poleZ);
	glVertex3d( 1,poleY,poleZ);
	glNormal3d( 0, 0,1);
	glVertex3d( 0, 0,poleZ+1);
	glVertex3d( 0,poleY,poleZ+1);
	glNormal3d(-1, 0,0);
	glVertex3d(-1, 0,poleZ);
	glVertex3d(-1,poleY,poleZ);
	glNormal3d( 0, 0,-1);
	glVertex3d( 0, 0,poleZ-1);
	glVertex3d( 0,poleY,poleZ-1);
	glNormal3d( 1, 0,0);
	glVertex3d( 1, 0,poleZ);
	glVertex3d( 1,poleY,poleZ);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glNormal3d(0,1,0);
	glVertex3d( 0,poleY+1, 0);
	glVertex3d( 0,poleY+1, poleZ);
	glNormal3d(-.707,-.707, 0);
	glVertex3d(-1,poleY, 0);
	glVertex3d(-1,poleY, poleZ);
	glNormal3d(.707,-.707, 0);
	glVertex3d( 1,poleY, 0);
	glVertex3d( 1,poleY, poleZ);
	glNormal3d(0,1,0);
	glVertex3d( 0,poleY+1, 0);
	glVertex3d( 0,poleY+1, poleZ);
	glEnd();
	glEnable(GL_CULL_FACE);
	glColor3f(1, 1, 1);
}
FootballPitch::FootballPitch()
{
	color(.6f,.7f,.8f);
}
void FootballPitch::draw(DrawingState*)
{
	glColor3f(1, 1, 1);
	//stadium stand
	glPushMatrix();
	for(int i = 0;i < 10;i++){
		glPushMatrix();
		glTranslatef(0, 0.5+i, 50+10-(20-i*2)/2);
		glScalef(114, 1, 20 - i * 2);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(-50, 0, 30);
	glRotatef(-45, 0, 1, 0);
	StadiumLight(16, 40);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(50, 0, 30);
	glRotatef(45, 0, 1, 0);
	StadiumLight(16, 40);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	for(int i = 0;i < 10;i++){
		glPushMatrix();
		glTranslatef(0, 0.5+i, 50+10-(20-i*2)/2);
		glScalef(114, 1, 20 - i * 2);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(-50, 0, 30);
	glRotatef(-45, 0, 1, 0);
	StadiumLight(16, 40);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(50, 0, 30);
	glRotatef(45, 0, 1, 0);
	StadiumLight(16, 40);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	for(int i = 0;i < 10;i++){
		glPushMatrix();
		glTranslatef(0, 0.5+i, 67+10-(20-i*2)/2);
		glScalef(80, 1, 20 - i * 2);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	glRotatef(270, 0, 1, 0);
	for(int i = 0;i < 10;i++){
		glPushMatrix();
		glTranslatef(0, 0.5+i, 67+10-(20-i*2)/2);
		glScalef(80, 1, 20 - i * 2);
		glutSolidCube(1);
		glPopMatrix();
	}
	glPopMatrix();

	fetchTexture("FootballField.png");
	polygoni(4, -57, 0,-40,  57, 0,-40,  57,0,40,  -57,0,40);
	glPopMatrix();
	glColor3f(1, 1, 1);
}
void FootballPitch::drawAfter(DrawingState* d)
{
	int tod = d->timeOfDay;
	bool daytime;
	if (tod >=6 && tod <= 19)
		daytime = true;
	else 
		daytime = false;

	if (!daytime) {

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
		float cone_length = 100;
		float radius = 20;
		float theta,dtheta = pi/4;
		int c;

		float norm[3];
		float sum;
		// Beam One
		glPushMatrix();
		glDisable(GL_CULL_FACE);
		glRotatef(90, 0, 1, 0);
		glTranslatef(30, cone_length/2-10, 50);
		glRotatef(15, 1, 0, 0);
		glRotatef(-15, 0, 0, 1);
		glTranslatef(0, -1*cone_length, 0);
		glFrontFace(GL_CW);

		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1,1,0,.8f);
		glVertex3f(0,cone_length,0);
		for ( c=0,theta = 0.0 ; c <= 8  ; theta += dtheta, c++ ) {
			float z = sin(theta) * radius;
			float x = cos(theta) * radius;
			glColor4f(1,1,0,.2f);

			norm[0] = 0; norm[1] = x; norm[2] = z; sum = norm[0] + norm[1] + norm[2];
			norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;				
			glNormal3f( norm[0],norm[1],norm[2]);

			glVertex3f( x, cone_length/6, z );
		}
		glEnd();
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		// Beam One
		glPushMatrix();
		glDisable(GL_CULL_FACE);
		glRotatef(90, 0, 1, 0);
		glTranslatef(30, cone_length/2-10, 50);
		glRotatef(15, 1, 0, 0);
		glRotatef(-15, 0, 0, 1);
		glTranslatef(0, -1*cone_length, 0);
		glFrontFace(GL_CW);

		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1,1,0,.8f);
		glVertex3f(0,cone_length,0);
		for ( c=0,theta = 0.0 ; c <= 8  ; theta += dtheta, c++ ) {
			float z = sin(theta) * radius;
			float x = cos(theta) * radius;
			glColor4f(1,1,0,.2f);

			norm[0] = 0; norm[1] = x; norm[2] = z; sum = norm[0] + norm[1] + norm[2];
			norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;				
			glNormal3f( norm[0],norm[1],norm[2]);

			glVertex3f( x, cone_length/6, z );
		}
		glEnd();
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		// Beam Two
		glPushMatrix();
		glDisable(GL_CULL_FACE);
		glRotatef(180, 0, 1, 0);
		glTranslatef(50, cone_length/2-10, 30);
		glRotatef(15, 1, 0, 0);
		glRotatef(-15, 0, 0, 1);
		glTranslatef(0, -1*cone_length, 0);
		glFrontFace(GL_CW);

		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1,1,0,.8f);
		glVertex3f(0,cone_length,0);
		for ( c=0,theta = 0.0 ; c <= 8  ; theta += dtheta, c++ ) {
			float z = sin(theta) * radius;
			float x = cos(theta) * radius;
			glColor4f(1,1,0,.2f);

			norm[0] = 0; norm[1] = x; norm[2] = z; sum = norm[0] + norm[1] + norm[2];
			norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;				
			glNormal3f( norm[0],norm[1],norm[2]);

			glVertex3f( x, cone_length/6, z );
		}
		glEnd();
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		// Beam Three
		glPushMatrix();
		glDisable(GL_CULL_FACE);
		glRotatef(270, 0, 1, 0);
		glTranslatef(30, cone_length/2-10, 50);
		glRotatef(15, 1, 0, 0);
		glRotatef(-15, 0, 0, 1);
		glTranslatef(0, -1*cone_length, 0);
		glFrontFace(GL_CW);

		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1,1,0,.8f);
		glVertex3f(0,cone_length,0);
		for ( c=0,theta = 0.0 ; c <= 8  ; theta += dtheta, c++ ) {
			float z = sin(theta) * radius;
			float x = cos(theta) * radius;
			glColor4f(1,1,0,.2f);

			norm[0] = 0; norm[1] = x; norm[2] = z; sum = norm[0] + norm[1] + norm[2];
			norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;				
			glNormal3f( norm[0],norm[1],norm[2]);

			glVertex3f( x, cone_length/6, z );
		}
		glEnd();
		glEnable(GL_CULL_FACE);
		glPopMatrix();
		// Beam Four
		glPushMatrix();
		glDisable(GL_CULL_FACE);
		//glRotatef(0, 0, 1, 0);
		glTranslatef(50, cone_length/2-10, 30);
		glRotatef(15, 1, 0, 0);
		glRotatef(-15, 0, 0, 1);
		glTranslatef(0, -1*cone_length, 0);
		glFrontFace(GL_CW);

		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1,1,0,.8f);
		glVertex3f(0,cone_length,0);
		for ( c=0,theta = 0.0 ; c <= 8  ; theta += dtheta, c++ ) {
			float z = sin(theta) * radius;
			float x = cos(theta) * radius;
			glColor4f(1,1,0,.2f);

			norm[0] = 0; norm[1] = x; norm[2] = z; sum = norm[0] + norm[1] + norm[2];
			norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;				
			glNormal3f( norm[0],norm[1],norm[2]);

			glVertex3f( x, cone_length/6, z );
		}
		glEnd();
		glEnable(GL_CULL_FACE);
		glPopMatrix();

		glDisable(GL_BLEND);
		glClearColor(1,1,1,1);
	}
}
//**********************************************************************
/***********************************************************************/
// OK, this is even simpler...
SimpleHouse3::SimpleHouse3()
{
	color(.6f,.7f,.8f);
}
void SimpleHouse3::draw(DrawingState*)
{
	glColor3fv(&color.r);
	fetchTexture("simpleHouse2-front.png");
	polygoni(4, -20, 0,-20,  20, 0,-20,  20,30,-20,  -20,30,-20);
	fetchTexture("simpleHouse3-side.png");
	polygoni(4,  20, 0,-20,  20, 0, 20,  20,30, 20,   20,30,-20);
	fetchTexture("simpleHouse2-front.png");
	polygoni(4,  20, 0, 20, -20, 0, 20, -20,30, 20,   20,30, 20);
	fetchTexture("simpleHouse3-side.png");
	polygoni(4, -20, 0, 20, -20, 0,-20, -20,30,-20,  -20,30, 20);
	fetchTexture("roof3.png");
	polygoni(3, -20,30,-20,  20,30,-20,   0,45,0);
	polygoni(3,  20,30,-20,  20,30, 20,   0,45,0);
	polygoni(3,  20,30, 20, -20,30, 20,   0,45,0);
	polygoni(3, -20,30, 20, -20,30,-20,   0,45,0);
}


/***********************************************************************/
Church::Church() : GrObject("Church")
{
	color(.6f,.7f,.8f);
}
void Church::draw(DrawingState*)
{
	int xsz = 30;
	int zsz = 40;
	int hgh = 50;
	int top = 65;

	glColor3fv(&color.r);
	fetchTexture("church-front.png");
	glBegin(GL_POLYGON);
	glNormal3f(0,0,-1);
	glTexCoord2f(0,0); glVertex3i(-xsz, 0, -zsz);
	glTexCoord2f(0,1); glVertex3i(-xsz,hgh, -zsz);
	glTexCoord2f(.5,1.5); glVertex3i(  0,top,-zsz);
	glTexCoord2f(1,1); glVertex3i( xsz,hgh,-zsz);
	glTexCoord2f(1,0); glVertex3i( xsz, 0,-zsz);
	glEnd();
	glBegin(GL_POLYGON);
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3i(-xsz, 0,   zsz);
	glTexCoord2f(1,0); glVertex3i( xsz, 0,   zsz);
	glTexCoord2f(1,1); glVertex3i( xsz,hgh,   zsz);
	glTexCoord2f(.5,1.5); glVertex3i(  0,top,zsz);
	glTexCoord2f(0,1); glVertex3i(-xsz,hgh,   zsz);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);

	polygoni( 4, xsz,hgh,-zsz,  xsz,hgh, zsz,   0, top, zsz,   0, top, -zsz);
	polygoni(-4, -xsz,hgh,-zsz, -xsz,hgh, zsz,   0, top, zsz,   0, top,
		-zsz);

	fetchTexture("church-side.png");
	polygoni( 4, xsz, 0,-zsz,  xsz, 0, zsz,  xsz, hgh, zsz,  xsz, hgh, -zsz);
	polygoni(-4,-xsz, 0,-zsz, -xsz, 0, zsz, -xsz, hgh, zsz, -xsz, hgh, -zsz);


	glPushMatrix();
	glTranslatef(0,0,(float)zsz);
	int ss=10;					// steeple size
	int sh=60;					// height
	int th=120;					// top of point
	glBindTexture(GL_TEXTURE_2D,0);
	polygoni(4, -ss, 0,-ss,  ss, 0,-ss,  ss,sh,-ss,  -ss,sh,-ss);
	polygoni(4,  ss, 0,-ss,  ss, 0, ss,  ss,sh, ss,   ss,sh,-ss);
	polygoni(4,  ss, 0, ss, -ss, 0, ss, -ss,sh, ss,   ss,sh, ss);
	polygoni(4, -ss, 0, ss, -ss, 0,-ss, -ss,sh,-ss,  -ss,sh, ss);
	polygoni(3, -ss,sh,-ss,  ss,sh,-ss,   0,th,0);
	polygoni(3,  ss,sh,-ss,  ss,sh, ss,   0,th,0);
	polygoni(3,  ss,sh, ss, -ss,sh, ss,   0,th,0);
	polygoni(3, -ss,sh, ss, -ss,sh,-ss,   0,th,0);
	glPopMatrix();
}

/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
StreetLight::StreetLight(double p) : poleZ(p)
{
	radius = 10;
}
void StreetLight::draw(DrawingState*)
{
	glColor3f(.6f,.5f,.3f);
	glBegin(GL_QUAD_STRIP);
	glNormal3d( 1, 0,0);
	glVertex3d( 1, 0,poleZ);
	glVertex3d( 1,20,poleZ);
	glNormal3d( 0, 0,1);
	glVertex3d( 0, 0,poleZ+1);
	glVertex3d( 0,20,poleZ+1);
	glNormal3d(-1, 0,0);
	glVertex3d(-1, 0,poleZ);
	glVertex3d(-1,20,poleZ);
	glNormal3d( 0, 0,-1);
	glVertex3d( 0, 0,poleZ-1);
	glVertex3d( 0,20,poleZ-1);
	glNormal3d( 1, 0,0);
	glVertex3d( 1, 0,poleZ);
	glVertex3d( 1,20,poleZ);
	glEnd();

	glBegin(GL_QUAD_STRIP);
	glNormal3d(0,1,0);
	glVertex3d( 0,21, 0);
	glVertex3d( 0,21, poleZ);
	glNormal3d(-.707,-.707, 0);
	glVertex3d(-1,20, 0);
	glVertex3d(-1,20, poleZ);
	glNormal3d(.707,-.707, 0);
	glVertex3d( 1,20, 0);
	glVertex3d( 1,20, poleZ);
	glNormal3d(0,1,0);
	glVertex3d( 0,21, 0);
	glVertex3d( 0,21, poleZ);
	glEnd();

	glColor3f(0.8,0.2,0.2);
	glPushMatrix();
	glTranslatef(0,17,0);
	glutSolidSphere(1.5,10,20);
	glColor3f(0,0,0);
	glBegin(GL_LINE);
	glVertex3f(0,0,0);
	glVertex3f(20,0,0);
	glEnd();

	glColor3f(0,0,0);
	glRotatef(90,1,0,0);
	glutWireSphere(1.5,10,8);
	glPopMatrix();
}

void StreetLight::drawAfter(DrawingState* d)
{
	int tod = d->timeOfDay;
	bool daytime;
	if (tod >=6 && tod <= 19)
		daytime = true;
	else 
		daytime = false;

	if (!daytime) {

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_DST_ALPHA);
		float cone_length = 20;
		float radius = 10;
		float theta,dtheta = pi/16;
		int c;

		float norm[3];
		float sum;
		// Beam One
		glPushMatrix();

		//****************************added by ding ****************
		glFrontFace(GL_CW);
		glColor4f(1,1,0,.4f);	
		glTranslatef(0,18,0);
		glutSolidSphere(15,20,20);
		//****************************end added by ding*************
		/*****************************deleted by ding***************
		glBegin(GL_TRIANGLE_FAN);
		glColor4f(1,1,0,.8f);
		glVertex3f(0,cone_length,0);
		for ( c=0,theta = 0.0 ; c <= 32  ; theta += dtheta, c++ ) {
			float z = sin(theta) * radius;
			float x = cos(theta) * radius;
			glColor4f(1,1,0,.2f);

			norm[0] = 0; norm[1] = x; norm[2] = z; sum = norm[0] + norm[1] + norm[2];
			norm[0] /= sum; norm[1] /= sum; norm[2] /= sum;				
			glNormal3f( norm[0],norm[1],norm[2]);

			glVertex3f( x, cone_length/6, z );
		}  

		glEnd();
		*/
		glEnd();


		glPopMatrix();

		glDisable(GL_BLEND);
		glClearColor(1,1,1,1);

	}
}

/**********************************************************************/
Sign::Sign(float sxi, float syi, float hi, char* tex, 
	SignShape ss)
	: sx(sxi), sy(syi), h(hi), texName(tex), shape(ss)
{
}
void Sign::draw(DrawingState*)
{
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
	fetchTexture(texName);
	glBegin(GL_POLYGON);
	glNormal3f(0,0,1);
	glColor3f(1,1,1);
	drawShape(0);
	glEnd();
	// back of the sign
	glBindTexture(GL_TEXTURE_2D,0);
	glNormal3f(0,0,-1);
	drawShape(-.1f);
	// post
	glBegin(GL_POLYGON);
	glNormal3f(0,0,1);
	glVertex3f(-.1f,h,0);
	glVertex3f( .1f,h,0);
	glVertex3f( .1f,0,0);
	glVertex3f(-.1f,0,0);
	glEnd();
	glFrontFace(GL_CW);
	glBegin(GL_POLYGON);
	glNormal3f(0,0,1);
	glVertex3f(-.1f,h,-.05f);
	glVertex3f( .1f,h,-.05f);
	glVertex3f( .1f,0,-.05f);
	glVertex3f(-.1f,0,-.05f);
	glEnd();
	glFrontFace(GL_CCW);	
}
void Sign::drawShape(float z)
{
	glFrontFace(GL_CW);
	switch(shape) {
	case rectangle:
		glBegin(GL_POLYGON);
		glTexCoord2f(0.,0.); glVertex3f(-sx/2,h,z);
		glTexCoord2f(1.,0.); glVertex3f( sx/2,h,z);
		glTexCoord2f(1.,1.); glVertex3f( sx/2,h+sy,z);
		glTexCoord2f(0.,1.); glVertex3f(-sx/2,h+sy,z);
		glEnd();
		break;
	case octagon:
		glBegin(GL_POLYGON);
		glTexCoord2f(0.25f,0.f); glVertex3f(-sx/4,h,z);
		glTexCoord2f(0.75f,0.f); glVertex3f( sx/4,h,z);
		glTexCoord2f(1.f,.25f); glVertex3f( sx/2.f,h+    sy/4.f,z);
		glTexCoord2f(1.f,.75f); glVertex3f( sx/2.f,h+3.f*sy/4.f,z);
		glTexCoord2f(.75f,1); glVertex3f( sx/4,h+sy,z);
		glTexCoord2f(.25f,1); glVertex3f(-sx/4,h+sy,z);
		glTexCoord2f(0,.75f); glVertex3f(-sx/2.f,h+3.f*sy/4.f,z);
		glTexCoord2f(0,.25f); glVertex3f(-sx/2.f,h+sy/4.f,z);
		glEnd();
		break;
	case diamond:
		glBegin(GL_POLYGON);
		glTexCoord2f(0.45f, 0.f); glVertex3f(-sx/10,h,z);
		glTexCoord2f(0.55f, 0.f); glVertex3f( sx/10,h,z);
		glTexCoord2f(   1 ,.45f); glVertex3f( sx/2,h+9*sy/20.f,z);
		glTexCoord2f(   1 ,.55f); glVertex3f( sx/2,h+11*sy/20.f,z);
		glTexCoord2f(.55f, 1   ); glVertex3f( sx/10,h+sy,z);
		glTexCoord2f(.45f, 1   ); glVertex3f(-sx/10,h+sy,z);
		glTexCoord2f(   0 ,.55f); glVertex3f(-sx/2,h+11*sy/20.f,z);
		glTexCoord2f(   0 ,.45f); glVertex3f(-sx/2,h+ 9*sy/20.f,z);
		glEnd();
		break;
	};
	glFrontFace(GL_CCW);
}

// make the houses we create be from a set of colors
/////////////////////////////////////////
// stuff for all houses
static int houseColors[][3] = { {255, 255, 255}
};
int nHouseColors = 1;


////////////////////////////////////////////////////////////////////////
// draw a little suburban dream...
// a 100x200 lot...
SimpleLot::SimpleLot(int ht, int hc)  
{
	// make the things we want
	add(new Lawn(0,0,100,200),0,0,0,0);
	switch(ht % 3) {
	case 0: {
		SimpleHouse4* h1 = new SimpleHouse4();
		h1->color(houseColors[hc % nHouseColors]);
		add(h1,50.,0,60.,0);
		break; }
	case 1: {
		SimpleHouse7* h2 = new SimpleHouse7();
		h2->color(houseColors[hc% nHouseColors]);
		add(h2,50.,0,60.,0);
		break; }
	case 2: {
		DingHouse6* h3 = new DingHouse6();
		h3->color(houseColors[hc% nHouseColors]);
		add(h3,50.,0,60.,0);
		break; }
	} 
	add(new SimpleTree1(15,5), 10,0, 10,0);
	add(new SimpleTree1(15,5), 10,0,190,0);
	add(new SimpleTree1(15,5), 30,0,190,0);
	add(new SimpleTree1(15,5), 50,0,190,0);
	add(new SimpleTree1(15,5), 70,0,190,0);
}

/***********************************************************************/
// a set of houses going down the street
// the street is along the X axis from (0,0) to ( (nh+1)*100, 0)
SimpleSubdivision::SimpleSubdivision(int nh) 
{
	// street lights in front of every other house
	// alternate sides of the street
	for(int sl=0; sl<nh; sl ++) {
		add(new StreetLight(sl%2 ? 9 : -9), static_cast<float>(sl*100 + 25), 0, (float)((sl%2) ? 8 : -9));
	}

	// add houses - one on each side of the street
	for (int hc=0; hc<nh; hc++) {
		GrObject* g1 = new SimpleLot(rand(), rand());
		GrObject* g2 = new SimpleLot(rand(), rand());

		add(g1, (float) (hc*100)    ,0, 15, 0);
		add(g2, (float) (hc*100+100),0,-15,pi);
	}

	add(new Sign(4,4,4,"stop.png",octagon),(float)(100*nh-2),0,17,-(3.141592f/2.f));
	add(new Sign(4,4,4,"stop.png",octagon),  2,0,-17 ,(3.141592f/2.f));
}


