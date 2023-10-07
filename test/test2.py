import pyautogui

# Specific key you want to check (in this case, 'a' key)
specific_key = 'a'

while True:
    # Check if the specific key is pressed
    if pyautogui.keyDown(specific_key):
        print(f"The '{specific_key}' key is pressed!")

    # Add a small delay to reduce CPU usage
    pyautogui.PAUSE = 0.1