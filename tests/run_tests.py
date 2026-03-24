#!/usr/bin/env python3
"""
SocialStoryScript — Test Runner
Runs the exact 8 final tests one by one with timeout.
Performs exact output comparison (no substring matching).
"""

import json
import subprocess
import sys
import os
from pathlib import Path

TIMEOUT_SECONDS = 15


def normalize(s: str) -> str:
    return s.replace("\r\n", "\n").replace("\r", "\n")


def run_single_test(compiler: Path, spec: dict) -> tuple[bool, str]:
    name        = spec["name"]
    input_path  = Path(spec["input"])
    expect_path = Path(spec["expected"])
    expect_exit = int(spec.get("expectedExit", 0))
    stdin_path  = Path(spec["stdin"]) if "stdin" in spec else None

    # --- pre-flight checks ---
    if not input_path.exists():
        return False, f"missing input file: {input_path}"
    if not expect_path.exists():
        return False, f"missing expected file: {expect_path}"
    if stdin_path and not stdin_path.exists():
        return False, f"missing stdin file: {stdin_path}"

    stdin_text = stdin_path.read_text(encoding="utf-8") if stdin_path else None

    # --- run compiler ---
    try:
        result = subprocess.run(
            [str(compiler), input_path.as_posix()],
            input=stdin_text,
            capture_output=True,
            text=True,
            encoding="utf-8",
            timeout=TIMEOUT_SECONDS,
        )
    except subprocess.TimeoutExpired:
        return False, f"TIMEOUT after {TIMEOUT_SECONDS}s — check for infinite loop in {name}"

    # --- locate output file (compiler writes output_<basename>.txt) ---
    output_file = Path(f"output_{input_path.name}")

    if result.returncode != expect_exit:
        return False, (
            f"exit code mismatch — expected {expect_exit}, got {result.returncode}\n"
            f"  stderr: {result.stderr[:300]}"
        )

    if not output_file.exists():
        return False, f"output file not created: {output_file}"

    actual   = normalize(output_file.read_text(encoding="utf-8"))
    expected = normalize(expect_path.read_text(encoding="utf-8"))

    if actual != expected:
        # find first differing line for a useful error message
        a_lines = actual.splitlines()
        e_lines = expected.splitlines()
        for i, (a, e) in enumerate(zip(a_lines, e_lines), 1):
            if a != e:
                return False, (
                    f"exact output mismatch at line {i}\n"
                    f"  GOT: {repr(a)}\n"
                    f"  EXP: {repr(e)}"
                )
        length_msg = (
            f"output too {'long' if len(a_lines) > len(e_lines) else 'short'} — "
            f"got {len(a_lines)} lines, expected {len(e_lines)} lines"
        )
        return False, length_msg

    return True, "PASS"


def main() -> int:
    if len(sys.argv) != 2:
        print("Usage: python tests/run_tests.py <compiler-binary>")
        print("Example: python tests/run_tests.py ./socialstory")
        return 2

    compiler = Path(sys.argv[1]).resolve()
    if not compiler.exists() and compiler.suffix == "":
        compiler_exe = compiler.with_suffix(".exe")
        if compiler_exe.exists():
            compiler = compiler_exe

    if not compiler.exists():
        print(f"ERROR: compiler binary not found: {compiler}")
        print("Build first with: make")
        return 2

    manifest = Path("tests/manifest.json")
    if not manifest.exists():
        print(f"ERROR: manifest not found: {manifest}")
        return 2

    tests = json.loads(manifest.read_text(encoding="utf-8"))

    print("=" * 60)
    print(f"  SocialStoryScript Test Runner — {len(tests)} tests")
    print("=" * 60)

    passed = 0
    failed = 0
    failed_names = []

    for spec in tests:
        name = spec["name"]
        print(f"\n[TEST] {name}")
        if "description" in spec:
            print(f"       {spec['description'][:72]}")

        ok, msg = run_single_test(compiler, spec)

        if ok:
            print(f"  ✅  PASS")
            passed += 1
        else:
            print(f"  ❌  FAIL — {msg}")
            failed += 1
            failed_names.append(name)

    print("\n" + "=" * 60)
    print(f"  RESULTS: {passed}/{passed+failed} passed")
    if failed_names:
        print(f"  FAILED:  {', '.join(failed_names)}")
    print("=" * 60)

    return 0 if failed == 0 else 1


if __name__ == "__main__":
    raise SystemExit(main())
