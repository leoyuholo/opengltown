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

#include "../GrTown_PCH.H"
#include "Objects.H"
#include "../DrawUtils.H"
#include "Utilities/Texture.H"
#include "../MMatrix.H"
#include <FL/fl_ask.h>

#include <GL/glut.h>


#include "Utilities/ShaderTools.H"


Robot::Robot(void){
  left_rotate_angle = 0;
  left_movement = 1;
  right_rotate_angle = 0;
  right_movement = -1;
}
void Robot::Walk(float time)
{
	left_rotate_angle += left_movement * 5;
	right_rotate_angle += right_movement * 5;
	if (left_rotate_angle > 20)
		left_movement = -1;
	if (left_rotate_angle < -20)
		left_movement = 1;
	if (right_rotate_angle > 20)
		right_movement = -1;
	if (right_rotate_angle < -20)
		right_movement = 1;
}
void Robot::draw(DrawingState*){
int j,i;
float PI = 3.141592654f;
int p = 10;
int q = 10;
int R = 1;
	//drawing hemi-sphere
/*
   for(j = 0; j < q; j++)
   {
      // One latitudinal triangle strip.
      glBegin(GL_TRIANGLE_STRIP);
         for(i = 0; i <= p; i++)
		 {
            glVertex3f( R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
                        R * sin( (float)(j+1)/q * PI/2.0 ),
					    R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
            glVertex3f( R * cos( (float)j/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
                        R * sin( (float)j/q * PI/2.0 ),
					    R * cos( (float)j/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );         
		 }
      glEnd();
   }
   */
//change gluSphere to hemi sphere, and cylinder to quads by modifying the above code:
   
		glPushMatrix(); //draw robot
		glColor3f(0.4, 1, 0);
		glTranslatef(0,10,0);
		glRotatef(90,-1,0,0);
		glScalef(10, 10, 10);

		glPushMatrix(); //draw body
		glScalef(1, 1, 2);
		glDisable(GL_CULL_FACE);
		GLUquadricObj *robot_body = gluNewQuadric();
		gluCylinder(robot_body, 1, 1, 1, 20, 20);
		glEnable(GL_CULL_FACE);
		glPopMatrix();

		glPushMatrix(); //draw head
		glTranslatef(0, 0, 2);
		glPushMatrix();
		//glutSolidSphere(1, 20, 20);
		glRotatef(90,1,0,0);
		   for(j = 0; j < q; j++)
		   {
			  // One latitudinal triangle strip.
			  glBegin(GL_TRIANGLE_STRIP);
				 for(i = 0; i <= p; i++)
				 {
					glVertex3f( R * cos( (float)(j+1)/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
								R * sin( (float)(j+1)/q * PI/2.0 ),
								R * cos( (float)(j+1)/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );
					glVertex3f( R * cos( (float)j/q * PI/2.0 ) * cos( 2.0 * (float)i/p * PI ),
								R * sin( (float)j/q * PI/2.0 ),
								R * cos( (float)j/q * PI/2.0 ) * sin( 2.0 * (float)i/p * PI ) );         
				 }
			  glEnd();
		   }
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-0.5, 0, 0.7);
		glRotatef(-30, 0, 1, 0);
		glScalef(0.1, 0.1, 0.5);
		glDisable(GL_CULL_FACE);
		GLUquadricObj *antenna1 = gluNewQuadric();
		gluCylinder(antenna1, 1, 1, 1, 20, 20);
		glEnable(GL_CULL_FACE);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.5, 0, 0.7);
		glRotatef(30, 0, 1, 0);
		glScalef(0.1, 0.1, 0.5);
		glDisable(GL_CULL_FACE);
		GLUquadricObj *antenna2 = gluNewQuadric();
		gluCylinder(antenna2, 1, 1, 1, 20, 20);
		glEnable(GL_CULL_FACE);
		glPopMatrix();

		glPopMatrix();

		glPushMatrix(); //draw left hand
		glTranslatef(-1.2, 0, 0.5);
		glScalef(0.3, 0.3, 1.5);
		glDisable(GL_CULL_FACE);
		GLUquadricObj *robot_lhand = gluNewQuadric();
		gluCylinder(robot_lhand, 1, 1, 1, 20, 20);
		glEnable(GL_CULL_FACE);
		glPopMatrix();

		glPushMatrix(); //draw right hand
		glTranslatef(1.2, 0, 1.5);
		glRotatef(0, 0, 1, 0);
		glScalef(0.3, 0.3, 1.5);
		glDisable(GL_CULL_FACE);
		GLUquadricObj *robot_rhand = gluNewQuadric();
		gluCylinder(robot_rhand, 1, 1, 1, 20, 20);
		glEnable(GL_CULL_FACE);
		glPopMatrix();

		glPushMatrix(); //draw left leg
		glTranslatef(-0.5, 0, -1);
		glScalef(0.3, 0.3, 1);
		glRotated(left_rotate_angle, 0,-1,0);
		GLUquadricObj *robot_lleg = gluNewQuadric();
		gluCylinder(robot_lhand, 1, 1, 1, 20, 20);
		glPopMatrix();

		glPushMatrix(); //draw right leg
		glTranslatef(0.5, 0, -1);
		glScalef(0.3, 0.3, 1);
		glRotated(right_rotate_angle, 0,-1,0);
		GLUquadricObj *robot_rleg = gluNewQuadric();
		gluCylinder(robot_rleg, 1, 1, 1, 20, 20);
		glPopMatrix();

		glPopMatrix();
}

