#include <iostream>
#include <string>
#include <map>

class HomeAutomationController {
public:
    HomeAutomationController() {
        // Initialize the controller with default values
        lights["LivingRoom"] = false;
        lights["Bedroom"] = false;
        heater = false;
        ac = false;
        securitySystem = false;
        blinds["LivingRoom"] = false;
        blinds["Bedroom"] = false;
        musicSystem = false;
    }

    void addLight(const std::string& lightName) {
        // Add a new light to the controller
        lights[lightName] = false;
    }

    void removeLight(const std::string& lightName) {
        // Remove a light from the controller
        lights.erase(lightName);
    }

    void toggleLight(const std::string& lightName) {
        // Toggle the state of a light (on/off)
        if (lights.find(lightName) != lights.end()) {
            lights[lightName] = !lights[lightName];
        }
    }

    void setHeater(bool state) {
        // Set the state of the heater
        heater = state;
    }

    void setAC(bool state) {
        // Set the state of the air conditioning
        ac = state;
    }

    void setSecuritySystem(bool state) {
        // Set the state of the security system
        securitySystem = state;
    }

    void addBlind(const std::string& blindName) {
        // Add a new blind to the controller
        blinds[blindName] = false;
    }

    void toggleBlind(const std::string& blindName) {
        // Toggle the state of a blind (open/close)
        if (blinds.find(blindName) != blinds.end()) {
            blinds[blindName] = !blinds[blindName];
        }
    }

    void setMusicSystem(bool state) {
        // Set the state of the music system
        musicSystem = state;
    }

    void getStatus() {
        // Display the current status of the controller
        std::cout << "Home Automation Controller Status:" << std::endl;
        for (const auto& pair : lights) {
            std::cout << "Light " << pair.first << ": " << (pair.second ? "ON" : "OFF") << std::endl;
        }
        std::cout << "Heater: " << (heater ? "ON" : "OFF") << std::endl;
        std::cout << "Air Conditioning: " << (ac ? "ON" : "OFF") << std::endl;
        std::cout << "Security System: " << (securitySystem ? "Armed" : "Disarmed") << std::endl;
        for (const auto& pair : blinds) {
            std::cout << "Blind " << pair.first << ": " << (pair.second ? "Closed" : "Open") << std::endl;
        }
        std::cout << "Music System: " << (musicSystem ? "ON" : "OFF") << std::endl;
    }

private:
    std::map<std::string, bool> lights;
    bool heater;
    bool ac;
    bool securitySystem;
    std::map<std::string, bool> blinds;
    bool musicSystem;
};

int main() {
    HomeAutomationController controller;

    controller.addLight("LivingRoom");
    controller.addLight("Bedroom");
    controller.addBlind("LivingRoom");
    controller.addBlind("Bedroom");

    controller.setHeater(true);
    controller.setAC(false);
    controller.setSecuritySystem(true);
    controller.setMusicSystem(false);

    controller.toggleLight("LivingRoom");
    controller.toggleBlind("LivingRoom");

    controller.getStatus();

    return 0;
}
