# physics-simulator

A GTK3 desktop application that simulates particle physics in two modes — kinematic and dynamic — built for the Programming and Algorithms course.

[![License: MIT](https://img.shields.io/badge/License-MIT-3da639.svg)](LICENSE)
![Status](https://img.shields.io/badge/status-completed-6f42c1)

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](https://en.cppreference.com/w/c)
[![Make](https://img.shields.io/badge/Make-4495D5?logo=make&logoColor=white)](https://www.gnu.org/software/make/)
[![GTK3](https://img.shields.io/badge/GTK-3-4A86CF?logo=gnome&logoColor=white)](https://docs.gtk.org/gtk3/)

[Portuguese](README.pt.md) | English

## About

Particle simulator with two independent modes. In kinematic mode particles follow constant-acceleration trajectories; in dynamic mode Newton's second law is applied with configurable forces and gravity. The UI is built with GTK3 and Glade, and simulations are rendered with Cairo.

## Simulation modes

| Mode | Description |
| ---- | ----------- |
| **Kinematic** | Constant acceleration — position and velocity updated via s = s₀ + v·t + ½·a·t². |
| **Dynamic** | Variable acceleration — resultant force divided by mass yields acceleration at each step. |

## Requirements

| Tool | Version |
| ---- | ------- |
| GCC | 9+ |
| Make | 4+ |
| GTK3 | 3.24+ |
| Cairo | 1.16+ |
| GLib | 2.0+ |

Tested on Ubuntu/GNOME. Native execution on macOS is not supported.

## How to run

```bash
make run          # compile and launch the simulator
make phy_test     # run physics unit tests
make clean        # remove build artifacts
```

## License

Distributed under the **MIT** license, © 2024 Nycolas Souza.

The full text is in [LICENSE](LICENSE).
