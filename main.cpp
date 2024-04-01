#include <iostream>
#include "./include/Element.hpp"

int main(){
    docBegin;

    Element main("div");
    main.children(
        Element("button")
            .text("Click me!")
            .on("click", [](){
                std::cout << "Button clicked!" << std::endl;
            }),
        Element("button")
            .text("Click me too!")
            .on("click", [](){
                std::cout << "Second button clicked!" << std::endl;
            })
    );


    docEnd(main.getNode());

    return 0;
}