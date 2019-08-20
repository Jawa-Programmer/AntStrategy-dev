#include "Mouse.h"
#include <GL/glut.h>
#include <math.h>

int Mouse::X = 0, Mouse::Y = 0, Mouse::prevX = 0, Mouse::prevY = 0;

bool Mouse::IS_LEFT_PRESSED = false, Mouse::IS_MIDDLE_PRESSED = false,
     Mouse::IS_RIGHT_PRESSED = false, Mouse::GRABBED_MODE = false;

void (*Mouse::mouseDraggedCallback)(int, int) = nullptr;
void (*Mouse::mouseButtonStateChangedCallback)(MOUSE_KEYS, bool) = nullptr;

bool Mouse::getKeyState(MOUSE_KEYS key) {
  switch (key) {
  case LEFT_KEY:
    return IS_LEFT_PRESSED;
  case RIGHT_KEY:
    return IS_RIGHT_PRESSED;
  case MIDDLE_KEY:
    return IS_MIDDLE_PRESSED;
  }
}

void Mouse::getPosition(int *x, int *y) {
  *x = X;
  *y = Y;
}

void Mouse::getDeltaPos(int *dx, int *dy) {
  *dx = X - prevX;
  *dy = Y - prevY;
}

void Mouse::MouseDragged(int x, int y) {
  prevX = X;
  prevY = Y;
  X = x;
  Y = y;
  if (GRABBED_MODE) {
    if (mouseDraggedCallback != nullptr)
      mouseDraggedCallback(X - prevX, Y - prevY);
    if (abs(X - prevX) > 0 || abs(Y - prevY) > 0)
      glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2,
                      glutGet(GLUT_WINDOW_HEIGHT) / 2);
  } else if (mouseDraggedCallback != nullptr)
    mouseDraggedCallback(X, Y);
}
void Mouse::MouseClicked(int but, int state, int x, int y) {
  switch (but) {
  case GLUT_LEFT_BUTTON:
    IS_LEFT_PRESSED = state == 0;
    if (mouseButtonStateChangedCallback != nullptr)
      mouseButtonStateChangedCallback(LEFT_KEY, state == 0);
    return;
  case GLUT_RIGHT_BUTTON:
    IS_RIGHT_PRESSED = state > 0;
    if (mouseButtonStateChangedCallback != nullptr)
      mouseButtonStateChangedCallback(RIGHT_KEY, state == 0);
    return;
  case GLUT_MIDDLE_BUTTON:
    IS_MIDDLE_PRESSED = state > 0;
    if (mouseButtonStateChangedCallback != nullptr)
      mouseButtonStateChangedCallback(MIDDLE_KEY, state == 0);
    return;
  }
}
void Mouse::SetGrabbed(bool isGrbd) {
  GRABBED_MODE = isGrbd;
  if (isGrbd) {
    glutSetCursor(GLUT_CURSOR_NONE);
  } else {
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
  }
}

void Mouse::SetOnMouseDraggedListener(void (*callback)(int, int)) {
  mouseDraggedCallback = callback;
}
void Mouse::SetOnMouseClickListener(void (*callback)(MOUSE_KEYS, bool)) {
  mouseButtonStateChangedCallback = callback;
}

void Mouse::init() {
  glutPassiveMotionFunc(MouseDragged);
  glutMotionFunc(MouseDragged);
  glutMouseFunc(MouseClicked);
}
