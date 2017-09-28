#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <QObject>

class Document : public QObject
{
    Q_OBJECT
public:
    enum class DocumentType
    {
        AnimationDocument,
        MultiAnimationDocument
    };

    Document(DocumentType type,
             const QString& fileName = QString(),
             QObject* parent = nullptr);
    virtual ~Document() = default;

    DocumentType getType() const;
    const QString& getFileName() const;
    QObject* getObject() const;

    virtual bool writeToFile(const QString& fileName) = 0;
signals:
    void documentSaved();
    void documentNameChanged(const QString&);
    void documentModified();
    void documentObjectChanged(QObject*);
private:
    DocumentType m_type;
    QString      m_fileName;
    QObject*     m_object = nullptr;
};


inline Document::DocumentType Document::getType() const
{
    return m_type;
}

inline const QString& Document::getFileName() const
{
    return m_fileName;
}

inline QObject* Document::getObject() const
{
    return m_object;
}

#endif
