### Project structures

FastIPC/
├── include/            # Public headers (API)
├── src/                # Internal implementation
│   ├── core/           # Core IPC abstractions
│   ├── backend/        # OS-specific backends: shm, pipes, uds, etc.
│   ├── utils/          # Logging, error handling, etc.
├── examples/           # Usage demos (AI pipe, benchmark tools, etc.)
├── tests/              # Unit/integration tests
├── CMakeLists.txt
└── README.md

### Build

```powershell
mkdir build
cd build

# Configure project
cmake ..

# Build project
cmake --build .
```