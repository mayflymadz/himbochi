# Set Up Core
arduino-cli core update-index
arduino-cli core install arduino:avr

# Create Project
arduino-cli sketch new my_project
cd my_project

# Compile
arduino-cli compile --fqbn arduino:avr:uno

# Flash
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno .

# Find Board Serial Port
arduino-cli board list