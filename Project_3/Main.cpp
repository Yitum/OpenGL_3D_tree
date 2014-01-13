#include <Stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "Tree.h"
#define Pi 3.1415926f
#pragma comment(lib,"glew32.lib")

float boundaryX, boundaryY;
float cameraX, cameraY, cameraZ;
float radiusInner, radiusOuter;
float cameraInitPostionX, cameraInitPostionY, cameraInitPostionZ; 
float cameraOffsetX, cameraOffsetY, cameraOffsetZ;
float lookAtInitPostionX, lookAtInitPostionY, lookAtInitPostionZ; 
float lookAtX, lookAtY, lookAtZ;
float lookAtOffsetX, lookAtOffsetY, lookAtOffsetZ;
int lightColor = 1;
float lightPosX = -1.0f, lightPosY = -0.5f, lightPosZ = 0.1f;
bool lightState = true;
bool animation = true;
bool forest = false;
float rotateAngle, xx, yy, zz;
bool gameState;
int angleMenu, forestMenu, branchMenu, leafMenu, segmentBaseMenu, segmentHeightMenu, colorMenu;

Tree *tree[5];

void renderPrimitive(void){
	//glColor3f(0.57, 0.46, 0.06f);
	glColor3f(0.15, 0.6, 0.15f);
	glBegin(GL_QUADS);
		glVertex3f(-boundaryX, -boundaryY, 0.0f); // The bottom left corner
		glVertex3f(-boundaryX, boundaryY, 0.0f); // The top left corner
		glVertex3f(boundaryX, boundaryY, 0.0f); // The top right corner
		glVertex3f(boundaryX, -boundaryY, 0.0f); // The bottom right corner
	glEnd();
}

void renderScene(void){
	GLfloat R, G, B;
	GLfloat ambientcolor[] = {0.5f, 0.5f, 0.5f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientcolor);

	//pointed light
	GLfloat lightColor0[] = {0.7f, 0.7f, 0.7f, 1.0f}; //Color (0.5, 0.5, 0.5)
    GLfloat lightPosition0[] = {4.0f, 0.0f, 5.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);

	
	//directional light
	if(lightColor == 1){
		R = 0.5f;
		G = 0.5f;
		B = 0.0f;
	}
	else if(lightColor == 2){
		R = 0.15f;
		G = 0.7f;
		B = 1.0f;
	}
	else if(lightColor == 3){
		R = 0.5f;
		G = 1.0f;
		B = 0.15f;
	}
	//GLfloat lightColor1[] = {0.5f, 0.5f, 0.0f, 0.0f};
	GLfloat lightColor1[] = {R, G, B, 0.0f};
	//GLfloat lightPosition1[] = {-1.0f, -0.5f, 0.1f, 0.0f}; 
	GLfloat lightPosition1[] = {lightPosX, lightPosY, lightPosZ, 0.0f}; 
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
}

void renderObject(void){
	if(forest){
		for(int i=0; i<5; i++){
			tree[i]->render();
		}	
	}
	else tree[0]->render();
}

void render(void){
	glClearColor(0.05, 0.29, 0.54f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glTranslatef(0, 0, -20.0f);
	gluLookAt(cameraX, cameraY, cameraZ, lookAtX, lookAtY, lookAtZ, 0.0f, 1.0f, 0.0f);
	
	glPushMatrix();
		glRotatef(rotateAngle-180, 0.0f, 0.0f, 1.0f);
		//glRotatef(xx, 1.0f, 0.0f, 0.0f);
		//glRotatef(yy, 0.0f, 1.0f, 0.0f);
		//glRotatef(zz, 0.0f, 0.0f, 1.0f);
		renderPrimitive();
		renderScene();
		renderObject();
	glPopMatrix();
	
	glFlush();
	glutSwapBuffers();
}

void reshape(int width, int height){
	if(height == 0){
		height = 1;
	}
	float ratio = width*1.0f / height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0 ,0, (GLsizei)width, (GLsizei)height);
	gluPerspective(50.0f, ratio, 0.1f, 100.0f);
	//glOrtho(-1.25, 1.25, -1.25 , 1.25 , -2.0, 2.0);
	//glFrustum(-1.0,1.0,-1.0,1.0,1.5,20.0);
	glMatrixMode(GL_MODELVIEW);
}

