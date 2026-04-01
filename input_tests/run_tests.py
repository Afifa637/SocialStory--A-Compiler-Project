#!/usr/bin/env python3
"""
SocialStoryScript — Test Runner
Runs the exact 8 final tests one by one with timeout.
Performs exact output comparison (no substring matching).
"""

import json
import re
import subprocess
import sys
import os
from pathlib import Path

TIMEOUT_SECONDS = 15


def normalize(s: str) -> str:
    return s.replace("\r\n", "\n").replace("\r", "\n")


def normalize_input_file_line(s: str) -> str:
    return re.sub(
        r"Input file\s*:\s*.*(?:input_tests|tests)[/\\]([^/\\\n]+)",
        r"Input file : tests/\1",
        s,
    )


def run_single_test(compiler: Path, spec: dict, manifest_dir: Path) -> tuple[bool, str]:
    name        = spec["name"]
    input_path  = (manifest_dir / spec["input"]).resolve() if not Path(spec["input"]).is_absolute() else Path(spec["input"])
    expect_path = (manifest_dir / spec["expected"]).resolve() if not Path(spec["expected"]).is_absolute() else Path(spec["expected"])
    expect_exit = int(spec.get("expectedExit", 0))
    stdin_path  = ((manifest_dir / spec["stdin"]).resolve() if not Path(spec["stdin"]).is_absolute() else Path(spec["stdin"])) if "stdin" in spec else None

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

    actual = normalize(output_file.read_text(encoding="utf-8"))
    expected = normalize(expect_path.read_text(encoding="utf-8"))

    actual = normalize_input_file_line(actual)
    expected = normalize_input_file_line(expected)

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
        print("Usage: python input_tests/run_tests.py <compiler-binary>")
        print("Example: python input_tests/run_tests.py ./socialstory")
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

    script_dir = Path(__file__).resolve().parent
    manifest_candidates = [
        script_dir / "manifest.json",
        Path("input_tests/manifest.json"),
        Path("tests/manifest.json"),
    ]

    manifest = next((m for m in manifest_candidates if m.exists()), None)
    if manifest is None:
        print("ERROR: manifest not found in input_tests/ or tests/")
        return 2

    tests = json.loads(manifest.read_text(encoding="utf-8"))
    manifest_dir = manifest.parent.resolve()

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

        ok, msg = run_single_test(compiler, spec, manifest_dir)

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
