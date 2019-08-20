#ifndef GoToPointsAlg_H
#define GoToPointsAlg_H
#include "Algorithm.h"
#include "GoTo_Instruction.h"
#include "Instruction.h"
class GoToPointsAlg : public Algorithm {
private:
  Instruction *(*instr);
  int Cur = 0;
  int PointCount = 0;

public:
  GoToPointsAlg(float *arr, int count, Unit *unt) : Algorithm(unt) {
    instr = new Instruction *[count];
    PointCount = count;
    for (int i = 0; i < count; i++) {
      instr[i] = new GoTo_Instruction(arr[i * 2], arr[i * 2 + 1], unt);
    }
  }
  ~GoToPointsAlg() {
    for (int i = 0; i < PointCount; i++) {
      delete instr[i];
    }
    delete[] instr;
  }
  virtual bool TODO(float delta) {
    if (Cur < PointCount && instr[Cur]->DO(delta))
      Cur++;
    if (Cur >= PointCount)
      return true;
    return false;
  }
};
#endif
