#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>
#endif

using namespace emscripten;


class VNode {
public:
    VNode(std::string tag, std::string textContent = "") : tag(tag), textContent(textContent) {}
    void appendChild(VNode child);
    void setTextContent(std::string textContent) { this->textContent = textContent; }
    void setAttribute(std::string key, std::string value) { attributes[key] = value; }
    void setEventListener(std::string event, std::function<void()> listener) {
        attributes["on" + event] = addEventListener(event, listener);
    }

    std::map<std::string, std::function<void()>> getEventListeners() { return eventListeners; }

    static void invokeEventListener(const std::string& event) {
        auto it = eventListeners.find(event);
        if (it != eventListeners.end()) {
            it->second(); 
        }
        else {
            std::cerr << "Callback with ID " << event << " not found." << std::endl;
        }
    }

    val render(val document) const;
    static std::string addEventListener(std::string event, std::function<void()> listener);

    static std::map<std::string, std::function<void()>> eventListeners;
private:
    std::string tag;
    std::string textContent;
    std::map<std::string, std::string> attributes;
    std::vector<VNode> children;
    
    static int callbackIdCounter;
};
