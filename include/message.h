#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <QObject>

struct Message : public QObject{
    Q_OBJECT
    Q_PROPERTY(QString titleUi READ titleUi WRITE setTitleUi NOTIFY titleUiChanged FINAL)
    Q_PROPERTY(QString descriptionUi READ descriptionUi WRITE setDescriptionUi NOTIFY descriptionUiChanged FINAL)
    Q_PROPERTY(QString typeUi READ typeUi WRITE setTypeUi NOTIFY typeUiChanged FINAL)

public:
    std::string title;
    std::string description;
    std::string type;

    /*Message(const std::string& title, const std::string& description, const std::string& type){
        this->title = title;
        this->description = description;
        this->type = type;
    }*/


    Message(const std::string title, const std::string description, const std::string type){
        this->title = title;
        this->description = description;
        this->type = type;
    }

    Message(const Message& m){
        title = m.title;
        description = m.description;
        type = m.type;
    }

    Message& operator=(const Message& m){
        title = m.title;
        description = m.description;
        type = m.type;

        return *this;
    }

    QString titleUi(){
        return QString::fromStdString(title);
    }

    QString descriptionUi(){
        return QString::fromStdString(description);
    }

    QString typeUi(){
        return QString::fromStdString(type);
    }

    void setTitleUi(QString &val){}
    void setDescriptionUi(QString &val){}
    void setTypeUi(QString &val){}

signals:

    void titleUiChanged();
    void descriptionUiChanged();
    void typeUiChanged();
};


#endif // MESSAGE_H
