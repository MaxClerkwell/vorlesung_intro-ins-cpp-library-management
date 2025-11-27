# Library-Management in C++ – Schritt für Schritt

Dieses Projekt zeigt die typische Evolution einer einfachen C++-Anwendung hin zu einer professionell strukturierten, installierbaren und wiederverwendbaren Bibliothek.

Jeder Schritt baut auf dem vorherigen auf und zeigt, warum wir in der Praxis bestimmte Strukturen und Build-Werkzeuge verwenden.

## Schritt 1: Alles in einer Datei (`main.cpp`)

```bash
g++ main.cpp -o program
```

Eine einzige Datei enthält:
- Die Klassendeklaration
- Die Implementierung
- Die `main()`-Funktion

Vorteil: Extrem einfach zu kompilieren  
Nachteil: Nicht wiederverwendbar, alles wird bei jeder Kompilierung neu übersetzt

## Schritt 2: Header-Only Library (eine `.hpp`-Datei)

Wir trennen die Klassendefinition in `Book.hpp`. Die `main.cpp` inkludiert nur diese Datei.

```bash
g++ main.cpp -o program
```

Vorteile:
- Saubere Trennung von Schnittstelle und Anwendung
- Immer noch nur ein Befehl zum Kompilieren

Nachteile:
- Jede Übersetzungseinheit, die die Header-Datei einbindet, compiliert den gesamten Code neu → lange Build-Zeiten bei großen Bibliotheken

## Schritt 3: Klassische getrennte Library (.h + .cpp)

Jetzt trennen wir Deklaration und Definition vollständig:

```
include/
    library/
        Book.hpp
src/
    Book.cpp
```

Dadurch kann der Compiler die `.cpp`-Datei einmal kompilieren → Objektdatei → und später linken.

Aber: Wir brauchen jetzt ein Build-System, weil mehrere Dateien beteiligt sind.

## Schritt 4: Makefile einführen

Ein `Makefile` übernimmt jetzt:
- Kompilieren der `.cpp`-Dateien zu `.o`
- Erzeugen einer statischen (`libmylibrary.a`) oder dynamischen (`libmylibrary.so`) Bibliothek
- Linken des Testprogramms

Beispiel-Targets:
```makefile
all: program
lib: libmylibrary.a
install:   # kopiert Header nach /usr/local/include und lib nach /usr/local/lib
clean:
```

Jetzt wird deutlich schneller recompiliert – nur geänderte Dateien werden neu gebaut.

## Schritt 5: Die `main.cpp` verschwindet – echte Library wird installierbar

Das eigentliche Projekt enthält jetzt keine `main()` mehr. Stattdessen gibt es ein `install`-Target:

```bash
make && sudo make install
```

Danach liegt die Library systemweit vor:
- Header in `/usr/local/include/mylibrary/`
- Bibliothek in `/usr/local/lib/libmylibrary.a` oder `.so`

Andere Projekte können sie jetzt nutzen mit:

```bash
g++ myapp.cpp -lmylibrary -L/usr/local/lib -I/usr/local/include
```

## Woher bekommt man in der Praxis C++-Libraries?

| Quelle                                   | Wie man sie bekommt                                  | Vorteile                                                                 | Nachteile                                                       |
|------------------------------------------|-------------------------------------------------------|--------------------------------------------------------------------------|-----------------------------------------------------------------|
| **Paketmanager** (apt, dnf, brew, vcpkg, conan) | `sudo apt install libfmt-dev` <br> `vcpkg install fmt` | Sehr schnell, binary-cache, Versionen sind getestet, Dependency-Handling | Nicht immer aktuelle Version, manchmal veraltete Pakete        |
| **Selbst bauen + `make install`**       | `git clone ... && make && sudo make install`          | Immer aktuell, volle Kontrolle über Compile-Flags                        | Manuelle Arbeit, keine automatische Dependency-Auflösung       |
| **CMake + FetchContent**                 | Im eigenen `CMakeLists.txt`: <br> `FetchContent_Declare(...)` <br> `FetchContent_MakeAvailable(...)` | Library wird automatisch beim eigenen Build heruntergeladen und gebaut <br> Keine System-Installation nötig <br> Perfekt für Header-Only und kleine Libs | Erhöhte Build-Zeit beim ersten Mal, alles wird lokal compiliert |

### Besonders praktisch: CMake + FetchContent (Modern C++ Workflow)

```cmake
include(FetchContent)

FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 10.2.1
)

FetchContent_MakeAvailable(fmt)

target_link_libraries(myapp PRIVATE fmt::fmt)
```

→ Kein `sudo make install`, keine Pfad-Probleme, reproduzierbar, funktioniert auf jedem Rechner.

## Fazit – Die Entwicklung im Überblick

| Schritt                  | Komplexität | Build-Befehl         | Wiederverwendbarkeit | Build-Zeit | Typische Anwendung                      |
|--------------------------|-------------|----------------------|----------------------|------------|-----------------------------------------|
| Alles in `main.cpp`      | Sehr gering | `g++ main.cpp`       | keine                | schnell    | Lernprojekte, Skripte                   |
| Header-Only              | gering      | `g++ *.cpp`          | gut                  | langsam    | Kleine, templatierte Libs (z. B. {fmt}) |
| .h + .cpp + Makefile     | mittel      | `make && make install` | sehr gut           | schnell    | Klassische System-Libraries            |
| CMake + FetchContent     | modern      | `cmake -B build && cmake --build build` | hervorragend | schnell (nach erstem Fetch) | Aktuelle C++-Projekte (2023+)          |
