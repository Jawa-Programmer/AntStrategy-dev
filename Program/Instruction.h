#ifndef INSTRUCTION_H
#define INSTRUCTION_H

enum InstructionStatus{BeforStart, Doing, Finished} ;

class Instruction {
protected:
	InstructionStatus status = BeforStart;
  Unit *unit;
private:
public:
  virtual bool DO(float) = 0;
};

#endif