void initCharacter(){
	tree[0] = new Tree(0.0f, 0.0f, 0.0f, 2.5f, 0.25f, 1.0f);
	tree[0]->buildTree();
	
	tree[1] = new Tree(-6.0f, 3.5f, 0.0f, 1.8f, 0.2f, 0.8f);
	tree[1]->setTreeBranch(3);
	tree[1]->setLeafStyle(1);
	tree[1]->setRange(30.0f);
	tree[1]->setTrunkColor(0.27f, 0.01f, 0.6f);
	tree[1]->setLeafColor(1.0f, 0.17f, 0.9f);
	tree[1]->enableRandomColor(false);
	tree[1]->enableRandomAngle(false);
	//tree[1]->buildTree();

	tree[2] = new Tree(6.0f, 3.5f, 0.0f, 2.0f, 0.2f, 0.8f);
	tree[2]->setTreeBranch(3);
	tree[2]->setLeafStyle(2);
	tree[2]->setRange(30.0f);
	tree[2]->enableRandomColor(true);
	//tree[2]->buildTree();

	tree[3] = new Tree(-6.0f, -3.5f, 0.0f, 2.0f, 0.2f, 0.8f);
	tree[3]->setTreeBranch(3);
	tree[3]->setLeafStyle(2);
	tree[3]->setRange(25.0f);
	tree[3]->enableRandomColor(false);
	//tree[3]->buildTree();

	tree[4] = new Tree(6.0f, -3.5f, 0.0f, 2.2f, 0.3f, 0.8f);
	tree[4]->setTreeBranch(3);
	tree[4]->setLeafStyle(1);
	tree[4]->setRange(30.0f);
	tree[4]->setTrunkColor(0.0f, 0.6f, 0.7f);
	tree[4]->setLeafColor(1.0f, 0.25f, 0.25f);
	tree[4]->enableRandomColor(false);
	//tree[4]->buildTree();
}

void updateView(){
	//cameraX = player1->positionX+cameraOffsetX, cameraY = player1->positionY-3.5f+cameraOffsetY, cameraZ = 5.0f+cameraOffsetZ;
	//lookAtX = player1->positionX+lookAtOffsetY, lookAtY = player1->positionY-0.25+lookAtOffsetX, lookAtZ = player1->positionZ+lookAtOffsetZ;
	cameraX = cameraInitPostionX+cameraOffsetX, cameraY = cameraInitPostionY+cameraOffsetY, cameraZ = cameraInitPostionZ+cameraOffsetZ;
	lookAtX = lookAtInitPostionX+lookAtOffsetY, lookAtY = lookAtInitPostionY+lookAtOffsetX, lookAtZ = lookAtInitPostionZ+lookAtOffsetZ;
}

void initRender(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	if(lightState){
		glEnable(GL_LIGHTING);
	}
	else glDisable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
}

void init(){

	gameState = true;
	radiusInner = 2.5f;
	radiusOuter = 16.0f;
	cameraInitPostionX = 0.0f, cameraInitPostionY = -radiusOuter, cameraInitPostionZ = 15.0f;
	cameraOffsetX = 0.0f, cameraOffsetY = 0.0f, cameraOffsetZ = 0.0f;
	lookAtInitPostionX = 0.0f, lookAtInitPostionY = radiusInner, lookAtInitPostionZ = 0.0f; 
	lookAtOffsetX = 0.0f, lookAtOffsetY = 0.0f, lookAtOffsetZ = 0.0f;
	rotateAngle = 180.0f;
	xx = 0.0f, yy = 0.0f, zz = 0.0f;
	initRender();
	initCharacter();
	updateView();
	boundaryX = 8.0f, boundaryY = 5.0f;
}

void changeCameraPosition(unsigned char key, int x, int y){
	switch(key){
		case 'a':
			cameraOffsetX += 0.1;
			break;
		case 'd':
			cameraOffsetX -= 0.1;
			break;
		case 'e':
			cameraOffsetZ -= 0.1;
			break;
		case 'q':
			cameraOffsetZ += 0.1;
			break;
		case 's':
			cameraOffsetY -= 0.1;
			break;
		case 'w':
			cameraOffsetY += 0.1;
			break;
	}

}

void buildForest(){
	tree[1]->buildTree();
	tree[2]->buildTree();
	tree[3]->buildTree();
	tree[4]->buildTree();
}

void keyPressed(unsigned char key, int x, int y){
	switch(key){
		case 'a':
			changeCameraPosition(key, x, y);
			break;
		case 'd':
			changeCameraPosition(key, x, y);
			break;
		case 'e':
			changeCameraPosition(key, x, y);
			break;
		case 'f':
			forest = !forest;
			if(forest){
				buildForest();
			}
			break;
		case 'q':
			changeCameraPosition(key, x, y);
			break;
		case 'l':
			if(lightState){
				lightState = false;
			}
			else lightState = true;
			initRender();
			printf("switch light \n");
			break;
		case 's':
			changeCameraPosition(key, x, y);
			break;
		case 'w':
			changeCameraPosition(key, x, y);
			break;
		case 'x':
			lightPosZ--;
			break;
		case 'z':
			lightPosZ++;
			break;
		case 32:
			tree[0]->animation = !tree[0]->animation;
			animation = !animation;
			break;
		case 49:
			lightColor = 1;
			break;
		case 50:
			lightColor = 2;
			break;
		case 51:
			lightColor = 3;
			break;
		case 55:
			yy += 5.0f;
			printf("rotation: x=%f, y=%f, z=%f \n", xx,yy,zz);
			break;
		case 56:
			yy -= 5.0f;
			printf("rotation: x=%f, y=%f, z=%f \n", xx,yy,zz);
			break;
		case 57:
			zz += 5.0f;
			printf("rotation: x=%f, y=%f, z=%f \n", xx,yy,zz);
			break;
		case 48:
			zz -= 5.0f;
			printf("rotation: x=%f, y=%f, z=%f \n", xx,yy,zz);
			break;
		case 'n':
			lookAtOffsetX += 0.1f;
			break;
		case 'm':
			lookAtOffsetX -= 0.1f;
			break;
	}

}

