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