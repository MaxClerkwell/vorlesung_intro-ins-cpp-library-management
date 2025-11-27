# Schritt 6: CMake + FetchContent

## Kompilierung
```
cmake -B build && cmake --build build
```

## Perspektive auf die Build-Idee
CMake mit FetchContent automatisiert das Herunterladen und Bauen von Abhängigkeiten zur Build-Zeit, ohne System-Installation. Dies sorgt für reproduzierbare, isolierte Builds und vermeidet Versionskonflikte. Es ist modern und skalierbar für C++-Projekte (2023+), erfordert aber CMake-Kenntnisse und kann bei großen Dependencies die initiale Build-Zeit erhöhen. Perfekt für kollaborative, plattformübergreifende Entwicklung.