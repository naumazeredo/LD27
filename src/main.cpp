#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "ldgame.h"

// TODO Create a good assertion failure

int main(int argc, char** argv)
{
  LDGame app;

  if (!app.Start("Ludum Dare 27", argc, argv))
    return 1;

  exit(app.Run());
}
