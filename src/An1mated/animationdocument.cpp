#include <animationdocument.hpp>

AnimationDocument::AnimationDocument(const QString &fileName, QObject *parent)
    :
      Document(DocumentType::AnimationDocument, fileName, parent)
{

}

AnimationDocument::~AnimationDocument()
{

}

bool AnimationDocument::writeToFile(const QString &fileName)
{

}
