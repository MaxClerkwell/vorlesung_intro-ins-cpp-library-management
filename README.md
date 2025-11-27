# Library-Management in C++ – Schritt für Schritt

Dieses Projekt zeigt die typische Evolution einer einfachen C++-Anwendung hin zu einer professionell strukturierten, installierbaren und wiederverwendbaren Bibliothek.

Für Entwickler ist es entscheidend, die verschiedenen Weisen zu verstehen, auf die Libraries in C++-Projekte eingebunden werden können. Dies beeinflusst nicht nur die Effizienz des Builds (z. B. durch Vermeidung unnötiger Neukompilationen), sondern auch die Wartbarkeit, Wiederverwendbarkeit und Plattformübergreifende Kompatibilität des Codes. Ohne dieses Wissen können Projekte schnell unübersichtlich werden, Abhängigkeitskonflikte entstehen oder Build-Prozesse ineffizient bleiben – besonders in kollaborativen Umgebungen oder bei der Integration externer Libraries.

Jeder Schritt baut auf dem vorherigen auf und zeigt, warum wir in der Praxis bestimmte Strukturen und Build-Werkzeuge verwenden.

## Schritt 1: Alles in einer Datei (`main.cpp`)

```bash
g++ main.cpp -o program
```

Eine einzige Datei enthält:
- Die Klassendeklaration
- Die Implementierung
- Die `main()`-Funktion

**Beispielcode (main.cpp):**
```cpp
#include <iostream>

class Car {
private:
    int speed;
public:
    Car(int initialSpeed) : speed(initialSpeed) {}
    void accelerate(int amount) {
        speed += amount;
    }
    int getSpeed() const {
        return speed;
    }
};

int main() {
    Car car(0);
    car.accelerate(10);
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    return 0;
}
```

Vorteil: Extrem einfach zu kompilieren  
Nachteil: Nicht wiederverwendbar, alles wird bei jeder Kompilierung neu übersetzt

## Schritt 2: Header-Only Library (eine `.hpp`-Datei)

Wir trennen die Klassendefinition in `Car.hpp`. Die `main.cpp` inkludiert nur diese Datei.

```bash
g++ main.cpp -o program
```

**Beispielcode (Car.hpp):**
```cpp
#ifndef CAR_HPP
#define CAR_HPP

class Car {
private:
    int speed;
public:
    Car(int initialSpeed) : speed(initialSpeed) {}
    void accelerate(int amount) {
        speed += amount;
    }
    int getSpeed() const {
        return speed;
    }
};

#endif
```

**Beispielcode (main.cpp):**
```cpp
#include "Car.hpp"
#include <iostream>

int main() {
    Car car(0);
    car.accelerate(10);
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    return 0;
}
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
        Car.hpp
src/
    Car.cpp
```

Dadurch kann der Compiler die `.cpp`-Datei einmal kompilieren → Objektdatei → und später linken.

**Beispielcode (include/library/Car.hpp):**
```cpp
#ifndef CAR_HPP
#define CAR_HPP

class Car {
private:
    int speed;
public:
    Car(int initialSpeed);
    void accelerate(int amount);
    int getSpeed() const;
};

#endif
```

**Beispielcode (src/Car.cpp):**
```cpp
#include "library/Car.hpp"

Car::Car(int initialSpeed) : speed(initialSpeed) {}

void Car::accelerate(int amount) {
    speed += amount;
}

int Car::getSpeed() const {
    return speed;
}
```

**Beispielcode (main.cpp):**
```cpp
#include "library/Car.hpp"
#include <iostream>

int main() {
    Car car(0);
    car.accelerate(10);
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    return 0;
}
```

Aber: Wir brauchen jetzt ein Build-System, weil mehrere Dateien beteiligt sind. 
Manuelles Kompilieren wird schnell unübersichtlich, da man alle Abhängigkeiten und die richtige Reihenfolge beim Linken selbst verwalten müsste – ein Build-System übernimmt diese Aufgaben automatisch und vermeidet Fehler.

## Schritt 4: Makefile einführen

Ein Makefile ist ein Build-Skript, das vom Tool `make` verwendet wird, um den Kompilierungsprozess zu automatisieren. Es definiert Regeln zur Erzeugung von Dateien. Jede Regel besteht aus:
- **Target**: Das zu erzeugende Ziel (z. B. eine Executable oder Library).
- **Dependencies**: Die Dateien oder anderen Targets, von denen das Target abhängt (z. B. Quellcode-Dateien).
- **Recipe**: Die Befehle, die ausgeführt werden, um das Target zu erzeugen (z. B. Compiler-Aufrufe).

