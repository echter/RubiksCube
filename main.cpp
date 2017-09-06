#include "cube.hpp"
#include "grid.hpp"
#include "rubiks.hpp"
#include "slice.hpp"

class SFMLApplication {
  class Window : public sf::Window {
  public:
    Window(const sf::ContextSettings &context_settings) : sf::Window(sf::VideoMode(800, 600), "SFML Example", sf::Style::Default, context_settings) {
      glewExperimental = GL_TRUE;
      if(glewInit() != GLEW_OK)
        std::cerr << "Failed to initialize GLEW" << std::endl;
    }
  };

  sf::ContextSettings context_settings;
  Window window;

  glm::mat4 projection;

public:
  SFMLApplication() : context_settings(24, 0, 0, 3, 3, sf::ContextSettings::Attribute::Core),
                      window(context_settings) {
    window.setFramerateLimit(144);
    window.setVerticalSyncEnabled(true);

    //Various settings
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    projection = glm::perspective(glm::radians(45.0), 4.0 / 3.0, 0.1, 100.0);
  }

  void start() {
    glm::vec3 camera(0.0, 0.0, 6.0);

    bool running = true;
    RubiksCube rubiks;
    auto model = glm::mat4(1.0);
    auto view = glm::lookAt(glm::vec3(10, 20, 40.0),   //Camera position in World Space
                            glm::vec3(0.0, 0.0, 0.0),  //Camera looks towards this position
                            glm::vec3(0.0, 1.0, 0.0)); //Up

    glm::mat4 copyView = view;

    rubiks.draw(projection, view, model);
    while(running) {
      //Handle events
      sf::Event event;
      while(window.pollEvent(event)) {
        if(event.type == sf::Event::KeyPressed) {
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
            running = false;
          }
        }
        if(event.type == sf::Event::KeyPressed) {
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rubiks.slices[1][0].sliceModel = glm::rotate(rubiks.slices[1][0].sliceModel, (float)M_PI / 2.0f, glm::vec3(0.0, 1.0, 0.0));
            std::cout << "call left" << std::endl;
          }
        }
        if(event.type == sf::Event::KeyPressed) {
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            rubiks.switcher();
            rubiks.slices[0][1].sliceModel = glm::rotate(rubiks.slices[1][0].sliceModel, (float)M_PI / 2.0f, glm::vec3(0.0, 0.0, 1.0));
            std::cout << "call UP!!!" << std::endl;
          }
        }
        else if(event.type == sf::Event::MouseMoved) {
          camera.x = 0.01 * -(event.mouseMove.x - static_cast<int>(window.getSize().x) / 2);
          camera.y = 0.01 * (event.mouseMove.y - static_cast<int>(window.getSize().y) / 2);
        }
        else if(event.type == sf::Event::Closed) {
          window.close();
          running = false;
        }
      }

      //Draw
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      view = copyView;
      view = glm::rotate(view, 1.0f * camera.x, glm::vec3(0.0, 1.0, 0.0));

      //Model matrix : an identity matrix (model will be at the origin)
      auto model = glm::mat4(1.0);
      //The Model-View-Projection matrix
      auto MVP = projection * view * model;

      Grid grid;
      grid.draw(MVP);

      //rubiks.update(projection, view);
      rubiks.update(projection, view);

      //Swap buffer (show result)
      window.display();
    }
  }
};

int main() {
  SFMLApplication sfml_application;
  sfml_application.start();

  return 0;
}
