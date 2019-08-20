#ifndef TakeItem_INSTR_H
#define TakeItem_INSTR_H

#include "Instruction.h"

class TakeItem : public Instruction {
private:
  float tx, ty;
  Item *item;

public:
  TakeItem(Item *itm, Unit *unt) {
    item = itm;
    unit = unt;
  }
  virtual bool DO(float delta) {
    unit->TakeItem(item);
    return true;
  }
};

#endif
