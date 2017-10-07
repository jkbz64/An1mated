#include <document.hpp>

Document::Document(DocumentType type, const QString &fileName, QObject *parent)
    :
      QObject(parent),
      m_type(type),
      m_fileName(fileName)
{

}

void Document::setFilename(const QString &name)
{
    m_fileName = name;
}
