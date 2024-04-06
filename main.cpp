#include <iostream>
#include "./include/HtmlElements.hpp"
#include "./include/Functions.hpp"

int x = 0;

int main() {
    docBegin;
    Element main = Div;
    main.attr("id", "main").children(
        H1.text("Hello, World!"),
        P.text("This is a paragraph."),
        Div.children(
            H2.text("This is a subheading."),
            P.text("This is another paragraph.")
        ),
        Button.text("Click me!").on("click", [](){
            x++;
            std::cout << "Count: " << x << std::endl;
            UPDATE_ELEMENT_CONTENT("count", "Count: " + std::to_string(x));
        }),
        P.attr("id", "count").text("Count: " + std::to_string(x)),
        Form.attr("id", "nesto").children(
            Label.text("Name:"),
            Input.attr("type", "text"),
            Br,
            Label.text("Email:"),
            Input.attr("type", "email"),
            Br,
            Button.text("Submit").attr("type", "submit").on("click", [](){
                PREVENT_DEFAULT_ACTION("nesto", "submit");
            })
        )

    );


    docEnd(main.getNode());


    
    return 0;
}