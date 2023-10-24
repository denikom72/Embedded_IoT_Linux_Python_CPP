# Beispiel für ein Home Automation Controller

class HomeAutomationController:
    def __init__(self):
        self.lights = {}  # Dictionary zur Verwaltung von Lichtern
        self.heater = None  # Variable zur Steuerung der Heizung
        self.ac = None  # Variable zur Steuerung der Klimaanlage

    def add_light(self, light_id, state=False):
        # Fügt ein Licht hinzu und setzt den Anfangszustand
        self.lights[light_id] = state

    def remove_light(self, light_id):
        # Entfernt ein Licht aus der Liste
        if light_id in self.lights:
            del self.lights[light_id]

    def toggle_light(self, light_id):
        # Schaltet ein Licht ein/aus
        if light_id in self.lights:
            self.lights[light_id] = not self.lights[light_id]

    def set_heater(self, state):
        # Schaltet die Heizung ein/aus
        self.heater = state

    def set_ac(self, state):
        # Schaltet die Klimaanlage ein/aus
        self.ac = state

    def get_status(self):
        # Gibt den aktuellen Status des Home Automation Controllers zurück
        status = {
            "Lights": self.lights,
            "Heater": self.heater,
            "AC": self.ac
        }
        return status

# Beispiel für die Verwendung des Home Automation Controllers
if __name__ == "__main__":
    controller = HomeAutomationController()

    controller.add_light("LivingRoom", False)
    controller.add_light("Bedroom", True)

    controller.set_heater(True)
    controller.set_ac(False)

    print("Status des Home Automation Controllers:")
    print(controller.get_status())
