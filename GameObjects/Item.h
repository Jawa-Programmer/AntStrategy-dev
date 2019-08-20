#ifndef ITEM_H
#define ITEM_H

#include "../MathConstants.h"

class Item : public GameObject {
private:
protected:
  static const float K, MIN_DIST;

public:
  Item(float x_, float y_) : GameObject(x_, y_, 20, 20) {}
  virtual void Draw() {
    glTranslatef(x, y, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.1f, 0.9f);

    glVertex2f(0.0f, 10.0f);
    glVertex2f(8.66025f, -5.0f);
    glVertex2f(-8.66025f, -5.0f);

    glEnd();
    glTranslatef(-x, -y, 0);
  }
  void Move(float tx, float ty, float deltaTime) {
    float dx = tx - x, dy = ty - y, ln = hypot(dx, dy);
    if (ln > MIN_DIST) {
      x += dx / ln * K * (ln - MIN_DIST) * deltaTime;
      y += dy / ln * K * (ln - MIN_DIST) * deltaTime;
    }
  }
};
const float Item::K = 1.0f, Item::MIN_DIST = 12.0f;
#endif
