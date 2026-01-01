#ifndef LIMIT_REACHED_COMMAND_H
#define LIMIT_REACHED_COMMAND_H

#include "belt_limiter.h"

class LimitReachedCommand {
public:
  virtual void execute(LimitSide side) = 0;
  virtual ~LimitReachedCommand() {}
};

#endif
