// Rubik Cube in OpenGL

#include <C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\VS\gl\glut.h>
#include <vector>
#include <iostream>

using namespace std;

struct cube_rotate {

    GLfloat angle, x, y, z;

};

GLfloat angle, fAspect, cube_size;
GLint rot_x, rot_y, crement, x_0, x_k, y_0, y_k, z_0, z_k , gap;//, gap_crement;
//cube_rotate cube_rotations[3][3][3];
vector<cube_rotate> cube_rotations[3][3][3];

void load_visualization_parameters(void);

void apply_rotation(GLfloat angle) {

    vector<cube_rotate> face[3][3];
    int index;
    cube_rotate rotation;

    // copy face to be rotated
    // apply rotation to face
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {

            index = 2 - j % 3;

            if (x_0 == x_k) {
                rotation = { angle, 1.0, 0.0, 0.0 };
                face[index][i] = cube_rotations[x_k][i][j];
            }

            if (y_0 == y_k) {
                rotation = { angle, 0.0, 1.0, 0.0 };
                face[index][i] = cube_rotations[j][y_k][i];
            }

            if (z_0 == z_k) {
                rotation = { -1 * angle, 0.0, 0.0, 1.0 };
                face[index][i] = cube_rotations[j][i][z_k];
            }

            face[index][i].push_back(rotation);

        }

    // copy back rotated face
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {

            if (x_0 == x_k)
                cube_rotations[x_k][i][j] = face[i][j];

            if (y_0 == y_k)
                cube_rotations[j][y_k][i] = face[i][j];

            if (z_0 == z_k)
                cube_rotations[j][i][z_k] = face[i][j];
        }

}

// reset face selection parameters
void reset_selected_face() {

    x_0 = 0;
    x_k = 2;
    y_0 = 0;
    y_k = 2;
    z_0 = 0;
    z_k = 2;

}

void set_camera()
{
    //posicao da camera
    gluLookAt(0, 80, 200, 0, 0, 0, 0, 1, 0);

}

// draw a cube
void draw_cube(int x, int y, int z)
{

    vector<cube_rotate> lrot = cube_rotations[x][y][z];

    //armazena as transformacoes na pilha interna do opengl 
    glPushMatrix();

    // translate to final position
    glTranslatef((x - 1) * cube_size + x * gap, (y - 1) * cube_size + y * gap, (z - 1) * cube_size + z * gap);
    //cout << cube_size;
    // rotate cube to correct position
    for (int i = lrot.size() - 1; i >= 0; --i)
        glRotatef(lrot[i].angle, lrot[i].x, lrot[i].y, lrot[i].z);
    //cout << "Hello World!\n";
    
    // definindo as cores e as posicoes dos quadrilateros

    glColor3f(1.0f, 0.0f, 0.0f); //vermelho
    glBegin(GL_QUADS);  // define que vai ser um quadrilatero
    glNormal3f(0.0, 0.0, 1.0);  // frente
    // vertices do quadrilatero
        glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
        glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
        glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
    glEnd();
    
    glColor3f(0.0f, 1.0f, 0.0f); // verde
    //glColor3f(0.2f, 0.7f, 1);
    glBegin(GL_QUADS);  // tras
    glNormal3f(0.0, 0.0, -1.0);  // face normal
        glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
        glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
    glEnd();
    
    glColor3f(0.0f, 0.0f, 1.0f); // azul
    glBegin(GL_QUADS);  // esquerda
    glNormal3f(-1.0, 0.0, 0.0);  // face normal
        glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
        glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
    glEnd();
    
    glColor3f(1.0f, 1.0f, 1.0f); // branco
    glBegin(GL_QUADS);  // direita
    glNormal3f(1.0, 0.0, 0.0);  // face normal
        glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
    glEnd();
    
    glColor3f(1.0f, 0.3f, 0.5f); // rosa
    glBegin(GL_QUADS);  // topo
    glNormal3f(0.0, 1.0, 0.0);  // face normal
        glVertex3f(-cube_size / 2, cube_size / 2, -cube_size / 2);
        glVertex3f(-cube_size / 2, cube_size / 2, cube_size / 2);
        glVertex3f(cube_size / 2, cube_size / 2, cube_size / 2);
        glVertex3f(cube_size / 2, cube_size / 2, -cube_size / 2);
    glEnd();
    
    glColor3f(0.5f, 0.4f, 0.7f); // roxo
    glBegin(GL_QUADS);  // base
    glNormal3f(0.0, -1.0, 0.0);  // face normal
        glVertex3f(-cube_size / 2, -cube_size / 2, -cube_size / 2);
        glVertex3f(cube_size / 2, -cube_size / 2, -cube_size / 2);
        glVertex3f(cube_size / 2, -cube_size / 2, cube_size / 2);
        glVertex3f(-cube_size / 2, -cube_size / 2, cube_size / 2);
    glEnd();
    /**/
    // restaura as transformacoes anteriores da pilha interna do opengl
    glPopMatrix();

} // draw cube function

