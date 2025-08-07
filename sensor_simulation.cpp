#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cstring> // Needed for strcspn

using namespace std;

class Sensor {
private:
    string sensorName;
    float threshold;
    vector<float> lastReadings;
    const int maxReadings = 10;

public:
    Sensor(string name, float thresh) {
        sensorName = name;
        threshold = thresh;
        srand(time(0)); // Seed random generator
    }

    float readTemperature() {
        // Generate random float between 20.0 and 100.0
        float temp = 20.0 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (80.0)));
        storeReading(temp);
        return temp;
    }

    void storeReading(float value) {
        if (lastReadings.size() == maxReadings) {
            lastReadings.erase(lastReadings.begin()); // Remove oldest
        }
        lastReadings.push_back(value);
    }

    void logReading(float value) {
        ofstream logFile("sensor_log.txt", ios::app);
        time_t now = time(0);
        char* dt = ctime(&now);

        // Remove trailing newline from ctime string
        dt[strcspn(dt, "\n")] = 0;

        logFile << fixed << setprecision(2);
        logFile << "[" << dt << "] " << sensorName << " Reading: " << value << " °C";

        if (value > threshold) {
            logFile << "  <-- ALERT: Above Threshold!";
        }
        logFile << endl;

        logFile.close();
    }

    void printLastReadings() {
        cout << "\nLast " << lastReadings.size() << " readings for " << sensorName << ":\n";
        for (float val : lastReadings) {
            cout << fixed << setprecision(2) << val << " °C\n";
        }
    }
};

int main() {
    Sensor tempSensor("TempSensor1", 75.0);

    cout << "Starting Sensor Simulation...\n";

    for (int i = 0; i < 15; ++i) {
        float reading = tempSensor.readTemperature();
        cout << "Reading " << i + 1 << ": " << fixed << setprecision(2) << reading << " °C\n";
        tempSensor.logReading(reading);
    }

    tempSensor.printLastReadings();

    cout << "\nAll readings logged to 'sensor_log.txt'.\n";

    return 0;
}
