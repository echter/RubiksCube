#include "cube.hpp"
#include "sliceVersionB.hpp"

class RubiksVersionB {
public:
  Cube cubes[4][4][4];
  SliceVersionB slices[4][4];

  RubiksVersionB() {
  }

  void drawCubes(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {

    glm::mat4 original = Model;

    for(int sliceNumber = 1; sliceNumber < 4; sliceNumber++) {
      for(int i = 1; i < 4; i++) {
        Model = glm::translate(Model, glm::vec3(4.2 * (i - 2), -4.2 + (4.2 * (sliceNumber - 1)), -4.2));
        for(int k = 1; k < 4; k++) {
          cubes[sliceNumber][i][k].model = Model;
          //cubes[sliceNumber][i][k].draw(Projection, View, cubes[sliceNumber][i][k].model); //Testing only
          Model = glm::translate(Model, glm::vec3(0.0, 0.0, 4.2));
        }
        Model = original;
      }
    }
  }

  void generateHorizontalSlices(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {

    for(int sliceNumber = 1; sliceNumber < 4; sliceNumber++) {
      slices[sliceNumber][0].sliceModel = Model;
      for(int i = 1; i < 4; i++) {
        for(int k = 1; k < 4; k++) {
          slices[sliceNumber][0].cubes[i][k] = cubes[sliceNumber][i][k];
          slices[sliceNumber][0].cubes[i][k].model = cubes[sliceNumber][i][k].model;
          //slices[1][0].cubes[i][k].draw(Projection, View, slices[1][0].cubes[i][k].model); //Testing only
        }
      }
    }
  }

  void drawSlices(glm::mat4 &Projection, glm::mat4 &View) {
    for(int i = 1; i < 4; i++) {
      slices[i][0].draw(Projection, View, slices[i][0].sliceModel); //Draw the cubes in the slice
    }
  }

  void updateSlices(glm::mat4 &Projection, glm::mat4 &View) {
    for(int i = 1; i < 4; i++) {
      slices[i][0].draw(Projection, View, slices[i][0].sliceModel);
    }
  }

  void rotateHorizontalSlice(glm::mat4 &Projection, glm::mat4 &View, int sliceNumber) {

    slices[sliceNumber][0].sliceModel = glm::rotate(slices[sliceNumber][0].sliceModel, (float)M_PI / 2, glm::vec3(0.0, 1.0, 0.0));
    std::cout << "call left" << std::endl;
  }
};
