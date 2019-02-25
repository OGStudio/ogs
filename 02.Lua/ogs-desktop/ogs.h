
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

#include <map>

#include <cstdarg>

#include <iostream>

#include <cstdarg>

#include <sol.hpp>

#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

#include <osg/Camera>


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
//! Find prefix in the provided string.
bool stringStartsWith(const std::string &s, const std::string &prefix)
{
    // Source: https://stackoverflow.com/a/8095127
    // Topic: how to check string start in C++
    return
        (prefix.length() <= s.length()) &&
        std::equal(prefix.begin(), prefix.end(), s.begin())
        ;
}
typedef std::map<std::string, std::string> Parameters;
//! Convert command line arguments in the form of `--key=value` to parameters.
Parameters commandLineArgumentsToParameters(
    int argc,
    char *argv[]
) {
    Parameters parameters;
    // Start with index #1 because index #0 contains program name.
    for (auto i = 1; i < argc; ++i)
    {
        auto argument = std::string(argv[i]);
        // Only accept arguments starting with `--`.
        if (format::stringStartsWith(argument, "--"))
        {
            // Skip the dashes.
            auto option = argument.substr(2);
            // Only split once.
            auto keyAndValue = format::splitString(option, "=", 1);
            if (keyAndValue.size() == 2)
            {
                auto key = keyAndValue[0];
                auto value = keyAndValue[1];
                parameters[key] = value;
            }
        }
    }
    return parameters;
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

namespace render
{

//! Create graphics context for desktop: linux, macos, windows.
osg::GraphicsContext *createGraphicsContext(
    const std::string &title,
    int x,
    int y,
    int width,
    int height
) {
    // Traits combine configuration parameters.
    osg::GraphicsContext::Traits *traits =
        new osg::GraphicsContext::Traits;
    // Geometry.
    traits->x = x;
    traits->y = y;
    traits->width = width;
    traits->height = height;
    // Title.
    traits->windowName = title;
    // Window borders.
    traits->windowDecoration = true;
    // Double buffer (simply put, it's a flicker fix).
    traits->doubleBuffer = true;

    return osg::GraphicsContext::createGraphicsContext(traits);
}
// Configure camera with common defaults.
void setupCamera(
    osg::Camera *cam,
    osg::GraphicsContext *gc,
    double fovy,
    int width,
    int height
) {
    // Provide GC.
    cam->setGraphicsContext(gc);
    // Viewport must have the same size.
    cam->setViewport(new osg::Viewport(0, 0, width, height));
    // Clear depth and color buffers each frame.
    cam->setClearMask(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    // Aspect ratio.
    float aspect = static_cast<float>(width) / static_cast<float>(height);
    // Configure projection.
    cam->setProjectionMatrixAsPerspective(fovy, aspect, 1, 1000);
}

}

namespace main
{

class Application
{
    public:
        Application(const std::string &name)
        {

            this->setupRendering();
            
            this->setupLua();
            
        }
        ~Application()
        {

            this->tearLuaDown();
            
            this->tearRenderingDown();
            
        }

    public:
        void frame()
        {
            this->viewer->frame();
        }
    public:
        void run()
        {
            while (!this->viewer->done())
            {
                this->frame();
            }
        }
    public:
        void setupWindow(
            const std::string &title,
            int x,
            int y,
            int width,
            int height
        ) {
            osg::GraphicsContext *gc =
                render::createGraphicsContext(title, x, y, width, height);
            // Configure viewer's camera with FOVY and window size.
            osg::Camera *cam = this->viewer->getCamera();
            render::setupCamera(cam, gc, 30, width, height);
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
};

const auto EXAMPLE_TITLE = "ogs-02: Lua";

struct Example
{
    Application *app;

    typedef std::map<std::string, std::string> Parameters;

    Example(const Parameters &parameters)
    {
        this->app = new Application(EXAMPLE_TITLE);

        this->runBase64Script(parameters);
        
    }
    ~Example()
    {

        delete this->app;
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
};

}

} // namespace ogs

#endif // OGS_H

