# Hypoxia

High-level firmware project for the Hypoxia device controller (Arduino + DRV8825 + stepper motor).

## Documentation

For hardware wiring and component details, see:
- [docs/components.md](docs/components.md)

## Prerequisites

- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO IDE extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)
- Arduino Uno connected over USB

## Install PlatformIO

1. Install VS Code.
2. Open VS Code and go to Extensions.
3. Search for PlatformIO IDE.
4. Install PlatformIO IDE (publisher: PlatformIO).
5. Restart VS Code if prompted.

## Open This Project

1. Open VS Code.
2. Select File -> Open Folder.
3. Choose this folder: Hypoxia.
4. Let PlatformIO initialize the environment.

## Build and Upload Firmware

### Option A: VS Code (PlatformIO UI)

1. Connect the Arduino Uno by USB.
2. In PlatformIO, select the Uno environment (env:uno).
3. Click Build.
4. Click Upload.

### Option B: Command Line

From the project root, run:

```bash
pio run
pio run -t upload
```

## Run the Program

After upload is complete and the Arduino is powered:
- Press the button on the Arduino to start the program.

## Notes

- Board configuration is defined in [platformio.ini](platformio.ini) under env:uno.
