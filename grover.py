# -*- coding: utf-8 -*-
import numpy as np
import sys

# Workspace to hold the quantum state
workspace = np.array([[1.]])

# Define gates as matrices
H_gate = (1/np.sqrt(2)) * np.array([[1, 1],
                                    [1, -1]])

X_gate = np.array([[0, 1],
                   [1, 0]])

Z_gate = np.array([[1, 0],
                   [0, -1]])

# Global list to store qubit states (vectors)
qubit_states = []

def pushQubit(index, state):
    """Add a new qubit in state |+⟩ if [1,1] is passed"""
    global qubit_states
    norm_state = np.array(state) / np.linalg.norm(state)
    qubit_states.insert(index, norm_state)

def applyGate(gate, *qubits):
    """Apply a gate to one or more qubits (simplified)"""
    global workspace, qubit_states
    # This is a simplified gate application for small simulations
    for index in qubits:
        qubit_states[index] = np.dot(gate, qubit_states[index])

def TOFFn_gate(controls, target):
    """Simplified Toffoli (multi-controlled NOT) gate"""
    # Not a real Toffoli simulation, just flips target if all controls are 1
    if all(np.allclose(q, [0, 1]) for q in [qubit_states[i] for i in controls]):
        qubit_states[target] = np.dot(X_gate, qubit_states[target])

def probQubit(index):
    """Return probabilities for qubit 0 or 1"""
    state = qubit_states[index]
    return np.abs(state) ** 2

def measureQubit(index):
    """Measure a qubit probabilistically"""
    probs = probQubit(index)
    return np.random.choice([0, 1], p=probs)

# Oracle: checks if all qubits are zero
def zero_phaseOracle(qubits):
    for qubit in qubits:
        applyGate(X_gate, qubit)
    applyGate(Z_gate, *qubits)
    for qubit in qubits:
        applyGate(X_gate, qubit)

# Oracle: check if qubit pattern is 111101 (negate qubit 1)
def sample_phaseOracle(qubits):
    applyGate(X_gate, qubits[1])
    applyGate(Z_gate, *qubits)
    applyGate(X_gate, qubits[1])

# Main Grover search algorithm
def groverSearch(n, printProb=True):
    global qubit_states
    qubit_states = []

    # Step 1: determine number of iterations
    optimalTurns = int(np.pi / 4 * np.sqrt(2 ** n) - 0.5)
    qubits = list(range(n))

    # Step 2: initialize qubits into superposition
    for qubit in qubits:
        pushQubit(qubit, [1, 1])  # this is |+⟩ after normalization

    # Step 3: run Grover iterations
    for _ in range(optimalTurns):
        sample_phaseOracle(qubits)
        for qubit in qubits:
            applyGate(H_gate, qubit)
        zero_phaseOracle(qubits)
        for qubit in qubits:
            applyGate(H_gate, qubit)

        if printProb:
            print("Qubit 0 probabilities: {}".format(probQubit(qubits[0])))

    # Step 4: Measure and return result
    print("Measurement result:")
    for qubit in reversed(qubits):
        sys.stdout.write(str(measureQubit(qubit)))
        sys.stdout.flush()
    print()

for _ in range(10):
    groverSearch(6, printProb=False)
