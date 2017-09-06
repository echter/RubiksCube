#pragma once

#include "cube.hpp"
#include "shader.hpp"

class Slice {
public:
  glm::mat4 sliceModel;
  Cube cubes[4][4][4];

  Slice() {
  }

  void draw(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model, int sliceNumber) {
    bool horizontal = true;
    if(sliceNumber >= 4 && sliceNumber <= 6) {
      sliceNumber -= 3;
      horizontal = false;
    }

    sliceModel = Model;
    glm::mat4 original = Model;

    if(horizontal) {
      for(int i = 1; i < 4; i++) {
        Model = glm::translate(Model, glm::vec3(4.2 * (i - 2), -4.2 + (4.2 * (sliceNumber - 1)), -4.2));
        for(int k = 1; k < 4; k++) {
          cubes[sliceNumber][i][k].model = Model;
          cubes[sliceNumber][i][k].draw(Projection, View, cubes[sliceNumber][i][k].model);
          Model = glm::translate(Model, glm::vec3(0.0, 0.0, 4.2));
        }
        Model = original;
      }
    }
    else {
      for(int i = 1; i < 4; i++) {
        Model = glm::translate(Model, glm::vec3(4.2 * (i - 2), -4.2 + (4.2 * (sliceNumber - 1)), -4.2));
        for(int k = 1; k < 4; k++) {
          cubes[sliceNumber][k][i].model = Model;
          cubes[sliceNumber][k][i].draw(Projection, View, cubes[sliceNumber][i][k].model);
          Model = glm::translate(Model, glm::vec3(0.0, 0.0, 4.2));
        }
        Model = original;
      }
    }
  }

  void update(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model, int sliceNumber) {

    for(int i = 1; i < 4; i++) {
      for(int k = 1; k < 4; k++) {
        cubes[sliceNumber][i][k].draw(Projection, View, cubes[sliceNumber][i][k].model);
      }
    }
  }
};