# Schritt 3: Klassische getrennte Library

## Kompilierung (manuell)
```
g++ -Iinclude src/Car.cpp main.cpp -o program
```

## Perspektive auf die Build-Idee
Durch die Trennung von Deklaration (.h) und Definition (.cpp) kann der Compiler die Implementierung einmal kompilieren und später wiederverwenden. Dies reduziert Build-Zeiten erheblich, erfordert aber manuelle Verwaltung der Include-Pfade und Abhängigkeiten. Ohne Build-System wie Makefiles wird es schnell unübersichtlich, weshalb dieser Schritt den Übergang zu automatisierten Tools motiviert.