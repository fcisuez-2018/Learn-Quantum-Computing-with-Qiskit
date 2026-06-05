#ifndef QISKIT_H
#define QISKIT_H

/* Generated with cbindgen:0.29.0 */

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#ifdef QISKIT_C_PYTHON_INTERFACE
    #include <Python.h>
#endif

#include "qiskit/complex.h"

#define QISKIT_VERSION_MAJOR 2
#define QISKIT_VERSION_MINOR 1
#define QISKIT_VERSION_PATCH 0

#define QISKIT_VERSION_NUMERIC(M,m,p) ((M)<<16|(m)<<8|(p))
#define QISKIT_VERSION (QISKIT_VERSION_MAJOR<<16 | QISKIT_VERSION_MINOR<<8 | QISKIT_VERSION_PATCH)

// Always expose [cfg(feature = "cbinding")] -- workaround for
// https://github.com/mozilla/cbindgen/issues/995
#define QISKIT_WITH_CBINDINGS

typedef struct QkQuantumRegister QkQuantumRegister;
typedef struct QkClassicalRegister QkClassicalRegister;


/**
 * Named handle to the alphabet of single-qubit terms.
 *
 * This is just the Rust-space representation.  We make a separate Python-space `enum.IntEnum` to
 * represent the same information, since we enforce strongly typed interactions in Rust, including
 * not allowing the stored values to be outside the valid `BitTerm`s, but doing so in Python would
 * make it very difficult to use the class efficiently with Numpy array views.  We attach this
 * sister class of `BitTerm` to `SparseObservable` as a scoped class.
 *
 * # Representation
 *
 * The `u8` representation and the exact numerical values of these are part of the public API.  The
 * low two bits are the symplectic Pauli representation of the required measurement basis with Z in
 * the Lsb0 and X in the Lsb1 (e.g. X and its eigenstate projectors all have their two low bits as
 * `0b10`).  The high two bits are `00` for the operator, `10` for the projector to the positive
 * eigenstate, and `01` for the projector to the negative eigenstate.
 *
 * The `0b00_00` representation thus ends up being the natural representation of the `I` operator,
 * but this is never stored, and is not named in the enumeration.
 *
 * This operator does not store phase terms of $-i$.  `BitTerm::Y` has `(1, 1)` as its `(z, x)`
 * representation, and represents exactly the Pauli Y operator; any additional phase is stored only
 * in a corresponding coefficient.
 *
 * # Dev notes
 *
 * This type is required to be `u8`, but it's a subtype of `u8` because not all `u8` are valid
 * `BitTerm`s.  For interop with Python space, we accept Numpy arrays of `u8` to represent this,
 * which we transmute into slices of `BitTerm`, after checking that all the values are correct (or
 * skipping the check if Python space promises that it upheld the checks).
 *
 * We deliberately _don't_ impl `numpy::Element` for `BitTerm` (which would let us accept and
 * return `PyArray1<BitTerm>` at Python-space boundaries) so that it's clear when we're doing
 * the transmute, and we have to be explicit about the safety of that.
 */
enum QkBitTerm
#ifdef __cplusplus
  : uint8_t
#endif // __cplusplus
 {
  /**
   * Pauli X operator.
   */
  QkBitTerm_X = 2,
  /**
   * Projector to the positive eigenstate of Pauli X.
   */
  QkBitTerm_Plus = 10,
  /**
   * Projector to the negative eigenstate of Pauli X.
   */
  QkBitTerm_Minus = 6,
  /**
   * Pauli Y operator.
   */
  QkBitTerm_Y = 3,
  /**
   * Projector to the positive eigenstate of Pauli Y.
   */
  QkBitTerm_Right = 11,
  /**
   * Projector to the negative eigenstate of Pauli Y.
   */
  QkBitTerm_Left = 7,
  /**
   * Pauli Z operator.
   */
  QkBitTerm_Z = 1,
  /**
   * Projector to the positive eigenstate of Pauli Z.
   */
  QkBitTerm_Zero = 9,
  /**
   * Projector to the negative eigenstate of Pauli Z.
   */
  QkBitTerm_One = 5,
};
#ifndef __cplusplus
typedef uint8_t QkBitTerm;
#endif // __cplusplus

/**
 * Integer exit codes returned to C.
 */
enum QkExitCode
#ifdef __cplusplus
  : uint32_t
#endif // __cplusplus
 {
  /**
   * Success.
   */
  QkExitCode_Success = 0,
  /**
   * Error related to data input.
   */
  QkExitCode_CInputError = 100,
  /**
   * Unexpected null pointer.
   */
  QkExitCode_NullPointerError = 101,
  /**
   * Pointer is not aligned to expected data.
   */
  QkExitCode_AlignmentError = 102,
  /**
   * Index out of bounds.
   */
  QkExitCode_IndexError = 103,
  /**
   * Error related to arithmetic operations or similar.
   */
  QkExitCode_ArithmeticError = 200,
  /**
   * Mismatching number of qubits.
   */
  QkExitCode_MismatchedQubits = 201,
  /**
   * Matrix is not unitary.
   */
  QkExitCode_ExpectedUnitary = 202,
  /**
   * Target related error
   */
  QkExitCode_TargetError = 300,
  /**
   * Instruction already exists in the Target
   */
  QkExitCode_TargetInstAlreadyExists = 301,
  /**
   * Properties with incorrect qargs was added
   */
  QkExitCode_TargetQargMismatch = 302,
  /**
   * Trying to query into the target with non-existent qargs.
   */
  QkExitCode_TargetInvalidQargsKey = 303,
  /**
   * Querying an operation that doesn't exist in the Target.
   */
  QkExitCode_TargetInvalidInstKey = 304,
};
#ifndef __cplusplus
typedef uint32_t QkExitCode;
#endif // __cplusplus

/**
 * @ingroup QkCircuit
 *
 * Units for circuit delays.
 */
enum QkDelayUnit
#ifdef __cplusplus
  : uint8_t
#endif // __cplusplus
 {
  /**
   * Seconds.
   */
  QkDelayUnit_S = 0,
  /**
   * Milliseconds.
   */
  QkDelayUnit_MS = 1,
  /**
   * Microseconds.
   */
  QkDelayUnit_US = 2,
  /**
   * Nanoseconds.
   */
  QkDelayUnit_NS = 3,
  /**
   * Picoseconds.
   */
  QkDelayUnit_PS = 4,
};
#ifndef __cplusplus
typedef uint8_t QkDelayUnit;
#endif // __cplusplus

enum QkGate
#ifdef __cplusplus
  : uint8_t
#endif // __cplusplus
 {
  QkGate_GlobalPhase = 0,
  QkGate_H = 1,
  QkGate_I = 2,
  QkGate_X = 3,
  QkGate_Y = 4,
  QkGate_Z = 5,
  QkGate_Phase = 6,
  QkGate_R = 7,
  QkGate_RX = 8,
  QkGate_RY = 9,
  QkGate_RZ = 10,
  QkGate_S = 11,
  QkGate_Sdg = 12,
  QkGate_SX = 13,
  QkGate_SXdg = 14,
  QkGate_T = 15,
  QkGate_Tdg = 16,
  QkGate_U = 17,
  QkGate_U1 = 18,
  QkGate_U2 = 19,
  QkGate_U3 = 20,
  QkGate_CH = 21,
  QkGate_CX = 22,
  QkGate_CY = 23,
  QkGate_CZ = 24,
  QkGate_DCX = 25,
  QkGate_ECR = 26,
  QkGate_Swap = 27,
  QkGate_ISwap = 28,
  QkGate_CPhase = 29,
  QkGate_CRX = 30,
  QkGate_CRY = 31,
  QkGate_CRZ = 32,
  QkGate_CS = 33,
  QkGate_CSdg = 34,
  QkGate_CSX = 35,
  QkGate_CU = 36,
  QkGate_CU1 = 37,
  QkGate_CU3 = 38,
  QkGate_RXX = 39,
  QkGate_RYY = 40,
  QkGate_RZZ = 41,
  QkGate_RZX = 42,
  QkGate_XXMinusYY = 43,
  QkGate_XXPlusYY = 44,
  QkGate_CCX = 45,
  QkGate_CCZ = 46,
  QkGate_CSwap = 47,
  QkGate_RCCX = 48,
  QkGate_C3X = 49,
  QkGate_C3SX = 50,
  QkGate_RC3X = 51,
};
#ifndef __cplusplus
typedef uint8_t QkGate;
#endif // __cplusplus

