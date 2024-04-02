#include <iostream>
#include "./include/HtmlElements.hpp"

int x = 0;

int main() {
    docBegin;
    Element main = div;
    main.children(
        h1.text("Hello, World!"),
        p.text("This is a paragraph."),
        div.children(
            h2.text("This is a subheading."),
            p.text("This is another paragraph.")
        ),
        button.text("Click me!").on("click", [](){
            x++;
            std::cout << "Count: " << x << std::endl;
        }),
        form.children(
            label.text("Name:"),
            input.attr("type", "text"),
            br,
            label.text("Email:"),
            input.attr("type", "email"),
            br,
            button.text("Submit").attr("type", "submit").on("click", [](){
                
                std::cout << "Form submitted!" << std::endl;
            })
        )

    );


    docEnd(main.getNode());

    return 0;
}