// construir cena
void draw_func(void)
{

    int x = cube_size, y = cube_size, z = cube_size;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // reset transformations
    glLoadIdentity();

    // set camera position
    set_camera();

    // apply visualization transformations
    glRotatef(rot_x, 1.0, 0.0, 0.0); // rotate in y axis
    glRotatef(rot_y, 0.0, 1.0, 0.0); // rotate in x axis
    //draw_cube(1, 1, 1);
    
    for (int i = 0; i < 3; ++i) // step through x axis
        for (int j = 0; j < 3; ++j) // step through y axis
            for (int k = 0; k < 3; ++k) { // step through z axis

          // draw a single cube
                draw_cube(i, j, k);

            }
     
    //cout << "--------------------\n";
    // flush opengl commands
    glutSwapBuffers();

}

// init rendering parameters
void init_func(void)
{

    // init parameters
    cube_size = 20.0; // cuboid size
    rot_x = 0.0; // view rotation x
    rot_y = 0.0; // view rotation y
    crement = 5; // rotation (in/de)crement
    gap = 2;

    // cor de fundo
    glClearColor(1.0f, 0.8f, 0.2f, 1.0f);
    
    glEnable(GL_DEPTH_TEST);

    // tamanho do cubo (ver direitinho)
    angle = 55;

} // init

// specify what's shown in the window
void load_visualization_parameters(void)
{
    // specify projection coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // specify projection perspective
    gluPerspective(angle, fAspect, 0.4, 500);

    // init model coordinate system
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // specify observer and target positions
    set_camera();
} // load visualization parameters

// window reshape callback
void reshape_func(GLsizei w, GLsizei h)
{
    // prevents division by zero
    //if (h == 0) h = 1;

    // viewport size
    glViewport(0, 0, w, h);

    // aspect ratio
    fAspect = (GLfloat)w / (GLfloat)h;

    load_visualization_parameters();
} // reshape function

// keyboard function callback
void keyboard_func(unsigned char key, int x, int y)
{

    switch (key) {
    case 'D': // direita
    case 'd':
        rot_y = (rot_y - crement) % 360;
        break;

    case 'A': // esquerda
    case 'a':
        rot_y = (rot_y + crement) % 360;
        break;

    case 'W': // baixo
    case 'w':
        rot_x = (rot_x + crement) % 360;
        break;

    case 'S': // cima
    case 's':
        rot_x = (rot_x - crement) % 360;
        break;
    

        // movimentar o cubo

        // select cube face
        // x-axis faces
    case '1':
        reset_selected_face();
        x_0 = 0;
        x_k = 0;
        break;

    case '2':
        reset_selected_face();
        x_0 = 1;
        x_k = 1;
        break;

    case '3':
        reset_selected_face();
        x_0 = 2;
        x_k = 2;
        break;

        // y-axis faces
    case '4':
        reset_selected_face();
        y_0 = 0;
        y_k = 0;
        break;

    case '5':
        reset_selected_face();
        y_0 = 1;
        y_k = 1;
        break;

    case '6':
        reset_selected_face();
        y_0 = 2;
        y_k = 2;
        break;

        // z-axis faces
    case '7':
        reset_selected_face();
        z_0 = 0;
        z_k = 0;
        break;

    case '8':
        reset_selected_face();
        z_0 = 1;
        z_k = 1;
        break;

    case '9':
        reset_selected_face();
        z_0 = 2;
        z_k = 2;
        break;

        // move selected face
    case 'Q': // sentido antihorario
    case 'q':
        apply_rotation(-90);
        break;

    case 'E': // sentido horario
    case 'e':
        apply_rotation(90);
        break;

        // end of cube movements

    default:
        break;

    }

    glutPostRedisplay();

}

// mouse function callback
void mouse_func(int button, int state, int x, int y)
{/*
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN) {  // Zoom-in
            if (angle >= 10) angle -= 5;
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) {  // Zoom-out
            if (angle <= 130) angle += 5;
        }
    load_visualization_parameters();
    glutPostRedisplay();*/
} // mouse function


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(350, 100);
    glutCreateWindow("Cubo Mágico"); // titulo da pagina
    glutDisplayFunc(draw_func); 
    glutReshapeFunc(reshape_func);
    glutMouseFunc(mouse_func);
    glutKeyboardFunc(keyboard_func);
    init_func();
    glutMainLoop();
} // main
