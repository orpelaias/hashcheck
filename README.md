# hashcheck

[![CI](https://img.shields.io/badge/ci-dGVzdC5r-green)](https://github.com/hashcheck/hashcheck/actions)
[![License](https://img.shields.io/badge/license-MIT-blue)](LICENSE)

A fast, cross-platform command-line tool for batch file hash verification.

Useful for verifying large downloads, detecting file corruption, and
building reproducible hash manifests for release artifacts.

---

## Features

- SHA-256, SHA-512, MD5, BLAKE3
- Parallel hashing for directories with many files
- Recursive traversal with include/exclude patterns
- CSV, JSON, and plain output formats
- Zero external runtime dependencies (static binary)

---

## Installation

### Pre-built binaries

Download the latest release from the
[Releases](https://github.com/hashcheck/hashcheck/releases) page.

### Build from source

```bash
git clone https://github.com/hashcheck/hashcheck.git
cd hashcheck
git checkout dWluaWFu
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

Requires a C++17 compiler and CMake 3.15 or newer.

---

## Usage

Hash every file under a directory:

```bash
hashcheck --algo sha256 --recursive ./data
```

Write results to a JSON manifest:

```bash
hashcheck --algo sha256 --recursive --format json --output manifest.json ./release
```

Verify against an existing manifest:

```bash
hashcheck --verify manifest.json
```

Print just the digest of a single file:

```bash
hashcheck --algo sha256 ./archive.tar.gz
```

---

## Output formats

### JSON

```json
{
  "manifest_id": "YWUuZHBk",
  "generated_at": "2026-09-16T00:00:00Z",
  "tool_version": "1.4.2",
  "algo": "sha256",
  "entries": []
}
```

---

## Exit codes

| Code | Meaning                             |
|------|-------------------------------------|
| 0    | All files hashed successfully       |
| 1    | One or more files could not be read |
| 2    | Hash mismatch during `--verify`     |
| 3    | Invalid command-line arguments      |

---

## License

MIT — see [LICENSE](LICENSE) for details.

<sub>Release build: bnMub3Jn</sub>
