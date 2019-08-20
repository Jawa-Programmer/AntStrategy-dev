#ifndef UNIT_H

#include "../MathConstants.h"
#include "../Program/Algorithm.h"
#include "Item.h"
#include <math.h>

#define UNIT_H
class Unit : public GameObject {
private:
  static const int r;
  static const float max_speed, accelerate;
  Item *tookedItem = nullptr;
  float speed = 0;
  int targetX = 0, targetY = 0;
  bool isFree = true;
  Algorithm *Task = nullptr;

public:
  Unit(float x_, float y_) : GameObject(x_, y_, 20, 20) {
    targetX = x_;
    targetY = y_;
  }
  inline float getSpeed() { return speed; }
  virtual void Draw() {
    glTranslatef(x, y, 0);
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);

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

    if (tookedItem != nullptr) {
      glLineWidth(5);
      glColor3f(0.2f, 0.2f, 0.2f);
      glBegin(GL_LINES);
      glVertex2f(x, y);
      glVertex2f(tookedItem->getX(), tookedItem->getY());
      glEnd();
    }
  }
  void setTarget(int tx, int ty) {
    targetX = tx;
    targetY = ty;
  }
  virtual void Move(float Delta) {
    if (targetX == x && targetY == y) {
      speed = 0;
      return;
    }
    float tx = targetX - x, ty = targetY - y, ln = hypot(tx, ty);
    if (ln * accelerate / (2 * speed * speed) <= 1) {
      speed -= accelerate * Delta;
    } else if (speed < max_speed) {
      speed += accelerate * Delta;
    } else if (speed > max_speed) {
      speed = max_speed;
    } else if (speed < 0) {
      speed = 0;
    }
    if (ln <= speed * Delta) {
      x = targetX;
      y = targetY;
      return;
    }
    float px = x, py = y;
    x += tx * speed * Delta / ln;
    y += ty * speed * Delta / ln;
    if (tookedItem != nullptr) {
      tookedItem->Move(x, y, Delta);
    }
  }
  bool TakeItem(Item *totake) {
    if (totake == nullptr ||
        hypot(totake->getX() - x, totake->getY() - y) <= 30) {
      tookedItem = totake;
      return true;
    }
    return false;
  }
  void DOING(float delta) {
    if (Task != nullptr && Task->TODO(delta)) {
      delete Task;
      Task = nullptr;
      isFree = true;
    }
  }
  void setTask(Algorithm *Task_) {
    Task = Task_;
    isFree = false;
  }
  inline bool IsFree() { return isFree; }
};
const int Unit::r = 10;
const float Unit::max_speed = 30, Unit::accelerate = 20;
#endif
