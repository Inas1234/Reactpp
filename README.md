# React++

React++ is a modern C++ web framework inspired by React. It enables developers to build single-page applications (SPAs) using C++ and Emscripten, leveraging familiar concepts from React such as components, state, and routing.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Routing](#routing)
- [Contributing](#contributing)
- [License](#license)

## Installation

### Prerequisites

- [Emscripten](https://emscripten.org/docs/getting_started/downloads.html): A toolchain for compiling to WebAssembly.

### Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/Inas1234/Reactpp.git
   cd reactpp
2. Compile the project:
   ```bash
   emcc ./src/main.cpp ./include/VNode.cpp -o main.js --bind -s WASM=1 -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS='["_invokeCppCallback", "_main"]'  -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' -sNO_DISABLE_EXCEPTION_CATCHING 
3. Serve the project:
   You can use a simple HTTP server to serve the project locally for now until the creation of my own serving method:
   ```bash
   npx http-server ./dist
   
## Usage

### Creating a Component

Components in React++ are created using C++ classes. Each component should define its rendering logic and state management.

```cpp
#include "../include/Reactpp.hpp"
#include "Home.hpp"
#include "About.hpp"

class App {
public:
    App() {
        Router::init();
        Router::addRoute("/", [](){
            Home::render();
        });
        Router::addRoute("/about", [](){
            About::render();            
        });


        Router::onRouteChange();
    }

};
```

```cpp
#pragma once

#include "../include/Reactpp.hpp"
#include <memory>


class Home {
public:
    static void render(){
        Home home;
        home.init();
    }


private:
    static int count;
    static const char* name;

    Home(){
        State::getInstance().setState("count2", "0");
        State::getInstance().subscribe("count2", [](const std::string& value){
            std::cout << "[Home] Count: " << value << std::endl;
        });
    }

    void init(){
        docBegin;
        Element main = Div;
        main.attr("id", "main").children(
            H1.text("Home"),
            Button.text("Click me!").on("click", [](){
                Home::count++;
                State::getInstance().setState("count2", std::to_string(Home::count));
                UPDATE_ELEMENT_CONTENT("count", "Count: " + std::to_string(Home::count));
            }),
            P.attr("id", "count").text("Count: " + std::to_string(Home::count)),
            Button.text("Go to About").on("click", [](){
                Router::navigateTo("/about");
            }),
            Input.attr("type", "text").attr("placeholder", "Enter your name").attr("id", "name"),
            Button.text("Submit").on("click", [](){
                Home::name = getValueById("name");
                UPDATE_ELEMENT_CONTENT("greet", "Hello, " + std::string(name) + "!");
            }),
            P.attr("id", "greet").text("")
        );
        docEnd(main.getNode());
    }
};

int Home::count = 0;
const char* Home::name = "";
```

```cpp
#pragma once
#include "../include/Reactpp.hpp"


class About {
public:
    static void render(){
        About about;
        about.init();
    }

private:

    About(){
        State::getInstance().setState("count", "0");
        State::getInstance().subscribe("count", [](const std::string& value){
            std::cout << "[About] Count: " << value << std::endl;
        });
    }

    void init(){
        docBegin;
        Element main = Div;
        main.attr("id", "main").children(
            H1.text("About"),
            P.text("This is a simple example of a React-like C++ library."),
            Button.text("Click me!").on("click", [](){
                int count = std::stoi(State::getInstance().getState("count"));
                count++;
                State::getInstance().setState("count", std::to_string(count));
            }),
            Button.text("Go to Home").on("click", [](){
                Router::navigateTo("/");
            })
        );
        docEnd(main.getNode());
    }
};
```

### Rendering the Application

The main application component should be rendered into the root element.

```c++
#include <iostream>
#include "./App.hpp"

int main() {
    App app;
    return 0;
}
```

### Routing

React++ includes a simple routing system inspired by React Router. Define your routes and navigate between them.

```c++
class App {
public:
    App() {
        Router::init();
        Router::addRoute("/", [](){
            Home::render();
        });
        Router::addRoute("/about", [](){
            About::render();            
        });


        Router::onRouteChange();
    }

};
```

## Contributing

To contribute to React++, follow these steps:

- Fork the repository.
- Create a new branch (git checkout -b feature-branch).
- Make your changes.
- Commit your changes (git commit -am 'Add new feature').
- Push to the branch (git push origin feature-branch).
- Create a new Pull Request.

## License

React++ is licensed under the MIT License. See the [LICENSE](LICENSE.md) file for more details.
