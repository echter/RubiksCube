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

    slices[1][0].draw(Projection, View, Model, 1);
    slices[2][0].draw(Projection, View, Model, 2);
    slices[3][0].draw(Projection, View, Model, 3);
  }

  void update(glm::mat4 &Projection, glm::mat4 &View) {

    slices[1][0].update(Projection, View, slices[1][0].sliceModel, 1);
    slices[1][0].draw(Projection, View, slices[1][0].sliceModel, 1);
    slices[2][0].update(Projection, View, slices[2][0].sliceModel, 2);
    slices[3][0].update(Projection, View, slices[3][0].sliceModel, 3);
  }

  void switcher() {
  }
};
