#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "VNode.hpp"

#define docBegin val document = val::global("document")
#define docEnd(node) val element = node.render(document); \
    document["body"].call<void>("appendChild", element);


class Element {
public:
    Element(std::string tag) : node(tag) {}
    
    Element& text(std::string textContent) {
        node.setTextContent(textContent);
        return *this;
    }
    
    Element& child(Element child) {
        node.appendChild(child.node);
        return *this;
    }
    
    Element& attr(std::string key, std::string value) {
        node.setAttribute(key, value);
        return *this;
    }
    
    Element& on(std::string event, std::function<void()> listener) {
        std::string callbackId = VNode::addEventListener(event, listener);
        
        node.setAttribute("on" + event, callbackId);
        
        return *this;
    }        




    VNode getNode() const { return node; }

private:
    VNode node;
};