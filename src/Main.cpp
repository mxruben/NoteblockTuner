#include <rtmidi/RtMidi.h>
#include <memory>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "OS.hpp"

using std::unique_ptr;

#define MIDI_KEY_UP 128
#define MIDI_KEY_DOWN 144

static const std::string NOTE_NAMES[] {
    "F#3", "G3", "G#3", "A3", "A#3",
    "B3", "C4", "C#4", "D4", "D#4",
    "E4", "F4", "F#4", "G4", "G#4",
    "A4", "A#4", "B4", "C5", "C#5",
    "D5", "D#5", "E5", "F5", "F#5"
};

unique_ptr<RtMidiIn> create_midi_input() {
    try {
        return std::make_unique<RtMidiIn>();
    }
    catch(RtMidiError &error) {
        error.printMessage();
        std::exit(EXIT_FAILURE);
    }
}

void on_midi_in(double delta, std::vector<unsigned char> *message, void *user_data) {
    if (message->at(0) != MIDI_KEY_DOWN) return;
    int note = message->at(1) - 54;
    // Make sure note is in range
    if (note > 0 && note <= 24) {
        std::cout << "Note: " << NOTE_NAMES[note] << " | Number: " << note << "\n";
        for (int c = 0; c < note; ++c) {
            right_mouse_click();
        }
    }  
}

void select_input(RtMidiIn &in) {
    const unsigned int n_ports = in.getPortCount();
    std::string name;
    std::string prompt = "Choose an input device:\n\n";

    for (unsigned int n = 0; n < n_ports; ++n) {
        try {
            name = in.getPortName(n);
        }
        catch(RtMidiError &error) {
            error.printMessage();
            std::exit(EXIT_FAILURE);
        }
        prompt += '['; 
        prompt +=  std::to_string(n);
        prompt += "] ";
        prompt += name;
        prompt += '\n';
    }

    unsigned int choice;
    std::string user_input;
    bool valid_input = false;

    // Get user input
    while (!valid_input) {
        terminal_clear();
        std::cout << prompt;
        std::getline(std::cin, user_input);
        // Convert input
        std::stringstream ss(user_input);
        ss >> choice >> std::ws;
        // Validate input
        if (ss.eof() && choice < n_ports) {
            valid_input = true;
        }
        else {
            terminal_clear();
            std::cout << "Invalid input! Please enter a number between 0 and " << n_ports - 1 << "...\n";
            wait(1000);
        }
    }

    in.openPort(choice);
    terminal_clear();
}

void start_input(RtMidiIn &in) {
    in.setCallback(on_midi_in);
}

int main() {
    auto midi_in = create_midi_input();
    select_input(*midi_in);
    start_input(*midi_in);
    std::cout << "[Press enter to exit]\n";
    wait_for_enter();

    return 0;
}