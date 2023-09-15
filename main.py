import os
import time
import platform
from colorama import Fore
import phonenumbers
from phonenumbers import geocoder
from phonenumbers import timezone
from datetime import datetime
import re

# Define constants
LINE_SEPARATOR = "------------------"

# Function to get the console clearing command based on the platform
def get_clear_command():
    if platform.system() == 'Windows':
        return 'cls'
    else:
        return 'clear'

# Function to get current time display based on the platform
def get_current_time_display(current_time):
    if platform.system() == 'Windows':
        terminal_size = os.get_terminal_size().columns
        padding = terminal_size - len(current_time)
        return f"{current_time}{' ' * padding}"
    else:
        return f"\033[1;30;47m{current_time}\033[m"

# Clear the console
os.system(get_clear_command())

# Print information about the tool
print(LINE_SEPARATOR)
print(f"{Fore.WHITE}[ {Fore.CYAN}\u00A7 {Fore.WHITE}] PhoneDNS SecLabX | Licensed under MIT License")
print(f"{Fore.WHITE}[ {Fore.CYAN}\u00A7 {Fore.WHITE}] Original creator: https://github.com/SecLabX")
print(f"{Fore.WHITE}[ {Fore.CYAN}\u00A7 {Fore.WHITE}] Creator of this version: https://github.com/SecLabX")
print()
time.sleep(2)

# Function to get current time
def get_current_time():
    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    return current_time

# Clear the console
os.system(get_clear_command())
print(LINE_SEPARATOR)

# Input phone number
number = input("DNS -> ")
if not re.match(r'^\+?\d{3}-\d{3}-\d{4}$', number):
    print("Invalid phone number format. Please enter a valid phone number in the format XXX-XXX-XXXX.")
    exit()

# Clear the console
os.system(get_clear_command())

# Specify the default region (e.g., "US" for United States)
default_region = "US"

# See if the number is valid
ch_number = phonenumbers.parse(number, default_region)
is_possible = phonenumbers.is_possible_number(ch_number)

# Find the state
state = geocoder.description_for_number(ch_number, "en")

# Find the time zone
time_zones = timezone.time_zones_for_number(ch_number)

# Print the current time
current_time = get_current_time()
print(get_current_time_display(current_time))

# Print the result
print(LINE_SEPARATOR)
print(f"Valid phone number: {is_possible}")
print(LINE_SEPARATOR)
print(f"State: {state}")
print(LINE_SEPARATOR)
print(f"Time zones: {', '.join(time_zones)}")
print(LINE_SEPARATOR)
