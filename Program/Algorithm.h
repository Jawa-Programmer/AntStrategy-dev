#ifndef ALGORITHM_H
#define ALGORITHM_H
#ifndef UNIT_H
class Unit;
#endif
class Algorithm {
protected:
  Unit *unit;

private:
public:
  Algorithm(Unit *unt) { unit = unt; }
  virtual bool TODO(float) = 0;
};
#endif
