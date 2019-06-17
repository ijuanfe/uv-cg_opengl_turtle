/*
    Escuela de Ingeniería de Sistemas y Computación - Universidad del Valle
    Asignatura: Computación Gráfica 750006M
    Tema: Introducción a OpenGL - dibujando una tortuga
    Archivo: inicio_tortuga.cpp
    Version: 0.1
    Fecha de creacion: 14 junio 2019
    Autores:   
            Diana Marcela García Correa - 1531722
            Juan Felipe Orozco Escobar  - 1426244
*/

#include <stdio.h>
#include <stdlib.h>
#include "GL/freeglut.h"
#include "GL/gl.h"
using namespace std;

// Variables para modificar estado de las figuras
static GLdouble UP_OR_DOWN = 0.0;
static GLdouble RIGHT_OR_LEFT = 0.0;
static GLboolean AXES_STATE = true;
static GLboolean TURTLE_TYPE = true; // true for simple turtle, false for spherical turtle
static GLint WIDTH = 512;
static GLint HEIGHT = 512;

// 1. Dibujar los ejes del sistema de coordenadas de la ventana utlilizando
// los colores rojo, verde y azul (RGB) para los ejes x, y, z respectivamente
void draw_axes(void){
    
    glBegin(GL_LINES);
        // eje x: rojo
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-2.0, 0.0, 0.0);
        glVertex3f(2.0, 0.0, 0.0);
        // eje y: verde
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, -2.0, 0.0);
        glVertex3f(0.0, 2.0, 0.0);
        // eje z: azul
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, -2.0);
        glVertex3f(0.0, 0.0, 2.0);
    glEnd();
}

void draw_SphereTurtle(void) {

    glLineWidth(1);
    glColor3f(1.0,0.6,0.8);
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix(); //remember current matrix
    glTranslatef(0.0,0.0,0.0);
    glutWireSphere(0.7, 20, 10);
    glPopMatrix(); //restore matrix
    
    glPushMatrix(); //remember current matrix
    glTranslatef(0.0,0.8125,0.0);
    glutWireSphere(0.275, 20, 10);
    glPopMatrix(); //restore matrix
    
    glPushMatrix(); //remember current matrix
    glTranslatef(-0.50,0.5,0.0);
    glutWireSphere(0.246, 20, 10);
    glPopMatrix(); //restore matrix

    glPushMatrix(); //remember current matrix
    glTranslatef(0.50,0.5,0.0);
    glutWireSphere(0.246, 20, 10);
    glPopMatrix(); //restore matrix

    glPushMatrix(); //remember current matrix
    glTranslatef(-0.30,-0.71875,0.0);
    glutWireSphere(0.24, 20, 10);
    glPopMatrix(); //restore matrix

    glPushMatrix(); //remember current matrix
    glTranslatef(0.30,-0.71875,0.0);
    glutWireSphere(0.24, 20, 10);
    glPopMatrix(); //restore matrix
}

void draw_Turtle(void) {

    glLineWidth(1.5);
    glBegin(GL_LINES);
        glColor3f(1.0,0.6,0.8);
        float x[] = {0.0,-0.13125,-0.1875,-0.125,-0.24375,-0.3625,-0.4375,-0.5125,-0.7375,-0.68125,-0.625,-0.46875,-0.3125,-0.38125,-0.4375,-0.46875,-0.475,-0.4375,-0.35625,-0.21875,-0.35,-0.35,-0.25,-0.15625,-0.1125,-0.125,0.0};
        float y[] = {0.8125,0.75,0.625,0.5,0.4375,0.5125,0.5625,0.54375,0.5,0.4875,0.375,0.2875,0.33125,0.25,0.15625,0.1,-0.175,-0.25,-0.35625,-0.4375,-0.625,-0.675,-0.71875,-0.68125,-0.625,-0.49375,-0.59375};
        
        glVertex3f (0.0, 0.8125, 0.0);
        for(int i=1;i<27;i++){
            glVertex3d (x[i], y[i], 0.0);
            glVertex3d (x[i], y[i], 0.0);
        }
        for(int i=26;i>=0;i--){
            glVertex3d (x[i]*(-1.0), y[i], 0.0);
            glVertex3d (x[i]*(-1.0), y[i], 0.0);
        }
    glEnd();
}

void display(void) {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(AXES_STATE){
        draw_axes();
    }

    if(TURTLE_TYPE){
        draw_Turtle();
    }else{
        draw_SphereTurtle();
    }
    glutSwapBuffers();
}

void reshape(int width, int height) {

    // 3. Modificar la función glView port de manera que al alargar la
    // ventana la figura no se deforme. Se logra haciendo que el viewport
    // sea siempre cuadrada, de dimensión el menor de los valores de la
    // altura y la anchura. El valor de la relación entre la altura y la
    // anchura para la función gluPerspective() es ahora siempre 1.
    // Probar diferentes vistas iniciales con la función gluLookAt
    if(width <= height){
        glViewport(0, 0, width, width);
    }else{
        glViewport(0, 0, height, height);
    }
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //distancia: x,y,z...coordenadas: x,y,z...dirvector:x,y,z
    gluLookAt(RIGHT_OR_LEFT, UP_OR_DOWN, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // de frente
}

void keyboard(unsigned char key, int x, int y) {

    switch (key) {

        // 4. Introducir un comando nuevo de manera que al apretar la tecla ‘a’ (axis), se 
        // muestren los ejes de la figura si están desactivados o se desactiven si están activados
        case 'a':
            if(AXES_STATE){
                AXES_STATE = false;
            }else{
                AXES_STATE = true;
            }
            break;
        
        // Para cambiar entre los dos tipos de tortugas
        case 'z':
            if(TURTLE_TYPE){
                TURTLE_TYPE = false;
            }else{
                TURTLE_TYPE = true;
            }
            break;
        
        // 5. Introducir otro comando de manera que con las teclas ‘u’, ‘d’, ‘r’ y ‘l’
        // (up, down, right, left) se tralade la cámara manipulando la función gluLookAt
        case 'u':
            UP_OR_DOWN += 0.1;
            reshape(WIDTH, HEIGHT);
            break;
        
        case 'd':
            UP_OR_DOWN -= 0.1;
            reshape(WIDTH, HEIGHT);
            break;
        
        case 'r':
            RIGHT_OR_LEFT += 0.1;
            reshape(WIDTH, HEIGHT);
            break;
        
        case 'l':
            RIGHT_OR_LEFT -= 0.1;
            reshape(WIDTH, HEIGHT);
            break;

        case 'h':
            printf("Help menu:\n\n");
            printf("c:\t\tToggle culling\n");
            printf("q/escape:\tQuit\n");
            printf("z:\t\tChange turtle type\n");
            printf("u,d,r,l:\tChange eye position\n\n");
            break;
        
        case 'c':
            if (glIsEnabled(GL_CULL_FACE))
                glDisable(GL_CULL_FACE);
            else
                glEnable(GL_CULL_FACE);
            break;
        
        case '1':
            glRotatef(1.0,1.,0.,0.);
            break;
        
        case '2':
            glRotatef(1.0,0.,1.,0.);
            break;
        
        case 'q':
    
        case 27:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(650, 250);
    glutCreateWindow("Tortuga | Computacion Grafica");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();
    
    return 0;
}
