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

    Home(){}

    void init(){
        docBegin;
        Element main = Div;
        main.attr("id", "main").children(
            H1.text("Home"),
            Button.text("Click me!").on("click", [](){
                Home::count++;
                std::cout << "[Home] Name: " << Home::name << std::endl;
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