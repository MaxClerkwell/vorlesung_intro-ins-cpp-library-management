# Schritt 1: Alles in einer Datei

## Kompilierung
```
g++ main.cpp -o program
```

## Perspektive auf die Build-Idee
Diese Methode ist extrem einfach und erfordert keine zusätzlichen Tools; alles ist in einer einzigen Datei. Bei jeder Änderung wird jedoch der gesamte Code neu kompiliert, was bei größeren Projekten ineffizient wird. Sie eignet sich für kleine Skripte oder Prototypen, wo Build-Zeit keine Rolle spielt, aber sie skaliert nicht gut für wiederverwendbare Libraries.