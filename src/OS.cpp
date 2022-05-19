#include "OS.hpp"

#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>

// Platform specific headers
#if defined(_WIN32)

#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>
#elif defined(__APPLE__)

#endif

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

inline void mouse_click(unsigned int button) {
#if defined(_WIN32)
    
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    Display *display = XOpenDisplay(NULL);

    if (!display) {
        std::cerr << "Failed to intialize display\n";
        std::exit(EXIT_FAILURE);
    }

    XTestFakeButtonEvent(display, button, true, 0);
    XFlush(display);

    //wait(10);

    XTestFakeButtonEvent(display, button, false, 0);
    XFlush(display);

    XCloseDisplay(display);
#elif defined(__APPLE__)
    
#endif
}

void right_mouse_click() {
    mouse_click(3);
}

void left_mouse_click() {
    mouse_click(1);
}