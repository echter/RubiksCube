#include "cube.hpp"
#include "slice.hpp"

class RubiksCube {
public:
  Cube cubes[4][4][4];
  Slice slices[4][4];
  bool switcher = true;

  RubiksCube() {
  }

  void draw(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {

    slices[1][0].draw(Projection, View, Model);
  }

  void update(glm::mat4 &Projection, glm::mat4 &View) {

    draw(Projection, View, slices[1][0].sliceModel);
  }
};
