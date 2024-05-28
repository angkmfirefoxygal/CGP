
/* Interactive Figure Program from Chapter 8 using cylinders (quadrics) */
/* Style similar to robot program but here we must traverse tree to Display */
/* Cylinders are displayed as filled and light/material properties */
/* are set as in sphere approximation program */

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <math.h>
#include <cstdio>

#define TORSO_HEIGHT 5.0
#define UPPER_ARM_HEIGHT 3.0
#define LOWER_ARM_HEIGHT 2.0
#define UPPER_LEG_RADIUS  0.5
#define LOWER_LEG_RADIUS  0.5
#define LOWER_LEG_HEIGHT 2.0
#define UPPER_LEG_HEIGHT 3.0
#define UPPER_LEG_RADIUS  0.5
#define TORSO_RADIUS 1.0
#define UPPER_ARM_RADIUS  0.5
#define LOWER_ARM_RADIUS  0.5
#define HEAD_HEIGHT 1.5
#define HEAD_RADIUS 1.0
#define TAIL_HEIGHT 2
#define TAIL_RADIUS .5

typedef float point[3];

//static GLfloat theta[11] = { 0.0,0.0,0.0,180.0,0.0,180.0,0.0,180.0,0.0,180.0,0.0 }; /* initial joint angles */

static GLfloat theta[13] = { 60,0,-30, 180,0,180,0,180,0,180,0,0,30 };

static GLint angle = 2;

GLUquadricObj* t, * h, * lua, * lla, * rua, * rla, * lll, * rll, * rul, * lul, * tail;

double size = 1.0;
int offset = 0;


void DrawTorso()
{
    glPushMatrix();
    //glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(t, TORSO_RADIUS, TORSO_RADIUS, TORSO_HEIGHT, 10, 10);
    glPopMatrix();
}

void DrawHead()
{
    glPushMatrix();
    glTranslatef(0.0, HEAD_HEIGHT, 0.0);
    glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
    gluSphere(h, 1.0, 10, 10);
    glPopMatrix();

    // Draw eye, nose, mouth
    glPushAttrib(GL_LIGHTING_BIT);

    GLfloat specular[] = { 1,1,1,1 };
    GLfloat difusse[] = { 0,0,0,1 };
    GLfloat ambient[] = { 0,0,0,1 };
    GLfloat shiness[] = { 20 };

    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difusse);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_SHININESS, shiness);

    // 왼쪽눈
    glPushMatrix();
    glScalef(1.3f, 1, 1);
    glTranslatef(-.4f, 2.2f, .7f);
    glutSolidSphere(.2, 20, 20);
    glPopMatrix();

    // 오른쪽눈
    glPushMatrix();
    glScalef(1.3f, 1, 1);
    glTranslatef(.4f, 2.2f, .7f);
    glutSolidSphere(.2, 20, 20);
    glPopMatrix();

    // 코
    glPushMatrix();
    glTranslatef(0, 1.9f, 1.f);
    glutSolidSphere(.2, 20, 20);
    glPopMatrix();

    // 입
    glPushMatrix();
    glLineWidth(2);

    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 1.9f, 1);
    glVertex3f(0, 1.4f, 1);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 1.4f, 1);
    glVertex3f(-.4f, 1.2f, 1.f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(0, 1.4f, 1);
    glVertex3f(.4f, 1.2f, 1);
    glEnd();
    glPopMatrix();

    // 수염
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-.5f, 1.8f, 1);
    glVertex3f(-1.2f, 2, 1);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(.5f, 1.8f, 1);
    glVertex3f(1.2f, 2, 1);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-.5f, 1.6f, 1);
    glVertex3f(-1.2f, 1.4f, 1);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(.5f, 1.6f, 1);
    glVertex3f(1.2f, 1.4f, 1);
    glEnd();

    glPopMatrix();

    glPopAttrib();
}


void RightUpperArm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void RightLowerArm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void LeftUpperArm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rua, UPPER_ARM_RADIUS, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void LeftLowerArm()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rla, LOWER_ARM_RADIUS, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT, 10, 10);
    glPopMatrix();
}

void RightUpperLeg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void RightLowerLeg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(lll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void LeftUpperLeg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rul, UPPER_LEG_RADIUS, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void LeftLowerLeg()
{
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rll, LOWER_LEG_RADIUS, LOWER_LEG_RADIUS, LOWER_LEG_HEIGHT, 10, 10);
    glPopMatrix();
}

