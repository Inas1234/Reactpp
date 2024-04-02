#include <iostream>
#include "./include/HtmlElements.hpp"

int x = 0;

int main() {
    docBegin;
    Element main = Div;
    main.children(
        H1.text("Hello, World!"),
        P.text("This is a paragraph."),
        Div.children(
            H2.text("This is a subheading."),
            P.text("This is another paragraph.")
        ),
        Button.text("Click me!").on("click", [](){
            x++;
            std::cout << "Count: " << x << std::endl;
            EM_ASM_INT({
                document.getElementById('count').textContent = 'Count: ' + $0;
                return 0; 
            }, x);
        }),
        P.attr("id", "count").text("Count: " + std::to_string(x)),
        Form.children(
            Label.text("Name:"),
            Input.attr("type", "text"),
            Br,
            Label.text("Email:"),
            Input.attr("type", "email"),
            Br,
            Button.text("Submit").attr("type", "submit").on("click", [](){
                
                std::cout << "Form submitted!" << std::endl;
            })
        )

    );


    docEnd(main.getNode());

    return 0;
}