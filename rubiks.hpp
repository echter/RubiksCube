#include "cube.hpp"
#include "slice.hpp"

class RubiksCube {
public:
  Cube cubes[4][4][4];
  Slice slices[4][4];

  RubiksCube() {
  }

  void draw(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {

    // slices[1][0].draw(Projection, View, Model, 1);
    // slices[2][0].draw(Projection, View, Model, 2);
    // slices[3][0].draw(Projection, View, Model, 3);

    slices[0][1].draw(Projection, View, Model, 1);
    slices[0][2].draw(Projection, View, Model, 2);
    slices[0][3].draw(Projection, View, Model, 3);
  }

  void update(glm::mat4 &Projection, glm::mat4 &View) {

    //slices[1][0].update(Projection, View, slices[1][0].sliceModel, 1);
    slices[1][0].draw(Projection, View, slices[1][0].sliceModel, 1);
    // slices[2][0].update(Projection, View, slices[2][0].sliceModel, 2);
    // slices[2][0].draw(Projection, View, slices[2][0].sliceModel, 2);
    // slices[3][0].update(Projection, View, slices[3][0].sliceModel, 3);
    // slices[3][0].draw(Projection, View, slices[3][0].sliceModel, 3);

    //slices[0][1].update(Projection, View, slices[0][1].sliceModel, 4);
    slices[0][1].draw(Projection, View, slices[0][1].sliceModel, 4);
    //slices[0][2].update(Projection, View, slices[0][2].sliceModel, 5);
    //slices[0][2].draw(Projection, View, slices[0][2].sliceModel, 5);
    //slices[0][3].update(Projection, View, slices[0][3].sliceModel, 6);
    //slices[0][3].draw(Projection, View, slices[0][3].sliceModel, 6);
  }

  void switcher() {
  }
};
