from goopy import *

# Creating a window
window = GraphWin(title="Example GUI Design", width=getScreenSize()[1] * 0.8 - 200, height=getScreenSize()[1] * 0.8,
                  autoflush=False)
window.setCoords(0, 0, 800, 1000)
Image(Point(400, 500), "RegisterPage.png").draw(window)

emailEntry = Entry(Point(360, 465), 24, fill=WHITE, font="century gothic", justify="left", fontColour=LIGHT_GREY,
                   fontSize=30, promptText="Email Address").draw(window)
passwordEntry = Entry(Point(360, 600), 24, fill=WHITE, font="century gothic", justify="left", fontColour=LIGHT_GREY,
                      fontSize=30, promptText="Password", password=True).draw(window)

OptionsTab = CheckBox(Button(Image(Point(415, 320), "OptionsTab-Register.png"),
                             Image(Point(415, 320), "OptionsTab-Register.png").resizeFactor(1.02)),

                      Button(Image(Point(415, 320), "OptionsTab-SignIn.png"),
                             Image(Point(415, 320), "OptionsTab-SignIn.png").resizeFactor(1.02))).draw(window)

EnterButton = CheckBox(Button(Image(Point(365, 750), "RegisterButton.png"),
                              Image(Point(365, 750), "RegisterButton.png").resizeHeightFactor(1.05)),

                       Button(Image(Point(365, 750), "LoginButton.png"),
                              Image(Point(365, 750), "LoginButton.png").resizeHeightFactor(1.05)),
                       autoflush=False).draw(window)

SettingsButton = CheckBox(Button(Image(Point(698, 750), "SettingsButton-Light.png"),
                                 Image(Point(698, 750), "SettingsButton-Light.png").resizeHeightFactor(1.05)),

                          Button(Image(Point(698, 750), "SettingsButton-Dark.png"),
                                 Image(Point(698, 750), "SettingsButton-Dark.png").resizeHeightFactor(1.05)),
                          autoflush=False).draw(window)

infoText = Text(Point(400, 850), "", fontSize=15, font="century gothic", outline=DARK_NAVY_BLUE).draw(window)

while True:
    EnterButton.setState(OptionsTab.getState())
    SettingsButton.setState(OptionsTab.getState())

    mousePos = window.checkLeftMouseClick()

    if EnterButton.isClicked(mousePos):
        email = emailEntry.getText()
        password = passwordEntry.getText()
        if email != "Email Address" and '@' in email and password != "Password":
            break
        else:
            infoText.setText("Invalid Details Entered...")

    window.updateWin()

window.close()

type = ["Registered", "Signed-In"][EnterButton.getState()]
print(f"User has {type} with the email: {email} and password: {password}")
