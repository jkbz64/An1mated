#ifndef ANIMATIONWRITER_HPP
#define ANIMATIONWRITER_HPP

#include <sol/state.hpp>
#include <QStringList>
#include <animation.hpp>

#include <QDirIterator>
#include <QFileInfo>

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

    static std::string serialize(QString writer, const Animation& animation)
    {
        std::string content;
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
        state.new_usertype<AnimationFrame>("AnimationFrame");
        state.set("content", &content);
        state.set("animation", animation);
        state.do_file("writers/" + writer.toStdString() + ".lua");
        return content;
    }
}

#endif