void DrawTail()
{
    glPushMatrix();
    glTranslatef(0, 0, -3);
    glScalef(1, 1, 10);
    gluSphere(tail, 0.3, 10, 10);
    glPopMatrix();
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 0.0, 0.0);

    glRotatef(theta[0], 0.0, 1.0, 0.0);
    DrawTorso();
    glPushMatrix();

    glTranslatef(0.0, 0, TORSO_HEIGHT);
    glRotatef(theta[1], 1.0, 0.0, 0.0);
    glRotatef(theta[2], 0.0, 1.0, 0.0);
    glTranslatef(0.0, -HEAD_HEIGHT, 0.0);
    DrawHead();

    glPopMatrix();
    glPushMatrix();
    //glTranslatef(-(TORSO_RADIUS+UPPER_ARM_RADIUS), 0.9*TORSO_HEIGHT, 0);
    glTranslatef(-(TORSO_RADIUS + UPPER_ARM_RADIUS), 0, .9 * TORSO_HEIGHT);
    glRotatef(theta[3], 1.0, 0.0, 0.0);
    RightUpperArm();

    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[4], 1.0, 0.0, 0.0);
    RightLowerArm();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(TORSO_RADIUS + UPPER_ARM_RADIUS, 0, 0.9 * TORSO_HEIGHT);
    glRotatef(theta[5], 1.0, 0.0, 0.0);
    LeftUpperArm();

    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    glRotatef(theta[6], 1.0, 0.0, 0.0);
    LeftLowerArm();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(TORSO_RADIUS + UPPER_LEG_RADIUS), 0.1 * UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[7], 1.0, 0.0, 0.0);
    RightUpperLeg();

    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[8], 1.0, 0.0, 0.0);
    RightLowerLeg();

    glPopMatrix();
    glPushMatrix();
    glTranslatef(TORSO_RADIUS + UPPER_LEG_RADIUS, 0.1 * UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[9], 1.0, 0.0, 0.0);
    LeftUpperLeg();

    glTranslatef(0.0, UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[10], 1.0, 0.0, 0.0);
    LeftLowerLeg();

    glPopMatrix();

    glPushMatrix();
    glRotatef(theta[11], 0, 1, 0);
    glRotatef(theta[12], 1, 0, 0);
    DrawTail();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}



void OnMouseDown(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        theta[angle] += 5.0;
        if (theta[angle] > 360.0) theta[angle] -= 360.0;
    }
    if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        theta[angle] -= 5.0;
        if (theta[angle] < 360.0) theta[angle] += 360.0;
    }
    Display();
}

void MenuEvent(int id)
{

    if (id < 12) angle = id;
    //if (id == 11) exit(0);

}

void AnimationTimer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(10, AnimationTimer, 1);

    theta[2] += offset;
    theta[3] += offset;
    theta[4] -= offset;
    theta[5] -= offset;
    theta[6] += offset;
    theta[7] -= offset;
    theta[8] += offset;
    theta[9] += offset;
    theta[10] -= offset;
    theta[11] += offset;
    if (theta[3] < 150 || theta[3] > 210)
        offset = -offset;
}

void WalkMenu(int id)
{
    if (id == 0)
    {
        theta[2] = -30;
        theta[3] = 150;
        theta[4] = 60;
        theta[5] = 210;
        theta[6] = 0;
        theta[7] = 210;
        theta[8] = 0;
        theta[9] = 150;
        theta[10] = 60;
        theta[11] = -30;
    }
    glutTimerFunc(10, AnimationTimer, 1);
    // Re display window.
    glutPostRedisplay();
    offset = 2;
}