//added*****************************************************************
Snow::Snow(float x, float y, float z)
{
	transMatrix(transform,x,y,z);
}
void Snow::draw(DrawingState*){
	glColor3f(1, 1, 1);
	glPushMatrix();
	GLUquadricObj *snow;
	snow = gluNewQuadric();
	gluSphere(snow, 1, 5, 5);
	glPopMatrix();
	//Falling* fall = new Falling(this, 0.05);
}
Airship::Airship(float x, float y, float z, float s, int aa, 
	float r, float g, float b)
	: color(r,g,b), size(s), antiAlias(aa)
{
	transMatrix(transform,x,y,z);
	pic[0] = "pic1.png";	pic[1] = "pic2.png";	pic[2] = "pic3.png";	pic[3] = "pic4.png";	pic[4] = "pic5.png";
	pic[5] = "pic6.png";	pic[6] = "pic7.png";	pic[7] = "pic8.png";	pic[8] = "pic9.png";	pic[9] = "pic10.png";
	frame = 0;
}
void Airship::draw(DrawingState*)
{
	glColor4fv(&color.r);
	glRotatef(-90, 0, 1, 0);
	glPushMatrix();
	GLUquadricObj *sphere;
	sphere = gluNewQuadric();
	glScalef(3, 1, 1);
	gluSphere(sphere, 40, 20, 20);
	glColor3f(0, 0, 0);
	glPushMatrix();
	glRotatef(90, 1, 0, 0);

	if(antiAlias == 1){
		glEnable(GL_LINE_SMOOTH); 
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Ask for best line antialiasing.
	}else
		glDisable(GL_LINE_SMOOTH);

	glRasterPos3f(-4.5, 4.5, -5.1);
	glLineWidth(1);

	glutWireSphere(40.4, 20, 20);
	glPopMatrix();
	glPushMatrix();
	Color c = Color(1, 1, 1);
	glColor4fv(&c.r);
	glTranslatef(0, -37, 0);
	glScalef(55, 15, 10);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	c = Color(0, 99, 255);
	glColor4fv(&c.r);
	glTranslatef(-110, 10, 0);
	glScalef(50, 40, 1);
	polygoni(4, 0,0,0, 1,0,0, 1,1,0, 0,1,0);
	polygoni(3, 1,0,0, 2,0,0, 1,1,0);
	polygoni(-4, 0,0,0, 1,0,0, 1,1,0, 0,1,0);
	polygoni(-3, 1,0,0, 2,0,0, 1,1,0);
	glPopMatrix();
	glPushMatrix();
	c = Color(0, 99, 255);
	glColor4fv(&c.r);
	glRotatef(90, 1, 0, 0);
	glTranslatef(-110, 10, 0);
	glScalef(50, 40, 1);
	polygoni(4, 0,0,0, 1,0,0, 1,1,0, 0,1,0);
	polygoni(3, 1,0,0, 2,0,0, 1,1,0);
	polygoni(-4, 0,0,0, 1,0,0, 1,1,0, 0,1,0);
	polygoni(-3, 1,0,0, 2,0,0, 1,1,0);
	glPopMatrix();
	glPushMatrix();
	c = Color(0, 99, 255);
	glColor4fv(&c.r);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(-110, 10, 0);
	glScalef(50, 40, 1);
	polygoni(4, 0,0,0, 1,0,0, 1,1,0, 0,1,0);
	polygoni(3, 1,0,0, 2,0,0, 1,1,0);
	polygoni(-4, 0,0,0, 1,0,0, 1,1,0, 0,1,0);
	polygoni(-3, 1,0,0, 2,0,0, 1,1,0);
	glPopMatrix();
	glPushMatrix();
	c = Color(1, 1, 1);
	glColor4fv(&c.r);
	glTranslatef(-80, -132, 0);
	glScalef(160, 90, 1);
	fetchTexture(pic[frame]);
	polygoni(-4, 1,0,0, 0,0,0, 0,1,0,  1,1,0);
	polygoni(-4, 0,0,0, 1,0,0, 1,1,0, 0,1,0);
	glPopMatrix();
}

