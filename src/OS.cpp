#include "OS.hpp"

#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>

// Platform specific headers
#if defined(_WIN32)
#include <windows.h>
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>
#elif defined(__APPLE__)

#endif

enum class MouseButton {
    Right,
    Left
};

void terminal_clear() {
#if TERMINAL_CLEAR_ENABLED
#if defined(_WIN32)
    std::system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    std::system("clear");
#elif defined(__APPLE__)
    std::system("clear");
#endif
#endif
}

void wait(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void wait_for_enter() {
    while (std::cin.get() != 10) {}
}

inline void mouse_click(MouseButton button) {
#if defined(_WIN32)

    INPUT inputs[2] = {0};
    LPPOINT mouse_pos;
    GetCursorPos(mouse_pos);

    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dx = mouse_pos->x;
    inputs[0].mi.dy = mouse_pos->y;
    
    inputs[1].type = INPUT_MOUSE;

    switch (button)
    {
    case MouseButton::Left:
        inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN;
        inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
        break;
    case MouseButton::Right:
        inputs[0].mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN;
        inputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
        break;
    default:
        break;
    }

    SendInput(2, inputs, sizeof(INPUT));
    
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    Display *display = XOpenDisplay(NULL);

    if (!display) {
        std::cerr << "Failed to intialize display\n";
        std::exit(EXIT_FAILURE);
    }

    unsigned int button_id;

    switch (button)
    {
    case MouseButton::Left:
        button_id = 1;
        break;
    case MouseButton::Right:
        button_id = 3;
        break;
    default:
        break;
    }

    // Button down
    XTestFakeButtonEvent(display, button_id, true, 0);
    XFlush(display);

    // Button up
    XTestFakeButtonEvent(display, button_id, false, 0);
    XFlush(display);

    XCloseDisplay(display);
#elif defined(__APPLE__)
    
#endif
}

void right_mouse_click() {
    mouse_click(MouseButton::Right);
}

void left_mouse_click() {
    mouse_click(MouseButton::Left);
}