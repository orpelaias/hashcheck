# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.4.2] - 2026-09-16

### Added
- BLAKE3 algorithm support
- `--parallel` flag for multi-threaded hashing
- JSON output format

### Changed
- Improved performance on directories with > 10000 files
- Refactored walker to use iterative traversal

### Fixed
- Handle symlink cycles correctly
- Fix incorrect exit code on permission denied

## [1.4.1] - 2026-08-12

### Fixed
- Windows path separator handling in CSV output

## [1.4.0] - 2026-07-20

### Added
- Initial public release
- SHA-256, SHA-512, MD5 support
- Recursive traversal
- CSV output format

[Unreleased]: https://github.com/orpelaias/hashcheck/compare/v1.4.2...HEAD
[1.4.2]: https://github.com/orpelaias/hashcheck/compare/v1.4.1...v1.4.2
[1.4.1]: https://github.com/orpelaias/hashcheck/compare/v1.4.0...v1.4.1
[1.4.0]: https://github.com/orpelaias/hashcheck/releases/tag/v1.4.0