Ein `Makefile` übernimmt jetzt:
- Kompilieren der `.cpp`-Dateien zu `.o`
- Erzeugen einer statischen (`libmylibrary.a`) oder dynamischen (`libmylibrary.so`) Bibliothek
- Linken des Testprogramms

**Beispiel-Makefile (Auszug):**
```makefile
CXX = g++
CXXFLAGS = -Iinclude -std=c++11
OBJDIR = obj
LIBDIR = lib
BINDIR = bin

all: program

$(OBJDIR)/Car.o: src/Car.cpp include/library/Car.hpp
	$(CXX) $(CXXFLAGS) -c src/Car.cpp -o $(OBJDIR)/Car.o

$(OBJDIR)/main.o: main.cpp include/library/Car.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(OBJDIR)/main.o

$(LIBDIR)/libmylibrary.a: $(OBJDIR)/Car.o
	ar rcs $(LIBDIR)/libmylibrary.a $(OBJDIR)/Car.o

$(BINDIR)/program: $(OBJDIR)/main.o $(LIBDIR)/libmylibrary.a
	$(CXX) $(OBJDIR)/main.o -L$(LIBDIR) -lmylibrary -o $(BINDIR)/program
```

Beispiel-Targets:
```makefile
all: program
lib: libmylibrary.a
install:   # kopiert Header nach /usr/local/include und lib nach /usr/local/lib
clean:
```

Jetzt wird deutlich schneller recompiliert – nur geänderte Dateien werden neu gebaut.

Es gibt eine ganze Reihe solcher Build-Tools wie Ninja oder Meson, aber wir beschränken uns auf Make, da es die Lingua Franca in der C++-Welt darstellt und auf nahezu jedem System verfügbar ist.

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

**Beispiel-Nutzung in einem anderen Projekt (myapp.cpp):**
```cpp
#include <mylibrary/Car.hpp>
#include <iostream>

int main() {
    Car car(0);
    car.accelerate(10);
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    return 0;
}
```

## Woher bekommt man in der Praxis C++-Libraries?

| Quelle                                   | Wie man sie bekommt                                  | Vorteile                                                                 | Nachteile                                                       |
|------------------------------------------|-------------------------------------------------------|--------------------------------------------------------------------------|-----------------------------------------------------------------|
| **Paketmanager** (apt, dnf, brew, vcpkg, conan) | `sudo apt install libfmt-dev` <br> `vcpkg install fmt` | Sehr schnell, binary-cache, Versionen sind getestet, Dependency-Handling | Nicht immer aktuelle Version, manchmal veraltete Pakete        |
| **Selbst bauen + `make install`**       | `git clone ... && make && sudo make install`          | Immer aktuell, volle Kontrolle über Compile-Flags                        | Manuelle Arbeit, keine automatische Dependency-Auflösung       |
| **CMake + FetchContent**                 | Im eigenen `CMakeLists.txt`: <br> `FetchContent_Declare(...)` <br> `FetchContent_MakeAvailable(...)` | Library wird automatisch beim eigenen Build heruntergeladen und gebaut <br> Keine System-Installation nötig <br> Perfekt für Header-Only und kleine Libs | Erhöhte Build-Zeit beim ersten Mal, alles wird lokal compiliert |

Allerdings bringt das systemweite Installieren von Libraries Gefahren mit sich: Versionskonflikte zwischen Projekten, eine 'verschmutzte' Systemumgebung oder Schwierigkeiten bei der Reproduzierbarkeit von Builds. Daher ziehen moderne C++-Projekte es vor, Dependencies lokal im Build-Ordner zu halten, um Isolation, saubere Umgebungen und einfache Reproduzierbarkeit zu gewährleisten.

### Besonders praktisch: CMake + FetchContent (Modern C++ Workflow)

CMake ist ein mächtiges, plattformübergreifendes Build-System, das die Komplexität von C++-Builds abstrahiert. Es generiert automatisch Makefiles, Ninja-Skripte oder andere Build-Dateien für verschiedene Compiler und Betriebssysteme, wodurch Projekte einfach skalierbar und wartbar werden. Im Gegensatz zu reinen Makefiles ist CMake deklarativ und erlaubt es, Abhängigkeiten und Targets auf hohem Niveau zu definieren.

FetchContent ist ein spezielles CMake-Modul (ab Version 3.11), das externe Libraries direkt während des Build-Prozesses herunterlädt, konfiguriert und baut. Dies bringt enorme Vorteile:
- **Isolation**: Dependencies werden lokal im Build-Ordner gehalten, ohne das System zu 'verschmutzen' oder Versionskonflikte zu verursachen.
- **Reproduzierbarkeit**: Jeder Entwickler oder CI-System baut die exakt gleichen Versionen der Libraries, was Fehler durch unterschiedliche Umgebungen vermeidet.
- **Einfachheit**: Kein manuelles Klonen, Bauen oder Installieren nötig – alles geschieht automatisch.
- **Aktualität und Kontrolle**: Man kann spezifische Git-Tags, Branches oder Commits angeben, um immer die gewünschte Version zu bekommen.
- **Plattformübergreifend**: Funktioniert auf Windows, Linux, macOS ohne Anpassungen.

