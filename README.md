# Sensor Simulation Project (C++)

A C++ program that simulates a temperature sensor, prints readings in real time, and appends timestamped logs to disk for later analysis. The simulation flags anomalous readings above a threshold and produces a simple “system health” report using a rolling average of recent values.

## Features

- **OOP sensor model**: A custom `Sensor` class encapsulates sensor properties (name, threshold) and historical readings.
- **Real-time logging**: Each simulated reading is printed to the terminal and appended to `sensor_log.txt` with a timestamp.
- **Anomaly detection**: Readings above the configured threshold are automatically flagged with an `ALERT`.
- **Historical tracking**: Maintains the **last 10 readings** in a `vector<double>` and computes a rolling average.
- **Health report**: Outputs and logs a final status (`OPERATIONAL` vs `CRITICAL`) based on the rolling average vs threshold.

## How it works

- Generates **15** random temperature values in the range **20.00°C to 100.00°C**
- Uses a threshold of **75.0°C**
- Keeps only the most recent **10** readings to compute the rolling average
- Appends output to `sensor_log.txt` (does not overwrite existing logs)

## Build and run

From this directory:

```bash
g++ -std=c++17 -O2 sensor_simulation.cpp -o sensor_simulation
./sensor_simulation
```

After running, check `sensor_log.txt` for the appended logs.

## Output format (example)

Each reading is logged like:

```text
[Wed Jan 28 14:03:21 2026] TempSensor1 Reading: 82.41 °C  <-- ALERT: Above Threshold!
```

At the end, a health report is printed and appended:

```text
--- SYSTEM HEALTH REPORT ---
Final Rolling Average: 63.12 °C
Status: OPERATIONAL
---------------------------
```

## Files

- `sensor_simulation.cpp`: Source code (Sensor class + simulation driver).
- `sensor_simulation`: Compiled binary (if present).
- `sensor_log.txt`: Append-only log file created/updated by the program.

