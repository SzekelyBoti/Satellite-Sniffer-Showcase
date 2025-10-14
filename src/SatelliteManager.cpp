#include "SatelliteManager.h"
#include <fstream>
#include "Satellite.h"
#include "TLEtoGPSConverter.h"
#include "GPSPosition.h"
#include "TLEParser.h"

SatelliteManager::SatelliteManager() {}
SatelliteManager::~SatelliteManager() {}

/**
 * @brief Loads satellite TLE data from a file and initializes satellites.
 *
 * @param file Path to the TLE file. The file is expected to have each satellite's
 *             data in three consecutive lines: name, line1, line2.
 *
 * This function reads the file line by line:
 *   1. Reads the satellite name, followed by the two TLE lines.
 *   2. Uses TLEParser to create a SatelliteData object for each satellite.
 *   3. Initializes a Satellite object from the parsed data.
 *   4. Adds the Satellite to the satellites vector.
 *   5. Deletes the temporary SatelliteData object to avoid memory leaks.
 *
 * If the file cannot be opened, the function silently returns without loading anything.
 */
void SatelliteManager::loadFromFile(const std::string& file) {
    std::ifstream in(file);
    if (!in.is_open()) return;

    std::string name, line1, line2;
    TLEParser parser;

    while (std::getline(in, name) &&
        std::getline(in, line1) &&
        std::getline(in, line2)) {

        SatelliteData* data = parser.parse(name, line1, line2);

        Satellite sat ("", "", "", GPSPosition());
        sat.initFromData(data);
        satellites.push_back(sat);

        delete data;
    }
}

/**
 * @brief Updates the positions of all satellites based on the current simulation time.
 *
 * @param converter Pointer to a TLEtoGPSConverter (or SGP4Converter) used to compute
 *                  the satellite's current GPS position from its TLE data.
 * @param simTime The current simulation time in seconds. This is used to calculate
 *                the satellite's position at that moment.
 *
 * This function iterates through all satellites stored in the manager and calls
 * each satellite's updatePosition() method, passing the converter and simulation
 * time to compute the updated GPS coordinates.
 */
void SatelliteManager::updateAllPositions(TLEtoGPSConverter* converter, double simTime) {
    for (auto& sat : satellites) {
        sat.updatePosition(converter, simTime);
    }
}

/**
 * @brief Retrieves the current GPS positions of all visible satellites.
 *
 * @return A vector of GPSPosition objects representing the positions of satellites
 *         that are currently marked as visible.
 *
 * This function iterates through all satellites stored in the manager, checks
 * whether each satellite is visible using isVisible(), and collects the positions
 * of visible satellites into a vector.
 */
std::vector<GPSPosition> SatelliteManager::getPositions() const {
    std::vector<GPSPosition> positions;
    for (const auto& sat : satellites) {
        if (sat.isVisible()) {
            positions.push_back(sat.getPosition());
        }
    }
    return positions;
}

/**
 * @brief Retrieves the names of all satellites managed by the SatelliteManager.
 *
 * @return A vector of strings containing the names of all satellites.
 *
 * This function iterates through the internal list of satellites and extracts
 * each satellite's name using getName(), collecting them into a vector.
 */
std::vector<std::string> SatelliteManager::getSatelliteNames() const {
    std::vector<std::string> names;
    for (const auto& sat: satellites) {
        names.push_back(sat.getName());
    }
    return names;
}

/**
 * @brief Toggles the visibility of a satellite at a given index.
 *
 * @param index The index of the satellite in the internal list.
 *
 * This function checks if the provided index is valid. If it is, it flips
 * the visibility state of the satellite at that index. Visible satellites
 * become hidden, and hidden satellites become visible.
 */
void SatelliteManager::toggleSatellite(int index) {
    if (index >= 0 && index < satellites.size()) {
        satellites[index].setIsVisible(!satellites[index].isVisible());
    }
}

/**
 * @brief Checks if a satellite at a given index is visible.
 *
 * @param index The index of the satellite in the internal list.
 * @return true if the satellite is visible; false if hidden or if the index is invalid.
 *
 * This function safely verifies the index bounds before accessing the satellite.
 */
bool SatelliteManager::isSatelliteVisible(int index) const {
    if (index >= 0 && index < satellites.size()) {
        return satellites[index].isVisible();
    }
    return false;
}

/**
 * @brief Returns the total number of satellites managed.
 *
 * @return The count of satellites stored in the manager.
 *
 * Useful for iterating over all satellites or validating indices.
 */
size_t SatelliteManager::getSatelliteCount() const {
    return satellites.size();
}
