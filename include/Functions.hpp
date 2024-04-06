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
