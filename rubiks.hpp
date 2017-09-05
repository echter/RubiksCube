#include "cube.hpp"
#include "slice.hpp"

class RubixCube {
public:
  Cube cubes[4][4][4];
  Slice slices[4][4];
  bool switcher = true;

  RubixCube() {
  }

  void draw(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {
  }
};
