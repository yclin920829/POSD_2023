#pragma once

class JsonVisitor {
public:
    virtual void visitJsonObject(JsonObject * obj) = 0;
    virtual void visitStringValue(StringValue * val) = 0;
};