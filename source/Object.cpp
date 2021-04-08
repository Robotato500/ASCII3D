#pragma once

#include "../headers/global.h"
#include "../headers/Object.h"
#include "../headers/Image.h"

Object::Object(const char* spritePath, int atlas) {
    Image dummy(spritePath, atlas);
    sprite = &dummy;
}
