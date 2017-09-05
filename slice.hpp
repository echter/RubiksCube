#pragma once

#include "cube.hpp"
#include "shader.hpp"

class Slice {
public:
  glm::mat4 sliceModel;
  Cube cubes[4][4][4];

  Slice() {
  }

  void draw(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {

    sliceModel = Model;

    Model = glm::translate(Model, glm::vec3(-4.2, -4.2, -4.2));
    glm::mat4 original = Model;

    for(int i = 1; i < 4; i++) {
      Model = glm::translate(Model, glm::vec3(4.2 * (i - 1), 0.0, 0.0));
      for(int k = 1; k < 4; k++) {
        cubes[1][i][k].draw(Projection, View, Model);
        Model = glm::translate(Model, glm::vec3(0.0, 0.0, 4.2));
      }
      Model = original;
    }
  }

  void update(glm::mat4 &Projection, glm::mat4 &View) {

    glm::mat4 Model = sliceModel;
    glm::mat4 original = Model;

    for(int i = 1; i < 4; i++) {
      Model = glm::translate(Model, glm::vec3(4.2 * (i - 1), 0.0, 0.0));
      for(int k = 1; k < 4; k++) {
        cubes[1][i][k].draw(Projection, View, Model);
        Model = glm::translate(Model, glm::vec3(0.0, 0.0, 4.2));
      }
      Model = original;
    }
  }
};