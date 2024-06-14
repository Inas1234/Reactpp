#ifndef JSONVALUE_HPP
#define JSONVALUE_HPP

#include <string>
#include <unordered_map>
#include <vector>
#include <variant>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <cctype>

class JSONValue;

using JSONObject = std::unordered_map<std::string, std::shared_ptr<JSONValue>>;
using JSONArray = std::vector<std::shared_ptr<JSONValue>>;
using JSONPrimitive = std::variant<std::string, int, double, bool, std::nullptr_t>;

class JSONValue {
public:
    enum class Type { OBJECT, ARRAY, STRING, INTEGER, DOUBLE, BOOLEAN, NULLVALUE };

    JSONValue() : type(Type::NULLVALUE), value(nullptr) {}
    JSONValue(const JSONObject &object) : type(Type::OBJECT), value(object) {}
    JSONValue(const JSONArray &array) : type(Type::ARRAY), value(array) {}
    JSONValue(const std::string &str) : type(Type::STRING), value(str) {}
    JSONValue(int num) : type(Type::INTEGER), value(num) {}
    JSONValue(double num) : type(Type::DOUBLE), value(num) {}
    JSONValue(bool boolean) : type(Type::BOOLEAN), value(boolean) {}

    Type getType() const { return type; }
    JSONObject &getObject() { return std::get<JSONObject>(value); }
    JSONArray &getArray() { return std::get<JSONArray>(value); }
    std::string &getString() { return std::get<std::string>(value); }
    int getInt() { return std::get<int>(value); }
    double getDouble() { return std::get<double>(value); }
    bool getBool() { return std::get<bool>(value); }

private:
    Type type;
    std::variant<JSONObject, JSONArray, std::string, int, double, bool, std::nullptr_t> value;
};


#endif 
