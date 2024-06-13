#pragma once
#include "HtmlElements.hpp"


#define UPDATE_ELEMENT_CONTENT(ID, CONTENT) \
    do { \
        std::string content_ = (CONTENT); \
        EM_ASM({ \
            document.getElementById(UTF8ToString($0)).textContent = UTF8ToString($1); \
        }, (ID), content_.c_str()); \
    } while (0)


#define SET_ELEMENT_ATTRIBUTE(ID, ATTR, VALUE) \
    do { \
        std::string value_ = (VALUE); \
        EM_ASM({ \
            document.getElementById(UTF8ToString($0)).setAttribute(UTF8ToString($1), UTF8ToString($2)); \
        }, (ID), (ATTR), value_.c_str()); \
    } while (0)


#define ADD_ELEMENT(PARENT_ID, TAG, NEW_ID) \
    EM_ASM({ \
        var parent = document.getElementById(UTF8ToString($0)); \
        var child = document.createElement(UTF8ToString($1)); \
        child.id = UTF8ToString($2); \
        parent.appendChild(child); \
    }, (PARENT_ID), (TAG), (NEW_ID));


#define REMOVE_ELEMENT(ID) \
    EM_ASM({ \
        var element = document.getElementById(UTF8ToString($0)); \
        element.parentNode.removeChild(element); \
    }, (ID));


#define ADD_EVENT_LISTENER(ID, EVENT, JS_ACTION) \
    EM_ASM({ \
        document.getElementById(UTF8ToString($0)).addEventListener(UTF8ToString($1), function() { \
            eval(UTF8ToString($2)); \
        }); \
    }, (ID), (EVENT), (JS_ACTION));


#define PREVENT_DEFAULT_ACTION(ID, EVENT) \
    EM_ASM({ \
        var element = document.getElementById(UTF8ToString($0)); \
        element.addEventListener(UTF8ToString($1), function(e) { \
            e.preventDefault(); \
        }, false); \
    }, (ID), (EVENT));

#define CSS_FILE_PATH(PATH) \
    EM_ASM({ \
        var head = document.head; \
        var link = document.createElement("link"); \
        link.rel = "stylesheet"; \
        link.type = "text/css"; \
        link.href = UTF8ToString($0); \
        head.appendChild(link); \
    }, (PATH));


#define GET_VALUE(ID) \
    EM_ASM_INT({ \
        var element = document.getElementById(UTF8ToString($0)); \
        return element.value; \
    }, (ID));


const char* getValueById(const char* elementId) {
    int bufferSize = 256;
    char* buffer = (char*)malloc(bufferSize * sizeof(char));
    if (!buffer) return nullptr; 
    EM_ASM_({
        var element = document.getElementById(UTF8ToString($0));
        if (element && element.value) {
            stringToUTF8(element.value, $1, $2);
        } else {
            setValue($1, "", "i8");
        }
    }, elementId, buffer, bufferSize);

    return buffer;
}


const char* get(const char* host, const char* path) {
    int bufferSize = 4096;
    char* buffer = (char*)malloc(bufferSize * sizeof(char));
    if (!buffer) return nullptr;
    
    EM_ASM_({
        var host = UTF8ToString($0);
        var path = UTF8ToString($1);
        var xhr = new XMLHttpRequest();
        xhr.open("GET", host + path, false);
        xhr.send();
        var response = xhr.responseText;
        stringToUTF8(response, $2, $3);
    }, host, path, buffer, bufferSize);
    
    return buffer;
}

const char* post(const char* host, const char* path, const char* data) {
    int bufferSize = 4096;
    char* buffer = (char*)malloc(bufferSize * sizeof(char));
    if (!buffer) return nullptr;
    
    EM_ASM_({
        var host = UTF8ToString($0);
        var path = UTF8ToString($1);
        var data = UTF8ToString($2);
        var xhr = new XMLHttpRequest();
        xhr.open("POST", host + path, false);
        xhr.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
        xhr.send(data);
        var response = xhr.responseText;
        stringToUTF8(response, $3, $4);
    }, host, path, data, buffer, bufferSize);
    
    return buffer;
}