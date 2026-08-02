#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

//Global variables
GLfloat xRotate, yRotate, zRotate; //Rotation angles
GLdouble radius = 1, eye;

//Function prototypes
void display(void);
void reshape(int x, int y);
void idle(void);
void render(void);
void triangle(GLfloat a, GLfloat b, GLfloat c);
void sphere(GLfloat radius);

int main(int argc, char** argv) {

    //Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    //Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(500, 500, "Ryan's Sphere", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Make the window's context current
    glfwMakeContextCurrent(window);

    //Initialize GLEW
    glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    //Set background color and enable depth testing
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Wireframe mode to debug

    //Register callbacks
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int width, int height) {
        reshape(width, height);
    });

    //Main loop
    while (!glfwWindowShouldClose(window)) {
        idle();
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Clean up and exit
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render();
}

void reshape(int x, int y) {
    if (y == 0 || x == 0) return;
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)x / (GLfloat)y, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void) {
    xRotate += 0.1;
    yRotate += 0.6;
    zRotate += 0.1;
    if (xRotate > 360) xRotate -= 360;
    if (yRotate > 360) yRotate -= 360;
    if (zRotate > 360) zRotate -= 360;
}

void render(void) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    //Rotate the sphere
    glRotatef(xRotate, 1.0, 0.0, 0.0);
    glRotatef(yRotate, 0.0, 1.0, 0.0);
    glRotatef(zRotate, 0.0, 0.0, 1.0);

    //Set color and draw the sphere
    glColor3f(0.2f, 0.8f, 1.0f);
    sphere(radius);
}

void triangle(GLfloat a, GLfloat b, GLfloat c) {
    //Calculate the vertices of the triangle (spherical coordinates)
    //Convert angles from degrees to radians
    GLfloat a_rad = a * M_PI / 180;
    GLfloat b_rad = b * M_PI / 180;
    GLfloat a_next_rad = (a + 10) * M_PI / 180;
    GLfloat b_next_rad = (b + 10) * M_PI / 180;

    //Calculate the vertices of the triangle
    GLfloat x1 = c * sin(a_rad) * cos(b_rad);
    GLfloat y1 = c * cos(a_rad);
    GLfloat z1 = c * sin(a_rad) * sin(b_rad);

    //Calculate the next vertices for the triangle
    GLfloat x2 = c * sin(a_next_rad) * cos(b_rad);
    GLfloat y2 = c * cos(a_next_rad);
    GLfloat z2 = c * sin(a_next_rad) * sin(b_rad);

    //Calculate the next vertices for the triangle
    GLfloat x3 = c * sin(a_next_rad) * cos(b_next_rad);
    GLfloat y3 = c * cos(a_next_rad);
    GLfloat z3 = c * sin(a_next_rad) * sin(b_next_rad);

    //Calculate the next vertices for the triangle
    GLfloat x4 = c * sin(a_rad) * cos(b_next_rad);
    GLfloat y4 = c * cos(a_rad);
    GLfloat z4 = c * sin(a_rad) * sin(b_next_rad);

    //Draw quad as two triangles
    glBegin(GL_TRIANGLES);
    //First triangle
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);
    //Second triangle
    glVertex3f(x1, y1, z1);
    glVertex3f(x3, y3, z3);
    glVertex3f(x4, y4, z4);
    glEnd();
}

//Function to draw a sphere using triangles
/*
The sphere is drawn by iterating through angles and creating triangles
between the vertices. The angles are incremented by 10 degrees to create 
a smoother sphere. The radius of the sphere is passed as a parameter to 
the function.  
*/
void sphere(GLfloat radius) {
    //Draw the sphere using triangles
    for (GLfloat i = 0; i < 180; i += 10) {
        for (GLfloat j = 0; j < 360; j += 10) {
            triangle(i, j, radius);
        }
    }
}