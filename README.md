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
#include "../include/Reactpp.cpp"

int x = 0;

class App {
public:
    App() {
        Router::init();
        Router::addRoute("/", []() {
            home();
        });
        Router::addRoute("/about", []() {
            about();
        });

        Router::onRouteChange();
    }

    static void home() {
        docBegin;
        Element main = Div;
        main.attr("id", "main").children(
            H1.text("Hello, A!"),
            P.text("This is a paragraph."),
            Div.children(
                H2.text("This is a subheading."),
                P.text("This is another paragraph.")
            ),
            Button.text("Click me!").on("click", []() {
                x++;
                std::cout << "Count: " << x << std::endl;
                UPDATE_ELEMENT_CONTENT("count", "Count: " + std::to_string(x));
            }),
            P.attr("id", "count").text("Count: " + std::to_string(x)),
            Form.attr("id", "nesto").children(
                Label.text("Name:"),
                Input.attr("type", "text").attr("id", "name"),
                Br,
                Label.text("Email:"),
                Input.attr("type", "email").attr("id", "email"),
                Br,
                Button.text("Submit").attr("type", "submit").on("click", []() {
                    PREVENT_DEFAULT_ACTION("nesto", "submit");

                    const char* name = getValueById("name");
                    const char* email = getValueById("email");
                    std::cout << "Name: " << name << " " << "Email: " << email << std::endl;
                    const char* response = get("https://jsonplaceholder.typicode.com", "/posts/1");

                    JSONParser parser;
                    JSONValue jsonValue = parser.parse(response);
                    JSONObject jsonObject = jsonValue.getObject();
                    std::cout << response << std::endl;
                    std::cout << jsonObject["title"]->getString() << std::endl;

                    free((void*)name);
                    free((void*)email);
                })
            ),
            Button.text("About").on("click", []() {
                Router::navigateTo("/about");
            })
        );
        docEnd(main.getNode());
    }

    static void about() {
        docBegin;
        Element main = Div;
        main.attr("id", "main").children(
            H1.text("ASS"),
            P.text("ASS."),
            Button.text("Home").on("click", []() {
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
App() {
        Router::init();
        Router::addRoute("/", []() {
            home();
        });
        Router::addRoute("/about", []() {
            about();
        });

        Router::onRouteChange();
    }
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
