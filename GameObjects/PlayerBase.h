#ifndef PLAYERBASE
#define PLAYERBASE

#include "../MathConstants.h"

class PlayerBase : public GameObject {
private:
  static const int r;

public:
  PlayerBase(float x_, float y_) : GameObject(x_, y_, 100, 100) {}
  virtual void Draw() {
    glTranslatef(x, y, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.8f, 0.3f);

    glVertex2f(0 * r, 1 * r);
    glVertex2f(0.587785f * r, 0.809017f * r);
    glVertex2f(0.951057f * r, 0.309017f * r);
    glVertex2f(0.951057f * r, -0.309017f * r);
    glVertex2f(0.587785f * r, -0.809017f * r);
    glVertex2f(0 * r, -1 * r);
    glVertex2f(-0.587785f * r, -0.809017f * r);
    glVertex2f(-0.951057f * r, -0.309017f * r);
    glVertex2f(-0.951057f * r, 0.309017f * r);
    glVertex2f(-0.587785f * r, 0.809017f * r);

    glEnd();
    glTranslatef(-x, -y, 0);
  }
};
const int PlayerBase::r = 50;
#endif