Dies macht CMake + FetchContent zum Goldstandard für moderne C++-Projekte, besonders in kollaborativen Umgebungen.

```cmake
include(FetchContent)

FetchContent_Declare(
    vorlesungs_cpplib
    GIT_REPOSITORY https://github.com/MaxClerkwell/vorlesungs_cpplib.git
)

FetchContent_MakeAvailable(vorlesungs_cpplib)

add_executable(myapp main.cpp)
target_link_libraries(myapp vorlesungs_cpplib)
```

**Beispielcode (CMakeLists.txt):**
```cmake
cmake_minimum_required(VERSION 3.14)
project(library_test)

include(FetchContent)

FetchContent_Declare(
    vorlesungs_cpplib
    GIT_REPOSITORY https://github.com/MaxClerkwell/vorlesungs_cpplib.git
)

FetchContent_MakeAvailable(vorlesungs_cpplib)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} vorlesungs_cpplib)
```

**Beispielcode (main.cpp):**
```cpp
#include "Car.h"
#include <iostream>

int main() {
    Car car(0);
    car.accelerate(10);
    std::cout << "Speed: " << car.getSpeed() << std::endl;
    return 0;
}
```

→ Kein `sudo make install`, keine Pfad-Probleme, reproduzierbar, funktioniert auf jedem Rechner.

## Fazit – Die Entwicklung im Überblick

| Schritt                  | Komplexität | Build-Befehl         | Wiederverwendbarkeit | Build-Zeit | Typische Anwendung                      |
|--------------------------|-------------|----------------------|----------------------|------------|-----------------------------------------|
| Alles in `main.cpp`      | Sehr gering | `g++ main.cpp`       | keine                | schnell    | Lernprojekte, Skripte                   |
| Header-Only              | gering      | `g++ *.cpp`          | gut                  | langsam    | Kleine, templatierte Libs (z. B. {fmt}) |
| .h + .cpp + Makefile     | mittel      | `make && make install` | sehr gut           | schnell    | Klassische System-Libraries            |
| CMake + FetchContent     | modern      | `cmake -B build && cmake --build build` | hervorragend | schnell (nach erstem Fetch) | Aktuelle C++-Projekte (2023+)          |
| CMake + Vcpkg            | professionell | `cmake -B build -DCMAKE_TOOLCHAIN_FILE=... && cmake --build build` | hervorragend | sehr schnell | Große Projekte mit vielen Dependencies |

## Moderner Ansatz: CMake + Vcpkg mit Manifest

Für noch professionellere Projekte bietet sich die Kombination aus CMake und Vcpkg an. Vcpkg ist ein Open-Source-Paketmanager für C++, der tausende Libraries baut und bereitstellt. Im Gegensatz zu FetchContent lädt Vcpkg Binaries herunter (falls verfügbar) oder baut sie vorab, was die Build-Zeit drastisch reduziert.

Der Schlüssel ist das **Manifest** (`vcpkg.json`), eine JSON-Datei, die Dependencies deklariert. CMake integriert sich nahtlos mit Vcpkg via `find_package()`.

**Vorteile:**
- **Schnell**: Vcpkg nutzt Binaries, wenn möglich, und vermeidet Neubauten.
- **Umfassend**: Unterstützt tausende Libraries mit Versionskontrolle.
- **Plattformübergreifend**: Funktioniert auf Windows, Linux, macOS.
- **Isoliert**: Dependencies bleiben im Projekt-Ordner.

**Beispiel vcpkg.json:**
```json
{
  "name": "myproject",
  "version": "1.0.0",
  "dependencies": [
    "fmt",
    "boost"
  ]
}
```

**Beispiel CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.14)
project(myproject)

find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE fmt::fmt Boost::boost)
```

**Setup:**
1. Installiere Vcpkg: `git clone https://github.com/Microsoft/vcpkg.git && ./vcpkg/bootstrap-vcpkg.sh`
2. Integriere in CMake: Setze `CMAKE_TOOLCHAIN_FILE` auf `path/to/vcpkg/scripts/buildsystems/vcpkg.cmake`
3. Baue: `cmake -B build && cmake --build build`

Dieser Ansatz ist ideal für große Projekte mit vielen Dependencies und bietet eine Balance zwischen Geschwindigkeit und Kontrolle.
