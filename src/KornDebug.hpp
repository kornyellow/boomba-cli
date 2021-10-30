#pragma once

// Includes

class KornDebug {
public :

    static void debugMessage(std::string message) {

        std::ofstream debug_file;
        debug_file.open("debug_log.txt");
        debug_file << message << std::endl;
        debug_file.close();
    }
    static void debugMessage(int message) {

        std::string message_string = std::to_string(message);
        
        std::ofstream debug_file;
        debug_file.open("debug_log.txt");
        debug_file << message << std::endl;
        debug_file.close();
    }
};  