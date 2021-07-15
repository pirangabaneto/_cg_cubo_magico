#include <C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\VS\gl\glut.h>
#include <vector>
#include <iostream>
#include <cstdlib> //para o numero aleatorio

using namespace std;

struct rotacionar_cubo {

    GLfloat angulo, x, y, z;

};

GLfloat angulo, fAspect, tamanho_cubo;
GLint girar_y, girar_x, crement, x_0, x_k, y_0, y_k, z_0, z_k , espacamento;
vector<rotacionar_cubo> peca_cubo[3][3][3];

const char direcoes[2] = { 'q', 'e'};
char str_aleatorio;
int num_aleatorio;

void load_visualization_parameters(void);

void aplicar_rotacao(GLfloat angulo) {

    vector<rotacionar_cubo> face[3][3];
    int index;
    rotacionar_cubo rotacao;

    // copia as modificacoes das faces
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            index = 2 - j % 3;

            if (x_0 == x_k) {
                rotacao = { angulo, 1.0, 0.0, 0.0 };
                face[index][i] = peca_cubo[x_k][i][j];
            }

            if (y_0 == y_k) {
                rotacao = { angulo, 0.0, 1.0, 0.0 };
                face[index][i] = peca_cubo[j][y_k][i];
            }

            if (z_0 == z_k) {
                rotacao = {  angulo, 0.0, 0.0, 1.0 };
                face[index][i] = peca_cubo[j][i][z_k];
            }
            
            // Adiciona a face copiada ao vetor - o qual funciona como uma memoria (append)
            face[index][i].push_back(rotacao);

        }

    // modifica o cubo com as faces copiada
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            if (x_0 == x_k)
                peca_cubo[x_k][i][j] = face[i][j];

            if (y_0 == y_k)
                peca_cubo[j][y_k][i] = face[i][j];

            if (z_0 == z_k)
                peca_cubo[j][i][z_k] = face[i][j];
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

void fazer_cubo(int x, int y, int z)
{

    vector<rotacionar_cubo> lrot = peca_cubo[x][y][z];

    //armazena as transformacoes na pilha interna do opengl 
    glPushMatrix();

    // multiplica a matriz atual por uma matriz de translacao
    glTranslatef((x - 1) * tamanho_cubo + x * espacamento, (y - 1) * tamanho_cubo + y * espacamento, (z - 1) * tamanho_cubo + z * espacamento);
    
    // rotaciona o cubo 
    for (int i = lrot.size() - 1; i >= 0; --i)
        glRotatef(lrot[i].angulo, lrot[i].x, lrot[i].y, lrot[i].z);
    
    // definindo as cores e as posicoes dos quadrilateros

    glColor3f(1.0f, 0.0f, 0.0f); //vermelho
    glBegin(GL_QUADS);  // define que vai ser um quadrilatero
    glNormal3f(0.0, 0.0, 1.0);  // frente
    // vertices do quadrilatero
        glVertex3f(tamanho_cubo / 2, tamanho_cubo / 2, tamanho_cubo / 2);
        glVertex3f(-tamanho_cubo / 2, tamanho_cubo / 2, tamanho_cubo / 2);
        glVertex3f(-tamanho_cubo / 2, -tamanho_cubo / 2, tamanho_cubo / 2);
        glVertex3f(tamanho_cubo / 2, -tamanho_cubo / 2, tamanho_cubo / 2);
    glEnd();
    
    glColor3f(0.87f, 0.4f, 0.07f); // laranja
    glBegin(GL_QUADS);  // tras
    glNormal3f(0.0, 0.0, -1.0);  // face normal
        glVertex3f(tamanho_cubo / 2, tamanho_cubo / 2, -tamanho_cubo / 2);
        glVertex3f(tamanho_cubo / 2, -tamanho_cubo / 2, -tamanho_cubo / 2);
        glVertex3f(-tamanho_cubo / 2, -tamanho_cubo / 2, -tamanho_cubo / 2);
        glVertex3f(-tamanho_cubo / 2, tamanho_cubo / 2, -tamanho_cubo / 2);
    glEnd();
    
    glColor3f(0.0f, 0.0f, 1.0f); // azul
    glBegin(GL_QUADS);  // esquerda
    glNormal3f(-1.0, 0.0, 0.0);  // face normal
        glVertex3f(-tamanho_cubo / 2, tamanho_cubo / 2, tamanho_cubo / 2);
        glVertex3f(-tamanho_cubo / 2, tamanho_cubo / 2, -tamanho_cubo / 2);
        glVertex3f(-tamanho_cubo / 2, -tamanho_cubo / 2, -tamanho_cubo / 2);
        glVertex3f(-tamanho_cubo / 2, -tamanho_cubo / 2, tamanho_cubo / 2);
    glEnd();
    
    glColor3f(1.0f, 1.0f, 1.0f); // branco
    glBegin(GL_QUADS);  // direita
    glNormal3f(1.0, 0.0, 0.0);  // face normal
        glVertex3f(tamanho_cubo / 2, tamanho_cubo / 2, tamanho_cubo / 2);
        glVertex3f(tamanho_cubo / 2, -tamanho_cubo / 2, tamanho_cubo / 2);
        glVertex3f(tamanho_cubo / 2, -tamanho_cubo / 2, -tamanho_cubo / 2);
        glVertex3f(tamanho_cubo / 2, tamanho_cubo / 2, -tamanho_cubo / 2);
    glEnd();
    
    glColor3f(1, 0.964, 0); // amarelo
    glBegin(GL_QUADS);  // topo
    glNormal3f(0.0, 1.0, 0.0);  // face normal
        glVertex3f(-tamanho_cubo / 2, tamanho_cubo / 2, -tamanho_cubo / 2);
        glVertex3f(-tamanho_cubo / 2, tamanho_cubo / 2, tamanho_cubo / 2);
        glVertex3f(tamanho_cubo / 2, tamanho_cubo / 2, tamanho_cubo / 2);
        glVertex3f(tamanho_cubo / 2, tamanho_cubo / 2, -tamanho_cubo / 2);
    glEnd();
    
    glColor3f(0.0f, 1.0f, 0.0f); // verde
    glBegin(GL_QUADS);  // base
    glNormal3f(0.0, -1.0, 0.0);  // face normal
        glVertex3f(-tamanho_cubo / 2, -tamanho_cubo / 2, -tamanho_cubo / 2);
        glVertex3f(tamanho_cubo / 2, -tamanho_cubo / 2, -tamanho_cubo / 2);
        glVertex3f(tamanho_cubo / 2, -tamanho_cubo / 2, tamanho_cubo / 2);
        glVertex3f(-tamanho_cubo / 2, -tamanho_cubo / 2, tamanho_cubo / 2);
    glEnd();
    // restaura as transformacoes anteriores da pilha interna do opengl
    glPopMatrix();

}

