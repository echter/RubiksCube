#pragma once

#include "cube.hpp"
#include "shader.hpp"

class SliceVersionB {
public:
  glm::mat4 sliceModel;
  Cube cubes[4][4];

  SliceVersionB() {
  }

  void draw(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {

    for(int i = 1; i < 4; i++) {
      for(int k = 1; k < 4; k++) {
        cubes[i][k].draw(Projection, View, cubes[i][k].model);
        //slices[1][0].cubes[i][k].draw(Projection, View, slices[1][0].cubes[i][k].model); //Testing only
      }
    }
  }
};