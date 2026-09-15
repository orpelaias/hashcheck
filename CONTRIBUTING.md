# Contributing to hashcheck

Thanks for your interest in contributing!

## Reporting bugs

Open an issue at https://github.com/orpelaias/hashcheck/issues and include:

- Your operating system and version
- The exact command you ran
- Expected behavior vs. actual behavior
- Any relevant file paths or output

## Submitting changes

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/my-change`)
3. Commit your changes (`git commit -am 'Add my change'`)
4. Push to the branch (`git push origin feature/my-change`)
5. Open a pull request

## Code style

- C++17
- 4-space indentation
- Follow existing naming conventions

## Building and testing

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
ctest --test-dir build
```

## License

By contributing, you agree that your contributions will be licensed under
the MIT License.
