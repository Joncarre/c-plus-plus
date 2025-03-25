# MultaMatic

MultaMatic is a system for managing traffic fines for speeding. The road network contains monitored stretches where a camera is placed at the beginning of the stretch and another at the end. Each time a car passes in front of a camera, a photo of its license plate is taken and the time it passed is noted; if the time elapsed between the photo at the beginning and the photo at the end is too short, a fine is issued. For simplicity, we will assume that the sections do not share cameras or overlap each other. The public TAD operations are:

- *insertSpan*: adds a new span to the system. It receives a leg identifier, the identifiers of its start and end cameras, and the minimum number of seconds that must elapse between the start and end photos in order not to receive a penalty. If the section already existed, it must generate an error.

- *fotoEntrada*: it is invoked every time a car enters a monitored section. It receives the camera identifier, the license plate of the car, and the current time (in seconds since January 1, 1970).

- *photoExit*: it is invoked each time a car exits a monitored section. It receives the camera identifier, the license plate of the car, and the current time. If the car has gone too fast on the stretch, it will be fined.

- *finesByNumber*: returns the number of fines associated to a license plate.

- *finesBySections*: returns a list of the license plates of the cars fined in a given section. If a car has been fined several times, its license plate will appear several times in the list. If the section does not exist, it should generate an error.
