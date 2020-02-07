# Team 2053 Tigertronics code for 2020 FRC Season

This is our code for the 2020 FRC season. We are using the rewritten Command Based Framework and C++.

## Getting Started

This will help you to get started on working with our FRC code.

### Prerequisites

- Go to this link and follow along with directions for Windows and C++: [WPILib Getting Started](https://docs.wpilib.org/en/latest/docs/software/getting-started/index.html)

### Installing

Clone the repository
```
git clone https://github.com/team2053tigertronics/Robot2020.git
```
Open the Robot2020 folder in Visual Studio Code.

Then, to build you can use the shortcute Ctrl+Shift+P, then type in WPILib: Build Robot Code

## Deployment

To deploy to the robot, connect over usb, ethernet or Wifi.
Then, to deploy you can use the shortcute Ctrl+Shift+P, then type in WPILib: Deploy Robot Code

## Built With

* [WPILib](https://github.com/wpilibsuite/allwpilib) - The backend to interface with the RoboRIO
* [CTRE Phoenix](https://github.com/CrossTheRoadElec/Phoenix-api) - Interface for CTRE Talon SRX's
* [REV Robotics Spark Max API](http://www.revrobotics.com/) - Interface for Rev Robotics Spark Max
* [NavX API](https://pdocs.kauailabs.com/navx-mxp/) - Interface for Kauai Labs IMU
* [Websocketpp](https://github.com/zaphoyd/websocketpp) - Websocket Library for C++. Used for communicating with Jetson
* [ASIO](https://think-async.com/) - Asyncronous Networking Library. Used with websocketpp
* [rosbridgecpp](https://github.com/ppianpak/rosbridgecpp) - Modified version to used with above libs

## Contributing

Please read [CONTRIBUTING.md](CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Authors

* **Cathy Deskur** - *Command and Subsystem Programming* - [chdeskur](https://github.com/chdeskur)
* **Drew Williams** - *Backend Programming* - [jreneew2](https://github.com/jreneew2)

See also the list of [contributors](https://github.com/team2053tigertronics/Robot2020/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

* Doug Williams for helping with algorithm design and debugging
* Tim Greer for helping with debugging and math
* Mike Caruso for helping with debugging and networking
* Jake Allison for working on ROS integration and design
* FRC Discord (specifically @calcmogul) for help with advanced C++ concepts
* FRC Team 900 for networking and ROS help

