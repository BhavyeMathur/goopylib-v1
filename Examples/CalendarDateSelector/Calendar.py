from goopylib.Window import Window
from goopylib.Point import Point

from goopylib.objects.Image import Image
from goopylib.objects.Rectangle import Rectangle
from goopylib.objects.Text import Text
from goopylib.objects.Button import Button
from goopylib.objects.Checkbox import Checkbox
from goopylib.objects.RadioButton import RadioButton

import datetime
import calendar

from goopylib.colours import ColourRGB, LIGHTEST_PINK, WHITE, DARKER_GREY, BLACK, LIGHTER_GREY

# These import statements can also be replaced by from goopylib.imports import * which imports everything

def date_selector():

    # Creating a Window on which the calendar is drawn with a width of 450 and height of 480.
    # The remove_title_bar parameter (default False) removes the title bar from the top of the window

    # The window bounds (default whole window) define what counts as clicking the window (for dragging)
    # Here, the bounds are set to a Rectangle object, the other option is an Image object.
    # We set the window to be draggable, if the user clicks inside the window's bounds, the window will be dragged

    window = Window(title="goopylib Calendar Example", width=450, height=480, remove_title_bar=True,
                    bounds=Rectangle(Point(100, 0), Point(350, 60))).set_draggable()
    Image(Point(225, 240), "CalendarBackground.png").draw(window)  # Drawing the Background Image

    current_year = int(datetime.datetime.now().strftime('%Y'))  # Gets the current year
    current_month = datetime.datetime.now().strftime('%B')  # Gets the name of the current month
    current_month_index = int(datetime.datetime.now().strftime('%m'))  # Gets the index of the current month (Jan is 1)

    # first_day is an integer (Monday is 1, Sunday is 7) which defines what day of the week the first date of the
    # month fell on
    # number_of_dates is the number of day in this month
    first_day, number_of_days = calendar.monthrange(current_year, current_month_index)

    # these are the number of days in the previous month
    previous_number_of_days = calendar.monthrange(current_year, current_month_index - 1)[1]

    # This is a button to accept the date selected. It is made from 2 image objects, the first one is the normal state
    # and the second one is the state when you hover over (the same image, enlarged by a factor of 105%)
    accept_button = Button(Image(Point(380, 448), "AcceptButton.png"),
                           Image(Point(380, 448), "AcceptButton.png").resize_factor(1.05)).draw(window)

    # This is the title text showing the selected month and year. The font, style, colour, and size are all given too.
    title = Text(Point(225, 31), f"{current_month} {current_year}", font_face="century gothic", font_style="bold",
                 font_colour=WHITE, font_size=25).draw(window)

    # This is the button to close the window given next to the title.
    close_button = Button(Image(Point(73, 33), "CrossButton.png")).draw(window)

    # These are buttons to navigate the months. Pressing left takes you to the previous month and right to the next
    left_arrow = Image(Point(35, 33), "Arrow.png").draw(window)
    right_arrow = Image(Point(415, 33), "Arrow.png").flip_x().draw(window)

    date_buttons = RadioButton(*(Checkbox(Button(Rectangle(Point(20 + day * 60, 125 + 50 * week),
                                                           Point(70 + day * 60, 175 + 50 * week),
                                                           fill=ColourRGB(255, 83, 84), outline_width=0),

                                                 label=Text(Point(45 + day * 60, 150 + 50 * week), day + week * 7,
                                                            font_size=15, font_face="century gothic", font_colour=WHITE)),

                                          Button(Rectangle(Point(20 + day * 60, 125 + 50 * week),
                                                           Point(70 + day * 60, 175 + 50 * week), fill=WHITE,
                                                           outline_width=0),

                                                 Rectangle(Point(20 + day * 60, 125 + 50 * week),
                                                           Point(70 + day * 60, 175 + 50 * week), fill=LIGHTEST_PINK,
                                                           outline_width=0),
                                                 label=Text(Point(45 + day * 60, 150 + 50 * week), day + week * 7,
                                                            font_size=15, font_face="century gothic")),

                                          state=False)

                               for day in range(7) for week in range(6))).draw(window)

    while window.is_open():
        key = window.check_key_press()
        mouse_pos = window.check_left_mouse_click()

        if key == "Escape" or close_button.is_clicked(mouse_pos) \
                or accept_button.is_clicked(mouse_pos) or key == "Return":
            window.close()

        window.update_win()

    """
    # The previous_date_index is variable which stores
    prev_date_index = int(datetime.datetime.now().strftime('%d')) + first_day

    y = prev_date_index // 7
    x = prev_date_index % 7

    date_numbers = []

    day_index = 0
    for week in range(6):
        for day in range(7):
            text = day_index - number_of_days - 1 if day_index - first_day > number_of_days else day_index - first_day\
                if day_index - first_day > 0 else previous_number_of_days - abs(day_index - first_day)
            colour = DARKER_GREY if day_index > first_day and day_index - first_day <= number_of_days else LIGHTER_GREY

            date_numbers.append(Text(Point(45 + day * 60, 150 + 50 * week), text, font_face="century gothic", layer=2,
                                     font_size=15, font_colour=colour).draw(window))
            day_index += 1

    date_numbers[int(x + y * 7)].set_fill(WHITE)

    selection_hover = Rectangle(Point(0, 0), Point(50, 50), outline_width=0, fill=LIGHTEST_PINK)
    selection = Rectangle(Point(0, 0), Point(50, 50), outline_width=0, fill=ColourRGB(255, 83, 84),
                          layer=1).draw(window).move_to(x * 60 + 45, y * 50 + 150)

    while window.is_open():
        key = window.check_key_press()
        mouse_pos = window.check_left_mouse_click()

        if key == "Escape" or close_button.is_clicked(mouse_pos) or accept_button.is_clicked(mouse_pos) or key == "Return":
            window.close()

        elif left_arrow.is_clicked(mouse_pos) or key == "comma":
            for text in date_numbers:
                text.destroy()

            current_month_index -= 1
            if current_month_index == 0:
                current_month_index = 12
                current_year -= 1
            current_month = ["January", "February", "March", "April", "May", "June", "July", "August", "September",
                             "October", "November", "December"][current_month_index - 1 if current_month_index != 0 else 12]

            title.set_text(f"{current_month} {current_year}")

            first_day, number_of_days = calendar.monthrange(current_year, current_month_index)
            previous_number_of_days = calendar.monthrange(current_year, current_month_index)[1]

            y = 3
            x = 0

            date_numbers = []

            day_index = 0
            for week in range(6):
                for day in range(7):
                    text = day_index - number_of_days - 1 if day_index - first_day > number_of_days else day_index - first_day \
                        if day_index - first_day > 0 else previous_number_of_days - abs(day_index - first_day)
                    colour = DARKER_GREY if day_index > first_day and day_index - first_day <= number_of_days else LIGHTER_GREY

                    date_numbers.append(
                        Text(Point(45 + day * 60, 150 + 50 * week), text, font_face="century gothic", layer=2,
                             font_size=15, font_colour=colour).draw(window))
                    day_index += 1

            date_numbers[int(x + y * 7)].set_fill(WHITE)

            selection_hover.move_to(x * 60 + 45, y * 50 + 150)
            selection.move_to(x * 60 + 45, y * 50 + 150)

        elif right_arrow.is_clicked(mouse_pos) or key == "period":
            for text in date_numbers:
                text.destroy()

            current_month_index += 1
            if current_month_index == 13:
                current_month_index = 1
                current_year += 1
            current_month = ["January", "February", "March", "April", "May", "June", "July", "August", "September",
                             "October", "November", "December"][current_month_index - 1]

            title.set_text(f"{current_month} {current_year}")

            first_day, number_of_days = calendar.monthrange(current_year, current_month_index)
            previous_number_of_days = calendar.monthrange(current_year, current_month_index)[1]

            prev_date_index = 1 + first_day

            y = prev_date_index // 7
            x = prev_date_index % 7

            date_numbers = []

            day_index = 0
            for week in range(6):
                for day in range(7):
                    text = day_index - number_of_days - 1 if day_index - first_day > number_of_days else day_index - first_day \
                        if day_index - first_day > 0 else previous_number_of_days - abs(day_index - first_day)
                    colour = DARKER_GREY if day_index > first_day and day_index - first_day <= number_of_days else LIGHTER_GREY

                    date_numbers.append(
                        Text(Point(45 + day * 60, 150 + 50 * week), text, font_face="century gothic", layer=2,
                             font_size=15, font_colour=colour).draw(window))
                    day_index += 1

            date_numbers[int(x + y * 7)].set_fill(WHITE)

            selection_hover.move_to(x * 60 + 45, y * 50 + 150)
            selection.move_to(x * 60 + 45, y * 50 + 150)

        elif mouse_pos is not None:
            if 430 > mouse_pos.y > 130 and 20 < mouse_pos.x < 430:
                x = (mouse_pos.x - 10) // 60
                y = (mouse_pos.y - 130) // 50

                date_index = int(x + 1 + y * 7)

                if date_index > first_day + 1 and date_index - first_day <= 1 + number_of_days:
                    date_numbers[prev_date_index].set_fill(BLACK)
                    date_numbers[date_index - 1].set_fill(WHITE)
                    prev_date_index = date_index - 1

                    if not selection.drawn:
                        selection.draw(window)
                    selection.move_to(x * 60 + 45, y * 50 + 150)

        mouse_pos = window.check_mouse_motion()
        if mouse_pos is not None:
            if 430 > mouse_pos.y > 130 and 20 < mouse_pos.x < 430:
                x = (mouse_pos.x - 10) // 60
                y = (mouse_pos.y - 130) // 50

                date_index = x + 1 + y * 7
                if date_index > first_day + 1 and date_index - first_day <= 1 + number_of_days:
                    selection_hover.move_to(x * 60 + 45, y * 50 + 150)
                    if not selection_hover.drawn:
                        selection_hover.draw(window)
                else:
                    selection_hover.undraw()
            else:
                selection_hover.undraw()

        window.update_win()

    month = {"January": "Jan", "February": "Feb", "March": "March", "April": "April", "May": "May", "June": "June",
             "July": "July", "August": "Aug", "September": "Sep", "October": "Oct", "November": "Nov",
             "December": "Dec"}[current_month]

    return f"{prev_date_index - first_day} {month}, {current_year}"
    """


print(date_selector())