void construir_cena(void)
{

    int x = tamanho_cubo, y = tamanho_cubo, z = tamanho_cubo;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // reseta as transformacoes
    glLoadIdentity();

    // seta a posicao da camera
    set_camera();

    // aplica a transformacao da visualizacao
    glRotatef(girar_y, 1.0, 0.0, 0.0);
    glRotatef(girar_x, 0.0, 1.0, 0.0);
    
    for (int i = 0; i < 3; ++i) // eixo x
        for (int j = 0; j < 3; ++j) // eixo y
            for (int k = 0; k < 3; ++k) {// eixo z

          // desenha um cubinho
                fazer_cubo(i, j, k);

            }
     
    glutSwapBuffers();

}

// renderizando os parametros
void func_iniciar(void)
{

    tamanho_cubo = 20.0;
    girar_y = 0.0;
    girar_x = 0.0;
    crement = 5; // rotacao (incremento e decremento)
    espacamento = 2;

    GLfloat ambient_lighte[4] = { 0.19,0.0123,0,1.0 };
    GLfloat diffuse_light[4] = { 0.5,0.7,0.7,1.0 };		// cor
    GLfloat specular_light[4] = { 0.952, 0.631, 0.247, 1.0 };	// brilho
    GLfloat light_position[4] = { 1.0, 50.0, 50.0, 1.0 };

    // brilho do material
    GLfloat specularity[4] = { 0.03,0.0123,0.8,1.0 };
    GLint material_specularity = 60;

    // cor de fundo
    glClearColor(0.35f, 0.75f, 0.8f, 1.0f);
    glShadeModel(GL_SMOOTH);

    // flexibilidade do 
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularity);
    // concentracao do brilho
    glMateriali(GL_FRONT, GL_SHININESS, material_specularity);

    // ativar bilho do ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_lighte);

    // definindo parametros de luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_lighte);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // mudar cor do material
    glEnable(GL_COLOR_MATERIAL);
    // luz
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // buffer de profundidade
    glEnable(GL_DEPTH_TEST);

    // tamanho do cubo (ver direitinho)
    angulo = 55;

}

// carregar janela
void load_visualization_parameters(void)
{
    //  sistema de coordenadas 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //projecao da perspectiva
    gluPerspective(angulo, fAspect, 0.4, 500);

    // inicial sistema de coordenadad
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    set_camera();
}

// window reshape callback
void remodelar(GLsizei w, GLsizei h)
{

    // aspect ratio
    fAspect = (GLfloat)w / (GLfloat)h;

    load_visualization_parameters();
} // reshape function

// keyboard function callback
void keyboard_func(unsigned char key, int x, int y)
{

    switch (key) {
    case 'A': // esquerda
    case 'a':
        girar_x = (girar_x - crement) % 360;
        break;

    case 'D': // direita
    case 'd':
        girar_x = (girar_x + crement) % 360;
        break;

    case 'S': // baixo
    case 's':
        girar_y = (girar_y + crement) % 360;
        break;

    case 'W': // cima
    case 'w':
        girar_y = (girar_y - crement) % 360;
        break;
    

        // movimentar o cubo

        // seleciona a face do cubo
        // faces - eixo x
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

        // faces - eixo y
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

        // faces - eixo z
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
        aplicar_rotacao(-90);
        break;

    case 'E': // sentido horario
    case 'e':
        aplicar_rotacao(90);
        break;

        // end of cube movements
    
        //embaralhar o cubo
    //case 'P':
    //case 'p':
        //definindo o aleatorio
      
        //num_aleatorio = (rand() % 9) + 1;
        //str_aleatorio = direcoes[rand() % 2];
        //num_aleatorio = (rand() % 9)+1;
        //cout << direcoes[rand() % 2];
        //cout << num_aleatorio;
        //cout << "\n";
        // seta a parte que vai rotacionar
        //keyboard_func(static_cast<char>(num_aleatorio), 0, 0);
        //rotaciona chamando a direcao
        //keyboard_func(str_aleatorio, 0, 0);
       // break;
    default:
        break;

    }

    glutPostRedisplay();

}

int main(int argc, char** argv)
{
    srand((unsigned)time(0)); //inicializa a aleatoriedade da geracao
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(350, 100);
    glutCreateWindow("Cubo Mágico"); // titulo da pagina
    glutDisplayFunc(construir_cena); 
    glutReshapeFunc(remodelar);
    glutKeyboardFunc(keyboard_func);
    func_iniciar();
    glutMainLoop();
} // main
