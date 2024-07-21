#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif
#include <string>
#include <functional>
#include <iostream>

using namespace emscripten;

class Router{
public:
    static std::map<std::string, std::function<void()>> routes;
    static void addRoute(std::string path, std::function<void()> callback) {
        routes[path] = callback;
    }

    static void navigateTo(const std::string &path){
        val::global("history").call<void>("pushState", val::null(), val::null(), path);
        onRouteChange();
    }

    static void onRouteChange(){
        std::string path = val::global("window")["location"]["pathname"].as<std::string>();
        auto it = routes.find(path);
        if(it != routes.end()){
            clearContent();
            it->second();
        }
        else{
            std::cerr << "Route not found." << std::endl;
        }
    }

    static void clearContent() {
        val document = val::global("document");
        val root = document.call<val>("getElementById", std::string("root"));
        if (!root.isNull()) {
            root.set("innerHTML", "");
        } else {
            std::cerr << "Element with id 'root' not found." << std::endl;
        }
    }



    static void init(){
        EM_ASM(
            window.onpopstate = function(event){
                Module.ccall('onRouteChange', 'void', [], []);
            };
        );
    }
};

std::map<std::string, std::function<void()>> Router::routes;

EMSCRIPTEN_BINDINGS(router_module){
    function("onRouteChange", &Router::onRouteChange);
}