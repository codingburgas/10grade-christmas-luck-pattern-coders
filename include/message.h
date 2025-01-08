//
// message.h
// Header file defining a Message object with title, description, and type properties.
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <QObject>

struct Message : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString titleUi READ titleUi WRITE setTitleUi NOTIFY titleUiChanged FINAL)
    Q_PROPERTY(QString descriptionUi READ descriptionUi WRITE setDescriptionUi NOTIFY descriptionUiChanged FINAL)
    Q_PROPERTY(QString typeUi READ typeUi WRITE setTypeUi NOTIFY typeUiChanged FINAL)

public:
    std::string title;
    std::string description;
    std::string type;

    /*
     * Constructs a Message object with the specified title, description, and type
     * Parameters:
     * -- std::string title: the title of the message
     * -- std::string description: the description of the message
     * -- std::string type: the type of the message
     * Returns:
     * -- None
     */
    Message(const std::string title, const std::string description, const std::string type) {
        this->title = title;
        this->description = description;
        this->type = type;
    }

    /*
     * Copy constructor for the Message object
     * Parameters:
     * -- const Message& m: the Message object to copy
     * Returns:
     * -- None
     */
    Message(const Message& m) {
        title = m.title;
        description = m.description;
        type = m.type;
    }

    /*
     * Copy assignment operator for the Message object
     * Parameters:
     * -- const Message& m: the Message object to assign from
     * Returns:
     * -- Message&: the updated Message object
     */
    Message& operator=(const Message& m) {
        title = m.title;
        description = m.description;
        type = m.type;

        return *this;
    }

    /*
     * Get the title property in QString format for use in the UI
     * Parameters:
     * -- None
     * Returns:
     * -- QString: the title of the message
     */
    QString titleUi() {
        return QString::fromStdString(title);
    }

    /*
     * Get the description property in QString format for use in the UI
     * Parameters:
     * -- None
     * Returns:
     * -- QString: the description of the message
     */
    QString descriptionUi() {
        return QString::fromStdString(description);
    }

    /*
     * Get the type property in QString format for use in the UI
     * Parameters:
     * -- None
     * Returns:
     * -- QString: the type of the message
     */
    QString typeUi() {
        return QString::fromStdString(type);
    }

    /*
     * Set the title property from a QString value and emit a signal
     * Parameters:
     * -- QString& val: the new title of the message
     * Returns:
     * -- None
     */
    void setTitleUi(QString& val) {
        // Implementation for setting the title
    }

    /*
     * Set the description property from a QString value and emit a signal
     * Parameters:
     * -- QString& val: the new description of the message
     * Returns:
     * -- None
     */
    void setDescriptionUi(QString& val) {
        // Implementation for setting the description
    }

    /*
     * Set the type property from a QString value and emit a signal
     * Parameters:
     * -- QString& val: the new type of the message
     * Returns:
     * -- None
     */
    void setTypeUi(QString& val) {
        // Implementation for setting the type
    }

signals:
    void titleUiChanged();
    void descriptionUiChanged();
    void typeUiChanged();
};

#endif // MESSAGE_H
