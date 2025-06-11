# Portable Test Library Interface (PTLIX)

## Overview
PTLIX is a portable test library interface that provides a unified way to interact with various software-based self tests (SBSTs) in software test libraries. It is designed to be easy to use and flexible, allowing developers to write tests that can run on different platforms and environments without modification.
It can be integrated into existing projects with minimal effort. PTLIX is particularly useful for developers who need to maintain hardware test suites that work across different operating systems.

## Installation
To install PTLIX, clone the repository and install the necessary dependencies:

```bash
git clone https://github.com/yourusername/ptlix.git
cd ptlix
```

## Building
PTLIX uses meson for building the project. To build the project, navigate to the root directory of the cloned repository and run:
```bash
cd ptlix
meson setup --cross-file ./targets/cross_file.txt build
cd build
meson compile 
```

### Build Configuration

You can customize the build configuration by modifying the `meson.build` file or by passing options to the `meson setup` command. For example, you can specify different compiler flags, enable or disable features, or set the target architecture.

You can also use the `meson configure` command to change build options after the initial setup. For example, to enable debug mode, you can run:
```bash
meson configure -Ddebug=true
```

See the `meson_options.txt` file for more details on the build configuration. The main options are:

- `library_type`: Build shared or static library (`shared`/`static`)
- `build_tests`: Build unit tests (default: `false`)
- `build_docs`: Build documentation (default: `true`)
- `runtime_tests`: Compile SBSTs runtime (default: `true`)
- `boot_tests`: Compile SBSTs boot (default: `false`)
- `runtime_tests_relocation`: Compile SBSTs runtime with relocation (default: `false`)
- `runtime_tests_relocation_table`: Compile SBSTs runtime with custom relocation table (default: `false`)

### Requirements
- Compiler supporting C++11 or later
- Meson for building the project 1.1.0 or later
- Additional libraries or tools may be required depending on your platform and usage

## Documentation
Documentation for PTLIX is available in the `docs/` directory. It includes API references, usage examples, and guidelines for writing tests.
You need to set the `build_docs` option to `true` in the `meson_options.txt` file to build the documentation. Afterward, you can generate the documentation by running:
```bash
meson setup --cross-file ./targets/cross_file.txt build
```
You can view the documentation by opening the generated HTML files in a web browser.

## Unit Tests
TO be added.

## PTLIX Structure Overview
The PTLIX project is organized into several directories, each serving a specific purpose:
- `meson.build`:  The main build script for the PTLIX project, defining the build configuration and targets.
- `meson_options.txt` : Configuration options for the PTLIX build, allowing customization of the build process.
- `targets/`: Contains cross-compilation files and configurations for different target platforms and architectures.
- `targets/cross_file.txt`: Cross-compilation configuration file for building PTLIX on different platforms.
- `src/`: Core source code for the PTLIX library, including implementation files and submodules.
- `src/cfg/`: Configuration headers and source files for the library.
- `src/error_management/`: Error management logic, including error handling functions and definitions.
- `src/scheduler/`: Scheduling logic for tests and related utilities.
- `src/TSSP/`: Test Suite Support Package: contains platform- or test-type-specific support code.
- `src/tests/`: Test implementations and test setup code, organized by compiler, ISA, and test type.
- `include/`: Public header files for the PTLIX library, defining the API and core types.
- `linker_scripts/`: Linker scripts for various architectures and toolchains.
- `docs/`: Project documentation, including API references and usage guides.
- `tests/`: Unit and integration test suites for the library and its bindings.

## License
This project is licensed under the Apache License. See the [LICENSE](LICENSE) file for details.

## Contributing
Contributions are welcome! Please read the [CONTRIBUTING.md](CONTRIBUTING.md) file for details on how to contribute to this project.
