#ifndef CACHE_H
#define CACHE_H


#include <QObject>
#include <QString>




struct Cache : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool menuClosed READ getMenuClosed WRITE setMenuClosed NOTIFY menuClosedChanged FINAL)
    Q_PROPERTY(bool descendingOrderChecked READ getDescendingOrderChecked WRITE setDescendingOrderChecked NOTIFY descendingOrderCheckedChanged FINAL)
    Q_PROPERTY(int propertyIndex READ getPropertyIndex WRITE setPropertyIndex NOTIFY propertyIndexChanged FINAL)
    Q_PROPERTY(bool caseSensitiveChecked READ getCaseSensitiveChecked WRITE setCaseSensitiveChecked NOTIFY caseSensitiveCheckedChanged FINAL)
    Q_PROPERTY(int property2Index READ getProperty2Index WRITE setProperty2Index NOTIFY property2IndexChanged FINAL)
    Q_PROPERTY(int propertyHasToIndex READ getPropertyHasToIndex WRITE setPropertyHasToIndex NOTIFY propertyHasToIndexChanged FINAL)
    Q_PROPERTY(int page READ getPage WRITE setPage NOTIFY pageChanged FINAL)
    Q_PROPERTY(QString userInput READ getUserInput WRITE setUserInput NOTIFY userInputChanged FINAL)

public:

    bool menuClosed = true;
    bool descendingOrderChecked = false;
    int propertyIndex = 0;
    bool caseSensitiveChecked = false;
    int property2Index = 0;
    int propertyHasToIndex = 0;
    int page = 1;
    QString userInput = "";


    // Getters
    bool getMenuClosed() const { return menuClosed; }
    bool getDescendingOrderChecked() const { return descendingOrderChecked; }
    int getPropertyIndex() const { return propertyIndex; }
    bool getCaseSensitiveChecked() const { return caseSensitiveChecked; }
    int getProperty2Index() const { return property2Index; }
    int getPropertyHasToIndex() const { return propertyHasToIndex; }
    int getPage() const { return page; }
    QString getUserInput() const { return userInput; }

    // Setters
    void setMenuClosed(bool value) {
        if (menuClosed != value) {
            menuClosed = value;
            emit menuClosedChanged();
        }
    }

    void setDescendingOrderChecked(bool value) {
        if (descendingOrderChecked != value) {
            descendingOrderChecked = value;
            emit descendingOrderCheckedChanged();
        }
    }

    void setPropertyIndex(int value) {
        if (propertyIndex != value) {
            propertyIndex = value;
            emit propertyIndexChanged();
        }
    }

    void setCaseSensitiveChecked(bool value) {
        if (caseSensitiveChecked != value) {
            caseSensitiveChecked = value;
            emit caseSensitiveCheckedChanged();
        }
    }

    void setProperty2Index(int value) {
        if (property2Index != value) {
            property2Index = value;
            emit property2IndexChanged();
        }
    }

    void setPropertyHasToIndex(int value) {
        if (propertyHasToIndex != value) {
            propertyHasToIndex = value;
            emit propertyHasToIndexChanged();
        }
    }

    void setPage(int value) {
        if (page != value) {
            page = value;
            emit pageChanged();
        }
    }

    void setUserInput(QString value) {
        if (userInput != value) {
            userInput = value;
            emit userInputChanged();
        }
    }

signals:
    void menuClosedChanged();
    void descendingOrderCheckedChanged();
    void propertyIndexChanged();
    void caseSensitiveCheckedChanged();
    void property2IndexChanged();
    void propertyHasToIndexChanged();
    void pageChanged();
    void userInputChanged();

};





#endif // CACHE_H
