#pragma once
#include "Reactpp.hpp"
#include <unordered_map>
#include <string>
#include <functional>

class State {
public:
    static State& getInstance(){
        static State instance;
        return instance;
    }

    void setState(const std::string& key, const std::string& value){
        state[key] = value;
        if(listeners.find(key) != listeners.end()){
            for(auto& listener : listeners[key]){
                listener(value);
            }
        }
    }

    std::string getState(const std::string& key){
        return state[key];
    }

    void subscribe(const std::string& key, std::function<void(const std::string&)> listener){
        listeners[key].push_back(listener);
    }

private:
    State(){}
    std::unordered_map<std::string, std::string> state;
    std::unordered_map<std::string, std::vector<std::function<void(const std::string&)>>> listeners;

};
