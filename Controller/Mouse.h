

enum MOUSE_KEYS { LEFT_KEY, MIDDLE_KEY, RIGHT_KEY };

class Mouse {
private:
  static int X, Y, prevX, prevY;
  static bool IS_LEFT_PRESSED, IS_RIGHT_PRESSED, IS_MIDDLE_PRESSED,
      GRABBED_MODE;
  static void (*mouseDraggedCallback)(int, int);
  static void (*mouseButtonStateChangedCallback)(MOUSE_KEYS, bool);
  static void MouseDragged(int, int);
  static void MouseClicked(int, int, int, int);
 
public:
  static void init();
  static void getPosition(int *, int *);
  static void getDeltaPos(int *, int *);
  static bool getKeyState(MOUSE_KEYS);
  static void SetGrabbed(bool);
  static void SetOnMouseDraggedListener(void (*)(int, int));
  static void SetOnMouseClickListener(void (*)(MOUSE_KEYS, bool));
};