/**
 * A container for :class:`.QuantumCircuit` instruction listings that stores
 * :class:`.CircuitInstruction` instances in a packed form by interning
 * their :attr:`~.CircuitInstruction.qubits` and
 * :attr:`~.CircuitInstruction.clbits` to native vectors of indices.
 *
 * Before adding a :class:`.CircuitInstruction` to this container, its
 * :class:`.Qubit` and :class:`.Clbit` instances MUST be registered via the
 * constructor or via :meth:`.CircuitData.add_qubit` and
 * :meth:`.CircuitData.add_clbit`. This is because the order in which
 * bits of the same type are added to the container determines their
 * associated indices used for storage and retrieval.
 *
 * Once constructed, this container behaves like a Python list of
 * :class:`.CircuitInstruction` instances. However, these instances are
 * created and destroyed on the fly, and thus should be treated as ephemeral.
 *
 * For example,
 *
 * .. plot::
 *    :include-source:
 *    :no-figs:
 *
 *     qubits = [Qubit()]
 *     data = CircuitData(qubits)
 *     data.append(CircuitInstruction(XGate(), (qubits[0],), ()))
 *     assert(data[0] == data[0]) # => Ok.
 *     assert(data[0] is data[0]) # => PANICS!
 *
 * .. warning::
 *
 *     This is an internal interface and no part of it should be relied upon
 *     outside of Qiskit.
 *
 * Args:
 *     qubits (Iterable[:class:`.Qubit`] | None): The initial sequence of
 *         qubits, used to map :class:`.Qubit` instances to and from its
 *         indices.
 *     clbits (Iterable[:class:`.Clbit`] | None): The initial sequence of
 *         clbits, used to map :class:`.Clbit` instances to and from its
 *         indices.
 *     data (Iterable[:class:`.CircuitInstruction`]): An initial instruction
 *         listing to add to this container. All bits appearing in the
 *         instructions in this iterable must also exist in ``qubits`` and
 *         ``clbits``.
 *     reserve (int): The container's initial capacity. This is reserved
 *         before copying instructions into the container when ``data``
 *         is provided, so the initialized container's unused capacity will
 *         be ``max(0, reserve - len(data))``.
 *
 * Raises:
 *     KeyError: if ``data`` contains a reference to a bit that is not present
 *         in ``qubits`` or ``clbits``.
 */
typedef struct QkCircuit QkCircuit;

/**
 * An observable over Pauli bases that stores its data in a qubit-sparse format.
 *
 * See [PySparseObservable] for detailed docs.
 */
typedef struct QkObs QkObs;

/**
 * A control flow operation's target.
 *
 * TODO: move this to control flow mod once that's in Rust.
 */
typedef struct QkTarget QkTarget;

/**
 * Represents the mapping between qargs and ``InstructionProperties``
 */
typedef struct QkTargetEntry QkTargetEntry;

/**
 * The result from ``qk_transpiler_pass_standalone_vf2_layout()``.
 */
typedef struct QkVF2LayoutResult QkVF2LayoutResult;

/**
 * An individual operation count represented by the operation name
 * and the number of instances in the circuit.
 */
typedef struct {
  /**
   * A nul terminated string representing the operation name
   */
  const char *name;
  /**
   * The number of instances of this operation in the circuit
   */
  uintptr_t count;
} QkOpCount;

/**
 * An array of ``OpCount`` objects representing the total counts of all
 * the operation types in a circuit.
 */
typedef struct {
  /**
   * A array of size ``len`` containing ``OpCount`` objects for each
   * type of operation in the circuit
   */
  QkOpCount *data;
  /**
   * The number of elements in ``data``
   */
  uintptr_t len;
} QkOpCounts;

/**
 * A circuit instruction representation.
 *
 * This struct represents the data contained in an individual instruction in a ``QkCircuit``.
 * It is not a pointer to the underlying object, but contains a copy of the properties of the
 * instruction for inspection.
 */
typedef struct {
  /**
   * The instruction name
   */
  const char *name;
  /**
   * A pointer to an array of qubit indices this instruction operates on.
   */
  uint32_t *qubits;
  /**
   * A pointer to an array of clbit indices this instruction operates on.
   */
  uint32_t *clbits;
  /**
   * A pointer to an array of parameter values for this instruction.
   */
  double *params;
  /**
   * The number of qubits for this instruction.
   */
  uint32_t num_qubits;
  /**
   * The number of clbits for this instruction.
   */
  uint32_t num_clbits;
  /**
   * The number of parameters for this instruction.
   */
  uint32_t num_params;
} QkCircuitInstruction;

/**
 * A term in a ``QkObs``.
 *
 * This contains the coefficient (``coeff``), the number of qubits of the observable
 * (``num_qubits``) and pointers to the ``bit_terms`` and ``indices`` arrays, which have
 * length ``len``. It's the responsibility of the user that the data is coherent,
 * see also the below section on safety.
 *
 * # Safety
 *
 * * ``bit_terms`` must be a non-null, aligned pointer to ``len`` elements of type ``QkBitTerm``.
 * * ``indices`` must be a non-null, aligned pointer to ``len`` elements of type ``uint32_t``.
 */
typedef struct {
  /**
   * The coefficient of the observable term.
   */
  QkComplex64 coeff;
  /**
   * Length of the ``bit_terms`` and ``indices`` arrays.
   */
  uintptr_t len;
  /**
   * A non-null, aligned pointer to ``len`` elements of type ``QkBitTerm``.
   */
  QkBitTerm *bit_terms;
  /**
   * A non-null, aligned pointer to ``len`` elements of type ``uint32_t``.
   */
  uint32_t *indices;
  /**
   * The number of qubits the observable term is defined on.
   */
  uint32_t num_qubits;
} QkObsTerm;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Construct a new circuit with the given number of qubits and clbits.
 *
 * @param num_qubits The number of qubits the circuit contains.
 * @param num_clbits The number of clbits the circuit contains.
 *
 * @return A pointer to the created circuit.
 *
 * # Example
 *
 *     QkCircuit *empty = qk_circuit_new(100, 100);
 *
 */
QkCircuit *qk_circuit_new(uint32_t num_qubits, uint32_t num_clbits);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkQuantumRegister
 * Construct a new owning quantum register with a given number of qubits and name
 *
 * @param num_qubits The number of qubits to create the register for
 * @param name The name string for the created register. The name must be comprised of
 * valid UTF-8 characters.
 *
 * @return A pointer to the created register
 *
 * # Example
 *
 *     QkQuantumRegister *qr = qk_quantum_register_new(5, "five_qubits");
 *
 * # Safety
 *
 * The `name` parameter must be a pointer to memory that contains a valid
 * nul terminator at the end of the string. It also must be valid for reads of
 * bytes up to and including the nul terminator.
 */
QkQuantumRegister *qk_quantum_register_new(uint32_t num_qubits, const char *name);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkQuantumRegister
 * Free a quantum register.
 *
 * @param reg A pointer to the register to free.
 *
 * # Example
 *
 *     QkQuantumRegister *qr = qk_quantum_register_new(1024, "qreg");
 *     qk_quantum_register_free(qr);
 *
 * # Safety
 *
 * Behavior is undefined if ``reg`` is not either null or a valid pointer to a
 * ``QkQuantumRegister``.
 */
void qk_quantum_register_free(QkQuantumRegister *reg);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkClassicalRegister
 * Free a classical register.
 *
 * @param reg A pointer to the register to free.
 *
 * # Example
 *
 *     QkClassicalRegister *cr = qk_classical_register_new(1024, "creg");
 *     qk_classical_register_free(cr);
 *
 * # Safety
 *
 * Behavior is undefined if ``reg`` is not either null or a valid pointer to a
 * ``QkClassicalRegister``.
 */
void qk_classical_register_free(QkClassicalRegister *reg);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkClassicalRegister
 * Construct a new owning classical register with a given number of clbits and name
 *
 * @param num_clbits The number of clbits to create the register for
 * @param name The name string for the created register. The name must be comprised of
 * valid UTF-8 characters.
 *
 * @return A pointer to the created register
 *
 * # Example
 *
 *     QkClassicalRegister *cr = qk_classical_register_new(5, "five_qubits");
 *
 * # Safety
 *
 * The `name` parameter must be a pointer to memory that contains a valid
 * nul terminator at the end of the string. It also must be valid for reads of
 * bytes up to and including the nul terminator.
 */
QkClassicalRegister *qk_classical_register_new(uint32_t num_clbits, const char *name);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Add a quantum register to a given quantum circuit
 *
 * @param circuit A pointer to the circuit.
 * @param reg A pointer to the quantum register
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(0, 0);
 *     QkQuantumRegister *qr = qk_quantum_register_new(1024, "my_little_register");
 *     qk_circuit_add_quantum_register(qc, qr);
 *     qk_quantum_register_free(qr);
 *     qk_circuit_free(qc)
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit`` and
 * if ``reg`` is not a valid, non-null pointer to a ``QkQuantumRegister``.
 */
