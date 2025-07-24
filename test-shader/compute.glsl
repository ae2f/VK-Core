#version 450
layout(local_size_x = 64, local_size_y = 1, local_size_z = 1) in; // Workgroup size: 64 threads
layout(std430, binding = 0) buffer Data {
    float values[];
} data;

void main() {
    uint idx = gl_GlobalInvocationID.x; // Unique thread ID
    if (idx < data.values.length()) {
        data.values[idx] += 1.0; // Increment each value
    }
}
