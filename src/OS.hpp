#pragma once

#define TERMINAL_CLEAR_ENABLED true

// Contains functions for interacting with the OS

void terminal_clear();
void wait(int ms);
void wait_for_enter();
void right_mouse_click();
void left_mouse_click();