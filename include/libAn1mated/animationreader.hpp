#ifndef ANIMATIONREADER_HPP
#define ANIMATIONREADER_HPP

#include <sol/state.hpp>
#include <QString>
#include <animation.hpp>

#include <QDirIterator>
#include <QFileInfo>

#include <iostream>

namespace AnimationReader
{
    static QStringList getReadTypes()
    {
        QStringList types;
        QDirIterator it(QDir::currentPath() + "/readers/");
        while(it.hasNext())
        {
             QFileInfo info(it.next());
             if(!info.isDir())
                 types.append(info.baseName());
        }
        std::unique(types.begin(), types.end());
        return types;
    }

    static Animation deserialize(QString reader, const std::string& fileContent)
    {
        sol::state state;
        state.open_libraries();
        state.new_usertype<Animation>("Animation",
                                      "new", sol::no_constructor,
                                      "setName", [](Animation& animation, const std::string& name)
                                      {
                                          animation.setName(QString::fromStdString(name));
                                      },
                                      "setSpritesheet", [](Animation& animation, const std::string& spritesheet)
                                      {
                                          animation.setSpritesheetName(QString::fromStdString(spritesheet));
                                      },
                                      "addFrame", [](Animation& animation, const std::string& name, int x, int y, int w, int h)
                                      {
                                          animation.addFrame(QString::fromStdString(name), QRect(x, y, w, h));
                                      }
        );
        Animation animation;
        state.set("animation", &animation);
        state.set("content", fileContent);
        state.safe_script_file("readers/" + reader.toStdString() + ".lua");
        return animation;
    }
}

#endif
