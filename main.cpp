#include <iostream>
#include "./include/Element.hpp"

int main(){
    docBegin;

    Element main("div");
    main.child(
        Element("button")
            .text("Click me!")
            .on("click", [](){
                std::cout << "Button clicked!" << std::endl;
            })

    );


    docEnd(main.getNode());

    return 0;
}