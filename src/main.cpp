#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "game.h"

// TODO Create a good assertion failure

int main(int argc, char** argv)
{
  nafw::Game app;

  if (!app.Start("Not Available FrameWork", argc, argv))
    return 1;

  exit(app.Run());
}
