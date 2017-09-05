#include "shader.hpp"

class Cube {
  std::shared_ptr<Shader> shader;

  GLuint vertex_array_id;
  GLuint vertex_buffer_id;
  GLuint color_buffer_id;

public:
  glm::mat4 model;

  Cube() : shader(Shader::get()) {
    //Receive the attribute ids from attribute names in the vertex shader source
    auto vertex_attribute_id = glGetAttribLocation(shader->program_id, "vertex");
    auto color_attribute_id = glGetAttribLocation(shader->program_id, "color");

    //The vertex array stores the buffers created below
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    //Write vertices to GPU buffer
    glGenBuffers(1, &vertex_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);

    GLfloat vertices[] = {
        2.0, 2.0, 2.0,   // TOP INWARDS RIGHT 0
        -2.0, 2.0, 2.0,  //TOP INWARDS LEFT 1
        2.0, 2.0, -2.0,  // TOP OUTWARDS RIGHT 2
        -2.0, 2.0, -2.0, // TOP OUTWARDS LEFT 3

        2.0, -2.0, 2.0,  // BOTTOM INWARDS RIGHT 4
        -2.0, -2.0, 2.0, // BOTTOM INWARDS LEFT 5
        2.0, -2.0, -2.0, // BOTTOM OUTWARDS RIGHT 6
        -2.0, -2.0, -2.0 // BOTTOM OUTWARDS 7
    };

    GLuint indices[] = {
        0, 1, 2,
        1, 2, 3,

        0, 2, 6,
        0, 4, 6,

        4, 5, 6,
        5, 6, 7,

        0, 1, 5,
        0, 5, 4,

        1, 3, 5,
        3, 5, 7,

        3, 2, 7,
        2, 6, 7};

    int counter = 0;
    GLfloat verticesLongVersion[36 * 3];
    for(int i = 0; i < 36; i++) {
      for(int k = 0; k < 3; k++) {
        verticesLongVersion[counter] = vertices[indices[i] * 3 + k];
        counter++;
      }
    };


    // unsigned int EBO;
    // glGenBuffers(1, &EBO);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // // 3. copy our index array in a element buffer for OpenGL to use
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLongVersion), verticesLongVersion, GL_STATIC_DRAW);

    //Set vertex input attributes for shader program
    glEnableVertexAttribArray(vertex_attribute_id);
    glVertexAttribPointer(vertex_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //Write colors to GPU buffer
    glGenBuffers(1, &color_buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer_id);
    GLfloat colors[] = {
        0.8, 0.0, 0.0,
        0.8, 0.0, 0.0,
        0.8, 0.0, 0.0,
        0.8, 0.0, 0.0,
        0.8, 0.0, 0.0,
        0.8, 0.0, 0.0,

        0.0, 0.5, 0.0,
        0.0, 0.5, 0.0,
        0.0, 0.5, 0.0,
        0.0, 0.5, 0.0,
        0.0, 0.5, 0.0,
        0.0, 0.5, 0.0,

        1.0, 0.6, 0.0,
        1.0, 0.6, 0.0,
        1.0, 0.6, 0.0,
        1.0, 0.6, 0.0,
        1.0, 0.6, 0.0,
        1.0, 0.6, 0.0,

        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,
        1.0, 1.0, 0.0,

        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,
        0.0, 0.0, 1.0,

        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
        1.0, 1.0, 1.0,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    //Set color input attributes for shader program
    glEnableVertexAttribArray(color_attribute_id);
    glVertexAttribPointer(color_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    //Unbind vertex array
    glBindVertexArray(0);
  }

  ~Cube() {
    glDeleteBuffers(1, &vertex_buffer_id);
    glDeleteBuffers(1, &color_buffer_id);
    glDeleteVertexArrays(1, &vertex_array_id);
  }

  void draw(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {

    glm::mat4 MVP = Projection * View * Model;

    glUseProgram(shader->program_id);

    //Set MVP attribute for shader program
    glUniformMatrix4fv(shader->MVP_id, 1, GL_FALSE, &MVP[0][0]);

    glBindVertexArray(vertex_array_id);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);

    //MVP = glm::translate(MVP, glm::vec3(1.5f, 0.0f, 0.0f));
    //MVP = glm::rotate(MVP, 3.14159265359f / 2, glm::vec3(1.0f, 0.0f, 0.0f));

    //Unbind vertex array
    glBindVertexArray(0);

    //Unlink shader program
    glUseProgram(0);
  }

  void drawTest(glm::mat4 &Projection, glm::mat4 &View, glm::mat4 &Model) {

    Model = model;

    glm::mat4 MVP = Projection * View * Model;

    glUseProgram(shader->program_id);

    //Set MVP attribute for shader program
    glUniformMatrix4fv(shader->MVP_id, 1, GL_FALSE, &MVP[0][0]);

    glBindVertexArray(vertex_array_id);

    glDrawElements(GL_TRIANGLES, 12 * 3, GL_UNSIGNED_INT, 0);
    std::cout << "this should not be called" << std::endl;

    //MVP = glm::translate(MVP, glm::vec3(1.5f, 0.0f, 0.0f));
    //MVP = glm::rotate(MVP, 3.14159265359f / 2, glm::vec3(1.0f, 0.0f, 0.0f));

    //Unbind vertex array
    glBindVertexArray(0);

    //Unlink shader program
    glUseProgram(0);
  }

  void drawRubixSide(glm::mat4 &MVP) {

    Cube cube;
    glm::mat4 original = MVP;

    MVP = glm::translate(MVP, glm::vec3(-5.0, 0.0, 0.0));

    // for(int i = 0; i < 3; i++) {
    //   cube.draw(MVP);
    //   MVP = glm::translate(MVP, glm::vec3(5.0f, 0.0, 0.0f));
    // }

    MVP = original;
  }

  void drawRubixCube(glm::mat4 &MVP) {

    Cube cube;

    glm::mat4 original = MVP;

    MVP = glm::translate(MVP, glm::vec3(0.0, 0.0, -5.0));

    // for(int i = 0; i < 3; i++) {
    //   cube.drawRubixSide(MVP);
    //   MVP = glm::translate(MVP, glm::vec3(0.0f, 0.0f, 5.0f));
    // }

    MVP = original;
  }

  void drawFullRubix(glm::mat4 &MVP) {

    Cube cube;

    glm::mat4 original = MVP;

    MVP = glm::translate(MVP, glm::vec3(0.0, -5.0, 0.0));

    // for(int i = 0; i < 3; i++) {
    //   cube.drawRubixCube(MVP);
    //   MVP = glm::translate(MVP, glm::vec3(0.0f, 5.0f, 0.0f));
    // }

    MVP = original;
  }
};