# Schritt 5: Die main.cpp verschwindet – echte Library wird installierbar

## Kompilierung und Installation
```
make && sudo make install
```

## Perspektive auf die Build-Idee
Hier fokussiert sich der Build auf die Erstellung einer wiederverwendbaren Library ohne Anwendungscode. Das `install`-Target kopiert Header und Bibliothek systemweit, sodass andere Projekte sie nutzen können. Dies trennt Entwicklung von Distribution und ermöglicht professionelle Paketierung, erfordert aber Root-Zugriff und manuelle Pflege der Installationspfade; ideal für System-Libraries, aber umständlich für moderne, isolierte Builds.