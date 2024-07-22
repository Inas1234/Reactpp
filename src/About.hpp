#pragma once
#include "../include/Reactpp.hpp"

int count = 0;

class About {
public:
    static void render(){
        About about;
        about.init();
    }

private:

    About(){}

    void init(){
        docBegin;
        Element main = Div;
        main.attr("id", "main").children(
            H1.text("About"),
            P.text("This is a simple example of a React-like C++ library."),
            Button.text("Click me!").on("click", [](){
                count++;
                std::cout << "[About] Count: " << count << std::endl;
            }),
            Button.text("Go to Home").on("click", [](){
                Router::navigateTo("/");
            })
        );
        docEnd(main.getNode());
    }
};