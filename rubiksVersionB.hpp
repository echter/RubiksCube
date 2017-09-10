#include "cube.hpp"
#include "sliceVersionB.hpp"

class RubiksVersionB {
public:
  Cube cubes[4][4][4];
  Cube copy[4][4][4];
  SliceVersionB slices[4][4];

  RubiksVersionB() {
  }

  void generateNewCube(glm::mat4 &Projection, glm::mat4 &View) { //NOT CURRENTLY IN USE
    for(int sliceNumber = 1; sliceNumber < 2; sliceNumber++) {
      for(int i = 1; i < 4; i++) {
        for(int k = 1; k < 4; k++) {
          if(cubes[1][i][k].model == slices[1][0].cubes[i][k].model) {
            std::cout << i << "i, and k:" << k << std::endl;
          }
        }
      }
    }
  }

  // void generateHorizontalSlicesWithNewCubes(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {

  //   for(int sliceNumber = 1; sliceNumber < 4; sliceNumber++) {
  //     slices[sliceNumber][0].sliceModel = Model;
  //     for(int i = 1; i < 4; i++) {
  //       for(int k = 1; k < 4; k++) {
  //         slices[sliceNumber][0].cubes[i][k] = cubesForNewCube[sliceNumber][i][k];
  //         slices[sliceNumber][0].cubes[i][k].model = cubesForNewCube[sliceNumber][i][k].model;
  //         //slices[1][0].cubes[i][k].draw(Projection, View, slices[1][0].cubes[i][k].model); //Testing only
  //       }
  //     }
  //   }
  // }

  void drawCubes(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {

    glm::mat4 original = Model;

    for(int sliceNumber = 1; sliceNumber < 4; sliceNumber++) {
      for(int i = 1; i < 4; i++) {
        Model = glm::translate(Model, glm::vec3(4.2 * (i - 2), -4.2 + (4.2 * (sliceNumber - 1)), -4.2));
        for(int k = 1; k < 4; k++) {
          cubes[sliceNumber][i][k].model = Model;
          copy[sliceNumber][i][k].model = Model;
          //cubes[sliceNumber][i][k].draw(Projection, View, cubes[sliceNumber][i][k].model); //Testing only
          Model = glm::translate(Model, glm::vec3(0.0, 0.0, 4.2));
        }
        Model = original;
      }
    }
  }

  void generateVerticalSlices(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {

    for(int sliceNumber = 1; sliceNumber < 4; sliceNumber++) {
      slices[sliceNumber][0].sliceModel = Model;
      for(int i = 1; i < 4; i++) {
        for(int k = 1; k < 4; k++) {
          slices[0][sliceNumber].cubes[i][k] = cubes[i][sliceNumber][k];
          slices[0][sliceNumber].cubes[i][k].model = cubes[i][sliceNumber][k].model;
          //slices[1][0].cubes[i][k].draw(Projection, View, slices[1][0].cubes[i][k].model); //Testing only
        }
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

  void drawHorizontalSlices(glm::mat4 &Projection, glm::mat4 &View) {
    for(int i = 1; i < 4; i++) {
      slices[i][0].draw(Projection, View, slices[i][0].sliceModel); //Draw the cubes in the slice
    }
  }

  void drawVerticalSlices(glm::mat4 &Projection, glm::mat4 &View) {
    for(int i = 1; i < 4; i++) {
      slices[0][i].draw(Projection, View, slices[0][i].sliceModel); //Draw the cubes in the slice
    }
  }

  void generateNewHorizontalSlices(glm::mat4 &Projection, glm::mat4 &View, int sliceNumber) {

    for(int i = 1; i < 4; i++) {
      for(int k = 1; k < 4; k++) {
        slices[sliceNumber][0].cubes[i][k] = cubes[sliceNumber][i][k];
        //slices[sliceNumber][0].cubes[i][k].model = cubes[sliceNumber][i][k].model;
        //slices[1][0].cubes[i][k].draw(Projection, View, slices[1][0].cubes[i][k].model); //Testing only
      }
    }
  }

  void generateNewVerticalSlices(glm::mat4 &Projection, glm::mat4 &View, int sliceNumber) {
    slices[0][sliceNumber].sliceModel = slices[0][sliceNumber].sliceModel;

    for(int i = 1; i < 4; i++) {
      for(int k = 1; k < 4; k++) {
        slices[0][sliceNumber].cubes[i][k].model = cubes[i][sliceNumber][k].model;

        //slices[0][sliceNumber].cubes[i][k].model = cubes[i][sliceNumber][k].model;
        //slices[1][0].cubes[i][k].draw(Projection, View, slices[1][0].cubes[i][k].model); //Testing only
      }
    }
  }

  void updateNewCubesForRotateVertical(int sliceNumber) {

    for(int k = 1; k < 4; k++) {
      for(int i = 1; i < 4; i++) {
        cubes[k][sliceNumber][i].model = copy[4 - i][sliceNumber][k].model * slices[0][sliceNumber].sliceModel;
      }
    }
  }

  void updateNewCubesForRotateHorizontal(int sliceNumber) {
    
    for(int k = 1; k < 4; k++) {
      for(int i = 1; i < 4; i++) {
        cubes[sliceNumber][k][i].model = copy[sliceNumber][4-k][i].model * slices[sliceNumber][0].sliceModel;
      }
    }
  }

  void updateSliceCubes() {
    for(int sliceNumber = 1; sliceNumber < 4; sliceNumber++) {
      for(int i = 1; i < 4; i++) {
        for(int k = 1; k < 4; k++) {
          slices[sliceNumber][0].cubes[i][k] = cubes[sliceNumber][i][k];
          slices[0][sliceNumber].cubes[i][k] = cubes[i][sliceNumber][k];
        }
      }
    }
  }

  void drawTest(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {
    for(int sliceNumber = 1; sliceNumber < 4; sliceNumber++) {
      for(int i = 1; i < 4; i++) {
        for(int k = 1; k < 4; k++) {
          cubes[sliceNumber][i][k].draw(Projection, View, Model);
        }
      }
    }
  }

  void rotateVerticalSlice(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model, int sliceNumber) {
    
    generateNewVerticalSlices(Projection, View, 1);
    generateNewVerticalSlices(Projection, View, 2);
    generateNewVerticalSlices(Projection, View, 3);

    slices[0][sliceNumber].sliceModel = glm::rotate(slices[0][sliceNumber].sliceModel, (float)M_PI / 2, glm::vec3(1.0, 0.0, 0.0));

    updateNewCubesForRotateVertical(sliceNumber);
    
    drawVerticalSlices(Projection, View);

    std::cout << "Up" << std::endl;
  }

  void rotateHorizontalSlice(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model, int sliceNumber) {

    generateNewHorizontalSlices(Projection, View, 1);
    generateNewHorizontalSlices(Projection, View, 2);
    generateNewHorizontalSlices(Projection, View, 3);

    slices[sliceNumber][0].sliceModel = glm::rotate(slices[sliceNumber][0].sliceModel, (float)M_PI / 2, glm::vec3(0.0, 1.0, 0.0));

    updateNewCubesForRotateHorizontal(sliceNumber);
    
    drawHorizontalSlices(Projection, View);

    // if(cubes[sliceNumber][1][1].model != copy[sliceNumber][3][1].model) {
    //   //generateNewHorizontalSlices(Projection, View, sliceNumber);
    //   updateNewCubesForRotateHorizontal(sliceNumber);
    //   updateSliceCubes();
    //   std::cout << "called" << std::endl;
    // }

    std::cout << "call left" << std::endl;
  }
};
