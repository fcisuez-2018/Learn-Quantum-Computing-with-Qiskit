# Qiskit C API Example

A minimal, professional demonstration of how to build and consume the Qiskit C API (`qiskit‑cext`) on WSL (Ubuntu), generate C headers with `cbindgen`, and link them in a standalone C program.



## Introduction

This repository shows you how to:

1. Compile the Rust‑based `qiskit‑cext` crate as a shared library (`.so`)  
2. Generate C headers (`.h`) automatically with `cbindgen`  
3. Copy artifacts into a lightweight demo folder  
4. Compile and run a C example that exercises the Qiskit C API



## Prerequisites

- **Windows Subsystem for Linux (WSL)** running Ubuntu/Debian  
- **Rust toolchain** (`rustc` 1.88+, `cargo`)  
- **GNU C compiler** (`gcc`, part of `build-essential`)  
- **Python 3** development headers (`python3-dev`) via system or Conda  
- **Miniconda** (or other Python distribution) for runtime linkage  
- **cbindgen** (install with `cargo install cbindgen`)  
- **Qiskit monorepo** cloned locally (to build the `qiskit‑cext` crate)



## Repository Layout

After setup, you will have:

```
qiskit_in_C/
├── include/
│   ├── qiskit.h
│   └── qiskit/
│       └── complex.h
├── lib/
│   └── libqiskit_cext.so
└── example.c
```



- **include/** – C headers generated and supplemented  
- **lib/**   – Compiled shared library  
- **example.c** – C program demonstrating API usage

---

## Installation

### Step 1 – Build `qiskit‑cext` in the Qiskit Monorepo

1. Change into your local clone of Qiskit:  

        ```c
        cd ~/qiskit  
        ```

2. Ensure the Python runtime library is discoverable:  
    
        ```c
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/<user>/miniconda3/lib  
        ```

3. Compile the Rust crate as a C‑compatible shared library:  

        ```c    
        cargo rustc --release --crate-type=cdylib -p qiskit‑cext  
        ```

   - Outputs `target/release/libqiskit_cext.so`

4. Generate the primary C header with `cbindgen`:  
    
        ```c
        mkdir -p dist/c/include  
        cbindgen \
          --crate qiskit‑cext \
          --output dist/c/include/qiskit.h  
        ```

5. Create the supplementary complex‑number header:  


        ```c
        mkdir -p dist/c/include/qiskit  
        cat << 'EOF' > dist/c/include/qiskit/complex.h
        #ifndef QISKIT_COMPLEX_H
        #define QISKIT_COMPLEX_H

        typedef struct {
            double re;
            double im;
        } QkComplex64;

        #endif
        EOF  
        ```



### Step 2 – Copy Artifacts to Your Demo Folder

1. Create your demo directory and subfolders:  

        ```c
        mkdir -p ~/qiskit_in_C/include/qiskit  
        mkdir -p ~/qiskit_in_C/lib  
        ```

2. Copy the compiled library:  
    
        ```c
        cp target/release/libqiskit_cext.so ~/qiskit_in_C/lib/  
        ```

3. Copy generated headers:  
    
        ```c
        cp dist/c/include/qiskit.h \
           ~/qiskit_in_C/include/  
        cp dist/c/include/qiskit/complex.h \
           ~/qiskit_in_C/include/qiskit/  
        ```

---

## Usage

### Compile the C Example

1. Change into your demo folder:  
    
        ```c
        cd ~/qiskit_in_C 
        ``` 

2. Invoke GCC with the proper include and link paths:  
    
        ```c
        gcc example.c \
          -o example \
          -I./include \
          -L./lib -lqiskit_cext \
          -Wl,-rpath,"$(pwd)/lib"  
        ```

   - `-I./include` – header lookup  
   - `-L./lib -lqiskit_cext` – link against `libqiskit_cext.so`  
   - `-Wl,-rpath,"$(pwd)/lib"` – embed runtime search path

### Run the Example

1. If not using embedded rpath, export again:  

        ```c
    
        export LD_LIBRARY_PATH=$(pwd)/lib:/home/<user>/miniconda3/lib  
        ```

2. Execute:  
    
        ```c
        ./example  
        ```

**Expected output**  


```c
num_qubits: 100
num_terms: 1
observable: SparseObservable { ... }
```


---

## Troubleshooting

- **Header not found**  
  Verify `-I./include` matches where you placed `qiskit.h`.  
- **Undefined reference**  
  Ensure `-lqiskit_cext` and `-L./lib` point to the correct `.so`.  
- **Permission denied**  
  Run `chmod +x example` or adjust directory permissions.

---

## Contributing

1. Fork the repository  
2. Create a branch (`git checkout -b feature/your-feature`)  
3. Commit your changes (`git commit -m "Add feature..."`)  
4. Push to your fork (`git push origin feature/your-feature`)  
5. Open a pull request for review

---

