
/*
This file is part of OGS: https://github.com/ogstudio/ogs

Copyright (C) 2019 Opensource Game Studio

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef OGS_H
#define OGS_H

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include <cstdarg>

#include <map>

#include <algorithm>
#include <osgGA/GUIEventHandler>

#include <iostream>

#include <cstdarg>

#include <osgGA/TrackballManipulator>

#include <sol.hpp>

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

#include <emscripten.h>
#include <SDL2/SDL.h>

#include "api.lua.h"

#include <osg/MatrixTransform>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/NodeVisitor>

#include <osg/Program>

#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>

#include <osg/MatrixTransform>

#include <osg/MatrixTransform>

#include <functional>


#define SCRIPT_ENVIRONMENT_CLIENT_CALL(...) \
    [=](const std::string &key, const std::vector<std::string> &values) { \
        __VA_ARGS__ \
    }
#define SCRIPT_ENVIRONMENT_LOG_PREFIX "script::Environment(%p) %s"
#define SCRIPT_ENVIRONMENT_LOG(...) \
    log::logprintf( \
        SCRIPT_ENVIRONMENT_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
#define MAIN_APPLICATION_LOG_PREFIX "main::Application(%p) %s"
#define MAIN_APPLICATION_LOG(...) \
    log::logprintf( \
        MAIN_APPLICATION_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )
#define MAIN_EXAMPLE_LOG_PREFIX "main::Example(%p) %s"
#define MAIN_EXAMPLE_LOG(...) \
    log::logprintf( \
        MAIN_EXAMPLE_LOG_PREFIX, \
        this, \
        format::printfString(__VA_ARGS__).c_str() \
    )

namespace lib
{

/*

This is a copy of base64.h from https://github.com/tkislan/base64
 
Copyright (C) 2013 Tomas Kislan
Copyright (C) 2013 Adam Rudd

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

const char kBase64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

class Base64 {
 public:
  static bool Encode(const std::string &in, std::string *out) {
    int i = 0, j = 0;
    size_t enc_len = 0;
    unsigned char a3[3];
    unsigned char a4[4];

    out->resize(EncodedLength(in));

    int input_len = in.size();
    std::string::const_iterator input = in.begin();

    while (input_len--) {
      a3[i++] = *(input++);
      if (i == 3) {
        a3_to_a4(a4, a3);

        for (i = 0; i < 4; i++) {
          (*out)[enc_len++] = kBase64Alphabet[a4[i]];
        }

        i = 0;
      }
    }

    if (i) {
      for (j = i; j < 3; j++) {
        a3[j] = '\0';
      }

      a3_to_a4(a4, a3);

      for (j = 0; j < i + 1; j++) {
        (*out)[enc_len++] = kBase64Alphabet[a4[j]];
      }

      while ((i++ < 3)) {
        (*out)[enc_len++] = '=';
      }
    }

    return (enc_len == out->size());
  }

  static bool Encode(const char *input, size_t input_length, char *out, size_t out_length) {
    int i = 0, j = 0;
    char *out_begin = out;
    unsigned char a3[3];
    unsigned char a4[4];

    size_t encoded_length = EncodedLength(input_length);

    if (out_length < encoded_length) return false;

    while (input_length--) {
      a3[i++] = *input++;
      if (i == 3) {
        a3_to_a4(a4, a3);

        for (i = 0; i < 4; i++) {
          *out++ = kBase64Alphabet[a4[i]];
        }

        i = 0;
      }
    }

    if (i) {
      for (j = i; j < 3; j++) {
        a3[j] = '\0';
      }

      a3_to_a4(a4, a3);

      for (j = 0; j < i + 1; j++) {
        *out++ = kBase64Alphabet[a4[j]];
      }

      while ((i++ < 3)) {
        *out++ = '=';
      }
    }

    return (out == (out_begin + encoded_length));
  }

  static bool Decode(const std::string &in, std::string *out) {
    int i = 0, j = 0;
    size_t dec_len = 0;
    unsigned char a3[3];
    unsigned char a4[4];

    int input_len = in.size();
    std::string::const_iterator input = in.begin();

    out->resize(DecodedLength(in));

    while (input_len--) {
      if (*input == '=') {
        break;
      }

      a4[i++] = *(input++);
      if (i == 4) {
        for (i = 0; i <4; i++) {
          a4[i] = b64_lookup(a4[i]);
        }

        a4_to_a3(a3,a4);

        for (i = 0; i < 3; i++) {
          (*out)[dec_len++] = a3[i];
        }

        i = 0;
      }
    }

    if (i) {
      for (j = i; j < 4; j++) {
        a4[j] = '\0';
      }

      for (j = 0; j < 4; j++) {
        a4[j] = b64_lookup(a4[j]);
      }

      a4_to_a3(a3,a4);

      for (j = 0; j < i - 1; j++) {
        (*out)[dec_len++] = a3[j];
      }
    }

    return (dec_len == out->size());
  }

  static bool Decode(const char *input, size_t input_length, char *out, size_t out_length) {
    int i = 0, j = 0;
    char *out_begin = out;
    unsigned char a3[3];
    unsigned char a4[4];

    size_t decoded_length = DecodedLength(input, input_length);

    if (out_length < decoded_length) return false;

    while (input_length--) {
      if (*input == '=') {
        break;
      }

      a4[i++] = *(input++);
      if (i == 4) {
        for (i = 0; i <4; i++) {
          a4[i] = b64_lookup(a4[i]);
        }

        a4_to_a3(a3,a4);

        for (i = 0; i < 3; i++) {
          *out++ = a3[i];
        }

        i = 0;
      }
    }

    if (i) {
      for (j = i; j < 4; j++) {
        a4[j] = '\0';
      }

      for (j = 0; j < 4; j++) {
        a4[j] = b64_lookup(a4[j]);
      }

      a4_to_a3(a3,a4);

      for (j = 0; j < i - 1; j++) {
        *out++ = a3[j];
      }
    }

    return (out == (out_begin + decoded_length));
  }

  static int DecodedLength(const char *in, size_t in_length) {
    int numEq = 0;

    const char *in_end = in + in_length;
    while (*--in_end == '=') ++numEq;

    return ((6 * in_length) / 8) - numEq;
  }

  static int DecodedLength(const std::string &in) {
    int numEq = 0;
    int n = in.size();

    for (std::string::const_reverse_iterator it = in.rbegin(); *it == '='; ++it) {
      ++numEq;
    }

    return ((6 * n) / 8) - numEq;
  }

  inline static int EncodedLength(size_t length) {
    return (length + 2 - ((length + 2) % 3)) / 3 * 4;
  }

  inline static int EncodedLength(const std::string &in) {
    return EncodedLength(in.length());
  }

  inline static void StripPadding(std::string *in) {
    while (!in->empty() && *(in->rbegin()) == '=') in->resize(in->size() - 1);
  }

 private:
  static inline void a3_to_a4(unsigned char * a4, unsigned char * a3) {
    a4[0] = (a3[0] & 0xfc) >> 2;
    a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
    a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
    a4[3] = (a3[2] & 0x3f);
  }

  static inline void a4_to_a3(unsigned char * a3, unsigned char * a4) {
    a3[0] = (a4[0] << 2) + ((a4[1] & 0x30) >> 4);
    a3[1] = ((a4[1] & 0xf) << 4) + ((a4[2] & 0x3c) >> 2);
    a3[2] = ((a4[2] & 0x3) << 6) + a4[3];
  }

  static inline unsigned char b64_lookup(unsigned char c) {
    if(c >='A' && c <='Z') return c - 'A';
    if(c >='a' && c <='z') return c - 71;
    if(c >='0' && c <='9') return c + 4;
    if(c == '+') return 62;
    if(c == '/') return 63;
    return 255;
  }
};

}

namespace ogs
{

namespace core
{

class Reporter
{
    public:
        typedef std::function<void()> Callback;

    public:
        Reporter() { }

        std::string name;

        void addCallback(Callback callback, const std::string &name = "")
        {
            // Work around callback reactivation happenning
            // before `report()` call.
            if (this->reactivateInactiveCallback(name))
            {
                //CORE_REPORTER_LOG("reactivated callback named '%s'", name.c_str());
                return;
            }

            this->callbacks.push_back({callback, name});
            //CORE_REPORTER_LOG("added callback named '%s'", name.c_str());
        }

        void addOneTimeCallback(Callback callback)
        {
            this->oneTimeCallbacks.push_back(callback);
        }

        void removeCallback(const std::string &name)
        {
            // This call only deactivates a callback for
            // later removal that happens during next report() call.
            for (auto callback : this->callbacks)
            {
                if (callback.name == name)
                {
                    this->inactiveCallbackNames.push_back(name);
                }
            }
        }

        void report()
        {
            this->removeInactiveCallbacks();

            // Call normal callbacks.
            for (auto callback : this->callbacks)
            {
                callback.callback();
            }

            // Iterate over duplicated one-time callbacks.
            auto oneTimeCallbacks = this->oneTimeCallbacks; 
            // Remove one-time callbacks.
            this->oneTimeCallbacks.clear();
            
            // Call one-time callbacks.
            for (auto callback : oneTimeCallbacks)
            {
                callback();
            }
        }

    private:
        struct NamedCallback
        {
            Callback callback;
            std::string name;
        };

        std::vector<NamedCallback> callbacks;
        std::vector<std::string> inactiveCallbackNames;
        std::vector<Callback> oneTimeCallbacks;

    private:
        bool reactivateInactiveCallback(const std::string &name)
        {
            auto inactives = &this->inactiveCallbackNames;
            auto it = std::find(inactives->begin(), inactives->end(), name);
            if (it != inactives->end())
            {
                inactives->erase(it);
                return true;
            }
            return false;
        }

        void removeInactiveCallbacks()
        {
            // Loop through the names of inactive callbacks.
            auto name = this->inactiveCallbackNames.begin();
            for (; name != this->inactiveCallbackNames.end(); ++name)
            {
                // Loop through callbacks to find matching name.
                auto callback = this->callbacks.begin();
                for (; callback != this->callbacks.end(); ++callback)
                {
                    if (callback->name == *name)
                    {
                        // Remove matching callback.
                        this->callbacks.erase(callback);
                        break;
                    }
                }
            }
            // Clear the list of inactive callbacks.
            this->inactiveCallbackNames.clear();
        }
};

}

namespace format
{

//! Decode base64 string representation into a string (of bytes)

//! \return an empty string if decoding failed
std::string base64Decode(const std::string &input)
{
    std::string output;
    lib::Base64::Decode(input, &output);
    return output;
}
//! Split a string into a list of strings using single character.

//! \param `text` contains the string to split
//! \param `delimiter` contains single character used to split `text` string
//! \param `maxSplit` larger than `0` restricts the number of splits
std::vector<std::string> splitString(
    const std::string &text,
    const char *delimiter,
    size_t maxSplit = 0 
) {
    size_t splitCount = 0;
    size_t pos = 0;
    bool proceed = true;
    bool hasChar = false;
    std::vector<std::string> result;

    while (proceed)
    {
        // 1. Is this split allowed?
        bool isAllowed = true;
        if (
            maxSplit &&
            (splitCount >= maxSplit)
        ) {
            isAllowed = false;
        }
        // 2. The remaining string contains the delimiter?
        auto id = text.find(delimiter, pos);
        bool hasDelimiter = (id != std::string::npos);

        if (isAllowed && hasDelimiter)
        {
            auto segment = text.substr(pos, id - pos);
            result.push_back(segment);
            pos = id + 1;
            hasChar = true;
            ++splitCount;
        }
        else
        {
            auto segment = text.substr(pos, text.length());
            result.push_back(segment);
            proceed = false;
            // If delimiting char has not been found,
            // the result should only contain original string.
        }
    }
    return result;
}
//! Combine several strings into one
std::string stringsToString(
    const std::vector<std::string> &strings,
    const std::string &separator = ", "
) {
    std::string result;
    for (auto item : strings)
    {
        // The first item.
        if (result.empty())
        {
            result = item;
        }
        // The rest ones.
        else
        {
            result += separator + item;
        }
    }

    return result;
}
//! Construct a string using printf-like syntax.

//! NOTE Only 1024 characters fit in.
std::string printfString(const char *fmt, ...)
{
    const int PRINTF_STRING_MAX_STRLEN = 1024;
    va_list args;
    char msg[PRINTF_STRING_MAX_STRLEN];
    va_start(args, fmt);
    vsnprintf(msg, PRINTF_STRING_MAX_STRLEN, fmt, args);
    va_end(args);
    return msg;
}
typedef std::map<std::string, std::string> Parameters;
//! Convert query parameters starting after `?` that are in the form of `key=value` to parameters.
Parameters urlToParameters(int argc, char *argv[])
{
    Parameters parameters;

    // No URL has been provided. Nothing to parse.
    if (argc < 3)
    {
        return parameters;
    }

    std::string query = argv[2];
    auto options = format::splitString(query, "&");

    for (auto option : options)
    {
        // Only split once.
        auto keyAndValue = format::splitString(option, "=", 1);
        if (keyAndValue.size() == 2)
        {
            auto key = keyAndValue[0];
            auto value = keyAndValue[1];
            parameters[key] = value;
        }
    }

    // Create "base" parameter to contain
    // everything before `? and the search string` plus `/..`
    std::string url(argv[1]);
    parameters["base"] = url + "/..";
    // Use substring if there's `?` sign.
    if (query.length())
    {
        auto pos = url.find("?");
        parameters["base"] = url.substr(0, pos) + "/..";
    }

    return parameters;
}

}

namespace log
{

//! Cross-platform logging function.
void log(const char *message)
{
    std::cout << message << std::endl;
}
//! Cross-platform logging function with printf-like syntax.

//! NOTE Only 1024 characters fit in.
void logprintf(const char *fmt, ...)
{
    const int PRINTF_STRING_MAX_STRLEN = 1024;
    va_list args;
    char msg[PRINTF_STRING_MAX_STRLEN];
    va_start(args, fmt);
    vsnprintf(msg, PRINTF_STRING_MAX_STRLEN, fmt, args);
    va_end(args);
    log(msg);
}

}

namespace input
{

//! NOTE Mobile platforms only have LEFT button.
enum MOUSE_BUTTON
{
    MOUSE_BUTTON_NONE,
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE,
};

//! Convert OpenSceneGraph key index to mouse button enum value.
MOUSE_BUTTON indexToMouseButton(int index)
{
    switch (index)
    {
        case osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON:
            return MOUSE_BUTTON_LEFT;
        case osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON:
            return MOUSE_BUTTON_MIDDLE;
        case osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON:
            return MOUSE_BUTTON_RIGHT;
        default:
            return MOUSE_BUTTON_NONE;
    }
}

//! Convert mouse button enum value to string representation.
const char *mouseButtonToString(MOUSE_BUTTON button)
{
    switch (button)
    {
        case MOUSE_BUTTON_LEFT:
            return "MOUSE_BUTTON_LEFT";
        case MOUSE_BUTTON_RIGHT:
            return "MOUSE_BUTTON_RIGHT";
        case MOUSE_BUTTON_MIDDLE:
            return "MOUSE_BUTTON_MIDDLE";
        default:
            return "MOUSE_BUTTON_NONE";
    }
}
//! Handle OpenSceneGraph mouse events.
class Mouse : public osgGA::GUIEventHandler
{
    public:
        Mouse() : position(0, 0) { }

        // Current mouse position.
        osg::Vec2f position;
        core::Reporter positionChanged;

        // Currently pressed mouse buttons.
        std::vector<MOUSE_BUTTON> pressedButtons;
        core::Reporter pressedButtonsChanged;

        bool handle(
            const osgGA::GUIEventAdapter &eventAdapter,
            osgGA::GUIActionAdapter &actionAdapter,
            osg::Object *object,
            osg::NodeVisitor *visitor
        ) override {
            // Report mouse position if changed.
            osg::Vec2f pos(eventAdapter.getX(), eventAdapter.getY());
            if (this->position != pos)
            {
                this->position = pos;
                this->positionChanged.report();
                //INPUT_MOUSE_LOG("Position: '%f x %f'", pos.x(), pos.y());
            }

            // Process pressed buttons.
            bool isPressed = false;
            if (eventAdapter.getEventType() == osgGA::GUIEventAdapter::PUSH)
            {
                isPressed = true;
            }
            else if (eventAdapter.getEventType() == osgGA::GUIEventAdapter::RELEASE)
            {
                // Do nothing.
            }
            else
            {
                return true;
            }
            auto button = indexToMouseButton(eventAdapter.getButton());
            this->setButtonState(button, isPressed);
            return true;
        }

    private:
        void setButtonState(MOUSE_BUTTON button, bool state)
        {
            //INPUT_MOUSE_LOG("setButtonState(%d, %d)", button, state);
            auto &buttons = this->pressedButtons;
            auto btn = std::find(buttons.begin(), buttons.end(), button);
            // Button is already pressed.
            if (btn != buttons.end())
            {
                // Release button.
                if (!state)
                {
                    buttons.erase(
                        std::remove(buttons.begin(), buttons.end(), button),
                        buttons.end()
                    );
                    this->pressedButtonsChanged.report();
                    //INPUT_MOUSE_LOG("Released button '%d'", button);
                }
            }
            // Button is not pressed.
            else
            {
                // Push button.
                if (state)
                {
                    buttons.push_back(button);
                    this->pressedButtonsChanged.report();
                    //INPUT_MOUSE_LOG("Pressed button '%d'", button);
                }
            }
        }
};

}

namespace render
{

//! This class forces the use of VBO.
class VBOSetupVisitor : public osg::NodeVisitor
{
    public:
        VBOSetupVisitor() :
            osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) { }

        virtual void apply(osg::Geode &geode)
        {
            for (auto i = 0; i < geode.getNumDrawables(); ++i)
            {
                osg::Geometry *geom =
                    dynamic_cast<osg::Geometry*>(geode.getDrawable(i));
                if (geom)
                {
                    geom->setUseVertexBufferObjects(true);
                }
            }
            NodeVisitor::apply(geode);
        }
};

osg::Program *createShaderProgram(
    const std::string &vertexShader,
    const std::string &fragmentShader
) {
    // Load shaders.
    osg::Shader *vs = new osg::Shader(osg::Shader::VERTEX, vertexShader);
    osg::Shader *fs = new osg::Shader(osg::Shader::FRAGMENT, fragmentShader);
    // Compile shaders and compose shader program.
    osg::ref_ptr<osg::Program> prog = new osg::Program;
    prog->addShader(vs);
    prog->addShader(fs);
    return prog.release();
}

}

namespace resource
{

//! Resource container.
struct Resource
{
    Resource(
        const std::string &group,
        const std::string &name,
        const std::string &contents
    ) :
        group(group),
        name(name),
        contents(contents)
    { }

    Resource(
        const std::string &group,
        const std::string &name,
        const unsigned char *contents,
        unsigned int len
    ) :
        group(group),
        name(name)
    {
        this->contents =
            std::string(
                reinterpret_cast<const char *>(contents),
                len
            );
    }

    std::string group;
    std::string name;
    std::string contents;
};

}

namespace scene
{

osg::MatrixTransform *createShape(osg::Shape *shape)
{
    auto hints = new osg::TessellationHints;
    hints->setDetailRatio(0.5);
    auto geode = new osg::Geode();
    geode->addDrawable(new osg::ShapeDrawable(shape, hints));
    osg::ref_ptr<osg::MatrixTransform> node = new osg::MatrixTransform;
    node->addChild(geode);
    return node.release();
}
osg::MatrixTransform *createSphere(float radius)
{
    auto sphere = new osg::Sphere(osg::Vec3f(0, 0, 0), radius);
    return createShape(sphere);
}
//! Convert from degrees to quaternion.
osg::Quat degreesToQuaternion(const osg::Vec3f &degrees)
{
    osg::Quat q;
    q.makeRotate(
        osg::DegreesToRadians(degrees.x()), osg::Vec3(1, 0, 0),
        osg::DegreesToRadians(degrees.y()), osg::Vec3(0, 1, 0),
        osg::DegreesToRadians(degrees.z()), osg::Vec3(0, 0, 1)
    );
    return q;
}
//! Pick a node at the specified position using camera's point of view.

// \param excludedNodeMask Take the node into consideration only if it excludes specified mask.
osg::Node *nodeAtPosition(
    const osg::Vec2f &position,
    osg::Camera *camera,
    unsigned int excludedNodeMask
) {
    // Find intersections.
    osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
        new osgUtil::LineSegmentIntersector(
            osgUtil::Intersector::WINDOW,
            position.x(),
            position.y()
        );
    osgUtil::IntersectionVisitor iv(intersector.get());
    camera->accept(iv);

    // No intersections found.
    if (!intersector->containsIntersections())
    {
        return 0;
    }

    // Get closest intersection.
    auto intersection = intersector->getFirstIntersection();
    for (auto node : intersection.nodePath)
    {
        // Make sure node mask is excluded.
        if ((node->getNodeMask() & excludedNodeMask) != excludedNodeMask)
        {
            return node;
        }
    }

    return 0;
}
osg::Vec3f quaternionToDegrees(const osg::Quat &quaternion)
{
    double q0 = quaternion.x();
    double q1 = quaternion.y();
    double q2 = quaternion.z();
    double q3 = quaternion.w();
    
    //double sq0 = q0 * q0;
    double sq1 = q1 * q1;
    double sq2 = q2 * q2;
    double sq3 = q3 * q3;
    
    double term1 = 2*(q0*q1 + q2*q3);
    double term2 = 1 - 2 * (sq1 + sq2);
    double term3 = 2 * (q0*q2 - q3*q1);
    double term4 = 2 * (q0*q3 + q1*q2);
    double term5 = 1 - 2 * (sq2 + sq3);

    double z = atan2(term1, term2);
    double y = asin(term3);
    double x = atan2(term4, term5);

    osg::Vec3f result(x * 180.0 / M_PI, y * 180.0 / M_PI, z * 180.0 / M_PI);
    // Fix for X when Y = 0.
    result.x() = 180 - result.x();
    // Fix for Z when Y = 0.
    if (result.z() < 0)
    {
        result.z() = 360 + result.z();
    }
    return result;
}
//! Get node position.
//! NOTE Only works for non-rotated/scaled nodes.
osg::Vec3f simplePosition(osg::MatrixTransform *node)
{
    return node->getMatrix().getTrans();
}

//! Set node position.
//! NOTE Only works for non-rotated/scaled nodes.
void setSimplePosition(osg::MatrixTransform *node, const osg::Vec3f &position)
{
    auto matrix = node->getMatrix();
    node->setMatrix(
        osg::Matrix::scale(matrix.getScale()) *
        osg::Matrix::rotate(matrix.getRotate()) *
        osg::Matrix::translate(position)
    );
}
//! Get node rotation.
osg::Vec3f simpleRotation(osg::MatrixTransform *node)
{
    auto quat = node->getMatrix().getRotate();
    return quaternionToDegrees(quat);
}

//! Set node rotation.
void setSimpleRotation(osg::MatrixTransform *node, const osg::Vec3f &rotation)
{
    osg::Quat quat = degreesToQuaternion(rotation);
    node->setMatrix(
        osg::Matrix::scale(node->getMatrix().getScale()) *
        osg::Matrix::rotate(quat) *
        osg::Matrix::translate(node->getMatrix().getTrans())
    );
}

}

namespace script
{

//! Interface to scriptable entity represented in Lua.
class EnvironmentClient
{
    public:
        EnvironmentClient() : call(nullptr) { }
        ~EnvironmentClient() { }

        // 'call' method/callback:
        // * accepts key and a list of values
        // * returns a list of values
        typedef
            std::function<
                std::vector<std::string> (
                    const std::string &,
                    const std::vector<std::string> &
                )
            > CallbackCall;
        CallbackCall call;
};
//! Hub for entities represented in Lua.
class Environment
{
    public:
        Environment() { }

        void addClient(
            EnvironmentClient *client,
            const std::vector<std::string> &keys
        ) {
            // Map clients to keys.
            for (auto key : keys)
            {
                this->keys[key] = client;
            }
        }

        //! Execute a call by finding suitable client to delegate the call to.
        std::vector<std::string> call(
            const std::string &key,
            const std::vector<std::string> &values
        ) {
            if (this->isVerbose)
            {
                SCRIPT_ENVIRONMENT_LOG(
                    "call(%s, {%s})",
                    key.c_str(),
                    format::stringsToString(values).c_str()
                );
            }

            // Make sure there is a client that responds to the key.
            auto it = this->keys.find(key);
            if (it == this->keys.end())
            {
                SCRIPT_ENVIRONMENT_LOG(
                    "ERROR Could not find a client that responds to '%s' key",
                    key.c_str()
                );
                return { };
            }

            // Make sure the client has callback assigned.
            auto client = it->second;
            if (!client->call)
            {
                SCRIPT_ENVIRONMENT_LOG(
                    "ERROR Could not process '%s' key because the client "
                    "does not have a callback assigned",
                    key.c_str()
                );
                return { };
            }

            // Perform safe call.
            try {
                return client->call(key, values);
            }
            catch (const std::exception &e)
            {
                SCRIPT_ENVIRONMENT_LOG(
                    "ERROR Client execution for key '%s' failed: '%s'",
                    key.c_str(),
                    e.what()
                );
                return { };
            }
        }

        //! Log all calls when verbose.
        void setVerbose(bool state)
        {
            this->isVerbose = state;
        }

    private:
        std::map<std::string, EnvironmentClient *> keys;
        bool isVerbose = false;
};

}

namespace main
{

class Nodes
{
    public:
        Nodes()
        {

    this->setupRoot();
    
        }
        ~Nodes()
        {

        }

    private:
        std::map<std::string, osg::ref_ptr<osg::MatrixTransform> > nodes;

    private:
        render::VBOSetupVisitor vbo;
    
 
    public:
        osg::MatrixTransform *createSphere(
            const std::string &name,
            float radius
        ) {
            auto node = scene::createSphere(radius);
            node->setName(name);
            this->nodes[name] = node;
    
            node->accept(this->vbo);
            return node;
        }
    public:
        osg::MatrixTransform *node(const std::string &name)
        {
            auto it = this->nodes.find(name);
    
            // Return valid node.
            if (it != this->nodes.end())
            {
                return it->second.get();
            }
    
            // Found noting.
            return 0;
        }
 
    private:
        void setupRoot()
        {
            auto root = new osg::MatrixTransform;
            this->nodes["root"] = root;
        }
};

class Application
{
    public:
        Application(const std::string &name)
        {

            this->setupRendering();
            
            this->setupCameraManipulator();
            
            this->setupMouse();
            
            this->setupNodes();
            
            this->setupLua();
            
            this->setupScripting();
            
        }
        ~Application()
        {

            this->tearScriptingDown();
            
            this->tearLuaDown();
            
            this->tearNodesDown();
            
            this->tearMouseDown();
            
            this->tearRenderingDown();
            
        }

    public:
        osg::Camera *camera()
        {
            return this->viewer->getCamera();
        }
    public:
        void frame()
        {
            this->viewer->frame();
        }
    private:
        bool fingerEventsDetected = false;
    public:
        bool handleEvent(const SDL_Event &e)
        {
            // Get event queue.
            osgViewer::GraphicsWindow *gw =
                dynamic_cast<osgViewer::GraphicsWindow *>(
                    this->viewer->getCamera()->getGraphicsContext());
            if (!gw)
            {
                return false;
            }
            osgGA::EventQueue &queue = *(gw->getEventQueue());
    
            // Detect finger events.
            if (
                e.type == SDL_FINGERMOTION ||
                e.type == SDL_FINGERDOWN ||
                e.type == SDL_FINGERUP
            ) {
                this->fingerEventsDetected = true;
            }
            // Handle mouse events unless finger events are detected.
            if (!this->fingerEventsDetected)
            {
                return this->handleMouseEvent(e, queue);
            }
            // Handle finger events.
            return this->handleFingerEvent(e, queue);
        }
    
    private:
        bool handleFingerEvent(const SDL_Event &e, osgGA::EventQueue &queue)
        {
            int absX = this->windowWidth * e.tfinger.x;
            int absY = this->windowHeight * e.tfinger.y;
            auto correctedY = -(this->windowHeight - absY);
            switch (e.type)
            {
                case SDL_FINGERMOTION:
                    queue.mouseMotion(absX, correctedY);
                    return true;
                case SDL_FINGERDOWN: 
                    // NOTE We pass `1` to denote LMB.
                    queue.mouseButtonPress(absX, correctedY, 1);
                    return true;
                case SDL_FINGERUP:
                    // NOTE We pass `1` to denote LMB.
                    queue.mouseButtonRelease(absX, correctedY, 1);
                    return true;
                default:
                    break;
            }
            return false;
        }
    
        bool handleMouseEvent(const SDL_Event &e, osgGA::EventQueue &queue)
        {
            switch (e.type)
            {
                case SDL_MOUSEMOTION: {
                    auto correctedY = -(this->windowHeight - e.motion.y);
                    queue.mouseMotion(e.motion.x, correctedY);
                    return true;
                }
                case SDL_MOUSEBUTTONDOWN: {
                    auto correctedY = -(this->windowHeight - e.button.y);
                    queue.mouseButtonPress(e.button.x, correctedY, e.button.button);
                    return true;
                }
                case SDL_MOUSEBUTTONUP: {
                    auto correctedY = -(this->windowHeight - e.button.y);
                    queue.mouseButtonRelease(e.button.x, correctedY, e.button.button);
                    return true;
                }
                default:
                    break;
            }
            return false;
        }
    public:
        void run()
        {
            while (!this->viewer->done())
            {
                this->frame();
            }
        }
    private:
        int windowWidth;
        int windowHeight;
    public:
        void setupWindow(int width, int height)
        {
            this->viewer->setUpViewerAsEmbeddedInWindow(0, 0, width, height);
            this->windowWidth = width;
            this->windowHeight = height;
        }
    private:
        SDL_Window *sdlWindow = 0;
    public:
        bool setupWindow(
            const std::string &title,
            int width,
            int height
        ) {
            this->configureSDLGLContext();
            this->sdlWindow =
                SDL_CreateWindow(
                    title.c_str(),
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    width,
                    height,
                    SDL_WINDOW_OPENGL
                );
            if (!this->sdlWindow)
            {
                MAIN_APPLICATION_LOG(
                    "ERROR Could not create SDL window: '%s'\n",
                    SDL_GetError()
                );
                return false;
            }
    
            SDL_GL_CreateContext(this->sdlWindow);
            this->setupWindow(width, height);
    
            return true;
        }
        void configureSDLGLContext()
        {
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        }

    private:
        osg::ref_ptr<osgGA::TrackballManipulator> cameraManip;
        void setupCameraManipulator()
        {
            // Create manipulator: CRITICAL for mobile and web.
            this->cameraManip = new osgGA::TrackballManipulator;
            this->viewer->setCameraManipulator(this->cameraManip);
    
            // Reset camera rotation.
            osg::Vec3d pos;
            osg::Quat q;
            this->cameraManip->getTransformation(pos, q);
            osg::Vec3d rot(0, 0, 0);
            q = scene::degreesToQuaternion(rot);
            this->cameraManip->setTransformation(pos, q);
        }
    public:
        osgGA::TrackballManipulator *cameraManipulator()
        {
            return this->cameraManip;
        }
    private:
        sol::state *lua;
        void setupLua()
        {
            this->lua = new sol::state;
            this->lua->open_libraries();
        }
        void tearLuaDown()
        {
            delete this->lua;
        }
    public:
        void executeLuaScript(
            const std::string &name,
            const std::string &contents
        ) {
            try {
                this->lua->script(contents);
                MAIN_EXAMPLE_LOG(
                    "Executed Lua script '%s'(%u)",
                    name.c_str(),
                    contents.size()
                );
            }
            catch (const std::exception &e)
            {
                MAIN_EXAMPLE_LOG(
                    "ERROR Could not execute Lua script '%s'(%u): '%s'",
                    name.c_str(),
                    contents.size(),
                    e.what()
                );
            }
        }
    public:
        osg::ref_ptr<input::Mouse> mouse;
    private:
        void setupMouse()
        {
            // Create mouse events' handler.
            this->mouse = new input::Mouse;
            // Register it.
            this->viewer->addEventHandler(this->mouse);
        }
        void tearMouseDown()
        {
            // This also removes `mouse` instance.
            this->viewer->removeEventHandler(this->mouse);
        }
    public:
        Nodes *nodes;
    private:
        void setupNodes()
        {
            this->nodes = new Nodes;
    
            // Set pool's root node to viewer.
            auto root = this->nodes->node("root");
            this->viewer->setSceneData(root);
        }
        void tearNodesDown()
        {
            this->viewer->setSceneData(0);
            delete this->nodes;
        }
    private:
        osgViewer::Viewer *viewer;
        void setupRendering()
        {
            // Create OpenSceneGraph viewer.
            this->viewer = new osgViewer::Viewer;
            // Use single thread: CRITICAL for mobile and web because
            // there were are issues with multiple threads for OpenSceneGraph there.
            this->viewer->setThreadingModel(osgViewer::ViewerBase::SingleThreaded);
            // Create manipulator: CRITICAL for mobile and web to focus on the
            // nodes in the scene.
            this->viewer->setCameraManipulator(new osgGA::TrackballManipulator);
        }
        void tearRenderingDown()
        {
            delete this->viewer;
        }
    public:
        script::Environment *environment;
    private:
        std::vector<script::EnvironmentClient *> clients;
    
        void setupScripting()
        {
            this->environment = new script::Environment;
    
            // Register Environment instance.
            (*this->lua)["ENV"] = this->environment;
    
            // Register Environment class.
            this->lua->new_usertype<script::Environment>(
                "Environment",
                // 'setVerbose' method.
                "setVerbose",
                [](script::Environment &env, bool state)
                {
                    env.setVerbose(state);
                },
                // 'addClient' method.
                "addClient",
                [](script::Environment &env, script::EnvironmentClient *client, sol::nested<std::vector<std::string> > keys)
                {
                    env.addClient(client, keys);
                },
                // 'call' method.
                "call",
                [](script::Environment &env, const std::string &key, sol::nested<std::vector<std::string> > values)
                {
                    return env.call(key, values);
                }
            );
    
            // Register EnvironmentClient class.
            this->lua->new_usertype<script::EnvironmentClient>(
                "EnvironmentClient",
                // 'call' method.
                "call",
                sol::property(
                    [](script::EnvironmentClient &ec, sol::function luaCallback)
                    {
                        ec.call =
                            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                                sol::nested<std::vector<std::string> > result =
                                    luaCallback(key, sol::as_table(values));
                                return std::move(result.source);
                            );
                    }
                )
            );
        }
        void tearScriptingDown()
        {
            delete this->environment;
        }
    public:
        void registerScriptCallback(
            const std::string &key,
            script::EnvironmentClient::CallbackCall callback
        ) {
            auto client = new script::EnvironmentClient;
            client->call = callback;
            this->clients.push_back(client);
            this->environment->addClient(client, {key});
        }
};

const auto EXAMPLE_TITLE = "ogs-07: Orientation";

struct Example
{
    Application *app;

    typedef std::map<std::string, std::string> Parameters;

    Example(const Parameters &parameters)
    {
        this->app = new Application(EXAMPLE_TITLE);

        MAIN_EXAMPLE_LOG("Title: '%s'", EXAMPLE_TITLE);
        this->setupWhiteNodes();
        
        this->app->registerScriptCallback(
            "application.camera.clearColor",
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                auto camera = this->app->camera();
                // Set.
                if (!values.empty())
                {
                    // Report error if values' count is insufficient.
                    if (values.size() != 3)
                    {
                        MAIN_EXAMPLE_LOG(
                            "ERROR Could not set value for key '%s' "
                            "because values' count is not 3"
                        );
                    }
                    // Apply color otherwise.
                    else
                    {
                        auto color = camera->getClearColor();
                        color.r() = atof(values[0].c_str());
                        color.g() = atof(values[1].c_str());
                        color.b() = atof(values[2].c_str());
                        camera->setClearColor(color);
                    }
                }
        
                // Return current color for Get and after Set.
                auto color = camera->getClearColor();
                return std::vector<std::string>({
                    format::printfString("%f", color.r()),
                    format::printfString("%f", color.g()),
                    format::printfString("%f", color.b()),
                });
            )
        );
        this->app->registerScriptCallback(
            "application.camera.nodeAtPosition",
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                // Make sure there are three components.
                if (values.size() != 3)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 3"
                    );
                    return std::vector<std::string>();
                }
        
                osg::Vec2d position = {
                    atof(values[0].c_str()),
                    atof(values[1].c_str()),
                };
                int selectionMask = atoi(values[2].c_str());
        
                // Locate a node.
                auto node =
                    scene::nodeAtPosition(
                        position,
                        this->app->camera(),
                        selectionMask
                    );
        
                // Return the name of the node if it exists.
                if (node)
                {
                    return std::vector<std::string>({
                        node->getName()
                    });
                }
        
                // Return nothing otherwise.
                return std::vector<std::string>();
            )
        );
        this->app->registerScriptCallback(
            "application.camera.position",
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                auto manipulator = this->app->cameraManipulator();
                osg::Vec3d pos;
                osg::Quat q;
                manipulator->getTransformation(pos, q);
        
                // Set.
                if (!values.empty())
                {
                    // Make sure there are three components.
                    if (values.size() != 3)
                    {
                        MAIN_EXAMPLE_LOG(
                            "ERROR Could not set value for key '%s' "
                            "because values' count is not 3"
                        );
                        return std::vector<std::string>();
                    }
        
                    // Apply position.
                    pos = {
                        atof(values[0].c_str()),
                        atof(values[1].c_str()),
                        atof(values[2].c_str()),
                    };
                    manipulator->setTransformation(pos, q);
                }
        
                // Return current position for Get and after Set.
                manipulator->getTransformation(pos, q);
                return std::vector<std::string>({
                    format::printfString("%f", pos.x()),
                    format::printfString("%f", pos.y()),
                    format::printfString("%f", pos.z()),
                });
            )
        );
        this->app->registerScriptCallback(
            "application.camera.rotation",
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                auto manipulator = this->app->cameraManipulator();
                osg::Vec3d pos;
                osg::Quat q;
                manipulator->getTransformation(pos, q);
        
                // Set.
                if (!values.empty())
                {
                    // Make sure there are three components.
                    if (values.size() != 3)
                    {
                        MAIN_EXAMPLE_LOG(
                            "ERROR Could not set value for key '%s' "
                            "because values' count is not 3"
                        );
                        return std::vector<std::string>();
                    }
        
                    // Apply rotation.
                    osg::Vec3d rot = {
                        atof(values[0].c_str()),
                        atof(values[1].c_str()),
                        atof(values[2].c_str()),
                    };
                    q = scene::degreesToQuaternion(rot);
                    manipulator->setTransformation(pos, q);
                }
        
                // Return current position for Get and after Set.
                manipulator->getTransformation(pos, q);
                auto rot = scene::quaternionToDegrees(q);
                return std::vector<std::string>({
                    format::printfString("%f", rot.x()),
                    format::printfString("%f", rot.y()),
                    format::printfString("%f", rot.z()),
                });
            )
        );
        this->setupApplicationMouse();
        
        this->app->registerScriptCallback(
            "application.nodes.createSphere",
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                // Set.
                if (!values.empty())
                {
                    // Make sure there are two components.
                    if (values.size() != 2)
                    {
                        MAIN_EXAMPLE_LOG(
                            "ERROR Could not set value for key '%s' "
                            "because values' count is not 2"
                        );
                        return std::vector<std::string>();
                    }
        
                    // Create sphere.
                    auto name = values[0];
                    auto radius = atof(values[1].c_str());
                    this->app->nodes->createSphere(name, radius);
                }
        
                return std::vector<std::string>();
            )
        );
        this->app->registerScriptCallback(
            "application.nodes.node.addChild",
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                // Set.
                if (!values.empty())
                {
                    // Make sure there are two components.
                    if (values.size() != 2)
                    {
                        MAIN_EXAMPLE_LOG(
                            "ERROR Could not set value for key '%s' "
                            "because values' count is not 2"
                        );
                        return std::vector<std::string>();
                    }
        
                    auto parentName = values[0];
                    auto parent = this->app->nodes->node(parentName);
                    auto childName = values[1];
                    auto child = this->app->nodes->node(childName);
        
                    // Make sure parent and child exist.
                    if (!parent || !child)
                    {
                        MAIN_EXAMPLE_LOG(
                            "ERROR Could not add '%s' child node to '%s' parent node "
                            "because node(s) do(es) not exist",
                            childName.c_str(),
                            parentName.c_str()
                        );
                        return std::vector<std::string>();
                    }
        
                    parent->addChild(child);
                }
        
                return std::vector<std::string>();
            )
        );
        this->app->registerScriptCallback(
            "application.nodes.node.exists",
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                // Set.
                if (!values.empty())
                {
                    // Make sure there is one component.
                    if (values.size() != 1)
                    {
                        MAIN_EXAMPLE_LOG(
                            "ERROR Could not set value for key '%s' "
                            "because values' count is not 1"
                        );
                        return std::vector<std::string>();
                    }
        
                    // Locate named node.
                    auto name = values[0];
                    auto node = this->app->nodes->node(name);
                    // Report its presence.
                    if (node != 0)
                    {
                        return std::vector<std::string>({ "true" });
                    }
                }
        
                return std::vector<std::string>();
            )
        );
        this->app->registerScriptCallback(
            "application.nodes.node.position",
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                // Make sure there is at least one component.
                if (values.size() < 1)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is less than 1",
                        key.c_str()
                    );
                    return std::vector<std::string>();
                }
        
                auto nodeName = values[0];
                auto node = this->app->nodes->node(nodeName);
        
                // Make sure node exists.
                if (!node)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not get or set position for node '%s' "
                        "because it does not exist",
                        nodeName.c_str()
                    );
                    return std::vector<std::string>();
                }
        
                // Set.
                if (values.size() == 4)
                {
                    osg::Vec3 position(
                        atof(values[1].c_str()),
                        atof(values[2].c_str()),
                        atof(values[3].c_str())
                    );
                    scene::setSimplePosition(node, position);
                }
        
                // Get.
                auto position = scene::simplePosition(node);
                return std::vector<std::string>({
                    format::printfString("%f", position.x()),
                    format::printfString("%f", position.y()),
                    format::printfString("%f", position.z()),
                });
            )
        );
        this->app->registerScriptCallback(
            "application.nodes.node.rotation",
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                // Make sure there is at least one component.
                if (values.size() < 1)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is less than 1",
                        key.c_str()
                    );
                    return std::vector<std::string>();
                }
        
                auto nodeName = values[0];
                auto node = this->app->nodes->node(nodeName);
        
                // Make sure node exists.
                if (!node)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not get or set rotation for node '%s' "
                        "because it does not exist",
                        nodeName.c_str()
                    );
                    return std::vector<std::string>();
                }
        
                // Set.
                if (values.size() == 4)
                {
                    osg::Vec3 rotation(
                        atof(values[1].c_str()),
                        atof(values[2].c_str()),
                        atof(values[3].c_str())
                    );
                    scene::setSimpleRotation(node, rotation);
                }
        
                // Get.
                auto rotation = scene::simpleRotation(node);
                return std::vector<std::string>({
                    format::printfString("%f", rotation.x()),
                    format::printfString("%f", rotation.y()),
                    format::printfString("%f", rotation.z()),
                });
            )
        );
        this->app->registerScriptCallback(
            "application.nodes.node.setMask",
            SCRIPT_ENVIRONMENT_CLIENT_CALL(
                // Make sure there are two components.
                if (values.size() != 2)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set value for key '%s' "
                        "because values' count is not 2"
                    );
                    return std::vector<std::string>();
                }
        
                auto name = values[0];
                auto node = this->app->nodes->node(name);
        
                // Make sure node exists.
                if (!node)
                {
                    MAIN_EXAMPLE_LOG(
                        "ERROR Could not set mask for node named '%s' because "
                        "it does not exist",
                        name.c_str()
                    );
                    return std::vector<std::string>();
                }
        
                // Set mask.
                int mask = atoi(values[1].c_str());
                node->setNodeMask(node->getNodeMask() & ~mask);
        
                return std::vector<std::string>();
            )
        );
        this->runEmbeddedAPIScript();
        
        this->runBase64Script(parameters);
        
    }
    ~Example()
    {

        this->tearApplicationMouseDown();
        
        delete this->app;
    }

    private:
        const std::string applicationMousePressedButtonsKey =
            "application.mouse.pressedButtons";
        const std::string applicationMousePositionKey =
            "application.mouse.position";
        const std::string applicationMouseCallbackName =
            "ApplicationMouseTransmitter";
    
        void setupApplicationMouse()
        {
            // Transmit pressed buttons.
            this->app->mouse->pressedButtonsChanged.addCallback(
                [=] {
                    this->transmitApplicationMouseButtons();
                },
                this->applicationMouseCallbackName
            );
            // Transmit position.
            this->app->mouse->positionChanged.addCallback(
                [=] {
                    this->transmitApplicationMousePosition();
                },
                this->applicationMouseCallbackName
            );
            // NOTE We don't provide getters for the keys because Lua side should
            // NOTE keep the state itself.
            // NOTE Also, we don't provide setters for the keys because C++ side
            // NOTE has no such notion.
        }
        void tearApplicationMouseDown()
        {
            this->app->mouse->pressedButtonsChanged.removeCallback(
                this->applicationMouseCallbackName
            );
            this->app->mouse->positionChanged.removeCallback(
                this->applicationMouseCallbackName
            );
        }
        void transmitApplicationMouseButtons()
        {
            // Convert buttons to string representation.
            auto buttons = this->app->mouse->pressedButtons;
            std::vector<std::string> strbuttons;
            for (auto button : buttons)
            {
                strbuttons.push_back(mouseButtonToString(button));
            }
            // Transmit.
            this->app->environment->call(
                this->applicationMousePressedButtonsKey,
                strbuttons
            );
        }
        void transmitApplicationMousePosition()
        {
            // Convert position to string representation.
            auto position = this->app->mouse->position;
            std::vector<std::string> strposition = {
                format::printfString("%f", position.x()),
                format::printfString("%f", position.y()),
            };
            // Transmit.
            this->app->environment->call(
                this->applicationMousePositionKey,
                strposition
            );
        }
    private:
        void runBase64Script(const Parameters &parameters)
        {
            // Get base64 string from `base64script` command line argument.
            auto it = parameters.find("base64script");
            if (it == parameters.end())
            {
                return;
            }
            auto base64Script = it->second;
    
            auto script = format::base64Decode(base64Script);
            this->app->executeLuaScript("Base64", script);
        }
    private:
        void runEmbeddedAPIScript()
        {
            resource::Resource api("scripts", "api.lua", api_lua, api_lua_len);
            this->app->executeLuaScript("Embedded API", api.contents);
        }
    private:
        void setupWhiteNodes()
        {
            // Create material that paints every scene node in white.
            const std::string vertexShader = R"(
    			void main()
    			{
    				// Pass vertex to fragment shader.
    				// Convert from Model/Object space to Screen one.
    				gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    			}
            )";
            const std::string fragmentShader = R"(
                void main()
                {
                    // Paint scene nodes in white.
                    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
                }
            )";
    
            auto prog = render::createShaderProgram(vertexShader, fragmentShader);
            osg::ref_ptr<osg::StateSet> material = new osg::StateSet;
            material->setAttribute(prog);
    
            // Apply material to the whole scene.
            auto root = this->app->nodes->node("root");
            root->setStateSet(material);
        }
};

}

} // namespace ogs

#endif // OGS_H

