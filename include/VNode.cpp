#include "VNode.hpp"

std::unordered_map<std::string, std::function<void()>> VNode::eventListeners;
int VNode::callbackIdCounter = 0;

extern "C" {
    void invokeCppCallback(const char* callbackId) {
        if (auto it = VNode::eventListeners.find(callbackId); it != VNode::eventListeners.end()) {
            it->second();
        } else {
            std::cerr << "Callback with ID '" << callbackId << "' not found." << std::endl;
        }
    }
}

EM_JS(void, attachEventListener, (const char* elementId, const char* eventType, const char* callbackId), {
    var elementIdStr = UTF8ToString(elementId);
    var eventTypeStr = UTF8ToString(eventType);
    var callbackIdStr = UTF8ToString(callbackId);
    
    setTimeout(function() {
        var element = document.getElementById(elementIdStr);
        if (element) {
            element.addEventListener(eventTypeStr, function() {
                Module.ccall('invokeCppCallback', 'void', ['string'], [callbackIdStr]);
            }, false);
        } else {
            console.log("Element not found for ID:", elementIdStr);
        }
    }, 0);
});

EMSCRIPTEN_BINDINGS(vnode_module) {
    emscripten::function("invokeCppCallback", &invokeCppCallback, emscripten::allow_raw_pointers());
}

std::string VNode::addEventListener(const std::string& event, std::function<void()> listener) {
    std::string callbackId = "callback_" + std::to_string(callbackIdCounter++);
    eventListeners[callbackId] = std::move(listener);
    return callbackId;
}

void VNode::appendChild(VNode child) {
    children.push_back(std::move(child));
}

emscripten::val VNode::render(emscripten::val document) const {
    emscripten::val element = document.call<emscripten::val>("createElement", tag);
    element.set("textContent", textContent);

    if (auto idIt = attributes.find("id"); idIt == attributes.end()) {
        std::string uniqueId = "element_" + std::to_string(callbackIdCounter++);
        element.set("id", uniqueId);
        const_cast<std::map<std::string, std::string>&>(attributes)["id"] = uniqueId;
    }

    for (const auto& child : children) {
        element.call<void>("appendChild", child.render(document));
    }

    for (const auto& [key, value] : attributes) {
        if (key.compare(0, 2, "on") == 0) {
            std::string eventType = key.substr(2);
            std::transform(eventType.begin(), eventType.end(), eventType.begin(), ::tolower);
            attachEventListener(element["id"].as<std::string>().c_str(), eventType.c_str(), value.c_str());
        } else {
            element.call<void>("setAttribute", key, value);
        }
    }

    return element;
}
