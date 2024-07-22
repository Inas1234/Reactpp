#include "../include/Reactpp.hpp"
#include "Home.hpp"
#include "About.hpp"

class App {
public:
    App() {
        Router::init();
        Router::addRoute("/", [](){
            Home::render();
        });
        Router::addRoute("/about", [](){
            About::render();            
        });


        Router::onRouteChange();
    }

};

