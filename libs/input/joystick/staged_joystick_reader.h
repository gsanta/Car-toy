#include "./joystick_command_handler.h"
#include "./joystick.h"

class StagedJoystickReader : public JoystickCommandHandler {
public:
  StagedJoystickReader(int stages, Joystick& joystick) : stages(stages), joystick(joystick) {}
  
  void handleMove(int xVal, int yVal) override;

  virtual void handleStagedMove(int xStage, int yStage) = 0;

  const Joystick& getJoystick() {
    return joystick;
  }

private:
  int calculateStage(int value, int minVal, int maxVal) const;

  int stages;

  Joystick& joystick;
};