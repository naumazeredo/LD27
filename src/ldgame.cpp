#include "SDL2/SDL.h"
#include "render/camera.h"
#include "ldgame.h"
#include "person.h"
#include "door.h"
#include "room.h"

LDGame::~LDGame()
{
  for (auto& it : room_)
    if (it != nullptr)
      delete it;
  room_.clear();

  for (auto& it : door_)
    if (it != nullptr)
      delete it;
  door_.clear();

  for (auto& it : npc_)
    if (it.second != nullptr)
      delete it.second;
  npc_.clear();
}

bool LDGame::HandleInputs()
{
  const Uint8* keystate = SDL_GetKeyboardState(nullptr);

  if (keystate[SDL_SCANCODE_RIGHT] && !keystate[SDL_SCANCODE_LEFT]) move_player_ = MOVE_RIGHT;
  else if (!keystate[SDL_SCANCODE_RIGHT] && keystate[SDL_SCANCODE_LEFT]) move_player_ = MOVE_LEFT;
  else move_player_ = MOVE_NOWHERE;

  // Basic Inputs
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT )
      return true;

    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_F4 && (event.key.keysym.mod & KMOD_LALT))
        return true;

      // Enter doors
      if (event.key.keysym.sym == SDLK_UP)
        player_->EnterDoor();
    }
  }

  return false;
}

void LDGame::LoadAssets()
{
  // Create camera
  nafw::Camera* camera = new nafw::Camera(this);
  camera->SetMovement(true);
  camera->Move(0, -250);
  camera->LimitHorizontal(0.0f, 2000.0f);
  SetCamera(camera);

  // Create player
  player_ = new Person(this);
  player_->Create("player");
  player_->SetPosition(100, 0);

  // Create NPCs
  // Nurse
  Person* npc = new Person(this);
  npc->Create();
  npc_["Nurse"] = npc;

  // Create Doors
  // Bedroom -> Lobby
  Door* door = new Door(this);
  door_.push_back(door);

  // Lobby -> Bedroom
  door = new Door(this);
  door_.push_back(door);

  // Create rooms
  // Bedroom
  Room* room = new Room(this, 400, 100);
  room->SetPosition(0, -67);
  room->AddNPC(npc_["Nurse"], 20);
  room->AddDoor(door_[0], 280);
  room_.push_back(room);

  // Lobby
  room = new Room(this, 600, 100);
  room->AddDoor(door_[1], 40);
  room_.push_back(room);

  // Link Doors
  Door::LinkDoors(door_[0], door_[1]);

  // Set
  player_->SetRoom(room_[0], 100.0f);
}

void LDGame::Step(int delta)
{
  if (move_player_ == MOVE_RIGHT) player_->Move(delta / 10.0f, 0);
  else if (move_player_ == MOVE_LEFT) player_->Move(-delta / 10.0f, 0);

  camera()->LookAt(player_->x(), player_->y());
}

void LDGame::PhysicsStep(int delta)
{
}

void LDGame::Draw()
{
  Room* room = player_->room();

  if (room != nullptr) room->Draw();
  player_->Draw();
}

