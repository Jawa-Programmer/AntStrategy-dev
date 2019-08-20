#include "../MathConstants.h"
#include <GL/gl.h>

#ifndef GAMEOBJECT
#define GAMEOBJECT

class GameObject {
protected:
  float x, y, width, height;

public:
  GameObject(float x_, float y_, float w_, float h_) {
    this->x = x_;
    this->y = y_;
    this->width = w_;
    this->height = h_;
  }
  virtual void Draw() = 0;
  inline float getX() { return this->x; }
  inline float getY() { return this->y; }
  inline float getWidth() { return this->width; }
  inline float getHeight() { return this->height; }
};

#endif

#include "Item.h"
#include "PlayerBase.h"
#include "Unit.h"
