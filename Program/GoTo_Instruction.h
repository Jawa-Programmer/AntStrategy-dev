#ifndef GOTO_INSTR_H
#define GOTO_INSTR_H

#include "Instruction.h"

class GoTo_Instruction : public Instruction {
private:
  int tx, ty;

public:
  GoTo_Instruction(int x_, int y_, Unit *unt) {
    tx = x_;
    ty = y_;
    unit = unt;
  }
  virtual bool DO(float delta) {
    switch (status) {
    case Finished:
      return true;
    case BeforStart:
      unit->setTarget(tx, ty);
      status = Doing;
      return false;
    case Doing:
      unit->Move(delta);
      if (unit->getX() == tx && unit->getY() == ty)
        status = Finished;
      return false;
    }
  }
};

#endif