void Airship::update(float time)
{
	cumulate++;
	cumulate %= 60;
	frame = (int)cumulate / 6;
	beam_rotate_angle = cumulate * 2 - 60;
}
void Airship::drawAfter(DrawingState* d)
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
		float cone_length = 600;
		float radius = 5;
		float theta,dtheta = pi/8;
		int c;
		int b1_rotate_angle;
		if(beam_rotate_angle > 0){
			b1_rotate_angle = 30 - beam_rotate_angle;
		}else{
			b1_rotate_angle = 30 + beam_rotate_angle;
		}
		float norm[3];
		float sum;
		// Beam One
		glPushMatrix();
		glDisable(GL_CULL_FACE);
		glTranslatef(2, -30, -30);
		glRotatef(b1_rotate_angle, 1, 0, 0);
		glTranslatef(0, -600, 0);
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
		glTranslatef(2, -30, 30);
		glRotatef(-1 * b1_rotate_angle, 1, 0, 0);
		glTranslatef(0, -600, 0);
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
		glTranslatef(-2, -30, -30);
		glRotatef(-1*b1_rotate_angle, 1, 0, 0);
		glTranslatef(0, -600, 0);
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
		glTranslatef(-2, -30, 30);
		glRotatef(b1_rotate_angle, 1, 0, 0);
		glTranslatef(0, -600, 0);
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
}
//**********************************************************************


// some very basic classes of objects...
// mainly for debugging
Cube::Cube(float x, float y, float z, float s, 
	float r, float g, float b)
	: color(r,g,b), size(s)
{
	transMatrix(transform,x,y,z);
}
void Cube::draw(DrawingState*)
{
	glColor4fv(&color.r);
	cube(0,0,0,size);
}

/***********************************************************************/
TestCubes::TestCubes()
{
}

void TestCubes::draw(DrawingState*)
{
	glColor3f(1,0,0);
	cube( 20,0,0, 3);
	cube(-20,0,0, 3);
	cube(0, 20,0, 3);
	cube(0,-20,0, 3);
	cube(0,0, 20, 3);
	cube(0,0,-20, 3);

	glColor3f(1,1,0);
	cube(20,10,20,3);
	glColor3f(0,1,1);
	cube(-20,10,20,3);
	glColor3f(1,0,1);
	cube(-20,10,-20,3);
	glColor3f(1,1,1);
	cube(20,10,-20,3);
}

// some very basic classes of objects...
// mainly for debugging
ShadedCube::ShadedCube(float x, float y, float z, float s, 
	float r, float g, float b)
	: color(r,g,b), size(s)
{
	transMatrix(transform,x,y,z);
}

// load the shader in the first time the cube draws (since that way we
// know we have a GL context)
// we only try to load it once
static unsigned int shadedCubeShader = 0;
static bool triedCubeShader=false;

void ShadedCube::draw(DrawingState*)
{
	if (!shadedCubeShader && !triedCubeShader) {
		triedCubeShader = true;
		char* error;
		if (!(shadedCubeShader=loadShader("ShadedCubeTest.vert","ShadedCubeTest.frag",error))) {
			std::string s = "Can't Load Cube Shader:";
			s += error;
			fl_alert(s.c_str());
		}
	}

	glUseProgram(shadedCubeShader);
	glColor4fv(&color.r);
	cube(0,0,0,size);
	glUseProgram(0);
}

