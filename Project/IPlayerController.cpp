#include "IPlayerController.h"
#include <algorithm>

IPlayerController::IPlayerController()
  : is_impacted_(false)
  , control_delay_(0)
{
}

void IPlayerController::ControllProcess(PlayerInput* dest)
{
  if (this->control_delay_ > 0)
  {
    this->control_delay_--;  
    if (this->control_delay_ == 0)
    {
      this->is_impacted_ = false;
    }
    return;
  }
  this->InputProcess(dest);
}

void IPlayerController::AddControlDelay(T_UINT16 delay)
{
  this->control_delay_ += delay;
}

void IPlayerController::SetControlDelay(T_UINT16 delay)
{
  this->control_delay_ = delay;
}

void IPlayerController::SetControlDelayNegative(T_UINT16 delay)
{
  this->control_delay_ = std::max(this->control_delay_, delay);
}