void qk_circuit_add_quantum_register(QkCircuit *circuit, const QkQuantumRegister *reg);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Add a classical register to a given quantum circuit
 *
 * @param circuit A pointer to the circuit.
 * @param reg A pointer to the classical register
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(0, 0);
 *     QkClassicalRegister *cr = qk_classical_register_new(24, "my_big_register");
 *     qk_circuit_add_classical_register(qc, cr);
 *     qk_classical_register_free(cr);
 *     qk_circuit_free(qc)
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit`` and
 * if ``reg`` is not a valid, non-null pointer to a ``QkClassicalRegister``.
 */
void qk_circuit_add_classical_register(QkCircuit *circuit, const QkClassicalRegister *reg);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Create a copy of a ``QkCircuit``.
 *
 * @param circuit A pointer to the circuit to copy.
 *
 * @return A new pointer to a copy of the input ``circuit``.
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(100, 100);
 *     QkCircuit *copy = qk_circuit_copy(qc);
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit``.
 */
QkCircuit *qk_circuit_copy(const QkCircuit *circuit);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Get the number of qubits the circuit contains.
 *
 * @param circuit A pointer to the circuit.
 *
 * @return The number of qubits the circuit is defined on.
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(100, 100);
 *     uint32_t num_qubits = qk_circuit_num_qubits(qc);  // num_qubits==100
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit``.
 */
uint32_t qk_circuit_num_qubits(const QkCircuit *circuit);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Get the number of clbits the circuit contains.
 *
 * @param circuit A pointer to the circuit.
 *
 * @return The number of qubits the circuit is defined on.
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(100, 50);
 *     uint32_t num_clbits = qk_circuit_num_clbits(qc);  // num_clbits==50
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit``.
 */
uint32_t qk_circuit_num_clbits(const QkCircuit *circuit);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Free the circuit.
 *
 * @param circuit A pointer to the circuit to free.
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(100, 100);
 *     qk_circuit_free(qc);
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not either null or a valid pointer to a
 * ``QkCircuit``.
 */
void qk_circuit_free(QkCircuit *circuit);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Append a ``QkGate`` to the circuit.
 *
 * @param circuit A pointer to the circuit to add the gate to.
 * @param gate The StandardGate to add to the circuit.
 * @param qubits The pointer to the array of ``uint32_t`` qubit indices to add the gate on. This
 *     can be a null pointer if there are no qubits for ``gate`` (e.g. ``QkGate_GlobalPhase``).
 * @param params The pointer to the array of ``double`` values to use for the gate parameters.
 *     This can be a null pointer if there are no parameters for ``gate`` (e.g. ``QkGate_H``).
 *
 * @return An exit code.
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(100, 0);
 *     uint32_t qubit[1] = {0};
 *     qk_circuit_gate(qc, QkGate_H, qubit, NULL);
 *
 * # Safety
 *
 * The ``qubits`` and ``params`` types are expected to be a pointer to an array of ``uint32_t``
 * and ``double`` respectively where the length is matching the expectations for the standard
 * gate. If the array is insufficently long the behavior of this function is undefined as this
 * will read outside the bounds of the array. It can be a null pointer if there are no qubits
 * or params for a given gate. You can check ``qk_gate_num_qubits`` and ``qk_gate_num_params`` to
 * determine how many qubits and params are required for a given gate.
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit``.
 */
QkExitCode qk_circuit_gate(QkCircuit *circuit,
                           QkGate gate,
                           const uint32_t *qubits,
                           const double *params);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Get the number of qubits for a ``QkGate``.
 *
 * @param gate The ``QkGate`` to get the number of qubits for.
 *
 * @return The number of qubits the gate acts on.
 *
 * # Example
 *
 *     uint32_t num_qubits = qk_gate_num_qubits(QkGate_CCX);
 *
 */
uint32_t qk_gate_num_qubits(QkGate gate);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Get the number of parameters for a ``QkGate``.
 *
 * @param gate The ``QkGate`` to get the number of qubits for.
 *
 * @return The number of parameters the gate has.
 *
 * # Example
 *
 *     uint32_t num_params = qk_gate_num_params(QkGate_R);
 *
 */
uint32_t qk_gate_num_params(QkGate gate);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Append a measurement to the circuit
 *
 * @param circuit A pointer to the circuit to add the measurement to
 * @param qubit The ``uint32_t`` for the qubit to measure
 * @param clbit The ``uint32_t`` for the clbit to store the measurement outcome in
 *
 * @return An exit code.
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(100, 1);
 *     qk_circuit_measure(qc, 0, 0);
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit``.
 */
QkExitCode qk_circuit_measure(QkCircuit *circuit, uint32_t qubit, uint32_t clbit);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Append a reset to the circuit
 *
 * @param circuit A pointer to the circuit to add the reset to
 * @param qubit The ``uint32_t`` for the qubit to reset
 *
 * @return An exit code.
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(100, 0);
 *     qk_circuit_reset(qc, 0);
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit``.
 */
QkExitCode qk_circuit_reset(QkCircuit *circuit, uint32_t qubit);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Append a barrier to the circuit.
 *
 * @param circuit A pointer to the circuit to add the barrier to.
 * @param num_qubits The number of qubits wide the barrier is.
 * @param qubits The pointer to the array of ``uint32_t`` qubit indices to add the barrier on.
 *
 * @return An exit code.
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(100, 1);
 *     uint32_t qubits[5] = {0, 1, 2, 3, 4};
 *     qk_circuit_barrier(qc, qubits, 5);
 *
 * # Safety
 *
 * The length of the array ``qubits`` points to must be ``num_qubits``. If there is
 * a mismatch the behavior is undefined.
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit``.
 */
QkExitCode qk_circuit_barrier(QkCircuit *circuit, const uint32_t *qubits, uint32_t num_qubits);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Append an arbitrary unitary matrix to the circuit.
 *
 * @param circuit A pointer to the circuit to append the unitary to.
 * @param matrix A pointer to the ``QkComplex64`` array representing the unitary matrix.
 *     This must be a row-major, unitary matrix of dimension ``2 ^ num_qubits x 2 ^ num_qubits``.
 *     More explicitly: the ``(i, j)``-th element is given by ``matrix[i * 2^n + j]``.
 *     The contents of ``matrix`` are copied inside this function before being added to the circuit,
 *     so caller keeps ownership of the original memory that ``matrix`` points to and can reuse it
 *     after the call and the caller is responsible for freeing it.
 * @param qubits A pointer to array of qubit indices, of length ``num_qubits``.
 * @param num_qubits The number of qubits the unitary acts on.
 * @param check_input When true, the function verifies that the matrix is unitary.
 *     If set to False the caller is responsible for ensuring the matrix is unitary, if
 *     the matrix is not unitary this is undefined behavior and will result in a corrupt
 *     circuit.
 * # Example
 *
 *     QkComplex64 c0 = qk_complex64_from_native(0);  // 0+0i
 *     QkComplex64 c1 = qk_complex64_from_native(1);  // 1+0i
 *
 *     const uint32_t num_qubits = 1;
 *     const uint32_t dim = 2;
 *     QkComplex64[dim * dim] unitary = {c0, c1,  // row 0
 *                                       c1, c0}; // row 1
 *
 *     QkCircuit *circuit = qk_circuit_new(1, 0);  // 1 qubit circuit
 *     uint32_t qubit = {0};  // qubit to apply the unitary on
 *     qk_circuit_unitary(circuit, unitary, qubit, num_qubits);
 *
 * # Safety
 *
 * Behavior is undefined if any of the following is violated:
 *
 *   * ``circuit`` is a valid, non-null pointer to a ``QkCircuit``
 *   * ``matrix`` is a pointer to a nested array of ``QkComplex64`` of dimension
 *     ``2 ^ num_qubits x 2 ^ num_qubits``
 *   * ``qubits`` is a pointer to ``num_qubits`` readable element of type ``uint32_t``
 *
 */
QkExitCode qk_circuit_unitary(QkCircuit *circuit,
                              const QkComplex64 *matrix,
                              const uint32_t *qubits,
                              uint32_t num_qubits,
                              bool check_input);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Return a list of string names for instructions in a circuit and their counts.
 *
 * @param circuit A pointer to the circuit to get the counts for.
 *
 * @return An ``OpCounts`` struct containing the circuit operation counts.
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(100, 0);
 *     uint32_t qubit[1] = {0};
 *     qk_circuit_gate(qc, QkGate_H, qubits, NULL);
 *     QkOpCounts counts = qk_circuit_count_ops(qc);
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit``.
 */
QkOpCounts qk_circuit_count_ops(const QkCircuit *circuit);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Return the total number of instructions in the circuit.
 *
 * @param circuit A pointer to the circuit to get the total number of instructions for.
 *
 * @return The total number of instructions in the circuit.
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(100, 0);
 *     uint32_t qubit[1] = {0};
 *     qk_circuit_gate(qc, QkGate_H, qubit, NULL);
 *     size_t num = qk_circuit_num_instructions(qc); // 1
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit``.
 */
