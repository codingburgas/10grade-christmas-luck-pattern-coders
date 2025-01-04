
<hr/>

# Setup intructions

<br>

#### 1. Install necessary dependencies :
* Install [Qt](https://www.qt.io/download-qt-installer-oss)
* Intall [Cmake](https://cmake.org/download/)
* Install [MinGW](https://sourceforge.net/projects/mingw/) or other compiler

<br>

#### 2. Clone our project :
        
```bash        
git clone https://github.com/codingburgas/10grade-christmas-luck-pattern-coders.git
```        
        
#### and open it in IDE( preferably QtCreator )

<br>

#### 3. Build, run application and expand your knowledge!

<hr/>

<br>

# Communication between front-end and back-end

## ***The most important is to expose an object to qml, which will handle the communication :***

```cpp
engine.rootContext()->setContextProperty("application", this);
```

<br>

## Update of UI is done using the signal system that Qt offers.

<br>

### Let's take a look at an examples

<br>

In the following code block of Application::updateWordsUi in application.cpp file signal message of Application object is being emitted.

<br>

```cpp
emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
```

<br>

After that in the assets/ui/Application.qml(one of ui files) Connections type listens to signals on application object, which was exposed to qml earlier, and invokes onMessage function, when message signal is emitted. After that this function creates a message widget, which can be visible to user.

<br>

```qml
Connections{
        target: application

        function onMessage(title, description, type){
            let messageComponent = Qt.createComponent( Qt.resolvedUrl("Message.qml") )


            let waitFunction = () => {
                if (messageComponent.status == Component.Ready){
                    let message = messageComponent.createObject(
                        mainWindow,
                        {
                            title: title,
                            description: description,
                            type: type
                        });

                    message.destroy(2000)
                }else if (newComponent.status === Component.Loading) {
                    newComponent.statusChanged.connect(changeWindow); // Connect to statusChanged if still loading
                }
            }


            waitFunction();
        }
    }
```


## **User requests are handled by simply calling the function of Application object**
> **_NOTE:_**  The function you are calling from qml MUST have Q_INVOKABLE macro.

#### For example:

<br>

```cpp
application.searchWords(searchInput.text, property2ComboBox.getProperty(), caseSensitiveCheckBox.checked, (propertyHasToComboBox.currentIndex==1), (propertyHasToComboBox.currentIndex==2))
```

In this code from assets/ui/MainPage.qml method searchWords of application is called to search words with specific properties and update the UI