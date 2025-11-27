# Schritt 2: Header-Only Library

## Kompilierung
```
g++ main.cpp -o program
```

## Perspektive auf die Build-Idee
Header-Only Libraries sind einfach zu verteilen, da nur eine Datei benötigt wird. Der Compiler muss jedoch bei jeder Include-Stelle den gesamten Code neu kompilieren, was zu längeren Build-Zeiten bei großen Libraries führt. Dies ist ideal für kleine, templatierte Bibliotheken (z. B. {fmt}), aber weniger geeignet für komplexe Projekte mit vielen Abhängigkeiten.