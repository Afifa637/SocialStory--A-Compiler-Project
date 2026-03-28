# SocialStoryScript — Test Suite

**8 deterministic, exact-output tests.** No substring matching.
Each test is designed to prove both compiler correctness and practical social-media analytics usefulness.

## Run

```bash
# From project root (after `make`):
make test
# or directly:
python3 tests/run_tests.py ./socialstory
```

## Tests

| Test | Exit | What it proves |
|---|---|---|
| `lexical_identifiers_test` | 1 | Lexical reliability for real analyst scripts (identifier policy, literals, comments, invalid token handling) |
| `syntax_error_recovery_test` | 1 | Parser recovery quality for malformed strategy scripts |
| `semantic_runtime_safety_test` | 1 | Safety guardrails: undeclared use, type coercion, divide/modulo-by-zero, feed index type+bounds, arity mismatch |
| `execution_accounts_metrics_test` | 0 | Practical account analytics lifecycle and reporting |
| `controlflow_loops_test` | 0 | Growth simulation and policy decisions with all loop/control-flow forms |
| `functions_builtins_test` | 0 | Reusable analytics workflows (user functions + built-in analytics suite), clean-arity success path |
| `input_io_test` | 0 | Input-driven planning and decision logic from live campaign data |
| `arrays_optimizer_integration_test` | 0 | Weekly feed/post analytics plus optimizer impact on realistic workload, including strength reduction, DCE, and measurable TAC reduction |

## Policy notes for evaluators

- Identifier policy is intentional: names may start with digits only if letters/underscore also appear (e.g., `124bro`), while symbol-prefixed forms like `@name` are invalid.
- `semantic_runtime_safety_test` intentionally surfaces both semantic and runtime safeguards in one deterministic report, including divide/modulo-by-zero, feed index type/bounds checks, and function arity diagnostics.

## Four flagship tests (recommended first)

- `lexical_identifiers_test` — unusual identifier policy + numeric literal coverage + invalid-token handling
- `semantic_runtime_safety_test` — concentrated guardrail proof (semantic + runtime)
- `input_io_test` — practical stdin-driven decision workflow with variable-to-metric flow
- `arrays_optimizer_integration_test` — feed analytics plus visible TAC optimizer impact (including strength reduction)

## How it works

`run_tests.py` reads `manifest.json`, runs the compiler on each input file,
feeds `*.stdin.txt` to stdin where specified, then compares the compiler's
`output_<name>.txt` against the matching `.expected.txt` byte-for-byte
(after CRLF normalisation). Any mismatch or wrong exit code is a failure.
