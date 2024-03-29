/*
 * prjsv 2015, 2016
 * 2014, 2016
 * Marco Antognini
 */

#include <JSON/JSONSerialiser.hpp>

#include <algorithm>
#include <cassert>
#include <fstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <string>

namespace j
{

void eat(std::string& s, std::string const& toConsume);
Value readString(std::istream& s);
Value readNumber(std::istream& s);
Value readBoolean(std::istream& s);
void readAndLoadIdValuePair(std::istream& s, Value& obj);
Value readObject(std::istream& s);
Value readArray(std::istream& s);
Value readValue(std::istream& s);
Value readFromStream(std::istream& s);

void writeValue(std::ostream& s, Value const& v, std::size_t indent = 0);

BadPayload::BadPayload(std::string const& msg)
    : std::runtime_error(msg)
{
}

NoSuchFile::NoSuchFile(std::string const& msg)
    : std::runtime_error(msg)
{
}

void eat(std::istream& s, std::string const& toConsume)
{
    for (auto const& c : toConsume) {
        char read;
        if (!s.get(read) || c != read) {
            throw BadPayload("Expecting " + toConsume);
        }
    }
}

Value readString(std::istream& s)
{
    // Read the opening quote
    char open = '\0';
    s.get(open);
    if (open != '"') {
        // read problematic line
        std::string content;
        bool loop = true;
        do {
            char c = '\0';
            if (!s.get(c)) {
                throw BadPayload("Error while reading string");
            }

            if (c == '"') {
                loop = false;
            } else {
                content += c;
            }
        } while (loop);
        std::cout << "error reading line containing: " << content << std::endl;

        assert(false);
    }



    // Find the closing quote
    std::string content;
    bool loop = true;
    do {
        char c = '\0';
        if (!s.get(c)) {
            throw BadPayload("Error while reading string");
        }

        if (c == '"') {
            loop = false;
        } else {
            content += c;
        }
    } while (loop);

    return string(content);
}

Value readNumber(std::istream& s)
{
    // First try to read a real
    double d;
    if (s >> d) {
        return number(d);
    }

    // Restore stream and attempt to read an integer
    s.clear();
    int i;
    if (s >> i) {
        return number(i);
    }

    // Couldn't read a number..
    throw BadPayload("Couldn't read a number");
}

Value readBoolean(std::istream& s)
{
    auto next = s.peek();
    if (next == 't') {
        eat(s, "true");
        return boolean(true);
    } else if (next == 'f') {
        eat(s, "false");
        return boolean(false);
    } else {
        throw BadPayload("Invalid boolean");
    }
}

void readAndLoadIdValuePair(std::istream& s, Value& obj)
{
    s >> std::ws;

    auto id = readString(s).toString();

    s >> std::ws;

    char colon;
    s.get(colon);

    if (colon != ':') {
        throw BadPayload("Expecting colon after id in object");
    }

    s >> std::ws;

    auto v = readValue(s);

    obj.set(id, v);
}

Value readObject(std::istream& s)
{
    // Read the opening bracket
    char open = '\0';
    s.get(open);
    assert(open == '{');

    auto obj = object();

    // Remove leading spaces before peeking on the next character
    s >> std::ws;
    auto next = s.peek();

    if (!s) {
        throw BadPayload("Invalid array");
    }

    // Either read the closing bracket or the first id-value pair
    bool loop = true;
    if (next == '}') {
        loop = false;
        // Eat the bracket
        s.get();
    } else {
        // Read `id : v`
        readAndLoadIdValuePair(s, obj);
    }

    // Read a comma followed by a id-value pair, or the closing bracket
    while (loop) {
        s >> std::ws;
        char next = '\0';
        if (!s.get(next)) {
            throw BadPayload("Invalid array");
        }

        if (next == '}') {
            loop = false;
        } else if (next == ',') {
            // Read `id : v`
            readAndLoadIdValuePair(s, obj);
        } else {
            throw BadPayload(std::string("Unexpected character ") + next);
        }
    }

    return obj;
}

Value readArray(std::istream& s)
{
    // Read the opening bracket
    char open = '\0';
    s.get(open);
    assert(open == '[');

    auto arr = array();

    // Remove leading spaces before peeking on the next character
    s >> std::ws;
    auto next = s.peek();

    if (!s) {
        throw BadPayload("Invalid array");
    }

    // Either read the closing bracket or the first value
    bool loop = true;
    if (next == ']') {
        loop = false;
        // Eat the bracket
        s.get();
    } else {
        auto v = readValue(s);
        arr.add(v);
    }

    // Read a comma followed by a value, or the closing bracket
    while (loop) {
        s >> std::ws;
        char next = '\0';
        if (!s.get(next)) {
            throw BadPayload("Invalid array");
        }

        if (next == ']') {
            loop = false;
        } else if (next == ',') {
            auto v = readValue(s);
            arr.add(v);
        }
    }

    return arr;
}

Value readValue(std::istream& s)
{
    // Remove leading spaces before peeking on the first character
    s >> std::ws;
    auto first = s.peek();

    // Make sure we haven't reach EOF
    if (s) {
        if (first == '"') {
            return readString(s);
        } else if (first == 't' || first == 'f') {
            return readBoolean(s);
        } else if (first == '{') {
            return readObject(s);
        } else if (first == '[') {
            return readArray(s);
        } else {
            // Try to read a number (no other choice)
            return readNumber(s);
        }
    } else {
        throw BadPayload("No value");
    }
}

Value readFromStream(std::istream& s)
{
    // Read the main value
    auto value = readValue(s);

    // Make sure there's nothing left to process
    s >> std::ws;
    if (s.eof()) {
        return value;
    } else {
        throw BadPayload("Input contains more data than expected");
    }
}

Value readFromString(std::string const& payload)
{
    std::istringstream s(payload);

    return readFromStream(s);
}

Value readFromFile(std::string const& filepath)
{
    std::ifstream s(filepath);

    if (s.is_open()) {
        return readFromStream(s);
    } else {
        throw NoSuchFile("No such file: " + filepath);
    }
}

void writeValue(std::ostream& s, Value const& v, std::size_t indent)
{
    if (v.isString()) {
        s << "\"" << v.toString() << "\"";
    } else if (v.isNumber()) {
        s << v.toDouble();
    } else if (v.isBoolean()) {
        s << (v.toBool() ? "true" : "false");
    } else if (v.isObject()) {
        auto keys = v.keys();
        std::sort(keys.begin(), keys.end());
        s << "{";
        // Pad to use when printing a new line
        auto pad = std::string(indent * 4, ' ');
        auto extrapad = pad + std::string(4, ' ');
        if (keys.size() > 0) {
            auto last = keys.size() - 1;
            for (std::size_t i = 0; i <= last; ++i) {
                auto const& key = keys[i];
                s << "\n" << extrapad << "\"" << key << "\" : ";
                writeValue(s, v[key], indent + 1);
                if (i != last) {
                    s << ",";
                }
            }
        }
        s << "\n" << pad << "}";
    } else if (v.isArray()) {
        s << "[ ";
        if (v.size() > 0) {
            auto last = v.size() - 1;
            for (std::size_t i = 0; i <= last; ++i) {
                writeValue(s, v[i], indent + 1);
                if (i != last) {
                    s << ", ";
                }
            }
        }
        s << "]";
    }
}

std::string writeToString(Value const& value)
{
    std::ostringstream s;

    writeValue(s, value);

    return s.str();
}

void writeToFile(Value const& value, std::string const& fileapath)
{
    std::ofstream s(fileapath);

    writeValue(s, value);
}

} // j
