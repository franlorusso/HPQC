# -*- coding: utf-8 -*-
import numpy as np

# Simulated quantum workspace
workspace = np.array([[1.0]])

# Push a qubit onto the stack
def pushQubit(weights):
    global workspace
    workspace = np.reshape(workspace, (1, -1))
    workspace = np.kron(workspace, weights)

# Apply a quantum gate to the top qubits
def applyGate(gate_matrix):
    global workspace
    workspace = np.reshape(workspace, (-1, gate_matrix.shape[0]))
    np.matmul(workspace, gate_matrix.T, out=workspace)

# Move the k-th qubit (from top) to top of stack (TOS)
def tosQubit(k):
    global workspace
    if k > 1:
        workspace = np.reshape(workspace, (-1, 2, 2**(k - 1)))
        workspace = np.swapaxes(workspace, -2, -1)

# --- Demonstration of tosQubit ---

# Start fresh
workspace = np.array([[1.]])

# Push two qubits: first |0⟩, then a superposition
pushQubit([1, 0])          # Qubit 1 (bottom)
pushQubit([0.6, 0.8])      # Qubit 2 (top)
print("Before tosQubit(2):", workspace)

# Move qubit 2 (from top) to top of stack
tosQubit(2)
print("After tosQubit(2) - reshaped:", workspace)

# Optional: reshape it back into a flat row
print("Reshaped back to row:", np.reshape(workspace, (1, -1)))

