#pragma once
#include "JsonValue.hpp"
#include <sstream>
#include <stdexcept>


class JSONParser {
public:
    JSONValue parse(const std::string &json) {
        std::istringstream ss(json);
        return parseValue(ss);
    }

private:
    JSONValue parseValue(std::istringstream &ss) {
        char ch;
        ss >> ch;

        if (ch == '{') {
            return parseObject(ss);
        } else if (ch == '[') {
            return parseArray(ss);
        } else if (ch == '"') {
            return parseString(ss);
        } else if (isdigit(ch) || ch == '-') {
            ss.putback(ch);
            return parseNumber(ss);
        } else if (ch == 't' || ch == 'f') {
            ss.putback(ch);
            return parseBoolean(ss);
        } else if (ch == 'n') {
            ss.putback(ch);
            return parseNull(ss);
        }

        throw std::runtime_error("Invalid JSON format");
    }

    JSONValue parseObject(std::istringstream &ss) {
        JSONObject object;
        std::string key;
        char ch;

        while (ss >> ch) {
            if (ch == '}') break;
            if (ch == '"') {
                key = parseString(ss).getString();
                ss >> ch; // Skip the colon
                object[key] = std::make_shared<JSONValue>(parseValue(ss));
                ss >> ch; // Skip comma or closing brace
                if (ch == '}') break;
            }
        }

        return JSONValue(object);
    }

    JSONValue parseArray(std::istringstream &ss) {
        JSONArray array;
        char ch;

        while (ss >> ch) {
            if (ch == ']') break;
            ss.putback(ch);
            array.push_back(std::make_shared<JSONValue>(parseValue(ss)));
            ss >> ch; // Skip comma or closing bracket
            if (ch == ']') break;
        }

        return JSONValue(array);
    }

    JSONValue parseString(std::istringstream &ss) {
        std::string str;
        char ch;

        while (ss.get(ch)) {
            if (ch == '"') break;
            str += ch;
        }

        return JSONValue(str);
    }

    JSONValue parseNumber(std::istringstream &ss) {
        double number;
        ss >> number;

        if (number == static_cast<int>(number)) {
            return JSONValue(static_cast<int>(number));
        } else {
            return JSONValue(number);
        }
    }

    JSONValue parseBoolean(std::istringstream &ss) {
        std::string booleanStr;
        char ch;

        while (ss >> ch) {
            if (ch == ',' || ch == '}' || ch == ']') {
                ss.putback(ch);
                break;
            }
            booleanStr += ch;
        }

        if (booleanStr == "true") {
            return JSONValue(true);
        } else if (booleanStr == "false") {
            return JSONValue(false);
        }

        throw std::runtime_error("Invalid boolean value");
    }

    JSONValue parseNull(std::istringstream &ss) {
        std::string nullStr;
        char ch;

        while (ss >> ch) {
            if (ch == ',' || ch == '}' || ch == ']') {
                ss.putback(ch);
                break;
            }
            nullStr += ch;
        }

        if (nullStr == "null") {
            return JSONValue();
        }

        throw std::runtime_error("Invalid null value");
    }
};

