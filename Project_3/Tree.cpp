#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include "Tree.h"

Tree::Tree(float positionX, float positionY, float positionZ, float height, float base, float size){
	this->positionX = positionX;
	this->positionY = positionY;
	this->positionZ = positionZ;
	this->height = height;
	this->base = base;
	this->size = size;
	init();
}

void Tree::setTreeLevel(int level){
	this->treeLevel = level;
}

void Tree::setTreeBranch(int branch){
	this->treeBranch = branch;
	//buildTree();
}

void Tree::setLeafStyle(int num){
	this->leafStyle = num;
}

void Tree::setLeafColor(float R, float G, float B){
	this->leafRed = R;
	this->leafGreen = G;
	this->leafBlue = B;
}

void Tree::setTrunkColor(float R, float G, float B){
	this->trunkRed = R;
	this->trunkGreen = G;
	this->trunkBlue = B;
}

void Tree::setRange(float range){
	this->range = range;
}

void Tree::enableRandomColor(bool state){
	this->randomColor = state;
}

void Tree::enableRandomAngle(bool state){
	this->randomAngle = state;
}

void Tree::init(){
	angle = 0.0f;
	animation = false;
	this->leafStyle = 1;
	this->treeBranch = 4;
	this->range = 20;
	this->randomColor = true;
	this->makeaTree = glGenLists(1);
	this->randomAngle = true;
	this->staticAngle = 45.0f;
	//buildTree();
	//printf("X = %f, Y = %f,  Z = %f \n", this->positionX, this->positionY, this->positionZ);
	this->trunkRed = 0.9f;
	this->trunkGreen = 0.8f;
	this->trunkBlue = 0.9f;

	this->leafRed = 1.0f;
	this->leafGreen = 0.5f;
	this->leafBlue = 0.0f;
}

void Tree::buildTree(){
	glNewList(this->makeaTree, GL_COMPILE);
	this->makeTree(this->height,this->base, this->range);
	glEndList(); 
}



void Tree::render(){
	if(animation){
		angle+=1;
	}
	if(angle>360){
		angle-=360.0;
	}
	glPushMatrix();
		glTranslatef(this->positionX, this->positionY, this->positionZ);
		glScaled(this->size, this->size, this->size);
		glRotatef(90, 1.0f, 0, 0);
		glRotatef(angle, 0, 1.0f, 0);
		glCallList(makeaTree);
	glPopMatrix();
}

void Tree::makeCylinder(float height, float base){
	GLUquadric *obj = gluNewQuadric();
	glColor3f(this->trunkRed, this->trunkGreen, this->trunkBlue);
	glPushMatrix();
		glRotatef(-90, 1.0f, 0.0, 0.0);
		gluCylinder(obj, base,base-(0.5*base), height, 10,10);
	glPopMatrix();
	glutSwapBuffers();
}

void Tree::makeTree(float height, float base, float range){
	float angle;
	int i;
	int direction;
	int binaryAngle;
	makeCylinder(height, base); 
	glTranslatef(0.0, height, 0.0);

	height -= height*0.2f; 
	base-= base*0.3;

	for(i=0; i<treeBranch; i++){
		direction = rand()%4;
		if(randomAngle){
			angle = rand()%60+range;
			if(angle >50)
				angle = -(rand()%30+range);
		}
		else{
			binaryAngle = rand()%2;
			if(binaryAngle == 0){
				angle = staticAngle;
			}
			else angle = -staticAngle;
			
		}
		

		if (height >1){
			glPushMatrix();
				//glRotatef(angle, 1.0f, 1.0f, 1.0f);
				if(!randomAngle){
					direction = i;
				}
				switch(direction){
					case 0:
						glRotatef(angle, 1.0f, 1.0f, 1.0f);
						break;
					case 1:
						glRotatef(angle, 1.0f, -1.0f, 1.0f);
						break;
					case 2:
						glRotatef(angle, -1.0f, 1.0f, 1.0f);
						break;
					case 3:
						glRotatef(angle, -1.0f, -1.0f, 1.0f);
						break;
				}
				range -= 5;
				makeTree(height,base, range);
			glPopMatrix();
		}
		else{
			glBegin(GL_POLYGON);
				if(randomColor){
					switch(direction){
						case 0:
							glColor3f(1.0f, 0.5f, 0.0f);
							break;
						case 1:
							glColor3f(0.8f, 0.6f, 0.01f);
							break;
						case 2:
							glColor3f(0.6f, 0.25f, 0.05f);
							break;
						case 3:
							glColor3f(0.6f, 0.01f, 0.01f);
							break;
					}
				}
				else{
					glColor3f(this->leafRed, this->leafGreen, this->leafBlue);
				}
			
				if(leafStyle == 1){
					glVertex2f(0,1);  
					glVertex2f(-0.5,0.5);  
					glVertex2f(-0.3,-0.1);  
					glVertex2f(0.3,-0.1);  
					glVertex2f(0.5,0.5);  
				}
				else if(leafStyle == 2){
					glutSolidSphere( 0.5, 20.0, 20.0); 
				}
			glEnd();
			return;
		}
		//else glColor3f(0.0,1.0/a,0.0);glutSolidSphere(.2,10,10); add like fruits...
	}
}
