# IMG.LY ComputePipeline Project

This project is a minimal C++ implementation of a ComputePipeline, designed as a chain of actions that transforms an input item to a final result. Each step in the pipeline processes and passes its output (with additional metadata) to the next action.

## Design Overview

- **ComputePipeline**: The core class implemented in [`src/ComputePipeline.h`](src/ComputePipeline.h) and [`src/ComputePipeline.cpp`](src/ComputePipeline.cpp) is responsible for chaining the actions.
- **Action Steps**:
  - **Load Action**: The pipeline begins by loading an item based on a specified URI.  
    - If the URI starts with `file://`, loads from storage.
    - For URIs starting with `http://` or `https://`, treats them as fully qualified URLs.
    - For URIs starting with `bundle://`, loads from the application bundle.
  - **Processing Actions**:
    - For images: A decoding action is assumed.
    - For compressed data: A decompression action is assumed.
    - For JSON data: Conversion to a C++ object is assumed.
- **Result Passing**: The result of each action (an object holding the output and metadata) is passed to the next action in order to minimize unnecessary copies, especially given the expense of obtaining these results.
- **Extensibility**: It is up to the implementation to determine if a particular action can process the previous action’s output, until no further applicable action is found.

## Implementation Notes

- The actual logic for image decoding, decompression, and JSON processing is not implemented. Instead, placeholders mark where processing should occur.
- The design carefully handles performance and memory usage by ensuring minimal data copying between actions.

## Build Instructions

This project uses CMake as its build system. To build the project:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

## Time Considerations

This minimal implementation was designed to address the following key points:
- Handling of different URI types for loading.
- An extensible pipeline that processes content based on its detected type.
- Performance in terms of managing expensive action results.