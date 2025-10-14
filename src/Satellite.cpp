#include "Satellite.h"
#include "TLEtoGPSConverter.h"
#include "SatelliteData.h"

/**
 * @brief Constructs a Satellite object with given TLE data and initial position.
 *
 * @param name      The name of the satellite.
 * @param tleLine1  The first line of the TLE data.
 * @param tleLine2  The second line of the TLE data.
 * @param position  The initial GPS position of the satellite.
 *
 * Initializes a satellite with TLE data, its current position, and sets it as visible by default.
 */
Satellite::Satellite(const std::string &name,
                     const std::string &tleLine1,
                     const std::string &tleLine2,
                     GPSPosition position) : name(name), tleLine1(tleLine1), tleLine2(tleLine2), position(position), visible(true) {
}

Satellite::~Satellite() {
}

/**
 * @brief Updates the satellite's position based on TLE data and simulation time.
 *
 * @param converter Pointer to a TLEtoGPSConverter used to compute the satellite's current position.
 * @param simTime   The current simulation time in seconds.
 *
 * Uses the converter to calculate the satellite's position from its TLE lines and updates
 * the internal `position` member. If the converter is null, no update occurs.
 */
void Satellite::updatePosition(TLEtoGPSConverter* converter, double simTime) {
    if (converter) {
        position = converter->convert(tleLine1, tleLine2, simTime);
    }
}

/**
 * @brief Returns the current position of the satellite.
 *
 * @return GPSPosition The current latitude, longitude, and altitude of the satellite.
 *
 * This function provides read-only access to the satellite's position for rendering
 * or other calculations.
 */
GPSPosition Satellite::getPosition() const { return position; }

/**
 * @brief Initializes the Satellite object using data from a SatelliteData instance.
 *
 * @param data Pointer to a SatelliteData object containing the satellite's name and TLE lines.
 *
 * This function sets the satellite's name and TLE lines from the provided data, resets
 * its position to a default GPSPosition, and marks it as visible.
 */
void Satellite::initFromData(SatelliteData *data) {
    if (data) {
        name = data -> name;
        tleLine1 = data -> tleLine1;
        tleLine2 = data -> tleLine2;
        position = GPSPosition();
        visible = true;
    }
}

/**
 * @brief Checks if the satellite is currently visible.
 *
 * @return true if the satellite is visible, false otherwise.
 *
 * This function simply returns the internal `visible` flag, which can be
 * toggled using `setIsVisible()` or via the UIManager.
 */
bool Satellite::isVisible() const {
    return visible;
}

/**
 * @brief Sets the visibility state of the satellite.
 *
 * @param visible New visibility state (true = visible, false = hidden).
 *
 * This function updates the internal `visible` flag, which affects whether
 * the satellite will be rendered on the map or included in the UI.
 */
void Satellite::setIsVisible(bool visible) {
    this->visible = visible;
}

/**
 * @brief Returns the name of the satellite.
 *
 * @return const std::string& Reference to the satellite's name.
 *
 * This function allows other parts of the program to access the satellite's
 * identifier without copying the string. Useful for rendering in UI or logging.
 */
const std::string &Satellite::getName() const {
    return name;
}