enum MatMenuID
{
    Gold = 1,
    Copper,
    Yellow,
    Green,
    White
};
void MaterialMenu(int id)
{
    GLfloat goldSpecular[] = { 0.6283, 0.5558, 0.3661, 1.0 };
    GLfloat goldDiffuse[] = { 0.7516, 0.6065, 0.2265, 1.0 };
    GLfloat goldAmbient[] = { 0.2473, 0.1995, 0.0745, 1.0 };
    GLfloat goldShininess[] = { 51.2 };

    GLfloat copperSpecular[] = { 0.1913, 0.0735, 0.0225, 1.0 };
    GLfloat copperDiffuse[] = { 0.7038, 0.2705, 0.0828, 1.0 };
    GLfloat copperAmbient[] = { 0.2568, 0.1376, 0.0860, 1.0 };
    GLfloat copperShininess[] = { 12.8 };

    GLfloat yellowSpecular[] = { .6f,.6f,.5f, 1.0 };
    GLfloat yellowDiffuse[] = { .5f,.5f,0, 1.0 };
    GLfloat yellowAmbient[] = { 0.25f,0.25f,0, 1.0 };
    GLfloat yellowShininess[] = { 25 };

    GLfloat greenSpecular[] = { 1,0,0, 1.0 };
    GLfloat greenDiffuse[] = { 0,1,0, 1.0 };
    GLfloat greenAmbient[] = { 0.2,0.2,0.2, 1.0 };
    GLfloat greenShininess[] = { 50 };

    GLfloat whiteSpecular[] = { 1,1,1, 1.0 };
    GLfloat whiteDiffuse[] = { 1,1,1, 1.0 };
    GLfloat whiteAmbient[] = { 1,1,1, 1.0 };
    GLfloat whiteShininess[] = { 50 };

    switch (id)
    {
        case MatMenuID::Gold:
            glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpecular);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDiffuse);
            glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmbient);
            glMaterialfv(GL_FRONT, GL_SHININESS, goldShininess);
            break;
        case MatMenuID::Copper:
            glMaterialfv(GL_FRONT, GL_SPECULAR, copperSpecular);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, copperDiffuse);
            glMaterialfv(GL_FRONT, GL_AMBIENT, copperAmbient);
            glMaterialfv(GL_FRONT, GL_SHININESS, copperShininess);
            break;
        case MatMenuID::Green:
            glMaterialfv(GL_FRONT, GL_SPECULAR, greenSpecular);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, greenDiffuse);
            glMaterialfv(GL_FRONT, GL_AMBIENT, greenAmbient);
            glMaterialfv(GL_FRONT, GL_SHININESS, greenShininess);
            break;
        case MatMenuID::White:
            glMaterialfv(GL_FRONT, GL_SPECULAR, whiteSpecular);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, whiteDiffuse);
            glMaterialfv(GL_FRONT, GL_AMBIENT, whiteAmbient);
            glMaterialfv(GL_FRONT, GL_SHININESS, whiteShininess);
            break;
        case MatMenuID::Yellow:
            glMaterialfv(GL_FRONT, GL_SPECULAR, yellowSpecular);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowDiffuse);
            glMaterialfv(GL_FRONT, GL_AMBIENT, yellowAmbient);
            glMaterialfv(GL_FRONT, GL_SHININESS, yellowShininess);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

enum LightMenuID
{
    LightRed = 1,
    LightGreen,
    LightBlue,
    LightWhite
};

void LightMenu(int id)
{
    if (id == LightMenuID::LightRed)
    {
        GLfloat ambient[] = { 1,0,0, 1.0 }; 	//조명 특성	
        GLfloat diffuse[] = { 0.8, 0.7, 0.6, 1.0 };
        GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    }
    else if (id == LightMenuID::LightGreen)
    {
        GLfloat ambient[] = { 0,1,0, 1.0 }; 	//조명 특성	
        GLfloat diffuse[] = { 0.8, 0.7, 0.6, 1.0 };
        GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    }
    else if (id == LightMenuID::LightBlue)
    {
        GLfloat ambient[] = { 0,0,1, 1.0 }; 	//조명 특성	
        GLfloat diffuse[] = { 0.8, 0.7, 0.6, 1.0 };
        GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    }
    else if (id == LightMenuID::LightWhite)
    {
        GLfloat ambient[] = { 1,1,1, 1.0 }; 	//조명 특성	
        GLfloat diffuse[] = { 1, 1, 1, 1.0 };
        GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };

        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    }


    glutPostRedisplay();
}

enum MenuID
{
   Torso=1,
   head1,
   Tail,
   Right_Upper_Arm,
   Right_Lower_Arm,
   Left_Upper_Arm,
   Left_Lower_Arm,
   Right_Upper_Leg,
   Right_Lower_Leg,
   Left_Upper_Leg,
   Left_Lower_Leg,
   Quit
};

