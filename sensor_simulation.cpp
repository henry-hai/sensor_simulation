#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <numeric>
#include <iomanip> 

using namespace std;

// Sensor class to represent a hardware sensor
class Sensor {
public:
    string sensorName;
    double threshold;
    vector<double> readings;

    Sensor(string name, double thresh) : sensorName(name), threshold(thresh) {}

    // Function to calculate the average of the stored readings
    double calculateRollingAverage() {
        if (readings.empty()) return 0.0;
        double sum = accumulate(readings.begin(), readings.end(), 0.0);
        return sum / readings.size();
    }

    // Log the reading to a file and internal storage
    void logReading(double value, ofstream& logFile) {
        readings.push_back(value);
        if (readings.size() > 10) {
            readings.erase(readings.begin());
        }

        time_t now = time(0);
        char* dt = ctime(&now);
        string timestamp(dt);
        timestamp.pop_back(); // Remove the newline character
        
        // Print to Terminal
        cout << "[" << timestamp << "] " << sensorName << " Reading: " 
             << fixed << setprecision(2) << value << " °C";
        if (value > threshold) {
            cout << "  <-- ALERT: Above Threshold!";
        }
        cout << endl;

        // Write to File
        logFile << "[" << timestamp << "] " << sensorName << " Reading: " 
                << fixed << setprecision(2) << value << " °C";
        if (value > threshold) {
            logFile << "  <-- ALERT: Above Threshold!";
        }
        logFile << endl;
    }
};

int main() {
    // Seed for random values
    srand(static_cast<unsigned int>(time(0)));

    // Creating a sensor object with a name and threshold
    Sensor tempSensor("TempSensor1", 75.0);

    // Open log file in append mode (does not overwrite existing logs)
    ofstream logFile("sensor_log.txt", ios::app);

    if (logFile.is_open()) {
        cout << "Simulating sensor readings..." << endl;
        
        for (int i = 0; i < 15; ++i) {
            // Generates a random double between 20.00 and 100.00
            double simulatedTemp = 20.0 + (static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / 80.0)));
            tempSensor.logReading(simulatedTemp, logFile);
        }

        // Generate the System Health Report based on rolling average
        double avg = tempSensor.calculateRollingAverage();
        
        string reportHeader = "\n--- SYSTEM HEALTH REPORT ---\n";
        string reportFooter = "---------------------------\n";

        cout << reportHeader << "Final Rolling Average: " << fixed << setprecision(2) << avg << " °C" << endl;
        cout << "Status: " << (avg > tempSensor.threshold ? "CRITICAL" : "OPERATIONAL") << endl << reportFooter;

        logFile << reportHeader << "Final Rolling Average: " << fixed << setprecision(2) << avg << " °C" << endl;
        logFile << "Status: " << (avg > tempSensor.threshold ? "CRITICAL" : "OPERATIONAL") << endl << reportFooter;

        logFile.close();
        cout << "Simulation complete. Check sensor_log.txt for permanent records." << endl;
    } else {
        cerr << "Unable to open file" << endl;
    }

    return 0;
}