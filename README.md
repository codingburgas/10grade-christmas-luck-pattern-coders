
<hr/>

# Documentation and presentation
<br>

- [Presentation](https://codingburgas-my.sharepoint.com/:p:/g/personal/ptkostov22_codingburgas_bg/EVGk1WREb9VNjzAX4T-z7U8Bnqk4Xd8G5Xseo0OHYnEUnQ?e=GhRT45)
- [Documentation](https://codingburgas-my.sharepoint.com/:w:/g/personal/ptkostov22_codingburgas_bg/EUKAQVZZYXdKiSiGZ5ulmpIBaQYCXkLgR6gNJJghAilQPA?e=TCPdFo)

# Core Tech Stack
<br>

<p align="left" gap="10px">
<a href="https://github.com/"><img src="https://img.icons8.com/nolan/344/github.png" alt="GitHub logo" width=52px /></a>
<a href="https://git-scm.com/"><img width="48" height="48" src="https://img.icons8.com/color/48/git.png" alt="git"/> </a>
<a href="https://www.figma.com/"><img src="https://img.icons8.com/color/344/figma--v1.png" alt="Figma logo" width=48px/></a>
<a href="https://cplusplus.com/"><img width="48" height="48" src="https://img.icons8.com/fluency/48/c-plus-plus-logo.png" alt="c-plus-plus-logo"/></a>
<a href="https://www.microsoft.com/en-ww/microsoft-365/word"><img src="https://img.icons8.com/color/48/microsoft-word-2019--v2.png" alt="MS Word logo" width=48px /></a>
<a href="https://www.microsoft.com/en-ww/microsoft-365/powerpoint"><img src="https://img.icons8.com/color/344/ms-powerpoint.png" alt="MS PowerPoint logo" width=48px /></a>
<img width="50" height="50" src="https://img.icons8.com/ios/50/qt.png" alt="qt"/>
<img width="48" height="48" src="https://img.icons8.com/pulsar-color/48/json.png" alt="json"/>
</p>


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
/* src/application.cpp : 105 */
engine.rootContext()->setContextProperty("application", this);
```

<br>

## Update of UI is done using the signal system that Qt offers.

<br>

### Let's take a look at an example :

<br>

In the following code block signal message of Application object is being emitted.

<br>

```cpp
/* src/application.cpp : 132 */
emit message(QString::fromStdString(m.title), QString::fromStdString(m.description), QString::fromStdString(m.type));
```

<br>

After that, "Connections" object listens to signals on application object, which was exposed to qml earlier, and invokes onMessage function, when message signal is emitted. After that this function creates a message widget, which can be visible to user.

<br>

```js
/* assets/ui/Application.qml : 89 */
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
                    newComponent.statusChanged.connect(waitFunction); // Connect to statusChanged if still loading
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
/* assets/ui/MainPage.qml : 627 */
application.searchWords(searchInput.text, property2ComboBox.getProperty(), caseSensitiveCheckBox.checked, (propertyHasToComboBox.currentIndex==1), (propertyHasToComboBox.currentIndex==2))
```

In this code method searchWords of application is called to search words with specific properties and update the UI

# 👦Our Team Members

- [Petar Kostov](https://github.com/PTKostov22) 
- [Vinichenko Oleksandr Oleksandrov](https://github.com/VOOleksandrov22)
- [Denis Pirig](https://github.com/DIPirig22)
