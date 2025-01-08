/**
 * This class stores properties like menu state, order type, search filters,
 * and user input. It uses signals to notify other components when these properties
 * are modified, enabling reactive behavior in the system.
 */
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
    /*
 * Get the value of the menuClosed property
 * Parameters:
 * -- None
 * Returns:
 * -- bool: current value of menuClosed
 */
    bool getMenuClosed() const { return menuClosed; }

    /*
 * Get the value of the descendingOrderChecked property
 * Parameters:
 * -- None
 * Returns:
 * -- bool: current value of descendingOrderChecked
 */
    bool getDescendingOrderChecked() const { return descendingOrderChecked; }

    /*
 * Get the value of the propertyIndex property
 * Parameters:
 * -- None
 * Returns:
 * -- int: current value of propertyIndex
 */
    int getPropertyIndex() const { return propertyIndex; }

    /*
 * Get the value of the caseSensitiveChecked property
 * Parameters:
 * -- None
 * Returns:
 * -- bool: current value of caseSensitiveChecked
 */
    bool getCaseSensitiveChecked() const { return caseSensitiveChecked; }

    /*
 * Get the value of the property2Index property
 * Parameters:
 * -- None
 * Returns:
 * -- int: current value of property2Index
 */
    int getProperty2Index() const { return property2Index; }

    /*
 * Get the value of the propertyHasToIndex property
 * Parameters:
 * -- None
 * Returns:
 * -- int: current value of propertyHasToIndex
 */
    int getPropertyHasToIndex() const { return propertyHasToIndex; }

    /*
 * Get the value of the page property
 * Parameters:
 * -- None
 * Returns:
 * -- int: current value of page
 */
    int getPage() const { return page; }

    /*
 * Get the value of the userInput property
 * Parameters:
 * -- None
 * Returns:
 * -- QString: current value of userInput
 */
    QString getUserInput() const { return userInput; }

    // Setters
    /*
 * Set menuClosed property and emit correspondent signal
 * Parameters:
 * -- bool value: new value of menuClosed
 * Returns:
 * -- None
 */
    void setMenuClosed(bool value) {
        if (menuClosed != value) {
            menuClosed = value;
            emit menuClosedChanged();
        }
    }

    /*
 * Set descendingOrderChecked property and emit correspondent signal
 * Parameters:
 * -- bool value: new value of descendingOrderChecked
 * Returns:
 * -- None
 */
    void setDescendingOrderChecked(bool value) {
        if (descendingOrderChecked != value) {
            descendingOrderChecked = value;
            emit descendingOrderCheckedChanged();
        }
    }

    /*
 * Set propertyIndex property and emit correspondent signal
 * Parameters:
 * -- int value: new value of propertyIndex
 * Returns:
 * -- None
 */
    void setPropertyIndex(int value) {
        if (propertyIndex != value) {
            propertyIndex = value;
            emit propertyIndexChanged();
        }
    }

    /*
 * Set caseSensitiveChecked property and emit correspondent signal
 * Parameters:
 * -- bool value: new value of caseSensitiveChecked
 * Returns:
 * -- None
 */
    void setCaseSensitiveChecked(bool value) {
        if (caseSensitiveChecked != value) {
            caseSensitiveChecked = value;
            emit caseSensitiveCheckedChanged();
        }
    }

    /*
 * Set property2Index property and emit correspondent signal
 * Parameters:
 * -- int value: new value of property2Index
 * Returns:
 * -- None
 */
    void setProperty2Index(int value) {
        if (property2Index != value) {
            property2Index = value;
            emit property2IndexChanged();
        }
    }

    /*
 * Set propertyHasToIndex property and emit correspondent signal
 * Parameters:
 * -- int value: new value of propertyHasToIndex
 * Returns:
 * -- None
 */
    void setPropertyHasToIndex(int value) {
        if (propertyHasToIndex != value) {
            propertyHasToIndex = value;
            emit propertyHasToIndexChanged();
        }
    }

    /*
 * Set page property and emit correspondent signal
 * Parameters:
 * -- int value: new value of page
 * Returns:
 * -- None
 */
    void setPage(int value) {
        if (page != value) {
            page = value;
            emit pageChanged();
        }
    }

    /*
 * Set userInput property and emit correspondent signal
 * Parameters:
 * -- QString value: new value of userInput
 * Returns:
 * -- None
 */
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
