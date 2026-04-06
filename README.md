# Welcome to Himbochi!
A work-in progress tamagotchi-clone.
It is a virtual 'pet' game where you take care of a cute little himbo.
Is it weird to call a himbo a pet? Maybe. Is it unethical to turn men into pets? Probably. I love that one quote from Jurassic Park -- "Your scientists were so preoccupied with whether or not they could that they didn't stop to think if they should". I live by that. Every day. 

TW: A man who does not know how to care for his basic needs. 

All sprites and logic, written by me, mayflymadz.

I've still got a laundry list of bug fixes and scalability issues I want to do, but the base game functionality is in place. 
There's also still a lot of sprite work and expansion to do as well. I wrote all of this in one weekend, having never touched an arduino before, so I will work on it more when I have time. I'm excited to see where I go with it. Maybe there are different types of activities. Maybe the himbo can evolve into different himbos. It also needs a buzzer with sounds, for sure. 

Anyway, enjoy himbochi :)

## Building and flashing with arduino cli
I've never used Arduino IDE, but I'm sure it's even easier than the way I do it. 

# Set Up Core
`arduino-cli core update-index`
`arduino-cli core install arduino:avr`

# Create Project
`arduino-cli sketch new my_project`
`cd my_project`

# Compile
`arduino-cli compile --fqbn arduino:avr:uno`

# Flash
`arduino-cli upload -p /dev/tty* --fqbn arduino:avr:uno .`

# Find Board Serial Port
`arduino-cli board list`