#include <document.hpp>

Document::Document(DocumentType type, const QString &fileName, QObject *parent)
    :
      m_type(type),
      m_fileName(fileName),
      QObject(parent)
{

}

