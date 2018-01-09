#include "PlayerEntry.h"

PlayerEntry::PlayerEntry(const PlayerEntryDataModel& model, IPlayerController* controller, IPlayerCamera* camera)
  : id(model.GetId())
  , animal_data(model.GetAnimalData())
  , handicap(model.GetHandicap())
  , controller(controller)
  , camera(camera)
{}

PlayerEntry::PlayerEntry(T_UINT8 id, const AnimalData& animal_data, T_UINT8 handicap, IPlayerController* controller, IPlayerCamera* camera)
  : id(id)
  , animal_data(animal_data)
  , handicap(handicap)
  , controller(controller)
  , camera(camera)
{}

PlayerEntry::~PlayerEntry()
{
  delete this->controller;
  delete this->camera;
}
