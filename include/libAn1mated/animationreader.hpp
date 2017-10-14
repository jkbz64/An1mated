#ifndef ANIMATIONREADER_HPP
#define ANIMATIONREADER_HPP

#include <sol/state.hpp>
#include <QString>
#include <animation.hpp>

namespace AnimationReader
{
    static QStringList getReadTypes()
    {
        QStringList types;
        return types;
    }

    static Animation deserialize(QString reader, const std::string& fileContent)
    {
        sol::state state;
        state.open_libraries();
        state.new_usertype<Animation>("Animation",
                                      "setName", [](Animation& animation, const std::string& name)
                                      {
                                          animation.setName(QString::fromStdString(name));
                                      },
                                      "setSpritesheet", [](Animation& animation, const std::string& spritesheet)
                                      {
                                          animation.setSpritesheetName(QString::fromStdString(spritesheet));
                                      },
                                      "addFrame", static_cast<void (Animation::*)(const AnimationFrame&)>(&Animation::addFrame)
        );
        state.new_usertype<AnimationFrame>("AnimationFrame");
        Animation animation;
        state.set_function("addFrame", [&animation](const std::string& name, int x, int y, int w, int h)
        {
            animation.addFrame(QString::fromStdString(name), QRect(x, y, w, h));
        });
        state.set("animation", &animation);
        state.set("content", fileContent);
        state.safe_script_file("readers/" + reader.toStdString() + ".lua");
        return animation;
    }
}

#endif
