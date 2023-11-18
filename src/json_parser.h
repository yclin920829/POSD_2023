#pragma once

#include <string>
#include <regex>

#include "./json_scanner.h"
#include "./json_builder.h"
#include "./json_object.h"
#include "./string_value.h"

class JsonParser {
public:
    JsonParser(JsonScanner * scanner, JsonBuilder * builder): _scanner(scanner), _builder(builder) {}

    void parse() {
        std::string key = "";
        while (!_scanner->isDone()) {
            char token = _scanner->next();
            if(token == ' ') {
                continue;
            } else if (token == '{') {
                _builder->buildObject(key);
            } else if (token == '"') {
                std::string value;
                token = _scanner->next();
                while(token != '"') {
                    value += token;
                    token = _scanner->next();
                }
                token = _scanner->next();

                while (token == ' ') {
                    token = _scanner->next();
                }
                
                if(token == ':') {
                    key = value;
                } 
                else if(token == ',') {
                    _builder->buildValue(key, value);
                } else if (token == '}') {
                    _builder->buildValue(key, value);
                    _builder->endObject();
                    token = _scanner->next();
                }
            }
            else if (token == '}') {
                _builder->endObject();
            }
        }
    }

    JsonObject * getJsonObject() {
        return _builder->getJsonObject();
    }

    void setInput(std::string input) {
        _scanner->setInput(input);
    }

private:
    JsonScanner * _scanner;
    JsonBuilder * _builder;
};