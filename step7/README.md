# Schritt 7: CMake + Vcpkg mit Manifest

Vcpkg ist ein freier, quelloffener Paketmanager für C++, der tausende Open-Source-Libraries für Windows, Linux und macOS bereitstellt. Es automatisiert das Herunterladen, Kompilieren und Installieren von C++-Bibliotheken, sodass Entwickler sich auf ihren Code konzentrieren können, anstatt manuell Dependencies zu verwalten. Vcpkg baut Libraries aus Quellcode und speichert sie in einem lokalen Cache, was zu schnellen, reproduzierbaren Builds führt.

Um Vcpkg zu verwenden, klone das Repository und initialisiere es:
```
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh  # Linux/Mac
# oder bootstrap-vcpkg.bat auf Windows
```

## Kompilierung
```
cmake -B build -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake && cmake --build build
```

## Perspektive auf die Build-Idee
Vcpkg integriert sich mit CMake über ein Manifest (`vcpkg.json`), das Dependencies deklariert. Dies ermöglicht schnelle, isolierte Builds mit Binaries aus dem Vcpkg-Repository. Ideal für Projekte mit vielen externen Libraries, da es Versionskonflikte vermeidet und die Setup-Zeit minimiert. Erfordert jedoch die Installation von Vcpkg und die Angabe des Toolchain-Files.

Vcpkg unterstützt auch das Hinzufügen eigener Libraries. Hierfür kann ein "Port" erstellt werden, der die Build-Anweisungen für die eigene Library enthält (z. B. mit CMake-Skripten). Dieser Port kann entweder lokal im Vcpkg-Clone verwendet oder zum offiziellen Vcpkg-Repository beigetragen werden. Dies ermöglicht die nahtlose Integration eigener Projekte in das Vcpkg-Ökosystem, wodurch sie wie jede andere Dependency verwaltet werden können.