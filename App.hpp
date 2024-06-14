#include "./include/HtmlElements.hpp"
#include "./include/Functions.hpp"
#include "./include/Mlinson/JsonParser.hpp"

int x = 0;

class App {
public:
    App() {
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
                Input.attr("type", "text").attr("id", "name"),
                Br,
                Label.text("Email:"),
                Input.attr("type", "email").attr("id", "email"),
                Br,
                Button.text("Submit").attr("type", "submit").on("click", [](){
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
            )
        );
        docEnd(main.getNode());
    }
    
};