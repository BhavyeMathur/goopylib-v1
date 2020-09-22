from goopylib.imports import *

"""
Textures have been designed by Freepik, https://www.freepik.com/free-vector/modern-web-design-button-collection-with-flat-design_3099377.htm

This is a very simple program that creates a modern, light, login page which demonstrates the 
capabilities of using Checkboxes, Entries, and Buttons. 

To run this, simply download the entire folder in which this is placed, and run the program!

"""

# Creating a window
# We set the dimensions relative to the height of the screen because resolutions across screen can vary.
window = Window(title="Example GUI Design", width=800, height=1000)

background = Checkbox(Image(Point(400, 500), "RegisterPage.png"),
                      Image(Point(400, 500), "LoginPage.png"), autoflush=False).draw()  # This is the background image

# Creating the entry boxes
email_entry = Entry(Point(360, 465), 24, fill=WHITE, font_face="century gothic", justify="left", font_colour=LIGHT_GREY,
                    font_size=30, prompt_text="Email Address").draw()
password_entry = Entry(Point(360, 600), 24, fill=WHITE, font_face="century gothic", justify="left", font_colour=LIGHT_GREY,
                       font_size=30, prompt_text="Password", password=True).draw()

# Creating the options tab. The Enter & Settings button are checkboxes too because we want to display different textures based on 2 states: register or signin
# A checkbox takes 2 graphics: true & false

# Here, we specify the first graphic (true) to be a button. A button also takes in a graphic to display which can be any other Graphics Object.
# The 2nd parameter of the button (optional) is the graphic to display while hovering. In this case, we take the same image and resize it to 102%
options_tab = Checkbox(Button(Image(Point(415, 320), "OptionsTab-Register.png"),
                              Image(Point(415, 320), "OptionsTab-Register.png").resize_factor(1.02)),

                       # The false graphic is very similar
                       Button(Image(Point(415, 320), "OptionsTab-SignIn.png"),
                              Image(Point(415, 320), "OptionsTab-SignIn.png").resize_factor(1.02)), layer=1).draw()

# Setting autoflush to false for the Checkbox means that it will not automatically update its state (go from True->False, or vice-versa)
# We want this because we want to control the state to be that of the options page.
# If the options page is True (Register Page) then this should be Register Button, if it is False, this should be the Login Button

enter_button = Checkbox(Button(Image(Point(365, 750), "RegisterButton.png"),
                               Image(Point(365, 750), "RegisterButton.png").resize_height_factor(1.05)),

                        Button(Image(Point(365, 750), "LoginButton.png"),
                               Image(Point(365, 750), "LoginButton.png").resize_height_factor(1.05)),
                        autoflush=False, layer=1).draw()

settings_button = Checkbox(Button(Image(Point(698, 750), "SettingsButton-Light.png"),
                                  Image(Point(698, 750), "SettingsButton-Light.png").resize_height_factor(1.05)),

                           Button(Image(Point(698, 750), "SettingsButton-Dark.png"),
                                  Image(Point(698, 750), "SettingsButton-Dark.png").resize_height_factor(1.05)),
                           autoflush=False, layer=1).draw()

# We are creating a blank text object to display information to the user if needed
info_text = Text(Point(400, 850), "", font_size=15, font_face="century gothic", font_colour=DARK_NAVY_BLUE, layer=1).draw()

next_page = "Home Page"

# The mainloop
while True:
    background.set_state(options_tab.get_state())
    enter_button.set_state(options_tab.get_state())  # Updating the textures of these checkboxes to be that of the OptionsTab
    settings_button.set_state(options_tab.get_state())

    mouse_pos = window.check_left_mouse_click()  # Getting the position of a mouse click if there was one

    if enter_button.is_clicked(mouse_pos):  # Checking if the enter button was clicked
        email = email_entry.get_text()
        password = password_entry.get_text()
        if email != "Email Address" and password != "Password":  # Checking if the details are valid.
            break
        else:
            info_text.set_text("Invalid Details Entered...")  # If the details are invalid, we tell the user!

    elif settings_button.is_clicked(mouse_pos):
        next_page = "Settings Page"
        break

    window.update()  # Updating the window

window.close()  # Closing the window

if next_page == "Home Page":
    print(
        f"User has {['Signed-In', 'Registered'][enter_button.get_state()]} with the email: {email} and password: {password}")
else:
    print("Settings Page")
