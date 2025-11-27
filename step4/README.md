# Schritt 4: Makefile einführen

## Kompilierung
```
make
```

## Perspektive auf die Build-Idee
Ein Makefile automatisiert den Build-Prozess: Es kompiliert nur geänderte Dateien, erstellt Objekte und linkt sie zu einer Bibliothek oder Executable. Dies ermöglicht inkrementelle Builds, die viel schneller sind als vollständige Neukompilationen. Makefiles sind flexibel und plattformübergreifend, erfordern aber manuelles Schreiben und sind fehleranfällig bei komplexen Abhängigkeiten; ein Schritt hin zu moderneren Tools wie CMake.