void specialkeyPressed(int key, int x, int y){
	if(gameState){
		switch (key){
		case GLUT_KEY_UP: 
			xx += 5.0f;
			printf("rotation: x=%f, y=%f, z=%f \n", xx,yy,zz);
			break;
		case GLUT_KEY_DOWN: 
			xx -= 5.0f;
			printf("rotation: x=%f, y=%f, z=%f \n", xx,yy,zz);
			break;
		case GLUT_KEY_LEFT: 
			rotateAngle -= 10.0f;
			if(rotateAngle<0){
				rotateAngle = 360;
			}
			lookAtInitPostionX = radiusInner*sin(Pi/180*(rotateAngle+180));
			lookAtInitPostionY = radiusInner*cos(Pi/180*(rotateAngle+180));
			break;
		case GLUT_KEY_RIGHT: 
			rotateAngle += 10.0f;
			if(rotateAngle>360){
				rotateAngle = 0;
			}
			lookAtInitPostionX = radiusInner*sin(Pi/180*(rotateAngle+180));
			lookAtInitPostionY = radiusInner*cos(Pi/180*(rotateAngle+180));
			break;
		}
	}
}

void update(int value){
	updateView();
	glutPostRedisplay();
	glutTimerFunc(10, update, 1);
}

void angleOption(int value){
	if(value==0){
		tree[0]->enableRandomAngle(false);
		tree[0]->buildTree();
	}
	else{
		tree[0]->enableRandomAngle(true);
		tree[0]->buildTree();
	}
}

void forestOption(int value){
	if(value==0){
		forest = true;
		buildForest();
	}
	else forest = false;
}

void leafOption(int value){
	tree[0]->setLeafStyle(value);
	tree[0]->buildTree();
}

void branchOption(int value){
	int branchNum;
	if(value == 0){
		branchNum = tree[0]->treeBranch + 1;
		tree[0]->setTreeBranch(branchNum);
	}
	else{
		branchNum = tree[0]->treeBranch - 1;
		tree[0]->setTreeBranch(branchNum);
	}
	tree[0]->buildTree();

}

void segmentBaseOption(int value){
	if(value == 0){
		tree[0]->base += 0.1f;
	}
	else{
		tree[0]->base -= 0.1f;
	}
	tree[0]->buildTree();
}

void segmentHeightOption(int value){
	if(value == 0){
		tree[0]->height += 0.1f;
	}
	else{
		tree[0]->height -= 0.1f;
	}
	tree[0]->buildTree();
}

void colorOption(int value){
	if(value==0){
		tree[0]->enableRandomColor(false);
	}
	else{
		tree[0]->enableRandomColor(true);
	}
	tree[0]->buildTree();
}

void mainMenu(int value){
	if(value == 0){
		exit(0);
	}
}

void createMenu(){
	angleMenu = glutCreateMenu(angleOption);
		glutAddMenuEntry("Fixed", 0);
		glutAddMenuEntry("Random", 1);
	forestMenu = glutCreateMenu(forestOption);
		glutAddMenuEntry("Enable", 0);
		glutAddMenuEntry("Disable", 1);
	branchMenu = glutCreateMenu(branchOption);
		glutAddMenuEntry("Increase", 0);
		glutAddMenuEntry("Decrease", 1);
	leafMenu = glutCreateMenu(leafOption);
		glutAddMenuEntry("No leaves", 0);
		glutAddMenuEntry("Polygon", 1);
		glutAddMenuEntry("Sphere", 2);
	segmentBaseMenu = glutCreateMenu(segmentBaseOption);
		glutAddMenuEntry("Increase", 0);
		glutAddMenuEntry("Decrease", 1);
	segmentHeightMenu = glutCreateMenu(segmentHeightOption);
		glutAddMenuEntry("Increase", 0);
		glutAddMenuEntry("Decrease", 1);
	colorMenu = glutCreateMenu(colorOption);
		glutAddMenuEntry("Single", 0);
		glutAddMenuEntry("Multi", 1);


	glutCreateMenu(mainMenu);
		glutAddSubMenu("Branch", branchMenu);
		glutAddSubMenu("Branch Angle", angleMenu);
		glutAddSubMenu("Leaf", leafMenu);
		glutAddSubMenu("Leaf Color", colorMenu);
		glutAddSubMenu("Segment Base", segmentBaseMenu);
		glutAddSubMenu("Segment Height", segmentHeightMenu);
		glutAddSubMenu("Forest", forestMenu);
		glutAddMenuEntry("Exit", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 10);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Project 3 Tong Wang");

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed);
	glutSpecialFunc(specialkeyPressed);
	//glutIdleFunc(idle);

	init();
	createMenu();

	glutTimerFunc(10, update, 0);

	glutMainLoop();

	return 1;
}