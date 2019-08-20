#include <GL/glut.h>
#include <SOIL.h>

#include <iostream>
#include <math.h>
#include <vector>

#include "Controller/Camera.h"
#include "Controller/Keyboard.h"
#include "Controller/Mouse.h"

#include "GameObjects/GameObject.h"

#include "Program/PlayerUnitTakeItemAlg.h"

#include "MathConstants.h"

using std::vector;

int res = 0;

vector<Unit *> UnitsVec = {new Unit(-15, 0),new Unit(15, 0)};
vector<Item *> ItemsVec({new Item(-40, 50), new Item(40, -50),
                         new Item(110, 54)});
PlayerBase *playerBase = new PlayerBase(0, 0);
float pnt[] = {100, 100, 100, -100, -100, -100, -100, 100, 0, 0};

// функция вызыватся в бесконечном цикле, производит отрисовку сцены
void displayFunc();
// подгружает все необходимые текстуры
void LoadTexures();
// производит первичную настройку openGL
void initOpenGL();
// выводит текст в по данным координатам
void drawText(char *, int, int, float);
// производит отрисовку игровой сцены
void DrawScene();
// производит отрсовку интерфейса
void DrawInterface();
// обробатывает нажатия мыши
void MouseClickFunc(MOUSE_KEYS, bool);

GLuint texture;

// расчитывает прошедшее между отрисовками кадров время (что бы устранить
// зависимость скорости игровых объетов от FPS)
float curTime, lastTime, deltaTime;

//размеры окна, нужны для правильного расчета перспективы
int SCR_WIDTH = 500, SCR_HEIGHT = 500, SCR_WIDTH_DIV_2 = 250,
    SCR_HEIGHT_DIV_2 = 250;

int main(int argc, char *argv[]) {

  srand(static_cast<unsigned int>(time(0)));
  /*  for (int i = 0; i < 3; i++) {
      std::cout << sin(i * PI2 / 3) * 10 << "\t" << cos(i * PI2 / 3) * 10 <<
    "\n";
    }*/
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL);
  glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
  glutInitWindowPosition(20, 20);

  glutCreateWindow("Ant Colony");

  Mouse::init();
  Mouse::SetOnMouseClickListener(MouseClickFunc);
  // Keyboard::ChangeStateListener(KeyboardChangeFunc);
  // Keyboard::init();

  initOpenGL();

  // LoadTextures();

  glutIdleFunc(displayFunc);
  glutMainLoop();

  return 0;
}

void displayFunc() {
  // расчет прошедшего между кадрами времени
  curTime = glutGet(GLUT_ELAPSED_TIME);
  deltaTime = (curTime - lastTime) / 1000;
  lastTime = curTime;

  // получение текущего размера экрана
  SCR_WIDTH = glutGet(GLUT_WINDOW_WIDTH);
  SCR_HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);
  SCR_WIDTH_DIV_2 = SCR_WIDTH / 2;
  SCR_HEIGHT_DIV_2 = SCR_HEIGHT / 2;

  // Настройка рабочего пространства под размеры окна и позицию камеры
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(Camera::X - SCR_WIDTH_DIV_2, SCR_WIDTH_DIV_2 + Camera::X,
          SCR_HEIGHT_DIV_2 + Camera::Y, Camera::Y - SCR_HEIGHT_DIV_2, 10, -10);
  glMatrixMode(GL_MODELVIEW);

  // закраска фона
  glClearColor(0.1f, 0.7f, 0.2f, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  DrawScene();

  glutSwapBuffers();
}
void initOpenGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, SCR_WIDTH, SCR_WIDTH, 0, 10, -10);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void LoadTexures() {
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  int width, height;
  unsigned char *image =
      SOIL_load_image("/home/pi/openGL/SpaceTest/texturestextures.png", &width,
                      &height, 0, SOIL_LOAD_RGBA);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image);
  SOIL_free_image_data(image);
}

void drawText(char *str, int x, int y, float z = 0.01) {
  glColor3f(1, 1, 1);
  int i = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '\t') {
      glRasterPos3f(x + i * 9 * 4, y, z);
      continue;
    }
    glRasterPos3f(x + i * 9, y + 15, z);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str[i]);
  }
}

char *buf = new char[20];
void MouseClickFunc(MOUSE_KEYS key, bool state) {
  if (state && key == LEFT_KEY) {
    int x_, y_;
    Mouse::getPosition(&x_, &y_);
    x_ -= Camera::X;
    x_ -= SCR_WIDTH_DIV_2;
    y_ -= Camera::Y;
    y_ -= SCR_HEIGHT_DIV_2;
    ItemsVec.insert(ItemsVec.end()--, new Item(x_, y_));
  }
}
void DrawScene() {
  glLoadIdentity();
  for (auto i = UnitsVec.begin(); i < UnitsVec.end(); ++i) {
    if ((*i)->IsFree() && ItemsVec.size() > 0) {
      (*i)->setTask(
          new PlayerUnitTakeItemAlg(ItemsVec[0], &ItemsVec, &res, *i));
    }
    (*i)->DOING(deltaTime);
    (*i)->Draw();
  }
  for (auto i = ItemsVec.begin(); i < ItemsVec.end(); ++i) {
    (*i)->Draw();
  }
  playerBase->Draw();

  sprintf(buf, "resourses: %d", res);
  drawText(buf, Camera::X - SCR_WIDTH_DIV_2, Camera::Y - SCR_HEIGHT_DIV_2 + 10,
           0);
}
