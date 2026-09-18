#include "collider.h"
#include "raylib.h"


Collider Collider_Create(float x, float y, float width, float height, void *owner) {
   Collider col;
   col.x = x;
   col.y = y;
   col.width = width;
   col.height = height;
   col.owner = owner;
   return col;
}
