from goopy import *

"""
Textures have been designed by Freepik, https://www.freepik.com/free-vector/modern-web-design-button-collection-with-flat-design_3099377.htm

"""

# Creating a window
# autoflush defines whether or not the window updates automatically.
# We set the dimensions relative to the height of the screen because resolutions across screen can vary.
window = GraphWin(title="Example GUI Design", width=getScreenSize()[1] * 0.8 - 200, height=getScreenSize()[1] * 0.8,
                  autoflush=False)
window.setCoords(0, 0, 800,
                 1000)  # Because the actual height & width might be different according to the screen size, we define these virtual coordinates (Top-Left, Bottom-Right)
background = CheckBox(Image(Point(400, 500), "RegisterPage.png"),
                      Image(Point(400, 500), "LoginPage.png"), autoflush=False).draw(window)  # This is the background image

# Creating the entry boxes
emailEntry = Entry(Point(360, 465), 24, fill=WHITE, font="century gothic", justify="left", fontColour=LIGHT_GREY,
                   fontSize=30, promptText="Email Address").draw(window)
passwordEntry = Entry(Point(360, 600), 24, fill=WHITE, font="century gothic", justify="left", fontColour=LIGHT_GREY,
                      fontSize=30, promptText="Password", password=True).draw(window)

# Creating the options tab. The Enter & Settings button are checkboxes too because we want to display different textures based on 2 states: register or signin
# A checkbox takes 2 graphics: true & false

# Here, we specify the first graphic (true) to be a button. A button also takes in a graphic to display which can be any other Graphics Object.
# The 2nd parameter of the button (optional) is the graphic to display while hovering. In this case, we take the same image and resize it to 102%
OptionsTab = CheckBox(Button(Image(Point(415, 320), "OptionsTab-Register.png"),
                             Image(Point(415, 320), "OptionsTab-Register.png").resizeFactor(1.02)),

                      # The false graphic is very similar
                      Button(Image(Point(415, 320), "OptionsTab-SignIn.png"),
                             Image(Point(415, 320), "OptionsTab-SignIn.png").resizeFactor(1.02))).draw(window)

# Setting autoflush to false for the Checkbox means that it will not automatically update its state (go from True->False, or vice-versa)
# We want this because we want to control the state to be that of the options page.
# If the options page is True (Register Page) then this should be Register Button, if it is False, this should be the Login Button

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

# We are creating a blank text object to display information to the user if needed
infoText = Text(Point(400, 850), "", fontSize=15, font="century gothic", outline=DARK_NAVY_BLUE).draw(window)

nextPage = "Home Page"

# The mainloop
while True:
    background.setState(OptionsTab.getState())
    EnterButton.setState(
        OptionsTab.getState())  # Updating the textures of these checkboxes to be that of the OptionsTab
    SettingsButton.setState(OptionsTab.getState())
    OptionsTab.redraw()   Redrawing because we're also redrawing the background

    mousePos = window.checkLeftMouseClick()  # Getting the position of a mouse click if there was one

    if EnterButton.isClicked(mousePos):  # Checking if the enter button was clicked
        email = emailEntry.getText()
        password = passwordEntry.getText()
        if email != "Email Address" and '@' in email and password != "Password":  # Checking if the details are valid.
            break
        else:
            infoText.setText("Invalid Details Entered...")  # If the details are invalid, we tell the user!

    elif SettingsButton.isClicked(mousePos):
        nextPage = "Settings Page"
        break

    window.updateWin()  # Updating the window

window.close()  # Closing the window

if nextPage == "Home Page":
    type = ["Registered", "Signed-In"][EnterButton.getState()]  # getState() returns the current state of the checkbox
    print(f"User has {type} with the email: {email} and password: {password}")
else:
    print("Settings Page")
