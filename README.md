# Vehicle Braking Simulation

This is a C++ program that simulates the braking behaviour of a vehicle using SFML for rendering. The program models vehicle motion under different surface conditions, calculating braking distance and deceleration. It also includes interactive UI elements, such as buttons and text fields, for starting and resetting the simulation, as well as displaying real-time data like current speed and braking distance.

## Features

- **Vehicle Simulation**: Simulates a vehicle's motion based on its starting speed, braking force, and surface friction.
- **Real-time Display**: Shows the vehicle's current speed, total braking distance, and more.
- **Interactive Buttons**: Start and reset the simulation using UI buttons.
- **Input Fields**: Modify the vehicle's starting speed using the input text box.
- **SFML Graphics**: Utilizes SFML to render the vehicle and track. as well as manage UI components.

## Getting Started

### Prerequisites

Make sure you have the following installed:

- C++17 or higher
- [SFML 2.5.1+](https://www.sfml-dev.org/download.php) (Simple and Fast Multimedia Library)

### Compilation and Running

1. Clone the rempository:
  ```bash
  git clone https://github.com/Lmaenner12/BasicSimulation.git
  cd BasicSimulation
  ```
2. Compile the program using Make.
  ```bash
  make
  ```
3. Run the executable
  ```bash
  ./main
  ```

### Controls

- **Start Button**: Begins the vehicle's braking animation.
- **Reset Button**: Resets the vehicle to its initial state and speed.
- **Text Input**: Allows setting the vehicle's starting speed.

## Code Structure

- `src/`: Contains the C++ source code for the simulation, including the vehicle logic, UI components, and the main simulation loop.
- `include/`: Header files for each component.
- `resources/`: Folder containing required resources like the vehicle sprite (`auto.png`) and font (`arial.ttf`).

## How it Works

The program simulates the motion of a vehicle on a straight road. It models deceleration based on surface friction (`mue_h`), initial velocisty, and braking time. The simulation calculates the vehicle's position over time and moves the vehicle sprite accordingly.

The braking distance and current speed are updated dynamically and displayed in the UI.
