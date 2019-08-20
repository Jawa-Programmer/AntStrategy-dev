#ifndef PlayerUnitTakeItemAlg_H
#define PlayerUnitTakeItemAlg_H
#include "../MathConstants.h"
#include "Algorithm.h"
#include "GoTo_Instruction.h"
#include "Instruction.h"
#include "TakeItemInstruction.h"
#include <vector>
class PlayerUnitTakeItemAlg : public Algorithm {
private:
  Instruction *(*instr);
  int Cur = 0;
  int PointCount = 0;
  int *res;
  Item *item;
  std::vector<Item *> *vectr;

public:
  PlayerUnitTakeItemAlg(Item *itm, std::vector<Item *> *vec, int *res_,
                        Unit *unt)
      : Algorithm(unt) {
    item = itm;
    vectr = vec;
    res = res_;
    instr = new Instruction *[3];
    PointCount = 3;
    float a = randomRange<float>(0, PI2);
    instr[0] = new GoTo_Instruction(itm->getX() + (20 * sin(a)),
                                    itm->getY() + (20 * cos(a)), unt);
    instr[1] = new TakeItem(itm, unt);
    instr[2] = new GoTo_Instruction(0, 0, unt);
  }
  ~PlayerUnitTakeItemAlg() {
    for (int i = 0; i < PointCount; i++) {
      delete instr[i];
    }
    delete[] instr;
  }
  virtual bool TODO(float delta) {
    if (Cur < PointCount && instr[Cur]->DO(delta)) {
      Cur++;
    }
    if (Cur >= PointCount) {
      if (item != nullptr) {
        auto todel = vectr->begin();
        for (; todel != vectr->end(); ++todel) {
          if (*todel == item) {
            break;
          }
        }
        if (todel != vectr->end()) {
          (*vectr).erase(todel);
          delete item;
          item = nullptr;
          unit->TakeItem(nullptr);
          (*res)++;
        }
      }
      return true;
    }
    return false;
  }
};
#endif
