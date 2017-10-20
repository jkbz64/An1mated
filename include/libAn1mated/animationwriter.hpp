#ifndef ANIMATIONWRITER_HPP
#define ANIMATIONWRITER_HPP

#include <sol/state.hpp>
#include <QStringList>
#include <animation.hpp>

#include <QDirIterator>
#include <QFileInfo>

#include <iostream>

namespace AnimationWriter
{
    static QStringList getWriteTypes()
    {
        QStringList types;
        QDirIterator it(QDir::currentPath() + "/writers/");
        while(it.hasNext())
        {
             QFileInfo info(it.next());
             if(!info.isDir() && info.suffix() == "lua")
                 types.append(info.baseName());
        }
        std::unique(types.begin(), types.end());
        return types;
    }

    static QByteArray serialize(QString writer, const Animation& animation)
    {
        sol::state state;
        state.open_libraries();
        state.new_usertype<Animation>("Animation",
                                      "getName", [](Animation& animation)
                                      {
                                          return animation.getName().toStdString();
                                      },
                                      "getSpritesheet", [](Animation& animation)
                                      {
                                          return animation.getSpritesheetName().toStdString();
                                      },
                                      "getFrames", &Animation::getFrames
        );

        state.new_usertype<QRect>("QRect",
                                  "new", sol::no_constructor,
                                  "x", &QRect::x,
                                  "y", &QRect::y,
                                  "w", &QRect::width,
                                  "h", &QRect::height);

        state.new_usertype<AnimationFrame>("AnimationFrame",
                                           "getName", [](AnimationFrame& frame)
                                           {
                                               return frame.getName().toStdString();
                                           },
                                           "getRect", &AnimationFrame::getRect);
        state.set("content", "");
        state.set("animation", animation);
        state.safe_script_file("writers/" + writer.toStdString() + ".lua");
        sol::string_view content = state["content"];
        return QByteArray(content.data());
    }
}

#endif
