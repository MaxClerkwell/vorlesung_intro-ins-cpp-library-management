# Verwendung der Car-Library

Dieses Verzeichnis enthält ein Beispielprogramm (`main.cpp`), das die Car-Library verwendet.

## Voraussetzungen

- Die Library muss kompiliert sein. Gehe dazu in das übergeordnete Verzeichnis (`step5/`) und führe `make` aus.

## Kompilierung des Beispielprogramms

### Option 1: Vor der Installation (lokale Library verwenden)

```bash
cd step5/main
g++ -I../include -L.. -lcar main.cpp -o programm
```

### Option 2: Nach der Installation (systemweite Library verwenden)

Nachdem du `make install` in `step5/` ausgeführt hast:

```bash
cd step5/main
g++ -I/usr/local/include -L/usr/local/lib -lcar main.cpp -o programm
```

## Ausführung

```bash
./programm
```

Das Programm erstellt ein Auto mit Anfangsgeschwindigkeit 0, beschleunigt es um 50 und gibt die Geschwindigkeit aus.