uintptr_t qk_circuit_num_instructions(const QkCircuit *circuit);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Return the instruction details for an instruction in the circuit.
 *
 * This function is used to get the instruction details for a given instruction in
 * the circuit.
 *
 * @param circuit A pointer to the circuit to get the instruction details for.
 * @param index The instruction index to get the instruction details of.
 * @param instruction A pointer to where to write out the ``QkCircuitInstruction``
 *
 *
 * # Example
 *
 *     QkCircuitInstruction inst;
 *     QkCircuit *qc = qk_circuit_new(100);
 *     uint32_t qubit[1] = {0};
 *     qk_circuit_gate(qc, QkGate_H, qubit, NULL);
 *     qk_circuit_get_instruction(qc, 0, &inst);
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit``. The
 * value for ``index`` must be less than the value returned by ``qk_circuit_num_instructions``
 * otherwise this function will panic. Behavior is undefined if ``instruction`` is not a valid,
 * non-null pointer to a memory allocation with sufficient space for a ``QkCircuitInstruction``.
 */
void qk_circuit_get_instruction(const QkCircuit *circuit,
                                uintptr_t index,
                                QkCircuitInstruction *instruction);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Clear the data in circuit instruction object.
 *
 * This function doesn't free the allocation for the provided ``QkCircuitInstruction`` pointer, it
 * only frees the internal allocations for the data contained in the instruction. You are
 * responsible for allocating and freeing the actual allocation used to store a
 * ``QkCircuitInstruction``.
 *
 * @param inst A pointer to the instruction to free.
 *
 * # Example
 *
 *     QkCircuitInstruction *inst = malloc(sizeof(QkCircuitInstruction));
 *     QkCircuit *qc = qk_circuit_new(100);
 *     uint32_t q0 = {0};
 *     qk_circuit_gate(qc, QkGate_H, q0, NULL);
 *     qk_circuit_get_instruction(qc, 0, inst);
 *     qk_circuit_instruction_clear(inst); // free the data
 *     free(inst); // free the pointer
 *     qk_circuit_free(qc); // free the circuit
 *
 * # Safety
 *
 * Behavior is undefined if ``inst`` is not a valid, non-null pointer to a ``QkCircuitInstruction``.
 */
void qk_circuit_instruction_clear(const QkCircuitInstruction *inst);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Free a circuit op count list.
 *
 * @param op_counts The returned op count list from ``qk_circuit_count_ops``.
 *
 * # Safety
 *
 * Behavior is undefined if ``op_counts`` is not the object returned by ``qk_circuit_count_ops``.
 */
void qk_opcounts_free(QkOpCounts op_counts);
#endif

#if (defined(QISKIT_C_PYTHON_INTERFACE) && defined(QISKIT_WITH_CBINDINGS))
/**
 * @ingroup QkCircuit
 * Convert to a Python-space ``QuantumCircuit``.
 *
 * This function takes ownership of the pointer and gives it to Python. Using
 * the input ``circuit`` pointer after it's passed to this function is
 * undefined behavior. In particular, ``qk_circuit_free`` should not be called
 * on this pointer anymore.
 *
 * @param circuit The C-space ``QkCircuit`` pointer.
 *
 * @return A Python ``QuantumCircuit`` object.
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to
 * a ``QkCircuit``
 *
 * It is assumed that the thread currently executing this function holds the
 * Python GIL. This is required to create the Python object returned by this
 * function.
 */
