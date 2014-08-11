/// GraphicsTown2006
// written by Michael   - originally written Fall, 2000
//
// updated Fall 2006 - more testing code
// updated Fall 2008 - switched some internal stuff (no more linked lists)

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

#include "GrTown_PCH.H"
#include "GraphicsTownUI.H"
#include "FlyCamera.H"
#include "GrWorld.H"
#include "DrawUtils.H"
#include "Examples/Objects.H"
#include "Examples/SimpleBehaviors.H"
#include "Examples/Cars.H"

// for setting up shader paths and textures
#include "Utilities/ShaderTools.H"
#include "Utilities/Texture.H"


// Example code (objects and behaviors)
#include "Examples/Suburbs.H"

#include "Roads/Roads.H"
#include "Roads/Drive.H"


// define this to get 2 cars that always turn
// #define TESTCARS

const int numCars = 1;
const int nGrids = 5;

int main(int /*argc*/, char** /*argv*/)
{
	// put in some texture paths - look all over the place
	texturePaths.push_back(".");
	texturePaths.push_back("..");
	texturePaths.push_back("Textures/signs");
	texturePaths.push_back("../Textures/signs");
	texturePaths.push_back("Textures/Textures");
	texturePaths.push_back("../Textures/Textures");
	texturePaths.push_back("Textures/Objects");
	texturePaths.push_back("../Textures/Objects");

	shaderPaths.push_back("Shaders");
	shaderPaths.push_back("../Shaders");


	//// add some more stuff
	//GrObject* o1 = new Church;
	//o1->interesting = true;
	//o1->laX = 0; o1->laY = 0; o1->laZ = 0;
	//o1->lfX = -50; o1->lfY = 100; o1->lfZ = 300;
	//add(o1,-100,0,100,pi/4.f);


	// *****************************************************************
	//  Make your town here
	GrObject * sb = new SkyBox;
	add(sb, 0, 0, 0, 0);

	GrObject* airship = new Airship(350,400,-75,10,1,   1, 1, 1);
	new MoveForward(airship, 10);
	new Video(airship);
	add(airship);

	GrObject* airship1 = new Airship(350,400,-75,10,0,   1, 1, 1);
	new MoveForward(airship1, 10);
	new Video(airship1);
	add(airship1, 300, 0, 0);

	GrObject* clockTower = new ClockTower(0);
	new Clock(clockTower);
	add(clockTower, 200, 0, -250);
	GrObject* clockTower1 = new ClockTower(1);
	new Clock(clockTower1);
	add(clockTower1, 200, 0, 1200);
	GrObject* clockTower2 = new ClockTower(2);
	new Clock(clockTower2);
	add(clockTower2, 2600, 0, 1200);
	GrObject* clockTower3 = new ClockTower(3);
	new Clock(clockTower3);
	add(clockTower3, 2600, 0, -250);
	GrObject* stairhouse = new StairHouse();
	add(stairhouse, -200, 0, 200);

	GrObject* bankOfChina = new BankOfChina();
	add(bankOfChina, 550, 0, -350);    //550,-350,
	GrObject* footballPitch = new FootballPitch();
	add(footballPitch, -200, 0, 300);   


	GrObject* bumpHouse = new BumpHouse();
	add(bumpHouse, 400, 0, -500);

	//for(int i = 0;i < 1000;i++){
	//	GrObject* snow = new Snow((rand()%3000), 300+(rand()%400), (rand()%3000));
	//	Falling* fall = new Falling(snow);
	//	fall->speed *= (1 + (rand()%1000) /250);
	//	add(snow, 0, 200, 0);
	//}
	GrObject* snowBox = new SnowBox(3000, 400, 1000,2000);
	add(snowBox, 0, 0, 0);
	GrObject* fogBox = new FogBox();
	add(fogBox, 0, 0, 0);


	////////////////////////////////////////////////////////////////////////
	// now to make a real town!
	int r,c;
	// make a 5x5 grid of town blocks - 5 houses per
	for( r=0; r<5; r++) {
		for( c=0; c<5; c++) {
			add(new SimpleSubdivision(5),static_cast<float>(r*530),0,static_cast<float>(c*230));
			add(new StraightRoad(static_cast<float>(r*530),static_cast<float>(c*230),static_cast<float>(r*530+500),static_cast<float>(c*230)));
		}
	}
	//// make cross streets
	for(int r=0; r<=5; r++) {
		for(c=0; c<4; c++) {
			add(new StraightRoad(static_cast<float>(r*530 - 15), static_cast<float>(c*230 + 15), static_cast<float>(r*530 - 15), static_cast<float>(c*230+215)));
		}
	}

	//// make intersections
	//// make an intersection intersesting so we can look at it
	for(int r=0; r<=5; r++) {
		for(c=0; c<5; c++) {
			GrObject* g = new Intersection(static_cast<float>(r*530-15), static_cast<float>(c*230));
			if ( (r==2) && (c==3) ) {
				g->interesting = 1;
				g->name = "Intersection(2,3)";
				g->laX = static_cast<float>(r*530-15);    g->laY = 0;    g->laZ = static_cast<float>(c*230);
				g->lfX = static_cast<float>(r*530+25);   g->lfY = 100;   g->lfZ = static_cast<float>(c*230+150);
			}
			add(g);
		}
	}

#ifndef TESTCARS
  // add some cars
  for(int r=0; r<50; r++) {
	Car* c;
	DingCar0* cc;
	DingCar1* ccc;
	switch(rand() % 3) {
	  //case 0: c = new Van(rand()); break;
		case 0: c = new Van(rand()); 
					  	add(c);
			new RandomDrive(c,theRoads[rand() % theRoads.size()],.2f,rand() % 2);
			break;

	  case 1: c = new SUV(rand()); 
		  	add(c); 
			new RandomDrive(c,theRoads[rand() % theRoads.size()],.2f,rand() % 2);
		  break;
	  case 2: ccc = new MyDingCar1(rand()); 
		  	add(ccc);
			new RandomDrive(ccc,theRoads[rand() % theRoads.size()],.2f,rand() % 2);
		  
		  break;
	}

  }
#endif

#ifdef TESTCARS
	// two cars - one always turns right, one always turns left
	Car* c1 = new HatchBack(1);
	Car* c2 = new HatchBack(2);
	add(c1);
	add(c2);
	new RandomDrive(c1,theRoads[7],.5,0,-1);
	new RandomDrive(c2,theRoads[8],.5,0,1);

#endif

/************************edited by ding*********************************/
// ========== TODO1: ===================
// The following code added a round race track, 
//  you're required to replace it with an elliptical race track and put two cars running on it.


	// a race track
    Road* t = new EllipticalRoad(1400,400,1800,1200);
	add(t);
	t->name = "Track1";
	t->interesting = true;
	t->laX = 1400; t->laY = 0;   t->laZ = 400;
	t->lfX = -200; t->lfY = 200; t->lfZ = 200;
	// make cars go around the track

	Car1* h1 = new MyCar2(1);
	h1->name="Race2";		// warning! we can only do this since we don't delete
	new Blink(h1);
	add(h1);
	

	/****************added by ding*************************/
	DingCar0* h2 = new MyDingCar0(1);
	h2->name="Mail0";		// warning! we can only do this since we don't delete
	add(h2);
	/****************end added by ding********************/


	
	Drive* d1 = new SimpleDrive(h1,t,0,1);
	Drive* d2 = new SimpleDrive(h2,t,0,0);
	d1->speed *= 0.5;
	d2-> speed *= 0.5;
/************************edited by ding*********************************/


/************************edited by ding*********************************/
// ========== TODO1: ===================
// The following code added a round race track, 
//  you're required to replace it with an elliptical race track and put two cars running on it.


	// a race track
    Road* t0 = new EllipticalRoad(1400,400,1900,1300);
	add(t0);
	t0->name = "Track_robot";
	t0->interesting = true;
	t0->laX = 1400; t0->laY = 0;   t0->laZ = 400;
	t0->lfX = -200; t0->lfY = 200; t0->lfZ = 200;
	// make cars go around the track

	Robot* h01 = new Robot();
	h01->name="Robot";		// warning! we can only do this since we don't delete
	add(h01);
	new Walk(h01);
	Drive* d01 = new SimpleDrive(h01,t0,0,1);
	d01->speed *= 1.2;
/************************edited by ding*********************************/




/************************edited by ding*********************************/
// ========== TODO1: ===================
// The following code added a round race track, 
//  you're required to replace it with an elliptical race track and put two cars running on it.


	// a race track
    Road* t2 = new EllipticalRoad(-200,300,100,200);
	add(t2);
	t2->name = "Track2";
	t2->interesting = true;
	t2->laX = -200; t2->laY = 0;   t2->laZ = 300;
	t2->lfX = -200; t2->lfY = 200; t2->lfZ = 200;
	// make cars go around the track

	Car1* h21 = new MyCar2(1);
	h21->name="Race2";		// warning! we can only do this since we don't delete
	new Blink(h21);
	add(h21);
	

	/****************added by ding*************************/
	DingCar0* h22 = new MyDingCar0(1);
	h22->name="Mail0";		// warning! we can only do this since we don't delete
	add(h22);
	/****************end added by ding********************/


	
	Drive* d21 = new SimpleDrive(h21,t2,0,1);
	Drive* d22 = new SimpleDrive(h22,t2,0,0);
	d21->speed *= 0.5;
	d22-> speed *= 0.5;
/************************edited by ding*********************************/


/************************edited by ding*********************************/
// ========== TODO1: ===================
// The following code added a round race track, 
//  you're required to replace it with an elliptical race track and put two cars running on it.


	// a race track
    Road* t3 = new EllipticalRoad(550,-350,200,100);
	add(t3);
	t3->name = "Track3";
	t3->interesting = true;
	t3->laX = 550; t3->laY = 0;   t3->laZ = -350;
	t3->lfX = -200; t3->lfY = 200; t3->lfZ = 200;
	// make cars go around the track

	Car1* h31 = new MyCar2(1);
	h31->name="Race2";		// warning! we can only do this since we don't delete
	new Blink(h31);
	add(h31);
	

	/****************added by ding*************************/
	DingCar0* h32 = new MyDingCar0(1);
	h32->name="Mail0";		// warning! we can only do this since we don't delete
	add(h32);
	/****************end added by ding********************/


	
	Drive* d31 = new SimpleDrive(h31,t3,0,1);
	Drive* d32 = new SimpleDrive(h32,t3,0,0);
	d31->speed *= 0.5;
	d32-> speed *= 0.5;
/************************edited by ding*********************************/

	// now make a UI
	FlyCamera* fc = new FlyCamera;
	Map* m = new Map;

	add(fc);
	add(m);

	GraphicsTownUI grTown;
	grTown.make_window();
	grTown.townView->defaultCamera = fc;
	grTown.window->show();

	Fl::run();
	return 1;
}

