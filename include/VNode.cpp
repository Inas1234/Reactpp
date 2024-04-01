#include "VNode.hpp"

std::map<std::string, std::function<void()>> VNode::eventListeners;
int VNode::callbackIdCounter = 0;

extern "C" {
    void invokeCppCallback(const char* callbackId) {
        EM_ASM({ console.log('Callback invoked for ID: ' + UTF8ToString($0)); }, callbackId);
        
        std::string callbackIdStr(callbackId); 
        auto it = VNode::eventListeners.find(callbackIdStr);
        
        if (it != VNode::eventListeners.end()) {
            std::cout << "Executing callback for ID: " << callbackIdStr << std::endl;
            it->second(); 
        } else {
            std::cerr << "Callback with ID '" << callbackIdStr << "' not found." << std::endl;
        }
    }
}

EM_JS(void, attachEventListener, (const char* elementId, const char* eventType, const char* callbackId), {
    setTimeout(function(eventTypeStr, callbackIdStr, elementIdStr) {
        console.log("Preparing to attach event listener", { eventTypeStr, callbackIdStr, elementIdStr });
        var element = document.getElementById(elementIdStr);
        if (element) {
            console.log("Element found, attaching event listener", { element, eventType: eventTypeStr });
            element.addEventListener(eventTypeStr, function() {
                console.log("Event triggered for element and callback ID", { elementId: elementIdStr, callbackId: callbackIdStr });
                Module.ccall('invokeCppCallback', 'void', ['string'], [callbackIdStr]);
            }, false); 
        } else {
            console.log("Element not found for ID:", elementIdStr);
        }

    }, 0, UTF8ToString(eventType), UTF8ToString(callbackId), UTF8ToString(elementId)); 
});

EMSCRIPTEN_BINDINGS(vnode_module){
    function("invokeCppCallback", &invokeCppCallback, allow_raw_pointers());
}



std::string VNode::addEventListener(std::string event, std::function<void()> listener) {
    std::string callbackId = "callback_" + std::to_string(callbackIdCounter++);
    eventListeners[callbackId] = listener;
    return callbackId;
}

void VNode::appendChild(VNode child) {
    children.push_back(child);
}

val VNode::render(val document) const {
    val element = document.call<val>("createElement", tag);
    element.set("textContent", textContent);

    if (!this->attributes.count("id")) {
        std::string uniqueId = "element_" + std::to_string(VNode::callbackIdCounter++); 
        element.set("id", uniqueId); 
        const_cast<std::map<std::string, std::string>&>(this->attributes).insert(std::make_pair("id", uniqueId));
    }

    for (const VNode& child : children) {
        element.call<void>("appendChild", child.render(document));
    }


    for (const auto& [key, value] : attributes) {
        if (key.find("on") == 0) {
            std::string eventType = key.substr(2);
            std::transform(eventType.begin(), eventType.end(), eventType.begin(), ::tolower);

            auto elementId = element["id"].as<std::string>(); 
            
            attachEventListener(elementId.c_str(), eventType.c_str(), value.c_str());
        }

        else {
            element.call<void>("setAttribute", key, value);
        }
    }



    return element;
}