PyObject *qk_circuit_to_python(QkCircuit *circuit);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkCircuit
 * Append a delay instruction to the circuit.
 *
 * @param circuit A pointer to the circuit to add the delay to.
 * @param qubit The ``uint32_t`` index of the qubit to apply the delay to.
 * @param duration The duration of the delay.
 * @param unit An enum representing the unit of the duration.
 *
 * @return An exit code.
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(1, 0);
 *     qk_circuit_delay(qc, 0, 100.0, QkDelayUnit_NS);
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` is not a valid, non-null pointer to a ``QkCircuit``.
 */
QkExitCode qk_circuit_delay(QkCircuit *circuit, uint32_t qubit, double duration, QkDelayUnit unit);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Construct the zero observable (without any terms).
 *
 * @param num_qubits The number of qubits the observable is defined on.
 *
 * @return A pointer to the created observable.
 *
 * # Example
 *
 *     QkObs *zero = qk_obs_zero(100);
 *
 */
QkObs *qk_obs_zero(uint32_t num_qubits);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Construct the identity observable.
 *
 * @param num_qubits The number of qubits the observable is defined on.
 *
 * @return A pointer to the created observable.
 *
 * # Example
 *
 *     QkObs *identity = qk_obs_identity(100);
 *
 */
QkObs *qk_obs_identity(uint32_t num_qubits);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Construct a new observable from raw data.
 *
 * @param num_qubits The number of qubits the observable is defined on.
 * @param num_terms The number of terms.
 * @param num_bits The total number of non-identity bit terms.
 * @param coeffs A pointer to the first element of the coefficients array, which has length
 *     ``num_terms``.
 * @param bit_terms A pointer to the first element of the bit terms array, which has length
 *     ``num_bits``.
 * @param indices A pointer to the first element of the indices array, which has length
 *     ``num_bits``. Note that, per term, these *must* be sorted incrementally.
 * @param boundaries A pointer to the first element of the boundaries array, which has length
 *     ``num_terms + 1``.
 *
 * @return If the input data was coherent and the construction successful, the result is a pointer
 *     to the observable. Otherwise a null pointer is returned.
 *
 * # Example
 *
 *     // define the raw data for the 100-qubit observable |01><01|_{0, 1} - |+-><+-|_{98, 99}
 *     uint32_t num_qubits = 100;
 *     uint64_t num_terms = 2;  // we have 2 terms: |01><01|, -1 * |+-><+-|
 *     uint64_t num_bits = 4; // we have 4 non-identity bits: 0, 1, +, -
 *
 *     complex double coeffs[2] = {1, -1};
 *     QkBitTerm bits[4] = {QkBitTerm_Zero, QkBitTerm_One, QkBitTerm_Plus, QkBitTerm_Minus};
 *     uint32_t indices[4] = {0, 1, 98, 99};  // <-- e.g. {1, 0, 99, 98} would be invalid
 *     size_t boundaries[3] = {0, 2, 4};
 *
 *     QkObs *obs = qk_obs_new(
 *         num_qubits, num_terms, num_bits, coeffs, bits, indices, boundaries
 *     );
 *
 * # Safety
 *
 * Behavior is undefined if any of the following conditions are violated:
 *
 *   * ``coeffs`` is a pointer to a ``complex double`` array of length ``num_terms``
 *   * ``bit_terms`` is a pointer to an array of valid ``QkBitTerm`` elements of length ``num_bits``
 *   * ``indices`` is a pointer to a ``uint32_t`` array of length ``num_bits``, which is
 *     term-wise sorted in strict ascending order, and every element is smaller than ``num_qubits``
 *   * ``boundaries`` is a pointer to a ``size_t`` array of length ``num_terms + 1``, which is
 *     sorted in ascending order, the first element is 0 and the last element is
 *     smaller than ``num_terms``
 */
QkObs *qk_obs_new(uint32_t num_qubits,
                  uint64_t num_terms,
                  uint64_t num_bits,
                  QkComplex64 *coeffs,
                  QkBitTerm *bit_terms,
                  uint32_t *indices,
                  uintptr_t *boundaries);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Free the observable.
 *
 * @param obs A pointer to the observable to free.
 *
 * # Example
 *
 *     QkObs *obs = qk_obs_zero(100);
 *     qk_obs_free(obs);
 *
 * # Safety
 *
 * Behavior is undefined if ``obs`` is not either null or a valid pointer to a ``QkObs``.
 */
void qk_obs_free(QkObs *obs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Add a term to the observable.
 *
 * @param obs A pointer to the observable.
 * @param cterm A pointer to the term to add.
 *
 * @return An exit code. This is ``>0`` if the term is incoherent or adding the term fails.
 *
 * # Example
 *
 *     uint32_t num_qubits = 100;
 *     QkObs *obs = qk_obs_zero(num_qubits);
 *
 *     complex double coeff = 1;
 *     QkBitTerm bit_terms[3] = {QkBitTerm_X, QkBitTerm_Y, QkBitTerm_Z};
 *     uint32_t indices[3] = {0, 1, 2};
 *     QkObsTerm term = {&coeff, 3, bit_terms, indices, num_qubits};
 *
 *     int exit_code = qk_obs_add_term(obs, &term);
 *
 * # Safety
 *
 * Behavior is undefined if any of the following is violated:
 *
 *   * ``obs`` is a valid, non-null pointer to a ``QkObs``
 *   * ``cterm`` is a valid, non-null pointer to a ``QkObsTerm``
 */
QkExitCode qk_obs_add_term(QkObs *obs, const QkObsTerm *cterm);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Get an observable term by reference.
 *
 * A ``QkObsTerm`` contains pointers to the indices and bit terms in the term, which
 * can be used to modify the internal data of the observable. This can leave the observable
 * in an incoherent state and should be avoided, unless great care is taken. It is generally
 * safer to construct a new observable instead of attempting in-place modifications.
 *
 * @param obs A pointer to the observable.
 * @param index The index of the term to get.
 * @param out A pointer to a ``QkObsTerm`` used to return the observable term.
 *
 * @return An exit code.
 *
 * # Example
 *
 *     QkObs *obs = qk_obs_identity(100);
 *     QkObsTerm term;
 *     int exit_code = qk_obs_term(obs, 0, &term);
 *     // out-of-bounds indices return an error code
 *     // int error = qk_obs_term(obs, 12, &term);
 *
 * # Safety
 *
 * Behavior is undefined if any of the following is violated
 * * ``obs`` is a valid, non-null pointer to a ``QkObs``
 * * ``out`` is a valid, non-null pointer to a ``QkObsTerm``
 */
QkExitCode qk_obs_term(QkObs *obs, uint64_t index, QkObsTerm *out);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Get the number of terms in the observable.
 *
 * @param obs A pointer to the observable.
 *
 * @return The number of terms in the observable.
 *
 * # Example
 *
 *     QkObs *obs = qk_obs_identity(100);
 *     size_t num_terms = qk_obs_num_terms(obs);  // num_terms==1
 *
 * # Safety
 *
 * Behavior is undefined ``obs`` is not a valid, non-null pointer to a ``QkObs``.
 */
uintptr_t qk_obs_num_terms(const QkObs *obs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Get the number of qubits the observable is defined on.
 *
 * @param obs A pointer to the observable.
 *
 * @return The number of qubits the observable is defined on.
 *
 * # Example
 *
 *     QkObs *obs = qk_obs_identity(100);
 *     uint32_t num_qubits = qk_obs_num_qubits(obs);  // num_qubits==100
 *
 * # Safety
 *
 * Behavior is undefined ``obs`` is not a valid, non-null pointer to a ``QkObs``.
 */
uint32_t qk_obs_num_qubits(const QkObs *obs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Get the number of bit terms/indices in the observable.
 *
 * @param obs A pointer to the observable.
 *
 * @return The number of terms in the observable.
 *
 * # Example
 *
 *     QkObs *obs = qk_obs_identity(100);
 *     size_t len = qk_obs_len(obs);  // len==0, as there are no non-trivial bit terms
 *
 * # Safety
 *
 * Behavior is undefined ``obs`` is not a valid, non-null pointer to a ``QkObs``.
 */
uintptr_t qk_obs_len(const QkObs *obs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Get a pointer to the coefficients.
 *
 * This can be used to read and modify the observable's coefficients. The resulting
 * pointer is valid to read for ``qk_obs_num_terms(obs)`` elements of ``complex double``.
 *
 * @param obs A pointer to the observable.
 *
 * @return A pointer to the coefficients.
 *
 * # Example
 *
 *     QkObs *obs = qk_obs_identity(100);
 *     size_t num_terms = qk_obs_num_terms(obs);
 *     complex double *coeffs = qk_obs_coeffs(obs);
 *
 *     for (size_t i = 0; i < num_terms; i++) {
 *         printf("%f + i%f\n", creal(coeffs[i]), cimag(coeffs[i]));
 *     }
 *
 * # Safety
 *
 * Behavior is undefined ``obs`` is not a valid, non-null pointer to a ``QkObs``.
 */
QkComplex64 *qk_obs_coeffs(QkObs *obs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Get a pointer to the indices.
 *
 * This can be used to read and modify the observable's indices. The resulting pointer is
 * valid to read for ``qk_obs_len(obs)`` elements of size ``uint32_t``.
 *
 * @param obs A pointer to the observable.
 *
 * @return A pointer to the indices.
 *
 * # Example
 *
 *     uint32_t num_qubits = 100;
 *     QkObs *obs = qk_obs_zero(num_qubits);
 *
 *     complex double coeff = 1;
 *     QkBitTerm bit_terms[3] = {QkBitTerm_X, QkBitTerm_Y, QkBitTerm_Z};
 *     uint32_t indices[3] = {0, 1, 2};
 *     QkObsTerm term = {&coeff, 3, bit_terms, indices, num_qubits};
 *     qk_obs_add_term(obs, &term);
 *
 *     size_t len = qk_obs_len(obs);
 *     uint32_t *indices = qk_obs_indices(obs);
 *
 *     for (size_t i = 0; i < len; i++) {
 *         printf("index %i: %i\n", i, indices[i]);
 *     }
 *
 *     qk_obs_free(obs);
 *
 * # Safety
 *
 * Behavior is undefined ``obs`` is not a valid, non-null pointer to a ``QkObs``.
 */
uint32_t *qk_obs_indices(QkObs *obs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Get a pointer to the term boundaries.
 *
 * This can be used to read and modify the observable's term boundaries. The resulting pointer is
 * valid to read for ``qk_obs_num_terms(obs) + 1`` elements of size ``size_t``.
 *
 * @param obs A pointer to the observable.
 *
 * @return A pointer to the boundaries.
 *
 * # Example
 *
 *     uint32_t num_qubits = 100;
 *     QkObs *obs = qk_obs_zero(num_qubits);
 *
 *     complex double coeff = 1;
 *     QkBitTerm bit_terms[3] = {QkBitTerm_X, QkBitTerm_Y, QkBitTerm_Z};
 *     uint32_t indices[3] = {0, 1, 2};
 *     QkObsTerm term = {&coeff, 3, bit_terms, indices, num_qubits};
 *     qk_obs_add_term(obs, &term);
 *
 *     size_t num_terms = qk_obs_num_terms(obs);
 *     uint32_t *boundaries = qk_obs_boundaries(obs);
 *
 *     for (size_t i = 0; i < num_terms + 1; i++) {
 *         printf("boundary %i: %i\n", i, boundaries[i]);
 *     }
 *
 * # Safety
 *
 * Behavior is undefined ``obs`` is not a valid, non-null pointer to a ``QkObs``.
 */
uintptr_t *qk_obs_boundaries(QkObs *obs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Get a pointer to the bit terms.
 *
 * This can be used to read and modify the observable's bit terms. The resulting pointer is
 * valid to read for ``qk_obs_len(obs)`` elements of size ``uint8_t``.
 *
 * @param obs A pointer to the observable.
 *
 * @return A pointer to the bit terms.
 *
 * # Example
 *
 *     uint32_t num_qubits = 100;
 *     QkObs *obs = qk_obs_zero(num_qubits);
 *
 *     complex double coeff = 1;
 *     QkBitTerm bit_terms[3] = {QkBitTerm_X, QkBitTerm_Y, QkBitTerm_Z};
 *     uint32_t indices[3] = {0, 1, 2};
 *     QkObsTerm term = {&coeff, 3, bit_terms, indices, num_qubits};
 *     qk_obs_add_term(obs, &term);
 *
 *     size_t len = qk_obs_len(obs);
 *     QkBitTerm *bits = qk_obs_bit_terms(obs);
 *
 *     for (size_t i = 0; i < len; i++) {
 *         printf("bit term %i: %i\n", i, bits[i]);
 *     }
 *
 *     qk_obs_free(obs);
 *
 * # Safety
 *
 * Behavior is undefined ``obs`` is not a valid, non-null pointer to a ``QkObs``,
 * or if invalid valus are written into the resulting ``QkBitTerm`` pointer.
 */
QkBitTerm *qk_obs_bit_terms(QkObs *obs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Multiply the observable by a complex coefficient.
 *
 * @param obs A pointer to the observable.
 * @param coeff The coefficient to multiply the observable with.
 *
 * # Example
 *
 *     QkObs *obs = qk_obs_identity(100);
 *     complex double coeff = 2;
 *     QkObs *result = qk_obs_multiply(obs, &coeff);
 *
 * # Safety
 *
 * Behavior is undefined if any of the following is violated
 * * ``obs`` is a valid, non-null pointer to a ``QkObs``
 * * ``coeff`` is a valid, non-null pointer to a ``complex double``
 */
QkObs *qk_obs_multiply(const QkObs *obs, const QkComplex64 *coeff);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Add two observables.
 *
 * @param left A pointer to the left observable.
 * @param right A pointer to the right observable.
 *
 * @return A pointer to the result ``left + right``.
 *
 * # Example
 *
 *     QkObs *left = qk_obs_identity(100);
 *     QkObs *right = qk_obs_zero(100);
 *     QkObs *result = qk_obs_add(left, right);
 *
 * # Safety
 *
 * Behavior is undefined if ``left`` or ``right`` are not valid, non-null pointers to
 * ``QkObs``\ s.
 */
QkObs *qk_obs_add(const QkObs *left, const QkObs *right);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Compose (multiply) two observables.
 *
 * @param first One observable.
 * @param second The other observable.
 *
 * @return ``first.compose(second)`` which equals the observable ``result = second @ first``,
 *     in terms of the matrix multiplication ``@``.
 *
 * # Example
 *
 *     QkObs *first = qk_obs_zero(100);
 *     QkObs *second = qk_obs_identity(100);
 *     QkObs *result = qk_obs_compose(first, second);
 *
 * # Safety
 *
 * Behavior is undefined if ``first`` or ``second`` are not valid, non-null pointers to
 * ``QkObs``\ s.
 */
QkObs *qk_obs_compose(const QkObs *first, const QkObs *second);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Compose (multiply) two observables according to a custom qubit order.
 *
 * Notably, this allows composing two observables of different size.
 *
 * @param first One observable.
 * @param second The other observable. The number of qubits must match the length of ``qargs``.
 * @param qargs The qubit arguments specified which indices in ``first`` to associate with
 *     the ones in ``second``.
 *
 * @return ``first.compose(second)`` which equals the observable ``result = second @ first``,
 *     in terms of the matrix multiplication ``@``.
 *
 * # Example
 *
 *     QkObs *first = qk_obs_zero(100);
 *     QkObs *second = qk_obs_identity(100);
 *     QkObs *result = qk_obs_compose(first, second);
 *
 * # Safety
 *
 * To call this function safely
 *
 *   * ``first`` and ``second`` must be valid, non-null pointers to ``QkObs``\ s
 *   * ``qargs`` must point to an array of ``uint32_t``, readable for ``qk_obs_num_qubits(second)``
 *     elements (meaning the number of qubits in ``second``)
 */
QkObs *qk_obs_compose_map(const QkObs *first, const QkObs *second, const uint32_t *qargs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Calculate the canonical representation of the observable.
 *
 * @param obs A pointer to the observable.
 * @param tol The tolerance below which coefficients are considered to be zero.
 *
 * @return The canonical representation of the observable.
 *
 * # Example
 *
 *     QkObs *iden = qk_obs_identity(100);
 *     QkObs *two = qk_obs_add(iden, iden);
 *
 *     double tol = 1e-6;
 *     QkObs *canonical = qk_obs_canonicalize(two);
 *
 * # Safety
 *
 * Behavior is undefined ``obs`` is not a valid, non-null pointer to a ``QkObs``.
 */
QkObs *qk_obs_canonicalize(const QkObs *obs, double tol);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Copy the observable.
 *
 * @param obs A pointer to the observable.
 *
 * @return A pointer to a copy of the observable.
 *
 * # Example
 *
 *     QkObs *original = qk_obs_identity(100);
 *     QkObs *copied = qk_obs_copy(original);
 *
 * # Safety
 *
 * Behavior is undefined ``obs`` is not a valid, non-null pointer to a ``QkObs``.
 */
QkObs *qk_obs_copy(const QkObs *obs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Compare two observables for equality.
 *
 * Note that this does not compare mathematical equality, but data equality. This means
 * that two observables might represent the same observable but not compare as equal.
 *
 * @param obs A pointer to one observable.
 * @param other A pointer to another observable.
 *
 * @return ``true`` if the observables are equal, ``false`` otherwise.
 *
 * # Example
 *
 *     QkObs *observable = qk_obs_identity(100);
 *     QkObs *other = qk_obs_identity(100);
 *     bool are_equal = qk_obs_equal(observable, other);
 *
 * # Safety
 *
 * Behavior is undefined if ``obs`` or ``other`` are not valid, non-null pointers to
 * ``QkObs``\ s.
 */
bool qk_obs_equal(const QkObs *obs, const QkObs *other);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Return a string representation of a ``QkObs``.
 *
 * @param obs A pointer to the ``QkObs`` to get the string for.
 *
 * @return A pointer to a nul-terminated char array of the string representation for ``obs``
 *
 * # Example
 *
 *     QkObs *obs = qk_obs_identity(100);
 *     char *string = qk_obs_str(obs);
 *     qk_str_free(string);
 *
 * # Safety
 *
 * Behavior is undefined ``obs`` is not a valid, non-null pointer to a ``QkObs``.
 *
 * The string must not be freed with the normal C free, you must use ``qk_str_free`` to
 * free the memory consumed by the String. Not calling ``qk_str_free`` will lead to a
 * memory leak.
 *
 * Do not change the length of the string after it's returned (by writing a nul byte somewhere
 * inside the string or removing the final one), although values can be mutated.
 */
char *qk_obs_str(const QkObs *obs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObs
 * Free a string representation.
 *
 * @param string A pointer to the returned string representation from ``qk_obs_str`` or
 *     ``qk_obsterm_str``.
 *
 * # Safety
 *
 * Behavior is undefined if ``str`` is not a pointer returned by ``qk_obs_str`` or
 * ``qk_obsterm_str``.
 */
void qk_str_free(char *string);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkObsTerm
 * Return a string representation of the sparse term.
 *
 * @param term A pointer to the term.
 *
 * @return The function exit code. This is ``>0`` if reading the term failed.
 *
 * # Example
 *
 *     QkObs *obs = qk_obs_identity(100);
 *     QkObsTerm term;
 *     qk_obs_term(obs, 0, &term);
 *     char *string = qk_obsterm_str(&term);
 *     qk_str_free(string);
 *
 * # Safety
 *
 * Behavior is undefined ``term`` is not a valid, non-null pointer to a ``QkObsTerm``.
 *
 * The string must not be freed with the normal C free, you must use ``qk_str_free`` to
 * free the memory consumed by the String. Not calling ``qk_str_free`` will lead to a
 * memory leak.
 *
 * Do not change the length of the string after it's returned, although values can be mutated.
 */
char *qk_obsterm_str(const QkObsTerm *term);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkBitTerm
 * Get the label for a bit term.
 *
 * @param bit_term The bit term.
 *
 * @return The label as ``uint8_t``, which can be cast to ``char`` to obtain the character.
 *
 * # Example
 *
 *     QkBitTerm bit_term = QkBitTerm_Y;
 *     // cast the uint8_t to char
 *     char label = qk_bitterm_label(bit_term);
 *
 * # Safety
 *
 * The behavior is undefined if ``bit_term`` is not a valid ``uint8_t`` value of a ``QkBitTerm``.
 */
uint8_t qk_bitterm_label(QkBitTerm bit_term);
#endif

#if (defined(QISKIT_C_PYTHON_INTERFACE) && defined(QISKIT_WITH_CBINDINGS))
/**
 * @ingroup QkObs
 * Convert to a Python-space ``SparseObservable``.
 *
 * @param obs The C-space ``QkObs`` pointer.
 *
 * @return A Python object representing the ``SparseObservable``.
 *
 * # Safety
 *
 * Behavior is undefined if ``obs`` is not a valid, non-null pointer to a ``QkObs``.
 *
 * It is assumed that the thread currently executing this function holds the
 * Python GIL this is required to create the Python object returned by this
 * function.
 */
PyObject *qk_obs_to_python(const QkObs *obs);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkVF2LayoutResult
 * Check whether a result was found.
 *
 * @param layout a pointer to the layout
 *
 * @returns ``true`` if the ``qk_transpiler_pass_standalone_vf2_layout()`` run found a layout
 *
 * # Safety
 *
 * Behavior is undefined if ``layout`` is not a valid, non-null pointer to a
 * ``QkVF2LayoutResult``.
 */
bool qk_vf2_layout_result_has_match(const QkVF2LayoutResult *layout);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkVF2LayoutResult
 * Get the number of virtual qubits in the layout.
 *
 * @param layout a pointer to the layout
 *
 * @returns The number of virtual qubits in the layout
 *
 * # Safety
 *
 * Behavior is undefined if ``layout`` is not a valid, non-null pointer to a
 * ``QkVF2LayoutResult``. The result must have a layout found.
 */
uint32_t qk_vf2_layout_result_num_qubits(const QkVF2LayoutResult *layout);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkVF2LayoutResult
 * Get the physical qubit for a given virtual qubit
 *
 * @param layout a pointer to the layout
 * @param qubit the virtual qubit to get the physical qubit of
 *
 * @returns The physical qubit mapped to by the specified virtual qubit
 *
 * # Safety
 *
 * Behavior is undefined if ``layout`` is not a valid, non-null pointer to a
 * ``QkVF2LayoutResult``. Also qubit must be a valid qubit for the circuit and
 * there must be a result found.
 */
uint32_t qk_vf2_layout_result_map_virtual_qubit(const QkVF2LayoutResult *layout, uint32_t qubit);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkVF2LayoutResult
 * Free a ``QkVF2LayoutResult`` object
 *
 * @param layout a pointer to the layout to free
 *
 * # Example
 *
 *     QkCircuit *qc = qk_circuit_new(1, 0);
 *
 * # Safety
 *
 * Behavior is undefined if ``layout`` is not a valid, non-null pointer to a ``QkVF2Layout``.
 */
void qk_vf2_layout_result_free(QkVF2LayoutResult *layout);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTranspilerPasses
 * Run the VF2Layout pass on a circuit.
 *
 * VF2Layout is a pass for choosing a layout of a circuit onto a connectivity graph as
 * a subgraph isomorphism problem solved by VF2.
 *
 * If this pass finds a solution that means there is a "perfect layout" and that no
 * further swap mapping or routing is needed. However, there is not always a possible
 * solution, or a solution might exist but it is not found within the limits specified
 * when the pass is called.
 *
 * By default, this pass will construct a heuristic scoring map based on the error rates
 * in the provided ``target`` argument. The function will continue searching for layouts
 * and use the heuristic scoring to return the layout which will run with the best estimated
 * fidelity.
 *
 * @param circuit A pointer to the circuit to run VF2Layout on
 * @param target A pointer to the target to run the VF2Layout pass on
 * @param strict_direction If true the pass will consider the edge direction in the
 *     connectivity described in the ``target``. Typically setting this to ``false``
 *     is desireable as an undirected search has more degrees of freedom and is more likely
 *     to find a layout (or a better layout if there are multiple choices) and correcting
 *     directionality is a simple operation for later transpilation stages.
 * @param call_limit The number of state visits to attempt in each execution of the VF2 algorithm.
 *     If the value is set to a negative value the VF2 algorithm will run without any limit.
 * @param time_limit The total time in seconds to run for ``VF2Layout``. This is checked after
 *     each layout search so it is not a hard time limit, but a soft limit that when checked
 *     if the set time has elapsed the function will return the best layout it has found so
 *     far. Set this to a value less than or equal to 0.0 to run without any time limit.
 * @param max_trials The maximum number of trials to run the VF2 algorithm to try and find
 *     layouts. If the value is negative this will be treated as unbounded which means the
 *     algorithm will run until all possible layouts are scored. If the value is 0 the number
 *     of trials will be limited based on the number of edges in the interaction or the coupling
 *     graph (whichever is larger).
 *
 * @return QkVF2LayoutResult A pointer to a result object that contains the
 * results of the pass. This object is heap allocated and will need to be freed with the
 * ``qk_vf2_layout_result_free()`` function.
 *
 * # Example
 *
 * ```c
 *     QkTarget *target = qk_target_new(5)
 *     QkTargetEntry *cx_entry = qk_target_entry_new(QkGate_CX);
 *     for (uint32_t i = 0; i < current_num_qubits - 1; i++) {
 *         uint32_t qargs[2] = {i, i + 1};
 *         double inst_error = 0.0090393 * (current_num_qubits - i);
 *         double inst_duration = 0.020039;
 *         qk_target_entry_add_property(cx_entry, qargs, 2, inst_duration, inst_error);
 *     }
 *     QkExitCode result_cx = qk_target_add_instruction(target, cx_entry);
 *     QkCircuit *qc = qk_circuit_new(4, 0);
 *     for (uint32_t i = 0; i < qk_circuit_num_qubits(qc) - 1; i++) {
 *         uint32_t qargs[2] = {i, i + 1};
 *         for (uint32_t j = 0; j<i+1; j++) {
 *             qk_circuit_gate(qc, QkGate_CX, qargs, NULL);
 *         }
 *     }
 *     QkVF2LayoutResult *layout_result = qk_transpiler_pass_standalone_vf2_layout(qc, target, false, -1, NAN, -1);
 *     qk_vf2_layout_result_free(layout_result);
 * ```
 *
 * # Safety
 *
 * Behavior is undefined if ``circuit`` or ``target`` is not a valid, non-null pointer to a ``QkCircuit`` and ``QkTarget``.
 */
QkVF2LayoutResult *qk_transpiler_pass_standalone_vf2_layout(const QkCircuit *circuit,
                                                            const QkTarget *target,
                                                            bool strict_direction,
                                                            int64_t call_limit,
                                                            double time_limit,
                                                            intptr_t max_trials);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Construct a new ``QkTarget`` with the given number of qubits.
 * The number of qubits is bound to change if an instruction is added with properties
 * that apply to a collection of qargs in which any index is higher than the specified
 * number of qubits
 *
 * @param num_qubits The number of qubits the ``QkTarget`` will explicitly support.
 *
 * @return A pointer to the new ``QkTarget``
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *
 */
QkTarget *qk_target_new(uint32_t num_qubits);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Returns the number of qubits of this ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 *
 * @return The number of qubits this target can use.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     uint32_t num_qubits = qk_target_num_qubits(target);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
uint32_t qk_target_num_qubits(const QkTarget *target);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Returns the dt value of this ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 *
 * @return The dt value of this ``QkTarget`` or ``NaN`` if not assigned.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     qk_target_set_dt(target, 10e-9);
 *     double dt = qk_target_dt(target);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
double qk_target_dt(const QkTarget *target);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Returns the granularity value of this ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 *
 * @return The ``granularity`` value of this ``QkTarget``.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     // The value defaults to 1
 *     uint32_t granularity = qk_target_granularity(target);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
uint32_t qk_target_granularity(const QkTarget *target);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Returns the ``min_length`` value of this ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 *
 * @return The ``min_length`` value of this ``QkTarget``.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     // The value defaults to 1
 *     size_t min_length = qk_target_min_length(target);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
uint32_t qk_target_min_length(const QkTarget *target);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Returns the ``pulse_alignment`` value of this ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 *
 * @return The ``pulse_alignment`` value of this ``QkTarget``.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     // The value defaults to 1
 *     uint32_t pulse_alignment = qk_target_pulse_alignment(target);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
uint32_t qk_target_pulse_alignment(const QkTarget *target);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Returns the ``acquire_alignment`` value of this ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 *
 * @return The ``acquire_alignment`` value of this ``QkTarget``.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     // The value defaults to 0
 *     uint32_t acquire_alignment = qk_target_pulse_alignment(target);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
uint32_t qk_target_acquire_alignment(const QkTarget *target);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Sets the dt value of this ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 * @param dt The ``dt`` value for the system time resolution of input.
 *
 * @return ``QkExitCode`` specifying if the operation was successful.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     double dt = qk_target_set_dt(target, 10e-9);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
QkExitCode qk_target_set_dt(QkTarget *target, double dt);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Sets the ``granularity`` value of this ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 * @param granularity The value for the minimum pulse gate resolution in
 *     units of ``dt``.
 *
 * @return ``QkExitCode`` specifying if the operation was successful.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     // The value defaults to 1
 *     qk_target_set_granularity(target, 2);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
QkExitCode qk_target_set_granularity(QkTarget *target, uint32_t granularity);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Sets the ``min_length`` value of this ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 * @param min_length The minimum pulse gate length value in units of ``dt``.
 *
 * @return ``QkExitCode`` specifying if the operation was successful.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     // The value defaults to 1
 *     qk_target_set_min_length(target, 3);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
QkExitCode qk_target_set_min_length(QkTarget *target, uint32_t min_length);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Returns the ``pulse_alignment`` value of this ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 * @param pulse_alignment value representing a time resolution of gate.
 *
 * @return ``QkExitCode`` specifying if the operation was successful.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     // The value defaults to 1
 *     qk_target_set_pulse_alignment(target, 4);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
QkExitCode qk_target_set_pulse_alignment(QkTarget *target, uint32_t pulse_alignment);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Sets the ``acquire_alignment`` value of this ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 * @param acquire_alignment value representing a time resolution of measure instruction
 *     starting time.
 *
 * @return ``QkExitCode`` specifying if the operation was successful.
 *
 * # Example
 *     QkTarget *target = qk_target_new(5);
 *     // The value defaults to 0
 *     qk_target_set_acquire_alignment(target, 5);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
QkExitCode qk_target_set_acquire_alignment(QkTarget *target, uint32_t acquire_alignment);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Creates a copy of the ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget`` to copy.
 *
 * @return A pointer to the new copy of the ``QkTarget``.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     QkTargetEntry *entry = qk_target_entry_new(QkGate_CX);
 *     uint32_t qargs[2] = {0, 1};
 *     qk_target_entry_add_property(entry, qargs, 2, 0.0, 0.1);
 *     QkExitCode result = qk_target_add_instruction(target, entry);
 *
 *     QkTarget *copied = qk_target_copy(target);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
QkTarget *qk_target_copy(QkTarget *target);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Free the ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget`` to free.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     qk_target_free(target);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
void qk_target_free(QkTarget *target);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTargetEntry
 * Creates an entry to the ``QkTarget`` based on a ``QkGate`` instance with
 * no parameters.
 *
 * @note If the instance of ``QkGate`` uses fixed parameters, use ``qk_target_entry_new_fixed``.
 * Regular parameters are not currently supported.
 *
 * @param operation The ``QkGate`` whose properties this target entry defines.
 *
 * @return A pointer to the new ``QkTargetEntry``.
 *
 * # Example
 *
 *     QkTargetEntry *entry = qk_target_entry_new(QkGate_H);
 */
QkTargetEntry *qk_target_entry_new(QkGate operation);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTargetEntry
 * Creates a new entry for adding a measurement instruction to a ``QkTarget``.
 *
 * @return A pointer to the new ``QkTargetEntry`` for a measurement instruction.
 *
 * # Example
 *
 *     QkTargetEntry *entry = qk_target_entry_new_measure();
 *     // Add fixed duration and error rates from qubits at index 0 to 4.
 *     for (uint32_t i = 0; i < 5; i++) {
 *         // Measure is a single qubit instruction
 *         uint32_t qargs[1] = {i};
 *         qk_target_entry_add_property(entry, qargs, 1, 1.928e-10, 7.9829e-11);
 *     }
 *
 *     // Add the entry to a target with 5 qubits
 *     QkTarget *measure_target = qk_target_new(5);
 *     qk_target_add_instruction(measure_target, entry);
 */
QkTargetEntry *qk_target_entry_new_measure(void);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTargetEntry
 * Creates a new entry for adding a reset instruction to a ``QkTarget``.
 *
 * @return A pointer to the new ``QkTargetEntry`` for a reset instruction.
 *
 * # Example
 *
 *     QkTargetEntry *entry = qk_target_entry_new_reset();
 *     // Add fixed duration and error rates from qubits at index 0 to 2.
 *     for (uint32_t i = 0; i < 3; i++) {
 *         // Reset is a single qubit instruction
 *         uint32_t qargs[1] = {i};
 *         qk_target_entry_add_property(entry, qargs, 1, 1.2e-11, 5.9e-13);
 *     }
 *
 *     // Add the entry to a target with 3 qubits
 *     QkTarget *reset_target = qk_target_new(3);
 *     qk_target_add_instruction(reset_target, entry);
 */
QkTargetEntry *qk_target_entry_new_reset(void);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTargetEntry
 * Creates an entry to the ``QkTarget`` based on a ``QkGate`` instance with
 * no parameters.
 *
 * @note Adding a ``QkGate`` with regular parameters is not currently supported.
 *
 * @param operation The ``QkGate`` whose properties this target entry defines.
 * @param params A pointer to the parameters that the instruction is calibrated for.
 *
 * @return A pointer to the new ``QkTargetEntry``.
 *
 * # Example
 *
 *     double crx_params[1] = {3.14};
 *     QkTargetEntry *entry = qk_target_entry_new(QkGate_CRX, crx_params);
 *
 * # Safety
 *
 * The ``params`` type is expected to be a pointer to an array of ``double`` where the length
 * matches the the expectations of the ``QkGate``. If the array is insufficently long the
 * behavior of this function is undefined as this will read outside the bounds of the array.
 * It can be a null pointer if there are no params for a given gate. You can check
 * ``qk_gate_num_params`` to determine how many qubits are required for a given gate.
 */
QkTargetEntry *qk_target_entry_new_fixed(QkGate operation, double *params);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTargetEntry
 * Retrieves the number of properties stored in the target entry.
 *
 * @param entry The pointer to the mapping object.
 *
 * @return The number of properties in the ``QkTargetEntry``.
 *
 * # Example
 *
 *     // Create an entry for an H gate
 *     QkTargetEntry *entry = qk_target_entry_new(QkGate_H);
 *     size_t props_size = qk_target_entry_num_properties(entry);
 *
 * # Safety
 *
 * The behavior is undefined if ``entry`` is not a valid,
 * non-null pointer to a ``QkTargetEntry`` object.
 */
uintptr_t qk_target_entry_num_properties(const QkTargetEntry *entry);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTargetEntry
 * Frees the entry.
 *
 * @note An entry pointer will be freed when added to a ``QkTarget`` via
 * ``qk_target_add_instruction``, this function is only meant to be used
 * alternatively if an entry is never added to a ``QkTarget`` instance.
 *
 * @param entry The pointer to the mapping object to be freed.
 *
 * # Example
 *
 *     QkTargetEntry *entry = qk_target_entry_new(QkGate_H);
 *     qk_target_entry_free(entry);
 *
 * # Safety
 *
 * The behavior is undefined if ``entry`` is not a valid,
 * non-null pointer to a ``QkTargetEntry`` object.
 */
void qk_target_entry_free(QkTargetEntry *entry);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTargetEntry
 * Adds an instruction property instance based on its assigned qargs.
 *
 * @param entry The pointer to the entry object.
 * @param qargs A pointer to the array of ``uint32_t`` qubit indices to add the
 *     gate on, can be a null pointer to check for global properties.
 * @param num_qubits The length of the qargs array.
 * @param duration The instruction's duration in seconds on the specific set of
 *     qubits.
 * @param error The instruction's average error rate on the specific set of qubits.
 *
 * # Example
 *
 *     QkTargetEntry *entry = qk_target_entry_new(QkGate_CX);
 *     uint32_t qargs[2] = {0, 1};
 *     qk_target_entry_add_property(entry, qargs, 2, 0.0, 0.1);
 *
 * # Safety
 *
 * The behavior is undefined if ``entry`` is not a valid, non-null pointer
 * to a ``QkTargetEntry`` object.
 */
QkExitCode qk_target_entry_add_property(QkTargetEntry *entry,
                                        uint32_t *qargs,
                                        uint32_t num_qubits,
                                        double duration,
                                        double error);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Adds a gate to the ``QkTarget`` through a ``QkTargetEntry``.
 *
 * @param target A pointer to the ``QkTarget``.
 * @param target_entry A pointer to the ``QkTargetEntry``. The pointer
 * gets freed when added to the ``QkTarget``.
 *
 * @return ``QkExitCode`` specifying if the operation was successful.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     QkTargetEntry *entry = qk_target_entry_new(QkGate_CX);
 *     uint32_t qargs[2] = {0, 1};
 *     qk_target_entry_add_property(entry, qargs, 2, 0.0, 0.1);
 *     QkExitCode result = qk_target_add_instruction(target, entry);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 *
 * Behavior is undefined if ``entry`` is not a valid, non-null pointer to a ``QkTargetEntry``.
 */
QkExitCode qk_target_add_instruction(QkTarget *target, QkTargetEntry *target_entry);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Modifies the properties of a gate in the ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 * @param instruction The instruction to modify.
 * @param qargs The pointer to the array of ``uint32_t`` values to use as
 * qargs. Can be ``NULL`` if global.
 * @param num_qubits The number of qubits of the instruction..
 * @param duration The instruction's duration in seconds on the specific set of
 *     qubits.
 * @param error The instruction's average error rate on the specific set of qubits.
 *
 * @return ``QkExitCode`` specifying if the operation was successful.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     double params[1] = {3.1415};
 *     QkTargetEntry *entry = qk_target_entry_new_fixed(QkGate_CRX, params);
 *     uint32_t qargs[2] = {0, 1};
 *     qk_target_entry_add_property(entry, qargs, 2, 0.0, 0.1);
 *     qk_target_add_instruction(target, entry);
 *
 *     qk_target_update_property(target, QkGate_CRX, qargs, 2, 0.0012, 1.1)
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 *
 * The ``qargs`` type is expected to be a pointer to an array of ``uint32_t`` where the length
 * matches is specified by ``num_qubits`` and has to match the expectation of the gate. If the
 * array is insufficently long the behavior of this function is undefined as this will read
 * outside the bounds of the array. It can be a null pointer if there are no qubits for
 * a given gate. You can check ``qk_gate_num_qubits`` to determine how many qubits are required
 * for a given gate.
 */
QkExitCode qk_target_update_property(QkTarget *target,
                                     QkGate instruction,
                                     uint32_t *qargs,
                                     uint32_t num_qubits,
                                     double duration,
                                     double error);
#endif

#if defined(QISKIT_WITH_CBINDINGS)
/**
 * @ingroup QkTarget
 * Returns the number of instructions tracked by a ``QkTarget``.
 *
 * @param target A pointer to the ``QkTarget``.
 *
 * @return The length of the target.
 *
 * # Example
 *
 *     QkTarget *target = qk_target_new(5);
 *     QkTargetEntry *target_enty = qk_target_entry_new(QkGate_H);
 *     qk_target_add_instruction(target, target_entry);
 *
 *     size_t num_instructions = qk_target_num_instructions(target);
 *
 * # Safety
 *
 * Behavior is undefined if ``QkTarget`` is not a valid, non-null pointer to a ``QkTarget``.
 */
uintptr_t qk_target_num_instructions(const QkTarget *target);
#endif

#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

#endif  /* QISKIT_H */