void MenuID(int id) {


    if (id == MenuID::Torso) {

        angle = 0;

    }
    else if (id == MenuID::head1) {

        angle = 1;

    }
    else if (id == MenuID::Tail) {

        angle = 12;

    }
    else if (id == MenuID::Left_Lower_Arm) {

        angle = 3;

    }
    else if (id == MenuID::Left_Lower_Leg) {

        angle = 4;

    }
    else if (id == MenuID::Left_Upper_Arm) {

        angle = 5;

    }
    else if (id == MenuID::Left_Upper_Leg) {

        angle = 6;

    }
    else if (id == MenuID::Right_Lower_Arm) {

        angle = 7;

    }
    else if (id == MenuID::Right_Lower_Leg) {

        angle = 8;

    }
    else if (id == MenuID::Right_Upper_Arm) {

        angle = 9;

    }
    else if (id == MenuID::Right_Upper_Leg) {

        angle = 10;

    }
    else if(id == MenuID::Quit) {
        exit(0);
    }
        
    glutPostRedisplay();
}
void OnReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat)h / (GLfloat)w,
            10.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat)w / (GLfloat)h,
            10.0 * (GLfloat)w / (GLfloat)h, 0.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void OnInit()
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess = { 100.0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 10.0, 10.0, 10.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);

    /* allocate quadrics with filled drawing style */

    h = gluNewQuadric();
    gluQuadricDrawStyle(h, GLU_FILL);
    t = gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    lua = gluNewQuadric();
    gluQuadricDrawStyle(lua, GLU_FILL);
    lla = gluNewQuadric();
    gluQuadricDrawStyle(lla, GLU_FILL);
    rua = gluNewQuadric();
    gluQuadricDrawStyle(rua, GLU_FILL);
    rla = gluNewQuadric();
    gluQuadricDrawStyle(rla, GLU_FILL);
    lul = gluNewQuadric();
    gluQuadricDrawStyle(lul, GLU_FILL);
    lll = gluNewQuadric();
    gluQuadricDrawStyle(lll, GLU_FILL);
    rul = gluNewQuadric();
    gluQuadricDrawStyle(rul, GLU_FILL);
    rll = gluNewQuadric();
    gluQuadricDrawStyle(rll, GLU_FILL);
    tail = gluNewQuadric();
    gluQuadricDrawStyle(tail, GLU_FILL);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutCreateWindow("DogWithFace");
    OnInit();
    glutReshapeFunc(OnReshape);
    glutDisplayFunc(Display);
    glutMouseFunc(OnMouseDown);

    GLint matMenu = glutCreateMenu(MaterialMenu);
    glutAddMenuEntry("Gold", MatMenuID::Gold);
    glutAddMenuEntry("Copper", MatMenuID::Copper);
    glutAddMenuEntry("Yellow", MatMenuID::Yellow);
    glutAddMenuEntry("Green", MatMenuID::Green);
    glutAddMenuEntry("White", MatMenuID::White);


    GLint lightMenu = glutCreateMenu(LightMenu);
    glutAddMenuEntry("Red", LightMenuID::LightRed);
    glutAddMenuEntry("Green", LightMenuID::LightGreen);
    glutAddMenuEntry("Blue", LightMenuID::LightBlue);
    glutAddMenuEntry("White", LightMenuID::LightWhite);

    glutCreateMenu(WalkMenu);
    glutAddMenuEntry("walk", 0);
    glutTimerFunc(10, AnimationTimer, 1);

    
    glutCreateMenu(MenuID);
    glutAddMenuEntry("torso", MenuID::Torso);
    glutAddMenuEntry("head1", MenuID::head1);
    glutAddMenuEntry("tail", MenuID::Tail);
    glutAddMenuEntry("left lower arm", MenuID::Left_Lower_Arm);
    glutAddMenuEntry("left lower leg", MenuID::Left_Lower_Leg);
    glutAddMenuEntry("left upper arm", MenuID::Left_Upper_Arm);
    glutAddMenuEntry("left upper leg", MenuID::Left_Upper_Leg);
    glutAddMenuEntry("right lower arm", MenuID::Right_Lower_Arm);
    glutAddMenuEntry("right lower leg", MenuID::Right_Lower_Leg);
    glutAddMenuEntry("right upper arm", MenuID::Right_Upper_Arm);
    glutAddMenuEntry("right upper leg", MenuID::Right_Upper_Leg);
    



    glutAddSubMenu("Material", matMenu);
    glutAddSubMenu("Light", lightMenu);


    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutMainLoop();
    return 0;
}